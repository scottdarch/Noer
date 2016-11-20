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
- !!processor_version '0.1.25'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/driver_examples/sai/interrupt_transfer/pin_mux.h"

#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/devices/MK66F18/drivers/fsl_common.h"
#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/devices/MK66F18/drivers/fsl_port.h"

#define PCR_ODE_ENABLED               0x01u   /*!< Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is configured as a digital output. */
#define PCR_PE_ENABLED                0x01u   /*!< Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is configured as a digital input. */
#define PCR_PS_UP                     0x01u   /*!< Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN10_IDX                       10u   /*!< Pin number for pin 10 in a port */
#define PIN11_IDX                       11u   /*!< Pin number for pin 11 in a port */
#define PIN12_IDX                       12u   /*!< Pin number for pin 12 in a port */
#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port */
#define PIN17_IDX                       17u   /*!< Pin number for pin 17 in a port */
#define SOPT5_UART0TXSRC_UART_TX      0x00u   /*!< UART 0 transmit data source select: UART0_TX pin */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: B11, peripheral: I2S0, signal: TXD0, pin_signal: ADC0_SE15/TSI0_CH14/PTC1/LLWU_P6/SPI0_PCS3/UART1_RTS_b/FTM0_CH0/FB_AD13/SDRAM_A21/I2S0_TXD0}
  - {pin_num: C8, peripheral: I2S0, signal: MCLK, pin_signal: CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/I2S0_RX_BCLK/FB_AD9/SDRAM_A17/I2S0_MCLK}
  - {pin_num: C7, peripheral: I2C1, signal: SCL, pin_signal: ADC1_SE6b/PTC10/I2C1_SCL/FTM3_CH6/I2S0_RX_FS/FB_AD5/SDRAM_A13, open_drain: enable, pull_select: up, pull_enable: enable}
  - {pin_num: B7, peripheral: I2C1, signal: SDA, pin_signal: ADC1_SE7b/PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/I2S0_RXD1/FB_RW_b, open_drain: enable, pull_select: up, pull_enable: enable}
  - {pin_num: G3, peripheral: I2S0, signal: TX_BCLK, pin_signal: PTE12/I2S0_TX_BCLK/FTM3_CH7}
  - {pin_num: G4, peripheral: I2S0, signal: TX_FS, pin_signal: PTE11/I2C3_SCL/I2S0_TX_FS/LPUART0_RTS_b/FTM3_CH6}
  - {pin_num: E10, peripheral: UART0, signal: RX, pin_signal: TSI0_CH9/PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/SDRAM_D17/EWM_IN/TPM_CLKIN0}
  - {pin_num: E9, peripheral: UART0, signal: TX, pin_signal: TSI0_CH10/PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/SDRAM_D16/EWM_OUT_b/TPM_CLKIN1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Port B Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTB, PIN16_IDX, kPORT_MuxAlt3);           /* PORTB16 (pin E10) is configured as UART0_RX */
  PORT_SetPinMux(PORTB, PIN17_IDX, kPORT_MuxAlt3);           /* PORTB17 (pin E9) is configured as UART0_TX */
  PORT_SetPinMux(PORTC, PIN1_IDX, kPORT_MuxAlt6);            /* PORTC1 (pin B11) is configured as I2S0_TXD0 */
  PORT_SetPinMux(PORTC, PIN10_IDX, kPORT_MuxAlt2);           /* PORTC10 (pin C7) is configured as I2C1_SCL */
  PORTC->PCR[10] = ((PORTC->PCR[10] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_ENABLED)                          /* Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is configured as a digital input. */
      | PORT_PCR_ODE(PCR_ODE_ENABLED)                        /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTC, PIN11_IDX, kPORT_MuxAlt2);           /* PORTC11 (pin B7) is configured as I2C1_SDA */
  PORTC->PCR[11] = ((PORTC->PCR[11] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_ENABLED)                          /* Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is configured as a digital input. */
      | PORT_PCR_ODE(PCR_ODE_ENABLED)                        /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTC, PIN6_IDX, kPORT_MuxAlt6);            /* PORTC6 (pin C8) is configured as I2S0_MCLK */
  PORT_SetPinMux(PORTE, PIN11_IDX, kPORT_MuxAlt4);           /* PORTE11 (pin G4) is configured as I2S0_TX_FS */
  PORT_SetPinMux(PORTE, PIN12_IDX, kPORT_MuxAlt4);           /* PORTE12 (pin G3) is configured as I2S0_TX_BCLK */
  SIM->SOPT5 = ((SIM->SOPT5 &
    (~(SIM_SOPT5_UART0TXSRC_MASK)))                          /* Mask bits to zero which are setting */
      | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX)       /* UART 0 transmit data source select: UART0_TX pin */
    );
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
