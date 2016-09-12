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
#include <avr/interrupt.h>
#include <util/atomic.h>

// +--------------------------------------------------------------------------+
// | DATA
// +--------------------------------------------------------------------------+
static Dog_state _state_machine;

// +--------------------------------------------------------------------------+
// | TIMER
// +--------------------------------------------------------------------------+
// 136 years before roll-over.
static volatile uint32_t _time_seconds = 0;
// quarter second resolution.
static uint16_t _sub_second_millis = 0;

// semaphore to tell the main loop to run the state machine asap.
static volatile bool _do_sm_tick = true;

ISR(TIM0_COMPA_vect)
{
    _sub_second_millis += 250;
    if (_sub_second_millis == 1000) {
        _time_seconds += 1;
        _sub_second_millis = 0;
        // Run the state machine once per second. This means that 1 tick == 1 second
        // for its internal logic.
        _do_sm_tick = true;
    }
}

// +--------------------------------------------------------------------------+
// | STATE MACHINE :: IFace :: MCU
// +--------------------------------------------------------------------------+
void dog_stateIfaceMCU_on_init(const Dog_state *handle)
{
    GTCCR |= (1 << TSM);
    TIMSK |= (1 << OCIE0A);
    TCCR0A = (1 << WGM01); // clear timer on compare match.
    // F_CPU/1024: 1000000/1024=976 times per second the timer/counter will be compared against
    // OCR0A.
    TCCR0B = ((1 << CS00) | (1 << CS02));
    // 976/4=244: 4 times per second the timer ISR will be invoked.
    OCR0A = 244;
    GTCCR &= ~(1 << TSM);

    // Initialize the output to trigger the WTV020SD
    PIN_INIT_OUTPUT(SOUND_TRIGGER);
    PIN_OUT_LOW(SOUND_TRIGGER);

    // Turn on the status LED to let the meat puppets know we're alive.
    PIN_INIT_OUTPUT(LED_STATUS);
    PIN_OUT_HIGH(LED_STATUS);

    sei();
}

void dog_stateIfaceMCU_on_sleep(const Dog_state *handle)
{
    // TODO: sleep until the TOF sensor wakes us up.
}

// +--------------------------------------------------------------------------+
// | MAIN
// +--------------------------------------------------------------------------+
int main(int argc, const char *argv[])
{

    dog_state_init(&_state_machine);
    
    dog_state_enter(&_state_machine);

    // Run the state machine at full speed until we've finished initializing.
    while (!dog_state_isStateActive(&_state_machine, Dog_state_firmware_running)) {
        dog_state_runCycle(&_state_machine);
    }

    // Once Initialized we slow down to 1 tick per second and a whole lot of
    // bein' asleep.
    uint32_t last_time_seconds = _time_seconds;

    while (true) {
        ATOMIC_BLOCK(ATOMIC_FORCEON)
        {
            // Do time sensitive stuff here with the interrupts disabled. Don't
            // take more than 100msec or so!
            if (_time_seconds != last_time_seconds) {
                PIN_OUT_TOGGLE(LED_STATUS);
                last_time_seconds = _time_seconds;
            }
            if (_do_sm_tick) {
                _do_sm_tick = false;
                dog_state_runCycle(&_state_machine);
            }
        }
        // TODO: sleep until the next clock tick or until the TOF
        // sensor wakes us up.
    }
}
