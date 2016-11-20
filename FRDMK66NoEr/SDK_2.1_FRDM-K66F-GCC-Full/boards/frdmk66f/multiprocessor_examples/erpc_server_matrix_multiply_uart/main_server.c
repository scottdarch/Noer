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
 */

#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/multiprocessor_examples/erpc_common/erpc_error_handler.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/multiprocessor_examples/erpc_common/erpc_matrix_multiply/service/erpc_matrix_multiply.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/multiprocessor_examples/erpc_common/erpc_matrix_multiply/service/erpc_matrix_multiply_server.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/multiprocessor_examples/erpc_server_matrix_multiply_uart/board.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/middleware/multicore_2.1.0/erpc/erpc_c/setup/erpc_server_setup.h"

#if BOARD_DEBUG_UART_TYPE == DEBUG_CONSOLE_DEVICE_TYPE_UART
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/devices/MK66F18/cmsis_drivers/fsl_uart_cmsis.h"
#elif BOARD_DEBUG_UART_TYPE == DEBUG_CONSOLE_DEVICE_TYPE_LPUART
#include "fsl_lpuart_cmsis.h"
#elif BOARD_DEBUG_UART_TYPE == DEBUG_CONSOLE_DEVICE_TYPE_LPSCI
#include "fsl_lpsci_cmsis.h"
#endif

#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/multiprocessor_examples/erpc_server_matrix_multiply_uart/pin_mux.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/multiprocessor_examples/erpc_server_matrix_multiply_uart/clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ERPC_DEMO_UART Driver_USART0

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

uint32_t UART0_GetFreq(void)
{
    return CLOCK_GetFreq(UART0_CLK_SRC);
}

uint32_t UART1_GetFreq(void)
{
    return CLOCK_GetFreq(UART1_CLK_SRC);
}

uint32_t UART2_GetFreq(void)
{
    return CLOCK_GetFreq(UART2_CLK_SRC);
}

uint32_t UART3_GetFreq(void)
{
    return CLOCK_GetFreq(UART3_CLK_SRC);
}

uint32_t UART4_GetFreq(void)
{
    return CLOCK_GetFreq(UART4_CLK_SRC);
}

/*!
 * @brief erpcMatrixMultiply function implementation.
 *
 * This is the implementation of the erpcMatrixMultiply function called by the primary core.
 *
 * @param matrix1 First matrix
 * @param matrix2 Second matrix
 * @param result_matrix Result matrix
 */
void erpcMatrixMultiply(const Matrix *matrix1, const Matrix *matrix2, Matrix *result_matrix)
{
    int32_t i, j, k;

    /* Clear the result matrix */
    for (i = 0; i < matrix_size; ++i)
    {
        for (j = 0; j < matrix_size; ++j)
        {
            (*result_matrix)[i][j] = 0;
        }
    }

    /* Multiply two matrices */
    for (i = 0; i < matrix_size; ++i)
    {
        for (j = 0; j < matrix_size; ++j)
        {
            for (k = 0; k < matrix_size; ++k)
            {
                (*result_matrix)[i][j] += (*matrix1)[i][k] * (*matrix2)[k][j];
            }
        }
    }
}

/*!
 * @brief Main function
 */
int main()
{
    BOARD_InitPins();
    BOARD_BootClockRUN();

    /* UART transport layer initialization */
    erpc_transport_t transport;

    transport = erpc_transport_cmsis_uart_init((void *)&ERPC_DEMO_UART);

    /* eRPC server side initialization */
    erpc_server_init(transport);

    /* adding the service to the server */
    erpc_add_service_to_server(create_MatrixMultiplyService_service());

    while (1)
    {
        /* process message */
        erpc_status_t status = erpc_server_poll();

        /* handle error status */
        if (status != kErpcStatus_Success)
        {
            /* print error description */
            erpc_error_handler(status);

            /* stop erpc server */
            erpc_server_stop();

            /* exit program loop */
            break;
        }

        /* do other tasks */
        int i;
        for (i = 0; i < 10000; i++)
        {
        }
    }
    while (1)
    {
    }
}
