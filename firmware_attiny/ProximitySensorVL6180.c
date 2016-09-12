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

#include "mcu.h"
#include "Dog_stateRequired.h"
#include "SparkFun_VL6180X.h"
#include "USI_TWI_Master.h"

#define PROXIMITY_SENSOR_ADDR 0x29

typedef struct ProximitySensorVL6180_t {
    TWIPeripheral _interface;
} ProximitySensorVL6180;

/**
* This implementation assumes a single, specific proximity sensor.
*/
static ProximitySensorVL6180 _the_proximity_sensor;

// +--------------------------------------------------------------------------+
// | VL6180x HELPERS
// +--------------------------------------------------------------------------+
static uint8_t VL6180x_getRegister(ProximitySensorVL6180 *self, uint16_t address)
{
    uint8_t long_address[2]    = {0xFF & (address >> 8), (0xFF & address)};
    uint8_t single_byte_buffer = 0;
    if (self->_interface.start_with_data(&self->_interface, false, long_address, 2)) {
        self->_interface.start_with_data(&self->_interface, true, &single_byte_buffer, 1);
    }
    return single_byte_buffer;
}

static void VL6180x_setRegister(ProximitySensorVL6180 *self, uint16_t address, uint8_t data)
{
    uint8_t long_address[3] = {0xFF & (address >> 8), (0xFF & address), data};
    self->_interface.start_with_data(&self->_interface, false, long_address, 3);
}

static void VL6180xAdditionalSettings(ProximitySensorVL6180 *self)
{
    // Recommended settings from datasheet
    // http://www.st.com/st-web-ui/static/active/en/resource/technical/document/application_note/DM00122600.pdf

    VL6180x_setRegister(self, VL6180X_SYSTEM_GROUPED_PARAMETER_HOLD, 0x1);
    VL6180x_setRegister(self, VL6180X_SYSRANGE_THRESH_LOW, 0x4D);
    VL6180x_setRegister(self, VL6180X_SYSTEM_INTERRUPT_CONFIG_GPIO, 0x01);

    VL6180x_setRegister(self, VL6180X_SYSTEM_MODE_GPIO1,
                        0x10); // Set GPIO1 high when sample complete
    VL6180x_setRegister(self, VL6180X_READOUT_AVERAGING_SAMPLE_PERIOD,
                        0x30); // Set Avg sample period
    VL6180x_setRegister(self, VL6180X_SYSRANGE_VHV_REPEAT_RATE,
                        0xFF); // Set auto calibration period (Max = 255)/(OFF = 0)
    VL6180x_setRegister(self, VL6180X_SYSRANGE_VHV_RECALIBRATE,
                        0x01); // perform a single temperature calibration
    // Optional settings from datasheet
    // http://www.st.com/st-web-ui/static/active/en/resource/technical/document/application_note/DM00122600.pdf
    VL6180x_setRegister(self, VL6180X_SYSRANGE_INTERMEASUREMENT_PERIOD,
                        0x09); // Set default ranging inter-measurement period to 100ms
    // Additional settings defaults from community
    VL6180x_setRegister(self, VL6180X_SYSRANGE_MAX_CONVERGENCE_TIME, 0x32);
    VL6180x_setRegister(self, VL6180X_SYSRANGE_RANGE_CHECK_ENABLES, 0x10 | 0x01);
    VL6180x_setRegister(self, VL6180X_SYSRANGE_EARLY_CONVERGENCE_ESTIMATE, 0x7B);
    VL6180x_setRegister(self, VL6180X_SYSALS_INTEGRATION_PERIOD, 0x64);

    VL6180x_setRegister(self, VL6180X_READOUT_AVERAGING_SAMPLE_PERIOD, 0x30);
    VL6180x_setRegister(self, VL6180X_FIRMWARE_RESULT_SCALER, 0x01);
    VL6180x_setRegister(self, VL6180X_SYSTEM_GROUPED_PARAMETER_HOLD, 0x0);
}

static void VL6180xDefautSettings(ProximitySensorVL6180 *self)
{
    // Required by datasheet
    // http://www.st.com/st-web-ui/static/active/en/resource/technical/document/application_note/DM00122600.pdf
    VL6180x_setRegister(self, 0x0207, 0x01);
    VL6180x_setRegister(self, 0x0208, 0x01);
    VL6180x_setRegister(self, 0x0096, 0x00);
    VL6180x_setRegister(self, 0x0097, 0xfd);
    VL6180x_setRegister(self, 0x00e3, 0x00);
    VL6180x_setRegister(self, 0x00e4, 0x04);
    VL6180x_setRegister(self, 0x00e5, 0x02);
    VL6180x_setRegister(self, 0x00e6, 0x01);
    VL6180x_setRegister(self, 0x00e7, 0x03);
    VL6180x_setRegister(self, 0x00f5, 0x02);
    VL6180x_setRegister(self, 0x00d9, 0x05);
    VL6180x_setRegister(self, 0x00db, 0xce);
    VL6180x_setRegister(self, 0x00dc, 0x03);
    VL6180x_setRegister(self, 0x00dd, 0xf8);
    VL6180x_setRegister(self, 0x009f, 0x00);
    VL6180x_setRegister(self, 0x00a3, 0x3c);
    VL6180x_setRegister(self, 0x00b7, 0x00);
    VL6180x_setRegister(self, 0x00bb, 0x3c);
    VL6180x_setRegister(self, 0x00b2, 0x09);
    VL6180x_setRegister(self, 0x00ca, 0x09);
    VL6180x_setRegister(self, 0x0198, 0x01);
    VL6180x_setRegister(self, 0x01b0, 0x17);
    VL6180x_setRegister(self, 0x01ad, 0x00);
    VL6180x_setRegister(self, 0x00ff, 0x05);
    VL6180x_setRegister(self, 0x0100, 0x05);
    VL6180x_setRegister(self, 0x0199, 0x05);
    VL6180x_setRegister(self, 0x01a6, 0x1b);
    VL6180x_setRegister(self, 0x01ac, 0x3e);
    VL6180x_setRegister(self, 0x01a7, 0x1f);
    VL6180x_setRegister(self, 0x0030, 0x00);
}

// +--------------------------------------------------------------------------+
// | ProximitySensor API
// +--------------------------------------------------------------------------+

static ProximitySensorVL6180 *get_instance()
{
    return &_the_proximity_sensor;
}

static ProximitySensorVL6180 *init_proximity_sensor(ProximitySensorVL6180 *sensor)
{
    if (sensor) {

        // Falling SDA edge (e.g. start condition) triggers the INT0 interrupt.
        MCUCR |= (1 << ISC01);

        // Enable INT0
        GIMSK |= (1 << INT0);

        PIN_INIT_OUTPUT(TOF_RESET);
        // Hardware reset the TOF sensor.
        // We'll release it out of reset when we start configuration.
        PIN_OUT_LOW(TOF_RESET);
        twi_peripheral_init(&sensor->_interface, PROXIMITY_SENSOR_ADDR);
    }
    return sensor;
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
    // TODO: blink LED to confirm interrupt.
    // VL6180x_setRegister((ProximitySensorVL6180*)get_instance(), VL6180X_SYSTEM_INTERRUPT_CLEAR,
    // 0x7);
}

// +--------------------------------------------------------------------------+
// | STATE MACHINE :: IFace :: TOF
// +--------------------------------------------------------------------------+

// +--[INIT OPERATIONS]-------------------------------------------------------+
void dog_stateIfaceTOF_on_config_start(const Dog_state *handle)
{
    PIN_OUT_HIGH(TOF_RESET);
}

void dog_stateIfaceTOF_on_init(const Dog_state *handle)
{
    init_proximity_sensor(get_instance());
}

bool dog_stateIfaceTOF_is_sensor_reset(const Dog_state *handle)
{
    return (VL6180x_getRegister(get_instance(), VL6180X_SYSTEM_FRESH_OUT_OF_RESET) == 1);
}

bool dog_stateIfaceTOF_did_write_default_settings(const Dog_state *handle)
{
    VL6180xDefautSettings(get_instance());
    return true;
}

bool dog_stateIfaceTOF_did_write_application_settings(const Dog_state *handle)
{
    VL6180xAdditionalSettings(get_instance());
    return true;
}

void dog_stateIfaceTOF_on_config_complete(const Dog_state *handle)
{
    VL6180x_setRegister(get_instance(), VL6180X_SYSTEM_FRESH_OUT_OF_RESET, 0x01);
}

bool dog_stateIfaceTOF_is_sensor_ready(const Dog_state *handle)
{
    return (VL6180x_getRegister(get_instance(), VL6180X_RESULT_RANGE_STATUS) & 0x01);
}

// +--[RUNNING OPERATIONS FOR MCU]--------------------------------------------+
void dog_stateIfaceTOF_on_start(const Dog_state *handle)
{
    VL6180x_setRegister(get_instance(), VL6180X_SYSRANGE_START,
                        0x03); //< 0x03 for continuous ranging.
}

bool dog_stateIfaceTOF_object_detected(const Dog_state *handle)
{
    return false;
}

// +--[RUNNING OPERATIONS FOR TOF]--------------------------------------------+
uint8_t dog_stateIfaceTOF_get_range_status(const Dog_state *handle)
{
    return VL6180x_getRegister(get_instance(), VL6180X_RESULT_INTERRUPT_STATUS_GPIO);
}

void dog_stateIfaceTOF_on_reset_range_status(const Dog_state *handle)
{
    VL6180x_setRegister(get_instance(), VL6180X_SYSTEM_INTERRUPT_CLEAR, 0x7);
}

void dog_stateIfaceTOF_on_handle_error(const Dog_state *handle, const uint8_t error)
{
    // TODO: determine if we need to reset the MCU for some or all errors.
}
