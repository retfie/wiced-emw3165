/*
 * This module does provides various mappings to or from the CLM rate indexes.
 *
 * $Copyright (C) 2011 Broadcom Corporation$
 */
/*FILE-CSTYLED*/

#ifndef _WLU_RATES_MATRIX_H_
#define _WLU_RATES_MATRIX_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <bcmwifi_rates.h>
#include <wlioctl.h>
#include <typedefs.h>
#include <epivers.h>
#include <bcmutils.h>
#include <bcmendian.h>
#include <bcmwifi_channels.h>
#include <wlc_ppr.h>

#ifdef LINUX
#include <inttypes.h>
#endif
#include <miniopt.h>

#define WL_UNSUPPORTED_IDX 0xFFF

typedef enum clm_rate_group_id {
	RATE_GROUP_ID_DSSS = 0,
	RATE_GROUP_ID_OFDM,
	RATE_GROUP_ID_MCS0_7,
	RATE_GROUP_ID_VHT8_9SS1,
	RATE_GROUP_ID_DSSS_MULTI1,
	RATE_GROUP_ID_OFDM_CDD1,
	RATE_GROUP_ID_MCS0_7_CDD1,
	RATE_GROUP_ID_VHT8_9SS1_CDD1,
	RATE_GROUP_ID_MCS0_7_STBC,
	RATE_GROUP_ID_VHT8_9SS1_STBC,
	RATE_GROUP_ID_MCS8_15,
	RATE_GROUP_ID_VHT8_9SS2,
	RATE_GROUP_ID_DSSS_MULTI2,
	RATE_GROUP_ID_OFDM_CDD2,
	RATE_GROUP_ID_MCS0_7_CDD2,
	RATE_GROUP_ID_VHT8_9SS1_CDD2,
	RATE_GROUP_ID_MCS0_7_STBC_SPEXP1,
	RATE_GROUP_ID_VHT8_9SS1_STBC_SPEXP1,
	RATE_GROUP_ID_MCS8_15_SPEXP1,
	RATE_GROUP_ID_VHT8_9SS2_SPEXP1,
	RATE_GROUP_ID_MCS16_23,
	RATE_GROUP_ID_VHT8_9SS3,
	RATE_GROUP_ID_OFDM_TXBF1,
	RATE_GROUP_ID_MCS0_7_TXBF1,
	RATE_GROUP_ID_VHT8_9SS1_TXBF1,
	RATE_GROUP_ID_MCS8_15_TXBF0,
	RATE_GROUP_ID_OFDM_TXBF2,
	RATE_GROUP_ID_MCS0_7_TXBF2,
	RATE_GROUP_ID_VHT8_9SS1_TXBF2,
	RATE_GROUP_ID_MCS8_15_TXBF1,
	RATE_GROUP_ID_VHT8_9SS2_TXBF1,
	RATE_GROUP_ID_MCS16_23_TXBF0,
	RATE_GROUP_ID_COUNT
} clm_rate_group_id_t;


typedef struct {
    char label[23];
    uint8 chains;
    clm_rate_group_id_t id;
    clm_rates_t rate;
    uint bw20ssl;
    uint bw20n;
    uint bw20ht;
    uint bw40ssl;
    uint bw40n;
    uint bw40ht;
    uint bw20in40ssl;
    uint bw20in40n;
    uint bw20in40ht;
    uint bw80ssl;
    uint bw80n;
    uint bw80ht;
    uint bw20in80ssl;
    uint bw20in80n;
    uint bw20in80ht;
    uint bw40in80ssl;
    uint bw40in80n;
    uint bw40in80ht;
} clm_rate_matrix_t;

typedef enum reg_rate_index {
	NO_RATE = -1,
	DSSS1, DSSS2, DSSS5, DSSS11,
	OFDM6, OFDM9, OFDM12, OFDM18,
	OFDM24, OFDM36, OFDM48, OFDM54,
	MCS0, MCS1, MCS2, MCS3,
	MCS4, MCS5, MCS6, MCS7,
	VHT8SS1, VHT9SS1,
	DSSS1_MULTI1, DSSS2_MULTI1, DSSS5_MULTI1, DSSS11_MULTI1,
	OFDM6_CDD1, OFDM9_CDD1, OFDM12_CDD1, OFDM18_CDD1,
	OFDM24_CDD1, OFDM36_CDD1, OFDM48_CDD1, OFDM54_CDD1,
	MCS0_CDD1, MCS1_CDD1, MCS2_CDD1, MCS3_CDD1,
	MCS4_CDD1, MCS5_CDD1, MCS6_CDD1, MCS7_CDD1,
	VHT8SS1_CDD1, VHT9SS1_CDD1,
	MCS0_STBC, MCS1_STBC, MCS2_STBC, MCS3_STBC,
	MCS4_STBC, MCS5_STBC, MCS6_STBC, MCS7_STBC,
	VHT8SS1_STBC, VHT9SS1_STBC,
	MCS8, MCS9, MCS10, MCS11,
	MCS12, MCS13, MCS14, MCS15,
	VHT8SS2, VHT9SS2,
	DSSS1_MULTI2, DSSS2_MULTI2, DSSS5_MULTI2, DSSS11_MULTI2,
	OFDM6_CDD2, OFDM9_CDD2, OFDM12_CDD2, OFDM18_CDD2,
	OFDM24_CDD2, OFDM36_CDD2, OFDM48_CDD2, OFDM54_CDD2,
	MCS0_CDD2, MCS1_CDD2, MCS2_CDD2, MCS3_CDD2,
	MCS4_CDD2, MCS5_CDD2, MCS6_CDD2, MCS7_CDD2,
	VHT8SS1_CDD2, VHT9SS1_CDD2,
	MCS0_STBC_SPEXP1, MCS1_STBC_SPEXP1, MCS2_STBC_SPEXP1, MCS3_STBC_SPEXP1,
	MCS4_STBC_SPEXP1, MCS5_STBC_SPEXP1, MCS6_STBC_SPEXP1, MCS7_STBC_SPEXP1,
	VHT8SS1_STBC_SPEXP1, VHT9SS1_STBC_SPEXP1,
	MCS8_SPEXP1, MCS9_SPEXP1, MCS10_SPEXP1, MCS11_SPEXP1,
	MCS12_SPEXP1, MCS13_SPEXP1, MCS14_SPEXP1, MCS15_SPEXP1,
	VHT8SS2_SPEXP1, VHT9SS2_SPEXP1,
	MCS16, MCS17, MCS18, MCS19,
	MCS20, MCS21, MCS22, MCS23,
	VHT8SS3, VHT9SS3,
	OFDM6_TXBF1, OFDM9_TXBF1, OFDM12_TXBF1, OFDM18_TXBF1,
	OFDM24_TXBF1, OFDM36_TXBF1, OFDM48_TXBF1, OFDM54_TXBF1,
	MCS0_TXBF1, MCS1_TXBF1, MCS2_TXBF1, MCS3_TXBF1,
	MCS4_TXBF1, MCS5_TXBF1, MCS6_TXBF1, MCS7_TXBF1,
	VHT8SS1_TXBF1, VHT9SS1_TXBF1,
	MCS8_TXBF0, MCS9_TXBF0, MCS10_TXBF0, MCS11_TXBF0,
	MCS12_TXBF0, MCS13_TXBF0, MCS14_TXBF0, MCS15_TXBF0,
	OFDM6_TXBF2, OFDM9_TXBF2, OFDM12_TXBF2, OFDM18_TXBF2,
	OFDM24_TXBF2, OFDM36_TXBF2, OFDM48_TXBF2, OFDM54_TXBF2,
	MCS0_TXBF2, MCS1_TXBF2, MCS2_TXBF2, MCS3_TXBF2,
	MCS4_TXBF2, MCS5_TXBF2, MCS6_TXBF2, MCS7_TXBF2,
	VHT8SS1_TXBF2, VHT9SS1_TXBF2,
	MCS8_TXBF1, MCS9_TXBF1, MCS10_TXBF1, MCS11_TXBF1,
	MCS12_TXBF1, MCS13_TXBF1, MCS14_TXBF1, MCS15_TXBF1,
	VHT8SS2_TXBF1, VHT9SS2_TXBF1,
	MCS16_TXBF0, MCS17_TXBF0, MCS18_TXBF0, MCS19_TXBF0,
	MCS20_TXBF0, MCS21_TXBF0, MCS22_TXBF0, MCS23_TXBF0,
} reg_rate_index_t;

typedef enum ppr_rate_type {
	PPR_RATE_DSSS,
	PPR_RATE_OFDM,
	PPR_RATE_HT,
	PPR_RATE_VHT,
} ppr_rate_type_t;

typedef struct ppr_tbl {
	char label[23];
	clm_rate_group_id_t id;
	clm_rates_t         rate;
} ppr_tbl_t;

typedef struct ppr_group {
	clm_rate_group_id_t	id;
	wl_tx_chains_t		chain;
	wl_tx_mode_t		mode;
	wl_tx_nss_t		nss;
	ppr_rate_type_t		rate_type;
	reg_rate_index_t	first_rate;
} ppr_group_t;

static const ppr_group_t ppr_group_table[] = {
	/*group id				chains			mode			nss		rate type		offset-first*/
	{RATE_GROUP_ID_DSSS,			WL_TX_CHAINS_1,		WL_TX_MODE_NONE,	WL_TX_NSS_1,	PPR_RATE_DSSS,		DSSS1},
	{RATE_GROUP_ID_OFDM,			WL_TX_CHAINS_1,		WL_TX_MODE_NONE,	WL_TX_NSS_1,	PPR_RATE_OFDM,		OFDM6},
	{RATE_GROUP_ID_MCS0_7,			WL_TX_CHAINS_1,		WL_TX_MODE_NONE,	WL_TX_NSS_1,	PPR_RATE_VHT,		MCS0},
	{RATE_GROUP_ID_VHT8_9SS1,		WL_TX_CHAINS_1,		WL_TX_MODE_NONE,	WL_TX_NSS_1,	PPR_RATE_VHT,		MCS0},
	{RATE_GROUP_ID_DSSS_MULTI1,		WL_TX_CHAINS_2,		WL_TX_MODE_NONE,	WL_TX_NSS_1,	PPR_RATE_DSSS,		DSSS1_MULTI1},
	{RATE_GROUP_ID_OFDM_CDD1,		WL_TX_CHAINS_2,		WL_TX_MODE_CDD,		WL_TX_NSS_1,	PPR_RATE_OFDM,		OFDM6_CDD1},
	{RATE_GROUP_ID_MCS0_7_CDD1,		WL_TX_CHAINS_2,		WL_TX_MODE_CDD,		WL_TX_NSS_1,	PPR_RATE_VHT,		MCS0_CDD1},
	{RATE_GROUP_ID_VHT8_9SS1_CDD1,		WL_TX_CHAINS_2,		WL_TX_MODE_CDD,		WL_TX_NSS_1,	PPR_RATE_VHT,		MCS0_CDD1},
	{RATE_GROUP_ID_MCS0_7_STBC,		WL_TX_CHAINS_2,		WL_TX_MODE_STBC,	WL_TX_NSS_2,	PPR_RATE_VHT,		MCS0_STBC},
	{RATE_GROUP_ID_VHT8_9SS1_STBC,		WL_TX_CHAINS_2,		WL_TX_MODE_STBC,	WL_TX_NSS_2,	PPR_RATE_VHT,		MCS0_STBC},
	{RATE_GROUP_ID_MCS8_15,			WL_TX_CHAINS_2,		WL_TX_MODE_NONE,	WL_TX_NSS_2,	PPR_RATE_VHT,		MCS8},
	{RATE_GROUP_ID_VHT8_9SS2,		WL_TX_CHAINS_2,		WL_TX_MODE_NONE,	WL_TX_NSS_2,	PPR_RATE_VHT,		MCS8},
	{RATE_GROUP_ID_DSSS_MULTI2,		WL_TX_CHAINS_3,		WL_TX_MODE_NONE,	WL_TX_NSS_1,	PPR_RATE_DSSS,		DSSS1_MULTI2},
	{RATE_GROUP_ID_OFDM_CDD2,		WL_TX_CHAINS_3,		WL_TX_MODE_CDD,		WL_TX_NSS_1,	PPR_RATE_OFDM,		OFDM6_CDD2},
	{RATE_GROUP_ID_MCS0_7_CDD2,		WL_TX_CHAINS_3,		WL_TX_MODE_CDD,		WL_TX_NSS_1,	PPR_RATE_VHT,		MCS0_CDD2},
	{RATE_GROUP_ID_VHT8_9SS1_CDD2,		WL_TX_CHAINS_3,		WL_TX_MODE_CDD,		WL_TX_NSS_1,	PPR_RATE_VHT,		MCS0_CDD2},
	{RATE_GROUP_ID_MCS0_7_STBC_SPEXP1,	WL_TX_CHAINS_3,		WL_TX_MODE_STBC,	WL_TX_NSS_2,	PPR_RATE_VHT,		MCS0_STBC_SPEXP1},
	{RATE_GROUP_ID_VHT8_9SS1_STBC_SPEXP1,	WL_TX_CHAINS_3,		WL_TX_MODE_STBC,	WL_TX_NSS_2,	PPR_RATE_VHT,		MCS0_STBC_SPEXP1},
	{RATE_GROUP_ID_MCS8_15_SPEXP1,		WL_TX_CHAINS_3,		WL_TX_MODE_NONE,	WL_TX_NSS_2,	PPR_RATE_VHT,		MCS8_SPEXP1},
	{RATE_GROUP_ID_VHT8_9SS2_SPEXP1,	WL_TX_CHAINS_3,		WL_TX_MODE_NONE,	WL_TX_NSS_2,	PPR_RATE_VHT,		MCS8_SPEXP1},
	{RATE_GROUP_ID_MCS16_23,		WL_TX_CHAINS_3,		WL_TX_MODE_NONE,	WL_TX_NSS_3,	PPR_RATE_VHT,		MCS16},
	{RATE_GROUP_ID_VHT8_9SS3,		WL_TX_CHAINS_3,		WL_TX_MODE_NONE,	WL_TX_NSS_3,	PPR_RATE_VHT,		MCS16},
	{RATE_GROUP_ID_OFDM_TXBF1,		WL_TX_CHAINS_2,		WL_TX_MODE_TXBF,	WL_TX_NSS_1,	PPR_RATE_OFDM,		OFDM6_TXBF1},
	{RATE_GROUP_ID_MCS0_7_TXBF1,		WL_TX_CHAINS_2,		WL_TX_MODE_TXBF,	WL_TX_NSS_1,	PPR_RATE_VHT,		MCS0_TXBF1},
	{RATE_GROUP_ID_VHT8_9SS1_TXBF1,		WL_TX_CHAINS_2,		WL_TX_MODE_TXBF,	WL_TX_NSS_1,	PPR_RATE_VHT,		MCS0_TXBF1},
	{RATE_GROUP_ID_MCS8_15_TXBF0,		WL_TX_CHAINS_2,		WL_TX_MODE_TXBF,	WL_TX_NSS_2,	PPR_RATE_HT,		MCS8_TXBF0},
	{RATE_GROUP_ID_OFDM_TXBF2,		WL_TX_CHAINS_3,		WL_TX_MODE_TXBF,	WL_TX_NSS_1,	PPR_RATE_OFDM,		OFDM6_TXBF2},
	{RATE_GROUP_ID_MCS0_7_TXBF2,		WL_TX_CHAINS_3,		WL_TX_MODE_TXBF,	WL_TX_NSS_1,	PPR_RATE_VHT,		MCS0_TXBF2},
	{RATE_GROUP_ID_VHT8_9SS1_TXBF2,		WL_TX_CHAINS_3,		WL_TX_MODE_TXBF,	WL_TX_NSS_1,	PPR_RATE_VHT,		MCS0_TXBF2},
	{RATE_GROUP_ID_MCS8_15_TXBF1,		WL_TX_CHAINS_3,		WL_TX_MODE_TXBF,	WL_TX_NSS_2,	PPR_RATE_VHT,		MCS8_TXBF1},
	{RATE_GROUP_ID_VHT8_9SS2_TXBF1,		WL_TX_CHAINS_3,		WL_TX_MODE_TXBF,	WL_TX_NSS_2,	PPR_RATE_VHT,		MCS8_TXBF1},
	{RATE_GROUP_ID_MCS16_23_TXBF0,		WL_TX_CHAINS_3,		WL_TX_MODE_TXBF,	WL_TX_NSS_3,	PPR_RATE_HT,		MCS16_TXBF0},
};

static const ppr_tbl_t ppr_table[] = {
	/* Label			Rate Group ID				CLM index*/
	{"DSSS1",			RATE_GROUP_ID_DSSS,			WL_RATE_1X1_DSSS_1},
	{"DSSS2",			RATE_GROUP_ID_DSSS,			WL_RATE_1X1_DSSS_2},
	{"DSSS5",			RATE_GROUP_ID_DSSS,			WL_RATE_1X1_DSSS_5_5},
	{"DSSS11",			RATE_GROUP_ID_DSSS,			WL_RATE_1X1_DSSS_11},
	{"OFDM6",			RATE_GROUP_ID_OFDM,			WL_RATE_1X1_OFDM_6},
	{"OFDM9",			RATE_GROUP_ID_OFDM,			WL_RATE_1X1_OFDM_9},
	{"OFDM12",			RATE_GROUP_ID_OFDM,			WL_RATE_1X1_OFDM_12},
	{"OFDM18",			RATE_GROUP_ID_OFDM,			WL_RATE_1X1_OFDM_18},
	{"OFDM24",			RATE_GROUP_ID_OFDM,			WL_RATE_1X1_OFDM_24},
	{"OFDM36",			RATE_GROUP_ID_OFDM,			WL_RATE_1X1_OFDM_36},
	{"OFDM48",			RATE_GROUP_ID_OFDM,			WL_RATE_1X1_OFDM_48},
	{"OFDM54",			RATE_GROUP_ID_OFDM,			WL_RATE_1X1_OFDM_54},
	{"MCS0",			RATE_GROUP_ID_MCS0_7,			WL_RATE_1X1_MCS0},
	{"MCS1",			RATE_GROUP_ID_MCS0_7,			WL_RATE_1X1_MCS1},
	{"MCS2",			RATE_GROUP_ID_MCS0_7,			WL_RATE_1X1_MCS2},
	{"MCS3",			RATE_GROUP_ID_MCS0_7,			WL_RATE_1X1_MCS3},
	{"MCS4",			RATE_GROUP_ID_MCS0_7,			WL_RATE_1X1_MCS4},
	{"MCS5",			RATE_GROUP_ID_MCS0_7,			WL_RATE_1X1_MCS5},
	{"MCS6",			RATE_GROUP_ID_MCS0_7,			WL_RATE_1X1_MCS6},
	{"MCS7",			RATE_GROUP_ID_MCS0_7,			WL_RATE_1X1_MCS7},
	{"VHT8SS1",			RATE_GROUP_ID_VHT8_9SS1,		WL_RATE_1X1_VHT8SS1},
	{"VHT9SS1",			RATE_GROUP_ID_VHT8_9SS1,		WL_RATE_1X1_VHT9SS1},
	{"DSSS1_MULTI1",		RATE_GROUP_ID_DSSS_MULTI1,		WL_RATE_1X2_DSSS_1},
	{"DSSS2_MULTI1",		RATE_GROUP_ID_DSSS_MULTI1,		WL_RATE_1X2_DSSS_2},
	{"DSSS5_MULTI1",		RATE_GROUP_ID_DSSS_MULTI1,		WL_RATE_1X2_DSSS_5_5},
	{"DSSS11_MULTI1",		RATE_GROUP_ID_DSSS_MULTI1,		WL_RATE_1X2_DSSS_11},
	{"OFDM6_CDD1",			RATE_GROUP_ID_OFDM_CDD1,	        WL_RATE_1X2_CDD_OFDM_6},
	{"OFDM9_CDD1",			RATE_GROUP_ID_OFDM_CDD1,	        WL_RATE_1X2_CDD_OFDM_9},
	{"OFDM12_CDD1",			RATE_GROUP_ID_OFDM_CDD1,		WL_RATE_1X2_CDD_OFDM_12,},
	{"OFDM18_CDD1",			RATE_GROUP_ID_OFDM_CDD1,		WL_RATE_1X2_CDD_OFDM_18,},
	{"OFDM24_CDD1",			RATE_GROUP_ID_OFDM_CDD1,		WL_RATE_1X2_CDD_OFDM_24,},
	{"OFDM36_CDD1",			RATE_GROUP_ID_OFDM_CDD1,		WL_RATE_1X2_CDD_OFDM_36,},
	{"OFDM48_CDD1",			RATE_GROUP_ID_OFDM_CDD1,		WL_RATE_1X2_CDD_OFDM_48,},
	{"OFDM54_CDD1",			RATE_GROUP_ID_OFDM_CDD1,		WL_RATE_1X2_CDD_OFDM_54,},
	{"MCS0_CDD1",			RATE_GROUP_ID_MCS0_7_CDD1,		WL_RATE_1X2_CDD_MCS0},
	{"MCS1_CDD1",			RATE_GROUP_ID_MCS0_7_CDD1,		WL_RATE_1X2_CDD_MCS1},
	{"MCS2_CDD1",			RATE_GROUP_ID_MCS0_7_CDD1,		WL_RATE_1X2_CDD_MCS2},
	{"MCS3_CDD1",			RATE_GROUP_ID_MCS0_7_CDD1,		WL_RATE_1X2_CDD_MCS3},
	{"MCS4_CDD1",			RATE_GROUP_ID_MCS0_7_CDD1,		WL_RATE_1X2_CDD_MCS4},
	{"MCS5_CDD1",			RATE_GROUP_ID_MCS0_7_CDD1,		WL_RATE_1X2_CDD_MCS5},
	{"MCS6_CDD1",			RATE_GROUP_ID_MCS0_7_CDD1,		WL_RATE_1X2_CDD_MCS6},
	{"MCS7_CDD1",			RATE_GROUP_ID_MCS0_7_CDD1,		WL_RATE_1X2_CDD_MCS7},
	{"VHT8SS1_CDD1",		RATE_GROUP_ID_VHT8_9SS1_CDD1,		WL_RATE_1X2_VHT8SS1},
	{"VHT9SS1_CDD1",		RATE_GROUP_ID_VHT8_9SS1_CDD1,		WL_RATE_1X2_VHT9SS1},
	{"MCS0_STBC",			RATE_GROUP_ID_MCS0_7_STBC,		WL_RATE_2X2_STBC_MCS0},
	{"MCS1_STBC",			RATE_GROUP_ID_MCS0_7_STBC,		WL_RATE_2X2_STBC_MCS1},
	{"MCS2_STBC",			RATE_GROUP_ID_MCS0_7_STBC,		WL_RATE_2X2_STBC_MCS2},
	{"MCS3_STBC",			RATE_GROUP_ID_MCS0_7_STBC,		WL_RATE_2X2_STBC_MCS3},
	{"MCS4_STBC",			RATE_GROUP_ID_MCS0_7_STBC,		WL_RATE_2X2_STBC_MCS4},
	{"MCS5_STBC",			RATE_GROUP_ID_MCS0_7_STBC,		WL_RATE_2X2_STBC_MCS5},
	{"MCS6_STBC",			RATE_GROUP_ID_MCS0_7_STBC,		WL_RATE_2X2_STBC_MCS6},
	{"MCS7_STBC",			RATE_GROUP_ID_MCS0_7_STBC,		WL_RATE_2X2_STBC_MCS7},
	{"VHT8SS1_STBC",		RATE_GROUP_ID_VHT8_9SS1_STBC,		WL_RATE_2X2_STBC_VHT8SS1},
	{"VHT9SS1_STBC",		RATE_GROUP_ID_VHT8_9SS1_STBC,		WL_RATE_2X2_STBC_VHT9SS1},
	{"MCS8",			RATE_GROUP_ID_MCS8_15,			WL_RATE_2X2_SDM_MCS8},
	{"MCS9",			RATE_GROUP_ID_MCS8_15,			WL_RATE_2X2_SDM_MCS9},
	{"MCS10",			RATE_GROUP_ID_MCS8_15,			WL_RATE_2X2_SDM_MCS10},
	{"MCS11",			RATE_GROUP_ID_MCS8_15,			WL_RATE_2X2_SDM_MCS11},
	{"MCS12",			RATE_GROUP_ID_MCS8_15,			WL_RATE_2X2_SDM_MCS12},
	{"MCS13",			RATE_GROUP_ID_MCS8_15,			WL_RATE_2X2_SDM_MCS13},
	{"MCS14",			RATE_GROUP_ID_MCS8_15,			WL_RATE_2X2_SDM_MCS14},
	{"MCS15",			RATE_GROUP_ID_MCS8_15,			WL_RATE_2X2_SDM_MCS15},
	{"VHT8SS2",			RATE_GROUP_ID_VHT8_9SS2,		WL_RATE_2X2_VHT8SS2},
	{"VHT9SS2",			RATE_GROUP_ID_VHT8_9SS2,		WL_RATE_2X2_VHT9SS2},
	{"DSSS1_MULTI2",		RATE_GROUP_ID_DSSS_MULTI2,		WL_RATE_1X3_DSSS_1},
	{"DSSS2_MULTI2",		RATE_GROUP_ID_DSSS_MULTI2,		WL_RATE_1X3_DSSS_2},
	{"DSSS5_MULTI2",		RATE_GROUP_ID_DSSS_MULTI2,		WL_RATE_1X3_DSSS_5_5},
	{"DSSS11_MULTI2",		RATE_GROUP_ID_DSSS_MULTI2,		WL_RATE_1X3_DSSS_11},
	{"OFDM6_CDD2",			RATE_GROUP_ID_OFDM_CDD2,		WL_RATE_1X3_CDD_OFDM_6},
	{"OFDM9_CDD2",			RATE_GROUP_ID_OFDM_CDD2,		WL_RATE_1X3_CDD_OFDM_9},
	{"OFDM12_CDD2",			RATE_GROUP_ID_OFDM_CDD2,		WL_RATE_1X3_CDD_OFDM_12},
	{"OFDM18_CDD2",			RATE_GROUP_ID_OFDM_CDD2,		WL_RATE_1X3_CDD_OFDM_18},
	{"OFDM24_CDD2",			RATE_GROUP_ID_OFDM_CDD2,		WL_RATE_1X3_CDD_OFDM_24},
	{"OFDM36_CDD2",			RATE_GROUP_ID_OFDM_CDD2,		WL_RATE_1X3_CDD_OFDM_36},
	{"OFDM48_CDD2",			RATE_GROUP_ID_OFDM_CDD2,		WL_RATE_1X3_CDD_OFDM_48},
	{"OFDM54_CDD2",			RATE_GROUP_ID_OFDM_CDD2,		WL_RATE_1X3_CDD_OFDM_54},
	{"MCS0_CDD2",			RATE_GROUP_ID_MCS0_7_CDD2,		WL_RATE_1X3_CDD_MCS0},
	{"MCS1_CDD2",			RATE_GROUP_ID_MCS0_7_CDD2,		WL_RATE_1X3_CDD_MCS1},
	{"MCS2_CDD2",			RATE_GROUP_ID_MCS0_7_CDD2,		WL_RATE_1X3_CDD_MCS2},
	{"MCS3_CDD2",			RATE_GROUP_ID_MCS0_7_CDD2,		WL_RATE_1X3_CDD_MCS3},
	{"MCS4_CDD2",			RATE_GROUP_ID_MCS0_7_CDD2,		WL_RATE_1X3_CDD_MCS4},
	{"MCS5_CDD2",			RATE_GROUP_ID_MCS0_7_CDD2,		WL_RATE_1X3_CDD_MCS5},
	{"MCS6_CDD2",			RATE_GROUP_ID_MCS0_7_CDD2,		WL_RATE_1X3_CDD_MCS6},
	{"MCS7_CDD2",			RATE_GROUP_ID_MCS0_7_CDD2,		WL_RATE_1X3_CDD_MCS7},
	{"VHT8SS1_CDD2",		RATE_GROUP_ID_VHT8_9SS1_CDD2,		WL_RATE_1X3_VHT8SS1},
	{"VHT9SS1_CDD2",		RATE_GROUP_ID_VHT8_9SS1_CDD2,		WL_RATE_1X3_VHT9SS1},
	{"MCS0_STBC_SPEXP1",		RATE_GROUP_ID_MCS0_7_STBC_SPEXP1,	WL_RATE_2X3_STBC_MCS0},
	{"MCS1_STBC_SPEXP1",		RATE_GROUP_ID_MCS0_7_STBC_SPEXP1,	WL_RATE_2X3_STBC_MCS1},
	{"MCS2_STBC_SPEXP1",		RATE_GROUP_ID_MCS0_7_STBC_SPEXP1,	WL_RATE_2X3_STBC_MCS2},
	{"MCS3_STBC_SPEXP1",		RATE_GROUP_ID_MCS0_7_STBC_SPEXP1,	WL_RATE_2X3_STBC_MCS3},
	{"MCS4_STBC_SPEXP1",		RATE_GROUP_ID_MCS0_7_STBC_SPEXP1,	WL_RATE_2X3_STBC_MCS4},
	{"MCS5_STBC_SPEXP1",		RATE_GROUP_ID_MCS0_7_STBC_SPEXP1,	WL_RATE_2X3_STBC_MCS5},
	{"MCS6_STBC_SPEXP1",		RATE_GROUP_ID_MCS0_7_STBC_SPEXP1,	WL_RATE_2X3_STBC_MCS6},
	{"MCS7_STBC_SPEXP1",		RATE_GROUP_ID_MCS0_7_STBC_SPEXP1,	WL_RATE_2X3_STBC_MCS7},
	{"VHT8SS1_STBC_SPEXP1",		RATE_GROUP_ID_VHT8_9SS1_STBC_SPEXP1,	WL_RATE_2X3_STBC_VHT8SS1},
	{"VHT9SS1_STBC_SPEXP1",		RATE_GROUP_ID_VHT8_9SS1_STBC_SPEXP1,	WL_RATE_2X3_STBC_VHT9SS1},
	{"MCS8_SPEXP1",			RATE_GROUP_ID_MCS8_15_SPEXP1,		WL_RATE_2X3_SDM_MCS8},
	{"MCS9_SPEXP1",			RATE_GROUP_ID_MCS8_15_SPEXP1,		WL_RATE_2X3_SDM_MCS9},
	{"MCS10_SPEXP1",		RATE_GROUP_ID_MCS8_15_SPEXP1,		WL_RATE_2X3_SDM_MCS10},
	{"MCS11_SPEXP1",		RATE_GROUP_ID_MCS8_15_SPEXP1,		WL_RATE_2X3_SDM_MCS11},
	{"MCS12_SPEXP1",		RATE_GROUP_ID_MCS8_15_SPEXP1,		WL_RATE_2X3_SDM_MCS12},
	{"MCS13_SPEXP1",		RATE_GROUP_ID_MCS8_15_SPEXP1,		WL_RATE_2X3_SDM_MCS13},
	{"MCS14_SPEXP1",		RATE_GROUP_ID_MCS8_15_SPEXP1,		WL_RATE_2X3_SDM_MCS14},
	{"MCS15_SPEXP1",		RATE_GROUP_ID_MCS8_15_SPEXP1,		WL_RATE_2X3_SDM_MCS15},
	{"VHT8SS2_SPEXP1",		RATE_GROUP_ID_VHT8_9SS2_SPEXP1,		WL_RATE_2X3_VHT8SS2},
	{"VHT9SS2_SPEXP1",		RATE_GROUP_ID_VHT8_9SS2_SPEXP1,		WL_RATE_2X3_VHT9SS2},
	{"MCS16",			RATE_GROUP_ID_MCS16_23,			WL_RATE_3X3_SDM_MCS16},
	{"MCS17",			RATE_GROUP_ID_MCS16_23,			WL_RATE_3X3_SDM_MCS17},
	{"MCS18",			RATE_GROUP_ID_MCS16_23,			WL_RATE_3X3_SDM_MCS18},
	{"MCS19",			RATE_GROUP_ID_MCS16_23,			WL_RATE_3X3_SDM_MCS19},
	{"MCS20",			RATE_GROUP_ID_MCS16_23,			WL_RATE_3X3_SDM_MCS20},
	{"MCS21",			RATE_GROUP_ID_MCS16_23,			WL_RATE_3X3_SDM_MCS21},
	{"MCS22",			RATE_GROUP_ID_MCS16_23,			WL_RATE_3X3_SDM_MCS22},
	{"MCS23",			RATE_GROUP_ID_MCS16_23,			WL_RATE_3X3_SDM_MCS23},
	{"VHT8SS3",			RATE_GROUP_ID_VHT8_9SS3,		WL_RATE_3X3_VHT8SS3},
	{"VHT9SS3",			RATE_GROUP_ID_VHT8_9SS3,		WL_RATE_3X3_VHT9SS3},
	{"OFDM6_TXBF1",			RATE_GROUP_ID_OFDM_TXBF1,		WL_RATE_1X2_TXBF_OFDM_6},
	{"OFDM9_TXBF1",			RATE_GROUP_ID_OFDM_TXBF1,		WL_RATE_1X2_TXBF_OFDM_9},
	{"OFDM12_TXBF1",		RATE_GROUP_ID_OFDM_TXBF1,		WL_RATE_1X2_TXBF_OFDM_12},
	{"OFDM18_TXBF1",		RATE_GROUP_ID_OFDM_TXBF1,		WL_RATE_1X2_TXBF_OFDM_18},
	{"OFDM24_TXBF1",		RATE_GROUP_ID_OFDM_TXBF1,		WL_RATE_1X2_TXBF_OFDM_24},
	{"OFDM36_TXBF1",		RATE_GROUP_ID_OFDM_TXBF1,		WL_RATE_1X2_TXBF_OFDM_36},
	{"OFDM48_TXBF1",		RATE_GROUP_ID_OFDM_TXBF1,		WL_RATE_1X2_TXBF_OFDM_48},
	{"OFDM54_TXBF1",		RATE_GROUP_ID_OFDM_TXBF1,		WL_RATE_1X2_TXBF_OFDM_54},
	{"MCS0_TXBF1",			RATE_GROUP_ID_MCS0_7_TXBF1,		WL_RATE_1X2_TXBF_MCS0},
	{"MCS1_TXBF1",			RATE_GROUP_ID_MCS0_7_TXBF1,		WL_RATE_1X2_TXBF_MCS1},
	{"MCS2_TXBF1",			RATE_GROUP_ID_MCS0_7_TXBF1,		WL_RATE_1X2_TXBF_MCS1},
	{"MCS3_TXBF1",			RATE_GROUP_ID_MCS0_7_TXBF1,		WL_RATE_1X2_TXBF_MCS3},
	{"MCS4_TXBF1",			RATE_GROUP_ID_MCS0_7_TXBF1,		WL_RATE_1X2_TXBF_MCS4},
	{"MCS5_TXBF1",			RATE_GROUP_ID_MCS0_7_TXBF1,		WL_RATE_1X2_TXBF_MCS5},
	{"MCS6_TXBF1",			RATE_GROUP_ID_MCS0_7_TXBF1,		WL_RATE_1X2_TXBF_MCS6},
	{"MCS7_TXBF1",			RATE_GROUP_ID_MCS0_7_TXBF1,		WL_RATE_1X2_TXBF_MCS7},
	{"VHT8SS1_TXBF1",		RATE_GROUP_ID_VHT8_9SS1_TXBF1,		WL_RATE_1X2_TXBF_VHT8SS1},
	{"VHT9SS1_TXBF1",		RATE_GROUP_ID_VHT8_9SS1_TXBF1,		WL_RATE_1X2_TXBF_VHT9SS1},
	{"MCS8_TXBF0",			RATE_GROUP_ID_MCS8_15_TXBF0,		WL_RATE_2X2_TXBF_SDM_MCS8},
	{"MCS9_TXBF0",			RATE_GROUP_ID_MCS8_15_TXBF0,		WL_RATE_2X2_TXBF_SDM_MCS9},
	{"MCS10_TXBF0",			RATE_GROUP_ID_MCS8_15_TXBF0,		WL_RATE_2X2_TXBF_SDM_MCS10},
	{"MCS11_TXBF0",			RATE_GROUP_ID_MCS8_15_TXBF0,		WL_RATE_2X2_TXBF_SDM_MCS11},
	{"MCS12_TXBF0",			RATE_GROUP_ID_MCS8_15_TXBF0,		WL_RATE_2X2_TXBF_SDM_MCS12},
	{"MCS13_TXBF0",			RATE_GROUP_ID_MCS8_15_TXBF0,		WL_RATE_2X2_TXBF_SDM_MCS13},
	{"MCS14_TXBF0",			RATE_GROUP_ID_MCS8_15_TXBF0,		WL_RATE_2X2_TXBF_SDM_MCS14},
	{"MCS15_TXBF0",			RATE_GROUP_ID_MCS8_15_TXBF0,		WL_RATE_2X2_TXBF_SDM_MCS15},
	{"OFDM6_TXBF2",			RATE_GROUP_ID_OFDM_TXBF2,		WL_RATE_1X3_TXBF_OFDM_6},
	{"OFDM9_TXBF2",			RATE_GROUP_ID_OFDM_TXBF2,		WL_RATE_1X3_TXBF_OFDM_9},
	{"OFDM12_TXBF2",		RATE_GROUP_ID_OFDM_TXBF2,		WL_RATE_1X3_TXBF_OFDM_12},
	{"OFDM18_TXBF2",		RATE_GROUP_ID_OFDM_TXBF2,		WL_RATE_1X3_TXBF_OFDM_18},
	{"OFDM24_TXBF2",		RATE_GROUP_ID_OFDM_TXBF2,		WL_RATE_1X3_TXBF_OFDM_24},
	{"OFDM36_TXBF2",		RATE_GROUP_ID_OFDM_TXBF2,		WL_RATE_1X3_TXBF_OFDM_36},
	{"OFDM48_TXBF2",		RATE_GROUP_ID_OFDM_TXBF2,		WL_RATE_1X3_TXBF_OFDM_48},
	{"OFDM54_TXBF2",		RATE_GROUP_ID_OFDM_TXBF2,		WL_RATE_1X3_TXBF_OFDM_54},
	{"MCS0_TXBF2",			RATE_GROUP_ID_MCS0_7_TXBF2,		WL_RATE_1X3_TXBF_MCS0},
	{"MCS1_TXBF2",			RATE_GROUP_ID_MCS0_7_TXBF2,		WL_RATE_1X3_TXBF_MCS1},
	{"MCS2_TXBF2",			RATE_GROUP_ID_MCS0_7_TXBF2,		WL_RATE_1X3_TXBF_MCS2},
	{"MCS3_TXBF2",			RATE_GROUP_ID_MCS0_7_TXBF2,		WL_RATE_1X3_TXBF_MCS3},
	{"MCS4_TXBF2",			RATE_GROUP_ID_MCS0_7_TXBF2,		WL_RATE_1X3_TXBF_MCS4},
	{"MCS5_TXBF2",			RATE_GROUP_ID_MCS0_7_TXBF2,		WL_RATE_1X3_TXBF_MCS5},
	{"MCS6_TXBF2",			RATE_GROUP_ID_MCS0_7_TXBF2,		WL_RATE_1X3_TXBF_MCS6},
	{"MCS7_TXBF2",			RATE_GROUP_ID_MCS0_7_TXBF2,		WL_RATE_1X3_TXBF_MCS7},
	{"VHT8SS1_TXBF2",		RATE_GROUP_ID_VHT8_9SS1_TXBF2,		WL_RATE_1X3_TXBF_VHT8SS1},
	{"VHT9SS1_TXBF2",		RATE_GROUP_ID_VHT8_9SS1_TXBF2,		WL_RATE_1X3_TXBF_VHT9SS1},
	{"MCS8_TXBF1",			RATE_GROUP_ID_MCS8_15_TXBF1,		WL_RATE_2X3_TXBF_SDM_MCS8},
	{"MCS9_TXBF1",			RATE_GROUP_ID_MCS8_15_TXBF1,		WL_RATE_2X3_TXBF_SDM_MCS9},
	{"MCS10_TXBF1",			RATE_GROUP_ID_MCS8_15_TXBF1,		WL_RATE_2X3_TXBF_SDM_MCS10},
	{"MCS11_TXBF1",			RATE_GROUP_ID_MCS8_15_TXBF1,		WL_RATE_2X3_TXBF_SDM_MCS11},
	{"MCS12_TXBF1",			RATE_GROUP_ID_MCS8_15_TXBF1,		WL_RATE_2X3_TXBF_SDM_MCS12},
	{"MCS13_TXBF1",			RATE_GROUP_ID_MCS8_15_TXBF1,		WL_RATE_2X3_TXBF_SDM_MCS13},
	{"MCS14_TXBF1",			RATE_GROUP_ID_MCS8_15_TXBF1,		WL_RATE_2X3_TXBF_SDM_MCS14},
	{"MCS15_TXBF1",			RATE_GROUP_ID_MCS8_15_TXBF1,		WL_RATE_2X3_TXBF_SDM_MCS15},
	{"VHT8SS2_TXBF1",		RATE_GROUP_ID_VHT8_9SS2_TXBF1,		WL_RATE_2X3_TXBF_VHT8SS2},
	{"VHT9SS2_TXBF1",		RATE_GROUP_ID_VHT8_9SS2_TXBF1,		WL_RATE_2X3_TXBF_VHT9SS2},
	{"MCS16_TXBF0",			RATE_GROUP_ID_MCS16_23_TXBF0,		WL_RATE_3X3_TXBF_SDM_MCS16},
	{"MCS17_TXBF0",			RATE_GROUP_ID_MCS16_23_TXBF0,		WL_RATE_3X3_TXBF_SDM_MCS17},
	{"MCS18_TXBF0",			RATE_GROUP_ID_MCS16_23_TXBF0,		WL_RATE_3X3_TXBF_SDM_MCS18},
	{"MCS19_TXBF0",			RATE_GROUP_ID_MCS16_23_TXBF0,		WL_RATE_3X3_TXBF_SDM_MCS19},
	{"MCS20_TXBF0",			RATE_GROUP_ID_MCS16_23_TXBF0,		WL_RATE_3X3_TXBF_SDM_MCS20},
	{"MCS21_TXBF0",			RATE_GROUP_ID_MCS16_23_TXBF0,		WL_RATE_3X3_TXBF_SDM_MCS21},
	{"MCS22_TXBF0",			RATE_GROUP_ID_MCS16_23_TXBF0,		WL_RATE_3X3_TXBF_SDM_MCS22},
	{"MCS23_TXBF0",			RATE_GROUP_ID_MCS16_23_TXBF0,		WL_RATE_3X3_TXBF_SDM_MCS23},
};

#define MHZ_TO_HALF_MHZ 2

const char *get_clm_rate_group_label(int rategroup);
const char *get_reg_rate_string_from_ratespec(int ratespec);
reg_rate_index_t get_reg_rate_index_from_ratespec(int ratespec);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WLU_RATES_MATRIX_H_ */
