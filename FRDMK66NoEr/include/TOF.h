/**
 * CLEMENTINE! NO!                                ^ ^
 *                                                O O
 *                                                 ~
 *----------------------------------------------U-----U------------------------
 */
#pragma once

#include "fsl_common.h"

struct _TOFDriver;

typedef struct _TOFDriver {
    status_t (*enable_continuous_ranging)(struct _TOFDriver *self);

    status_t (*get_range)(struct _TOFDriver *self, uint8_t *out_range, uint8_t *out_range_status);

    const char *(*get_range_status_description)(uint8_t range_status);

} TOFDriver;
