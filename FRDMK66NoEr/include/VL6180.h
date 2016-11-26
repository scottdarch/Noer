/**
 * CLEMENTINE! NO!                                ^ ^
 *                                                O O
 *                                                 ~
 *----------------------------------------------U-----U------------------------
 */
#pragma once

#include <stdint.h>
#include "TOF.h"
#include "fsl_common.h"

#define VL6180X_I2C_ADDRESS 0x29

// +---[REGISTERS]-------------------------------------------------------------+
#define VL6180X_REG_IDENTIFICATION__MODEL_ID 0x000

#define VL6180X_REG_SYSTEM_MODE_GPIO1 0x011
#define VL6180X_REG_SYSTEM_INTERRUPT_CONFIG_GPIO 0x014
#define VL6180X_REG_SYSTEM_INTERRUPT_CLEAR 0x015
#define VL6180X_REG_SYSTEM_FRESH_OUT_OF_RESET 0x016
#define VL6180X_REG_SYSTEM_GROUPED_PARAMETER_HOLD 0x017

#define VL6180X_REG_SYSRANGE_START 0x018
#define VL6180X_REG_SYSRANGE_THRESH_LOW 0x01A
#define VL6180X_REG_SYSRANGE_INTERMEASUREMENT_PERIOD 0x01B
#define VL6180X_REG_SYSRANGE_MAX_CONVERGENCE_TIME 0x01C
#define VL6180X_REG_SYSRANGE_EARLY_CONVERGENCE_ESTIMATE 0x022

#define VL6180X_REG_RESULT_RANGE_STATUS 0x04D
#define VL6180X_REG_RESULT_INTERRUPT_STATUS_GPIO 0x04F
#define VL6180X_REG_RESULT_RANGE_VAL 0x062

#define VL6180X_REG_FIRMWARE_BOOTUP 0x119

// +---[DATATYPES]-------------------------------------------------------------+

typedef struct VL6180X_ID_t {
    uint8_t id : 8;
    uint8_t reserved_0 : 5;
    uint8_t model_maj : 3;
    uint8_t reserved_1 : 5;
    uint8_t model_min : 3;
    uint8_t reserved_2 : 5;
    uint8_t mod_maj : 3;
    uint8_t reserved_3 : 5;
    uint8_t mod_min : 3;
    uint8_t man_year : 4;
    uint8_t man_mon : 4;
    uint8_t man_day : 5;
    uint8_t man_phase : 3;
    uint16_t man_time : 16;
} VL6180X_ID;

static const char *const VL6180X_ERR_0000 = "No error";
static const char *const VL6180X_ERR_0001 = "VCSEL Continuity Test";
static const char *const VL6180X_ERR_0010 = "VCSEL Watchdog Test";
static const char *const VL6180X_ERR_0011 = "VCSEL Watchdog";
static const char *const VL6180X_ERR_0100 = "PLL1 Lock";
static const char *const VL6180X_ERR_0101 = "PLL2 Lock";
static const char *const VL6180X_ERR_0110 = "Early Convergence Estimate";
static const char *const VL6180X_ERR_0111 = "Max Convergence";
static const char *const VL6180X_ERR_1000 = "No Target Ignore";
static const char *const VL6180X_ERR_1001 = "Not used";
static const char *const VL6180X_ERR_1010 = "Not used";
static const char *const VL6180X_ERR_1011 = "Max Signal To Noise Ratio";
static const char *const VL6180X_ERR_1100 = "Raw Ranging Algo Underflow";
static const char *const VL6180X_ERR_1101 = "Raw Ranging Algo Overflow";
static const char *const VL6180X_ERR_1110 = "Ranging Algo Underflow";
static const char *const VL6180X_ERR_1111 = "Ranging Algo Overflow";
static const char *const VL6180X_ERR_XXXX = "(unknown)";

// +---[DRIVER]----------------------------------------------------------------+
struct _VL6180;

typedef struct _VL6180 {
    TOFDriver super;

    status_t (*get_id)(struct _VL6180 *self, VL6180X_ID *out_id);

    void *_private;
} VL6180;

VL6180 *get_instance_vl6180();
