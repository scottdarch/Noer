/*
 * Generated by erpcgen 1.3.0 on Mon Sep  5 16:12:47 2016.
 *
 * AUTOGENERATED - DO NOT EDIT
 */

#if !defined(_erpc_dac_adc_h_)
#define _erpc_dac_adc_h_

#include <stdint.h>
#include <stdbool.h>

// Aliases data types declarations
typedef struct AdcConfig AdcConfig;
typedef struct Vector Vector;

// Structures data types declarations
struct AdcConfig
{
    float vref;
    float atomicSteps;
};

struct Vector
{
    int16_t A_x;
    int16_t A_y;
    int16_t A_z;
    int16_t M_x;
    int16_t M_y;
    int16_t M_z;
};

// Constant variable declarations
extern const uint8_t StringMaxSize;

/*! @brief dac_adc identifiers */
enum _dac_adc_ids
{
    kdac_adc_service_id = 1,
    kdac_adc_adc_get_config_id = 1,
    kdac_adc_convert_dac_adc_id = 2,
    kdac_adc_set_led_id = 3,
    kdac_adc_init_mag_accel_id = 4,
    kdac_adc_read_senzor_mag_accel_id = 5,
    kdac_adc_board_get_name_id = 6,
};

#if defined(__cplusplus)
extern "C" {
#endif

//! @name dac_adc
//@{
void adc_get_config(AdcConfig * config);

void convert_dac_adc(uint32_t numberToConvert, uint32_t * result);

void set_led(uint8_t whichLed);

int32_t init_mag_accel(void);

void read_senzor_mag_accel(Vector * results);

void board_get_name(char * name);
//@}

#if defined(__cplusplus)
}
#endif

#endif // _erpc_dac_adc_h_
