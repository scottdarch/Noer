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

/* Kernel includes. */
#include "pin_mux.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/rtos_examples/freertos_mutex/board.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/rtos_examples/freertos_mutex/clock_config.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/rtos_examples/freertos_mutex/pin_mux.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/devices/MK66F18/fsl_device_registers.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/devices/MK66F18/utilities/fsl_debug_console.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/rtos/freertos_9.0.0/Source/include/FreeRTOS.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/rtos/freertos_9.0.0/Source/include/queue.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/rtos/freertos_9.0.0/Source/include/semphr.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/rtos/freertos_9.0.0/Source/include/task.h"
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/rtos/freertos_9.0.0/Source/include/timers.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

SemaphoreHandle_t xMutex;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void write_task_1(void *pvParameters);
static void write_task_2(void *pvParameters);

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    xMutex = xSemaphoreCreateMutex();

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    xTaskCreate(write_task_1, "WRITE_TASK_1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(write_task_2, "WRITE_TASK_2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    /* Start scheduling. */
    vTaskStartScheduler();
    for (;;)
        ;
}

/*!
 * @brief Write Task 1 function
 */
static void write_task_1(void *pvParameters)
{
    while (1)
    {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        PRINTF("ABCD |");
        taskYIELD();
        PRINTF(" EFGH\r\n");
        xSemaphoreGive(xMutex);
        taskYIELD();
    }
}

/*!
 * @brief Write Task 2 function
 */
static void write_task_2(void *pvParameters)
{
    while (1)
    {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        PRINTF("1234 |");
        taskYIELD();
        PRINTF(" 5678\r\n");
        xSemaphoreGive(xMutex);
        taskYIELD();
    }
}
