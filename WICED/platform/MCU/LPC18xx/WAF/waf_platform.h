/*
 * Copyright 2015, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *                   Constants
 ******************************************************/

/******************************************************
 *                    Macros
 ******************************************************/
#define DCT1_START_ADDR  ((uint32_t)&dct1_start_addr_loc)
#define DCT1_SIZE        ((uint32_t)&dct1_size_loc)
#define DCT1_END_ADDR    ( DCT1_START_ADDR + DCT1_SIZE - 1 )
#define DCT2_START_ADDR  ((uint32_t)&dct2_start_addr_loc)
#define DCT2_SIZE        ((uint32_t)&dct2_size_loc)
#define DCT2_END_ADDR    ( DCT2_START_ADDR + DCT2_SIZE - 1 )
#define SRAM_START_ADDR  ((uint32_t)&sram_start_addr_loc)
#define SRAM_SIZE        ((uint32_t)&sram_size_loc)

#define LPC18XX_BANKA_START_ADDRESS                   ( 0x1A000000 )
#define LPC18XX_BANKA_START_SECTOR                    ( 0 )
#define LPC18XX_BANKA_END_SECTOR                      ( 14 )
#define LPC18XX_BANKB_START_SECTOR                    ( 15 )
#define LPC18XX_BANKB_END_SECTOR                      ( 29 )
#define LPC18XX_BANKA_START_64KBYTE_SECTOR_RANGE      ( 0x1A010000 )
#define LPC18XX_BANKB_START_ADDRESS                   ( 0x1B000000 )
#define LPC18XX_BANKB_START_64KBYTE_SECTOR_RANGE      ( 0x1B010000 )
#define IS_ADDRESS_IN_BANKB_64K_SECTOR_RANGE(address) ( ( address > LPC18XX_BANKB_START_64KBYTE_SECTOR_RANGE ) ? ( 1 ) : ( 0 ) )
#define IS_ADDRESS_IN_BANKA_64K_SECTOR_RANGE(address) ( ( address > LPC18XX_BANKA_START_64KBYTE_SECTOR_RANGE ) ? ( 1 ) : ( 0 ) )
#define IS_ADDRESS_IN_BANKA(address)                  ( ( address < LPC18XX_BANKB_START_ADDRESS )              ? ( 1 ) : ( 0 ) )
#define IS_ADDRESS_IN_BANKB(address)                  ( ( address >= LPC18XX_BANKB_START_ADDRESS )              ? ( 1 ) : ( 0 ) )
#define LPC18XX_BANKA_SECTOR(address) \
    ( IS_ADDRESS_IN_BANKA_64K_SECTOR_RANGE(address) ? ( 8 + ( ( address - LPC18XX_BANKA_START_64KBYTE_SECTOR_RANGE ) / ( 64*1024 ) ) ) : ( ( address - LPC18XX_BANKA_START_ADDRESS ) / ( 8*1024 ) ) )
#define LPC18XX_BANKB_SECTOR(address) \
    ( IS_ADDRESS_IN_BANKB_64K_SECTOR_RANGE(address) ? ( 8 + ( ( address - LPC18XX_BANKB_START_64KBYTE_SECTOR_RANGE ) / ( 64*1024 ) ) ) : ( ( address - LPC18XX_BANKB_START_ADDRESS ) / ( 8*1024 ) ) )

#define PLATFORM_DCT_COPY1_START_ADDRESS              ( DCT1_START_ADDR )
#define PLATFORM_DCT_COPY1_END_ADDRESS                ( DCT1_END_ADDR )
#define PLATFORM_DCT_COPY2_START_ADDRESS              ( DCT2_START_ADDR )
#define PLATFORM_DCT_COPY2_END_ADDRESS                ( DCT2_END_ADDR )

#define PLATFORM_DCT_COPY1_START_SECTOR \
    ( (IS_ADDRESS_IN_BANKA(DCT1_START_ADDR)) ? ( LPC18XX_BANKA_SECTOR(DCT1_START_ADDR) ) : ( LPC18XX_BANKB_SECTOR(DCT1_START_ADDR) + LPC18XX_BANKB_START_SECTOR  ) )
#define PLATFORM_DCT_COPY1_END_SECTOR   \
    ( (IS_ADDRESS_IN_BANKA(DCT1_END_ADDR))   ? ( LPC18XX_BANKA_SECTOR(DCT1_END_ADDR) )   : ( LPC18XX_BANKB_SECTOR(DCT1_END_ADDR) + LPC18XX_BANKB_START_SECTOR ) )

#define PLATFORM_DCT_COPY2_START_SECTOR \
    ( (IS_ADDRESS_IN_BANKA(DCT2_START_ADDR)) ? ( LPC18XX_BANKA_SECTOR(DCT2_START_ADDR) ) : ( LPC18XX_BANKB_SECTOR(DCT2_START_ADDR) + LPC18XX_BANKB_START_SECTOR  ) )
#define PLATFORM_DCT_COPY2_END_SECTOR   \
    ( (IS_ADDRESS_IN_BANKA(DCT2_END_ADDR))   ? ( LPC18XX_BANKA_SECTOR(DCT2_END_ADDR) )   : ( LPC18XX_BANKB_SECTOR(DCT2_END_ADDR) + LPC18XX_BANKB_START_SECTOR ) )

/* DEFAULT APPS (eg FR and OTA) need only be loaded once. */
#define PLATFORM_DEFAULT_LOAD                         ( WICED_FRAMEWORK_LOAD_ONCE )

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
/* These come from the linker script */
extern void* dct1_start_addr_loc;
extern void* dct1_size_loc;
extern void* dct2_start_addr_loc;
extern void* dct2_size_loc;

/******************************************************
 *               Function Declarations
 ******************************************************/

/* WAF platform functions */
void platform_start_app         ( uint32_t entry_point );
void platform_load_app_chunk    ( const image_location_t* app_header_location, uint32_t offset, void* physical_address, uint32_t size );
void platform_erase_app_area    ( uint32_t physical_address, uint32_t size );
platform_result_t platform_erase_flash       ( uint16_t start_sector, uint16_t end_sector );
platform_result_t platform_write_flash_chunk ( uint32_t address, const void* data, uint32_t size );

/* Factory reset required function (defined in platform.c) */
wiced_bool_t platform_check_factory_reset( void );

#ifdef __cplusplus
} /* extern "C" */
#endif

