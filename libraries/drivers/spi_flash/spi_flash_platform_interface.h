/*
 * Copyright 2015, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#ifndef INCLUDED_SPI_FLASH_PLATFORM_INTERFACE_H
#define INCLUDED_SPI_FLASH_PLATFORM_INTERFACE_H

#ifdef __cplusplus
 extern "C" {
#endif


 typedef struct
 {
     /*@null@*/ /*@observer@*/  const void*   tx_buffer;
     /*@null@*/ /*@dependent@*/ void*         rx_buffer;
                                unsigned long length;
 } sflash_platform_message_segment_t;

extern int sflash_platform_init      ( /*@shared@*/ void* peripheral_id, /*@out@*/ void** platform_peripheral_out );
extern int sflash_platform_deinit    ( void );
extern int sflash_platform_send_recv ( const void* platform_peripheral, /*@in@*/ /*@out@*/ sflash_platform_message_segment_t* segments, unsigned int num_segments  );


#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_SPI_FLASH_PLATFORM_INTERFACE_H */
