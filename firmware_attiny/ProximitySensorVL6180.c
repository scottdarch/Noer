/*
 * Clementine! NO!                                                   ^ ^
 *                                                                   o o
 *                                                                    m
 * ----------------------------------------------------------------------------
 */

#include "ProximitySensor.h"
#include "USI_TWI_Master.h"

#define PROXIMITY_SENSOR_ADDR 0x29

typedef void (*proximity_threshold_breach)(struct ProximitySensor_t *, void *user_data);

typedef struct ProximitySensorVL6180_t {
    ProximitySensor super;
    void *_callback_user_data;
    proximity_threshold_breach _callback;
    TWIPeripheral _interface;
} ProximitySensorVL6180;

/**
 * This implementation assumes a single, specific proximity sensor.
 */
ProximitySensorVL6180 _the_proximity_sensor;

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
}

ProximitySensor *init_proximity_sensor()
{
    _the_proximity_sensor.super.service = _service;
    _the_proximity_sensor.super.register_proximity_threshold_breach =
        _register_proximity_threshold_breach;
    _the_proximity_sensor.super.last_proximity = 0;
    _the_proximity_sensor._callback            = 0;
    _the_proximity_sensor._callback_user_data = 0;
    twi_peripheral_init(&_the_proximity_sensor._interface);
    // Falling SDA edge (e.g. start condition) triggers the INT0 interrupt.
    MCUCR |= (1 << ISC01);
    // Enable INT0
    GIMSK |= (1 << INT0);

    return &_the_proximity_sensor.super;
}
