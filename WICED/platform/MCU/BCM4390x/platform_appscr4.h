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
 * Defines BCM43909 APPS CPU core
 */
#pragma once

#include <stddef.h>
#include "platform_map.h"
#include "platform_isr_interface.h"
#include "platform_isr.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *                      Macros
 ******************************************************/

#define PLATFORM_APPSCR4_CLEAR_ATOMIC(ptr, mask) \
    do \
    {  \
        uint32_t flags; \
        WICED_SAVE_INTERRUPTS(flags);    \
        *(ptr) &= ~(mask);               \
        WICED_RESTORE_INTERRUPTS(flags); \
    } \
    while(0)

#define PLATFORM_APPSCR4_SET_ATOMIC(ptr, mask) \
    do \
    {  \
        uint32_t flags; \
        WICED_SAVE_INTERRUPTS(flags);    \
        *(ptr) |= (mask);                \
        WICED_RESTORE_INTERRUPTS(flags); \
    } \
    while(0)

/******************************************************
 *                    Constants
 ******************************************************/

#define PLATFORM_APPSCR4    ( (volatile appscr4_regs_t*    ) PLATFORM_APPSCR4_REGBASE(    0x0 ) )
#define PLATFORM_CHIPCOMMON ( (volatile chipcommon_regs_t* ) PLATFORM_CHIPCOMMON_REGBASE( 0x0 ) )
#define PLATFORM_PMU        ( (volatile pmu_regs_t*        ) PLATFORM_PMU_REGBASE(        0x0 ) )

#define STRUCTURE_CHECK( unique_number, structure, member, offset ) \
    /* Make sure the expression is constant. */ \
    typedef enum { _STATIC_ASSERT_NOT_CONSTANT ## unique_number = (offsetof(structure,member) == (offset)) } _static_assert_e ## unique_number ; \
    /* Make sure the expression is true. */ \
    typedef char STATIC_ASSERT_FAIL ## unique_number [(offsetof(structure,member) == (offset)) ? 1 : -1]


/******************************************************
 *                   Enumerations
 ******************************************************/

typedef enum ExtIRQn
{
/******  External Interrupt Numbers ****/
/* Defined in oob_43909_rXX.xls */
  ChipCommon_ExtIRQn             = 0,
  Timer_ExtIRQn                  = 1,
  Core2_ExtIRQn                  = 2,
  Core3_ExtIRQn                  = 3,
  M2M_ExtIRQn                    = 4,
  GMAC_ExtIRQn                   = 5,
  I2S0_ExtIRQn                   = 6,
  I2S1_ExtIRQn                   = 7,
  Core8_ExtIRQn                  = 8,
  Core9_ExtIRQn                  = 9,
  Core10_ExtIRQn                 = 10,
  Core11_ExtIRQn                 = 11,
  Core12_ExtIRQn                 = 12,
  Core13_ExtIRQn                 = 13,
  Core14_ExtIRQn                 = 14,
  Core15_ExtIRQn                 = 15,
  SW0_ExtIRQn                    = 16,
  SW1_ExtIRQn                    = 17,
  Reserved18_ExtIRQn             = 18,
  Reserved19_ExtIRQn             = 19,
  Reserved20_ExtIRQn             = 20,
  Reserved21_ExtIRQn             = 21,
  Reserved22_ExtIRQn             = 22,
  Reserved23_ExtIRQn             = 23,
  Reserved24_ExtIRQn             = 24,
  Reserved25_ExtIRQn             = 25,
  Reserved26_ExtIRQn             = 26,
  Reserved27_ExtIRQn             = 27,
  Reserved28_ExtIRQn             = 28,
  ClockStable_ExtIRQn            = 29,
  Perf_ExtIRQn                   = 30,
  Serror_ExtIRQn                 = 31,

} ExtIRQn_Type;

typedef enum IRQn
{
/******  Interrupt Numbers ************/
  Timer_IRQn                     = 0,

} IRQn_Type;


/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned force_proc_reset       : 1;
        unsigned s_error_int_en         : 1;
        unsigned wfi_clk_stop           : 1;
        unsigned not_sleeping_clk_req_0 : 1;
        unsigned sleeping_clk_req       : 2;
        unsigned pclk_dbg_stop          : 1;
        unsigned force_clock_source     : 1;
        unsigned clock_source           : 4;
        unsigned trace_clk_divider      : 4;
        unsigned trace_clk_pclk         : 1;
        unsigned atb_clk_en             : 1;
        unsigned not_sleeping_clk_req_1 : 1;
        unsigned not_used               : 13;
    } bits;
} appscr4_core_ctrl_reg_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned force_proc_reset_log   : 1;
        unsigned s_error_log            : 1;
        unsigned s_bp_reset_log         : 1;
        unsigned standby_wfi            : 1;
        unsigned validate_firmware      : 1;
        unsigned not_used               : 27;
    } bits;
} appscr4_core_status_reg_t;

typedef struct
{
    appscr4_core_ctrl_reg_t   core_ctrl;     /* 0x00 */
    uint32_t                  core_cap;      /* 0x04 */
    appscr4_core_status_reg_t core_status;   /* 0x08 */
    uint32_t                  _PAD;          /* 0x0C */
    uint32_t                  fiqirq_status; /* 0x10 */
    uint32_t                  fiq_mask;      /* 0x14 */
    uint32_t                  irq_mask;      /* 0x18 */
    uint32_t                  sw_int;        /* 0x1C */
    uint32_t                  int_status;    /* 0x20 */
    uint32_t                  int_mask;      /* 0x24 */
    uint32_t                  cycle_cnt;     /* 0x28 */
    uint32_t                  int_timer;     /* 0x2C */
} appscr4_regs_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned force_alp_request      : 1;
        unsigned force_ht_request       : 1;
        unsigned force_ilp_request      : 1;
        unsigned alp_avail_request      : 1;
        unsigned ht_avail_request       : 1;
        unsigned force_hw_clock_req_off : 1;
        unsigned hq_clock_required      : 1;
        unsigned __reserved1            : 1;
        unsigned ext_src_req            : 1;
        unsigned __reserved2            : 7;
        unsigned alp_clock_available    : 1;
        unsigned ht_clock_available     : 1;
        unsigned bp_on_alp              : 1;
        unsigned bp_on_ht               : 1;
        unsigned __reserved3            : 4;
        unsigned ext_src_status         : 1;
        unsigned __reserved4            : 7;
    } bits;
} clock_control_status_t;

#define PLATFORM_CLOCKSTATUS_REG(core_base) ((volatile clock_control_status_t*)((core_base) + 0x1E0))

#ifndef SI_SFLASH
#define SI_SFLASH       (0x14000000)
#endif

/*
    Sflash Action Codes
    0000: Issue opcode only.
    0001: Issue opcode, shift in or out 1 byte of data.
    0010: Issue opcode, shift out 3 bytes of address.
    0011: Issue opcode, shift out 3 bytes of address, shift in or out 1 byte of data.
    0100: Issue opcode, shift out 3 bytes of address, shift in or out 4 bytes of data.
    0101: Issue opcode, shift out 3 bytes of address, shift out 4 bytes of X, shift in or out 4 bytes of data.
    0110: Issue opcode, shift out 1 byte of X and shift in or out 1 byte of data.
    0111: Issue opcode, shift out 3 bytes of address, shift out 1 byte of X, shift in or out 4 bytes of data for ST SFlash, or 3 bytes of X and 1 byte of data (Atmel mode).
    1000: No Opcode issued, shift in or out 4 bytes of data
    1001: Issue Opcode, shift in or out 2 bytes of data
    1010: issue Opcode, shift in or out 4 bytes of data
    1011: Issue opcode, shift out 3 or 4 bytes of address, shift in or out 4 bytes of data (Write data byte swapped version of "0100").
    1100: Issue opcode, shift out 3 or bytes of address, shift out 4 bytes of X, shift in or out 4 bytes of data (Write data byte swapped version of "0101").
*/

typedef enum
{
    SFLASH_ACTIONCODE_ONLY = 0x00,
    SFLASH_ACTIONCODE_1DATA = 0x01,
    SFLASH_ACTIONCODE_3ADDRESS = 0x02,
    SFLASH_ACTIONCODE_3ADDRESS_1DATA = 0x03,
    SFLASH_ACTIONCODE_3ADDRESS_4DATA = 0x04,
    SFLASH_ACTIONCODE_4DATA_ONLY = 0x08,
    SFLASH_ACTIONCODE_MAX_ENUM
} bcm43909_sflash_actioncode_t;

typedef struct
{
        unsigned int opcode                     : 8; /*   7:0 */
        unsigned int action_code                : 4; /*  11:8 */
        unsigned int cs_active                  : 1; /*    12 */
        unsigned int use_four_byte_address_mode : 1; /*    13 */
        unsigned int use_opcode_reg             : 1; /*    14 */
        unsigned int mode_bit_enable            : 1; /*    15 */
        unsigned int num_dummy_cycles           : 4; /* 19:16 */
        unsigned int backplane_write_dma_busy   : 1; /*    20 */
        unsigned int num_burst                  : 2; /* 22:21 */
        unsigned int high_speed_mode            : 1; /*    23 */
        unsigned int use_quad_address_mode      : 1; /*    24 */
        unsigned int reserved2                  : 6; /* 30:25 */
        unsigned int start_busy                 : 1; /*    31 */
} bcm43909_sflash_ctrl_bits_t;

typedef union
{
    uint32_t                    raw;
    bcm43909_sflash_ctrl_bits_t bits;
} bcm43909_sflash_ctrl_reg_t;

typedef enum
{
    SPROM_DIVIDE_BY_32 = 0,
    SPROM_DIVIDE_BY_64 = 1,
    SPROM_DIVIDE_BY_96 = 2,
    SPROM_DIVIDE_BY_128 = 3,
    SPROM_DIVIDE_BY_192 = 4,
    SPROM_DIVIDE_BY_256 = 5,
    SPROM_DIVIDE_BY_384 = 6,
    SPROM_DIVIDE_BY_512 = 7,
} sprom_divider_t;

typedef enum
{
    UART_CLOCK_SOURCE_EXTERNAL_INPUT = 0,
    UART_CLOCK_SOURCE_INTERNAL = 1,
} uart_clock_source_t;

typedef enum
{
    EXTERNAL_BUS_TYPE_NONE = 0,
    EXTERNAL_BUS_TYPE_ASYNCHRONOUS_PCMCIA_AND_IDE = 1,
    EXTERNAL_BUS_TYPE_ASYNCHRONOUS = 2,
    EXTERNAL_BUS_TYPE_ASYNCHRONOUS_AND_SYNCHRONOUS = 3,
} external_bus_type_t;

typedef enum
{
    FLASH_TYPE_NONE = 0,
    FLASH_TYPE_ST_MICRO_COMPATIBLE_SERIAL_FLASH = 1,
    FLASH_TYPE_ATMEL_COMPATIBLE_SERIAL_FLASH = 2,
    FLASH_TYPE_PARALLEL_FLASH = 7,
} flash_type_t;



typedef enum
{
    PLL_CONTROL_TYPE_NONE                  = 0x00,  /* Always zero if PMU is present */
    PLL_CONTROL_TYPE_4710_STYLE            = 0x08,  /* PLLCtlN, M0, M1, M2, and M3 registers present. */
    PLL_CONTROL_TYPE_4704_STYLE            = 0x10,  /* PLLCtlN, M0, M1, M2, and M3 registers present. */
    PLL_CONTROL_TYPE_4710_STYLE_25MHZ_FREF = 0x18,  /* with 25 MHz fref and no control of backplane frequency. */
    PLL_CONTROL_TYPE_4712_STYLE            = 0x04,  /* PLLCtlN, M0, M1, M2, and M3 registers present. */
    PLL_CONTROL_TYPE_5365_STYLE            = 0x0c,
    PLL_CONTROL_TYPE_4720_STYLE            = 0x04,  /* PLLCtlN and M3 registers present. */
    PLL_CONTROL_TYPE_4712_STYLE_25MHZ_FREF = 0x04,  /* with 25 MHz fref. PLLCtlN, M0, M1, M2, and M3 registers present. */
} pll_control_type_t;


typedef union
{
        uint32_t raw;
        struct
        {
              unsigned int opcode:8;                                 /*  7:0  */
              unsigned int gsio_code:3;                              /* 10:8  */
              unsigned int reserved1:1;                              /* 11    */
              unsigned int number_of_address_bytes_minus_1:2;        /* 13:12 */
              unsigned int number_of_wait_cycles:2;                  /* 15:14 */
              unsigned int number_of_data_bytes:2;                   /* 17:16 */
              unsigned int reserved:3;                               /* 20:18 */
              unsigned int chip_select_asserted_between_transfers:1; /* 21    */
              unsigned int big_endian:1;                             /* 22    */
              unsigned int command_error:1;                          /* 23    */
              unsigned int reserved2:6;                              /* 29:24 */
              unsigned int i2c_mode:1;                               /* 30    */
              unsigned int start_busy:1;                             /* 31    */

        } spi_bits;
        struct
        {
              unsigned int next_data_byte:8;                       /*  7:0  */
              unsigned int i2c_data_source:3;                      /* 10:8  */
              unsigned int reserved1:1;                            /* 11    */
              unsigned int start_condition_and_address_size:2;     /* 13:12 */
              unsigned int reserved2:2;                            /* 15:14 */
              unsigned int number_of_data_bytes:2;                 /* 17:16 */
              unsigned int read:1;                                 /* 18 - write=0 */
              unsigned int no_send_or_check_ack:1;                 /* 19    */
              unsigned int ack_received:1;                         /* 20    */
              unsigned int generate_stop_condition:1;              /* 21    */
              unsigned int big_endian:1;                           /* 22    */
              unsigned int command_error:1;                        /* 23    */
              unsigned int reserved3:6;                            /* 29:24 */
              unsigned int i2c_mode:1;                             /* 30    */
              unsigned int start_busy:1;                           /* 31    */
        } i2c_bits;

} gsio_control_register_t;

typedef enum
{
    pwm_channel_ctrl_alignment_left   = 0x0,
    pwm_channel_ctrl_alignment_right  = 0x1,
    pwm_channel_ctrl_alignment_center = 0x2,
} pwm_channel_ctrl_alignment_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int enable:1;                    /* 0     */
        unsigned int update:1;                    /* 1     */
        unsigned int update_all:1;                /* 2     */
        unsigned int is_single_shot:1;            /* 3     */
        unsigned int invert:1;                    /* 4     */
        pwm_channel_ctrl_alignment_t alignment:2; /* 6:5   */
        unsigned int reserved:25;                 /* 31:7  */
     } bits;
} pwm_channel_ctrl_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int low_cycle_time:16;  /* 0:15  */
        unsigned int high_cycle_time:16; /* 16:31 */
    } bits;
} pwm_channel_cycle_cnt_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int cycle_dead_low:16;  /* 0:15  */
        unsigned int cycle_dead_high:16; /* 16:31 */
    } bits;
} pwm_channel_dead_time_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int total_period:32; /* 31:0  */
    } bits;
} pwm_channel_total_period_t;

typedef struct
{
    pwm_channel_ctrl_t         ctrl;
    pwm_channel_cycle_cnt_t    cycle_cnt;
    pwm_channel_dead_time_t    dead_time;
    pwm_channel_total_period_t total_period;
} pwm_channel_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int time:1;      /* 0 */
        unsigned int calendar:1;  /* 1 */
        unsigned int reserved:30; /* 31:2 */
    } bits;
} rtc_control_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int hour_mode:1; /* 0 */
        unsigned int reserved:31; /* 31:1 */
    } bits;
} rtc_hour_mode_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int hundredths_seconds_units:4; /* 3:0 */
        unsigned int hundredths_seconds_tens:4;  /* 7:4 */
        unsigned int seconds_units:4;            /* 11:8 */
        unsigned int seconds_tens:3;             /* 14:12 */
        unsigned int reserved1:1;                /* 15 */
        unsigned int minutes_units:4;            /* 19:16 */
        unsigned int minutes_tens:3;             /* 22:20 */
        unsigned int reserved2:1;                /* 23 */
        unsigned int hours_units:4;              /* 27:24 */
        unsigned int hours_tens:2;               /* 29:28 */
        unsigned int am_pm_select:1;             /* 30 */
        unsigned int time_changed:1;             /* 31*/
    } bits;
} rtc_time_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int day_of_week:3;      /* 2:0 */
        unsigned int month_units:4;      /* 6:3 */
        unsigned int month_tens:1;       /* 7 */
        unsigned int date_units:4;       /* 11:8 */
        unsigned int date_tens:2;        /* 13:12 */
        unsigned int reserved1:2;        /* 15:14 */
        unsigned int year_units:4;       /* 19:16 */
        unsigned int year_tens:4;        /* 23:20 */
        unsigned int century_units:4;    /* 27:24 */
        unsigned int century_tens:2;     /* 29:28 */
        unsigned int reserved2:1;        /* 30 */
        unsigned int calendar_changed:1; /* 31*/
    } bits;
} rtc_calendar_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int hundredths_seconds_units:4; /* 3:0 */
        unsigned int hundredths_seconds_tens:4;  /* 7:4 */
        unsigned int seconds_units:4;            /* 11:8 */
        unsigned int seconds_tens:3;             /* 14:12 */
        unsigned int reserved1:1;                /* 15 */
        unsigned int minutes_units:4;            /* 19:16 */
        unsigned int minutes_tens:3;             /* 22:20 */
        unsigned int reserved2:1;                /* 23 */
        unsigned int hours_units:4;              /* 27:24 */
        unsigned int hours_tens:2;               /* 29:28 */
        unsigned int am_pm_select:1;             /* 30 */
        unsigned int reserved3:1;                /* 31*/
    } bits;
} rtc_time_alarm_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int reserved1:3;   /* 2:0 */
        unsigned int month_units:4; /* 6:3 */
        unsigned int month_tens:1;  /* 7 */
        unsigned int date_units:4;  /* 11:8 */
        unsigned int date_tens:2;   /* 13:12 */
        unsigned int reserved2:18;  /* 31:14 */
    } bits;
} rtc_calendar_alarm_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int hundredths_second:1; /* 0 */
        unsigned int second:1;            /* 1 */
        unsigned int minute:1;            /* 2 */
        unsigned int hour:1;              /* 3 */
        unsigned int date:1;              /* 4 */
        unsigned int month:1;             /* 5 */
        unsigned int reserved:26;         /* 31:6 */
    } bits;
} rtc_alarm_enable_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int hundredths_second:1; /* 0 */
        unsigned int second:1;            /* 1 */
        unsigned int minute:1;            /* 2 */
        unsigned int hour:1;              /* 3 */
        unsigned int date:1;              /* 4 */
        unsigned int month:1;             /* 5 */
        unsigned int alarm:1;             /* 6 */
        unsigned int reserved:25;         /* 31:7 */
    } bits;
} rtc_event_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int time_valid:1;           /* 0 */
        unsigned int calendar_valid:1;       /* 1 */
        unsigned int time_alarm_valid:1;     /* 2 */
        unsigned int calendar_alarm_valid:1; /* 3 */
        unsigned int reserved:28;            /* 31:4 */
    } bits;
} rtc_status_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int keep_rtc:1;  /* 0 */
        unsigned int reserved:31; /* 31:1 */
    } bits;
} rtc_keep_rtc_t;

typedef struct
{
    rtc_control_t        control;           /* Offset 0x00 */
    rtc_hour_mode_t      hour_mode;         /* Offset 0x04 */
    rtc_time_t           time;              /* Offset 0x08 */
    rtc_calendar_t       calendar;          /* Offset 0x0C */
    rtc_time_alarm_t     time_alarm;        /* Offset 0x10 */
    rtc_calendar_alarm_t calendar_alarm;    /* Offset 0x14 */
    rtc_alarm_enable_t   alarm_enable;      /* Offset 0x18 */
    rtc_event_t          event_flags;       /* Offset 0x1C */
    rtc_event_t          interrupt_enable;  /* Offset 0x20 */
    rtc_event_t          interrupt_disable; /* Offset 0x24 */
    rtc_event_t          interrupt_mask;    /* Offset 0x28 */
    rtc_status_t         status;            /* Offset 0x2C */
    rtc_keep_rtc_t       keep_rtc;          /* Offset 0x30 */
} rtc_regs_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int time:24;             /* 23:0 */
        unsigned int int_enable:1;        /* 24 */
        unsigned int req_active:1;        /* 25 */
        unsigned int force_alp_request:1; /* 26 */
        unsigned int force_ht_request:1;  /* 27 */
        unsigned int force_hq_required:1; /* 28 */
        unsigned int clkreq_group_sel:3;  /* 31:29 */
    } bits;
} pmu_res_req_timer_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int rsrc_req_timer_int0:1;    /* 0 */
        unsigned int rsrc_req_timer_int1:1;    /* 1 */
        unsigned int reserved3:6;
        unsigned int rsrc_event_int0:1;        /* 8 */
        unsigned int rsrc_event_int1:1;        /* 9 */
        unsigned int reserved2:6;
        unsigned int stats_timer_int:1;        /* 16 */
        unsigned int rtc_int:1;                /* 17 */
        unsigned int reserved1:14;
    } bits;
} pmu_intstatus_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int force_alp_request:1; /* 0 */
        unsigned int force_ht_request:1;  /* 1 */
        unsigned int force_hq_required:1; /* 2 */
        unsigned int clkreq_group_sel:3;  /* 5:3 */
        unsigned int reserved1:26;
    } bits;
} pmu_intctrl_t;

typedef union
{
    uint32_t raw;
    struct
    {
        unsigned int alp_period:14;       /* 13:0  */
        unsigned int reserved1:2;         /* 15:14 */
        unsigned int one_mhz_toggle_en:1; /* 16    */
        unsigned int reserved2:15;        /* 31:17 */
    } bits;
} pmu_slowclkperiod_t;

typedef struct
{
    rtc_regs_t          real_time_clock;    /* 0x000 */
    uint32_t            reserved1[371];     /* 0x034 */
    uint32_t            pmucontrol;         /* 0x600 */
    uint32_t            pmucapabilities;
    uint32_t            pmustatus;
    uint32_t            res_state;
    uint32_t            res_pending;
    uint32_t            pmutimer;
    uint32_t            min_res_mask;
    uint32_t            max_res_mask;
    uint32_t            res_table_sel;
    uint32_t            res_dep_mask;
    uint32_t            res_updn_timer;
    uint32_t            res_timer;
    uint32_t            clkstretch;
    uint32_t            pmuwatchdog;
    uint32_t            gpiosel;            /* 0x638, rev >= 1 */
    uint32_t            gpioenable;         /* 0x63c, rev >= 1 */
    uint32_t            res_req_timer_sel;
    pmu_res_req_timer_t res_req_timer0;
    uint32_t            res_req_mask0;
    uint32_t            pmucapabilities_ext;
    uint32_t            chipcontrol_addr;   /* 0x650 */
    uint32_t            chipcontrol_data;   /* 0x654 */
    uint32_t            regcontrol_addr;
    uint32_t            regcontrol_data;
    uint32_t            pllcontrol_addr;
    uint32_t            pllcontrol_data;
    uint32_t            pmustrapopt;        /* 0x668, corerev >= 28 */
    uint32_t            pmu_xtalfreq;       /* 0x66C, pmurev >= 10 */
    uint32_t            retention_ctl;      /* 0x670 */
    uint32_t            reserved3[3];
    uint32_t            retention_grpidx;   /* 0x680 */
    uint32_t            retention_grpctl;   /* 0x684 */
    uint32_t            reserved4[13];
    pmu_res_req_timer_t res_req_timer1;     /* 0x6BC */
    uint32_t            reserved5[6];
    uint32_t            pmucontrol_ext;     /* 0x6d8 */
    pmu_slowclkperiod_t slowclkperiod;      /* 0x6dc */
    uint32_t            reserved6[3];
    uint32_t            res_req_mask1;      /* 0x6EC */
    uint32_t            reserved7[4];
    pmu_intstatus_t     pmuintmask0;        /* 0x700 */
    pmu_intstatus_t     pmuintmask1;        /* 0x704 */
    uint32_t            reserved8[6];
    uint32_t            res_event0;         /* 0x720 */
    uint32_t            res_event1;         /* 0x724 */
    uint32_t            reserved9[6];
    pmu_intstatus_t     pmuintstatus;       /* 0x740 */
    uint32_t            reserved10[15];
    pmu_intctrl_t       pmuintctrl0;        /* 0x780 */
    pmu_intctrl_t       pmuintctrl1;        /* 0x784 */
} pmu_regs_t;

typedef union
{

    struct
    {
        union
        {
                uint32_t raw;
                struct
                {
                        unsigned int chip_id:16;       /* 15:0 */
                        unsigned int revision_id:4;    /* 19:16 */
                        unsigned int package_option:4; /* 23:20 */
                        unsigned int core_count:4;     /* 27:24 */
                        unsigned int chip_type:4;      /* 31:28 */
                } bits;
        } chip_id;                   /* 0x00 - READ ONLY */

        union
        {
                uint32_t raw;
                struct
                {
                        unsigned int uart_count:2;                                 /*  1:0  */
                        unsigned int big_endian_mode:1;                            /*  2    */
                        unsigned int uart_clock_selected:2;                        /*  4:3 - see uart_clock_source_t */
                        unsigned int uart_using_gpio_8_to_11:1;                    /*  5    */
                        unsigned int external_bus_type:2;                          /*  7:6 - see external_bus_type_t */
                        unsigned int flash_type:3;                                 /* 10:8 - see flash_type_t */
                        unsigned int reserved1:2;                                  /* 12:11 */
                        unsigned int pll_control_type:5;                           /* 17:13 - see pll_control_type_t */
                        unsigned int dynamic_clock_control_supported:1;            /* 18 - zero if PMU is present */
                        unsigned int reserved2:3;                                  /* 21:19 */
                        unsigned int jtag_master_present:1;                        /* 22    */
                        unsigned int reserved3:4;                                  /* 26:23 */
                        unsigned int backplane_supports_64_bit_addresses:1;        /* 27    */
                        unsigned int pmu_present:1;                                /* 28    */
                        unsigned int enhanced_coexistence_interface_implemented:1; /* 29    */
                        unsigned int serial_prom_interface_implemented:1;          /* 30    */
                        unsigned int nand_flash_interface_implemented:1;           /* 31    */
                } bits;
        } core_capabilities;  /* 0x04 - READ ONLY */


        union
        {
                uint32_t raw;
                struct
                {
                        unsigned int uart_clock_override:1;                    /* 0 */
                        unsigned int extif_sync_clock_pin_is_a_output:1;       /* 1 */
                        unsigned int gpio_interrupt_without_backplane_clock:1; /* 2 */
                        unsigned int uart_clock_enable:1;                      /* 3 */
                        unsigned int otp_clock_enable:1;                       /* 4 */
                        unsigned int serial_prom_clock_enable:1;               /* 5 */
                        unsigned int reserved:26;                              /* 31:6 */
                } bits;
        } core_control;       /* 0x08 */

        uint32_t bist_status;        /* 0x0C */
    } core_ctrl_status;
    struct
    {
        uint8_t  reserved1[0x10];
        uint32_t otp_status;            /* 0x10 */
        uint32_t otp_ctrl;              /* 0x14 */
        uint32_t otp_prog;              /* 0x18 */
        uint32_t otp_layout;            /* 0x1C */
        uint8_t  reserved2[0x2C];
        uint32_t otp_layout_extensions; /* 0x4C */
        uint8_t  reserved3[0xA4];
        uint32_t otp_ctrl_1;            /* 0xF4 */
    } otp;

    struct
    {
        uint8_t  reserved[0x20];
        union
        {
            uint32_t raw;
            struct
            {
                  unsigned int gpio_interrupt_present:1;                           /*  0    */
                  unsigned int external_interrupt_present:1;                       /*  1    */
                  unsigned int reserved1:2;                                        /*  3:2  */
                  unsigned int enhanced_coexistence_interface_interrupt_present:1; /*  4    */
                  unsigned int power_management_unit_interrupt_present:1;          /*  5    */
                  unsigned int uart_interrupt_present:1;                           /*  6    */
                  unsigned int coexistence_wakeup_interrupt_present:1;             /*  7    */
                  unsigned int silicon_process_monitor_interrupt_present:1;        /*  8    */
                  unsigned int ascu_receive_interrupt_present:1;                   /*  9    */
                  unsigned int ascu_transmit_interrupt_present:1;                  /* 10    */
                  unsigned int ascu_astp_present:1;                                /* 11    */
                  unsigned int reserved2:19;                                       /* 30:12 */
                  unsigned int watchdog_reset_occurred:1;                          /* 31    */
            } read_bits;
            struct
            {
                  unsigned int reserved:31;            /* 30:0 */
                  unsigned int watchdog_reset_clear:1; /* 31   */
            } write_bits;
        } status;  /* 0x20 */

        union
        {
            uint32_t raw;
            struct
            {
                  unsigned int gpio_interrupt_enable:1;                           /*  0    */
                  unsigned int external_interrupt_enable:1;                       /*  1    */
                  unsigned int reserved1:2;                                       /*  3:2  */
                  unsigned int enhanced_coexistence_interface_interrupt_enable:1; /*  4    */
                  unsigned int power_management_unit_interrupt_enable:1;          /*  5    */
                  unsigned int uart_interrupt_enable:1;                           /*  6    */
                  unsigned int coexistence_wakeup_interrupts_enable:1;            /*  7    */
                  unsigned int silicon_process_monitor_interrupt_enable:1;        /*  8    */
                  unsigned int ascu_receive_interrupt_enable:1;                   /*  9    */
                  unsigned int ascu_transmit_interrupt_enable:1;                  /* 10    */
                  unsigned int ascu_astp_interrupt_enable:1;                      /* 11    */
                  unsigned int reserved2:20;                                      /* 31:12 */
            } bits;
        } mask;  /* 0x24 */
        uint32_t chip_ctrl;   /* 0x28 - Deprecated - use PMU chip control registers */
        uint32_t chip_status; /* 0x2C - READ ONLY */
    } interrupt;

    struct
    {
        uint8_t  reserved[0x30];
        uint32_t cmd;   /* 0x30 */
        uint32_t instr; /* 0x34 */
        uint32_t data;  /* 0x38 */
        uint32_t ctrl;  /* 0x3C */
    } jtag_master;

    struct
    {
        uint8_t  reserved[0x40];
        bcm43909_sflash_ctrl_reg_t control;    /* 0x40 */
        uint32_t address;                      /* 0x44 */
        uint32_t data;                         /* 0x48 */
    } sflash;


    struct
    {
        uint8_t  reserved[0x50];
        uint32_t address;   /* 0x50 */
        uint32_t data;      /* 0x54 */
    } broadcast;

    struct
    {
        uint8_t  reserved1[0x58];
        uint32_t pull_up;            /* 0x58 */
        uint32_t pull_down;          /* 0x5C */
        uint32_t input;              /* 0x60 */
        uint32_t output;             /* 0x64 */
        uint32_t output_enable;      /* 0x68 */
        uint32_t control;            /* 0x6C */
        uint32_t int_polarity;       /* 0x70 */
        uint32_t int_mask;           /* 0x74 */
        uint32_t event;              /* 0x78 */
        uint32_t event_int_mask;     /* 0x7C */
        uint8_t  reserved2[0x04];                      /* watchdog_counter */
        uint32_t event_int_polarity; /* 0x84 */
        uint32_t timer_val;          /* 0x88 */
        uint32_t timer_out_mask;     /* 0x8C */
        uint8_t  reserved3[0x18];
        uint32_t debug_sel;          /* 0xA8 */
    } gpio;


    struct
    {
            uint8_t  reserved1[0x80];
            uint32_t watchdog_counter;       /* 0x80 */
            uint8_t  reserved2[0x20];
            union
            {
                    uint32_t raw;
                    struct
                    {
                            unsigned int uart_divider:8;         /*  7:0  */
                            unsigned int jtag_master_divider:6;  /* 13:8  */
                            unsigned int reserved1:10;           /* 23:14 */
                            unsigned int serial_flash_divider:5; /* 28:24 */
                            unsigned int reserved2:3;            /* 31:29 */
                    } bits;
            } divider;                /* 0xA4 */
            uint8_t  reserved3[0x04];
            union
            {
                    uint32_t raw;
                    struct
                    {
                          unsigned int serial_extended_coexistence_interface_present:1;            /*  0    */
                          unsigned int general_serial_io_present:1;                                /*  1    */
                          unsigned int global_coexistence_interface_present:1;                     /*  2    */
                          unsigned int serial_extended_coexistence_interface_plain_uart_present:1; /*  3    */
                          unsigned int save_restore_engine_present:1;                              /*  4    */
                          unsigned int ascu_present:1;                                             /*  5    */
                          unsigned int always_on_backplane_present:1;                              /*  6    */
                          unsigned int pulse_width_modulation_present:1;                           /*  7    */
                          unsigned int general_serial_io_count:2;                                  /*  9:8  */
                          unsigned int reserved:22;                                                /* 31:10 */
                    } bits;
            } capabilities_extension; /* 0xAC - READ ONLY */
            uint8_t  reserved4[0x40];
            union
            {
                    uint32_t raw;
                    struct
                    {
                          unsigned int serial_prom_divider:3;            /*  2:0  */
                          unsigned int reserved1:1;                      /*  3    */
                          unsigned int general_serial_io_divider:17;     /* 20:4  */
                          unsigned int reserved2:11;                     /* 21:31 */

                    } bits;
            } clock_divider_2;        /* 0xF0 */
    } clock_control;


    struct
    {
        uint8_t  reserved1[0xD0];
        uint32_t backplane_addr_low;        /* 0xD0 */
        uint32_t backplane_addr_high;       /* 0xD4 */
        uint32_t backplane_data;            /* 0xD8 */
        uint8_t  reserved2[0x04];
        uint32_t backplane_indirect_access; /* 0xE0 */
        uint8_t  reserved3[0x14];
        uint32_t fab_id;                    /* 0xF8 */
        uint32_t erom_ptr_offset;           /* 0xFC */
        uint8_t  reserved4[0xEE8];
        uint32_t flag_status;               /* 0xFE8 */
    } interconnect;

    struct
    {
        uint8_t  reserved1[0xE4];
        struct
        {
            gsio_control_register_t control; /* 0xE4 */
            uint32_t address;                /* 0xE8 */
            uint32_t data;                   /* 0xEC */
            /* clock divider is in clock_divider_2 register */
        } interface_0;
        uint8_t  reserved2[0x390];
        struct
        {
            gsio_control_register_t control; /* 0x480 */
            uint32_t address;                /* 0x484 */
            uint32_t data;                   /* 0x488 */
            uint32_t clock_divider;          /* 0x48C */
        } interface_1;
        struct
        {
            gsio_control_register_t control; /* 0x490 */
            uint32_t address;                /* 0x494 */
            uint32_t data;                   /* 0x498 */
            uint32_t clock_divider;          /* 0x49C */
        } interface_2;
        struct
        {
            gsio_control_register_t control; /* 0x4A0 */
            uint32_t address;                /* 0x4A4 */
            uint32_t data;                   /* 0x4A8 */
            uint32_t clock_divider;          /* 0x4AC */
        } interface_3;
    } general_serial_io_controllers;

    struct
    {
        uint8_t  reserved1[0x100];
        struct
        {
            uint32_t config;               /* 0x100 */
            uint32_t memory_wait_count;    /* 0x104 */
            uint32_t attribute_wait_count; /* 0x108 */
            uint32_t io_wait_count;        /* 0x10C */
        } cs01;

        struct
        {
            uint32_t config;               /* 0x110 */
            uint32_t memory_wait_count;    /* 0x114 */
            uint32_t attribute_wait_count; /* 0x118 */
            uint32_t io_wait_count;        /* 0x11C */
        } cs23;

        struct
        {
            uint32_t config;               /* 0x120 */
            uint32_t memory_wait_count;    /* 0x124 */
        } cs4;

        struct
        {
            uint32_t config;               /* 0x128 */
            uint32_t memory_wait_count;    /* 0x12C */
        } parallel_flash;
    } external_bus_control;


    union
    {
        struct
        {
            uint8_t  reserved1[0x140];
            uint32_t output[2];                   /* 0x140 & 0x144 */
            uint32_t control[2];                  /* 0x148 & 0x14C */
            uint32_t input[2];                    /* 0x150 & 0x154 */
            uint32_t input_interrupt_polarity[2]; /* 0x158 & 0x15C */
            uint32_t interrupt_mask[2];           /* 0x160 & 0x164 */
            uint32_t event[2];                    /* 0x168 & 0x16C */
            uint32_t event_interrupt_mask[2];     /* 0x170 & 0x174 */
            uint32_t auxilliary_tx;               /* 0x178 */
            uint32_t auxilliary_rx;               /* 0x17C */
            uint32_t data_tag;                    /* 0x180 */

        } parallel;

        struct
        {
            uint8_t  reserved1[0x130];
            uint32_t config;                 /* 0x130 */
            uint32_t status;                 /* 0x134 */
            uint32_t status_mask;            /* 0x138 */
            uint32_t rx_nibble_changed;      /* 0x13C */
            uint8_t  reserved2[0x44];

            struct
            {
                uint32_t escape_value;                   /* 0x184 */
                uint32_t autobaud_counter;               /* 0x188 */
                uint32_t fifo_level;                     /* 0x18C */
                uint8_t  reserved2[0x30];
                uint32_t data;                           /* 0x1C0 */
                uint32_t baudrate_divisor;               /* 0x1C4 */
                uint32_t fifo_control;                   /* 0x1C8 */
                uint32_t line_control;                   /* 0x1CC */
                uint32_t modem_control;                  /* 0x1D0 */
                uint32_t line_status;                    /* 0x1D4 */
                uint32_t modem_status;                   /* 0x1D8 */
                uint32_t baudrate_adjustment;            /* 0x1DC */
                uint8_t  reserved3[0x10];
                uint32_t timestamp;                      /* 0x1F0 */
                uint32_t timestamp_slow;                 /* 0x1F4 */
                uint32_t timestamp_fractional_increment; /* 0x1F8 */
            } uart;
        } serial;
    } enhanced_coexistence_interface;

    struct
    {
        uint8_t  reserved[0x190];
        uint32_t control;   /* 0x190 */
        uint32_t address; /* 0x194 */
        uint32_t data;  /* 0x198 */
    } serial_prom;


    struct
    {
        uint8_t  reserved[0x1A0];
        uint32_t control;         /* 0x1A0 */
        uint32_t config;          /* 0x1A4 */
        uint32_t column_address;  /* 0x1A8 */
        uint32_t row_address;     /* 0x1AC */
        uint32_t data;            /* 0x1B0 */
        uint32_t wait_count;      /* 0x1B4 */
        uint32_t id_status[2];    /* 0x1B8 & 0x1BC */
    } nand_flash;

    struct
    {
        uint8_t  reserved[0x1E0];
        uint32_t status;          /* 0x1E0 */
    } pmu_clock_control;

    struct
    {
        uint8_t  reserved[0x200];
        uint32_t ascu_control;                  /* 0x200 */
        uint32_t ascu_gpio_control;             /* 0x204 */
        uint32_t ascu_bitsel_control;           /* 0x208 */
        uint32_t master_clk_offset_lo;          /* 0x20C */
        uint32_t master_clk_offset_hi;          /* 0x210 */
        uint32_t network_clk_offset;            /* 0x214 */
        uint32_t start_i2s0_ts;                 /* 0x218 */
        uint32_t start_i2s1_ts;                 /* 0x21C */
        uint32_t interrupt_status;              /* 0x220 */
        uint32_t interrupt_mask;                /* 0x224 */
        uint32_t audio_timer_tx_lo;             /* 0x228 */
        uint32_t audio_timer_tx_hi;             /* 0x22C */
        uint32_t audio_timer_rx_lo;             /* 0x230 */
        uint32_t audio_timer_rx_hi;             /* 0x234 */
        uint32_t audio_timer_frame_sync_lo;     /* 0x238 */
        uint32_t audio_timer_frame_sync_hi;     /* 0x23C */
        uint32_t audio_timer_fw_lo;             /* 0x240 */
        uint32_t audio_timer_fw_hi;             /* 0x244 */
        uint32_t audio_talker_timer_fw_lo;      /* 0x248 */
        uint32_t audio_talker_timer_fw_hi;      /* 0x24C */
        uint32_t network_timer_tx_lo;           /* 0x250 */
        uint32_t network_timer_tx_hi;           /* 0x254 */
        uint32_t network_timer_rx_lo;           /* 0x258 */
        uint32_t network_timer_rx_hi;           /* 0x25C */
        uint32_t network_timer_frame_sync_lo;   /* 0x260 */
        uint32_t network_timer_frame_sync_hi;   /* 0x264 */
        uint32_t network_timer_fw_lo;           /* 0x268 */
        uint32_t network_timer_fw_hi;           /* 0x26C */
        uint32_t sample_cnt0;                   /* 0x270 */
        uint32_t sample_cnt1;                   /* 0x274 */
    } audio_sync_control_unit;


    struct
    {
        uint8_t  reserved[0x300];
        struct
        {
                union   /* Offset 0x00 */
                {
                        volatile uint8_t receive_buffer;       /* Read Only  -  Accessible only when the Divisor Latch Access Bit (DLAB), Bit 7 of Line Control Register (LCR) is set to Zero */
                        volatile uint8_t transmit_holding;     /* Write Only -  Accessible only when the Divisor Latch Access Bit (DLAB), Bit 7 of Line Control Register (LCR) is set to Zero */
                        volatile uint8_t divisor_latch_low;    /* Read Write -  Accessible only when the Divisor Latch Access Bit (DLAB), Bit 7 of Line Control Register (LCR) is set to One */
                } tx_rx_dll;

                union   /* Offset 0x01 */
                {
                        volatile uint8_t interrupt_enable;     /* Read Write -  Accessible only when the Divisor Latch Access Bit (DLAB), Bit 7 of Line Control Register (LCR) is set to Zero */
                        volatile uint8_t divisor_latch_high;   /* Read Write -  Accessible only when the Divisor Latch Access Bit (DLAB), Bit 7 of Line Control Register (LCR) is set to One */
                } ie_dlh;

                union   /* Offset 0x02 */
                {
                        volatile uint8_t interrupt_identification;  /* Read  Only */
                        volatile uint8_t fifo_control;              /* Write Only */
                } iir_fcr;


                volatile uint8_t line_control;   /* Read Write */  /* Offset 0x03 */
                volatile uint8_t modem_control;  /* Read Write */  /* Offset 0x04 */
                volatile uint8_t line_status;    /* Read Only  */  /* Offset 0x05 */
                volatile uint8_t modem_status;   /* Read Only  */  /* Offset 0x06 */
                volatile uint8_t scratchpad;     /* Read Write */  /* Offset 0x07 */

                uint8_t  reserved[8];
        } uart[3];
    } uarts;

    struct
    {
        uint8_t reserved[0x400];

        union
        {
            uint32_t raw;
            struct
            {
                unsigned int update_time:32;         /* 31:0  */
            } bits;
        } globalctrl;

        pwm_channel_t pwm_channels[6];

    } pwm; /* 0x400 to 0x47C */

} chipcommon_regs_t;

typedef union
{
    uint8_t raw;
    struct
    {
        unsigned int pmu_ext_lpo_avail:1;   /* 0 */
        unsigned int clk_sel_out_int_lpo:1; /* 1 */
        unsigned int clk_sel_out_ext_lpo:1; /* 2 */
        unsigned int boot_from_wake:1;      /* 3 */
    } bits;
} hib_status_t;

#define GCI_CHIPCONTROL_GMAC_INTERFACE_REG           6
#define GCI_CHIPCONTROL_GMAC_INTERFACE_SHIFT         23
#define GCI_CHIPCONTROL_GMAC_INTERFACE_MASK          (0x3 << GCI_CHIPCONTROL_GMAC_INTERFACE_SHIFT)
#define GCI_CHIPCONTROL_GMAC_INTERFACE_RMII          (0x3 << GCI_CHIPCONTROL_GMAC_INTERFACE_SHIFT)
#define GCI_CHIPCONTROL_GMAC_INTERFACE_MII           (0x1 << GCI_CHIPCONTROL_GMAC_INTERFACE_SHIFT)

#define GCI_CHIPCONTROL_APPS_CPU_FREQ_REG            7
#define GCI_CHIPCONTROL_APPS_CPU_FREQ_SHIFT          16
#define GCI_CHIPCONTROL_APPS_CPU_FREQ_MASK           (0x7 << GCI_CHIPCONTROL_APPS_CPU_FREQ_SHIFT)
#define GCI_CHIPCONTROL_APPS_CPU_FREQ_320            (0x0 << GCI_CHIPCONTROL_APPS_CPU_FREQ_SHIFT)
#define GCI_CHIPCONTROL_APPS_CPU_FREQ_160            (0x1 << GCI_CHIPCONTROL_APPS_CPU_FREQ_SHIFT)

#define GCI_CHIPCONTROL_HIB_WAKE_COUNT_REG           10
#define GCI_CHIPCONTROL_HIB_WAKE_COUNT_SHIFT         0
#define GCI_CHIPCONTROL_HIB_WAKE_COUNT_MASK          (0xFFFFFFFF << GCI_CHIPCONTROL_HIB_WAKE_COUNT_SHIFT)
#define GCI_CHIPCONTROL_HIB_WAKE_COUNT_VAL(v)        (((v) << GCI_CHIPCONTROL_HIB_WAKE_COUNT_SHIFT) & GCI_CHIPCONTROL_HIB_WAKE_COUNT_MASK)

#define GCI_CHIPCONTROL_HIB_WAKE_CTL_REG             11
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_SHIFT           0
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_MASK            (0x7FF << GCI_CHIPCONTROL_HIB_WAKE_CTL_SHIFT)
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_RC_SHIFT    0
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_RC_MASK     (0x1F << GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_RC_SHIFT)
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_RC_VAL(v)   (((v) << GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_RC_SHIFT) & GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_RC_MASK)
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_FREQ_SHIFT  5
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_FREQ_MASK   (0x7 << GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_FREQ_SHIFT)
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_FREQ_128KHZ (0x0 << GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_FREQ_SHIFT)
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_FREQ_32KHZ  (0x2 << GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_FREQ_SHIFT)
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_FREQ_16KHZ  (0x3 << GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_FREQ_SHIFT)
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_DOWN_SHIFT  8
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_DOWN_MASK   (0x1 << GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_DOWN_SHIFT)
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_DOWN_EXEC   (0x1 << GCI_CHIPCONTROL_HIB_WAKE_CTL_LPO_DOWN_SHIFT)
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_XTAL_DOWN_SHIFT 9
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_XTAL_DOWN_MASK  (0x1 << GCI_CHIPCONTROL_HIB_WAKE_CTL_XTAL_DOWN_SHIFT)
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_XTAL_DOWN_EXEC  (0x1 << GCI_CHIPCONTROL_HIB_WAKE_CTL_XTAL_DOWN_SHIFT)
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_XTAL_PIN_SHIFT  10
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_XTAL_PIN_MASK   (0x1 << GCI_CHIPCONTROL_HIB_WAKE_CTL_XTAL_PIN_SHIFT)
#define GCI_CHIPCONTROL_HIB_WAKE_CTL_XTAL_PIN_SET    (0x1 << GCI_CHIPCONTROL_HIB_WAKE_CTL_XTAL_PIN_SHIFT)

#define GCI_CHIPCONTROL_HIB_READ_SEL_REG             11
#define GCI_CHIPCONTROL_HIB_READ_SEL_SHIFT           11
#define GCI_CHIPCONTROL_HIB_READ_SEL_MASK            (0x7 << GCI_CHIPCONTROL_HIB_READ_SEL_SHIFT)
#define GCI_CHIPCONTROL_HIB_READ_SEL_COUNT_0_7       (0x0 << GCI_CHIPCONTROL_HIB_READ_SEL_SHIFT)
#define GCI_CHIPCONTROL_HIB_READ_SEL_COUNT_15_8      (0x1 << GCI_CHIPCONTROL_HIB_READ_SEL_SHIFT)
#define GCI_CHIPCONTROL_HIB_READ_SEL_COUNT_23_16     (0x2 << GCI_CHIPCONTROL_HIB_READ_SEL_SHIFT)
#define GCI_CHIPCONTROL_HIB_READ_SEL_COUNT_31_24     (0x3 << GCI_CHIPCONTROL_HIB_READ_SEL_SHIFT)
#define GCI_CHIPCONTROL_HIB_READ_SEL_STATUS          (0x4 << GCI_CHIPCONTROL_HIB_READ_SEL_SHIFT)
#define GCI_CHIPCONTROL_HIB_READ_SEL_REVID           (0x5 << GCI_CHIPCONTROL_HIB_READ_SEL_SHIFT)

#define GCI_CHIPCONTROL_HIB_START_REG                11
#define GCI_CHIPCONTROL_HIB_START_SHIFT              14
#define GCI_CHIPCONTROL_HIB_START_MASK               (0x1 << GCI_CHIPCONTROL_HIB_START_SHIFT)
#define GCI_CHIPCONTROL_HIB_START_EXEC               (0x1 << GCI_CHIPCONTROL_HIB_START_SHIFT)

#define GCI_CHIPCONTROL_HIB_FORCE_EXT_LPO_REG        11
#define GCI_CHIPCONTROL_HIB_FORCE_EXT_LPO_SHIFT      15
#define GCI_CHIPCONTROL_HIB_FORCE_EXT_LPO_MASK       (0x1 << GCI_CHIPCONTROL_HIB_FORCE_EXT_LPO_SHIFT)
#define GCI_CHIPCONTROL_HIB_FORCE_EXT_LPO_EXEC       (0x1 << GCI_CHIPCONTROL_HIB_FORCE_EXT_LPO_SHIFT)

#define GCI_CHIPCONTROL_HIB_FORCE_INT_LPO_REG        11
#define GCI_CHIPCONTROL_HIB_FORCE_INT_LPO_SHIFT      16
#define GCI_CHIPCONTROL_HIB_FORCE_INT_LPO_MASK       (0x1 << GCI_CHIPCONTROL_HIB_FORCE_INT_LPO_SHIFT)
#define GCI_CHIPCONTROL_HIB_FORCE_INT_LPO_EXEC       (0x1 << GCI_CHIPCONTROL_HIB_FORCE_INT_LPO_SHIFT)

#define GCI_CHIPCONTROL_BP_CLK_FROM_ARMCR4_CLK_REG   11
#define GCI_CHIPCONTROL_BP_CLK_FROM_ARMCR4_CLK_SHIFT 17
#define GCI_CHIPCONTROL_BP_CLK_FROM_ARMCR4_CLK_MASK  (1 << GCI_CHIPCONTROL_BP_CLK_FROM_ARMCR4_CLK_SHIFT)

#define GCI_CHIPCONTROL_SW_DEEP_SLEEP_FLAG_REG       11
#define GCI_CHIPCONTROL_SW_DEEP_SLEEP_FLAG_SHIFT     26
#define GCI_CHIPCONTROL_SW_DEEP_SLEEP_FLAG_MASK      (1 << GCI_CHIPCONTROL_SW_DEEP_SLEEP_FLAG_SHIFT)
#define GCI_CHIPCONTROL_SW_DEEP_SLEEP_FLAG_SET       (1 << GCI_CHIPCONTROL_SW_DEEP_SLEEP_FLAG_SHIFT)

#define GCI_CHIPSTATUS_BOOT_MODE_REG                 4
#define GCI_CHIPSTATUS_BOOT_MODE_ACPU_SHIFT          21
#define GCI_CHIPSTATUS_BOOT_MODE_ACPU_MASK           (1 << GCI_CHIPSTATUS_BOOT_MODE_ACPU_SHIFT)
#define GCI_CHIPSTATUS_BOOT_MODE_WCPU_SHIFT          23
#define GCI_CHIPSTATUS_BOOT_MODE_WCPU_MASK           (1 << GCI_CHIPSTATUS_BOOT_MODE_WCPU_SHIFT)

#define GCI_CHIPSTATUS_HIB_READ_REG                  5
#define GCI_CHIPSTATUS_HIB_READ_SHIFT                16
#define GCI_CHIPSTATUS_HIB_READ_MASK                 (0xFF << GCI_CHIPSTATUS_HIB_READ_SHIFT)

#define PMU_CHIPCONTROL_PWM_CLK_ASCU_REG             6
#define PMU_CHIPCONTROL_PWM_CLK_ASCU_SHIFT           21
#define PMU_CHIPCONTROL_PWM_CLK_ASCU_MASK            (1 << PMU_CHIPCONTROL_PWM_CLK_ASCU_SHIFT)
#define PMU_CHIPCONTROL_PWM_CLK_EN_REG               6
#define PMU_CHIPCONTROL_PWM_CLK_EN_SHIFT             27
#define PMU_CHIPCONTROL_PWM_CLK_EN_MASK              (1 << PMU_CHIPCONTROL_PWM_CLK_EN_SHIFT)
#define PMU_CHIPCONTROL_PWM_CLK_SLOW_REG             6
#define PMU_CHIPCONTROL_PWM_CLK_SLOW_SHIFT           28
#define PMU_CHIPCONTROL_PWM_CLK_SLOW_MASK            (1 << PMU_CHIPCONTROL_PWM_CLK_SLOW_SHIFT)

#define PMU_CHIPCONTROL_APP_VDDM_POWER_FORCE_REG     7
#define PMU_CHIPCONTROL_APP_VDDM_POWER_FORCE_SHIFT   31
#define PMU_CHIPCONTROL_APP_VDDM_POWER_FORCE_MASK    (1 << PMU_CHIPCONTROL_APP_VDDM_POWER_FORCE_SHIFT)
#define PMU_CHIPCONTROL_APP_VDDM_POWER_FORCE_EN      (1 << PMU_CHIPCONTROL_APP_VDDM_POWER_FORCE_SHIFT)

#define PMU_REGULATOR_LPLDO1_REG                     4
#define PMU_REGULATOR_LPLDO1_SHIFT                   15
#define PMU_REGULATOR_LPLDO1_MASK                    (0x7 << PMU_REGULATOR_LPLDO1_SHIFT)
#define PMU_REGULATOR_LPLDO1_0_9_V                   (0x4 << PMU_REGULATOR_LPLDO1_SHIFT)
#define PMU_REGULATOR_LPLDO1_1_0_V                   (0x6 << PMU_REGULATOR_LPLDO1_SHIFT)

#define PMU_RES_MASK(bit)                            ( 1UL << (bit) )
#define PMU_RES_LPLDO_PU                             0
#define PMU_RES_BAND_GAP_PU                          1
#define PMU_RES_SLEEP_REGOFF_PULL_DOWN_EN            2
#define PMU_RES_CBUCK_LPOM_PU                        4
#define PMU_RES_CBUCK_PFM                            5
#define PMU_RES_COLD_START_WAIT                      6
#define PMU_RES_APP_VDDM_PWRSW                       7
#define PMU_RES_LNLDO                                8
#define PMU_RES_XTALLDO                              9
#define PMU_RES_LDO3P3                               10
#define PMU_RES_OTP_PU                               11
#define PMU_RES_XTAL_PU                              12
#define PMU_RES_SR_CLK_START                         13
#define PMU_RES_APP_DIGITAL_PWRSW                    14
#define PMU_RES_APP_CORE_READY                       15
#define PMU_RES_APP_CORE_READY_BUF                   16
#define PMU_RES_WL_CORE_READY                        17
#define PMU_RES_WL_CORE_READY_BUF                    18
#define PMU_RES_ALP_AVAIL                            19
#define PMU_RES_MINI_PMU                             20
#define PMU_RES_RADIO_PU                             21
#define PMU_RES_SR_CLK_STABLE                        22
#define PMU_RES_SR_SAVE_RESTORE                      23
#define PMU_RES_SR_VDDM_PWRSW                        25
#define PMU_RES_SR_SUBCORE_AND_PHY_PWRSW             26
#define PMU_RES_SR_SLEEP                             27
#define PMU_RES_HT_START                             28
#define PMU_RES_HT_AVAIL                             29
#define PMU_RES_MAC_PHY_CLK_AVAIL                    30
#define PMU_RES_HT_MASK                              ( PMU_RES_MASK( PMU_RES_LPLDO_PU )                  | \
                                                       PMU_RES_MASK( PMU_RES_BAND_GAP_PU )               | \
                                                       PMU_RES_MASK( PMU_RES_SLEEP_REGOFF_PULL_DOWN_EN ) | \
                                                       PMU_RES_MASK( PMU_RES_CBUCK_LPOM_PU )             | \
                                                       PMU_RES_MASK( PMU_RES_CBUCK_PFM )                 | \
                                                       PMU_RES_MASK( PMU_RES_COLD_START_WAIT )           | \
                                                       PMU_RES_MASK( PMU_RES_LNLDO )                     | \
                                                       PMU_RES_MASK( PMU_RES_XTALLDO )                   | \
                                                       PMU_RES_MASK( PMU_RES_XTAL_PU )                   | \
                                                       PMU_RES_MASK( PMU_RES_ALP_AVAIL )                 | \
                                                       PMU_RES_MASK( PMU_RES_HT_START )                  | \
                                                       PMU_RES_MASK( PMU_RES_HT_AVAIL ) )
#define PMU_RES_DEEP_SLEEP_MASK                      ( PMU_RES_MASK( PMU_RES_LPLDO_PU ) )
#define PMU_RES_SLEEP_MASK                           ( PMU_RES_MASK( PMU_RES_LPLDO_PU )                  | \
                                                       PMU_RES_MASK( PMU_RES_BAND_GAP_PU )               | \
                                                       PMU_RES_MASK( PMU_RES_SLEEP_REGOFF_PULL_DOWN_EN ) | \
                                                       PMU_RES_MASK( PMU_RES_CBUCK_LPOM_PU )             | \
                                                       PMU_RES_MASK( PMU_RES_CBUCK_PFM )                 | \
                                                       PMU_RES_MASK( PMU_RES_COLD_START_WAIT )           | \
                                                       PMU_RES_MASK( PMU_RES_APP_VDDM_PWRSW )            | \
                                                       PMU_RES_MASK( PMU_RES_LNLDO )                     | \
                                                       PMU_RES_MASK( PMU_RES_XTALLDO )                   | \
                                                       PMU_RES_MASK( PMU_RES_LDO3P3 )                    | \
                                                       PMU_RES_MASK( PMU_RES_OTP_PU )                    | \
                                                       PMU_RES_MASK( PMU_RES_APP_DIGITAL_PWRSW )         | \
                                                       PMU_RES_MASK( PMU_RES_APP_CORE_READY )            | \
                                                       PMU_RES_MASK( PMU_RES_APP_CORE_READY_BUF ) )
#define PMU_RES_APPS_UP_MASK                         ( PMU_RES_MASK( PMU_RES_LPLDO_PU )                  | \
                                                       PMU_RES_MASK( PMU_RES_BAND_GAP_PU )               | \
                                                       PMU_RES_MASK( PMU_RES_SLEEP_REGOFF_PULL_DOWN_EN ) | \
                                                       PMU_RES_MASK( PMU_RES_CBUCK_LPOM_PU )             | \
                                                       PMU_RES_MASK( PMU_RES_CBUCK_PFM )                 | \
                                                       PMU_RES_MASK( PMU_RES_COLD_START_WAIT )           | \
                                                       PMU_RES_MASK( PMU_RES_APP_VDDM_PWRSW )            | \
                                                       PMU_RES_MASK( PMU_RES_LNLDO )                     | \
                                                       PMU_RES_MASK( PMU_RES_LDO3P3 )                    | \
                                                       PMU_RES_MASK( PMU_RES_OTP_PU )                    | \
                                                       PMU_RES_MASK( PMU_RES_APP_DIGITAL_PWRSW )         | \
                                                       PMU_RES_MASK( PMU_RES_APP_CORE_READY )            | \
                                                       PMU_RES_MASK( PMU_RES_APP_CORE_READY_BUF )        | \
                                                       PMU_RES_HT_MASK )
#define PMU_RES_WLAN_UP_MASK                         ( PMU_RES_MASK( PMU_RES_LPLDO_PU )                  | \
                                                       PMU_RES_MASK( PMU_RES_BAND_GAP_PU )               | \
                                                       PMU_RES_MASK( PMU_RES_SLEEP_REGOFF_PULL_DOWN_EN ) | \
                                                       PMU_RES_MASK( PMU_RES_CBUCK_LPOM_PU )             | \
                                                       PMU_RES_MASK( PMU_RES_CBUCK_PFM )                 | \
                                                       PMU_RES_MASK( PMU_RES_COLD_START_WAIT )           | \
                                                       PMU_RES_MASK( PMU_RES_LNLDO )                     | \
                                                       PMU_RES_MASK( PMU_RES_XTALLDO )                   | \
                                                       PMU_RES_MASK( PMU_RES_LDO3P3 )                    | \
                                                       PMU_RES_MASK( PMU_RES_OTP_PU )                    | \
                                                       PMU_RES_MASK( PMU_RES_XTAL_PU )                   | \
                                                       PMU_RES_MASK( PMU_RES_SR_CLK_START )              | \
                                                       PMU_RES_MASK( PMU_RES_WL_CORE_READY )             | \
                                                       PMU_RES_MASK( PMU_RES_WL_CORE_READY_BUF )         | \
                                                       PMU_RES_MASK( PMU_RES_ALP_AVAIL )                 | \
                                                       PMU_RES_MASK( PMU_RES_SR_CLK_STABLE )             | \
                                                       PMU_RES_MASK( PMU_RES_SR_SAVE_RESTORE )           | \
                                                       PMU_RES_MASK( PMU_RES_SR_VDDM_PWRSW )             | \
                                                       PMU_RES_MASK( PMU_RES_SR_SUBCORE_AND_PHY_PWRSW )  | \
                                                       PMU_RES_MASK( PMU_RES_SR_SLEEP ) )
#define PMU_RES_WLAN_FAST_UP_MASK                    ( PMU_RES_MASK( PMU_RES_WL_CORE_READY )             | \
                                                       PMU_RES_MASK( PMU_RES_WL_CORE_READY_BUF ) )
#define PMU_RES_MAX_CLEAR_MASK                       0x0
#define PMU_RES_MAX_SET_MASK                         PMU_RES_HT_MASK /* HT resource bits may come cleared after bootrom. */

#define PMU_CONTROL_EXT_FAST_TRANS_EN_SHIFT          0
#define PMU_CONTROL_EXT_FAST_TRANS_EN_MASK           (1 << PMU_CONTROL_EXT_FAST_TRANS_EN_SHIFT)
#define PMU_CONTROL_EXT_ILP_ON_BP_DEBUG_MODE_SHIFT   1
#define PMU_CONTROL_EXT_ILP_ON_BP_DEBUG_MODE_MASK    (1 << PMU_CONTROL_EXT_ILP_ON_BP_DEBUG_MODE_SHIFT)

#define PMU_CONTROL_RESETCONTROL_SHIFT               13
#define PMU_CONTROL_RESETCONTROL_MASK                (0x3 << PMU_CONTROL_RESETCONTROL_SHIFT)
#define PMU_CONTROL_RESETCONTROL_UNTOUCHED           (0x0 << PMU_CONTROL_RESETCONTROL_SHIFT)
#define PMU_CONTROL_RESETCONTROL_RESET               (0x1 << PMU_CONTROL_RESETCONTROL_SHIFT)
#define PMU_CONTROL_RESETCONTROL_RESTORE_RES_MASKS   (0x2 << PMU_CONTROL_RESETCONTROL_SHIFT)

#define PMU_SLOWCLKPERIOD_ALP_PERIOD_MASK            0x3FFF

#define OOB_AOUT_M2M_INTR1                           12
#define OOB_AOUT_PMU_INTR0                           18
#define OOB_AOUT_PMU_INTR1                           20

#define OOB_APPSCR4_TIMER_IRQ_NUM                     0

STRUCTURE_CHECK(  1, chipcommon_regs_t, core_ctrl_status.bist_status, 0x0C );
STRUCTURE_CHECK(  2, chipcommon_regs_t, otp.otp_ctrl_1, 0xF4 );
STRUCTURE_CHECK(  3, chipcommon_regs_t, interrupt.chip_status, 0x2C );
STRUCTURE_CHECK(  4, chipcommon_regs_t, jtag_master.ctrl, 0x3C );
STRUCTURE_CHECK(  5, chipcommon_regs_t, sflash.data, 0x48 );
STRUCTURE_CHECK(  6, chipcommon_regs_t, broadcast.data, 0x54 );
STRUCTURE_CHECK(  7, chipcommon_regs_t, gpio.debug_sel, 0xA8 );
STRUCTURE_CHECK(  8, chipcommon_regs_t, clock_control.clock_divider_2, 0xF0 );
STRUCTURE_CHECK(  9, chipcommon_regs_t, interconnect.flag_status, 0xFE8 );
STRUCTURE_CHECK( 10, chipcommon_regs_t, general_serial_io_controllers.interface_3.clock_divider, 0x4AC );
STRUCTURE_CHECK( 11, chipcommon_regs_t, external_bus_control.parallel_flash.memory_wait_count, 0x12C );
STRUCTURE_CHECK( 12, chipcommon_regs_t, enhanced_coexistence_interface.parallel.data_tag, 0x180 );
STRUCTURE_CHECK( 13, chipcommon_regs_t, enhanced_coexistence_interface.serial.uart.timestamp_fractional_increment, 0x1F8 );
STRUCTURE_CHECK( 14, chipcommon_regs_t, serial_prom.data, 0x198 );
STRUCTURE_CHECK( 15, chipcommon_regs_t, nand_flash.id_status, 0x1B8 );
STRUCTURE_CHECK( 16, chipcommon_regs_t, pmu_clock_control.status, 0x1E0 );
STRUCTURE_CHECK( 17, chipcommon_regs_t, audio_sync_control_unit.sample_cnt1, 0x274 );
STRUCTURE_CHECK( 18, chipcommon_regs_t, uarts.uart[0].scratchpad, 0x307 );
STRUCTURE_CHECK( 19, chipcommon_regs_t, uarts.uart[1].scratchpad, 0x317 );
STRUCTURE_CHECK( 20, chipcommon_regs_t, uarts.uart[2].scratchpad, 0x327 );
STRUCTURE_CHECK( 21, chipcommon_regs_t, pwm.pwm_channels[5].total_period, 0x460 );
STRUCTURE_CHECK( 22, pmu_regs_t,        res_event1, 0x724 );
STRUCTURE_CHECK( 23, pmu_regs_t,        pmuintctrl1, 0x784 );

/******************************************************
 *                 Global Variables
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/

/******************************************************
 *               Function Definitions
 ******************************************************/

static inline __attribute__((always_inline)) void
platform_irq_enable_irq(unsigned irqno)
{
    PLATFORM_APPSCR4_SET_ATOMIC(&PLATFORM_APPSCR4->irq_mask, IRQN2MASK(irqno));
}

static inline __attribute__((always_inline)) void
platform_irq_disable_irq(unsigned irqno)
{
    PLATFORM_APPSCR4_CLEAR_ATOMIC(&PLATFORM_APPSCR4->irq_mask, IRQN2MASK(irqno));
}

static inline __attribute__((always_inline)) int
platform_irq_is_irq_enabled(unsigned irqno)
{
    return ((PLATFORM_APPSCR4->irq_mask & IRQN2MASK(irqno)) != 0);
}

static inline __attribute__((always_inline)) void
platform_irq_enable_int(unsigned irqno)
{
    PLATFORM_APPSCR4_SET_ATOMIC(&PLATFORM_APPSCR4->int_mask, IRQN2MASK(irqno));
}

static inline __attribute__((always_inline)) void
platform_irq_disable_int(unsigned irqno)
{
    PLATFORM_APPSCR4_CLEAR_ATOMIC(&PLATFORM_APPSCR4->int_mask, IRQN2MASK(irqno));
}

static inline __attribute__((always_inline)) int
platform_irq_is_int_enabled(unsigned irqno)
{
    return ((PLATFORM_APPSCR4->int_mask & IRQN2MASK(irqno)) != 0);
}

#ifdef __cplusplus
} /*extern "C" */
#endif
