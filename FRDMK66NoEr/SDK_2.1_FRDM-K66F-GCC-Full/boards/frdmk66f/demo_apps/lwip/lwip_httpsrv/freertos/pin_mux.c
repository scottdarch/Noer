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

#include "../../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/demo_apps/lwip/lwip_httpsrv/freertos/pin_mux.h"

#include "../../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/devices/MK66F18/drivers/fsl_common.h"
#include "../../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/devices/MK66F18/drivers/fsl_port.h"

#define PCR_ODE_ENABLED               0x01u   /*!< Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is configured as a digital output. */
#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */
#define PIN12_IDX                       12u   /*!< Pin number for pin 12 in a port */
#define PIN13_IDX                       13u   /*!< Pin number for pin 13 in a port */
#define PIN14_IDX                       14u   /*!< Pin number for pin 14 in a port */
#define PIN15_IDX                       15u   /*!< Pin number for pin 15 in a port */
#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port */
#define PIN17_IDX                       17u   /*!< Pin number for pin 17 in a port */
#define PIN26_IDX                       26u   /*!< Pin number for pin 26 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR THE PINS TOOL *****************************
BOARD_InitPins:
- options: {coreID: singlecore, enableClock: 'true'}
- pin_list:
  - {pin_num: E10, peripheral: UART0, signal: RX, pin_signal: TSI0_CH9/PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/SDRAM_D17/EWM_IN/TPM_CLKIN0}
  - {pin_num: E9, peripheral: SIM, signal: UART0_MOD_OUT, pin_signal: TSI0_CH10/PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/SDRAM_D16/EWM_OUT_b/TPM_CLKIN1}
  - {pin_num: K9, peripheral: ENET, signal: MII_RXD1, pin_signal: CMP2_IN0/PTA12/CAN0_TX/FTM1_CH0/RMII0_RXD1/MII0_RXD1/I2C2_SCL/I2S0_TXD0/FTM1_QD_PHA/TPM1_CH0}
  - {pin_num: J9, peripheral: ENET, signal: MII_RXD0, pin_signal: CMP2_IN1/PTA13/LLWU_P4/CAN0_RX/FTM1_CH1/RMII0_RXD0/MII0_RXD0/I2C2_SDA/I2S0_TX_FS/FTM1_QD_PHB/TPM1_CH1}
  - {pin_num: L10, peripheral: ENET, signal: MII_RXDV, pin_signal: PTA14/SPI0_PCS0/UART0_TX/RMII0_CRS_DV/MII0_RXDV/I2C2_SCL/I2S0_RX_BCLK/I2S0_TXD1}
  - {pin_num: L11, peripheral: ENET, signal: MII_TXEN, pin_signal: CMP3_IN1/PTA15/SPI0_SCK/UART0_RX/RMII0_TXEN/MII0_TXEN/I2S0_RXD0}
  - {pin_num: K10, peripheral: ENET, signal: MII_TXD0, pin_signal: CMP3_IN2/PTA16/SPI0_SOUT/UART0_CTS_b/UART0_COL_b/RMII0_TXD0/MII0_TXD0/I2S0_RX_FS/I2S0_RXD1}
  - {pin_num: K11, peripheral: ENET, signal: MII_TXD1, pin_signal: ADC1_SE17/PTA17/SPI0_SIN/UART0_RTS_b/RMII0_TXD1/MII0_TXD1/I2S0_MCLK}
  - {pin_num: M8, peripheral: ENET, signal: MII_RXER, pin_signal: PTA5/USB0_CLKIN/FTM0_CH2/RMII0_RXER/MII0_RXER/CMP2_OUT/I2S0_TX_BCLK/JTAG_TRST_b}
  - {pin_num: H10, peripheral: ENET, signal: MII_MDIO, pin_signal: ADC0_SE8/ADC1_SE8/TSI0_CH0/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/RMII0_MDIO/MII0_MDIO/SDRAM_CAS_b/FTM1_QD_PHA/TPM1_CH0,
    open_drain: enable}
  - {pin_num: H9, peripheral: ENET, signal: MII_MDC, pin_signal: ADC0_SE9/ADC1_SE9/TSI0_CH6/PTB1/I2C0_SDA/FTM1_CH1/RMII0_MDC/MII0_MDC/SDRAM_RAS_b/FTM1_QD_PHB/TPM1_CH1}
  - {pin_num: K4, peripheral: ENET, signal: CLKIN_1588, pin_signal: PTE26/ENET_1588_CLKIN/UART4_CTS_b/RTC_CLKOUT/USB0_CLKIN}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR THE PINS TOOL ***
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Port A Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Port B Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTA, PIN12_IDX, kPORT_MuxAlt4);           /* PORTA12 (pin K9) is configured as MII0_RXD1 */
  PORT_SetPinMux(PORTA, PIN13_IDX, kPORT_MuxAlt4);           /* PORTA13 (pin J9) is configured as MII0_RXD0 */
  PORT_SetPinMux(PORTA, PIN14_IDX, kPORT_MuxAlt4);           /* PORTA14 (pin L10) is configured as MII0_RXDV */
  PORT_SetPinMux(PORTA, PIN15_IDX, kPORT_MuxAlt4);           /* PORTA15 (pin L11) is configured as MII0_TXEN */
  PORT_SetPinMux(PORTA, PIN16_IDX, kPORT_MuxAlt4);           /* PORTA16 (pin K10) is configured as MII0_TXD0 */
  PORT_SetPinMux(PORTA, PIN17_IDX, kPORT_MuxAlt4);           /* PORTA17 (pin K11) is configured as MII0_TXD1 */
  PORT_SetPinMux(PORTA, PIN5_IDX, kPORT_MuxAlt4);            /* PORTA5 (pin M8) is configured as MII0_RXER */
  PORT_SetPinMux(PORTB, PIN0_IDX, kPORT_MuxAlt4);            /* PORTB0 (pin H10) is configured as MII0_MDIO */
  PORTB->PCR[0] = ((PORTB->PCR[0] &
    (~(PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK)))              /* Mask bits to zero which are setting */
      | PORT_PCR_ODE(PCR_ODE_ENABLED)                        /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTB, PIN1_IDX, kPORT_MuxAlt4);            /* PORTB1 (pin H9) is configured as MII0_MDC */
  PORT_SetPinMux(PORTB, PIN16_IDX, kPORT_MuxAlt3);           /* PORTB16 (pin E10) is configured as UART0_RX */
  PORT_SetPinMux(PORTB, PIN17_IDX, kPORT_MuxAlt3);           /* PORTB17 (pin E9) is configured as UART0_TX */
  PORT_SetPinMux(PORTE, PIN26_IDX, kPORT_MuxAlt2);           /* PORTE26 (pin K4) is configured as ENET_1588_CLKIN */
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
