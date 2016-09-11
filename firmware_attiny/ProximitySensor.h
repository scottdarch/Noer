/*
 * Clementine! NO!                                                   ^ ^
 *                                                                   o o
 *                                                                    m
 * ----------------------------------------------------------------------------
 */
#pragma once

#include "mcu.h"

struct ProximitySensor_t;

/**
 * Callback type.
 */
typedef void (*proximity_threshold_breach)(struct ProximitySensor_t *, void *user_data);

/**
 * A proximity sensor like a ToF IC or one of the Sharp infrared range finders.
 */
typedef struct ProximitySensor_t {

    /**
     * 0 - 255. The last proximity recorded.
     */
    uint8_t last_proximity;

    /**
     * Run the sensor for a slice of time. This method must not block on I/O.
     * @param  self	The driver to service.
     */
    void (*service)(struct ProximitySensor_t *self);

    // TODO: provide a "to (milli)meters" conversion utility.

} ProximitySensor;
