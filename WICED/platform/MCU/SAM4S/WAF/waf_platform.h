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
extern "C"
{
#endif

/******************************************************
 *                   Constants
 ******************************************************/

/******************************************************
 *                    Macros
 ******************************************************/
#define APP_HDR_START_ADDR                   ((uint32_t)&app_hdr_start_addr_loc)
#define APP_CODE_START_ADDR                  ((uint32_t)&app_code_start_addr_loc)
#define DCT1_START_ADDR                      ((uint32_t)&dct1_start_addr_loc)
#define DCT1_SIZE                            ((uint32_t)&dct1_size_loc)
#define DCT2_START_ADDR                      ((uint32_t)&dct2_start_addr_loc)
#define DCT2_SIZE                            ((uint32_t)&dct2_size_loc)
/*
 * Memory Layout
 * +------------------------------+
 * |                              | Lock Region 0 (8KB)
 * +--------- Bootloader ---------+
 * |                              | Lock Region 1 (8KB)
 * +------------------------------+
 * |                              | Lock Region 2 (8KB)
 * +------------ DCT1 ------------+
 * |                              | Lock Region 3 (8KB)
 * +------------------------------+
 * |                              | Lock Region 4 (8KB)
 * +------------ DCT2 ------------+
 * |                              | Lock Region 5 (8KB)
 * +------------------------------+
 *
 * Section Definition
 * ==================
 * A sector in here refers to SAM4S LOCK REGION (8KB). This design decision is
 * made to align sector size with DCT block size and bootloader size.
 *
 * Page Definition
 * ===============
 * A page in here refers to SAM4S page (512B). SAM4S only supports page write.
 */

#define PLATFORM_DCT_COPY1_START_SECTOR      ( 2 )                           /* Lock Region 2 */
#define PLATFORM_DCT_COPY1_START_ADDRESS     ( DCT1_START_ADDR )             /*               */
#define PLATFORM_DCT_COPY1_END_SECTOR        ( 3 )                           /* Lock Region 3 */
#define PLATFORM_DCT_COPY1_END_ADDRESS       ( DCT1_START_ADDR + DCT1_SIZE ) /*               */
#define PLATFORM_DCT_COPY2_START_SECTOR      ( 4  )                          /* Lock Region 4 */
#define PLATFORM_DCT_COPY2_START_ADDRESS     ( DCT2_START_ADDR )             /*               */
#define PLATFORM_DCT_COPY2_END_SECTOR        ( 5 )                           /* Lock Region 5 */
#define PLATFORM_DCT_COPY2_END_ADDRESS       ( DCT1_START_ADDR + DCT1_SIZE ) /*               */

/* DEFAULT APPS (eg FR and OTA) need only be loaded once. */
#define PLATFORM_DEFAULT_LOAD                ( WICED_FRAMEWORK_LOAD_ONCE )

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
platform_result_t  platform_erase_flash       ( uint16_t start_sector, uint16_t end_sector );
platform_result_t  platform_write_flash_chunk ( uint32_t address, const void* data, uint32_t size );

/* Factory reset required function (defined in platform.c) */
wiced_bool_t platform_check_factory_reset( void );

#ifdef __cplusplus
} /* extern "C" */
#endif

