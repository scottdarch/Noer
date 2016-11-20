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

#ifndef _FSL_I2C_CMSIS_H_
#define _FSL_I2C_CMSIS_H_
#include "../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/cmsis_driver_examples/i2c/edma_transfer/RTE_Device.h"
#include "../../../../SDK_2.1_FRDM-K66F-GCC-Full/CMSIS/Driver/Include/Driver_I2C.h"
#include "../../../../SDK_2.1_FRDM-K66F-GCC-Full/devices/MK66F18/drivers/fsl_common.h"
#include "../../../../SDK_2.1_FRDM-K66F-GCC-Full/devices/MK66F18/drivers/fsl_i2c.h"
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
#include "fsl_dmamux.h"
#endif
#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)
#include "fsl_i2c_dma.h"
#endif
#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)
#include "fsl_i2c_edma.h"
#endif

#if defined(I2C0)
extern ARM_DRIVER_I2C I2C0_Interrupt_Driver;
#endif

#if defined(I2C1)
extern ARM_DRIVER_I2C I2C1_Interrupt_Driver;
#endif

#if defined(I2C2)
extern ARM_DRIVER_I2C I2C2_Interrupt_Driver;
#endif

#if defined(I2C3)
extern ARM_DRIVER_I2C I2C3_Interrupt_Driver;
#endif

#if (defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT)

#if defined(I2C0)
extern ARM_DRIVER_I2C I2C0_Master_Dma_Driver;
#endif

#if defined(I2C1)
extern ARM_DRIVER_I2C I2C1_Master_Dma_Driver;
#endif

#if defined(I2C2)
extern ARM_DRIVER_I2C I2C2_Master_Dma_Driver;
#endif

#if defined(I2C3)
extern ARM_DRIVER_I2C I2C3_Master_Dma_Driver;
#endif

#endif

#if (defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT)

#if defined(I2C0)
extern ARM_DRIVER_I2C I2C0_Master_Edma_Driver;
#endif

#if defined(I2C1)
extern ARM_DRIVER_I2C I2C1_Master_Edma_Driver;
#endif

#if defined(I2C2)
extern ARM_DRIVER_I2C I2C2_Master_Edma_Driver;
#endif

#if defined(I2C3)
extern ARM_DRIVER_I2C I2C3_Master_Edma_Driver;
#endif

#endif

#endif
