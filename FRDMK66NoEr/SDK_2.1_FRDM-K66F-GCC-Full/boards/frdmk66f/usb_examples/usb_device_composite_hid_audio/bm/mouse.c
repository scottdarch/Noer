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

#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/usb_examples/usb_device_composite_hid_audio/bm/mouse.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/usb_examples/usb_device_composite_hid_audio/bm/board.h"
#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/usb_examples/usb_device_composite_hid_audio/bm/clock_config.h"
#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/usb_examples/usb_device_composite_hid_audio/bm/composite.h"
#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/usb_examples/usb_device_composite_hid_audio/bm/usb_device_ch9.h"
#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/usb_examples/usb_device_composite_hid_audio/bm/usb_device_class.h"
#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/usb_examples/usb_device_composite_hid_audio/bm/usb_device_config.h"
#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/usb_examples/usb_device_composite_hid_audio/bm/usb_device_descriptor.h"
#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/boards/frdmk66f/usb_examples/usb_device_composite_hid_audio/bm/usb_device_hid.h"
#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/devices/MK66F18/fsl_device_registers.h"
#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/middleware/usb_1.4.0/device/usb_device.h"
#include "../../../../../../SDK_2.1_FRDM-K66F-GCC-Full/middleware/usb_1.4.0/include/usb.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
* Variables
******************************************************************************/
USB_DATA_ALIGNMENT static uint8_t s_MouseBuffer[USB_HID_MOUSE_REPORT_LENGTH];
static usb_device_composite_struct_t *g_deviceComposite;

/*******************************************************************************
* Code
******************************************************************************/
/*!
 * @brief device mouse moves action.
 *
 * This function handle the mouse moves action.
 */
usb_status_t USB_DeviceMouseAction(void)
{
    static int8_t x = 0U;
    static int8_t y = 0U;
    enum
    {
        RIGHT,
        DOWN,
        LEFT,
        UP
    };
    static uint8_t dir = RIGHT;

    switch (dir)
    {
        case RIGHT:
            g_deviceComposite->hidMouse.buffer[1] = 2;
            g_deviceComposite->hidMouse.buffer[2] = 0U;
            x++;
            if (x > 5U)
            {
                dir++;
            }
            break;
        case DOWN:
            g_deviceComposite->hidMouse.buffer[1] = 0U;
            g_deviceComposite->hidMouse.buffer[2] = 2;
            y++;
            if (y > 5U)
            {
                dir++;
            }
            break;
        case LEFT:
            g_deviceComposite->hidMouse.buffer[1] = (uint8_t)(-2);
            g_deviceComposite->hidMouse.buffer[2] = 0U;
            x--;
            if (x < 1U)
            {
                dir++;
            }
            break;
        case UP:
            g_deviceComposite->hidMouse.buffer[1] = 0U;
            g_deviceComposite->hidMouse.buffer[2] = (uint8_t)(-2);
            y--;
            if (y < 1U)
            {
                dir = RIGHT;
            }
            break;
        default:
            break;
    }
    return USB_DeviceHidSend(g_deviceComposite->hidMouse.hidHandle, USB_HID_MOUSE_ENDPOINT,
                             g_deviceComposite->hidMouse.buffer, USB_HID_MOUSE_REPORT_LENGTH);
}

/*!
 * @brief device Hid callback function.
 *
 * This function handle the Hid class specified event.
 * @param handle          The USB class  handle.
 * @param event           The USB device event type.
 * @param param           The parameter of the class specific event.
 * @return kStatus_USB_Success or error.
 */
usb_status_t USB_DeviceHidMouseCallback(class_handle_t handle, uint32_t event, void *param)
{
    usb_status_t error = kStatus_USB_Error;

    switch (event)
    {
        case kUSB_DeviceHidEventSendResponse:
            if (g_deviceComposite->hidMouse.attach)
            {
                error = USB_DeviceMouseAction();
            }
            break;
        case kUSB_DeviceHidEventGetReport:
        case kUSB_DeviceHidEventSetReport:
        case kUSB_DeviceHidEventRequestReportBuffer:
            error = kStatus_USB_InvalidRequest;
            break;
        case kUSB_DeviceHidEventGetIdle:
        case kUSB_DeviceHidEventGetProtocol:
        case kUSB_DeviceHidEventSetIdle:
        case kUSB_DeviceHidEventSetProtocol:
            break;
        default:
            break;
    }

    return error;
}

/*!
 * @brief Hid device set configuration function.
 *
 * This function sets configuration for msc class.
 *
 * @param handle The Hid class handle.
 * @param configure Hid class configure index.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceHidMouseSetConfigure(class_handle_t handle, uint8_t configure)
{
    g_deviceComposite->hidMouse.attach = 1U;
    g_deviceComposite->hidMouse.buffer = s_MouseBuffer;
    return USB_DeviceMouseAction();
}

/*!
 * @brief Hid device set interface function.
 *
 * This function sets interface for msc class.
 *
 * @param handle The Hid class handle.
 * @param alternateSetting Hid class alternateSetting.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceHidMouseSetInterface(class_handle_t handle, uint8_t interface, uint8_t alternateSetting)
{
    return kStatus_USB_Error;
}

/*!
 * @brief device Hid init function.
 *
 * This function initializes the device with the composite device class information.
 *
 * @param deviceComposite          The pointer to the composite device structure.
 * @return kStatus_USB_Success .
 */
usb_status_t USB_DeviceHidMouseInit(usb_device_composite_struct_t *device_composite)
{
    g_deviceComposite = device_composite;
    return kStatus_USB_Success;
}
