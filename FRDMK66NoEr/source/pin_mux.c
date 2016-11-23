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

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
PinsProfile:
- !!product 'Pins v2.0'
- !!processor 'MK66FN2M0xxx18'
- !!package 'MK66FN2M0VMD18'
- !!mcu_data 'ksdk2_0'
- !!processor_version '1.0.1'
- !!board 'FRDM-K66F'
- pin_labels:
  - {pin_num: B4, pin_signal: PTD3/SPI0_SIN/UART2_TX/FTM3_CH3/FB_AD3/SDRAM_A11/I2C0_SDA, label:
'J2[10]/SPI0_SIN/FB_AD3', identifier: TOF_RDY}
  - {pin_num: C4, pin_signal: PTD2/LLWU_P13/SPI0_SOUT/UART2_RX/FTM3_CH2/FB_AD4/SDRAM_A12/I2C0_SCL,
label: 'J2[8]/SPI0_SOUT/FB_AD4', identifier: TOF_INT}
  - {pin_num: D4, pin_signal: ADC0_SE5b/PTD1/SPI0_SCK/UART2_CTS_b/FTM3_CH1/FB_CS0_b, label:
'J2[12]/SPI0_SCK/FB_CS0_B', identifier: I2C1_CS}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

#define PCR_PS_DOWN                                                                                \
    0x00u /*!< Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the \
             corresponding PE field is set. */
#define PIN1_IDX 1u                    /*!< Pin number for pin 1 in a port */
#define PIN16_IDX 16u                  /*!< Pin number for pin 16 in a port */
#define PIN17_IDX 17u                  /*!< Pin number for pin 17 in a port */
#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!< UART 0 transmit data source select: UART0_TX pin */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitPins:
- options: {prefix: BOARD_, coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: E10, peripheral: UART0, signal: RX, pin_signal:
TSI0_CH9/PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/SDRAM_D17/EWM_IN/TPM_CLKIN0, pull_select: down}
  - {pin_num: E9, peripheral: UART0, signal: TX, pin_signal:
TSI0_CH10/PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/SDRAM_D16/EWM_OUT_b/TPM_CLKIN1, pull_select:
down}
  - {pin_num: J3, peripheral: ADC0, signal: 'SE, 16', pin_signal: ADC0_SE16/CMP1_IN2/ADC0_SE21}
  - {pin_num: J6, peripheral: GPIOA, signal: 'GPIO, 1', pin_signal:
TSI0_CH2/PTA1/UART0_RX/FTM0_CH6/I2C3_SDA/LPUART0_RX/JTAG_TDI/EZP_DI, direction: OUTPUT, pull_select:
no_init}
  - {pin_num: M1, peripheral: ADC1, signal: 'DP, 0', pin_signal: ADC1_DP0/ADC0_DP3}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void)
{
    CLOCK_EnableClock(kCLOCK_PortA); /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB); /* Port B Clock Gate Control: Clock enabled */

    PORT_SetPinMux(PORTA, PIN1_IDX, kPORT_MuxAsGpio); /* PORTA1 (pin J6) is configured as PTA1 */
    PORT_SetPinMux(PORTB, PIN16_IDX,
                   kPORT_MuxAlt3); /* PORTB16 (pin E10) is configured as UART0_RX */
    PORTB->PCR[16] =
        ((PORTB->PCR[16] &
          (~(PORT_PCR_PS_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_DOWN) /* Pull Select: Internal pulldown resistor is enabled on the
                                       corresponding pin, if the corresponding PE field is set. */
         );
    PORT_SetPinMux(PORTB, PIN17_IDX,
                   kPORT_MuxAlt3); /* PORTB17 (pin E9) is configured as UART0_TX */
    PORTB->PCR[17] =
        ((PORTB->PCR[17] &
          (~(PORT_PCR_PS_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_DOWN) /* Pull Select: Internal pulldown resistor is enabled on the
                                       corresponding pin, if the corresponding PE field is set. */
         );
    SIM->SOPT5 =
        ((SIM->SOPT5 & (~(SIM_SOPT5_UART0TXSRC_MASK))) /* Mask bits to zero which are setting */
         | SIM_SOPT5_UART0TXSRC(
               SOPT5_UART0TXSRC_UART_TX) /* UART 0 transmit data source select: UART0_TX pin */
         );
}

#define PCR_PE_ENABLED                                                                           \
    0x01u /*!< Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding \
             pin, if the pin is configured as a digital input. */
#define PCR_PS_UP                                                                                \
    0x01u /*!< Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the \
             corresponding PE field is set. */
#define PIN10_IDX 10u /*!< Pin number for pin 10 in a port */
#define PIN11_IDX 11u /*!< Pin number for pin 11 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitBUTTONs:
- options: {prefix: BOARD_, coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: B2, peripheral: GPIOD, signal: 'GPIO, 11', pin_signal:
PTD11/LLWU_P25/SPI2_PCS0/SDHC0_CLKIN/LPUART0_CTS_b/FB_A19, direction: INPUT, pull_select: up,
    pull_enable: enable}
  - {pin_num: M9, peripheral: GPIOA, signal: 'GPIO, 10', pin_signal:
PTA10/LLWU_P22/FTM2_CH0/MII0_RXD2/FTM2_QD_PHA/TPM2_CH0/TRACE_D0, direction: INPUT, pull_select: up,
    pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitBUTTONs
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitBUTTONs(void)
{
    CLOCK_EnableClock(kCLOCK_PortA); /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD); /* Port D Clock Gate Control: Clock enabled */

    PORT_SetPinMux(PORTA, PIN10_IDX, kPORT_MuxAsGpio); /* PORTA10 (pin M9) is configured as PTA10 */
    PORTA->PCR[10] =
        ((PORTA->PCR[10] & (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK |
                              PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the
                                     corresponding pin, if the corresponding PE field is set. */
         | PORT_PCR_PE(
               PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on
                                  the corresponding pin, if the pin is configured as a digital
                                  input. */
         );
    PORT_SetPinMux(PORTD, PIN11_IDX, kPORT_MuxAsGpio); /* PORTD11 (pin B2) is configured as PTD11 */
    PORTD->PCR[11] =
        ((PORTD->PCR[11] & (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK |
                              PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the
                                     corresponding pin, if the corresponding PE field is set. */
         | PORT_PCR_PE(
               PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on
                                  the corresponding pin, if the pin is configured as a digital
                                  input. */
         );
}

#define PIN6_IDX 6u   /*!< Pin number for pin 6 in a port */
#define PIN9_IDX 9u   /*!< Pin number for pin 9 in a port */
#define PIN11_IDX 11u /*!< Pin number for pin 11 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitLEDs:
- options: {prefix: BOARD_, coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: L9, peripheral: GPIOA, signal: 'GPIO, 11', pin_signal:
PTA11/LLWU_P23/FTM2_CH1/MII0_RXCLK/I2C2_SDA/FTM2_QD_PHB/TPM2_CH1, direction: OUTPUT, slew_rate:
fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: E1, peripheral: GPIOE, signal: 'GPIO, 6', pin_signal:
PTE6/LLWU_P16/SPI1_PCS3/UART3_CTS_b/I2S0_MCLK/FTM3_CH1/USB0_SOF_OUT, direction: OUTPUT, slew_rate:
fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: D7, peripheral: GPIOC, signal: 'GPIO, 9', pin_signal:
ADC1_SE5b/CMP0_IN3/PTC9/FTM3_CH5/I2S0_RX_BCLK/FB_AD6/SDRAM_A14/FTM2_FLT0, direction: OUTPUT,
slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitLEDs
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitLEDs(void)
{
    CLOCK_EnableClock(kCLOCK_PortA); /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC); /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE); /* Port E Clock Gate Control: Clock enabled */

    const port_pin_config_t porta11_pinL9_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAsGpio,            /* Pin is configured as PTA11 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTA, PIN11_IDX,
                      &porta11_pinL9_config); /* PORTA11 (pin L9) is configured as PTA11 */
    const port_pin_config_t portc9_pinD7_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAsGpio,            /* Pin is configured as PTC9 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTC, PIN9_IDX,
                      &portc9_pinD7_config); /* PORTC9 (pin D7) is configured as PTC9 */
    const port_pin_config_t porte6_pinE1_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAsGpio,            /* Pin is configured as PTE6 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTE, PIN6_IDX,
                      &porte6_pinE1_config); /* PORTE6 (pin E1) is configured as PTE6 */
}

#define PIN8_IDX 8u                  /*!< Pin number for pin 8 in a port */
#define PIN9_IDX 9u                  /*!< Pin number for pin 9 in a port */
#define PIN13_IDX 13u                /*!< Pin number for pin 13 in a port */
#define PIN17_IDX 17u                /*!< Pin number for pin 17 in a port */
#define PORT_DFER_DFE_8_MASK 0x0100u /*!< Digital Filter Enable Mask for item 8. */
#define PORT_DFER_DFE_9_MASK 0x0200u /*!< Digital Filter Enable Mask for item 9. */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitACCEL_I2C:
- options: {prefix: BOARD_, coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: C9, peripheral: I2C0, signal: SCL, pin_signal:
PTD8/LLWU_P24/I2C0_SCL/LPUART0_RX/FB_A16, identifier: ACCEL_SCL, slew_rate: fast, open_drain:
enable,
    pull_select: down, pull_enable: disable, digital_filter: disable}
  - {pin_num: B9, peripheral: I2C0, signal: SDA, pin_signal: PTD9/I2C0_SDA/LPUART0_TX/FB_A17,
identifier: ACCEL_SDA, slew_rate: fast, open_drain: enable, pull_select: down,
    pull_enable: disable, digital_filter: disable}
  - {pin_num: D5, peripheral: GPIOC, signal: 'GPIO, 17', pin_signal:
PTC17/CAN1_TX/UART3_TX/ENET0_1588_TMR1/FB_CS4_b/FB_TSIZ0/FB_BE31_24_BLS7_0_b/SDRAM_DQM3, direction:
INPUT,
    slew_rate: fast, open_drain: disable, pull_select: up, pull_enable: enable}
  - {pin_num: D6, peripheral: GPIOC, signal: 'GPIO, 13', pin_signal:
PTC13/UART4_CTS_b/FTM_CLKIN1/FB_AD26/SDRAM_D26/TPM_CLKIN1, direction: INPUT, slew_rate: fast,
    open_drain: disable, pull_select: up, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitACCEL_I2C
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitACCEL_I2C(void)
{
    CLOCK_EnableClock(kCLOCK_PortC); /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD); /* Port D Clock Gate Control: Clock enabled */

    const port_pin_config_t portc13_pinD6_config = {
        kPORT_PullUp,               /* Internal pull-up resistor is enabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAsGpio,            /* Pin is configured as PTC13 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTC, PIN13_IDX,
                      &portc13_pinD6_config); /* PORTC13 (pin D6) is configured as PTC13 */
    const port_pin_config_t portc17_pinD5_config = {
        kPORT_PullUp,               /* Internal pull-up resistor is enabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAsGpio,            /* Pin is configured as PTC17 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTC, PIN17_IDX,
                      &portc17_pinD5_config);         /* PORTC17 (pin D5) is configured as PTC17 */
    PORT_EnablePinsDigitalFilter(                     /* Configure digital filter */
                                 PORTD,               /* Digital filter is configured on port D */
                                 PORT_DFER_DFE_8_MASK /* Digital filter is configured for PORTD0 */
                                     | PORT_DFER_DFE_9_MASK, /* Digital filter is configured for
                                                                PORTD1 */
                                 false                       /* Disable digital filter */
                                 );
    const port_pin_config_t portd8_pinC9_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainEnable,      /* Open drain is enabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt2,              /* Pin is configured as I2C0_SCL */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTD, PIN8_IDX,
                      &portd8_pinC9_config); /* PORTD8 (pin C9) is configured as I2C0_SCL */
    const port_pin_config_t portd9_pinB9_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainEnable,      /* Open drain is enabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt2,              /* Pin is configured as I2C0_SDA */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTD, PIN9_IDX,
                      &portd9_pinB9_config); /* PORTD9 (pin B9) is configured as I2C0_SDA */
}

#define PIN8_IDX 8u                  /*!< Pin number for pin 8 in a port */
#define PIN9_IDX 9u                  /*!< Pin number for pin 9 in a port */
#define PIN28_IDX 28u                /*!< Pin number for pin 28 in a port */
#define PIN29_IDX 29u                /*!< Pin number for pin 29 in a port */
#define PORT_DFER_DFE_8_MASK 0x0100u /*!< Digital Filter Enable Mask for item 8. */
#define PORT_DFER_DFE_9_MASK 0x0200u /*!< Digital Filter Enable Mask for item 9. */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitGYRO_I2C:
- options: {prefix: BOARD_, coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: B9, peripheral: I2C0, signal: SDA, pin_signal: PTD9/I2C0_SDA/LPUART0_TX/FB_A17,
identifier: GYRO_SDA, slew_rate: fast, open_drain: enable, pull_select: down,
    pull_enable: disable, digital_filter: disable}
  - {pin_num: C9, peripheral: I2C0, signal: SCL, pin_signal:
PTD8/LLWU_P24/I2C0_SCL/LPUART0_RX/FB_A16, identifier: GYRO_SCL, slew_rate: fast, open_drain: enable,
    pull_select: down, pull_enable: disable, digital_filter: disable}
  - {pin_num: H11, peripheral: GPIOA, signal: 'GPIO, 29', pin_signal: PTA29/MII0_COL/FB_A24,
direction: INPUT, slew_rate: fast, open_drain: enable, pull_select: up,
    pull_enable: enable}
  - {pin_num: H12, peripheral: GPIOA, signal: 'GPIO, 28', pin_signal: PTA28/MII0_TXER/FB_A25,
direction: INPUT, slew_rate: fast, open_drain: enable, pull_select: up,
    pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitGYRO_I2C
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitGYRO_I2C(void)
{
    CLOCK_EnableClock(kCLOCK_PortA); /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD); /* Port D Clock Gate Control: Clock enabled */

    const port_pin_config_t porta28_pinH12_config = {
        kPORT_PullUp,               /* Internal pull-up resistor is enabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainEnable,      /* Open drain is enabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAsGpio,            /* Pin is configured as PTA28 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTA, PIN28_IDX,
                      &porta28_pinH12_config); /* PORTA28 (pin H12) is configured as PTA28 */
    const port_pin_config_t porta29_pinH11_config = {
        kPORT_PullUp,               /* Internal pull-up resistor is enabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainEnable,      /* Open drain is enabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAsGpio,            /* Pin is configured as PTA29 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTA, PIN29_IDX,
                      &porta29_pinH11_config);        /* PORTA29 (pin H11) is configured as PTA29 */
    PORT_EnablePinsDigitalFilter(                     /* Configure digital filter */
                                 PORTD,               /* Digital filter is configured on port D */
                                 PORT_DFER_DFE_8_MASK /* Digital filter is configured for PORTD0 */
                                     | PORT_DFER_DFE_9_MASK, /* Digital filter is configured for
                                                                PORTD1 */
                                 false                       /* Disable digital filter */
                                 );
    const port_pin_config_t portd8_pinC9_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainEnable,      /* Open drain is enabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt2,              /* Pin is configured as I2C0_SCL */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTD, PIN8_IDX,
                      &portd8_pinC9_config); /* PORTD8 (pin C9) is configured as I2C0_SCL */
    const port_pin_config_t portd9_pinB9_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainEnable,      /* Open drain is enabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt2,              /* Pin is configured as I2C0_SDA */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTD, PIN9_IDX,
                      &portd9_pinB9_config); /* PORTD9 (pin B9) is configured as I2C0_SDA */
}

#define PIN6_IDX 6u                    /*!< Pin number for pin 6 in a port */
#define PIN14_IDX 14u                  /*!< Pin number for pin 14 in a port */
#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!< UART 0 transmit data source select: UART0_TX pin */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitDEBUG_UART:
- options: {prefix: BOARD_, coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: L10, peripheral: UART0, signal: TX, pin_signal:
PTA14/SPI0_PCS0/UART0_TX/RMII0_CRS_DV/MII0_RXDV/I2C2_SCL/I2S0_RX_BCLK/I2S0_TXD1, identifier: ''}
  - {pin_num: A2, peripheral: UART0, signal: RX, pin_signal:
ADC0_SE7b/PTD6/LLWU_P15/SPI0_PCS3/UART0_RX/FTM0_CH6/FB_AD0/FTM0_FLT0/SPI1_SOUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitDEBUG_UART
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitDEBUG_UART(void)
{
    CLOCK_EnableClock(kCLOCK_PortA); /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD); /* Port D Clock Gate Control: Clock enabled */

    PORT_SetPinMux(PORTA, PIN14_IDX,
                   kPORT_MuxAlt3); /* PORTA14 (pin L10) is configured as UART0_TX */
    PORT_SetPinMux(PORTD, PIN6_IDX, kPORT_MuxAlt3); /* PORTD6 (pin A2) is configured as UART0_RX */
    SIM->SOPT5 =
        ((SIM->SOPT5 & (~(SIM_SOPT5_UART0TXSRC_MASK))) /* Mask bits to zero which are setting */
         | SIM_SOPT5_UART0TXSRC(
               SOPT5_UART0TXSRC_UART_TX) /* UART 0 transmit data source select: UART0_TX pin */
         );
}

#define PIN0_IDX 0u                   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX 1u                   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX 2u                   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX 3u                   /*!< Pin number for pin 3 in a port */
#define PIN4_IDX 4u                   /*!< Pin number for pin 4 in a port */
#define PIN5_IDX 5u                   /*!< Pin number for pin 5 in a port */
#define PIN10_IDX 10u                 /*!< Pin number for pin 10 in a port */
#define PORT_DFER_DFE_10_MASK 0x0400u /*!< Digital Filter Enable Mask for item 10. */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitSDHC0:
- options: {prefix: BOARD_, coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: E4, peripheral: SDHC, signal: CMD, pin_signal:
ADC1_SE7a/PTE3/SPI1_SIN/UART1_RTS_b/SDHC0_CMD/TRACE_D1/SPI1_SOUT, slew_rate: fast, open_drain:
disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: D2, peripheral: SDHC, signal: 'DATA, 0', pin_signal:
ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/SDHC0_D0/TRACE_D3/I2C1_SCL/SPI1_SIN, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: D3, peripheral: SDHC, signal: 'DATA, 1', pin_signal:
ADC1_SE4a/PTE0/SPI1_PCS1/UART1_TX/SDHC0_D1/TRACE_CLKOUT/I2C1_SDA/RTC_CLKOUT, slew_rate: fast,
open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: E2, peripheral: SDHC, signal: 'DATA, 2', pin_signal:
PTE5/SPI1_PCS2/UART3_RX/SDHC0_D2/FTM3_CH0, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
  - {pin_num: E3, peripheral: SDHC, signal: 'DATA, 3', pin_signal:
PTE4/LLWU_P2/SPI1_PCS0/UART3_TX/SDHC0_D3/TRACE_D0, slew_rate: fast, open_drain: disable,
pull_select: down,
    pull_enable: disable}
  - {pin_num: D1, peripheral: SDHC, signal: DCLK, pin_signal:
ADC1_SE6a/PTE2/LLWU_P1/SPI1_SCK/UART1_CTS_b/SDHC0_DCLK/TRACE_D2, slew_rate: fast, open_drain:
disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: B3, peripheral: GPIOD, signal: 'GPIO, 10', pin_signal: PTD10/LPUART0_RTS_b/FB_A18,
direction: INPUT, slew_rate: fast, open_drain: disable, pull_select: up,
    pull_enable: enable, digital_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitSDHC0
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitSDHC0(void)
{
    CLOCK_EnableClock(kCLOCK_PortD); /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE); /* Port E Clock Gate Control: Clock enabled */

    PORT_EnablePinsDigitalFilter(                       /* Configure digital filter */
                                 PORTD,                 /* Digital filter is configured on port D */
                                 PORT_DFER_DFE_10_MASK, /* Digital filter is configured for PORTD0
                                                           */
                                 false                  /* Disable digital filter */
                                 );
    const port_pin_config_t portd10_pinB3_config = {
        kPORT_PullUp,               /* Internal pull-up resistor is enabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAsGpio,            /* Pin is configured as PTD10 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTD, PIN10_IDX,
                      &portd10_pinB3_config); /* PORTD10 (pin B3) is configured as PTD10 */
    const port_pin_config_t porte0_pinD3_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt4,              /* Pin is configured as SDHC0_D1 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTE, PIN0_IDX,
                      &porte0_pinD3_config); /* PORTE0 (pin D3) is configured as SDHC0_D1 */
    const port_pin_config_t porte1_pinD2_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt4,              /* Pin is configured as SDHC0_D0 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTE, PIN1_IDX,
                      &porte1_pinD2_config); /* PORTE1 (pin D2) is configured as SDHC0_D0 */
    const port_pin_config_t porte2_pinD1_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt4,              /* Pin is configured as SDHC0_DCLK */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTE, PIN2_IDX,
                      &porte2_pinD1_config); /* PORTE2 (pin D1) is configured as SDHC0_DCLK */
    const port_pin_config_t porte3_pinE4_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt4,              /* Pin is configured as SDHC0_CMD */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTE, PIN3_IDX,
                      &porte3_pinE4_config); /* PORTE3 (pin E4) is configured as SDHC0_CMD */
    const port_pin_config_t porte4_pinE3_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt4,              /* Pin is configured as SDHC0_D3 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTE, PIN4_IDX,
                      &porte4_pinE3_config); /* PORTE4 (pin E3) is configured as SDHC0_D3 */
    const port_pin_config_t porte5_pinE2_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt4,              /* Pin is configured as SDHC0_D2 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTE, PIN5_IDX,
                      &porte5_pinE2_config); /* PORTE5 (pin E2) is configured as SDHC0_D2 */
}

#define PIN0_IDX 0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX 1u   /*!< Pin number for pin 1 in a port */
#define PIN5_IDX 5u   /*!< Pin number for pin 5 in a port */
#define PIN12_IDX 12u /*!< Pin number for pin 12 in a port */
#define PIN13_IDX 13u /*!< Pin number for pin 13 in a port */
#define PIN14_IDX 14u /*!< Pin number for pin 14 in a port */
#define PIN15_IDX 15u /*!< Pin number for pin 15 in a port */
#define PIN16_IDX 16u /*!< Pin number for pin 16 in a port */
#define PIN17_IDX 17u /*!< Pin number for pin 17 in a port */
#define PIN26_IDX 26u /*!< Pin number for pin 26 in a port */
#define SOPT2_RMIISRC_ENET \
    0x01u /*!< RMII clock source select: External bypass clock (ENET_1588_CLKIN). */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitENET:
- options: {prefix: BOARD_, coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: K4, peripheral: ENET, signal: RMII_CLKIN, pin_signal:
PTE26/ENET_1588_CLKIN/UART4_CTS_b/RTC_CLKOUT/USB0_CLKIN, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: L10, peripheral: ENET, signal: RMII_CRS_DV, pin_signal:
PTA14/SPI0_PCS0/UART0_TX/RMII0_CRS_DV/MII0_RXDV/I2C2_SCL/I2S0_RX_BCLK/I2S0_TXD1, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: H9, peripheral: ENET, signal: RMII_MDC, pin_signal:
ADC0_SE9/ADC1_SE9/TSI0_CH6/PTB1/I2C0_SDA/FTM1_CH1/RMII0_MDC/MII0_MDC/SDRAM_RAS_b/FTM1_QD_PHB/TPM1_CH1,
    slew_rate: fast, open_drain: disable, drive_strength: low, pull_select: down, pull_enable:
disable}
  - {pin_num: H10, peripheral: ENET, signal: RMII_MDIO, pin_signal:
ADC0_SE8/ADC1_SE8/TSI0_CH0/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/RMII0_MDIO/MII0_MDIO/SDRAM_CAS_b/FTM1_QD_PHA/TPM1_CH0,
    slew_rate: fast, open_drain: disable, drive_strength: low, pull_select: down, pull_enable:
disable}
  - {pin_num: J9, peripheral: ENET, signal: RMII_RXD0, pin_signal:
CMP2_IN1/PTA13/LLWU_P4/CAN0_RX/FTM1_CH1/RMII0_RXD0/MII0_RXD0/I2C2_SDA/I2S0_TX_FS/FTM1_QD_PHB/TPM1_CH1,
    slew_rate: fast, open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: K9, peripheral: ENET, signal: RMII_RXD1, pin_signal:
CMP2_IN0/PTA12/CAN0_TX/FTM1_CH0/RMII0_RXD1/MII0_RXD1/I2C2_SCL/I2S0_TXD0/FTM1_QD_PHA/TPM1_CH0,
slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: M8, peripheral: ENET, signal: RMII_RXER, pin_signal:
PTA5/USB0_CLKIN/FTM0_CH2/RMII0_RXER/MII0_RXER/CMP2_OUT/I2S0_TX_BCLK/JTAG_TRST_b, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: K10, peripheral: ENET, signal: RMII_TXD0, pin_signal:
CMP3_IN2/PTA16/SPI0_SOUT/UART0_CTS_b/UART0_COL_b/RMII0_TXD0/MII0_TXD0/I2S0_RX_FS/I2S0_RXD1,
slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: K11, peripheral: ENET, signal: RMII_TXD1, pin_signal:
ADC1_SE17/PTA17/SPI0_SIN/UART0_RTS_b/RMII0_TXD1/MII0_TXD1/I2S0_MCLK, slew_rate: fast, open_drain:
disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: L11, peripheral: ENET, signal: RMII_TXEN, pin_signal:
CMP3_IN1/PTA15/SPI0_SCK/UART0_RX/RMII0_TXEN/MII0_TXEN/I2S0_RXD0, slew_rate: fast, open_drain:
disable,
    pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitENET
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitENET(void)
{
    CLOCK_EnableClock(kCLOCK_PortA); /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB); /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE); /* Port E Clock Gate Control: Clock enabled */

    const port_pin_config_t porta12_pinK9_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt4,              /* Pin is configured as RMII0_RXD1 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTA, PIN12_IDX,
                      &porta12_pinK9_config); /* PORTA12 (pin K9) is configured as RMII0_RXD1 */
    const port_pin_config_t porta13_pinJ9_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt4,              /* Pin is configured as RMII0_RXD0 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTA, PIN13_IDX,
                      &porta13_pinJ9_config); /* PORTA13 (pin J9) is configured as RMII0_RXD0 */
    const port_pin_config_t porta14_pinL10_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt4,              /* Pin is configured as RMII0_CRS_DV */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTA, PIN14_IDX,
                      &porta14_pinL10_config); /* PORTA14 (pin L10) is configured as RMII0_CRS_DV */
    const port_pin_config_t porta15_pinL11_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt4,              /* Pin is configured as RMII0_TXEN */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTA, PIN15_IDX,
                      &porta15_pinL11_config); /* PORTA15 (pin L11) is configured as RMII0_TXEN */
    const port_pin_config_t porta16_pinK10_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt4,              /* Pin is configured as RMII0_TXD0 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTA, PIN16_IDX,
                      &porta16_pinK10_config); /* PORTA16 (pin K10) is configured as RMII0_TXD0 */
    const port_pin_config_t porta17_pinK11_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt4,              /* Pin is configured as RMII0_TXD1 */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTA, PIN17_IDX,
                      &porta17_pinK11_config); /* PORTA17 (pin K11) is configured as RMII0_TXD1 */
    const port_pin_config_t porta5_pinM8_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt4,              /* Pin is configured as RMII0_RXER */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTA, PIN5_IDX,
                      &porta5_pinM8_config); /* PORTA5 (pin M8) is configured as RMII0_RXER */
    const port_pin_config_t portb0_pinH10_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt4,              /* Pin is configured as RMII0_MDIO */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTB, PIN0_IDX,
                      &portb0_pinH10_config); /* PORTB0 (pin H10) is configured as RMII0_MDIO */
    const port_pin_config_t portb1_pinH9_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt4,              /* Pin is configured as RMII0_MDC */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTB, PIN1_IDX,
                      &portb1_pinH9_config); /* PORTB1 (pin H9) is configured as RMII0_MDC */
    const port_pin_config_t porte26_pinK4_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt2,              /* Pin is configured as ENET_1588_CLKIN */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(
        PORTE, PIN26_IDX,
        &porte26_pinK4_config); /* PORTE26 (pin K4) is configured as ENET_1588_CLKIN */
    SIM->SOPT2 =
        ((SIM->SOPT2 & (~(SIM_SOPT2_RMIISRC_MASK))) /* Mask bits to zero which are setting */
         |
         SIM_SOPT2_RMIISRC(SOPT2_RMIISRC_ENET) /* RMII clock source select: External bypass clock
                                                  (ENET_1588_CLKIN). */
         );
}

#define PIN10_IDX 10u /*!< Pin number for pin 10 in a port */
                      /*
                       * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
                      BOARD_InitUSB:
                      - options: {prefix: BOARD_, coreID: singlecore, enableClock: 'true'}
                      - pin_list:
                        - {pin_num: K1, peripheral: USBHSDCD, signal: DM, pin_signal: USB1_DM/LLWU_P31, identifier:
                      K66_MICRO_USB_DN_DCD}
                        - {pin_num: J1, peripheral: USBHSDCD, signal: DP, pin_signal: USB1_DP/LLWU_P30, identifier:
                      K66_MICRO_USB_DP_DCD}
                        - {pin_num: K1, peripheral: USBPHY, signal: DM, pin_signal: USB1_DM/LLWU_P31, identifier:
                      K66_MICRO_USB_DN_PHY}
                        - {pin_num: J1, peripheral: USBPHY, signal: DP, pin_signal: USB1_DP/LLWU_P30, identifier:
                      K66_MICRO_USB_DP_PHY}
                        - {pin_num: F1, peripheral: USBPHY, signal: ID, pin_signal:
                      PTE10/LLWU_P18/I2C3_SDA/I2S0_TXD0/LPUART0_CTS_b/FTM3_CH5/USB1_ID, slew_rate: fast, open_drain:
                      disable,
                          pull_select: down, pull_enable: disable}
                        - {pin_num: L1, peripheral: USBPHY, signal: VBUS, pin_signal: USB1_VBUS/LLWU_P29}
                       * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
                       */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitUSB
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitUSB(void)
{
    CLOCK_EnableClock(kCLOCK_PortE); /* Port E Clock Gate Control: Clock enabled */

    const port_pin_config_t porte10_pinF1_config = {
        kPORT_PullDisable,          /* Internal pull-up/down resistor is disabled */
        kPORT_FastSlewRate,         /* Fast slew rate is configured */
        kPORT_PassiveFilterDisable, /* Passive filter is disabled */
        kPORT_OpenDrainDisable,     /* Open drain is disabled */
        kPORT_LowDriveStrength,     /* Low drive strength is configured */
        kPORT_MuxAlt7,              /* Pin is configured as USB1_ID */
        kPORT_UnlockRegister        /* Pin Control Register fields [15:0] are not locked */
    };
    PORT_SetPinConfig(PORTE, PIN10_IDX,
                      &porte10_pinF1_config); /* PORTE10 (pin F1) is configured as USB1_ID */
}

#define PIN18_IDX 18u /*!< Pin number for pin 18 in a port */
#define PIN19_IDX 19u /*!< Pin number for pin 19 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitOSCs:
- options: {prefix: BOARD_, coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: M12, peripheral: OSC, signal: EXTAL0, pin_signal:
EXTAL0/PTA18/FTM0_FLT2/FTM_CLKIN0/TPM_CLKIN0, slew_rate: no_init, open_drain: no_init, pull_select:
no_init,
    pull_enable: no_init}
  - {pin_num: M11, peripheral: OSC, signal: XTAL0, pin_signal:
XTAL0/PTA19/FTM1_FLT0/FTM_CLKIN1/LPTMR0_ALT1/TPM_CLKIN1, slew_rate: no_init, open_drain: no_init,
pull_select: no_init,
    pull_enable: no_init}
  - {pin_num: M6, peripheral: RTC, signal: EXTAL32, pin_signal: EXTAL32}
  - {pin_num: M7, peripheral: RTC, signal: XTAL32, pin_signal: XTAL32}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitOSCs
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitOSCs(void)
{
    CLOCK_EnableClock(kCLOCK_PortA); /* Port A Clock Gate Control: Clock enabled */

    PORT_SetPinMux(PORTA, PIN18_IDX,
                   kPORT_PinDisabledOrAnalog); /* PORTA18 (pin M12) is configured as EXTAL0 */
    PORT_SetPinMux(PORTA, PIN19_IDX,
                   kPORT_PinDisabledOrAnalog); /* PORTA19 (pin M11) is configured as XTAL0 */
}

#define PCR_ODE_ENABLED                                                                         \
    0x01u /*!< Open Drain Enable: Open drain output is enabled on the corresponding pin, if the \
             pin is configured as a digital output. */
#define PCR_PE_ENABLED                                                                           \
    0x01u /*!< Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding \
             pin, if the pin is configured as a digital input. */
#define PCR_PS_UP                                                                                \
    0x01u /*!< Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the \
             corresponding PE field is set. */
#define PIN1_IDX 1u   /*!< Pin number for pin 1 in a port */
#define PIN3_IDX 3u   /*!< Pin number for pin 3 in a port */
#define PIN10_IDX 10u /*!< Pin number for pin 10 in a port */
#define PIN11_IDX 11u /*!< Pin number for pin 11 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitVL6180:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: B7, peripheral: I2C1, signal: SDA, pin_signal:
ADC1_SE7b/PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/I2S0_RXD1/FB_RW_b, open_drain: enable, pull_select:
no_init,
    pull_enable: enable}
  - {pin_num: C7, peripheral: I2C1, signal: SCL, pin_signal:
ADC1_SE6b/PTC10/I2C1_SCL/FTM3_CH6/I2S0_RX_FS/FB_AD5/SDRAM_A13, open_drain: enable, pull_select:
no_init,
    pull_enable: enable}
  - {pin_num: D4, peripheral: GPIOD, signal: 'GPIO, 1', pin_signal:
ADC0_SE5b/PTD1/SPI0_SCK/UART2_CTS_b/FTM3_CH1/FB_CS0_b, direction: OUTPUT, pull_select: up}
  - {pin_num: B4, peripheral: GPIOD, signal: 'GPIO, 3', pin_signal:
PTD3/SPI0_SIN/UART2_TX/FTM3_CH3/FB_AD3/SDRAM_A11/I2C0_SDA, direction: INPUT, pull_select: up}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitVL6180
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitVL6180(void)
{
    CLOCK_EnableClock(kCLOCK_PortC); /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD); /* Port D Clock Gate Control: Clock enabled */

    PORT_SetPinMux(PORTC, PIN10_IDX,
                   kPORT_MuxAlt2); /* PORTC10 (pin C7) is configured as I2C1_SCL */
    PORTC->PCR[10] = ((PORTC->PCR[10] &
                       (~(PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK |
                          PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
                      |
                      PORT_PCR_PE(PCR_PE_ENABLED)     /* Pull Enable: Internal pullup or pulldown
                                                         resistor is enabled on the corresponding pin,
                                                         if the pin is configured as a digital input. */
                      | PORT_PCR_ODE(PCR_ODE_ENABLED) /* Open Drain Enable: Open drain output is
                                                         enabled on the corresponding pin, if the
                                                         pin is configured as a digital output. */
                      );
    PORT_SetPinMux(PORTC, PIN11_IDX,
                   kPORT_MuxAlt2); /* PORTC11 (pin B7) is configured as I2C1_SDA */
    PORTC->PCR[11] = ((PORTC->PCR[11] &
                       (~(PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK |
                          PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
                      |
                      PORT_PCR_PE(PCR_PE_ENABLED)     /* Pull Enable: Internal pullup or pulldown
                                                         resistor is enabled on the corresponding pin,
                                                         if the pin is configured as a digital input. */
                      | PORT_PCR_ODE(PCR_ODE_ENABLED) /* Open Drain Enable: Open drain output is
                                                         enabled on the corresponding pin, if the
                                                         pin is configured as a digital output. */
                      );
    PORT_SetPinMux(PORTD, PIN1_IDX, kPORT_MuxAsGpio); /* PORTD1 (pin D4) is configured as PTD1 */
    PORTD->PCR[1] =
        ((PORTD->PCR[1] &
          (~(PORT_PCR_PS_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the
                                     corresponding pin, if the corresponding PE field is set. */
         );
    PORT_SetPinMux(PORTD, PIN3_IDX, kPORT_MuxAsGpio); /* PORTD3 (pin B4) is configured as PTD3 */
    PORTD->PCR[3] =
        ((PORTD->PCR[3] &
          (~(PORT_PCR_PS_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the
                                     corresponding pin, if the corresponding PE field is set. */
         );
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
