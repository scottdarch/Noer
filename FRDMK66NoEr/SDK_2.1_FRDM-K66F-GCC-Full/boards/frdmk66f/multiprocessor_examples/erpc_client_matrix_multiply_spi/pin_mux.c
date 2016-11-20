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
- !!product 'Pins v1.0'
- !!processor 'MK66FN2M0xxx18'
- !!package 'MK66FN2M0VMD18'
- !!mcu_data 'ksdk2_0'
- !!processor_version '1.0.0'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/multiprocessor_examples/erpc_client_matrix_multiply_spi/pin_mux.h"

#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/devices/MK66F18/drivers/fsl_common.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/devices/MK66F18/drivers/fsl_port.h"

/*!< Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is configured as a digital input. */
#define PCR_PE_ENABLED 0x01u
/*!< Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
#define PCR_PS_UP 0x01u
#define PIN0_IDX 0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX 1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX 2u   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX 3u   /*!< Pin number for pin 3 in a port */
#define PIN4_IDX 4u   /*!< Pin number for pin 4 in a port */
#define PIN5_IDX 5u   /*!< Pin number for pin 5 in a port */
#define PIN6_IDX 6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX 7u   /*!< Pin number for pin 7 in a port */
#define PIN10_IDX 10u /*!< Pin number for pin 10 in a port */
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
  - {pin_num: A5, peripheral: SPI0, signal: PCS0_SS, pin_signal:
PTD0/LLWU_P12/SPI0_PCS0/UART2_RTS_b/FTM3_CH0/FB_ALE/FB_CS1_b/FB_TS_b}
  - {pin_num: D4, peripheral: SPI0, signal: SCK, pin_signal: ADC0_SE5b/PTD1/SPI0_SCK/UART2_CTS_b/FTM3_CH1/FB_CS0_b}
  - {pin_num: C4, peripheral: SPI0, signal: SOUT, pin_signal:
PTD2/LLWU_P13/SPI0_SOUT/UART2_RX/FTM3_CH2/FB_AD4/SDRAM_A12/I2C0_SCL}
  - {pin_num: B4, peripheral: SPI0, signal: SIN, pin_signal: PTD3/SPI0_SIN/UART2_TX/FTM3_CH3/FB_AD3/SDRAM_A11/I2C0_SDA}
  - {pin_num: M9, peripheral: GPIOA, signal: 'GPIO, 10', pin_signal:
PTA10/LLWU_P22/FTM2_CH0/MII0_RXD2/FTM2_QD_PHA/TPM2_CH0/TRACE_D0, pull_select: up, pull_enable: enable}
  - {pin_num: G12, peripheral: GPIOB, signal: 'GPIO, 2', pin_signal:
ADC0_SE12/TSI0_CH7/PTB2/I2C0_SCL/UART0_RTS_b/ENET0_1588_TMR0/SDRAM_WE/FTM0_FLT3}
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
    CLOCK_EnableClock(kCLOCK_PortD); /* Port D Clock Gate Control: Clock enabled */

    PORT_SetPinMux(PORTA, PIN10_IDX, kPORT_MuxAsGpio); /* PORTA10 (pin M9) is configured as PTA10 */
    PORTA->PCR[10] =
        ((PORTA->PCR[10] &
          (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         );
    PORT_SetPinMux(PORTB, PIN2_IDX, kPORT_MuxAsGpio); /* PORTB2 (pin G12) is configured as PTB2 */
    PORT_SetPinMux(PORTB, PIN16_IDX, kPORT_MuxAlt3);  /* PORTB16 (pin E10) is configured as UART0_RX */
    PORT_SetPinMux(PORTB, PIN17_IDX, kPORT_MuxAlt3);  /* PORTB17 (pin E9) is configured as UART0_TX */
    PORT_SetPinMux(PORTD, PIN0_IDX, kPORT_MuxAlt2);   /* PORTD0 (pin A5) is configured as SPI0_PCS0 */
    PORT_SetPinMux(PORTD, PIN1_IDX, kPORT_MuxAlt2);   /* PORTD1 (pin D4) is configured as SPI0_SCK */
    PORT_SetPinMux(PORTD, PIN2_IDX, kPORT_MuxAlt2);   /* PORTD2 (pin C4) is configured as SPI0_SOUT */
    PORT_SetPinMux(PORTD, PIN3_IDX, kPORT_MuxAlt2);   /* PORTD3 (pin B4) is configured as SPI0_SIN */
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
