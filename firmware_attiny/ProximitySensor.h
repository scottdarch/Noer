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
     * Register a callback with this driver.
     * TODO: provide a mechanism to define the threshold.
     *
     * @param  self    		The driver to register with.
     * @param  callback		The method to invoke when a proximity threshold has
     *                      been breached.
     * @param  user_data	Data to provide to the callback method when invoked.
     */
    void (*register_proximity_threshold_breach)(struct ProximitySensor_t *self,
                                                proximity_threshold_breach callback,
                                                void *user_data);

    /**
     * Run the sensor for a slice of time. This method must not block on I/O.
     * @param  self	The driver to service.
     */
    void (*service)(struct ProximitySensor_t *self);

    // TODO: provide a "to (milli)meters" conversion utility.

} ProximitySensor;
