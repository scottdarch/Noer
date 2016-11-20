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
 */

/* FreeRTOS kernel includes. */
#include "pin_mux.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/rtos_examples/freertos_hello/board.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/rtos_examples/freertos_hello/clock_config.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/rtos_examples/freertos_hello/pin_mux.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/devices/MK66F18/fsl_device_registers.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/devices/MK66F18/utilities/fsl_debug_console.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/rtos/freertos_9.0.0/Source/include/FreeRTOS.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/rtos/freertos_9.0.0/Source/include/queue.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/rtos/freertos_9.0.0/Source/include/task.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/rtos/freertos_9.0.0/Source/include/timers.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Task priorities. */
#define hello_task_PRIORITY (configMAX_PRIORITIES - 1)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void hello_task(void *pvParameters);

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Application entry point.
 */
int main(void)
{
    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    xTaskCreate(hello_task, "Hello_task", configMINIMAL_STACK_SIZE, NULL, hello_task_PRIORITY, NULL);
    vTaskStartScheduler();
    for (;;)
        ;
}

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
static void hello_task(void *pvParameters)
{
    for (;;)
    {
        PRINTF("Hello world.\r\n");
        vTaskSuspend(NULL);
    }
}
