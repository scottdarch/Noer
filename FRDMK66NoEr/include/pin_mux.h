/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction {
    kPIN_MUX_DirectionInput         = 0U, /* Input direction */
    kPIN_MUX_DirectionOutput        = 1U, /* Output direction */
    kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/* PORTB16 (coord E10), U7[4]/UART0_RX */
#define BOARD_DEBUG_UART_RX_PERIPHERAL UART0       /*!< Device name: UART0 */
#define BOARD_DEBUG_UART_RX_SIGNAL RX              /*!< UART0 signal: RX */
#define BOARD_DEBUG_UART_RX_PIN_NAME UART0_RX      /*!< Pin name */
#define BOARD_DEBUG_UART_RX_LABEL "U7[4]/UART0_RX" /*!< Label */
#define BOARD_DEBUG_UART_RX_NAME "DEBUG_UART_RX"   /*!< Identifier name */

/* PORTB17 (coord E9), U10[1]/UART0_TX */
#define BOARD_DEBUG_UART_TX_PERIPHERAL UART0        /*!< Device name: UART0 */
#define BOARD_DEBUG_UART_TX_SIGNAL TX               /*!< UART0 signal: TX */
#define BOARD_DEBUG_UART_TX_PIN_NAME UART0_TX       /*!< Pin name */
#define BOARD_DEBUG_UART_TX_LABEL "U10[1]/UART0_TX" /*!< Label */
#define BOARD_DEBUG_UART_TX_NAME "DEBUG_UART_TX"    /*!< Identifier name */

/* ADC0_SE16 (coord J3), J4[5]/ADC0 */
#define BOARD_ADC0_SE16_PERIPHERAL ADC0    /*!< Device name: ADC0 */
#define BOARD_ADC0_SE16_SIGNAL SE          /*!< ADC0 signal: SE */
#define BOARD_ADC0_SE16_CHANNEL 16         /*!< ADC0 SE channel: 16 */
#define BOARD_ADC0_SE16_PIN_NAME ADC0_SE16 /*!< Pin name */
#define BOARD_ADC0_SE16_LABEL "J4[5]/ADC0" /*!< Label */
#define BOARD_ADC0_SE16_NAME "ADC0_SE16"   /*!< Identifier name */

/* PORTA1 (coord J6), J3[15]/FTM0_CH6 */
#define BOARD_FTM0_CH6_GPIO GPIOA                         /*!< GPIO device name: GPIOA */
#define BOARD_FTM0_CH6_PORT PORTA                         /*!< PORT device name: PORTA */
#define BOARD_FTM0_CH6_GPIO_PIN 1U                        /*!< PORTA pin index: 1 */
#define BOARD_FTM0_CH6_PIN_NAME PTA1                      /*!< Pin name */
#define BOARD_FTM0_CH6_LABEL "J3[15]/FTM0_CH6"            /*!< Label */
#define BOARD_FTM0_CH6_NAME "FTM0_CH6"                    /*!< Identifier name */
#define BOARD_FTM0_CH6_DIRECTION kPIN_MUX_DirectionOutput /*!< Direction */

/* ADC1_DP0 (coord M1), J4[1]/DIFF_ADC1_DP0 */
#define BOARD_DIFF_ADC1_DP0_PERIPHERAL ADC1             /*!< Device name: ADC1 */
#define BOARD_DIFF_ADC1_DP0_SIGNAL DP                   /*!< ADC1 signal: DP */
#define BOARD_DIFF_ADC1_DP0_CHANNEL 0                   /*!< ADC1 DP channel: 0 */
#define BOARD_DIFF_ADC1_DP0_PIN_NAME ADC1_DP0           /*!< Pin name */
#define BOARD_DIFF_ADC1_DP0_LABEL "J4[1]/DIFF_ADC1_DP0" /*!< Label */
#define BOARD_DIFF_ADC1_DP0_NAME "DIFF_ADC1_DP0"        /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

/* PORTD11 (coord B2), SW2 */
#define BOARD_SW2_GPIO GPIOD                        /*!< GPIO device name: GPIOD */
#define BOARD_SW2_PORT PORTD                        /*!< PORT device name: PORTD */
#define BOARD_SW2_GPIO_PIN 11U                      /*!< PORTD pin index: 11 */
#define BOARD_SW2_PIN_NAME PTD11                    /*!< Pin name */
#define BOARD_SW2_LABEL "SW2"                       /*!< Label */
#define BOARD_SW2_NAME "SW2"                        /*!< Identifier name */
#define BOARD_SW2_DIRECTION kPIN_MUX_DirectionInput /*!< Direction */

/* PORTA10 (coord M9), SW3 */
#define BOARD_SW3_GPIO GPIOA                        /*!< GPIO device name: GPIOA */
#define BOARD_SW3_PORT PORTA                        /*!< PORT device name: PORTA */
#define BOARD_SW3_GPIO_PIN 10U                      /*!< PORTA pin index: 10 */
#define BOARD_SW3_PIN_NAME PTA10                    /*!< Pin name */
#define BOARD_SW3_LABEL "SW3"                       /*!< Label */
#define BOARD_SW3_NAME "SW3"                        /*!< Identifier name */
#define BOARD_SW3_DIRECTION kPIN_MUX_DirectionInput /*!< Direction */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitBUTTONs(void);

/* PORTA11 (coord L9), LEDRGB_BLUE */
#define BOARD_LED_BLUE_GPIO GPIOA                         /*!< GPIO device name: GPIOA */
#define BOARD_LED_BLUE_PORT PORTA                         /*!< PORT device name: PORTA */
#define BOARD_LED_BLUE_GPIO_PIN 11U                       /*!< PORTA pin index: 11 */
#define BOARD_LED_BLUE_PIN_NAME PTA11                     /*!< Pin name */
#define BOARD_LED_BLUE_LABEL "LEDRGB_BLUE"                /*!< Label */
#define BOARD_LED_BLUE_NAME "LED_BLUE"                    /*!< Identifier name */
#define BOARD_LED_BLUE_DIRECTION kPIN_MUX_DirectionOutput /*!< Direction */

/* PORTE6 (coord E1), LEDRGB_GREEN */
#define BOARD_LED_GREEN_GPIO GPIOE                         /*!< GPIO device name: GPIOE */
#define BOARD_LED_GREEN_PORT PORTE                         /*!< PORT device name: PORTE */
#define BOARD_LED_GREEN_GPIO_PIN 6U                        /*!< PORTE pin index: 6 */
#define BOARD_LED_GREEN_PIN_NAME PTE6                      /*!< Pin name */
#define BOARD_LED_GREEN_LABEL "LEDRGB_GREEN"               /*!< Label */
#define BOARD_LED_GREEN_NAME "LED_GREEN"                   /*!< Identifier name */
#define BOARD_LED_GREEN_DIRECTION kPIN_MUX_DirectionOutput /*!< Direction */

/* PORTC9 (coord D7), LEDRGB_RED */
#define BOARD_LED_RED_GPIO GPIOC                         /*!< GPIO device name: GPIOC */
#define BOARD_LED_RED_PORT PORTC                         /*!< PORT device name: PORTC */
#define BOARD_LED_RED_GPIO_PIN 9U                        /*!< PORTC pin index: 9 */
#define BOARD_LED_RED_PIN_NAME PTC9                      /*!< Pin name */
#define BOARD_LED_RED_LABEL "LEDRGB_RED"                 /*!< Label */
#define BOARD_LED_RED_NAME "LED_RED"                     /*!< Identifier name */
#define BOARD_LED_RED_DIRECTION kPIN_MUX_DirectionOutput /*!< Direction */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDs(void);

/* PORTD8 (coord C9), U8[4]/U19[11]/I2C0_SCL */
#define BOARD_ACCEL_SCL_PERIPHERAL I2C0                /*!< Device name: I2C0 */
#define BOARD_ACCEL_SCL_SIGNAL SCL                     /*!< I2C0 signal: SCL */
#define BOARD_ACCEL_SCL_PIN_NAME I2C0_SCL              /*!< Pin name */
#define BOARD_ACCEL_SCL_LABEL "U8[4]/U19[11]/I2C0_SCL" /*!< Label */
#define BOARD_ACCEL_SCL_NAME "ACCEL_SCL"               /*!< Identifier name */

/* PORTD9 (coord B9), U8[6]/U19[12]/I2C0_SDA */
#define BOARD_ACCEL_SDA_PERIPHERAL I2C0                /*!< Device name: I2C0 */
#define BOARD_ACCEL_SDA_SIGNAL SDA                     /*!< I2C0 signal: SDA */
#define BOARD_ACCEL_SDA_PIN_NAME I2C0_SDA              /*!< Pin name */
#define BOARD_ACCEL_SDA_LABEL "U8[6]/U19[12]/I2C0_SDA" /*!< Label */
#define BOARD_ACCEL_SDA_NAME "ACCEL_SDA"               /*!< Identifier name */

/* PORTC17 (coord D5), U8[11]/FXOS8700CQ_INT1 */
#define BOARD_ACCEL_INT1_GPIO GPIOC                        /*!< GPIO device name: GPIOC */
#define BOARD_ACCEL_INT1_PORT PORTC                        /*!< PORT device name: PORTC */
#define BOARD_ACCEL_INT1_GPIO_PIN 17U                      /*!< PORTC pin index: 17 */
#define BOARD_ACCEL_INT1_PIN_NAME PTC17                    /*!< Pin name */
#define BOARD_ACCEL_INT1_LABEL "U8[11]/FXOS8700CQ_INT1"    /*!< Label */
#define BOARD_ACCEL_INT1_NAME "ACCEL_INT1"                 /*!< Identifier name */
#define BOARD_ACCEL_INT1_DIRECTION kPIN_MUX_DirectionInput /*!< Direction */

/* PORTC13 (coord D6), U8[9]/FXOS8700CQ_INT2 */
#define BOARD_ACCEL_INT2_GPIO GPIOC                        /*!< GPIO device name: GPIOC */
#define BOARD_ACCEL_INT2_PORT PORTC                        /*!< PORT device name: PORTC */
#define BOARD_ACCEL_INT2_GPIO_PIN 13U                      /*!< PORTC pin index: 13 */
#define BOARD_ACCEL_INT2_PIN_NAME PTC13                    /*!< Pin name */
#define BOARD_ACCEL_INT2_LABEL "U8[9]/FXOS8700CQ_INT2"     /*!< Label */
#define BOARD_ACCEL_INT2_NAME "ACCEL_INT2"                 /*!< Identifier name */
#define BOARD_ACCEL_INT2_DIRECTION kPIN_MUX_DirectionInput /*!< Direction */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitACCEL_I2C(void);

/* PORTD9 (coord B9), U8[6]/U19[12]/I2C0_SDA */
#define BOARD_GYRO_SDA_PERIPHERAL I2C0                /*!< Device name: I2C0 */
#define BOARD_GYRO_SDA_SIGNAL SDA                     /*!< I2C0 signal: SDA */
#define BOARD_GYRO_SDA_PIN_NAME I2C0_SDA              /*!< Pin name */
#define BOARD_GYRO_SDA_LABEL "U8[6]/U19[12]/I2C0_SDA" /*!< Label */
#define BOARD_GYRO_SDA_NAME "GYRO_SDA"                /*!< Identifier name */

/* PORTD8 (coord C9), U8[4]/U19[11]/I2C0_SCL */
#define BOARD_GYRO_SCL_PERIPHERAL I2C0                /*!< Device name: I2C0 */
#define BOARD_GYRO_SCL_SIGNAL SCL                     /*!< I2C0 signal: SCL */
#define BOARD_GYRO_SCL_PIN_NAME I2C0_SCL              /*!< Pin name */
#define BOARD_GYRO_SCL_LABEL "U8[4]/U19[11]/I2C0_SCL" /*!< Label */
#define BOARD_GYRO_SCL_NAME "GYRO_SCL"                /*!< Identifier name */

/* PORTA29 (coord H11), U19[3]/FXAS21002_INT1 */
#define BOARD_GYRO_INT1_GPIO GPIOA                        /*!< GPIO device name: GPIOA */
#define BOARD_GYRO_INT1_PORT PORTA                        /*!< PORT device name: PORTA */
#define BOARD_GYRO_INT1_GPIO_PIN 29U                      /*!< PORTA pin index: 29 */
#define BOARD_GYRO_INT1_PIN_NAME PTA29                    /*!< Pin name */
#define BOARD_GYRO_INT1_LABEL "U19[3]/FXAS21002_INT1"     /*!< Label */
#define BOARD_GYRO_INT1_NAME "GYRO_INT1"                  /*!< Identifier name */
#define BOARD_GYRO_INT1_DIRECTION kPIN_MUX_DirectionInput /*!< Direction */

/* PORTA28 (coord H12), U19[2]/FXAS21002_INT2 */
#define BOARD_GYRO_INT2_GPIO GPIOA                        /*!< GPIO device name: GPIOA */
#define BOARD_GYRO_INT2_PORT PORTA                        /*!< PORT device name: PORTA */
#define BOARD_GYRO_INT2_GPIO_PIN 28U                      /*!< PORTA pin index: 28 */
#define BOARD_GYRO_INT2_PIN_NAME PTA28                    /*!< Pin name */
#define BOARD_GYRO_INT2_LABEL "U19[2]/FXAS21002_INT2"     /*!< Label */
#define BOARD_GYRO_INT2_NAME "GYRO_INT2"                  /*!< Identifier name */
#define BOARD_GYRO_INT2_DIRECTION kPIN_MUX_DirectionInput /*!< Direction */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitGYRO_I2C(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UART(void);

/* PORTE3 (coord E4), SDHC0_CMD */
#define BOARD_SDHC0_CMD_PERIPHERAL SDHC    /*!< Device name: SDHC */
#define BOARD_SDHC0_CMD_SIGNAL CMD         /*!< SDHC signal: CMD */
#define BOARD_SDHC0_CMD_PIN_NAME SDHC0_CMD /*!< Pin name */
#define BOARD_SDHC0_CMD_LABEL "SDHC0_CMD"  /*!< Label */
#define BOARD_SDHC0_CMD_NAME "SDHC0_CMD"   /*!< Identifier name */

/* PORTE1 (coord D2), SDHC0_D0 */
#define BOARD_SDHC0_D0_PERIPHERAL SDHC   /*!< Device name: SDHC */
#define BOARD_SDHC0_D0_SIGNAL DATA       /*!< SDHC signal: DATA */
#define BOARD_SDHC0_D0_CHANNEL 0         /*!< SDHC DATA channel: 0 */
#define BOARD_SDHC0_D0_PIN_NAME SDHC0_D0 /*!< Pin name */
#define BOARD_SDHC0_D0_LABEL "SDHC0_D0"  /*!< Label */
#define BOARD_SDHC0_D0_NAME "SDHC0_D0"   /*!< Identifier name */

/* PORTE0 (coord D3), SDHC0_D1 */
#define BOARD_SDHC0_D1_PERIPHERAL SDHC   /*!< Device name: SDHC */
#define BOARD_SDHC0_D1_SIGNAL DATA       /*!< SDHC signal: DATA */
#define BOARD_SDHC0_D1_CHANNEL 1         /*!< SDHC DATA channel: 1 */
#define BOARD_SDHC0_D1_PIN_NAME SDHC0_D1 /*!< Pin name */
#define BOARD_SDHC0_D1_LABEL "SDHC0_D1"  /*!< Label */
#define BOARD_SDHC0_D1_NAME "SDHC0_D1"   /*!< Identifier name */

/* PORTE5 (coord E2), SDHC0_D2 */
#define BOARD_SDHC0_D2_PERIPHERAL SDHC   /*!< Device name: SDHC */
#define BOARD_SDHC0_D2_SIGNAL DATA       /*!< SDHC signal: DATA */
#define BOARD_SDHC0_D2_CHANNEL 2         /*!< SDHC DATA channel: 2 */
#define BOARD_SDHC0_D2_PIN_NAME SDHC0_D2 /*!< Pin name */
#define BOARD_SDHC0_D2_LABEL "SDHC0_D2"  /*!< Label */
#define BOARD_SDHC0_D2_NAME "SDHC0_D2"   /*!< Identifier name */

/* PORTE4 (coord E3), SDHC0_D3 */
#define BOARD_SDHC0_D3_PERIPHERAL SDHC   /*!< Device name: SDHC */
#define BOARD_SDHC0_D3_SIGNAL DATA       /*!< SDHC signal: DATA */
#define BOARD_SDHC0_D3_CHANNEL 3         /*!< SDHC DATA channel: 3 */
#define BOARD_SDHC0_D3_PIN_NAME SDHC0_D3 /*!< Pin name */
#define BOARD_SDHC0_D3_LABEL "SDHC0_D3"  /*!< Label */
#define BOARD_SDHC0_D3_NAME "SDHC0_D3"   /*!< Identifier name */

/* PORTE2 (coord D1), SDHC0_DCLK */
#define BOARD_SDHC0_DCLK_PERIPHERAL SDHC     /*!< Device name: SDHC */
#define BOARD_SDHC0_DCLK_SIGNAL DCLK         /*!< SDHC signal: DCLK */
#define BOARD_SDHC0_DCLK_PIN_NAME SDHC0_DCLK /*!< Pin name */
#define BOARD_SDHC0_DCLK_LABEL "SDHC0_DCLK"  /*!< Label */
#define BOARD_SDHC0_DCLK_NAME "SDHC0_DCLK"   /*!< Identifier name */

/* PORTD10 (coord B3), SD_CARD_DETECT */
#define BOARD_SDCARD_CARD_DETECTION_GPIO GPIOD                   /*!< GPIO device name: GPIOD */
#define BOARD_SDCARD_CARD_DETECTION_PORT PORTD                   /*!< PORT device name: PORTD */
#define BOARD_SDCARD_CARD_DETECTION_GPIO_PIN 10U                 /*!< PORTD pin index: 10 */
#define BOARD_SDCARD_CARD_DETECTION_PIN_NAME PTD10               /*!< Pin name */
#define BOARD_SDCARD_CARD_DETECTION_LABEL "SD_CARD_DETECT"       /*!< Label */
#define BOARD_SDCARD_CARD_DETECTION_NAME "SDCARD_CARD_DETECTION" /*!< Identifier name */
#define BOARD_SDCARD_CARD_DETECTION_DIRECTION kPIN_MUX_DirectionInput /*!< Direction */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSDHC0(void);

/* PORTE26 (coord K4), U13[16]/ETHERNET_CLOCK */
#define BOARD_ETHERNET_CLOCK_PERIPHERAL ENET                /*!< Device name: ENET */
#define BOARD_ETHERNET_CLOCK_SIGNAL RMII_CLKIN              /*!< ENET signal: RMII_CLKIN */
#define BOARD_ETHERNET_CLOCK_PIN_NAME ENET_1588_CLKIN       /*!< Pin name */
#define BOARD_ETHERNET_CLOCK_LABEL "U13[16]/ETHERNET_CLOCK" /*!< Label */
#define BOARD_ETHERNET_CLOCK_NAME "ETHERNET_CLOCK"          /*!< Identifier name */

/* PORTA14 (coord L10), U13[15]/RMII0_CRS_DV */
#define BOARD_RMII0_CRS_DV_PERIPHERAL ENET              /*!< Device name: ENET */
#define BOARD_RMII0_CRS_DV_SIGNAL RMII_CRS_DV           /*!< ENET signal: RMII_CRS_DV */
#define BOARD_RMII0_CRS_DV_PIN_NAME RMII0_CRS_DV        /*!< Pin name */
#define BOARD_RMII0_CRS_DV_LABEL "U13[15]/RMII0_CRS_DV" /*!< Label */
#define BOARD_RMII0_CRS_DV_NAME "RMII0_CRS_DV"          /*!< Identifier name */

/* PORTB1 (coord H9), U13[11]/RMII0_MDC */
#define BOARD_RMII0_MDC_PERIPHERAL ENET           /*!< Device name: ENET */
#define BOARD_RMII0_MDC_SIGNAL RMII_MDC           /*!< ENET signal: RMII_MDC */
#define BOARD_RMII0_MDC_PIN_NAME RMII0_MDC        /*!< Pin name */
#define BOARD_RMII0_MDC_LABEL "U13[11]/RMII0_MDC" /*!< Label */
#define BOARD_RMII0_MDC_NAME "RMII0_MDC"          /*!< Identifier name */

/* PORTB0 (coord H10), U13[10]/RMII0_MDIO */
#define BOARD_RMII0_MDIO_PERIPHERAL ENET            /*!< Device name: ENET */
#define BOARD_RMII0_MDIO_SIGNAL RMII_MDIO           /*!< ENET signal: RMII_MDIO */
#define BOARD_RMII0_MDIO_PIN_NAME RMII0_MDIO        /*!< Pin name */
#define BOARD_RMII0_MDIO_LABEL "U13[10]/RMII0_MDIO" /*!< Label */
#define BOARD_RMII0_MDIO_NAME "RMII0_MDIO"          /*!< Identifier name */

/* PORTA13 (coord J9), U13[13]/RMII0_RXD0 */
#define BOARD_RMII0_RXD0_PERIPHERAL ENET            /*!< Device name: ENET */
#define BOARD_RMII0_RXD0_SIGNAL RMII_RXD0           /*!< ENET signal: RMII_RXD0 */
#define BOARD_RMII0_RXD0_PIN_NAME RMII0_RXD0        /*!< Pin name */
#define BOARD_RMII0_RXD0_LABEL "U13[13]/RMII0_RXD0" /*!< Label */
#define BOARD_RMII0_RXD0_NAME "RMII0_RXD0"          /*!< Identifier name */

/* PORTA12 (coord K9), U13[12]/RMII0_RXD1 */
#define BOARD_RMII0_RXD1_PERIPHERAL ENET            /*!< Device name: ENET */
#define BOARD_RMII0_RXD1_SIGNAL RMII_RXD1           /*!< ENET signal: RMII_RXD1 */
#define BOARD_RMII0_RXD1_PIN_NAME RMII0_RXD1        /*!< Pin name */
#define BOARD_RMII0_RXD1_LABEL "U13[12]/RMII0_RXD1" /*!< Label */
#define BOARD_RMII0_RXD1_NAME "RMII0_RXD1"          /*!< Identifier name */

/* PORTA5 (coord M8), U13[17]/RMII0_RXER */
#define BOARD_RMII0_RXER_PERIPHERAL ENET            /*!< Device name: ENET */
#define BOARD_RMII0_RXER_SIGNAL RMII_RXER           /*!< ENET signal: RMII_RXER */
#define BOARD_RMII0_RXER_PIN_NAME RMII0_RXER        /*!< Pin name */
#define BOARD_RMII0_RXER_LABEL "U13[17]/RMII0_RXER" /*!< Label */
#define BOARD_RMII0_RXER_NAME "RMII0_RXER"          /*!< Identifier name */

/* PORTA16 (coord K10), U13[20]/RMII0_TXD_0 */
#define BOARD_RMII0_TXD_0_PERIPHERAL ENET             /*!< Device name: ENET */
#define BOARD_RMII0_TXD_0_SIGNAL RMII_TXD0            /*!< ENET signal: RMII_TXD0 */
#define BOARD_RMII0_TXD_0_PIN_NAME RMII0_TXD0         /*!< Pin name */
#define BOARD_RMII0_TXD_0_LABEL "U13[20]/RMII0_TXD_0" /*!< Label */
#define BOARD_RMII0_TXD_0_NAME "RMII0_TXD_0"          /*!< Identifier name */

/* PORTA17 (coord K11), U13[21]/RMII0_TXD_1 */
#define BOARD_RMII0_TXD_1_PERIPHERAL ENET             /*!< Device name: ENET */
#define BOARD_RMII0_TXD_1_SIGNAL RMII_TXD1            /*!< ENET signal: RMII_TXD1 */
#define BOARD_RMII0_TXD_1_PIN_NAME RMII0_TXD1         /*!< Pin name */
#define BOARD_RMII0_TXD_1_LABEL "U13[21]/RMII0_TXD_1" /*!< Label */
#define BOARD_RMII0_TXD_1_NAME "RMII0_TXD_1"          /*!< Identifier name */

/* PORTA15 (coord L11), U13[19]/RMII0_TXEN */
#define BOARD_RMII0_TXEN_PERIPHERAL ENET            /*!< Device name: ENET */
#define BOARD_RMII0_TXEN_SIGNAL RMII_TXEN           /*!< ENET signal: RMII_TXEN */
#define BOARD_RMII0_TXEN_PIN_NAME RMII0_TXEN        /*!< Pin name */
#define BOARD_RMII0_TXEN_LABEL "U13[19]/RMII0_TXEN" /*!< Label */
#define BOARD_RMII0_TXEN_NAME "RMII0_TXEN"          /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitENET(void);

/* USB1_DM (coord K1), K66_MICRO_USB_DN */
#define BOARD_K66_MICRO_USB_DN_DCD_PERIPHERAL USBHSDCD         /*!< Device name: USBHSDCD */
#define BOARD_K66_MICRO_USB_DN_DCD_SIGNAL DM                   /*!< USBHSDCD signal: DM */
#define BOARD_K66_MICRO_USB_DN_DCD_PIN_NAME USB1_DM            /*!< Pin name */
#define BOARD_K66_MICRO_USB_DN_DCD_LABEL "K66_MICRO_USB_DN"    /*!< Label */
#define BOARD_K66_MICRO_USB_DN_DCD_NAME "K66_MICRO_USB_DN_DCD" /*!< Identifier name */

/* USB1_DP (coord J1), K66_MICRO_USB_DP */
#define BOARD_K66_MICRO_USB_DP_DCD_PERIPHERAL USBHSDCD         /*!< Device name: USBHSDCD */
#define BOARD_K66_MICRO_USB_DP_DCD_SIGNAL DP                   /*!< USBHSDCD signal: DP */
#define BOARD_K66_MICRO_USB_DP_DCD_PIN_NAME USB1_DP            /*!< Pin name */
#define BOARD_K66_MICRO_USB_DP_DCD_LABEL "K66_MICRO_USB_DP"    /*!< Label */
#define BOARD_K66_MICRO_USB_DP_DCD_NAME "K66_MICRO_USB_DP_DCD" /*!< Identifier name */

/* USB1_DM (coord K1), K66_MICRO_USB_DN */
#define BOARD_K66_MICRO_USB_DN_PHY_PERIPHERAL USBPHY           /*!< Device name: USBPHY */
#define BOARD_K66_MICRO_USB_DN_PHY_SIGNAL DM                   /*!< USBPHY signal: DM */
#define BOARD_K66_MICRO_USB_DN_PHY_PIN_NAME USB1_DM            /*!< Pin name */
#define BOARD_K66_MICRO_USB_DN_PHY_LABEL "K66_MICRO_USB_DN"    /*!< Label */
#define BOARD_K66_MICRO_USB_DN_PHY_NAME "K66_MICRO_USB_DN_PHY" /*!< Identifier name */

/* USB1_DP (coord J1), K66_MICRO_USB_DP */
#define BOARD_K66_MICRO_USB_DP_PHY_PERIPHERAL USBPHY           /*!< Device name: USBPHY */
#define BOARD_K66_MICRO_USB_DP_PHY_SIGNAL DP                   /*!< USBPHY signal: DP */
#define BOARD_K66_MICRO_USB_DP_PHY_PIN_NAME USB1_DP            /*!< Pin name */
#define BOARD_K66_MICRO_USB_DP_PHY_LABEL "K66_MICRO_USB_DP"    /*!< Label */
#define BOARD_K66_MICRO_USB_DP_PHY_NAME "K66_MICRO_USB_DP_PHY" /*!< Identifier name */

/* PORTE10 (coord F1), USB_ID */
#define BOARD_USB_ID_PERIPHERAL USBPHY /*!< Device name: USBPHY */
#define BOARD_USB_ID_SIGNAL ID         /*!< USBPHY signal: ID */
#define BOARD_USB_ID_PIN_NAME USB1_ID  /*!< Pin name */
#define BOARD_USB_ID_LABEL "USB_ID"    /*!< Label */
#define BOARD_USB_ID_NAME "USB_ID"     /*!< Identifier name */

/* USB1_VBUS (coord L1), P5V_K66_USB */
#define BOARD_P5V_K66_USB_PERIPHERAL USBPHY   /*!< Device name: USBPHY */
#define BOARD_P5V_K66_USB_SIGNAL VBUS         /*!< USBPHY signal: VBUS */
#define BOARD_P5V_K66_USB_PIN_NAME USB1_VBUS  /*!< Pin name */
#define BOARD_P5V_K66_USB_LABEL "P5V_K66_USB" /*!< Label */
#define BOARD_P5V_K66_USB_NAME "P5V_K66_USB"  /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitUSB(void);

/* PORTA18 (coord M12), EXTAL0 */
#define BOARD_EXTAL0_PERIPHERAL OSC  /*!< Device name: OSC */
#define BOARD_EXTAL0_SIGNAL EXTAL0   /*!< OSC signal: EXTAL0 */
#define BOARD_EXTAL0_PIN_NAME EXTAL0 /*!< Pin name */
#define BOARD_EXTAL0_LABEL "EXTAL0"  /*!< Label */
#define BOARD_EXTAL0_NAME "EXTAL0"   /*!< Identifier name */

/* PORTA19 (coord M11), X501[3] */
#define BOARD_XTAL0_PERIPHERAL OSC  /*!< Device name: OSC */
#define BOARD_XTAL0_SIGNAL XTAL0    /*!< OSC signal: XTAL0 */
#define BOARD_XTAL0_PIN_NAME XTAL0  /*!< Pin name */
#define BOARD_XTAL0_LABEL "X501[3]" /*!< Label */
#define BOARD_XTAL0_NAME "XTAL0"    /*!< Identifier name */

/* EXTAL32 (coord M6), Y3[2] */
#define BOARD_EXTAL32K_PERIPHERAL RTC   /*!< Device name: RTC */
#define BOARD_EXTAL32K_SIGNAL EXTAL32   /*!< RTC signal: EXTAL32 */
#define BOARD_EXTAL32K_PIN_NAME EXTAL32 /*!< Pin name */
#define BOARD_EXTAL32K_LABEL "Y3[2]"    /*!< Label */
#define BOARD_EXTAL32K_NAME "EXTAL32K"  /*!< Identifier name */

/* XTAL32 (coord M7), Y3[1] */
#define BOARD_XTAL32K_PERIPHERAL RTC  /*!< Device name: RTC */
#define BOARD_XTAL32K_SIGNAL XTAL32   /*!< RTC signal: XTAL32 */
#define BOARD_XTAL32K_PIN_NAME XTAL32 /*!< Pin name */
#define BOARD_XTAL32K_LABEL "Y3[1]"   /*!< Label */
#define BOARD_XTAL32K_NAME "XTAL32K"  /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitOSCs(void);

/* PORTC11 (coord B7), J2[18]/U20[C9]/I2C1_SDA/DA7212_SDA */
#define BOARD_INITVL6180_I2C1_SDA_PERIPHERAL I2C1   /*!< Device name: I2C1 */
#define BOARD_INITVL6180_I2C1_SDA_SIGNAL SDA        /*!< I2C1 signal: SDA */
#define BOARD_INITVL6180_I2C1_SDA_PIN_NAME I2C1_SDA /*!< Pin name */
#define BOARD_INITVL6180_I2C1_SDA_LABEL "J2[18]/U20[C9]/I2C1_SDA/DA7212_SDA" /*!< Label */
#define BOARD_INITVL6180_I2C1_SDA_NAME "I2C1_SDA"                            /*!< Identifier name */

/* PORTC10 (coord C7), J2[20]/U20[D8]/I2C1_SCL/DA7212_CLK */
#define BOARD_INITVL6180_I2C1_SCL_PERIPHERAL I2C1   /*!< Device name: I2C1 */
#define BOARD_INITVL6180_I2C1_SCL_SIGNAL SCL        /*!< I2C1 signal: SCL */
#define BOARD_INITVL6180_I2C1_SCL_PIN_NAME I2C1_SCL /*!< Pin name */
#define BOARD_INITVL6180_I2C1_SCL_LABEL "J2[20]/U20[D8]/I2C1_SCL/DA7212_CLK" /*!< Label */
#define BOARD_INITVL6180_I2C1_SCL_NAME "I2C1_SCL"                            /*!< Identifier name */

/* PORTD1 (coord D4), J2[12]/SPI0_SCK/FB_CS0_B */
#define BOARD_INITVL6180_I2C1_CS_GPIO GPIOD                         /*!< GPIO device name: GPIOD */
#define BOARD_INITVL6180_I2C1_CS_PORT PORTD                         /*!< PORT device name: PORTD */
#define BOARD_INITVL6180_I2C1_CS_GPIO_PIN 1U                        /*!< PORTD pin index: 1 */
#define BOARD_INITVL6180_I2C1_CS_PIN_NAME PTD1                      /*!< Pin name */
#define BOARD_INITVL6180_I2C1_CS_LABEL "J2[12]/SPI0_SCK/FB_CS0_B"   /*!< Label */
#define BOARD_INITVL6180_I2C1_CS_NAME "I2C1_CS"                     /*!< Identifier name */
#define BOARD_INITVL6180_I2C1_CS_DIRECTION kPIN_MUX_DirectionOutput /*!< Direction */

/* PORTD3 (coord B4), J2[10]/SPI0_SIN/FB_AD3 */
#define BOARD_INITVL6180_TOF_RDY_GPIO GPIOD                        /*!< GPIO device name: GPIOD */
#define BOARD_INITVL6180_TOF_RDY_PORT PORTD                        /*!< PORT device name: PORTD */
#define BOARD_INITVL6180_TOF_RDY_GPIO_PIN 3U                       /*!< PORTD pin index: 3 */
#define BOARD_INITVL6180_TOF_RDY_PIN_NAME PTD3                     /*!< Pin name */
#define BOARD_INITVL6180_TOF_RDY_LABEL "J2[10]/SPI0_SIN/FB_AD3"    /*!< Label */
#define BOARD_INITVL6180_TOF_RDY_NAME "TOF_RDY"                    /*!< Identifier name */
#define BOARD_INITVL6180_TOF_RDY_DIRECTION kPIN_MUX_DirectionInput /*!< Direction */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitVL6180(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
