/*
 * Clementine! NO!                                                   ^ ^
 *                                                                   o o
 *                                                                    m
 * ----------------------------------------------------------------------------
 */
#include "mcu.h"
#include "Dog_stateRequired.h"
#include "ProximitySensor.h"
#include <util/delay.h>
#include <avr/wdt.h>

// +--------------------------------------------------------------------------+
// | DATA
// +--------------------------------------------------------------------------+
static Dog_state _state_machine;
static ProximitySensor *_proximity_sensor;

// +--------------------------------------------------------------------------+
// | TIMER
// +--------------------------------------------------------------------------+
// 136 years before roll-over.
static volatile uint32_t _time_seconds = 0;
// quarter second resolution.
static uint16_t _sub_second_millis = 0;

ISR(TIM0_OVF_vect)
{
    _sub_second_millis += 250;
    if (_sub_second_millis == 1000) {
        _time_seconds += 1;
        _sub_second_millis = 0;
    }
}

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

uint32_t dog_stateIface_get_time_secs(const Dog_state *handle)
{
    return _time_seconds;
}

bool dog_stateIface_object_detected(const Dog_state *handle)
{
    return false;
}

void dog_stateIface_on_sleep(const Dog_state *handle)
{
    // TODO: CPU sleep then reset time since timers would not be running whilst
    // we sleet.
    //_time_seconds = 0;
    //_sub_second_millis = 0;
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
 * Initialize and acquire the proximity sensor for this device.
 */
extern ProximitySensor *init_proximity_sensor();

/**
 * Initialize the MCU and its peripherals.
 */
static void setup()
{
    // 976 times per second the timer/counter will be compared against OCR0A.
    TIMSK |= (1 << OCIE0A);
    TCCR0B |= (1 << CS00) | (1 << CS02);
    // 4 times per second the timer ISR will be invoked.
    OCR0A = 244;

    dog_state_init(&_state_machine);

    // Initialize the output to trigger the WTV020SD
    PIN_INIT_OUTPUT(SOUND_TRIGGER);
    PIN_OUT_LOW(SOUND_TRIGGER);

    // Start with the audio peripherals powered down.
    PIN_INIT_OUTPUT(SOUND_ENABLE);
    PIN_OUT_LOW(SOUND_ENABLE);

    // Turn on the status LED to say we're alive.
    PIN_INIT_OUTPUT(LED_STATUS);
    PIN_OUT_LOW(LED_STATUS);

    // Initialize Atmel-2561, Using USI as an I2C master
    _proximity_sensor = init_proximity_sensor();

    _proximity_sensor->register_proximity_threshold_breach(_proximity_sensor,
                                                           _on_proximity_threshold_breached, 0);
    sei();
}

int main(int argc, const char *argv[])
{
    setup();

    uint32_t last_time_seconds = _time_seconds;

    while (true) {
        dog_state_runCycle(&_state_machine);
        _proximity_sensor->service(_proximity_sensor);
        uint32_t now_seconds = _time_seconds;
        if (now_seconds != last_time_seconds) {
            PIN_OUT_TOGGLE(LED_STATUS);
            last_time_seconds = now_seconds;
        }
    }
}
