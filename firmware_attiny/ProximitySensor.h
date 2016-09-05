/*
 * Clementine! NO!                                                   ^ ^
 *                                                                   o o
 *                                                                    m
 * ----------------------------------------------------------------------------
 */
#pragma once

#include "mcu.h"

struct ProximitySensor_t;

typedef void (*proximity_threshold_breach)(struct ProximitySensor_t *, void *user_data);

typedef struct ProximitySensor_t {

    uint8_t last_proximity;

    void (*register_proximity_threshold_breach)(struct ProximitySensor_t *self,
                                                proximity_threshold_breach callback,
                                                void *user_data);

    void (*service)(struct ProximitySensor_t *self);
} ProximitySensor;

ProximitySensor *init_proximity_sensor();
