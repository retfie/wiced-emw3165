/*
 * Copyright 2015, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

/** @file
 *  I/O functions
 *
 *  Provides functions for sending and receiving to the network for use by
 *  framing layer.
 */
#include "amqp_frame.h"
#include "amqp_network.h"

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/
#define TCP_SERVER_THREAD_PRIORITY          (WICED_DEFAULT_LIBRARY_PRIORITY)
#define TCP_SERVER_STACK_SIZE               (6200)
#define TCP_CLIENT_PORT                     (50007)
#define TCP_CLIENT_INTERVAL                 (2)
#define TCP_CLIENT_CONNECT_TIMEOUT          (500)
#define TCP_CONNECTION_NUMBER_OF_RETRIES    (3)

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/
typedef struct wiced_amqp_network_message_s
{
    wiced_packet_t                   *packet;
    void                             *data;
} wiced_amqp_network_message_t;

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *               Static Function Declarations
 ******************************************************/
static void amqp_network_recv_thread ( uint32_t arg );
static void amqp_network_queue_thread( uint32_t arg );

/******************************************************
 *               Variable Definitions
 ******************************************************/

/******************************************************
 *               Function Definitions
 ******************************************************/

wiced_result_t amqp_network_init( const wiced_ip_address_t *server_ip_address, uint16_t portnumber, wiced_interface_t interface, void *p_user, wiced_amqp_socket_t *socket, const wiced_amqp_socket_security_t *security )
{
    wiced_result_t result;

    /* Create a TCP socket */
    if (( result = wiced_tcp_create_socket( &socket->socket, interface) ) != WICED_SUCCESS)
    {
        goto ERROR_CREATE_SOCKET;
    }

    if ( security != NULL )
    {
        if ( ( result = wiced_tls_init_root_ca_certificates( security->ca_cert ) ) != WICED_SUCCESS )
        {
            goto ERROR_CA_CERT_INIT;
        }

        if ( ( result = wiced_tls_init_advanced_context( &socket->tls_context, security->cert, security->key ) ) != WICED_SUCCESS )
        {
            goto ERROR_TLS_INIT;
        }
        wiced_tcp_enable_tls( &socket->socket, &socket->tls_context );
    }

    /* Bind to the socket */
    wiced_tcp_bind( &socket->socket, TCP_CLIENT_PORT );
    wiced_rtos_init_semaphore( &socket->net_semaphore );

    socket->quit   = WICED_FALSE;
    socket->p_user = p_user;
    if ( ( result = wiced_rtos_init_queue( &socket->queue, "amqp", sizeof(wiced_amqp_network_message_t), 3 ) ) != WICED_SUCCESS )
    {
        goto ERROR_QUE_INIT;
    }
    if ( ( result = wiced_rtos_create_thread( &socket->net_thread, TCP_SERVER_THREAD_PRIORITY, "aqmp network thread", amqp_network_recv_thread, TCP_SERVER_STACK_SIZE, socket ) ) != WICED_SUCCESS )
    {
        goto ERROR_QUE_THREAD;
    }
    if ( ( result = wiced_rtos_create_thread( &socket->queue_thread, WICED_DEFAULT_LIBRARY_PRIORITY, "amqp", amqp_network_queue_thread, TCP_SERVER_STACK_SIZE, socket ) ) != WICED_SUCCESS )
    {
        goto ERROR_RCV_THREAD;
    }

    socket->server_ip_address   = *server_ip_address;
    socket->portnumber          = portnumber;

    return WICED_SUCCESS;

ERROR_RCV_THREAD:
    wiced_rtos_thread_force_awake( &socket->queue_thread );
    wiced_rtos_thread_join( &socket->queue_thread );
    wiced_rtos_delete_thread( &socket->queue_thread );
ERROR_QUE_THREAD:
    wiced_rtos_deinit_queue( &socket->queue );
ERROR_QUE_INIT:
    if ( security == NULL ) goto ERROR_CA_CERT_INIT;
    wiced_tls_reset_context( socket->socket.tls_context );
ERROR_TLS_INIT:
    wiced_tls_deinit_root_ca_certificates( );
ERROR_CA_CERT_INIT:
    wiced_tcp_delete_socket( &socket->socket );
ERROR_CREATE_SOCKET:
    return result;
}

wiced_result_t amqp_network_connect( wiced_amqp_socket_t *socket )
{
    wiced_result_t  result;
    int             connection_retries;

    /* Connect to the remote TCP server, try several times */
    connection_retries = 0;
    do
    {
        result = wiced_tcp_connect( &socket->socket, &socket->server_ip_address, socket->portnumber, TCP_CLIENT_CONNECT_TIMEOUT );
        connection_retries++;
    }
    while( ( result != WICED_SUCCESS ) && ( connection_retries < TCP_CONNECTION_NUMBER_OF_RETRIES ) );

    if( result != WICED_SUCCESS)
    {
        return result;
    }
    wiced_rtos_set_semaphore( &socket->net_semaphore );

    return WICED_SUCCESS;
}

wiced_result_t amqp_network_disconnect( wiced_amqp_socket_t *socket )
{
    return wiced_tcp_disconnect( &socket->socket );
}

wiced_result_t amqp_network_deinit( wiced_amqp_socket_t *socket )
{

    socket->quit = WICED_TRUE;
    if ( wiced_rtos_is_current_thread( &socket->net_thread ) != WICED_SUCCESS )
    {
        wiced_rtos_thread_force_awake( &socket->net_thread );
        wiced_rtos_thread_join( &socket->net_thread );
        wiced_rtos_delete_thread( &socket->net_thread );
    }

    wiced_rtos_thread_force_awake( &socket->queue_thread );
    wiced_rtos_thread_join( &socket->queue_thread );
    wiced_rtos_delete_thread( &socket->queue_thread );

    if ( socket->socket.tls_context != NULL )
    {
        wiced_tls_deinit_root_ca_certificates();
    }

    return WICED_SUCCESS;
}

wiced_result_t amqp_network_create_buffer( wiced_amqp_buffer_t *buffer, uint16_t size, wiced_amqp_socket_t *socket)
{
    uint16_t available_data_length;

    /* Create the TCP packet. Memory for the tx_data is automatically allocated */
    return wiced_packet_create_tcp( &socket->socket, size, &buffer->packet, &buffer->data, &available_data_length);
}

wiced_result_t amqp_network_delete_buffer( wiced_amqp_buffer_t *buffer)
{

    /* Create the TCP packet. Memory for the tx_data is automatically allocated */
    return wiced_packet_delete( buffer->packet );
}

wiced_result_t amqp_network_send_buffer( const wiced_amqp_buffer_t *buffer, wiced_amqp_socket_t *socket)
{
    wiced_amqp_network_message_t message;

    message.packet = buffer->packet;
    message.data   = buffer->data;
    return wiced_rtos_push_to_queue( &socket->queue, &message, NEVER_TIMEOUT );
}

static void amqp_network_recv_thread(uint32_t arg)
{
    wiced_result_t result;
    wiced_amqp_socket_t* socket = (wiced_amqp_socket_t*) arg;

    while ( socket->quit != WICED_TRUE )
    {
        /* Wait here if not connected */
        wiced_rtos_get_semaphore( &socket->net_semaphore, NEVER_TIMEOUT );
        while( 1 )
        {
            uint8_t           *data;
            wiced_packet_t    *packet;

            /* Receive the query from the TCP client */
            result = wiced_tcp_receive( &socket->socket, &packet, WICED_WAIT_FOREVER );
            if ( result == WICED_SUCCESS)
            {
                uint16_t                     rx_data_length;
                uint16_t                     available_data_length;
                uint16_t                     current_size = 0;

                wiced_amqp_buffer_t buffer;

                /* Process the client request */
                wiced_packet_get_data(packet, 0, (uint8_t**)(&data), &rx_data_length, &available_data_length);
                while ( current_size < rx_data_length )
                {
                    uint32_t    size;
                    buffer.packet = packet;
                    buffer.data   = data + current_size;
                    if ( amqp_frame_recv( &buffer, socket->p_user, &size ) != WICED_SUCCESS )
                    {
                        break;
                    }
                    current_size = (uint16_t)( current_size + size );
                }
                /* Delete the packet, we're done with it */
                wiced_packet_delete( buffer.packet );
            }
            else
            {
                /* Send failed or connection has been lost, close the existing connection and */
                /* get ready to accept the next one */
                if ( socket->socket.tls_context != NULL )
                {
                    wiced_tls_reset_context( socket->socket.tls_context );
                }
                wiced_tcp_disconnect( &socket->socket );
                break;
            }
        }
    }

    wiced_tcp_delete_socket( &socket->socket );

    WICED_END_OF_CURRENT_THREAD( );
}

/*
 * Serialize all AMQP events for connection and channels to avoid any asynchronus behaviour.
 * The thread waits on the amqp_queue which can be fed by the user or the network receiving thread
 */
static void amqp_network_queue_thread( uint32_t arg )
{
    wiced_amqp_network_message_t message;
    wiced_amqp_socket_t         *socket = (wiced_amqp_socket_t*)arg;
    wiced_queue_t               *queue  = &socket->queue;

    while ( socket->quit != WICED_TRUE )
    {
        wiced_result_t result = wiced_rtos_pop_from_queue( queue, &message, NEVER_TIMEOUT );

        /* Check if we have any services that require re-announcement */
        if (result != WICED_SUCCESS)
        {
            break;
        }

        /* Set the end of the data portion */
        wiced_packet_set_data_end( message.packet, message.data );
        result = wiced_tcp_send_packet( &socket->socket,message.packet );
        if ( result != WICED_SUCCESS )
        {
            /* Delete packet, since the send failed */
            wiced_packet_delete( message.packet );
        }
    }
    wiced_rtos_deinit_queue( queue );

    WICED_END_OF_CURRENT_THREAD( );
}


