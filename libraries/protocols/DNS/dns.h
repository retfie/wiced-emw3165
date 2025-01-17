/*
 * Copyright 2015, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

/**
 * @file Public API for DNS protocol
 */

#pragma once

#include "wiced_tcpip.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *                 Global Variables
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/

/* DNS Client API */

/** Adds the IP address of a DNS server to the list used by the DNS client
 *
 * @param[in] address : The IP address of the DNS server
 *
 * @return @ref wiced_result_t
 */
wiced_result_t dns_client_add_server_address          ( wiced_ip_address_t address );


/** Wipes out the list of DNS servers used by the DNS client
 *
 * @return @ref wiced_result_t
 */
wiced_result_t dns_client_remove_all_server_addresses ( void );


/** Lookup a hostname (domain name) using the DNS client
 *
 * @param[in]  hostname   : The hostname string to look-up
 * @param[out] address    : Receives the IP address matching the hostname
 * @param[in]  timeout_ms : The timeout period in milliseconds
 *
 * @return @ref wiced_result_t
 */
wiced_result_t dns_client_hostname_lookup             ( const char* hostname, wiced_ip_address_t* address, uint32_t timeout_ms );

#ifdef __cplusplus
} /* extern "C" */
#endif
