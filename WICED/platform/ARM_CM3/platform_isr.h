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
 * Defines macros for defining and mapping interrupt handlers to the vector table of ARM-Cortex-M3 CPU
 */
#pragma once
#include "platform_constants.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *                      Macros
 ******************************************************/

/* Section where IRQ handlers are placed */
#define IRQ_SECTION ".text.irq"

/* Macro for defining an interrupt handler (non-RTOS-aware)
 *
 * @warning:
 * Do NOT call any RTOS primitive functions from here. If you need to call them,
 * define your interrupt handler using WWD_RTOS_DEFINE_ISR()
 *
 * @usage:
 * PLATFORM_DEFINE_ISR( my_irq )
 * {
 *     // Do something here
 * }
 *
 */
#if defined ( __GNUC__ )
/* GCC */
#define PLATFORM_DEFINE_NAKED_ISR( function ) \
        void function( void ); \
        __attribute__(( naked, interrupt, used, section( IRQ_SECTION ) )) void function( void )

#define PLATFORM_DEFINE_ISR( function ) \
        void function( void ); \
        __attribute__(( interrupt, used, section( IRQ_SECTION ) )) void function( void )

#elif defined ( __IAR_SYSTEMS_ICC__ )
/* IAR Systems */
#define PLATFORM_DEFINE_ISR( function ) \
        void function( void ); \
        __irq __root void function( void )

#else

#define PLATFORM_DEFINE_ISR( name )

#endif


/* Macro for mapping a defined function to an interrupt handler declared in
 * <Wiced-SDK>/WICED/platform/<Arch>/<Family>/platform_isr_interface.h
 *
 * @usage:
 * PLATFORM_MAP_ISR( my_irq, USART1_irq )
 */
#if defined( __GNUC__ )

#define PLATFORM_MAP_ISR( function, isr ) \
        extern void isr( void ); \
        __attribute__(( alias( #function ))) void isr ( void );

#elif defined ( __IAR_SYSTEMS_ICC__ )

#define PLATFORM_MAP_ISR( function, isr ) \
        extern void isr( void ); \
        _Pragma( TO_STRING( weak isr=function ) )

#else

#define PLATFORM_MAP_ISR( function, isr )

#endif


/* Macro for declaring a default handler for an unhandled interrupt
 *
 * @usage:
 * PLATFORM_SET_DEFAULT_ISR( USART1_irq, default_handler )
 */
#if defined( __GNUC__ )

#define PLATFORM_SET_DEFAULT_ISR( irq_handler, default_handler ) \
        __attribute__(( weak, alias( #default_handler ))) void irq_handler ( void );

#elif defined ( __IAR_SYSTEMS_ICC__ )

#define PLATFORM_SET_DEFAULT_ISR( irq_handler, default_handler ) \
        _Pragma( TO_STRING( weak irq_handler=default_handler ) )

#else

#define PLATFORM_SET_DEFAULT_ISR( irq_handler, default_handler )

#endif

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

#ifdef __cplusplus
} /*extern "C" */
#endif
