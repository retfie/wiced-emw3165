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
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

/* This is the soft AP used for device configuration */
#define CONFIG_AP_SSID       "WICED Config"
#define CONFIG_AP_CHANNEL    1
#define CONFIG_AP_SECURITY   WICED_SECURITY_WPA2_AES_PSK
#define CONFIG_AP_PASSPHRASE "12345678"

/* This is the soft AP available for normal operation (if used)*/
#define SOFT_AP_SSID         "WICED Device"
#define SOFT_AP_CHANNEL      1
#define SOFT_AP_SECURITY     WICED_SECURITY_WPA2_AES_PSK
#define SOFT_AP_PASSPHRASE   "WICED_PASSPHRASE"

/* This is the default AP the device will connect to (as a client)*/
#define CLIENT_AP_SSID       "dlink-test"
#define CLIENT_AP_PASSPHRASE "1234512345"
#define CLIENT_AP_BSS_TYPE   WICED_BSS_TYPE_INFRASTRUCTURE
#define CLIENT_AP_SECURITY   WICED_SECURITY_WPA2_MIXED_PSK
#define CLIENT_AP_CHANNEL    1
#define CLIENT_AP_BAND       WICED_802_11_BAND_2_4GHZ

/* This is the network interface the device will work with */
#define WICED_NETWORK_INTERFACE   WICED_STA_INTERFACE

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
