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
 * Defines BCM43909 common peripheral structures, macros, constants and declares BCM43909 peripheral API
 */
#pragma once

#include "platform_constants.h"
#include "platform_appscr4.h"
#include "wwd_constants.h"
#include "ring_buffer.h"
#include "RTOS/wwd_rtos_interface.h"
#include "platform_appscr4.h"
#include "platform_config.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************
 *                      Macros
 ******************************************************/

#define PLATFORM_DDR_FUNCNAME(type) platform_ddr_init_##type
#define PLATFORM_DDR_FUNCDECL(type) platform_result_t PLATFORM_DDR_FUNCNAME(type)( void )
#if PLATFORM_NO_DDR
#define PLATFORM_DDR_FUNCCALL(type)
#else
#define PLATFORM_DDR_FUNCCALL(type) do {PLATFORM_DDR_FUNCDECL(type); PLATFORM_DDR_FUNCNAME(type)();} while (0)
#endif

/******************************************************
 *                    Constants
 ******************************************************/

/* Default STDIO buffer size */
#ifndef STDIO_BUFFER_SIZE
#define STDIO_BUFFER_SIZE    (64)
#endif

#define UART_CONSOLE_MASK    (0x01)

/* OTP regions */
typedef enum
{
    PLATFORM_OTP_HW_RGN   = 1,
    PLATFORM_OTP_SW_RGN   = 2,
    PLATFORM_OTP_CI_RGN   = 4,
    PLATFORM_OTP_FUSE_RGN = 8,
    PLATFORM_OTP_ALL_RGN  = 0xf /* From h/w region to end of OTP including checksum */
} platform_otp_region_t;

/* Platform Capabilities */
typedef enum
{
    PLATFORM_CAPS_SDIO = (1 << 0),
    PLATFORM_CAPS_GMAC = (1 << 1),
    PLATFORM_CAPS_USB  = (1 << 2),
    PLATFORM_CAPS_HSIC = (1 << 3),
    PLATFORM_CAPS_I2S  = (1 << 4),
    PLATFORM_CAPS_I2C  = (1 << 5),
    PLATFORM_CAPS_UART = (1 << 6),
    PLATFORM_CAPS_DDR  = (1 << 7),
    PLATFORM_CAPS_SPI  = (1 << 8),
    PLATFORM_CAPS_JTAG = (1 << 9)
} platform_caps_t;

/* BCM4390x Platform Common Capabilities */
#define PLATFORM_CAPS_COMMON (PLATFORM_CAPS_I2C | PLATFORM_CAPS_UART | PLATFORM_CAPS_SPI)

#define PLATFORM_CAPABILITY_ENAB(capability) ((platform_capabilities_word & capability) != 0)

/******************************************************
 *                   Enumerations
 ******************************************************/

/*
 * BCM43909 supports pin multiplexing and function selection
 * in accordance with the below PinMux Table specification.
 *
 * Pads           0                   1              2                   3                   4              5                   6              7           8           9                 10                11
 * GPIO_0                             GPIO_0         FAST_UART_RX        I2C1_SDATA          PWM0           SPI1_MISO           PWM2           GPIO_12     GPIO_8                        PWM4              USB20H_CTL1
 * GPIO_1                             GPIO_1         FAST_UART_TX        I2C1_CLK            PWM1           SPI1_CLK            PWM3           GPIO_13     GPIO_9                        PWM5
 * GPIO_2                             GPIO_2                                                 GCI_GPIO_0                                                                TCK
 * GPIO_3                             GPIO_3                                                 GCI_GPIO_1                                                                TMS
 * GPIO_4                             GPIO_4                                                 GCI_GPIO_2                                                                TDI
 * GPIO_5                             GPIO_5                                                 GCI_GPIO_3                                                                TDO
 * GPIO_6                             GPIO_6                                                 GCI_GPIO_4                                                                TRST_L
 * GPIO_7                             GPIO_7         FAST_UART_RTS_OUT   PWM1                PWM3           SPI1_CS             I2C1_CLK       GPIO_15     GPIO_11     PMU_TEST_O                          PWM5
 * GPIO_8                             GPIO_8         SPI1_MISO           PWM2                PWM4           FAST_UART_RX                       GPIO_16     GPIO_12     TAP_SEL_P         I2C1_SDATA        PWM0
 * GPIO_9                             GPIO_9         SPI1_CLK            PWM3                PWM5           FAST_UART_TX                       GPIO_0      GPIO_13                       I2C1_CLK          PWM1
 * GPIO_10                            GPIO_10        SPI1_SISO           PWM4                I2C1_SDATA     FAST_UART_CTS_IN    PWM0           GPIO_1      GPIO_14     PWM2              SDIO_SEP_INT      SDIO_SEP_INT_0D
 * GPIO_11                            GPIO_11        SPI1_CS             PWM5                I2C1_CLK       FAST_UART_RTS_OUT   PWM1           GPIO_7      GPIO_15     PWM3
 * GPIO_12                            GPIO_12        I2C1_SDATA          FAST_UART_RX        SPI1_MISO      PWM2                PWM4           GPIO_8      GPIO_16     PWM0              SDIO_SEP_INT_0D   SDIO_SEP_INT
 * GPIO_13                            GPIO_13        I2C1_CLK            FAST_UART_TX        SPI1_CLK       PWM3                PWM5           GPIO_9      GPIO_0      PWM1
 * GPIO_14                            GPIO_14        PWM0                FAST_UART_CTS_IN    SPI1_SISO      I2C1_SDATA                         GPIO_10                 PWM4                                PWM2
 * GPIO_15                            GPIO_15        PWM1                FAST_UART_RTS_OUT   SPI1_CS        I2C1_CLK                           GPIO_11     GPIO_7      PWM5                                PWM3
 * GPIO_16                            GPIO_16        FAST_UART_CTS_IN    PWM0                PWM2           SPI1_SISO           I2C1_SDATA     GPIO_14     GPIO_10     RF_DISABLE_L      USB20H_CTL2       PWM4
 * sdio_clk       TEST_SDIO_CLK       SDIO_CLK                                                                                                                         SDIO_AOS_CLK
 * sdio_cmd       TEST_SDIO_CMD       SDIO_CMD                                                                                                                         SDIO_AOS_CMD
 * sdio_data_0    TEST_SDIO_DATA_0    SDIO_D0                                                                                                                          SDIO_AOS_D0
 * sdio_data_1    TEST_SDIO_DATA_1    SDIO_D1                                                                                                                          SDIO_AOS_D1
 * sdio_data_2    TEST_SDIO_DATA_2    SDIO_D2                                                                                                                          SDIO_AOS_D2
 * sdio_data_3    TEST_SDIO_DATA_3    SDIO_D3                                                                                                                          SDIO_AOS_D3
 * rf_sw_ctrl_5                       rf_sw_ctrl_5   GCI_GPIO_5
 * rf_sw_ctrl_6                       rf_sw_ctrl_6   UART_DBG_RX         SECI_IN
 * rf_sw_ctrl_7                       rf_sw_ctrl_7   UART_DBG_TX         SECI_OUT
 * rf_sw_ctrl_8                       rf_sw_ctrl_8   SECI_IN             UART_DBG_RX
 * rf_sw_ctrl_9                       rf_sw_ctrl_9   SECI_OUT            UART_DBG_TX
 * PWM0                               PWM0           GPIO_2              GPIO_18
 * PWM1                               PWM1           GPIO_3              GPIO_19
 * PWM2                               PWM2           GPIO_4              GPIO_20
 * PWM3                               PWM3           GPIO_5              GPIO_21
 * PWM4                               PWM4           GPIO_6              GPIO_22
 * PWM5                               PWM5           GPIO_8              GPIO_23
 * SPI0_MISO                          SPI0_MISO      GPIO_17             GPIO_24
 * SPI0_CLK                           SPI0_CLK       GPIO_18             GPIO_25
 * SPI0_SISO                          SPI0_SISO      GPIO_19             GPIO_26
 * SPI0_CS                            SPI0_CS        GPIO_20             GPIO_27
 * I2C0_SDATA                         I2C0_SDATA     GPIO_21             GPIO_28
 * I2C0_CLK                           I2C0_CLK       GPIO_22             GPIO_29
 * i2s_mclk0                          i2s_mclk0      GPIO_23             GPIO_0
 * i2s_sclk0                          i2s_sclk0      GPIO_24             GPIO_2
 * i2s_lrclk0                         i2s_lrclk0     GPIO_25             GPIO_3
 * i2s_sdatai0                        i2s_sdatai0    GPIO_26             GPIO_4
 * i2s_sdatao0                        i2s_sdatao0    GPIO_27             GPIO_5
 * i2s_sdatao1                        i2s_sdatao1    GPIO_28             GPIO_6
 * i2s_sdatai1                        i2s_sdatai1    GPIO_29             GPIO_8
 * i2s_mclk1                          i2s_mclk1      GPIO_30             GPIO_17
 * i2s_sclk1                          i2s_sclk1      GPIO_31             GPIO_30
 * i2s_lrclk1                         i2s_lrclk1     GPIO_0              GPIO_31
 */

/* 43909 pins (Note these are the pad names) */
typedef enum
{
    PIN_GPIO_0,
    PIN_GPIO_1,
    PIN_GPIO_2,
    PIN_GPIO_3,
    PIN_GPIO_4,
    PIN_GPIO_5,
    PIN_GPIO_6,
    PIN_GPIO_7,
    PIN_GPIO_8,
    PIN_GPIO_9,
    PIN_GPIO_10,
    PIN_GPIO_11,
    PIN_GPIO_12,
    PIN_GPIO_13,
    PIN_GPIO_14,
    PIN_GPIO_15,
    PIN_GPIO_16,
    PIN_SDIO_CLK,
    PIN_SDIO_CMD,
    PIN_SDIO_DATA_0,
    PIN_SDIO_DATA_1,
    PIN_SDIO_DATA_2,
    PIN_SDIO_DATA_3,
    PIN_UART0_CTS,
    PIN_UART0_RTS,
    PIN_UART0_RXD,
    PIN_UART0_TXD,
    PIN_PWM_0,
    PIN_PWM_1,
    PIN_PWM_2,
    PIN_PWM_3,
    PIN_PWM_4,
    PIN_PWM_5,
    PIN_RF_SW_CTRL_5,
    PIN_RF_SW_CTRL_6,
    PIN_RF_SW_CTRL_7,
    PIN_RF_SW_CTRL_8,
    PIN_RF_SW_CTRL_9,
    PIN_SPI_0_MISO,
    PIN_SPI_0_CLK,
    PIN_SPI_0_MOSI,
    PIN_SPI_0_CS,
    PIN_I2C0_SDATA,
    PIN_I2C0_CLK,
    PIN_I2S_MCLK0,
    PIN_I2S_SCLK0,
    PIN_I2S_LRCLK0,
    PIN_I2S_SDATAI0,
    PIN_I2S_SDATAO0,
    PIN_I2S_SDATAO1,
    PIN_I2S_SDATAI1,
    PIN_I2S_MCLK1,
    PIN_I2S_SCLK1,
    PIN_I2S_LRCLK1,
    PIN_SPI_1_CLK,
    PIN_SPI_1_MISO,
    PIN_SPI_1_MOSI,
    PIN_SPI_1_CS,
    PIN_I2C1_CLK,
    PIN_I2C1_SDATA,
    PIN_MAX  /* Denotes maximum value. Not a valid pin. */
} platform_pin_t;

/* 43909 pin function selection values (based on PinMux table) */
typedef enum
{
    PIN_FUNCTION_GPIO_0,
    PIN_FUNCTION_GPIO_1,
    PIN_FUNCTION_GPIO_2,
    PIN_FUNCTION_GPIO_3,
    PIN_FUNCTION_GPIO_4,
    PIN_FUNCTION_GPIO_5,
    PIN_FUNCTION_GPIO_6,
    PIN_FUNCTION_GPIO_7,
    PIN_FUNCTION_GPIO_8,
    PIN_FUNCTION_GPIO_9,
    PIN_FUNCTION_GPIO_10,
    PIN_FUNCTION_GPIO_11,
    PIN_FUNCTION_GPIO_12,
    PIN_FUNCTION_GPIO_13,
    PIN_FUNCTION_GPIO_14,
    PIN_FUNCTION_GPIO_15,
    PIN_FUNCTION_GPIO_16,
    PIN_FUNCTION_GPIO_17,
    PIN_FUNCTION_GPIO_18,
    PIN_FUNCTION_GPIO_19,
    PIN_FUNCTION_GPIO_20,
    PIN_FUNCTION_GPIO_21,
    PIN_FUNCTION_GPIO_22,
    PIN_FUNCTION_GPIO_23,
    PIN_FUNCTION_GPIO_24,
    PIN_FUNCTION_GPIO_25,
    PIN_FUNCTION_GPIO_26,
    PIN_FUNCTION_GPIO_27,
    PIN_FUNCTION_GPIO_28,
    PIN_FUNCTION_GPIO_29,
    PIN_FUNCTION_GPIO_30,
    PIN_FUNCTION_GPIO_31,
    PIN_FUNCTION_GCI_GPIO_0,
    PIN_FUNCTION_GCI_GPIO_1,
    PIN_FUNCTION_GCI_GPIO_2,
    PIN_FUNCTION_GCI_GPIO_3,
    PIN_FUNCTION_GCI_GPIO_4,
    PIN_FUNCTION_GCI_GPIO_5,
    PIN_FUNCTION_FAST_UART_RX,
    PIN_FUNCTION_FAST_UART_TX,
    PIN_FUNCTION_FAST_UART_CTS_IN,
    PIN_FUNCTION_FAST_UART_RTS_OUT,
    PIN_FUNCTION_UART_DBG_RX,
    PIN_FUNCTION_UART_DBG_TX,
    PIN_FUNCTION_SECI_IN,
    PIN_FUNCTION_SECI_OUT,
    PIN_FUNCTION_PWM0,
    PIN_FUNCTION_PWM1,
    PIN_FUNCTION_PWM2,
    PIN_FUNCTION_PWM3,
    PIN_FUNCTION_PWM4,
    PIN_FUNCTION_PWM5,
    PIN_FUNCTION_RF_SW_CTRL_5,
    PIN_FUNCTION_RF_SW_CTRL_6,
    PIN_FUNCTION_RF_SW_CTRL_7,
    PIN_FUNCTION_RF_SW_CTRL_8,
    PIN_FUNCTION_RF_SW_CTRL_9,
    PIN_FUNCTION_SPI0_CLK,
    PIN_FUNCTION_SPI0_MISO,
    PIN_FUNCTION_SPI0_MOSI,
    PIN_FUNCTION_SPI0_CS,
    PIN_FUNCTION_SPI1_CLK,
    PIN_FUNCTION_SPI1_MISO,
    PIN_FUNCTION_SPI1_MOSI,
    PIN_FUNCTION_SPI1_CS,
    PIN_FUNCTION_I2C0_SDATA,
    PIN_FUNCTION_I2C0_CLK,
    PIN_FUNCTION_I2C1_SDATA,
    PIN_FUNCTION_I2C1_CLK,
    PIN_FUNCTION_I2S_MCLK0,
    PIN_FUNCTION_I2S_SCLK0,
    PIN_FUNCTION_I2S_LRCLK0,
    PIN_FUNCTION_I2S_SDATAI0,
    PIN_FUNCTION_I2S_SDATAO0,
    PIN_FUNCTION_I2S_MCLK1,
    PIN_FUNCTION_I2S_SCLK1,
    PIN_FUNCTION_I2S_LRCLK1,
    PIN_FUNCTION_I2S_SDATAI1,
    PIN_FUNCTION_I2S_SDATAO1,
    PIN_FUNCTION_TEST_SDIO_CLK,
    PIN_FUNCTION_TEST_SDIO_CMD,
    PIN_FUNCTION_TEST_SDIO_DATA_0,
    PIN_FUNCTION_TEST_SDIO_DATA_1,
    PIN_FUNCTION_TEST_SDIO_DATA_2,
    PIN_FUNCTION_TEST_SDIO_DATA_3,
    PIN_FUNCTION_SDIO_CLK,
    PIN_FUNCTION_SDIO_CMD,
    PIN_FUNCTION_SDIO_D0,
    PIN_FUNCTION_SDIO_D1,
    PIN_FUNCTION_SDIO_D2,
    PIN_FUNCTION_SDIO_D3,
    PIN_FUNCTION_SDIO_AOS_CLK,
    PIN_FUNCTION_SDIO_AOS_CMD,
    PIN_FUNCTION_SDIO_AOS_D0,
    PIN_FUNCTION_SDIO_AOS_D1,
    PIN_FUNCTION_SDIO_AOS_D2,
    PIN_FUNCTION_SDIO_AOS_D3,
    PIN_FUNCTION_SDIO_SEP_INT,
    PIN_FUNCTION_SDIO_SEP_INT_0D,
    PIN_FUNCTION_USB20H_CTL1,
    PIN_FUNCTION_USB20H_CTL2,
    PIN_FUNCTION_RF_DISABLE_L,
    PIN_FUNCTION_TCK,
    PIN_FUNCTION_TMS,
    PIN_FUNCTION_TDI,
    PIN_FUNCTION_TDO,
    PIN_FUNCTION_TRST_L,
    PIN_FUNCTION_PMU_TEST_O,
    PIN_FUNCTION_TAP_SEL_P,
    PIN_FUNCTION_HW_DEFAULT,
    PIN_FUNCTION_SAME_AS_PIN,
    PIN_FUNCTION_UNKNOWN, /* Not a valid pin function */
    PIN_FUNCTION_MAX /* Denotes max value. Not a valid pin function */
} platform_pin_function_t;

/* 43909 pin function configuration values (added as required) */
typedef enum
{
    PIN_FUNCTION_CONFIG_GPIO_INPUT_PULL_UP,
    PIN_FUNCTION_CONFIG_GPIO_INPUT_PULL_DOWN,
    PIN_FUNCTION_CONFIG_GPIO_INPUT_HIGH_IMPEDANCE,
    PIN_FUNCTION_CONFIG_GPIO_OUTPUT_PUSH_PULL,
    PIN_FUNCTION_CONFIG_UNKNOWN,
    PIN_FUNCTION_CONFIG_MAX /* Denotes max value. Not a valid pin function configuration */
} platform_pin_function_config_t;

typedef enum
{
    UART_SLOW,
    UART_FAST,
    UART_GCI
} platform_uart_port_t;

typedef enum
{
    CLOCK_ILP,       /* Idle Low Power Clock */
    CLOCK_ALP,       /* Active Low Power Clock */
    CLOCK_HT,        /* High Throughput Clock */
    CLOCK_BACKPLANE, /* Whatever clock is backplane running now */
} platform_clock_t;

typedef enum
{
    MCU_POWERSAVE_DEEP_SLEEP,
    MCU_POWERSAVE_SLEEP,
    MCU_POWERSAVE_DEFAULT = MCU_POWERSAVE_DEEP_SLEEP
} platform_mcu_powersave_mode_t;

/******************************************************
 *                 Type Definitions
 ******************************************************/

typedef void (*platform_tick_sleep_idle_func)( void );

/******************************************************
 *                    Structures
 ******************************************************/

typedef struct
{
    platform_pin_t pin;
} platform_gpio_t;

typedef struct
{
    platform_uart_port_t   port;
    const platform_gpio_t* tx_pin;
    const platform_gpio_t* rx_pin;
    const platform_gpio_t* cts_pin;
    const platform_gpio_t* rts_pin;
    platform_clock_t       src_clk;
} platform_uart_t;

typedef struct
{
    wiced_ring_buffer_t*   rx_buffer;
    host_semaphore_type_t  rx_complete;
    host_semaphore_type_t  tx_complete;
    platform_uart_t*       interface;
    wiced_bool_t           hw_flow_control_is_on;
} platform_uart_driver_t;


typedef enum
{
    BCM4390X_GSIO_0 = 0,
    BCM4390X_GSIO_1 = 1,
    BCM4390X_GSIO_2 = 2,
    BCM4390X_GSIO_3 = 3,
    BCM4390X_GSIO_MAX,
} platform_gsio_interface_t;

typedef enum
{
    BCM4390X_SPI_0 = BCM4390X_GSIO_0,
    BCM4390X_SPI_1 = BCM4390X_GSIO_1,
} platform_spi_port_t;

typedef enum
{
    BCM4390X_I2C_0 = BCM4390X_GSIO_2,
    BCM4390X_I2C_1 = BCM4390X_GSIO_3,
} platform_i2c_port_t;

typedef struct
{
    platform_spi_port_t                  port;
    uint8_t                              gpio_alternate_function;
    const platform_gpio_t*               pin_mosi;
    const platform_gpio_t*               pin_miso;
    const platform_gpio_t*               pin_clock;
} platform_spi_t;

typedef struct
{
    int junk;
} platform_spi_slave_driver_t;

typedef struct
{
    int junk;
} platform_adc_t;

typedef struct
{
    platform_i2c_port_t                  port;
    uint8_t                              gpio_alternate_function;
    const platform_gpio_t*               pin_scl;
    const platform_gpio_t*               pin_sda;
} platform_i2c_t;

typedef struct
{
    platform_pin_t                       pin;
    platform_pin_function_t              func;
    wiced_bool_t                         update_all;
    wiced_bool_t                         is_single_shot;
    wiced_bool_t                         invert;
    pwm_channel_ctrl_alignment_t         alignment;
    pwm_channel_dead_time_t              dead_time;
} platform_pwm_t;

typedef enum
{
    BCM4390X_I2S_0,
    BCM4390X_I2S_1,
    BCM4390X_I2S_MAX,
} platform_i2s_port_t;

typedef enum
{
    BCM4390X_AUDIO_PLL_AUDIO_SYNC   = 0,
    BCM4390X_AUDIO_PLL_MCLK1        = 1,
    BCM4390X_AUDIO_PLL_MCLK2        = 2,
    BCM4390X_AUDIO_PLL_MAX,
} platform_audio_pll_channels_t;

typedef enum
{
    PLATFORM_I2S_READ,
    PLATFORM_I2S_WRITE,
    PLATFORM_I2S_MAX,
} platform_i2s_direction_t;

typedef struct
{
    platform_i2s_port_t                 port;
    unsigned                            is_master   : 1;
    IRQn_Type                           irqn;
    /* Only applicable when is_master==1. */
    platform_audio_pll_channels_t       audio_pll_ch;
} platform_i2s_port_info_t;

typedef struct
{
    const platform_i2s_port_info_t      *port_info;
    platform_i2s_direction_t            stream_direction;
} platform_i2s_t;

typedef enum
{
    PLATFORM_HIBERNATION_CLOCK_EXTERNAL,
    PLATFORM_HIBERNATION_CLOCK_INTERNAL_128KHZ,
    PLATFORM_HIBERNATION_CLOCK_INTERNAL_32KHZ,
    PLATFORM_HIBERNATION_CLOCK_INTERNAL_16KHZ
} platform_hibernation_clock_t;

typedef struct
{
    platform_hibernation_clock_t clock;              /* Defines which clock - external or internal to use, and if internal then which frequency. */
    uint32_t                     hib_ext_clock_freq; /* Defines external clock frequency, if set 0 then use default configuration. */
    int32_t                      rc_code;            /* Defines RC parameter of internal clock (the higher value, the lower frequency). Has to be created by calibration algorithm and applied by firmware. Negative value means default. */
} platform_hibernation_t;

typedef enum
{
    PLATFORM_TICK_COMMAND_POWERSAVE_BEGIN,
    PLATFORM_TICK_COMMAND_POWERSAVE_END,
    PLATFORM_TICK_COMMAND_RELEASE_PMU_TIMER_BEGIN,
    PLATFORM_TICK_COMMAND_RELEASE_PMU_TIMER_END
} platform_tick_command_t;

typedef enum
{
    PLATFORM_BACKPLANE_APPS,
    PLATFORM_BACKPLANE_WLAN,
    PLATFORM_BACKPLANE_AON
} platform_backplane_t;

/******************************************************
 *                 Global Variables
 ******************************************************/

extern uint32_t platform_capabilities_word;

/******************************************************
 *               Function Declarations
 ******************************************************/


/* Functions related to platform_pinmux driver */
platform_result_t platform_pin_function_init    ( platform_pin_t pin, platform_pin_function_t function, platform_pin_function_config_t config );
platform_result_t platform_pin_function_deinit  ( platform_pin_t pin, platform_pin_function_t function );
/* Call this from GPIO interrupt handler */
void              platform_gpio_irq             ( void );

/* Functions related to platform RTC driver */
platform_result_t platform_rtc_init             ( void );

/* Call this from UART interrupt handler */
void              platform_uart_irq             ( platform_uart_driver_t* driver );

/* Call this from ASCU interrupt handler */
void              platform_ascu_irq             ( uint32_t intr_status );

/* Functions related to ChipCommon */
void              platform_chipcommon_disable_irq ( void );
void              platform_chipcommon_enable_irq  ( void );

/*
 * Set specific GCI chipcontrol register.
 * Function atomically read register reg_offset, clear all bits found in clear_mask, then set all bits found in set_mask. And finally write back result.
*/
uint32_t          platform_gci_chipcontrol      ( uint8_t reg_offset, uint32_t clear_mask, uint32_t set_mask );

/*
 * Return value of specific GCI chipstatus register.
 */
uint32_t          platform_gci_chipstatus       (uint8_t reg_offset);

/*
 * Set specific PMU chipcontrol register.
 * Function atomically read register reg_offset, clear all bits found in clear_mask, then set all bits found in set_mask. And finally write back result.
*/
uint32_t          platform_pmu_chipcontrol      ( uint8_t reg_offset, uint32_t clear_mask, uint32_t set_mask );

/*
 * Set specific PMU regulator register.
 * Function atomically read register reg_offset, clear all bits found in clear_mask, then set all bits found in set_mask. And finally write back result.
*/
uint32_t          platform_pmu_regulatorcontrol (uint8_t reg_offset, uint32_t clear_mask, uint32_t set_mask);

/*
 * Modify generic register.
 * Function atomically read register reg_offset, clear all bits found in clear_mask, then set all bits found in set_mask. And finally write back result.
 */
uint32_t          platform_common_chipcontrol   (volatile uint32_t* reg, uint32_t clear_mask, uint32_t set_mask);

/* Return default PWM clock. Platform code can redefine if want to choose another. */
platform_clock_t  platform_pwm_getclock         ( void );

platform_result_t platform_filesystem_init      ( void );

platform_result_t platform_watchdog_init        ( void );

platform_result_t platform_backplane_init       ( void );

void              platform_backplane_print_cores( uint32_t backplane_mask );

void              platform_backplane_reset_cores( uint32_t* except_wrappers, uint32_t backplane_mask );

void              platform_irq_init             ( void );

platform_result_t platform_irq_remap_source     ( uint32_t wrapper_addr, uint8_t source_num, uint8_t bus_line_num );

platform_result_t platform_irq_remap_sink       ( uint8_t bus_line_num, uint8_t sink_num );

platform_result_t platform_mcu_powersave_init         ( void );

void              platform_mcu_powersave_set_mode     ( platform_mcu_powersave_mode_t mode );

void              platform_mcu_powersave_warmboot_init( void );

wiced_bool_t      platform_mcu_powersave_is_warmboot  ( void );

wiced_bool_t      platform_wlan_powersave_res_up   ( void );

wiced_bool_t      platform_wlan_powersave_res_down ( wiced_bool_t(*check_ready)(void), wiced_bool_t force );

void              platform_wlan_powersave_res_event( void );

uint32_t          platform_tick_sleep           ( platform_tick_sleep_idle_func idle_func, uint32_t ticks, wiced_bool_t powersave_permission );

void              platform_tick_execute_command ( platform_tick_command_t command );

void              platform_lpo_clock_init       ( void );

void              platform_sflash_init          ( void );

platform_result_t platform_hibernation_init     ( const platform_hibernation_t* hib );

/* Functions related to platform OTP driver */
platform_result_t platform_otp_init             ( void );
platform_result_t platform_otp_status           ( uint32_t* status );
platform_result_t platform_otp_size             ( uint32_t* size );
platform_result_t platform_otp_read_bit         ( unsigned int offset, uint16_t* read_bit );
platform_result_t platform_otp_read_word        ( unsigned int wn, uint16_t* data );
platform_result_t platform_otp_read_region      ( platform_otp_region_t region, uint16_t* data, unsigned int* wlen );
platform_result_t platform_otp_newcis           ( uint16_t* newcis_bit );
platform_result_t platform_otp_isunified        ( wiced_bool_t* is_unified );
platform_result_t platform_otp_avsbitslen       ( uint16_t* avsbitslen );

#ifdef __cplusplus
} /* extern "C" */
#endif

