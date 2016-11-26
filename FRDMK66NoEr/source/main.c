/**
 * CLEMENTINE! NO!                                ^ ^
 *                                                O O
 *                                                 ~
 *----------------------------------------------U-----U------------------------
 */
#include "fsl_debug_console.h"
#include "fsl_smc.h"
#include "fsl_pmc.h"
#include "board.h"
#include "fsl_lptmr.h"
#include "arm_math.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "VL6180.h"

/* Delay some time united in milliseconds. */
void Delay(uint32_t milliseconds)
{
    uint32_t i;
    uint32_t j;

    for (i = 0; i < milliseconds; i++) {
        for (j = 0; j < 10000U; j++) {
            __asm("NOP");
        }
    }
}

void SysTick_Handler(void)
{
}

int main()
{
    BOARD_InitPins();
    BOARD_InitBUTTONs();
    BOARD_InitLEDs();
    BOARD_InitSDHC0();
    BOARD_InitDEBUG_UART();
    BOARD_InitUSB();
    BOARD_BootClockHSRUN();
    BOARD_InitDebugConsole();

    PRINTF("FRDMK66 is pretty cool\n");
    LED_RED_INIT(0);
    LED_GREEN_INIT(1);
    LED_BLUE_INIT(1);

    TOFDriver *tof = (TOFDriver *)&get_instance_vl6180()->super;
    tof->enable_continuous_ranging(tof);
    LED_RED_OFF();

    uint8_t range, range_status;
    status_t bus_status;
    while (1) {
        LED_BLUE_ON();

        bus_status = tof->get_range(tof, &range, &range_status);
        if (!bus_status) {
            if (!(0xF0 & range_status) && range > 0) {
                LED_RED_ON();
            } else {
                LED_RED_OFF();
            }
            PRINTF("RANGE: %d, %s\n", range, tof->get_range_status_description(range_status >> 4));
        } else {
            PRINTF("BUS ERROR: %d\n", bus_status);
        }
        Delay(100);
        LED_BLUE_OFF();
        Delay(100);
    }
}
