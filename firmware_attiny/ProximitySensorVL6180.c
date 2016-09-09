/*
* Clementine! NO!                                                   ^ ^
*                                                                   o o
*                                                                    m
* ----------------------------------------------------------------------------
*/
/******************************************************************************
* (Based on) SparkFun_VL6180x.cpp
* Library for VL6180x time of flight range finder.
* Casey Kuhns @ SparkFun Electronics
* 10/29/2014
* https://github.com/sparkfun/SparkFun_ToF_Range_Finder-VL6180_Arduino_Library
*
* The VL6180x by ST micro is a time of flight range finder that
* uses pulsed IR light to determine distances from object at close
* range.  The average range of a sensor is between 0-200mm
*
* In this file are the functions in the VL6180x class
*
* Resources:
* This library uses the Arduino Wire.h to complete I2C transactions.
*
* Development environment specifics:
* 	IDE: Arduino 1.0.5
* 	Hardware Platform: Arduino Pro 3.3V/8MHz
* 	VL6180x Breakout Version: 1.0
* **Updated for Arduino 1.6.4 5/2015**
*
* This code is beerware. If you see me (or any other SparkFun employee) at the
* local pub, and you've found our code helpful, please buy us a round!
*
* Distributed as-is; no warranty is given.
******************************************************************************/

#include "ProximitySensor.h"
#include "SparkFun_VL6180X.h"
#include "USI_TWI_Master.h"
#include <util/delay.h>

#define PROXIMITY_SENSOR_ADDR 0x29

typedef void (*proximity_threshold_breach)(struct ProximitySensor_t *, void *user_data);

typedef enum {
    VL6180STATE_WAITING_FOR_RESET,
    VL6180STATE_READY
} VL6180State;

typedef struct ProximitySensorVL6180_t {
    ProximitySensor super;
    void *_callback_user_data;
    proximity_threshold_breach _callback;
    TWIPeripheral _interface;
    VL6180State _state;
} ProximitySensorVL6180;

/**
* This implementation assumes a single, specific proximity sensor.
*/
ProximitySensorVL6180 _the_proximity_sensor;

// +--------------------------------------------------------------------------+
// | VL6180x HELPERS
// +--------------------------------------------------------------------------+
static uint8_t VL6180x_getRegister(ProximitySensorVL6180 *self, uint8_t address)
{
    uint8_t single_byte_buffer = 0;
    if (self->_interface.start_with_data(&self->_interface, false, &address, 1)) {
        self->_interface.start_with_data(&self->_interface, true, &single_byte_buffer, 1);
    }
    return single_byte_buffer;
}

static void VL6180x_setRegister16bit(ProximitySensorVL6180 *self, uint16_t address, uint8_t data)
{
    uint8_t long_address[2] = {(0x0F & address), address >> 8};
    if (self->_interface.start_with_data(&self->_interface, false, long_address, 2)) {
        self->_interface.start_with_data(&self->_interface, false, &data, 1);
    }
}

static void VL6180x_setRegister(ProximitySensorVL6180 *self, uint8_t address, uint8_t data)
{
    if (self->_interface.start_with_data(&self->_interface, false, &address, 1)) {
        self->_interface.start_with_data(&self->_interface, false, &data, 1);
    }
}

static void VL6180xDefautSettings(ProximitySensorVL6180 *self)
{
    // Recommended settings from datasheet
    // http://www.st.com/st-web-ui/static/active/en/resource/technical/document/application_note/DM00122600.pdf

    // Enable Interrupts on Conversion Complete (any source)
    VL6180x_setRegister(self, VL6180X_SYSTEM_INTERRUPT_CONFIG_GPIO,
    (4 << 3) | (4)); // Set GPIO1 high when sample complete

    VL6180x_setRegister(self, VL6180X_SYSTEM_MODE_GPIO1,
    0x10); // Set GPIO1 high when sample complete
    VL6180x_setRegister16bit(self, VL6180X_READOUT_AVERAGING_SAMPLE_PERIOD,
    0x30);                                     // Set Avg sample period
    VL6180x_setRegister(self, VL6180X_SYSALS_ANALOGUE_GAIN, 0x46); // Set the ALS gain
    VL6180x_setRegister(self, VL6180X_SYSRANGE_VHV_REPEAT_RATE,
    0xFF); // Set auto calibration period (Max = 255)/(OFF = 0)
    VL6180x_setRegister(self, VL6180X_SYSALS_INTEGRATION_PERIOD,
    0x63); // Set ALS integration time to 100ms
    VL6180x_setRegister(self, VL6180X_SYSRANGE_VHV_RECALIBRATE,
    0x01); // perform a single temperature calibration
    // Optional settings from datasheet
    // http://www.st.com/st-web-ui/static/active/en/resource/technical/document/application_note/DM00122600.pdf
    VL6180x_setRegister(self, VL6180X_SYSRANGE_INTERMEASUREMENT_PERIOD,
    0x09); // Set default ranging inter-measurement period to 100ms
    VL6180x_setRegister(self, VL6180X_SYSALS_INTERMEASUREMENT_PERIOD,
    0x0A); // Set default ALS inter-measurement period to 100ms
    VL6180x_setRegister(self, VL6180X_SYSTEM_INTERRUPT_CONFIG_GPIO,
    0x24); // Configures interrupt on ‘New Sample Ready threshold event’
    // Additional settings defaults from community
    VL6180x_setRegister(self, VL6180X_SYSRANGE_MAX_CONVERGENCE_TIME, 0x32);
    VL6180x_setRegister(self, VL6180X_SYSRANGE_RANGE_CHECK_ENABLES, 0x10 | 0x01);
    VL6180x_setRegister16bit(self, VL6180X_SYSRANGE_EARLY_CONVERGENCE_ESTIMATE, 0x7B);
    VL6180x_setRegister16bit(self, VL6180X_SYSALS_INTEGRATION_PERIOD, 0x64);

    VL6180x_setRegister16bit(self, VL6180X_READOUT_AVERAGING_SAMPLE_PERIOD, 0x30);
    VL6180x_setRegister(self, VL6180X_SYSALS_ANALOGUE_GAIN, 0x40);
    VL6180x_setRegister16bit(self, VL6180X_FIRMWARE_RESULT_SCALER, 0x01);
}

static uint8_t VL6180x_getDistance(ProximitySensorVL6180 *self)
{
    VL6180x_setRegister(self, VL6180X_SYSRANGE_START, 0x01); // Start Single shot mode
    _delay_ms(10);
    return VL6180x_getRegister(self, VL6180X_RESULT_RANGE_VAL);
}

// +--------------------------------------------------------------------------+
// | EXTERNAL INTERRUPT
// +--------------------------------------------------------------------------+

/*
* This firmware is too simple to worry about interrupt dispatching. We'll just
* let the ProximitySensor implementation own it.
*/
ISR(INT0_vect)
{
}

// +--------------------------------------------------------------------------+
// | ProximitySensor API
// +--------------------------------------------------------------------------+

static void _register_proximity_threshold_breach(ProximitySensor *self,
proximity_threshold_breach callback,
void *user_data)
{
    ProximitySensorVL6180 *vl6180_self = (ProximitySensorVL6180 *)self;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        vl6180_self->_callback           = callback;
        vl6180_self->_callback_user_data = user_data;
    }
}

static void _service(ProximitySensor *self)
{
    ProximitySensorVL6180 *vl6180_self = (ProximitySensorVL6180 *)self;
    if (VL6180STATE_WAITING_FOR_RESET == vl6180_self->_state) {
        const uint8_t data = VL6180x_getRegister(&_the_proximity_sensor, VL6180X_SYSTEM_FRESH_OUT_OF_RESET);

        if (data == 1) {
            vl6180_self->_state = VL6180STATE_READY;
            // Required by datasheet
            // http://www.st.com/st-web-ui/static/active/en/resource/technical/document/application_note/DM00122600.pdf
            VL6180x_setRegister16bit(&_the_proximity_sensor, 0x0207, 0x01);
            VL6180x_setRegister16bit(&_the_proximity_sensor, 0x0208, 0x01);
            VL6180x_setRegister(&_the_proximity_sensor, 0x0096, 0x00);
            VL6180x_setRegister(&_the_proximity_sensor, 0x0097, 0xfd);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00e3, 0x00);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00e4, 0x04);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00e5, 0x02);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00e6, 0x01);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00e7, 0x03);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00f5, 0x02);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00d9, 0x05);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00db, 0xce);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00dc, 0x03);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00dd, 0xf8);
            VL6180x_setRegister(&_the_proximity_sensor, 0x009f, 0x00);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00a3, 0x3c);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00b7, 0x00);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00bb, 0x3c);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00b2, 0x09);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00ca, 0x09);
            VL6180x_setRegister16bit(&_the_proximity_sensor, 0x0198, 0x01);
            VL6180x_setRegister16bit(&_the_proximity_sensor, 0x01b0, 0x17);
            VL6180x_setRegister16bit(&_the_proximity_sensor, 0x01ad, 0x00);
            VL6180x_setRegister(&_the_proximity_sensor, 0x00ff, 0x05);
            VL6180x_setRegister16bit(&_the_proximity_sensor, 0x0100, 0x05);
            VL6180x_setRegister16bit(&_the_proximity_sensor, 0x0199, 0x05);
            VL6180x_setRegister16bit(&_the_proximity_sensor, 0x01a6, 0x1b);
            VL6180x_setRegister16bit(&_the_proximity_sensor, 0x01ac, 0x3e);
            VL6180x_setRegister16bit(&_the_proximity_sensor, 0x01a7, 0x1f);
            VL6180x_setRegister(&_the_proximity_sensor, 0x0030, 0x00);
        }
    }
}

ProximitySensor *init_proximity_sensor()
{
    _the_proximity_sensor.super.service = _service;
    _the_proximity_sensor.super.register_proximity_threshold_breach =
    _register_proximity_threshold_breach;
    _the_proximity_sensor.super.last_proximity = 0;
    _the_proximity_sensor._callback            = 0;
    _the_proximity_sensor._callback_user_data = 0;
    _the_proximity_sensor._state = VL6180STATE_WAITING_FOR_RESET;
    twi_peripheral_init(&_the_proximity_sensor._interface, PROXIMITY_SENSOR_ADDR);

    // Falling SDA edge (e.g. start condition) triggers the INT0 interrupt.
    MCUCR |= (1 << ISC01);

    // Enable INT0
    GIMSK |= (1 << INT0);

    return &_the_proximity_sensor.super;
}
