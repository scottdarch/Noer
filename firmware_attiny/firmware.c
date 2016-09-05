/*
 * Clementine! NO!                                                   ^ ^
 *                                                                   o o
 *                                                                    m
 * ----------------------------------------------------------------------------
 */
#include "mcu.h"
#include "Dog_stateRequired.h"
#include "ProximitySensor.h"

// +--------------------------------------------------------------------------+
// | DATA
// +--------------------------------------------------------------------------+
static Dog_state _state_machine;
static ProximitySensor *_proximity_sensor;

// +--------------------------------------------------------------------------+
// | PROXIMITY CALLBACK
// +--------------------------------------------------------------------------+
static void _on_proximity_threshold_breached(ProximitySensor *sensor, void *user_data)
{
}

// +--------------------------------------------------------------------------+
// | STATE MACHINE
// +--------------------------------------------------------------------------+
bool dog_stateIface_dog_detected(const Dog_state *handle)
{
    return false;
}

uint16_t dog_stateIface_get_time_millis(const Dog_state *handle)
{
    return 0;
}

bool dog_stateIface_object_detected(const Dog_state *handle)
{
    return false;
}

void dog_stateIface_on_sleep(const Dog_state *handle)
{
}

void dog_stateIface_on_play_no(const Dog_state *handle)
{
}

bool dog_stateIface_is_done_playing_no(const Dog_state *handle)
{
    return false;
}

// +--------------------------------------------------------------------------+
// | MAIN
// +--------------------------------------------------------------------------+
/**
 * Initialize the MCU and its peripherals.
 */
static void setup()
{
    dog_state_init(&_state_machine);

    // Initialize the output to trigger the WTV020SD
    PIN_INIT_OUTPUT(SOUND_TRIGGER);
    PIN_OUT_HIGH(SOUND_TRIGGER);

    // Start with the audio peripherals powered down.
    PIN_INIT_OUTPUT(SOUND_ENABLE);
    PIN_OUT_LOW(SOUND_ENABLE);

    // Turn on the status LED to say we're alive.
    PIN_INIT_OUTPUT(LED_STATUS);
    PIN_OUT_HIGH(LED_STATUS);

    // Initialize Atmel-2561, Using USI as an I2C master
    //_proximity_sensor = init_proximity_sensor();

    //_proximity_sensor->register_proximity_threshold_breach(_proximity_sensor,
    //                                                       _on_proximity_threshold_breached, 0);
    sei();
}

int main(int argc, const char *argv[]) __attribute__((noreturn));

int main(int argc, const char *argv[])
{
    setup();

    while (1) {
        // dog_state_runCycle(&_state_machine);
        //_proximity_sensor->service(_proximity_sensor);
    }
}
