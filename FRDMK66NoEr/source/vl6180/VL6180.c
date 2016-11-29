/**
 * CLEMENTINE! NO!                                ^ ^
 *                                                O O
 *                                                 ~
 *----------------------------------------------U-----U------------------------
 */
#include <stdbool.h>
#include "VL6180.h"
#include "fsl_i2c.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include "VL6180_state_irqRequired.h"
#include "VL6180_state_irq.h"

// +---------------------------------------------------------------------------+
// | PRIVATE::TYPES
// +---------------------------------------------------------------------------+
typedef struct _VL6180Private {
    Vl6180_state_irq state;
    VL6180 *self;
    uint16_t transfer_buffer;
    i2c_master_handle_t sensor_bus;
    i2c_master_config_t sensor_bus_config;
    i2c_master_transfer_t sensor_bus_tranfer;
} VL6180Private;

// +---------------------------------------------------------------------------+
// | PRIVATE::DATA
// +---------------------------------------------------------------------------+
VL6180 _singleton;
VL6180Private _singleton_private;
VL6180 *_singleton_addr = 0;

// +---------------------------------------------------------------------------+
// | PRIVATE::METHODS
// +---------------------------------------------------------------------------+
static const char *_vl6180x_get_error_description(uint8_t error)
{
    switch (error) {
    case 0:
        return VL6180X_ERR_0000;
    case 1:
        return VL6180X_ERR_0001;
    case 2:
        return VL6180X_ERR_0010;
    case 3:
        return VL6180X_ERR_0011;
    case 4:
        return VL6180X_ERR_0100;
    case 5:
        return VL6180X_ERR_0101;
    case 6:
        return VL6180X_ERR_0110;
    case 7:
        return VL6180X_ERR_0111;
    case 8:
        return VL6180X_ERR_1000;
    case 9:
        return VL6180X_ERR_1001;
    case 10:
        return VL6180X_ERR_1010;
    case 11:
        return VL6180X_ERR_1011;
    case 12:
        return VL6180X_ERR_1100;
    case 13:
        return VL6180X_ERR_1101;
    case 14:
        return VL6180X_ERR_1110;
    case 15:
        return VL6180X_ERR_1111;
    default:
        return VL6180X_ERR_XXXX;
    }
}

static bool _vl6180_is_running(VL6180 *self)
{
    VL6180Private *driver_private = (VL6180Private *)self->_private;

    return vl6180_state_irq_isStateActive((Vl6180_state_irq *)driver_private,
                                          Vl6180_state_irq_main_region_running);
}

static status_t _vl6180_write(VL6180 *self, uint16_t register_addr, uint8_t data, bool no_stop)
{
    VL6180Private *private_self = (VL6180Private *)self->_private;

    private_self->sensor_bus_tranfer.direction      = kI2C_Write;
    private_self->sensor_bus_tranfer.subaddress     = (uint32_t)register_addr;
    private_self->sensor_bus_tranfer.subaddressSize = 2;
    private_self->transfer_buffer                   = data;
    private_self->sensor_bus_tranfer.data           = (uint8_t *)&private_self->transfer_buffer;
    private_self->sensor_bus_tranfer.dataSize       = 1;

    if (private_self->sensor_bus_tranfer.flags & kI2C_TransferNoStopFlag) {
        private_self->sensor_bus_tranfer.flags |= kI2C_TransferRepeatedStartFlag;
    } else {
        private_self->sensor_bus_tranfer.flags &= ~(kI2C_TransferRepeatedStartFlag);
    }
    if (!no_stop) {
        private_self->sensor_bus_tranfer.flags &= ~(kI2C_TransferNoStopFlag);
    } else {
        private_self->sensor_bus_tranfer.flags |= kI2C_TransferNoStopFlag;
    }

    return I2C_MasterTransferBlocking(I2C1, &private_self->sensor_bus_tranfer);
}

static status_t _vl6180_read(VL6180 *self, uint16_t register_addr, uint8_t *out_data,
                             size_t out_data_len, bool no_stop)
{
    VL6180Private *private_self = (VL6180Private *)self->_private;

    private_self->sensor_bus_tranfer.direction      = kI2C_Read;
    private_self->sensor_bus_tranfer.data           = (uint8_t *)&private_self->transfer_buffer;
    private_self->sensor_bus_tranfer.subaddress     = (uint32_t)register_addr;
    private_self->sensor_bus_tranfer.subaddressSize = 2;
    private_self->sensor_bus_tranfer.data           = out_data;
    private_self->sensor_bus_tranfer.dataSize       = 1;

    if (private_self->sensor_bus_tranfer.flags & kI2C_TransferNoStopFlag) {
        private_self->sensor_bus_tranfer.flags |= kI2C_TransferRepeatedStartFlag;
    } else {
        private_self->sensor_bus_tranfer.flags &= ~(kI2C_TransferRepeatedStartFlag);
    }
    if (!no_stop) {
        private_self->sensor_bus_tranfer.flags &= ~(kI2C_TransferNoStopFlag);
    } else {
        private_self->sensor_bus_tranfer.flags |= kI2C_TransferNoStopFlag;
    }

    return I2C_MasterTransferBlocking(I2C1, &private_self->sensor_bus_tranfer);
}

static void _vl6180x_sr03(VL6180 *self)
{
    // Required by datasheet
    // http://www.st.com/st-web-ui/static/active/en/resource/technical/document/application_note/DM00122600.pdf
    _vl6180_write(self, 0x0207, 0x01, true);
    _vl6180_write(self, 0x0208, 0x01, true);
    _vl6180_write(self, 0x0096, 0x00, true);
    _vl6180_write(self, 0x0097, 0xfd, true);
    _vl6180_write(self, 0x00e3, 0x00, true);
    _vl6180_write(self, 0x00e4, 0x04, true);
    _vl6180_write(self, 0x00e5, 0x02, true);
    _vl6180_write(self, 0x00e6, 0x01, true);
    _vl6180_write(self, 0x00e7, 0x03, true);
    _vl6180_write(self, 0x00f5, 0x02, true);
    _vl6180_write(self, 0x00d9, 0x05, true);
    _vl6180_write(self, 0x00db, 0xce, true);
    _vl6180_write(self, 0x00dc, 0x03, true);
    _vl6180_write(self, 0x00dd, 0xf8, true);
    _vl6180_write(self, 0x009f, 0x00, true);
    _vl6180_write(self, 0x00a3, 0x3c, true);
    _vl6180_write(self, 0x00b7, 0x00, true);
    _vl6180_write(self, 0x00bb, 0x3c, true);
    _vl6180_write(self, 0x00b2, 0x09, true);
    _vl6180_write(self, 0x00ca, 0x09, true);
    _vl6180_write(self, 0x0198, 0x01, true);
    _vl6180_write(self, 0x01b0, 0x17, true);
    _vl6180_write(self, 0x01ad, 0x00, true);
    _vl6180_write(self, 0x00ff, 0x05, true);
    _vl6180_write(self, 0x0100, 0x05, true);
    _vl6180_write(self, 0x0199, 0x05, true);
    _vl6180_write(self, 0x01a6, 0x1b, true);
    _vl6180_write(self, 0x01ac, 0x3e, true);
    _vl6180_write(self, 0x01a7, 0x1f, true);
    _vl6180_write(self, 0x0030, 0x00, false);
}

void _vl6180x_setup_for_range(VL6180 *self)
{
    _vl6180_write(self, VL6180X_REG_SYSTEM_GROUPED_PARAMETER_HOLD, 0x1, true);

    _vl6180_write(self, VL6180X_REG_SYSTEM_MODE_GPIO1, 0x10, true);
    _vl6180_write(self, VL6180X_REG_SYSTEM_INTERRUPT_CONFIG_GPIO, 0x01, true);
    _vl6180_write(self, VL6180X_REG_SYSRANGE_THRESH_LOW, 90, true);
    _vl6180_write(self, VL6180X_REG_SYSRANGE_MAX_CONVERGENCE_TIME, 30, true);
    _vl6180_write(self, VL6180X_REG_SYSRANGE_INTERMEASUREMENT_PERIOD, 10, true);
    _vl6180_write(self, VL6180X_REG_SYSRANGE_EARLY_CONVERGENCE_ESTIMATE, 204, true);
    _vl6180_write(self, VL6180X_REG_SYSRANGE_PART_TO_PART_RANGE_OFFSET, 30, true);
    _vl6180_write(self, VL6180X_REG_SYSRANGE_VHV_REPEAT_RATE, 0xFF, true);

    _vl6180_write(self, VL6180X_REG_SYSTEM_GROUPED_PARAMETER_HOLD, 0x0, false);
}

// +--[STATE MACHINE]----------------------------------------------------------=
bool vl6180_state_irqIfaceVl6180_is_ready(const Vl6180_state_irq *handle)
{
    VL6180 *driver        = ((VL6180Private *)handle)->self;
    uint8_t sensor_status = 0;
    _vl6180_read(driver, VL6180X_REG_RESULT_RANGE_STATUS, &sensor_status, 1, false);

    return (0x1 & sensor_status);
}

void vl6180_state_irqIfaceSensor_on_start_calibration(const Vl6180_state_irq *handle)
{
    VL6180 *driver = ((VL6180Private *)handle)->self;
    _vl6180_write(driver, VL6180X_REG_SYSRANGE_VHV_RECALIBRATE, 0x01, false);
}

bool vl6180_state_irqIfaceSensor_is_done_calibrating(const Vl6180_state_irq *handle)
{
    VL6180 *driver         = ((VL6180Private *)handle)->self;
    uint8_t is_calibrating = 1;
    _vl6180_read(driver, VL6180X_REG_SYSRANGE_VHV_RECALIBRATE, &is_calibrating, 1, false);
    return !(is_calibrating);
}

bool vl6180_state_irqIfaceSensor_is_done_configuring(const Vl6180_state_irq *handle)
{
    VL6180 *driver = ((VL6180Private *)handle)->self;
    if (0 == vl6180_state_irqIfaceVl6180_get_config_memo((Vl6180_state_irq *)driver->_private)) {
        vl6180_state_irqIfaceVl6180_set_config_memo((Vl6180_state_irq *)driver->_private, 1);
        _vl6180x_sr03(driver);
        return false;
    } else {
        _vl6180x_setup_for_range(driver);
        return true;
    }
}

bool vl6180_state_irqIfaceVl6180_is_fresh_out_of_reset(const Vl6180_state_irq *handle)
{
    VL6180 *driver                = ((VL6180Private *)handle)->self;
    uint8_t is_fresh_out_of_reset = 0;
    _vl6180_read(driver, VL6180X_REG_SYSTEM_FRESH_OUT_OF_RESET, &is_fresh_out_of_reset, 1, false);
    return is_fresh_out_of_reset;
}

void vl6180_state_irqIfaceSensor_on_start_configuration(const Vl6180_state_irq *handle)
{
}

void vl6180_state_irqIfaceSensor_on_done_configuration(const Vl6180_state_irq *handle)
{
    VL6180 *driver = ((VL6180Private *)handle)->self;
    _vl6180_write(driver, VL6180X_REG_SYSTEM_FRESH_OUT_OF_RESET, 0x00, false);
}

bool vl6180_state_irqIfaceVl6180_did_reset_interrupt(const Vl6180_state_irq *handle)
{
    return true;
}

// +---------------------------------------------------------------------------+
// | TOFDriver::PUBLIC
// +---------------------------------------------------------------------------+

static status_t _vl6180_enable_continuous_ranging(TOFDriver *self)
{
    if (!_vl6180_is_running((VL6180 *)self)) {
        return kStatus_Fail;
    }
    return _vl6180_write((VL6180 *)self, VL6180X_REG_SYSRANGE_START, 0x03, false);
}

static status_t _vl6180_get_range(TOFDriver *self, uint8_t *out_range, uint8_t *out_range_status)
{
    if (!_vl6180_is_running((VL6180 *)self)) {
        return kStatus_Fail;
    }

    status_t bus_status;
    uint8_t range_status;
    if (out_range) {
        *out_range = 0;
    }
    bus_status =
        _vl6180_read((VL6180 *)self, VL6180X_REG_RESULT_RANGE_STATUS, &range_status, 1, false);
    if (!bus_status) {
        if (out_range_status) {
            *out_range_status = range_status;
        }
        if (!(0xF0 & range_status)) {
            bus_status =
                _vl6180_read((VL6180 *)self, VL6180X_REG_RESULT_RANGE_VAL, out_range, 1, false);
        }
    }
    return bus_status;
}

static void _vl6180_service(TOFDriver *self)
{
    VL6180Private *driver_private = (VL6180Private *)((VL6180 *)self)->_private;
    vl6180_state_irq_runCycle((Vl6180_state_irq *)driver_private);
}

static void _vl6180_reset(TOFDriver *self)
{
    VL6180Private *driver_private = (VL6180Private *)((VL6180 *)self)->_private;
    vl6180_state_irqIfaceSensor_raise_reset((Vl6180_state_irq *)driver_private);
}

// +---------------------------------------------------------------------------+
// | VL6180::PUBLIC
// +---------------------------------------------------------------------------+
static status_t _vl6180_get_id(VL6180 *self, VL6180X_ID *out_id)
{
    if (!_vl6180_is_running((VL6180 *)self)) {
        return kStatus_Fail;
    }
    return _vl6180_read(self, VL6180X_REG_IDENTIFICATION__MODEL_ID, (uint8_t *)out_id,
                        sizeof(VL6180X_ID), false);
}

static VL6180 *init_vl6180(VL6180 *driver)
{
    if (driver) {
        BOARD_InitVL6180();
        GPIO_WritePinOutput(BOARD_INITVL6180_I2C1_CS_GPIO, BOARD_INITVL6180_I2C1_CS_GPIO_PIN, 1U);
        BOARD_INITVL6180_I2C1_CS_GPIO->PDDR |= (1U << BOARD_INITVL6180_I2C1_CS_GPIO_PIN);

        GPIO_WritePinOutput(BOARD_INITVL6180_TOF_RDY_GPIO, BOARD_INITVL6180_TOF_RDY_GPIO_PIN, 1U);
        BOARD_INITVL6180_TOF_RDY_GPIO->PDDR |= (1U << BOARD_INITVL6180_TOF_RDY_GPIO_PIN);

        I2C_MasterGetDefaultConfig(&_singleton_private.sensor_bus_config);
        _singleton_private.sensor_bus_tranfer.slaveAddress   = VL6180X_I2C_ADDRESS;
        _singleton_private.sensor_bus_tranfer.subaddress     = 0;
        _singleton_private.sensor_bus_tranfer.subaddressSize = 0;
        _singleton_private.sensor_bus_tranfer.flags          = kI2C_TransferDefaultFlag;
        _singleton_private.sensor_bus_config.baudRate_Bps    = 400000U;
        _singleton_private.sensor_bus_config.enableHighDrive = false;
        _singleton_private.sensor_bus_config.enableMaster    = true;
        _singleton_private.self                              = driver;

        I2C_MasterInit(I2C1, &_singleton_private.sensor_bus_config, CLOCK_GetFreq(I2C1_CLK_SRC));

        driver->super.service                      = _vl6180_service;
        driver->super.reset                        = _vl6180_reset;
        driver->super.enable_continuous_ranging    = _vl6180_enable_continuous_ranging;
        driver->super.get_range                    = _vl6180_get_range;
        driver->super.get_range_status_description = _vl6180x_get_error_description;
        driver->get_id                             = _vl6180_get_id;
        driver->_private                           = &_singleton_private;

        vl6180_state_irq_init((Vl6180_state_irq *)&_singleton_private);
        vl6180_state_irq_enter((Vl6180_state_irq *)&_singleton_private);
    }
    return driver;
}

VL6180 *get_instance_vl6180(VL6180 *driver)
{
    if (!_singleton_addr) {
        _singleton_addr = init_vl6180(&_singleton);
    }
    return _singleton_addr;
}
