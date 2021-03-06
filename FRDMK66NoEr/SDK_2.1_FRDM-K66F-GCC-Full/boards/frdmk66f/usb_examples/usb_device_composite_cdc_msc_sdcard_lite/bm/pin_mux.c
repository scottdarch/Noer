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

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

#define PCR_PE_ENABLED                                                                                              \
    0x01u /*!< Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is \
             configured as a digital input. */
#define PCR_PS_UP                                                                                                 \
    0x01u /*!< Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE \
             field is set. */
#define PIN0_IDX 0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX 1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX 2u   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX 3u   /*!< Pin number for pin 3 in a port */
#define PIN4_IDX 4u   /*!< Pin number for pin 4 in a port */
#define PIN5_IDX 5u   /*!< Pin number for pin 5 in a port */
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
  - {pin_num: D3, peripheral: SDHC, signal: 'DATA, 1', pin_signal:
ADC1_SE4a/PTE0/SPI1_PCS1/UART1_TX/SDHC0_D1/TRACE_CLKOUT/I2C1_SDA/RTC_CLKOUT, pull_select: up, pull_enable: enable}
  - {pin_num: D2, peripheral: SDHC, signal: 'DATA, 0', pin_signal:
ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/SDHC0_D0/TRACE_D3/I2C1_SCL/SPI1_SIN, pull_select: up,
    pull_enable: enable}
  - {pin_num: D1, peripheral: SDHC, signal: DCLK, pin_signal:
ADC1_SE6a/PTE2/LLWU_P1/SPI1_SCK/UART1_CTS_b/SDHC0_DCLK/TRACE_D2, pull_select: up, pull_enable: enable}
  - {pin_num: E4, peripheral: SDHC, signal: CMD, pin_signal:
ADC1_SE7a/PTE3/SPI1_SIN/UART1_RTS_b/SDHC0_CMD/TRACE_D1/SPI1_SOUT, pull_select: up, pull_enable: enable}
  - {pin_num: E3, peripheral: SDHC, signal: 'DATA, 3', pin_signal: PTE4/LLWU_P2/SPI1_PCS0/UART3_TX/SDHC0_D3/TRACE_D0,
pull_select: up, pull_enable: enable}
  - {pin_num: E2, peripheral: SDHC, signal: 'DATA, 2', pin_signal: PTE5/SPI1_PCS2/UART3_RX/SDHC0_D2/FTM3_CH0,
pull_select: up, pull_enable: enable}
  - {pin_num: B3, peripheral: GPIOD, signal: 'GPIO, 10', pin_signal: PTD10/LPUART0_RTS_b/FB_A18, pull_select: up,
pull_enable: enable}
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
    CLOCK_EnableClock(kCLOCK_PortE); /* Port E Clock Gate Control: Clock enabled */

    PORT_SetPinMux(PORTB, PIN16_IDX, kPORT_MuxAlt3);   /* PORTB16 (pin E10) is configured as UART0_RX */
    PORT_SetPinMux(PORTB, PIN17_IDX, kPORT_MuxAlt3);   /* PORTB17 (pin E9) is configured as UART0_TX */
    PORT_SetPinMux(PORTD, PIN10_IDX, kPORT_MuxAsGpio); /* PORTD10 (pin B3) is configured as PTD10 */
    PORTD->PCR[10] =
        ((PORTD->PCR[10] &
          (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         );
    PORT_SetPinMux(PORTE, PIN0_IDX, kPORT_MuxAlt4); /* PORTE0 (pin D3) is configured as SDHC0_D1 */
    PORTE->PCR[0] =
        ((PORTE->PCR[0] &
          (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         );
    PORT_SetPinMux(PORTE, PIN1_IDX, kPORT_MuxAlt4); /* PORTE1 (pin D2) is configured as SDHC0_D0 */
    PORTE->PCR[1] =
        ((PORTE->PCR[1] &
          (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         );
    PORT_SetPinMux(PORTE, PIN2_IDX, kPORT_MuxAlt4); /* PORTE2 (pin D1) is configured as SDHC0_DCLK */
    PORTE->PCR[2] =
        ((PORTE->PCR[2] &
          (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         );
    PORT_SetPinMux(PORTE, PIN3_IDX, kPORT_MuxAlt4); /* PORTE3 (pin E4) is configured as SDHC0_CMD */
    PORTE->PCR[3] =
        ((PORTE->PCR[3] &
          (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         );
    PORT_SetPinMux(PORTE, PIN4_IDX, kPORT_MuxAlt4); /* PORTE4 (pin E3) is configured as SDHC0_D3 */
    PORTE->PCR[4] =
        ((PORTE->PCR[4] &
          (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         );
    PORT_SetPinMux(PORTE, PIN5_IDX, kPORT_MuxAlt4); /* PORTE5 (pin E2) is configured as SDHC0_D2 */
    PORTE->PCR[5] =
        ((PORTE->PCR[5] &
          (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
         | PORT_PCR_PS(PCR_PS_UP) /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                                     corresponding PE field is set. */
         | PORT_PCR_PE(PCR_PE_ENABLED) /* Pull Enable: Internal pullup or pulldown resistor is enabled on the
                                          corresponding pin, if the pin is configured as a digital input. */
         );
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
