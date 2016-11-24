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

} TOFDriver;
