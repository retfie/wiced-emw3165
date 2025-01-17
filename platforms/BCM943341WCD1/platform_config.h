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
 * Defines internal configuration of the BCM943341WCD1 board
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *  MCU Constants and Options
 *
 *  NOTE: The clock configuration utility from ST is used to calculate these values
 *        http://www.st.com/st-web-ui/static/active/en/st_prod_software_internet/resource/technical/software/utility/stsw-stm32090.zip
 ******************************************************/

/* CPU clock : 120 MHz */
#define CPU_CLOCK_HZ         ( 120000000 )

/* Use external crystal */
#define HSE_SOURCE           ( RCC_HSE_ON )

/* AHB clock  : System clock */
#define AHB_CLOCK_DIVIDER    ( RCC_SYSCLK_Div1 )

/* APB1 clock : AHB clock / 4 */
#define APB1_CLOCK_DIVIDER   ( RCC_HCLK_Div4 )

/* APB2 clock : AHB clock / 2 */
#define APB2_CLOCK_DIVIDER   ( RCC_HCLK_Div2 )

/* PLL source : external crystal */
#define PLL_SOURCE           ( RCC_PLLSource_HSE )

/* PLLM : 26 */
#define PLL_M_CONSTANT       ( 26 )

/* PLLN : 240 */
#define PLL_N_CONSTANT       ( 240 )

/* PLLP : 2 */
#define PLL_P_CONSTANT       ( 2 )

/* PLLQ : 5 */
#define PPL_Q_CONSTANT       ( 5 )

/* System clock source  : PLL clock */
#define SYSTEM_CLOCK_SOURCE  ( RCC_SYSCLKSource_PLLCLK )

/* SysTick clock source : AHB clock  */
#define SYSTICK_CLOCK_SOURCE ( SysTick_CLKSource_HCLK )

/* Internal flash wait state : 3 cycles */
#define INT_FLASH_WAIT_STATE ( FLASH_Latency_3 )

/* Internal flash voltage range : 2.7 to 3.6V */
#define PLATFORM_STM32_VOLTAGE_2V7_TO_3V6


/******************************************************
 *  Wi-Fi Options
 ******************************************************/

/*  GPIO pins are used to bootstrap Wi-Fi to SDIO or gSPI mode */
#define WICED_WIFI_USE_GPIO_FOR_BOOTSTRAP_0
#define WICED_WIFI_USE_GPIO_FOR_BOOTSTRAP_1

/*  Wi-Fi GPIO0 pin is used for out-of-band interrupt */
#define WICED_WIFI_OOB_IRQ_GPIO_PIN  ( 0 )

/* Wi-Fi power pin is present */
#define WICED_USE_WIFI_POWER_PIN

/* Wi-Fi power pin is active high */
#define WICED_USE_WIFI_POWER_PIN_ACTIVE_HIGH

/* Wi-Fi 32K clock is driven by MCO */
#define WICED_USE_WIFI_32K_CLOCK_MCO


/******************************************************
 *  Bluetooth Options
 ******************************************************/

/* Bluetooth device wake pin is present */
#define WICED_USE_BT_DEVICE_WAKE_PIN

/* Bluetooth host wake pin is present */
#define WICED_USE_BT_HOST_WAKE_PIN


#ifdef __cplusplus
} /* extern "C" */
#endif
