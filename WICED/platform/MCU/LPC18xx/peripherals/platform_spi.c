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
 *
 *This implemenration is not complete.
 */
#include "platform_peripheral.h"
#include "chip.h"
#include "RTOS/wwd_rtos_interface.h"
#include "wwd_assert.h"

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
 *               Function Declarations
 ******************************************************/

/******************************************************
 *                   Variables
 ******************************************************/

/******************************************************
 *               Function Definitions
 ******************************************************/

uint8_t platform_spi_get_port_number( platform_spi_port_t* spi )
{
    UNUSED_PARAMETER (spi );
    return 0;
}

platform_result_t platform_spi_init( const platform_spi_t* spi, const platform_spi_config_t* config )
{

    CHIP_CCU_CLK_T clkSSP;
    uint32_t num_bits;
    uint32_t clock_mode;
    platform_spi_t* spi_ptr = (platform_spi_t*) spi;
    LPC_SSP_T*   spi_base = ( LPC_SSP_T* )spi_ptr->spi_base;

    if( spi_ptr->semaphore_is_inited == WICED_FALSE )
    {
        host_rtos_init_semaphore( &spi_ptr->in_use_semaphore );
        spi_ptr->semaphore_is_inited = WICED_TRUE;
    }
    else
    {
        host_rtos_get_semaphore( &spi_ptr->in_use_semaphore, NEVER_TIMEOUT, WICED_FALSE );
    }

    /* Mux the port and pin to direct it to SPI */
    platform_pin_set_alternate_function( &spi_ptr->clock );
    platform_pin_set_alternate_function( &spi_ptr->miso  );
    platform_pin_set_alternate_function( &spi_ptr->mosi  );

    if ( spi_ptr->enable_cs_emulation == WICED_TRUE )
    {
        platform_gpio_init( config->chip_select, OUTPUT_PUSH_PULL );
        platform_gpio_output_high( config->chip_select );
    }
    else
    {
        platform_pin_set_alternate_function( &config->chip_select->hw_pin  );
    }

    /* for LPC18xx SSP only master mode is supported. */
    //Chip_SSP_Init( spi_base );


    if (spi_base == LPC_SSP1) {
        clkSSP = CLK_MX_SSP1;
    }
    else {
        clkSSP = CLK_MX_SSP0;
    }

    Chip_Clock_Enable(clkSSP);

    num_bits =  config->bits - 1 ;
    if ( config->mode & SPI_CLOCK_IDLE_HIGH )
    {
        if ( config->mode & SPI_CLOCK_RISING_EDGE )
        {
            /* CPOL=1, CPHA=1 */
            /* Clock idle state is one. Data are captured on the rising edge and propagated on the falling edge */
            clock_mode = SSP_CLOCK_MODE3;
        }
        else
        {
            /* CPOL=1, CPHA=0 */
            /* Clock idle state is one. Data are captured on the falling edge and propagated on the rising edge */
            clock_mode = SSP_CLOCK_MODE2;
        }
    }
    else
    {
        if ( config->mode & SPI_CLOCK_RISING_EDGE )
        {
            /* CPOL=0, CPHA=0 */
            /* Clock idle state is low. Data are captured on the rising edge and propagated on the falling edge */
            clock_mode = SSP_CLOCK_MODE0;
        }
        else
        {
            /* CPOL=0, CPHA=1 */
            /* Clock idle state is low. Data are captured on the falling edge and propagated on the rising edge */
            clock_mode = SSP_CLOCK_MODE1;
        }
    }
    //Chip_Clock_Enable(Chip_SSP_GetClockIndex(spi_base));
    Chip_SSP_Set_Mode(spi_base, SSP_MODE_MASTER);
    Chip_SSP_SetFormat( spi_base, num_bits, SSP_FRAMEFORMAT_SPI, clock_mode );
    Chip_SSP_SetBitRate( spi_base, config->speed );
    Chip_SSP_Int_Disable( spi_base );
    Chip_SSP_Enable( spi_base );

    return WICED_SUCCESS;
}

platform_result_t platform_spi_deinit( const platform_spi_t* spi )
{
    platform_spi_t* spi_ptr = (platform_spi_t*) spi;
    UNUSED_PARAMETER( spi );

    if ( spi_ptr->semaphore_is_inited == WICED_FALSE )
    {
        return PLATFORM_ERROR;
    }
    Chip_SCU_PinMuxSet( spi_ptr->clock.group, spi_ptr->clock.pin, 0 );
    Chip_SCU_PinMuxSet( spi_ptr->mosi.group, spi_ptr->mosi.pin, 0 );
    Chip_SCU_PinMuxSet( spi_ptr->miso.group, spi_ptr->miso.pin, 0 );

    host_rtos_set_semaphore( &spi_ptr->in_use_semaphore, WICED_FALSE );
    Chip_SSP_Disable( ( LPC_SSP_T* ) spi_ptr->spi_base );

    /* TODO: unimplemented */
    return PLATFORM_UNSUPPORTED;
}

platform_result_t platform_spi_transfer( const platform_spi_t* spi, const platform_spi_config_t* config, const platform_spi_message_segment_t* segments, uint16_t number_of_segments )
{
    platform_result_t       result      = PLATFORM_SUCCESS;
    LPC_SSP_T*              spi_base    = ( LPC_SSP_T* ) spi->spi_base;
    Chip_SSP_DATA_SETUP_T   ssp_setup;
    uint32_t                segment_index;
    platform_spi_t*         spi_ptr     = (platform_spi_t*) spi;


    if ( spi_ptr->enable_cs_emulation == WICED_TRUE )
    {
        platform_gpio_output_low( config->chip_select );
    }


    for ( segment_index = 0; segment_index < number_of_segments; segment_index++ )
    {
        ssp_setup.length  = segments[ segment_index ].length;
        ssp_setup.rx_data = segments[ segment_index ].rx_buffer;
        ssp_setup.tx_data = (void *) segments[ segment_index ].tx_buffer;
        ssp_setup.tx_cnt  = 0;
        ssp_setup.rx_cnt  = 0;

        Chip_SSP_RWFrames_Blocking( spi_base, &ssp_setup );
    }

    if ( spi_ptr->enable_cs_emulation == WICED_TRUE )
    {
        platform_gpio_output_high( config->chip_select );
    }


    /* TODO: utilize config to updat SSP configuration. */
    UNUSED_PARAMETER( config );
    return result;
}

