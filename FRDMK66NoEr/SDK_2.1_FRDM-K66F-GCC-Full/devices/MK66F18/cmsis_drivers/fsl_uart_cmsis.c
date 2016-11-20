/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.

 * Copyright (c) 2016, Freescale Semiconductor, Inc.
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
 */

#include "../../../../SDK_2.1_FRDM-K66F-GCC-Full/devices/MK66F18/cmsis_drivers/fsl_uart_cmsis.h"

#define ARM_UART_DRV_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(2, 0)

/*
 * ARMCC does not support split the data section automatically, so the driver
 * needs to split the data to separate sections explicitly, to reduce codesize.
 */
#if defined(__CC_ARM)
#define ARMCC_SECTION(section_name) __attribute__((section(section_name)))
#endif

typedef const struct _cmsis_uart_resource
{
    UART_Type *base;           /*!< uart peripheral base address.      */
    uint32_t (*GetFreq)(void); /*!< Function to get the clock frequency. */
} cmsis_uart_resource_t;

typedef struct _cmsis_uart_interrupt_driver_state
{
    cmsis_uart_resource_t *resource;  /*!< Basic uart resource. */
    uart_handle_t *handle;            /*!< Interupt transfer handle. */
    ARM_USART_SignalEvent_t cb_event; /*!< Callback function.     */
    bool isInitialized;               /*!< Is initialized or not. */
    bool isPowerOn;                   /*!< Is power on or not.    */
    bool isConfigured;                /*!< Configured to work or not. */
} cmsis_uart_interrupt_driver_state_t;

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)
typedef const struct _cmsis_uart_dma_resource
{
    DMA_Type *txDmaBase;       /*!< DMA peripheral base address for TX.    */
    uint32_t txDmaChannel;     /*!< DMA channel for uart TX.             */
    DMAMUX_Type *txDmamuxBase; /*!< DMAMUX peripheral base address for TX. */
    uint8_t txDmaRequest;      /*!< TX DMA request source.                 */

    DMA_Type *rxDmaBase;       /*!< DMA peripheral base address for RX.    */
    uint32_t rxDmaChannel;     /*!< DMA channel for uart RX.             */
    DMAMUX_Type *rxDmamuxBase; /*!< DMAMUX peripheral base address for RX. */
    uint8_t rxDmaRequest;      /*!< RX DMA request source.                 */
} cmsis_uart_dma_resource_t;

typedef struct _cmsis_uart_dma_driver_state
{
    cmsis_uart_resource_t *resource;        /*!< uart basic resource.      */
    cmsis_uart_dma_resource_t *dmaResource; /*!< uart DMA resource.        */
    uart_dma_handle_t *handle;              /*!< uart DMA transfer handle. */
    dma_handle_t *rxHandle;                 /*!< DMA RX handle.              */
    dma_handle_t *txHandle;                 /*!< DMA TX handle.              */
    ARM_USART_SignalEvent_t cb_event;       /*!< Callback function.     */
    bool isInitialized;                     /*!< Is initialized or not.      */
    bool isPowerOn;                         /*!< Is power on or not.         */
    bool isConfigured;                      /*!< Configured to work or not.  */
} cmsis_uart_dma_driver_state_t;
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
typedef const struct _cmsis_uart_edma_resource
{
    DMA_Type *txEdmaBase;      /*!< EDMA peripheral base address for TX.    */
    uint32_t txEdmaChannel;    /*!< EDMA channel for uart TX.             */
    DMAMUX_Type *txDmamuxBase; /*!< DMAMUX peripheral base address for TX. */
    uint8_t txDmaRequest;      /*!< TX EDMA request source.                 */

    DMA_Type *rxEdmaBase;      /*!< EDMA peripheral base address for RX.    */
    uint32_t rxEdmaChannel;    /*!< EDMA channel for uart RX.             */
    DMAMUX_Type *rxDmamuxBase; /*!< DMAMUX peripheral base address for RX. */
    uint8_t rxDmaRequest;      /*!< RX EDMA request source.                 */
} cmsis_uart_edma_resource_t;

typedef struct _cmsis_uart_edma_driver_state
{
    cmsis_uart_resource_t *resource;         /*!< uart basic resource.      */
    cmsis_uart_edma_resource_t *dmaResource; /*!< uart EDMA resource.        */
    uart_edma_handle_t *handle;              /*!< uart EDMA transfer handle. */
    edma_handle_t *rxHandle;                 /*!< EDMA RX handle.              */
    edma_handle_t *txHandle;                 /*!< EDMA TX handle.              */
    ARM_USART_SignalEvent_t cb_event;        /*!< Callback function.     */
    bool isInitialized;                      /*!< Is initialized or not.      */
    bool isPowerOn;                          /*!< Is power on or not.         */
    bool isConfigured;                       /*!< Configured to work or not. */
} cmsis_uart_edma_driver_state_t;
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

enum _uart_transfer_states
{
    kuart_TxIdle, /*!< TX idle. */
    kuart_TxBusy, /*!< TX busy. */
    kuart_RxIdle, /*!< RX idle. */
    kuart_RxBusy  /*!< RX busy. */
};

/* Driver Version */
static const ARM_DRIVER_VERSION s_uartDriverVersion = {ARM_USART_API_VERSION, ARM_UART_DRV_VERSION};

static const ARM_USART_CAPABILITIES s_uartDriverCapabilities = {
    1, /* supports uart (Asynchronous) mode */
    0, /* supports Synchronous Master mode */
    0, /* supports Synchronous Slave mode */
    0, /* supports uart Single-wire mode */
    0, /* supports uart IrDA mode */
    0, /* supports uart Smart Card mode */
    0, /* Smart Card Clock generator */
    0, /* RTS Flow Control available */
    0, /* CTS Flow Control available */
    0, /* Transmit completed event: \ref ARM_USART_EVENT_TX_COMPLETE */
    0, /* Signal receive character timeout event: \ref ARM_USART_EVENT_RX_TIMEOUT */
    0, /* RTS Line: 0=not available, 1=available */
    0, /* CTS Line: 0=not available, 1=available */
    0, /* DTR Line: 0=not available, 1=available */
    0, /* DSR Line: 0=not available, 1=available */
    0, /* DCD Line: 0=not available, 1=available */
    0, /* RI Line: 0=not available, 1=available */
    0, /* Signal CTS change event: \ref ARM_USART_EVENT_CTS */
    0, /* Signal DSR change event: \ref ARM_USART_EVENT_DSR */
    0, /* Signal DCD change event: \ref ARM_USART_EVENT_DCD */
    0, /* Signal RI change event: \ref ARM_USART_EVENT_RI */
};

/*
 * Common control function used by uart_NonBlockingControl/uart_DmaControl/uart_EdmaControl
 */
static int32_t UART_CommonControl(uint32_t control, uint32_t arg, cmsis_uart_resource_t *resource, bool *isConfigured)
{
    uart_config_t config;

    UART_GetDefaultConfig(&config);

    switch (control & ARM_USART_CONTROL_Msk)
    {
        case ARM_USART_MODE_ASYNCHRONOUS:
            /* USART Baudrate */
            config.baudRate_Bps = arg;
            break;

        /* TX/RX IO is controlled in application layer. */
        case ARM_USART_CONTROL_TX:
            if (arg)
            {
                UART_EnableTx(resource->base, true);
            }
            else
            {
                UART_EnableTx(resource->base, false);
            }
            return ARM_DRIVER_OK;

        case ARM_USART_CONTROL_RX:
            if (arg)
            {
                UART_EnableRx(resource->base, true);
            }
            else
            {
                UART_EnableRx(resource->base, false);
            }

            return ARM_DRIVER_OK;

        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    switch (control & ARM_USART_PARITY_Msk)
    {
        case ARM_USART_PARITY_NONE:
            config.parityMode = kUART_ParityDisabled;
            break;
        case ARM_USART_PARITY_EVEN:
            config.parityMode = kUART_ParityEven;
            break;
        case ARM_USART_PARITY_ODD:
            config.parityMode = kUART_ParityOdd;
            break;
        default:
            return ARM_USART_ERROR_PARITY;
    }

    switch (control & ARM_USART_STOP_BITS_Msk)
    {
        case ARM_USART_STOP_BITS_1:
            /* The GetDefaultConfig has already set for this case. */
            break;
#if defined(FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT) && FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
        case ARM_USART_STOP_BITS_2:
            config.stopBitCount = kUART_TwoStopBit;
            break;
#endif
        default:
            return ARM_USART_ERROR_STOP_BITS;
    }

    /* If uart is already configured, deinit it first. */
    if (*isConfigured)
    {
        UART_Deinit(resource->base);
        *isConfigured = false;
    }

    config.enableTx = true;
    config.enableRx = true;

    if (kStatus_UART_BaudrateNotSupport == UART_Init(resource->base, &config, resource->GetFreq()))
    {
        return ARM_USART_ERROR_BAUDRATE;
    }

    *isConfigured = true;

    return ARM_DRIVER_OK;
}

void KSDK_UART_NonBlockingCallback(UART_Type *base, uart_handle_t *handle, status_t status, void *userData)
{
    uint32_t event;

    if (kStatus_UART_TxIdle == status)
    {
        event = ARM_USART_EVENT_SEND_COMPLETE;
    }
    else if (kStatus_UART_RxIdle == status)
    {
        event = ARM_USART_EVENT_RECEIVE_COMPLETE;
    }

    /* User data is actually CMSIS driver callback. */
    if (userData)
    {
        ((ARM_USART_SignalEvent_t)userData)(event);
    }
}

static ARM_DRIVER_VERSION UARTx_GetVersion(void)
{
    return s_uartDriverVersion;
}

static ARM_USART_CAPABILITIES UARTx_GetCapabilities(void)
{
    return s_uartDriverCapabilities;
}

static int32_t UART_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event, cmsis_uart_interrupt_driver_state_t *uart)
{
    if (uart->isInitialized)
    {
        /* Driver is already initialized */
        return ARM_DRIVER_OK;
    }

    uart->cb_event = cb_event;
    uart->isInitialized = true;

    return ARM_DRIVER_OK;
}

static int32_t UART_NonBlockingUninitialize(cmsis_uart_interrupt_driver_state_t *uart)
{
    uart->isInitialized = false;
    return ARM_DRIVER_OK;
}

static int32_t UART_NonBlockingPowerControl(ARM_POWER_STATE state, cmsis_uart_interrupt_driver_state_t *uart)
{
    uart_config_t config;

    switch (state)
    {
        case ARM_POWER_OFF:
            if (uart->isPowerOn)
            {
                UART_Deinit(uart->resource->base);
                uart->isPowerOn = false;
                uart->isConfigured = false;
            }
            break;
        case ARM_POWER_LOW:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        case ARM_POWER_FULL:
            /* Must be initialized first. */
            if (!uart->isInitialized)
            {
                return ARM_DRIVER_ERROR;
            }

            if (!uart->isPowerOn)
            {
                UART_GetDefaultConfig(&config);
                config.enableTx = true;
                config.enableRx = true;

                UART_Init(uart->resource->base, &config, uart->resource->GetFreq());
                UART_TransferCreateHandle(uart->resource->base, uart->handle, KSDK_UART_NonBlockingCallback,
                                          (void *)uart->cb_event);
                uart->isPowerOn = true;
                uart->isConfigured = true;
            }
            break;
        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    return ARM_DRIVER_OK;
}

static int32_t UART_NonBlockingSend(const void *data, uint32_t num, cmsis_uart_interrupt_driver_state_t *uart)
{
    int32_t ret;
    status_t status;
    uart_transfer_t xfer;

    xfer.data = (uint8_t *)data;
    xfer.dataSize = num;

    status = UART_TransferSendNonBlocking(uart->resource->base, uart->handle, &xfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_UART_TxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t UART_NonBlockingReceive(void *data, uint32_t num, cmsis_uart_interrupt_driver_state_t *uart)
{
    int32_t ret;
    status_t status;
    uart_transfer_t xfer;

    xfer.data = data;
    xfer.dataSize = num;

    status = UART_TransferReceiveNonBlocking(uart->resource->base, uart->handle, &xfer, NULL);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_UART_RxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t UART_NonBlockingTransfer(const void *data_out,
                                        void *data_in,
                                        uint32_t num,
                                        cmsis_uart_interrupt_driver_state_t *uart)
{
    /* Only in synchronous mode */
    return ARM_DRIVER_ERROR;
}

static uint32_t UART_NonBlockingGetTxCount(cmsis_uart_interrupt_driver_state_t *uart)
{
    uint32_t cnt;

    /* If TX not in progress, then the TX count is txDataSizeAll saved in handle. */
    if (kStatus_NoTransferInProgress == UART_TransferGetSendCount(uart->resource->base, uart->handle, &cnt))
    {
        cnt = uart->handle->txDataSizeAll;
    }

    return cnt;
}

static uint32_t UART_NonBlockingGetRxCount(cmsis_uart_interrupt_driver_state_t *uart)
{
    uint32_t cnt;

    if (kStatus_NoTransferInProgress == UART_TransferGetReceiveCount(uart->resource->base, uart->handle, &cnt))
    {
        cnt = uart->handle->rxDataSizeAll;
    }

    return cnt;
}

static int32_t UART_NonBlockingControl(uint32_t control, uint32_t arg, cmsis_uart_interrupt_driver_state_t *uart)
{
    /* Must be power on. */
    if (!uart->isPowerOn)
    {
        return ARM_DRIVER_ERROR;
    }

    /* Does not support these features. */
    if (control & (ARM_USART_FLOW_CONTROL_Msk | ARM_USART_CPOL_Msk | ARM_USART_CPHA_Msk))
    {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    switch (control & ARM_USART_CONTROL_Msk)
    {
        /* Abort Send */
        case ARM_USART_ABORT_SEND:
            UART_TransferAbortSend(uart->resource->base, uart->handle);
            return ARM_DRIVER_OK;

        /* Abort receive */
        case ARM_USART_ABORT_RECEIVE:
            UART_TransferAbortReceive(uart->resource->base, uart->handle);
            return ARM_DRIVER_OK;

        default:
            break;
    }

    return UART_CommonControl(control, arg, uart->resource, &uart->isConfigured);
}

static ARM_USART_STATUS UART_NonBlockingGetStatus(cmsis_uart_interrupt_driver_state_t *uart)
{
    ARM_USART_STATUS stat;
    uint32_t ksdk_uart_status = UART_GetStatusFlags(uart->resource->base);

    stat.tx_busy = ((kuart_TxBusy == uart->handle->txState) ? (1U) : (0U));
    stat.rx_busy = ((kuart_RxBusy == uart->handle->rxState) ? (1U) : (0U));

    stat.tx_underflow = 0U;
    stat.rx_overflow = (!(!(ksdk_uart_status & kUART_RxOverrunFlag)));
#if defined(FSL_FEATURE_uart_HAS_LIN_BREAK_DETECT) && FSL_FEATURE_uart_HAS_LIN_BREAK_DETECT
    stat.rx_break = (!(!(ksdk_uart_status & kuart_LinBreakFlag)));
#else
    stat.rx_break = 0U;
#endif
    stat.rx_framing_error = (!(!(ksdk_uart_status & kUART_FramingErrorFlag)));
    stat.rx_parity_error = (!(!(ksdk_uart_status & kUART_ParityErrorFlag)));

    return stat;
}

static int32_t UARTx_SetModemControl(ARM_USART_MODEM_CONTROL control)
{
    return ARM_DRIVER_ERROR_UNSUPPORTED;
}

static ARM_USART_MODEM_STATUS UARTx_GetModemStatus(void)
{
    ARM_USART_MODEM_STATUS modem_status;

    modem_status.cts = 0U;
    modem_status.dsr = 0U;
    modem_status.ri = 0U;
    modem_status.dcd = 0U;

    return modem_status;
}

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)
void KSDK_UART_DmaCallback(UART_Type *base, uart_dma_handle_t *handle, status_t status, void *userData)
{
    uint32_t event;

    if (kStatus_UART_TxIdle == status)
    {
        event = ARM_USART_EVENT_SEND_COMPLETE;
    }
    else if (kStatus_UART_RxIdle == status)
    {
        event = ARM_USART_EVENT_RECEIVE_COMPLETE;
    }

    /* User data is actually CMSIS driver callback. */
    if (userData)
    {
        ((ARM_USART_SignalEvent_t)userData)(event);
    }
}

static int32_t UART_DmaInitialize(ARM_USART_SignalEvent_t cb_event, cmsis_uart_dma_driver_state_t *uart)
{
    if (uart->isInitialized)
    {
        /* Driver is already initialized */
        return ARM_DRIVER_OK;
    }

    uart->cb_event = cb_event;
    uart->isInitialized = true;

    return ARM_DRIVER_OK;
}

static int32_t UART_DmaUninitialize(cmsis_uart_dma_driver_state_t *uart)
{
    uart->isInitialized = false;
    return ARM_DRIVER_OK;
}

static int32_t UART_DmaPowerControl(ARM_POWER_STATE state, cmsis_uart_dma_driver_state_t *uart)
{
    uart_config_t config;
    cmsis_uart_dma_resource_t *dmaResource;

    switch (state)
    {
        case ARM_POWER_OFF:
            if (uart->isPowerOn)
            {
                UART_Deinit(uart->resource->base);
                DMAMUX_DisableChannel(uart->dmaResource->rxDmamuxBase, uart->dmaResource->rxDmaChannel);
                DMAMUX_DisableChannel(uart->dmaResource->txDmamuxBase, uart->dmaResource->txDmaChannel);
                uart->isPowerOn = false;
                uart->isConfigured = false;
            }
            break;
        case ARM_POWER_LOW:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        case ARM_POWER_FULL:
            /* Must be initialized first. */
            if (!uart->isInitialized)
            {
                return ARM_DRIVER_ERROR;
            }

            if (!uart->isPowerOn)
            {
                UART_GetDefaultConfig(&config);
                config.enableTx = true;
                config.enableRx = true;

                dmaResource = uart->dmaResource;

                /* Set up DMA setting. */
                DMA_CreateHandle(uart->rxHandle, dmaResource->rxDmaBase, dmaResource->rxDmaChannel);
                DMAMUX_SetSource(dmaResource->rxDmamuxBase, dmaResource->rxDmaChannel, dmaResource->rxDmaRequest);
                DMAMUX_EnableChannel(dmaResource->rxDmamuxBase, dmaResource->rxDmaChannel);

                DMA_CreateHandle(uart->txHandle, dmaResource->txDmaBase, dmaResource->txDmaChannel);
                DMAMUX_SetSource(dmaResource->txDmamuxBase, dmaResource->txDmaChannel, dmaResource->txDmaRequest);
                DMAMUX_EnableChannel(dmaResource->txDmamuxBase, dmaResource->txDmaChannel);

                /* Setup the uart. */
                UART_Init(uart->resource->base, &config, uart->resource->GetFreq());
                UART_TransferCreateHandleDMA(uart->resource->base, uart->handle, KSDK_UART_DmaCallback,
                                             (void *)uart->cb_event, uart->txHandle, uart->rxHandle);

                uart->isPowerOn = true;
                uart->isConfigured = true;
            }
            break;
        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    return ARM_DRIVER_OK;
}

static int32_t UART_DmaSend(const void *data, uint32_t num, cmsis_uart_dma_driver_state_t *uart)
{
    int32_t ret;
    status_t status;
    uart_transfer_t xfer;

    xfer.data = (uint8_t *)data;
    xfer.dataSize = num;

    status = UART_TransferSendDMA(uart->resource->base, uart->handle, &xfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_UART_RxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t UART_DmaReceive(void *data, uint32_t num, cmsis_uart_dma_driver_state_t *uart)
{
    int32_t ret;
    status_t status;
    uart_transfer_t xfer;

    xfer.data = data;
    xfer.dataSize = num;

    status = UART_TransferReceiveDMA(uart->resource->base, uart->handle, &xfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_UART_TxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t UART_DmaTransfer(const void *data_out, void *data_in, uint32_t num, cmsis_uart_dma_driver_state_t *uart)
{
    /* Only in synchronous mode */
    return ARM_DRIVER_ERROR;
}

static uint32_t UART_DmaGetTxCount(cmsis_uart_dma_driver_state_t *uart)
{
    uint32_t cnt;

    /* If TX not in progress, then the TX count is txDataSizeAll saved in handle. */
    if (kStatus_NoTransferInProgress == UART_TransferGetSendCountDMA(uart->resource->base, uart->handle, &cnt))
    {
        cnt = uart->handle->txDataSizeAll;
    }

    return cnt;
}

static uint32_t UART_DmaGetRxCount(cmsis_uart_dma_driver_state_t *uart)
{
    uint32_t cnt;

    if (kStatus_NoTransferInProgress == UART_TransferGetReceiveCountDMA(uart->resource->base, uart->handle, &cnt))
    {
        cnt = uart->handle->rxDataSizeAll;
    }

    return cnt;
}

static int32_t UART_DmaControl(uint32_t control, uint32_t arg, cmsis_uart_dma_driver_state_t *uart)
{
    /* Must be power on. */
    if (!uart->isPowerOn)
    {
        return ARM_DRIVER_ERROR;
    }

    /* Does not support these features. */
    if (control & (ARM_USART_FLOW_CONTROL_Msk | ARM_USART_CPOL_Msk | ARM_USART_CPHA_Msk))
    {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    switch (control & ARM_USART_CONTROL_Msk)
    {
        /* Abort Send */
        case ARM_USART_ABORT_SEND:
            UART_TransferAbortSendDMA(uart->resource->base, uart->handle);
            return ARM_DRIVER_OK;

        /* Abort receive */
        case ARM_USART_ABORT_RECEIVE:
            UART_TransferAbortReceiveDMA(uart->resource->base, uart->handle);
            return ARM_DRIVER_OK;

        default:
            break;
    }

    return UART_CommonControl(control, arg, uart->resource, &uart->isConfigured);
}

static ARM_USART_STATUS UART_DmaGetStatus(cmsis_uart_dma_driver_state_t *uart)
{
    ARM_USART_STATUS stat;
    uint32_t ksdk_uart_status = UART_GetStatusFlags(uart->resource->base);

    stat.tx_busy = ((kuart_TxBusy == uart->handle->txState) ? (1U) : (0U));
    stat.rx_busy = ((kuart_RxBusy == uart->handle->rxState) ? (1U) : (0U));

    stat.tx_underflow = 0U;
    stat.rx_overflow = (!(!(ksdk_uart_status & kUART_RxOverrunFlag)));
#if defined(FSL_FEATURE_uart_HAS_LIN_BREAK_DETECT) && FSL_FEATURE_uart_HAS_LIN_BREAK_DETECT
    stat.rx_break = (!(!(ksdk_uart_status & kuart_LinBreakFlag)));
#else
    stat.rx_break = 0U;
#endif
    stat.rx_framing_error = (!(!(ksdk_uart_status & kUART_FramingErrorFlag)));
    stat.rx_parity_error = (!(!(ksdk_uart_status & kUART_ParityErrorFlag)));

    return stat;
}
#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
void KSDK_UART_EdmaCallback(UART_Type *base, uart_edma_handle_t *handle, status_t status, void *userData)
{
    uint32_t event;

    if (kStatus_UART_TxIdle == status)
    {
        event = ARM_USART_EVENT_SEND_COMPLETE;
    }
    else if (kStatus_UART_RxIdle == status)
    {
        event = ARM_USART_EVENT_RECEIVE_COMPLETE;
    }

    /* User data is actually CMSIS driver callback. */
    if (userData)
    {
        ((ARM_USART_SignalEvent_t)userData)(event);
    }
}

static int32_t UART_EdmaInitialize(ARM_USART_SignalEvent_t cb_event, cmsis_uart_edma_driver_state_t *uart)
{
    if (uart->isInitialized)
    {
        /* Driver is already initialized */
        return ARM_DRIVER_OK;
    }

    uart->cb_event = cb_event;
    uart->isInitialized = true;

    return ARM_DRIVER_OK;
}

static int32_t UART_EdmaUninitialize(cmsis_uart_edma_driver_state_t *uart)
{
    uart->isInitialized = false;
    return ARM_DRIVER_OK;
}

static int32_t UART_EdmaPowerControl(ARM_POWER_STATE state, cmsis_uart_edma_driver_state_t *uart)
{
    uart_config_t config;
    cmsis_uart_edma_resource_t *dmaResource;

    switch (state)
    {
        case ARM_POWER_OFF:
            if (uart->isPowerOn)
            {
                UART_Deinit(uart->resource->base);
                DMAMUX_DisableChannel(uart->dmaResource->rxDmamuxBase, uart->dmaResource->rxEdmaChannel);
                DMAMUX_DisableChannel(uart->dmaResource->txDmamuxBase, uart->dmaResource->txEdmaChannel);
                uart->isPowerOn = false;
                uart->isConfigured = false;
            }
            break;
        case ARM_POWER_LOW:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        case ARM_POWER_FULL:
            /* Must be initialized first. */
            if (!uart->isInitialized)
            {
                return ARM_DRIVER_ERROR;
            }

            if (!uart->isPowerOn)
            {
                UART_GetDefaultConfig(&config);
                config.enableTx = true;
                config.enableRx = true;

                dmaResource = uart->dmaResource;

                /* Set up EDMA setting. */
                EDMA_CreateHandle(uart->rxHandle, dmaResource->rxEdmaBase, dmaResource->rxEdmaChannel);
                DMAMUX_SetSource(dmaResource->rxDmamuxBase, dmaResource->rxEdmaChannel, dmaResource->rxDmaRequest);
                DMAMUX_EnableChannel(dmaResource->rxDmamuxBase, dmaResource->rxEdmaChannel);

                EDMA_CreateHandle(uart->txHandle, dmaResource->txEdmaBase, dmaResource->txEdmaChannel);
                DMAMUX_SetSource(dmaResource->txDmamuxBase, dmaResource->txEdmaChannel, dmaResource->txDmaRequest);
                DMAMUX_EnableChannel(dmaResource->txDmamuxBase, dmaResource->txEdmaChannel);

                /* Setup the uart. */
                UART_Init(uart->resource->base, &config, uart->resource->GetFreq());
                UART_TransferCreateHandleEDMA(uart->resource->base, uart->handle, KSDK_UART_EdmaCallback,
                                              (void *)uart->cb_event, uart->txHandle, uart->rxHandle);

                uart->isPowerOn = true;
                uart->isConfigured = true;
            }
            break;
        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    return ARM_DRIVER_OK;
}

static int32_t UART_EdmaSend(const void *data, uint32_t num, cmsis_uart_edma_driver_state_t *uart)
{
    int32_t ret;
    status_t status;
    uart_transfer_t xfer;

    xfer.data = (uint8_t *)data;
    xfer.dataSize = num;

    status = UART_SendEDMA(uart->resource->base, uart->handle, &xfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_UART_RxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t UART_EdmaReceive(void *data, uint32_t num, cmsis_uart_edma_driver_state_t *uart)
{
    int32_t ret;
    status_t status;
    uart_transfer_t xfer;

    xfer.data = data;
    xfer.dataSize = num;

    status = UART_ReceiveEDMA(uart->resource->base, uart->handle, &xfer);

    switch (status)
    {
        case kStatus_Success:
            ret = ARM_DRIVER_OK;
            break;
        case kStatus_InvalidArgument:
            ret = ARM_DRIVER_ERROR_PARAMETER;
            break;
        case kStatus_UART_RxBusy:
            ret = ARM_DRIVER_ERROR_BUSY;
            break;
        default:
            ret = ARM_DRIVER_ERROR;
            break;
    }

    return ret;
}

static int32_t UART_EdmaTransfer(const void *data_out,
                                 void *data_in,
                                 uint32_t num,
                                 cmsis_uart_edma_driver_state_t *uart)
{
    /* Only in synchronous mode */
    return ARM_DRIVER_ERROR;
}

static uint32_t UART_EdmaGetTxCount(cmsis_uart_edma_driver_state_t *uart)
{
    uint32_t cnt;

    if (kStatus_NoTransferInProgress == UART_TransferGetSendCountEDMA(uart->resource->base, uart->handle, &cnt))
    {
        cnt = uart->handle->txDataSizeAll;
    }

    return cnt;
}

static uint32_t UART_EdmaGetRxCount(cmsis_uart_edma_driver_state_t *uart)
{
    uint32_t cnt;

    if (kStatus_NoTransferInProgress == UART_TransferGetReceiveCountEDMA(uart->resource->base, uart->handle, &cnt))
    {
        cnt = uart->handle->rxDataSizeAll;
    }

    return cnt;
}

static int32_t UART_EdmaControl(uint32_t control, uint32_t arg, cmsis_uart_edma_driver_state_t *uart)
{
    /* Must be power on. */
    if (!uart->isPowerOn)
    {
        return ARM_DRIVER_ERROR;
    }

    /* Does not support these features. */
    if (control & (ARM_USART_FLOW_CONTROL_Msk | ARM_USART_CPOL_Msk | ARM_USART_CPHA_Msk))
    {
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }

    switch (control & ARM_USART_CONTROL_Msk)
    {
        /* Abort Send */
        case ARM_USART_ABORT_SEND:
            UART_TransferAbortSendEDMA(uart->resource->base, uart->handle);
            return ARM_DRIVER_OK;

        /* Abort receive */
        case ARM_USART_ABORT_RECEIVE:
            UART_TransferAbortReceiveEDMA(uart->resource->base, uart->handle);
            return ARM_DRIVER_OK;

        default:
            break;
    }

    return UART_CommonControl(control, arg, uart->resource, &uart->isConfigured);
}

static ARM_USART_STATUS UART_EdmaGetStatus(cmsis_uart_edma_driver_state_t *uart)
{
    ARM_USART_STATUS stat;
    uint32_t ksdk_uart_status = UART_GetStatusFlags(uart->resource->base);

    stat.tx_busy = ((kuart_TxBusy == uart->handle->txState) ? (1U) : (0U));
    stat.rx_busy = ((kuart_RxBusy == uart->handle->rxState) ? (1U) : (0U));

    stat.tx_underflow = 0U;
    stat.rx_overflow = (!(!(ksdk_uart_status & kUART_RxOverrunFlag)));
#if defined(FSL_FEATURE_uart_HAS_LIN_BREAK_DETECT) && FSL_FEATURE_uart_HAS_LIN_BREAK_DETECT
    stat.rx_break = (!(!(ksdk_uart_status & kUART_LinBreakFlag)));
#else
    stat.rx_break = 0U;
#endif
    stat.rx_framing_error = (!(!(ksdk_uart_status & kUART_FramingErrorFlag)));
    stat.rx_parity_error = (!(!(ksdk_uart_status & kUART_ParityErrorFlag)));

    return stat;
}
#endif

#if (FSL_FEATURE_SOC_LPSCI_COUNT == 0)

#if defined(UART0)

extern uint32_t UART0_GetFreq(void);
extern void UART0_InitPins(void);
extern void UART0_DeinitPins(void);

cmsis_uart_resource_t uart0_Resource = {UART0, UART0_GetFreq};

uart_handle_t UART0_Handle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart0_non_blocking_driver_state")
cmsis_uart_interrupt_driver_state_t uart0_NonBlockingDriverState = {
#else
cmsis_uart_interrupt_driver_state_t uart0_NonBlockingDriverState = {
#endif
    &uart0_Resource, &UART0_Handle,
};

static int32_t UART0_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART0_InitPins();
    return UART_NonBlockingInitialize(cb_event, &uart0_NonBlockingDriverState);
}

static int32_t UART0_NonBlockingUninitialize(void)
{
    UART0_DeinitPins();
    return UART_NonBlockingUninitialize(&uart0_NonBlockingDriverState);
}

static int32_t UART0_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    return UART_NonBlockingPowerControl(state, &uart0_NonBlockingDriverState);
}

static int32_t UART0_NonBlockingSend(const void *data, uint32_t num)
{
    return UART_NonBlockingSend(data, num, &uart0_NonBlockingDriverState);
}

static int32_t UART0_NonBlockingReceive(void *data, uint32_t num)
{
    return UART_NonBlockingReceive(data, num, &uart0_NonBlockingDriverState);
}

static int32_t UART0_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_NonBlockingTransfer(data_out, data_in, num, &uart0_NonBlockingDriverState);
}

static uint32_t UART0_NonBlockingGetTxCount(void)
{
    return UART_NonBlockingGetTxCount(&uart0_NonBlockingDriverState);
}

static uint32_t UART0_NonBlockingGetRxCount(void)
{
    return UART_NonBlockingGetRxCount(&uart0_NonBlockingDriverState);
}

static int32_t UART0_NonBlockingControl(uint32_t control, uint32_t arg)
{
    return UART_NonBlockingControl(control, arg, &uart0_NonBlockingDriverState);
}

static ARM_USART_STATUS UART0_NonBlockingGetStatus(void)
{
    return UART_NonBlockingGetStatus(&uart0_NonBlockingDriverState);
}

/* uart0 Driver Control Block */
ARM_DRIVER_USART UART0_NonBlocking_Driver = {UARTx_GetVersion,
                                             UARTx_GetCapabilities,
                                             UART0_NonBlockingInitialize,
                                             UART0_NonBlockingUninitialize,
                                             UART0_NonBlockingPowerControl,
                                             UART0_NonBlockingSend,
                                             UART0_NonBlockingReceive,
                                             UART0_NonBlockingTransfer,
                                             UART0_NonBlockingGetTxCount,
                                             UART0_NonBlockingGetRxCount,
                                             UART0_NonBlockingControl,
                                             UART0_NonBlockingGetStatus,
                                             UARTx_SetModemControl,
                                             UARTx_GetModemStatus};

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_uart_dma_resource_t uart0_DmaResource = {
    RTE_UART0_DMA_TX_DMA_BASE, RTE_UART0_DMA_TX_CH, RTE_UART0_DMA_TX_DMAMUX_BASE, RTE_UART0_DMA_TX_PERI_SEL,

    RTE_UART0_DMA_RX_DMA_BASE, RTE_UART0_DMA_RX_CH, RTE_UART0_DMA_RX_DMAMUX_BASE, RTE_UART0_DMA_RX_PERI_SEL,
};

uart_dma_handle_t UART0_DmaHandle;
dma_handle_t UART0_DmaRxHandle;
dma_handle_t UART0_DmaTxHandle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart0_dma_driver_state")
cmsis_uart_dma_driver_state_t uart0_DmaDriverState = {
#else
cmsis_uart_dma_driver_state_t uart0_DmaDriverState = {
#endif
    &uart0_Resource, &uart0_DmaResource, &UART0_DmaHandle, &UART0_DmaRxHandle, &UART0_DmaTxHandle,
};

static int32_t UART0_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART0_InitPins();
    return UART_DmaInitialize(cb_event, &uart0_DmaDriverState);
}

static int32_t UART0_DmaUninitialize(void)
{
    UART0_DeinitPins();
    return UART_DmaUninitialize(&uart0_DmaDriverState);
}

static int32_t UART0_DmaPowerControl(ARM_POWER_STATE state)
{
    return UART_DmaPowerControl(state, &uart0_DmaDriverState);
}

static int32_t UART0_DmaSend(const void *data, uint32_t num)
{
    return UART_DmaSend(data, num, &uart0_DmaDriverState);
}

static int32_t UART0_DmaReceive(void *data, uint32_t num)
{
    return UART_DmaReceive(data, num, &uart0_DmaDriverState);
}

static int32_t UART0_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_DmaTransfer(data_out, data_in, num, &uart0_DmaDriverState);
}

static uint32_t UART0_DmaGetTxCount(void)
{
    return UART_DmaGetTxCount(&uart0_DmaDriverState);
}

static uint32_t UART0_DmaGetRxCount(void)
{
    return UART_DmaGetRxCount(&uart0_DmaDriverState);
}

static int32_t UART0_DmaControl(uint32_t control, uint32_t arg)
{
    return UART_DmaControl(control, arg, &uart0_DmaDriverState);
}

static ARM_USART_STATUS UART0_DmaGetStatus(void)
{
    return UART_DmaGetStatus(&uart0_DmaDriverState);
}

/* uart0 Driver Control Block */
ARM_DRIVER_USART UART0_Dma_Driver = {
    UARTx_GetVersion, UARTx_GetCapabilities, UART0_DmaInitialize,   UART0_DmaUninitialize, UART0_DmaPowerControl,
    UART0_DmaSend,    UART0_DmaReceive,      UART0_DmaTransfer,     UART0_DmaGetTxCount,   UART0_DmaGetRxCount,
    UART0_DmaControl, UART0_DmaGetStatus,    UARTx_SetModemControl, UARTx_GetModemStatus};
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

cmsis_uart_edma_resource_t uart0_EdmaResource = {
    RTE_UART0_DMA_TX_DMA_BASE, RTE_UART0_DMA_TX_CH, RTE_UART0_DMA_TX_DMAMUX_BASE, RTE_UART0_DMA_TX_PERI_SEL,

    RTE_UART0_DMA_RX_DMA_BASE, RTE_UART0_DMA_RX_CH, RTE_UART0_DMA_RX_DMAMUX_BASE, RTE_UART0_DMA_RX_PERI_SEL,
};

uart_edma_handle_t UART0_EdmaHandle;
edma_handle_t UART0_EdmaRxHandle;
edma_handle_t UART0_EdmaTxHandle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart0_edma_driver_state")
cmsis_uart_edma_driver_state_t uart0_EdmaDriverState = {
#else
cmsis_uart_edma_driver_state_t uart0_EdmaDriverState = {
#endif
    &uart0_Resource, &uart0_EdmaResource, &UART0_EdmaHandle, &UART0_EdmaRxHandle, &UART0_EdmaTxHandle,
};

static int32_t UART0_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART0_InitPins();
    return UART_EdmaInitialize(cb_event, &uart0_EdmaDriverState);
}

static int32_t UART0_EdmaUninitialize(void)
{
    UART0_DeinitPins();
    return UART_EdmaUninitialize(&uart0_EdmaDriverState);
}

static int32_t UART0_EdmaPowerControl(ARM_POWER_STATE state)
{
    return UART_EdmaPowerControl(state, &uart0_EdmaDriverState);
}

static int32_t UART0_EdmaSend(const void *data, uint32_t num)
{
    return UART_EdmaSend(data, num, &uart0_EdmaDriverState);
}

static int32_t UART0_EdmaReceive(void *data, uint32_t num)
{
    return UART_EdmaReceive(data, num, &uart0_EdmaDriverState);
}

static int32_t UART0_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_EdmaTransfer(data_out, data_in, num, &uart0_EdmaDriverState);
}

static uint32_t UART0_EdmaGetTxCount(void)
{
    return UART_EdmaGetTxCount(&uart0_EdmaDriverState);
}

static uint32_t UART0_EdmaGetRxCount(void)
{
    return UART_EdmaGetRxCount(&uart0_EdmaDriverState);
}

static int32_t UART0_EdmaControl(uint32_t control, uint32_t arg)
{
    return UART_EdmaControl(control, arg, &uart0_EdmaDriverState);
}

static ARM_USART_STATUS UART0_EdmaGetStatus(void)
{
    return UART_EdmaGetStatus(&uart0_EdmaDriverState);
}

/* uart0 Driver Control Block */
ARM_DRIVER_USART UART0_Edma_Driver = {
    UARTx_GetVersion,  UARTx_GetCapabilities, UART0_EdmaInitialize,  UART0_EdmaUninitialize, UART0_EdmaPowerControl,
    UART0_EdmaSend,    UART0_EdmaReceive,     UART0_EdmaTransfer,    UART0_EdmaGetTxCount,   UART0_EdmaGetRxCount,
    UART0_EdmaControl, UART0_EdmaGetStatus,   UARTx_SetModemControl, UARTx_GetModemStatus};
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

#endif /* uart0 */

#endif

#if defined(UART1)

extern uint32_t UART1_GetFreq(void);
extern void UART1_InitPins(void);
extern void UART1_DeinitPins(void);

cmsis_uart_resource_t uart1_Resource = {UART1, UART1_GetFreq};

uart_handle_t UART1_Handle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart1_non_blocking_driver_state")
cmsis_uart_interrupt_driver_state_t uart1_NonBlockingDriverState = {
#else
cmsis_uart_interrupt_driver_state_t uart1_NonBlockingDriverState = {
#endif
    &uart1_Resource, &UART1_Handle,
};

static int32_t UART1_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART1_InitPins();
    return UART_NonBlockingInitialize(cb_event, &uart1_NonBlockingDriverState);
}

static int32_t UART1_NonBlockingUninitialize(void)
{
    UART1_DeinitPins();
    return UART_NonBlockingUninitialize(&uart1_NonBlockingDriverState);
}

static int32_t UART1_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    return UART_NonBlockingPowerControl(state, &uart1_NonBlockingDriverState);
}

static int32_t UART1_NonBlockingSend(const void *data, uint32_t num)
{
    return UART_NonBlockingSend(data, num, &uart1_NonBlockingDriverState);
}

static int32_t UART1_NonBlockingReceive(void *data, uint32_t num)
{
    return UART_NonBlockingReceive(data, num, &uart1_NonBlockingDriverState);
}

static int32_t UART1_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_NonBlockingTransfer(data_out, data_in, num, &uart1_NonBlockingDriverState);
}

static uint32_t UART1_NonBlockingGetTxCount(void)
{
    return UART_NonBlockingGetTxCount(&uart1_NonBlockingDriverState);
}

static uint32_t UART1_NonBlockingGetRxCount(void)
{
    return UART_NonBlockingGetRxCount(&uart1_NonBlockingDriverState);
}

static int32_t UART1_NonBlockingControl(uint32_t control, uint32_t arg)
{
    return UART_NonBlockingControl(control, arg, &uart1_NonBlockingDriverState);
}

static ARM_USART_STATUS UART1_NonBlockingGetStatus(void)
{
    return UART_NonBlockingGetStatus(&uart1_NonBlockingDriverState);
}

/* uart1 Driver Control Block */
ARM_DRIVER_USART UART1_NonBlocking_Driver = {UARTx_GetVersion,
                                             UARTx_GetCapabilities,
                                             UART1_NonBlockingInitialize,
                                             UART1_NonBlockingUninitialize,
                                             UART1_NonBlockingPowerControl,
                                             UART1_NonBlockingSend,
                                             UART1_NonBlockingReceive,
                                             UART1_NonBlockingTransfer,
                                             UART1_NonBlockingGetTxCount,
                                             UART1_NonBlockingGetRxCount,
                                             UART1_NonBlockingControl,
                                             UART1_NonBlockingGetStatus,
                                             UARTx_SetModemControl,
                                             UARTx_GetModemStatus};

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_uart_dma_resource_t uart1_DmaResource = {
    RTE_UART1_DMA_TX_DMA_BASE, RTE_UART1_DMA_TX_CH, RTE_UART1_DMA_TX_DMAMUX_BASE, RTE_UART1_DMA_TX_PERI_SEL,

    RTE_UART1_DMA_RX_DMA_BASE, RTE_UART1_DMA_RX_CH, RTE_UART1_DMA_RX_DMAMUX_BASE, RTE_UART1_DMA_RX_PERI_SEL,
};

uart_dma_handle_t UART1_DmaHandle;
dma_handle_t UART1_DmaRxHandle;
dma_handle_t UART1_DmaTxHandle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart1_dma_driver_state")
cmsis_uart_dma_driver_state_t uart1_DmaDriverState = {
#else
cmsis_uart_dma_driver_state_t uart1_DmaDriverState = {
#endif
    &uart1_Resource, &uart1_DmaResource, &UART1_DmaHandle, &UART1_DmaRxHandle, &UART1_DmaTxHandle,
};

static int32_t UART1_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART1_InitPins();
    return UART_DmaInitialize(cb_event, &uart1_DmaDriverState);
}

static int32_t UART1_DmaUninitialize(void)
{
    UART1_DeinitPins();
    return UART_DmaUninitialize(&uart1_DmaDriverState);
}

static int32_t UART1_DmaPowerControl(ARM_POWER_STATE state)
{
    return UART_DmaPowerControl(state, &uart1_DmaDriverState);
}

static int32_t UART1_DmaSend(const void *data, uint32_t num)
{
    return UART_DmaSend(data, num, &uart1_DmaDriverState);
}

static int32_t UART1_DmaReceive(void *data, uint32_t num)
{
    return UART_DmaReceive(data, num, &uart1_DmaDriverState);
}

static int32_t UART1_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_DmaTransfer(data_out, data_in, num, &uart1_DmaDriverState);
}

static uint32_t UART1_DmaGetTxCount(void)
{
    return UART_DmaGetTxCount(&uart1_DmaDriverState);
}

static uint32_t UART1_DmaGetRxCount(void)
{
    return UART_DmaGetRxCount(&uart1_DmaDriverState);
}

static int32_t UART1_DmaControl(uint32_t control, uint32_t arg)
{
    return UART_DmaControl(control, arg, &uart1_DmaDriverState);
}

static ARM_USART_STATUS UART1_DmaGetStatus(void)
{
    return UART_DmaGetStatus(&uart1_DmaDriverState);
}

/* uart1 Driver Control Block */
ARM_DRIVER_USART UART1_Dma_Driver = {
    UARTx_GetVersion, UARTx_GetCapabilities, UART1_DmaInitialize,   UART1_DmaUninitialize, UART1_DmaPowerControl,
    UART1_DmaSend,    UART1_DmaReceive,      UART1_DmaTransfer,     UART1_DmaGetTxCount,   UART1_DmaGetRxCount,
    UART1_DmaControl, UART1_DmaGetStatus,    UARTx_SetModemControl, UARTx_GetModemStatus};
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

cmsis_uart_edma_resource_t uart1_EdmaResource = {
    RTE_UART1_DMA_TX_DMA_BASE, RTE_UART1_DMA_TX_CH, RTE_UART1_DMA_TX_DMAMUX_BASE, RTE_UART1_DMA_TX_PERI_SEL,

    RTE_UART1_DMA_RX_DMA_BASE, RTE_UART1_DMA_RX_CH, RTE_UART1_DMA_RX_DMAMUX_BASE, RTE_UART1_DMA_RX_PERI_SEL,
};

uart_edma_handle_t UART1_EdmaHandle;
edma_handle_t UART1_EdmaRxHandle;
edma_handle_t UART1_EdmaTxHandle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart1_edma_driver_state")
cmsis_uart_edma_driver_state_t uart1_EdmaDriverState = {
#else
cmsis_uart_edma_driver_state_t uart1_EdmaDriverState = {
#endif
    &uart1_Resource, &uart1_EdmaResource, &UART1_EdmaHandle, &UART1_EdmaRxHandle, &UART1_EdmaTxHandle,
};

static int32_t UART1_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART1_InitPins();
    return UART_EdmaInitialize(cb_event, &uart1_EdmaDriverState);
}

static int32_t UART1_EdmaUninitialize(void)
{
    UART1_DeinitPins();
    return UART_EdmaUninitialize(&uart1_EdmaDriverState);
}

static int32_t UART1_EdmaPowerControl(ARM_POWER_STATE state)
{
    return UART_EdmaPowerControl(state, &uart1_EdmaDriverState);
}

static int32_t UART1_EdmaSend(const void *data, uint32_t num)
{
    return UART_EdmaSend(data, num, &uart1_EdmaDriverState);
}

static int32_t UART1_EdmaReceive(void *data, uint32_t num)
{
    return UART_EdmaReceive(data, num, &uart1_EdmaDriverState);
}

static int32_t UART1_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_EdmaTransfer(data_out, data_in, num, &uart1_EdmaDriverState);
}

static uint32_t UART1_EdmaGetTxCount(void)
{
    return UART_EdmaGetTxCount(&uart1_EdmaDriverState);
}

static uint32_t UART1_EdmaGetRxCount(void)
{
    return UART_EdmaGetRxCount(&uart1_EdmaDriverState);
}

static int32_t UART1_EdmaControl(uint32_t control, uint32_t arg)
{
    return UART_EdmaControl(control, arg, &uart1_EdmaDriverState);
}

static ARM_USART_STATUS UART1_EdmaGetStatus(void)
{
    return UART_EdmaGetStatus(&uart1_EdmaDriverState);
}

/* uart1 Driver Control Block */
ARM_DRIVER_USART UART1_Edma_Driver = {
    UARTx_GetVersion,  UARTx_GetCapabilities, UART1_EdmaInitialize,  UART1_EdmaUninitialize, UART1_EdmaPowerControl,
    UART1_EdmaSend,    UART1_EdmaReceive,     UART1_EdmaTransfer,    UART1_EdmaGetTxCount,   UART1_EdmaGetRxCount,
    UART1_EdmaControl, UART1_EdmaGetStatus,   UARTx_SetModemControl, UARTx_GetModemStatus};
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

#endif /* uart1 */

#if defined(UART2)

extern uint32_t UART2_GetFreq(void);
extern void UART2_InitPins(void);
extern void UART2_DeinitPins(void);

cmsis_uart_resource_t uart2_Resource = {UART2, UART2_GetFreq};

uart_handle_t UART2_Handle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart2_non_blocking_driver_state")
cmsis_uart_interrupt_driver_state_t uart2_NonBlockingDriverState = {
#else
cmsis_uart_interrupt_driver_state_t uart2_NonBlockingDriverState = {
#endif
    &uart2_Resource, &UART2_Handle,
};

static int32_t UART2_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART2_InitPins();
    return UART_NonBlockingInitialize(cb_event, &uart2_NonBlockingDriverState);
}

static int32_t UART2_NonBlockingUninitialize(void)
{
    UART2_DeinitPins();
    return UART_NonBlockingUninitialize(&uart2_NonBlockingDriverState);
}

static int32_t UART2_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    return UART_NonBlockingPowerControl(state, &uart2_NonBlockingDriverState);
}

static int32_t UART2_NonBlockingSend(const void *data, uint32_t num)
{
    return UART_NonBlockingSend(data, num, &uart2_NonBlockingDriverState);
}

static int32_t UART2_NonBlockingReceive(void *data, uint32_t num)
{
    return UART_NonBlockingReceive(data, num, &uart2_NonBlockingDriverState);
}

static int32_t UART2_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_NonBlockingTransfer(data_out, data_in, num, &uart2_NonBlockingDriverState);
}

static uint32_t UART2_NonBlockingGetTxCount(void)
{
    return UART_NonBlockingGetTxCount(&uart2_NonBlockingDriverState);
}

static uint32_t UART2_NonBlockingGetRxCount(void)
{
    return UART_NonBlockingGetRxCount(&uart2_NonBlockingDriverState);
}

static int32_t UART2_NonBlockingControl(uint32_t control, uint32_t arg)
{
    return UART_NonBlockingControl(control, arg, &uart2_NonBlockingDriverState);
}

static ARM_USART_STATUS UART2_NonBlockingGetStatus(void)
{
    return UART_NonBlockingGetStatus(&uart2_NonBlockingDriverState);
}

/* uart2 Driver Control Block */
ARM_DRIVER_USART UART2_NonBlocking_Driver = {UARTx_GetVersion,
                                             UARTx_GetCapabilities,
                                             UART2_NonBlockingInitialize,
                                             UART2_NonBlockingUninitialize,
                                             UART2_NonBlockingPowerControl,
                                             UART2_NonBlockingSend,
                                             UART2_NonBlockingReceive,
                                             UART2_NonBlockingTransfer,
                                             UART2_NonBlockingGetTxCount,
                                             UART2_NonBlockingGetRxCount,
                                             UART2_NonBlockingControl,
                                             UART2_NonBlockingGetStatus,
                                             UARTx_SetModemControl,
                                             UARTx_GetModemStatus};

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_uart_dma_resource_t uart2_DmaResource = {
    RTE_UART2_DMA_TX_DMA_BASE, RTE_UART2_DMA_TX_CH, RTE_UART2_DMA_TX_DMAMUX_BASE, RTE_UART2_DMA_TX_PERI_SEL,

    RTE_UART2_DMA_RX_DMA_BASE, RTE_UART2_DMA_RX_CH, RTE_UART2_DMA_RX_DMAMUX_BASE, RTE_UART2_DMA_RX_PERI_SEL,
};

uart_dma_handle_t UART2_DmaHandle;
dma_handle_t UART2_DmaRxHandle;
dma_handle_t UART2_DmaTxHandle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart2_dma_driver_state")
cmsis_uart_dma_driver_state_t uart2_DmaDriverState = {
#else
cmsis_uart_dma_driver_state_t uart2_DmaDriverState = {
#endif
    &uart2_Resource, &uart2_DmaResource, &UART2_DmaHandle, &UART2_DmaRxHandle, &UART2_DmaTxHandle,
};

static int32_t UART2_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART2_InitPins();
    return UART_DmaInitialize(cb_event, &uart2_DmaDriverState);
}

static int32_t UART2_DmaUninitialize(void)
{
    UART2_DeinitPins();
    return UART_DmaUninitialize(&uart2_DmaDriverState);
}

static int32_t UART2_DmaPowerControl(ARM_POWER_STATE state)
{
    return UART_DmaPowerControl(state, &uart2_DmaDriverState);
}

static int32_t UART2_DmaSend(const void *data, uint32_t num)
{
    return UART_DmaSend(data, num, &uart2_DmaDriverState);
}

static int32_t UART2_DmaReceive(void *data, uint32_t num)
{
    return UART_DmaReceive(data, num, &uart2_DmaDriverState);
}

static int32_t UART2_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_DmaTransfer(data_out, data_in, num, &uart2_DmaDriverState);
}

static uint32_t UART2_DmaGetTxCount(void)
{
    return UART_DmaGetTxCount(&uart2_DmaDriverState);
}

static uint32_t UART2_DmaGetRxCount(void)
{
    return UART_DmaGetRxCount(&uart2_DmaDriverState);
}

static int32_t UART2_DmaControl(uint32_t control, uint32_t arg)
{
    return UART_DmaControl(control, arg, &uart2_DmaDriverState);
}

static ARM_USART_STATUS UART2_DmaGetStatus(void)
{
    return UART_DmaGetStatus(&uart2_DmaDriverState);
}

/* uart2 Driver Control Block */
ARM_DRIVER_USART UART2_Dma_Driver = {
    UARTx_GetVersion, UARTx_GetCapabilities, UART2_DmaInitialize,   UART2_DmaUninitialize, UART2_DmaPowerControl,
    UART2_DmaSend,    UART2_DmaReceive,      UART2_DmaTransfer,     UART2_DmaGetTxCount,   UART2_DmaGetRxCount,
    UART2_DmaControl, UART2_DmaGetStatus,    UARTx_SetModemControl, UARTx_GetModemStatus};
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

cmsis_uart_edma_resource_t uart2_EdmaResource = {
    RTE_UART2_DMA_TX_DMA_BASE, RTE_UART2_DMA_TX_CH, RTE_UART2_DMA_TX_DMAMUX_BASE, RTE_UART2_DMA_TX_PERI_SEL,

    RTE_UART2_DMA_RX_DMA_BASE, RTE_UART2_DMA_RX_CH, RTE_UART2_DMA_RX_DMAMUX_BASE, RTE_UART2_DMA_RX_PERI_SEL,
};

uart_edma_handle_t UART2_EdmaHandle;
edma_handle_t UART2_EdmaRxHandle;
edma_handle_t UART2_EdmaTxHandle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart2_edma_driver_state")
cmsis_uart_edma_driver_state_t uart2_EdmaDriverState = {
#else
cmsis_uart_edma_driver_state_t uart2_EdmaDriverState = {
#endif
    &uart2_Resource, &uart2_EdmaResource, &UART2_EdmaHandle, &UART2_EdmaRxHandle, &UART2_EdmaTxHandle,
};

static int32_t UART2_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART2_InitPins();
    return UART_EdmaInitialize(cb_event, &uart2_EdmaDriverState);
}

static int32_t UART2_EdmaUninitialize(void)
{
    UART2_DeinitPins();
    return UART_EdmaUninitialize(&uart2_EdmaDriverState);
}

static int32_t UART2_EdmaPowerControl(ARM_POWER_STATE state)
{
    return UART_EdmaPowerControl(state, &uart2_EdmaDriverState);
}

static int32_t UART2_EdmaSend(const void *data, uint32_t num)
{
    return UART_EdmaSend(data, num, &uart2_EdmaDriverState);
}

static int32_t UART2_EdmaReceive(void *data, uint32_t num)
{
    return UART_EdmaReceive(data, num, &uart2_EdmaDriverState);
}

static int32_t UART2_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_EdmaTransfer(data_out, data_in, num, &uart2_EdmaDriverState);
}

static uint32_t UART2_EdmaGetTxCount(void)
{
    return UART_EdmaGetTxCount(&uart2_EdmaDriverState);
}

static uint32_t UART2_EdmaGetRxCount(void)
{
    return UART_EdmaGetRxCount(&uart2_EdmaDriverState);
}

static int32_t UART2_EdmaControl(uint32_t control, uint32_t arg)
{
    return UART_EdmaControl(control, arg, &uart2_EdmaDriverState);
}

static ARM_USART_STATUS UART2_EdmaGetStatus(void)
{
    return UART_EdmaGetStatus(&uart2_EdmaDriverState);
}

/* uart2 Driver Control Block */
ARM_DRIVER_USART UART2_Edma_Driver = {
    UARTx_GetVersion,  UARTx_GetCapabilities, UART2_EdmaInitialize,  UART2_EdmaUninitialize, UART2_EdmaPowerControl,
    UART2_EdmaSend,    UART2_EdmaReceive,     UART2_EdmaTransfer,    UART2_EdmaGetTxCount,   UART2_EdmaGetRxCount,
    UART2_EdmaControl, UART2_EdmaGetStatus,   UARTx_SetModemControl, UARTx_GetModemStatus};
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

#endif /* uart2 */

#if defined(UART3)

extern uint32_t UART3_GetFreq(void);
extern void UART3_InitPins(void);
extern void UART3_DeinitPins(void);

cmsis_uart_resource_t uart3_Resource = {UART3, UART3_GetFreq};

uart_handle_t UART3_Handle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart3_non_blocking_driver_state")
cmsis_uart_interrupt_driver_state_t uart3_NonBlockingDriverState = {
#else
cmsis_uart_interrupt_driver_state_t uart3_NonBlockingDriverState = {
#endif
    &uart3_Resource, &UART3_Handle,
};

static int32_t UART3_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART3_InitPins();
    return UART_NonBlockingInitialize(cb_event, &uart3_NonBlockingDriverState);
}

static int32_t UART3_NonBlockingUninitialize(void)
{
    UART3_DeinitPins();
    return UART_NonBlockingUninitialize(&uart3_NonBlockingDriverState);
}

static int32_t UART3_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    return UART_NonBlockingPowerControl(state, &uart3_NonBlockingDriverState);
}

static int32_t UART3_NonBlockingSend(const void *data, uint32_t num)
{
    return UART_NonBlockingSend(data, num, &uart3_NonBlockingDriverState);
}

static int32_t UART3_NonBlockingReceive(void *data, uint32_t num)
{
    return UART_NonBlockingReceive(data, num, &uart3_NonBlockingDriverState);
}

static int32_t UART3_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_NonBlockingTransfer(data_out, data_in, num, &uart3_NonBlockingDriverState);
}

static uint32_t UART3_NonBlockingGetTxCount(void)
{
    return UART_NonBlockingGetTxCount(&uart3_NonBlockingDriverState);
}

static uint32_t UART3_NonBlockingGetRxCount(void)
{
    return UART_NonBlockingGetRxCount(&uart3_NonBlockingDriverState);
}

static int32_t UART3_NonBlockingControl(uint32_t control, uint32_t arg)
{
    return UART_NonBlockingControl(control, arg, &uart3_NonBlockingDriverState);
}

static ARM_USART_STATUS UART3_NonBlockingGetStatus(void)
{
    return UART_NonBlockingGetStatus(&uart3_NonBlockingDriverState);
}

/* uart3 Driver Control Block */
ARM_DRIVER_USART UART3_NonBlocking_Driver = {UARTx_GetVersion,
                                             UARTx_GetCapabilities,
                                             UART3_NonBlockingInitialize,
                                             UART3_NonBlockingUninitialize,
                                             UART3_NonBlockingPowerControl,
                                             UART3_NonBlockingSend,
                                             UART3_NonBlockingReceive,
                                             UART3_NonBlockingTransfer,
                                             UART3_NonBlockingGetTxCount,
                                             UART3_NonBlockingGetRxCount,
                                             UART3_NonBlockingControl,
                                             UART3_NonBlockingGetStatus,
                                             UARTx_SetModemControl,
                                             UARTx_GetModemStatus};

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_uart_dma_resource_t uart3_DmaResource = {
    RTE_UART3_DMA_TX_DMA_BASE, RTE_UART3_DMA_TX_CH, RTE_UART3_DMA_TX_DMAMUX_BASE, RTE_UART3_DMA_TX_PERI_SEL,

    RTE_UART3_DMA_RX_DMA_BASE, RTE_UART3_DMA_RX_CH, RTE_UART3_DMA_RX_DMAMUX_BASE, RTE_UART3_DMA_RX_PERI_SEL,
};

uart_dma_handle_t UART3_DmaHandle;
dma_handle_t UART3_DmaRxHandle;
dma_handle_t UART3_DmaTxHandle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart3_dma_driver_state")
cmsis_uart_dma_driver_state_t uart3_DmaDriverState = {
#else
cmsis_uart_dma_driver_state_t uart3_DmaDriverState = {
#endif
    &uart3_Resource, &uart3_DmaResource, &UART3_DmaHandle, &UART3_DmaRxHandle, &UART3_DmaTxHandle};

static int32_t UART3_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART3_InitPins();
    return UART_DmaInitialize(cb_event, &uart3_DmaDriverState);
}

static int32_t UART3_DmaUninitialize(void)
{
    UART3_DeinitPins();
    return UART_DmaUninitialize(&uart3_DmaDriverState);
}

static int32_t UART3_DmaPowerControl(ARM_POWER_STATE state)
{
    return UART_DmaPowerControl(state, &uart3_DmaDriverState);
}

static int32_t UART3_DmaSend(const void *data, uint32_t num)
{
    return UART_DmaSend(data, num, &uart3_DmaDriverState);
}

static int32_t UART3_DmaReceive(void *data, uint32_t num)
{
    return UART_DmaReceive(data, num, &uart3_DmaDriverState);
}

static int32_t UART3_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_DmaTransfer(data_out, data_in, num, &uart3_DmaDriverState);
}

static uint32_t UART3_DmaGetTxCount(void)
{
    return UART_DmaGetTxCount(&uart3_DmaDriverState);
}

static uint32_t UART3_DmaGetRxCount(void)
{
    return UART_DmaGetRxCount(&uart3_DmaDriverState);
}

static int32_t UART3_DmaControl(uint32_t control, uint32_t arg)
{
    return UART_DmaControl(control, arg, &uart3_DmaDriverState);
}

static ARM_USART_STATUS UART3_DmaGetStatus(void)
{
    return UART_DmaGetStatus(&uart3_DmaDriverState);
}

/* uart3 Driver Control Block */
ARM_DRIVER_USART UART3_Dma_Driver = {
    UARTx_GetVersion, UARTx_GetCapabilities, UART3_DmaInitialize,   UART3_DmaUninitialize, UART3_DmaPowerControl,
    UART3_DmaSend,    UART3_DmaReceive,      UART3_DmaTransfer,     UART3_DmaGetTxCount,   UART3_DmaGetRxCount,
    UART3_DmaControl, UART3_DmaGetStatus,    UARTx_SetModemControl, UARTx_GetModemStatus};
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

cmsis_uart_edma_resource_t uart3_EdmaResource = {
    RTE_UART3_DMA_TX_DMA_BASE, RTE_UART3_DMA_TX_CH, RTE_UART3_DMA_TX_DMAMUX_BASE, RTE_UART3_DMA_TX_PERI_SEL,

    RTE_UART3_DMA_RX_DMA_BASE, RTE_UART3_DMA_RX_CH, RTE_UART3_DMA_RX_DMAMUX_BASE, RTE_UART3_DMA_RX_PERI_SEL,
};

uart_edma_handle_t UART3_EdmaHandle;
edma_handle_t UART3_EdmaRxHandle;
edma_handle_t UART3_EdmaTxHandle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart3_edma_driver_state")
cmsis_uart_edma_driver_state_t uart3_EdmaDriverState = {
#else
cmsis_uart_edma_driver_state_t uart3_EdmaDriverState = {
#endif
    &uart3_Resource, &uart3_EdmaResource, &UART3_EdmaHandle, &UART3_EdmaRxHandle, &UART3_EdmaTxHandle,
};

static int32_t UART3_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART3_InitPins();
    return UART_EdmaInitialize(cb_event, &uart3_EdmaDriverState);
}

static int32_t UART3_EdmaUninitialize(void)
{
    UART3_DeinitPins();
    return UART_EdmaUninitialize(&uart3_EdmaDriverState);
}

static int32_t UART3_EdmaPowerControl(ARM_POWER_STATE state)
{
    return UART_EdmaPowerControl(state, &uart3_EdmaDriverState);
}

static int32_t UART3_EdmaSend(const void *data, uint32_t num)
{
    return UART_EdmaSend(data, num, &uart3_EdmaDriverState);
}

static int32_t UART3_EdmaReceive(void *data, uint32_t num)
{
    return UART_EdmaReceive(data, num, &uart3_EdmaDriverState);
}

static int32_t UART3_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_EdmaTransfer(data_out, data_in, num, &uart3_EdmaDriverState);
}

static uint32_t UART3_EdmaGetTxCount(void)
{
    return UART_EdmaGetTxCount(&uart3_EdmaDriverState);
}

static uint32_t UART3_EdmaGetRxCount(void)
{
    return UART_EdmaGetRxCount(&uart3_EdmaDriverState);
}

static int32_t UART3_EdmaControl(uint32_t control, uint32_t arg)
{
    return UART_EdmaControl(control, arg, &uart3_EdmaDriverState);
}

static ARM_USART_STATUS UART3_EdmaGetStatus(void)
{
    return UART_EdmaGetStatus(&uart3_EdmaDriverState);
}

/* uart3 Driver Control Block */
ARM_DRIVER_USART UART3_Edma_Driver = {
    UARTx_GetVersion,  UARTx_GetCapabilities, UART3_EdmaInitialize,  UART3_EdmaUninitialize, UART3_EdmaPowerControl,
    UART3_EdmaSend,    UART3_EdmaReceive,     UART3_EdmaTransfer,    UART3_EdmaGetTxCount,   UART3_EdmaGetRxCount,
    UART3_EdmaControl, UART3_EdmaGetStatus,   UARTx_SetModemControl, UARTx_GetModemStatus};
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

#endif /* uart3 */

#if defined(UART4)

extern uint32_t UART4_GetFreq(void);
extern void UART4_InitPins(void);
extern void UART4_DeinitPins(void);

cmsis_uart_resource_t uart4_Resource = {UART4, UART4_GetFreq};

uart_handle_t UART4_Handle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart4_non_blocking_driver_state")
cmsis_uart_interrupt_driver_state_t uart4_NonBlockingDriverState = {
#else
cmsis_uart_interrupt_driver_state_t uart4_NonBlockingDriverState = {
#endif
    &uart4_Resource, &UART4_Handle,
};

static int32_t UART4_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART4_InitPins();
    return UART_NonBlockingInitialize(cb_event, &uart4_NonBlockingDriverState);
}

static int32_t UART4_NonBlockingUninitialize(void)
{
    UART4_DeinitPins();
    return UART_NonBlockingUninitialize(&uart4_NonBlockingDriverState);
}

static int32_t UART4_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    return UART_NonBlockingPowerControl(state, &uart4_NonBlockingDriverState);
}

static int32_t UART4_NonBlockingSend(const void *data, uint32_t num)
{
    return UART_NonBlockingSend(data, num, &uart4_NonBlockingDriverState);
}

static int32_t UART4_NonBlockingReceive(void *data, uint32_t num)
{
    return UART_NonBlockingReceive(data, num, &uart4_NonBlockingDriverState);
}

static int32_t UART4_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_NonBlockingTransfer(data_out, data_in, num, &uart4_NonBlockingDriverState);
}

static uint32_t UART4_NonBlockingGetTxCount(void)
{
    return UART_NonBlockingGetTxCount(&uart4_NonBlockingDriverState);
}

static uint32_t UART4_NonBlockingGetRxCount(void)
{
    return UART_NonBlockingGetRxCount(&uart4_NonBlockingDriverState);
}

static int32_t UART4_NonBlockingControl(uint32_t control, uint32_t arg)
{
    return UART_NonBlockingControl(control, arg, &uart4_NonBlockingDriverState);
}

static ARM_USART_STATUS UART4_NonBlockingGetStatus(void)
{
    return UART_NonBlockingGetStatus(&uart4_NonBlockingDriverState);
}

/* uart4 Driver Control Block */
ARM_DRIVER_USART UART4_NonBlocking_Driver = {UARTx_GetVersion,
                                             UARTx_GetCapabilities,
                                             UART4_NonBlockingInitialize,
                                             UART4_NonBlockingUninitialize,
                                             UART4_NonBlockingPowerControl,
                                             UART4_NonBlockingSend,
                                             UART4_NonBlockingReceive,
                                             UART4_NonBlockingTransfer,
                                             UART4_NonBlockingGetTxCount,
                                             UART4_NonBlockingGetRxCount,
                                             UART4_NonBlockingControl,
                                             UART4_NonBlockingGetStatus,
                                             UARTx_SetModemControl,
                                             UARTx_GetModemStatus};

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_uart_dma_resource_t uart4_DmaResource = {
    RTE_UART4_DMA_TX_DMA_BASE, RTE_UART4_DMA_TX_CH, RTE_UART4_DMA_TX_DMAMUX_BASE, RTE_UART4_DMA_TX_PERI_SEL,

    RTE_UART4_DMA_RX_DMA_BASE, RTE_UART4_DMA_RX_CH, RTE_UART4_DMA_RX_DMAMUX_BASE, RTE_UART4_DMA_RX_PERI_SEL,
};

uart_dma_handle_t UART4_DmaHandle;
dma_handle_t UART4_DmaRxHandle;
dma_handle_t UART4_DmaTxHandle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart4_dma_driver_state")
cmsis_uart_dma_driver_state_t uart4_DmaDriverState = {
#else
cmsis_uart_dma_driver_state_t uart4_DmaDriverState = {
#endif
    &uart4_Resource, &uart4_DmaResource, &UART4_DmaHandle, &UART4_DmaRxHandle, &UART4_DmaTxHandle,
};

static int32_t UART4_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART4_InitPins();
    return UART_DmaInitialize(cb_event, &uart4_DmaDriverState);
}

static int32_t UART4_DmaUninitialize(void)
{
    UART4_DeinitPins();
    return UART_DmaUninitialize(&uart4_DmaDriverState);
}

static int32_t UART4_DmaPowerControl(ARM_POWER_STATE state)
{
    return UART_DmaPowerControl(state, &uart4_DmaDriverState);
}

static int32_t UART4_DmaSend(const void *data, uint32_t num)
{
    return UART_DmaSend(data, num, &uart4_DmaDriverState);
}

static int32_t UART4_DmaReceive(void *data, uint32_t num)
{
    return UART_DmaReceive(data, num, &uart4_DmaDriverState);
}

static int32_t UART4_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_DmaTransfer(data_out, data_in, num, &uart4_DmaDriverState);
}

static uint32_t UART4_DmaGetTxCount(void)
{
    return UART_DmaGetTxCount(&uart4_DmaDriverState);
}

static uint32_t UART4_DmaGetRxCount(void)
{
    return UART_DmaGetRxCount(&uart4_DmaDriverState);
}

static int32_t UART4_DmaControl(uint32_t control, uint32_t arg)
{
    return UART_DmaControl(control, arg, &uart4_DmaDriverState);
}

static ARM_USART_STATUS UART4_DmaGetStatus(void)
{
    return UART_DmaGetStatus(&uart4_DmaDriverState);
}

/* uart4 Driver Control Block */
ARM_DRIVER_USART UART4_Dma_Driver = {
    UARTx_GetVersion, UARTx_GetCapabilities, UART4_DmaInitialize,   UART4_DmaUninitialize, UART4_DmaPowerControl,
    UART4_DmaSend,    UART4_DmaReceive,      UART4_DmaTransfer,     UART4_DmaGetTxCount,   UART4_DmaGetRxCount,
    UART4_DmaControl, UART4_DmaGetStatus,    UARTx_SetModemControl, UARTx_GetModemStatus};
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

cmsis_uart_edma_resource_t uart4_EdmaResource = {
    RTE_UART4_DMA_TX_DMA_BASE, RTE_UART4_DMA_TX_CH, RTE_UART4_DMA_TX_DMAMUX_BASE, RTE_UART4_DMA_TX_PERI_SEL,

    RTE_UART4_DMA_RX_DMA_BASE, RTE_UART4_DMA_RX_CH, RTE_UART4_DMA_RX_DMAMUX_BASE, RTE_UART4_DMA_RX_PERI_SEL,
};

uart_edma_handle_t UART4_EdmaHandle;
edma_handle_t UART4_EdmaRxHandle;
edma_handle_t UART4_EdmaTxHandle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart4_edma_driver_state")
cmsis_uart_edma_driver_state_t uart4_EdmaDriverState = {
#else
cmsis_uart_edma_driver_state_t uart4_EdmaDriverState = {
#endif
    &uart4_Resource, &uart4_EdmaResource, &UART4_EdmaHandle, &UART4_EdmaRxHandle, &UART4_EdmaTxHandle,
};

static int32_t UART4_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART4_InitPins();
    return UART_EdmaInitialize(cb_event, &uart4_EdmaDriverState);
}

static int32_t UART4_EdmaUninitialize(void)
{
    UART4_DeinitPins();
    return UART_EdmaUninitialize(&uart4_EdmaDriverState);
}

static int32_t UART4_EdmaPowerControl(ARM_POWER_STATE state)
{
    return UART_EdmaPowerControl(state, &uart4_EdmaDriverState);
}

static int32_t UART4_EdmaSend(const void *data, uint32_t num)
{
    return UART_EdmaSend(data, num, &uart4_EdmaDriverState);
}

static int32_t UART4_EdmaReceive(void *data, uint32_t num)
{
    return UART_EdmaReceive(data, num, &uart4_EdmaDriverState);
}

static int32_t UART4_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_EdmaTransfer(data_out, data_in, num, &uart4_EdmaDriverState);
}

static uint32_t UART4_EdmaGetTxCount(void)
{
    return UART_EdmaGetTxCount(&uart4_EdmaDriverState);
}

static uint32_t UART4_EdmaGetRxCount(void)
{
    return UART_EdmaGetRxCount(&uart4_EdmaDriverState);
}

static int32_t UART4_EdmaControl(uint32_t control, uint32_t arg)
{
    return UART_EdmaControl(control, arg, &uart4_EdmaDriverState);
}

static ARM_USART_STATUS UART4_EdmaGetStatus(void)
{
    return UART_EdmaGetStatus(&uart4_EdmaDriverState);
}

/* uart4 Driver Control Block */
ARM_DRIVER_USART UART4_Edma_Driver = {
    UARTx_GetVersion,  UARTx_GetCapabilities, UART4_EdmaInitialize,  UART4_EdmaUninitialize, UART4_EdmaPowerControl,
    UART4_EdmaSend,    UART4_EdmaReceive,     UART4_EdmaTransfer,    UART4_EdmaGetTxCount,   UART4_EdmaGetRxCount,
    UART4_EdmaControl, UART4_EdmaGetStatus,   UARTx_SetModemControl, UARTx_GetModemStatus};
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

#endif /* uart4 */

#if defined(UART5)

extern uint32_t UART5_GetFreq(void);
extern void UART5_InitPins(void);
extern void UART5_DeinitPins(void);

cmsis_uart_resource_t uart5_Resource = {UART5, UART5_GetFreq};

uart_handle_t UART5_Handle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart5_non_blocking_driver_state")
cmsis_uart_interrupt_driver_state_t uart5_NonBlockingDriverState = {
#else
cmsis_uart_interrupt_driver_state_t uart5_NonBlockingDriverState = {
#endif
    &uart5_Resource, &UART5_Handle,
};

static int32_t UART5_NonBlockingInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART5_InitPins();
    return UART_NonBlockingInitialize(cb_event, &uart5_NonBlockingDriverState);
}

static int32_t UART5_NonBlockingUninitialize(void)
{
    UART5_DeinitPins();
    return UART_NonBlockingUninitialize(&uart5_NonBlockingDriverState);
}

static int32_t UART5_NonBlockingPowerControl(ARM_POWER_STATE state)
{
    return UART_NonBlockingPowerControl(state, &uart5_NonBlockingDriverState);
}

static int32_t UART5_NonBlockingSend(const void *data, uint32_t num)
{
    return UART_NonBlockingSend(data, num, &uart5_NonBlockingDriverState);
}

static int32_t UART5_NonBlockingReceive(void *data, uint32_t num)
{
    return UART_NonBlockingReceive(data, num, &uart5_NonBlockingDriverState);
}

static int32_t UART5_NonBlockingTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_NonBlockingTransfer(data_out, data_in, num, &uart5_NonBlockingDriverState);
}

static uint32_t UART5_NonBlockingGetTxCount(void)
{
    return UART_NonBlockingGetTxCount(&uart5_NonBlockingDriverState);
}

static uint32_t UART5_NonBlockingGetRxCount(void)
{
    return UART_NonBlockingGetRxCount(&uart5_NonBlockingDriverState);
}

static int32_t UART5_NonBlockingControl(uint32_t control, uint32_t arg)
{
    return UART_NonBlockingControl(control, arg, &uart5_NonBlockingDriverState);
}

static ARM_USART_STATUS UART5_NonBlockingGetStatus(void)
{
    return UART_NonBlockingGetStatus(&uart5_NonBlockingDriverState);
}

/* uart5 Driver Control Block */
ARM_DRIVER_USART UART5_NonBlocking_Driver = {UARTx_GetVersion,
                                             UARTx_GetCapabilities,
                                             UART5_NonBlockingInitialize,
                                             UART5_NonBlockingUninitialize,
                                             UART5_NonBlockingPowerControl,
                                             UART5_NonBlockingSend,
                                             UART5_NonBlockingReceive,
                                             UART5_NonBlockingTransfer,
                                             UART5_NonBlockingGetTxCount,
                                             UART5_NonBlockingGetRxCount,
                                             UART5_NonBlockingControl,
                                             UART5_NonBlockingGetStatus,
                                             UARTx_SetModemControl,
                                             UARTx_GetModemStatus};

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

cmsis_uart_dma_resource_t uart5_DmaResource = {
    RTE_UART5_DMA_TX_DMA_BASE, RTE_UART5_DMA_TX_CH, RTE_UART5_DMA_TX_DMAMUX_BASE, RTE_UART5_DMA_TX_PERI_SEL,

    RTE_UART5_DMA_RX_DMA_BASE, RTE_UART5_DMA_RX_CH, RTE_UART5_DMA_RX_DMAMUX_BASE, RTE_UART5_DMA_RX_PERI_SEL,
};

uart_dma_handle_t UART5_DmaHandle;
dma_handle_t UART5_DmaRxHandle;
dma_handle_t UART5_DmaTxHandle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart5_dma_driver_state")
cmsis_uart_dma_driver_state_t uart5_DmaDriverState = {
#else
cmsis_uart_dma_driver_state_t uart5_DmaDriverState = {
#endif
    &uart5_Resource, &uart5_DmaResource, &UART5_DmaHandle, &UART5_DmaRxHandle, UART5_DmaTxHandle,
};

static int32_t UART5_DmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART5_InitPins();
    return UART_DmaInitialize(cb_event, &uart5_DmaDriverState);
}

static int32_t UART5_DmaUninitialize(void)
{
    UART5_DeinitPins();
    return UART_DmaUninitialize(&uart5_DmaDriverState);
}

static int32_t UART5_DmaPowerControl(ARM_POWER_STATE state)
{
    return UART_DmaPowerControl(state, &uart5_DmaDriverState);
}

static int32_t UART5_DmaSend(const void *data, uint32_t num)
{
    return UART_DmaSend(data, num, &uart5_DmaDriverState);
}

static int32_t UART5_DmaReceive(void *data, uint32_t num)
{
    return UART_DmaReceive(data, num, &uart5_DmaDriverState);
}

static int32_t UART5_DmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_DmaTransfer(data_out, data_in, num, &uart5_DmaDriverState);
}

static uint32_t UART5_DmaGetTxCount(void)
{
    return UART_DmaGetTxCount(&uart5_DmaDriverState);
}

static uint32_t UART5_DmaGetRxCount(void)
{
    return UART_DmaGetRxCount(&uart5_DmaDriverState);
}

static int32_t UART5_DmaControl(uint32_t control, uint32_t arg)
{
    return UART_DmaControl(control, arg, &uart5_DmaDriverState);
}

static ARM_USART_STATUS UART5_DmaGetStatus(void)
{
    return UART_DmaGetStatus(&uart5_DmaDriverState);
}

/* uart5 Driver Control Block */
ARM_DRIVER_USART UART5_Dma_Driver = {
    UARTx_GetVersion, UARTx_GetCapabilities, UART5_DmaInitialize,   UART5_DmaUninitialize, UART5_DmaPowerControl,
    UART5_DmaSend,    UART5_DmaReceive,      UART5_DmaTransfer,     UART5_DmaGetTxCount,   UART5_DmaGetRxCount,
    UART5_DmaControl, UART5_DmaGetStatus,    UARTx_SetModemControl, UARTx_GetModemStatus};
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

cmsis_uart_edma_resource_t uart5_EdmaResource = {
    RTE_UART5_DMA_TX_DMA_BASE, RTE_UART5_DMA_TX_CH, RTE_UART5_DMA_TX_DMAMUX_BASE, RTE_UART5_DMA_TX_PERI_SEL,

    RTE_UART5_DMA_RX_DMA_BASE, RTE_UART5_DMA_RX_CH, RTE_UART5_DMA_RX_DMAMUX_BASE, RTE_UART5_DMA_RX_PERI_SEL,
};

uart_edma_handle_t UART5_EdmaHandle;
edma_handle_t UART5_EdmaRxHandle;
edma_handle_t UART5_EdmaTxHandle;

#if defined(__CC_ARM)
ARMCC_SECTION("uart5_edma_driver_state")
cmsis_uart_edma_driver_state_t uart5_EdmaDriverState = {
#else
cmsis_uart_edma_driver_state_t uart5_EdmaDriverState = {
#endif
    &uart5_Resource, &uart5_EdmaResource, &UART5_EdmaHandle, &UART5_EdmaRxHandle, &UART5_EdmaTxHandle,
};

static int32_t UART5_EdmaInitialize(ARM_USART_SignalEvent_t cb_event)
{
    UART5_InitPins();
    return UART_EdmaInitialize(cb_event, &uart5_EdmaDriverState);
}

static int32_t UART5_EdmaUninitialize(void)
{
    UART5_DeinitPins();
    return UART_EdmaUninitialize(&uart5_EdmaDriverState);
}

static int32_t UART5_EdmaPowerControl(ARM_POWER_STATE state)
{
    return UART_EdmaPowerControl(state, &uart5_EdmaDriverState);
}

static int32_t UART5_EdmaSend(const void *data, uint32_t num)
{
    return UART_EdmaSend(data, num, &uart5_EdmaDriverState);
}

static int32_t UART5_EdmaReceive(void *data, uint32_t num)
{
    return UART_EdmaReceive(data, num, &uart5_EdmaDriverState);
}

static int32_t UART5_EdmaTransfer(const void *data_out, void *data_in, uint32_t num)
{
    return UART_EdmaTransfer(data_out, data_in, num, &uart5_EdmaDriverState);
}

static uint32_t UART5_EdmaGetTxCount(void)
{
    return UART_EdmaGetTxCount(&uart5_EdmaDriverState);
}

static uint32_t UART5_EdmaGetRxCount(void)
{
    return UART_EdmaGetRxCount(&uart5_EdmaDriverState);
}

static int32_t UART5_EdmaControl(uint32_t control, uint32_t arg)
{
    return UART_EdmaControl(control, arg, &uart5_EdmaDriverState);
}

static ARM_USART_STATUS UART5_EdmaGetStatus(void)
{
    return UART_EdmaGetStatus(&uart5_EdmaDriverState);
}

/* uart5 Driver Control Block */
ARM_DRIVER_USART UART5_Edma_Driver = {
    UARTx_GetVersion,  UARTx_GetCapabilities, UART5_EdmaInitialize,  UART5_EdmaUninitialize, UART5_EdmaPowerControl,
    UART5_EdmaSend,    UART5_EdmaReceive,     UART5_EdmaTransfer,    UART5_EdmaGetTxCount,   UART5_EdmaGetRxCount,
    UART5_EdmaControl, UART5_EdmaGetStatus,   UARTx_SetModemControl, UARTx_GetModemStatus};
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

#endif /* uart5 */