/*
 * Copyright 2015, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#ifndef INCLUDED_WWD_BUFFER_H_
#define INCLUDED_WWD_BUFFER_H_


#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************
 *             Constants
 ******************************************************/

/******************************************************
 *             Structures
 ******************************************************/

typedef /*@abstract@*/ /*@owned@*/ char* wiced_buffer_t;

typedef struct
{
    /*@dependent@*/ void*    internal_buffer;
    uint16_t buff_size;
} nons_buffer_init_t;

/******************************************************
 *             Function declarations
 ******************************************************/

/*@external@*/ extern void nons_set_packet_size( uint16_t size );

/******************************************************
 *             Global variables
 ******************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ifndef INCLUDED_WWD_BUFFER_H_ */
