/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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
- !!processor_version '0.1.25'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

#define PIN16_IDX 16u /*!< Pin number for pin 16 in a port */
#define PIN17_IDX 17u /*!< Pin number for pin 17 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: E10, peripheral: UART0, signal: RX, pin_signal:
TSI0_CH9/PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/SDRAM_D17/EWM_IN/TPM_CLKIN0}
  - {pin_num: E9, peripheral: SIM, signal: UART0_MOD_OUT, pin_signal:
TSI0_CH10/PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/SDRAM_D16/EWM_OUT_b/TPM_CLKIN1}
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
    CLOCK_EnableClock(kCLOCK_PortB); /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD); /* Port D Clock Gate Control: Clock enabled */

    PORT_SetPinMux(PORTB, PIN16_IDX, kPORT_MuxAlt3); /* PORTB16 (pin E10) is configured as UART0_RX */
    PORT_SetPinMux(PORTB, PIN17_IDX, kPORT_MuxAlt3); /* PORTB17 (pin E9) is configured as UART0_TX */
}

#define PCR_ODE_ENABLED                                                                                                \
    0x01u /*!< Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is configured as a \
             digital output. */
#define PCR_PE_ENABLED                                                                                              \
    0x01u /*!< Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is \
             configured as a digital input. */
#define PCR_PS_UP                                                                                                 \
    0x01u /*!< Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE \
             field is set. */
#define PIN8_IDX 8u /*!< Pin number for pin 2 in a port */
#define PIN9_IDX 9u /*!< Pin number for pin 3 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
I2C0_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: G12, peripheral: I2C0, signal: SCL, pin_signal:
ADC0_SE12/TSI0_CH7/PTB2/I2C0_SCL/UART0_RTS_b/ENET0_1588_TMR0/SDRAM_WE/FTM0_FLT3, open_drain: enable,
    pull_select: up, pull_enable: enable}
  - {pin_num: G11, peripheral: I2C0, signal: SDA, pin_signal:
ADC0_SE13/TSI0_CH8/PTB3/I2C0_SDA/UART0_CTS_b/UART0_COL_b/ENET0_1588_TMR1/SDRAM_CS0_b/FTM0_FLT0, open_drain: enable,
    pull_select: up, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C0_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void I2C0_InitPins(void)
{
    CLOCK_EnableClock(kCLOCK_PortD); /* Port B Clock Gate Control: Clock enabled */

    PORT_SetPinMux(PORTD, PIN8_IDX, kPORT_MuxAlt2); /* PORTB2 (pin G12) is configured as I2C0_SCL */
    PORTD->PCR[8] =
        ((PORTD->PCR[8] & (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK |
                             PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         |
         PORT_PCR_ODE(PCR_ODE_ENABLED) /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if
                                          the pin is configured as a digital output. */
         );
    PORT_SetPinMux(PORTD, PIN9_IDX, kPORT_MuxAlt2); /* PORTB3 (pin G11) is configured as I2C0_SDA */
    PORTD->PCR[9] =
        ((PORTD->PCR[9] & (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK |
                             PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         |
         PORT_PCR_ODE(PCR_ODE_ENABLED) /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if
                                          the pin is configured as a digital output. */
         );
}

#define PIN8_IDX 8u /*!< Pin number for pin 2 in a port */
#define PIN9_IDX 9u /*!< Pin number for pin 3 in a port */
                    /*
                     * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
                    I2C0_DeinitPins:
                    - options: {coreID: singlecore, enableClock: 'false'}
                    - pin_list:
                      - {pin_num: G12, peripheral: ADC0, signal: 'SE, 12', pin_signal:
                    ADC0_SE12/TSI0_CH7/PTB2/I2C0_SCL/UART0_RTS_b/ENET0_1588_TMR0/SDRAM_WE/FTM0_FLT3}
                      - {pin_num: G11, peripheral: ADC0, signal: 'SE, 13', pin_signal:
                    ADC0_SE13/TSI0_CH8/PTB3/I2C0_SDA/UART0_CTS_b/UART0_COL_b/ENET0_1588_TMR1/SDRAM_CS0_b/FTM0_FLT0}
                     * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
                     */

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C0_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void I2C0_DeinitPins(void)
{
    PORT_SetPinMux(PORTD, PIN8_IDX, kPORT_PinDisabledOrAnalog); /* PORTB2 (pin G12) is configured as ADC0_SE12 */
    PORT_SetPinMux(PORTD, PIN9_IDX, kPORT_PinDisabledOrAnalog); /* PORTB3 (pin G11) is configured as ADC0_SE13 */
}

#define PCR_ODE_ENABLED                                                                                                \
    0x01u /*!< Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is configured as a \
             digital output. */
#define PCR_PE_ENABLED                                                                                              \
    0x01u /*!< Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is \
             configured as a digital input. */
#define PCR_PS_UP                                                                                                 \
    0x01u /*!< Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE \
             field is set. */
#define PIN10_IDX 10u /*!< Pin number for pin 10 in a port */
#define PIN11_IDX 11u /*!< Pin number for pin 11 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
I2C1_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: C7, peripheral: I2C1, signal: SCL, pin_signal:
ADC1_SE6b/PTC10/I2C1_SCL/FTM3_CH6/I2S0_RX_FS/FB_AD5/SDRAM_A13, open_drain: enable, pull_select: up, pull_enable: enable}
  - {pin_num: B7, peripheral: I2C1, signal: SDA, pin_signal:
ADC1_SE7b/PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/I2S0_RXD1/FB_RW_b, open_drain: enable, pull_select: up, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C1_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void I2C1_InitPins(void)
{
    CLOCK_EnableClock(kCLOCK_PortC); /* Port C Clock Gate Control: Clock enabled */

    PORT_SetPinMux(PORTC, PIN10_IDX, kPORT_MuxAlt2); /* PORTC10 (pin C7) is configured as I2C1_SCL */
    PORTC->PCR[10] =
        ((PORTC->PCR[10] & (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK |
                              PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         |
         PORT_PCR_ODE(PCR_ODE_ENABLED) /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if
                                          the pin is configured as a digital output. */
         );
    PORT_SetPinMux(PORTC, PIN11_IDX, kPORT_MuxAlt2); /* PORTC11 (pin B7) is configured as I2C1_SDA */
    PORTC->PCR[11] =
        ((PORTC->PCR[11] & (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK |
                              PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         |
         PORT_PCR_ODE(PCR_ODE_ENABLED) /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if
                                          the pin is configured as a digital output. */
         );
}

#define PIN10_IDX 10u /*!< Pin number for pin 10 in a port */
#define PIN11_IDX 11u /*!< Pin number for pin 11 in a port */
                      /*
                       * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
                      I2C1_DeinitPins:
                      - options: {coreID: singlecore, enableClock: 'false'}
                      - pin_list:
                        - {pin_num: B7, peripheral: ADC1, signal: 'SE, 7b', pin_signal:
                      ADC1_SE7b/PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/I2S0_RXD1/FB_RW_b}
                        - {pin_num: C7, peripheral: ADC1, signal: 'SE, 6b', pin_signal:
                      ADC1_SE6b/PTC10/I2C1_SCL/FTM3_CH6/I2S0_RX_FS/FB_AD5/SDRAM_A13}
                       * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
                       */

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C1_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void I2C1_DeinitPins(void)
{
    PORT_SetPinMux(PORTC, PIN10_IDX, kPORT_PinDisabledOrAnalog); /* PORTC10 (pin C7) is configured as ADC1_SE6b */
    PORT_SetPinMux(PORTC, PIN11_IDX, kPORT_PinDisabledOrAnalog); /* PORTC11 (pin B7) is configured as ADC1_SE7b */
}

#define PCR_ODE_ENABLED                                                                                                \
    0x01u /*!< Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is configured as a \
             digital output. */
#define PCR_PE_ENABLED                                                                                              \
    0x01u /*!< Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is \
             configured as a digital input. */
#define PCR_PS_UP                                                                                                 \
    0x01u /*!< Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE \
             field is set. */
#define PIN12_IDX 12u /*!< Pin number for pin 12 in a port */
#define PIN13_IDX 13u /*!< Pin number for pin 13 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
I2C2_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: K9, peripheral: I2C2, signal: SCL, pin_signal:
CMP2_IN0/PTA12/CAN0_TX/FTM1_CH0/RMII0_RXD1/MII0_RXD1/I2C2_SCL/I2S0_TXD0/FTM1_QD_PHA/TPM1_CH0, open_drain: enable,
    pull_select: up, pull_enable: enable}
  - {pin_num: J9, peripheral: I2C2, signal: SDA, pin_signal:
CMP2_IN1/PTA13/LLWU_P4/CAN0_RX/FTM1_CH1/RMII0_RXD0/MII0_RXD0/I2C2_SDA/I2S0_TX_FS/FTM1_QD_PHB/TPM1_CH1,
    open_drain: enable, pull_select: up, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C2_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void I2C2_InitPins(void)
{
    CLOCK_EnableClock(kCLOCK_PortA); /* Port A Clock Gate Control: Clock enabled */

    PORT_SetPinMux(PORTA, PIN12_IDX, kPORT_MuxAlt5); /* PORTA12 (pin K9) is configured as I2C2_SCL */
    PORTA->PCR[12] =
        ((PORTA->PCR[12] & (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK |
                              PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         |
         PORT_PCR_ODE(PCR_ODE_ENABLED) /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if
                                          the pin is configured as a digital output. */
         );
    PORT_SetPinMux(PORTA, PIN13_IDX, kPORT_MuxAlt5); /* PORTA13 (pin J9) is configured as I2C2_SDA */
    PORTA->PCR[13] =
        ((PORTA->PCR[13] & (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK |
                              PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         |
         PORT_PCR_ODE(PCR_ODE_ENABLED) /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if
                                          the pin is configured as a digital output. */
         );
}

#define PIN12_IDX 12u /*!< Pin number for pin 12 in a port */
#define PIN13_IDX 13u /*!< Pin number for pin 13 in a port */
                      /*
                       * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
                      I2C2_DeinitPins:
                      - options: {coreID: singlecore, enableClock: 'true'}
                      - pin_list:
                        - {pin_num: K9, peripheral: CMP2, signal: 'IN, 0', pin_signal:
                      CMP2_IN0/PTA12/CAN0_TX/FTM1_CH0/RMII0_RXD1/MII0_RXD1/I2C2_SCL/I2S0_TXD0/FTM1_QD_PHA/TPM1_CH0}
                        - {pin_num: J9, peripheral: CMP2, signal: 'IN, 1', pin_signal:
                      CMP2_IN1/PTA13/LLWU_P4/CAN0_RX/FTM1_CH1/RMII0_RXD0/MII0_RXD0/I2C2_SDA/I2S0_TX_FS/FTM1_QD_PHB/TPM1_CH1}
                       * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
                       */

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C2_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void I2C2_DeinitPins(void)
{
    CLOCK_EnableClock(kCLOCK_PortA); /* Port A Clock Gate Control: Clock enabled */

    PORT_SetPinMux(PORTA, PIN12_IDX, kPORT_PinDisabledOrAnalog); /* PORTA12 (pin K9) is configured as CMP2_IN0 */
    PORT_SetPinMux(PORTA, PIN13_IDX, kPORT_PinDisabledOrAnalog); /* PORTA13 (pin J9) is configured as CMP2_IN1 */
}

#define PCR_ODE_ENABLED                                                                                                \
    0x01u /*!< Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is configured as a \
             digital output. */
#define PCR_PE_ENABLED                                                                                              \
    0x01u /*!< Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is \
             configured as a digital input. */
#define PCR_PS_UP                                                                                                 \
    0x01u /*!< Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE \
             field is set. */
#define PIN10_IDX 10u /*!< Pin number for pin 10 in a port */
#define PIN11_IDX 11u /*!< Pin number for pin 11 in a port */
                      /*
                       * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
                      I2C3_InitPins:
                      - options: {coreID: singlecore, enableClock: 'true'}
                      - pin_list:
                        - {pin_num: G4, peripheral: I2C3, signal: SCL, pin_signal: PTE11/I2C3_SCL/I2S0_TX_FS/LPUART0_RTS_b/FTM3_CH6,
                      open_drain: enable, pull_select: up, pull_enable: enable}
                        - {pin_num: F1, peripheral: I2C3, signal: SDA, pin_signal:
                      PTE10/LLWU_P18/I2C3_SDA/I2S0_TXD0/LPUART0_CTS_b/FTM3_CH5/USB1_ID, open_drain: enable, pull_select: up,
                          pull_enable: enable}
                       * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
                       */

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C3_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void I2C3_InitPins(void)
{
    CLOCK_EnableClock(kCLOCK_PortE); /* Port E Clock Gate Control: Clock enabled */

    PORT_SetPinMux(PORTE, PIN10_IDX, kPORT_MuxAlt2); /* PORTE10 (pin F1) is configured as I2C3_SDA */
    PORTE->PCR[10] =
        ((PORTE->PCR[10] & (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK |
                              PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         |
         PORT_PCR_ODE(PCR_ODE_ENABLED) /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if
                                          the pin is configured as a digital output. */
         );
    PORT_SetPinMux(PORTE, PIN11_IDX, kPORT_MuxAlt2); /* PORTE11 (pin G4) is configured as I2C3_SCL */
    PORTE->PCR[11] =
        ((PORTE->PCR[11] & (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK |
                              PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         |
         PORT_PCR_ODE(PCR_ODE_ENABLED) /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if
                                          the pin is configured as a digital output. */
         );
}

#define PIN10_IDX 10u /*!< Pin number for pin 10 in a port */
#define PIN11_IDX 11u /*!< Pin number for pin 11 in a port */
                      /*
                       * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
                      I2C3_DeinitPins:
                      - options: {coreID: singlecore, enableClock: 'false'}
                      - pin_list:
                        - {pin_num: F1, peripheral: n/a, signal: disabled, pin_signal:
                      PTE10/LLWU_P18/I2C3_SDA/I2S0_TXD0/LPUART0_CTS_b/FTM3_CH5/USB1_ID}
                        - {pin_num: G4, peripheral: n/a, signal: disabled, pin_signal: PTE11/I2C3_SCL/I2S0_TX_FS/LPUART0_RTS_b/FTM3_CH6}
                       * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
                       */

/*FUNCTION**********************************************************************
 *
 * Function Name : I2C3_DeinitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void I2C3_DeinitPins(void)
{
    PORT_SetPinMux(PORTE, PIN10_IDX, kPORT_PinDisabledOrAnalog); /* PORTE10 (pin F1) is disabled */
    PORT_SetPinMux(PORTE, PIN11_IDX, kPORT_PinDisabledOrAnalog); /* PORTE11 (pin G4) is disabled */
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
