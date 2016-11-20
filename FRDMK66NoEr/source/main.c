#include "fsl_debug_console.h"
#include "fsl_smc.h"
#include "fsl_pmc.h"
#include "board.h"
#include "fsl_lptmr.h"
#include "arm_math.h"
#include "pin_mux.h"
#include "clock_config.h"

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
    BOARD_InitVL6180();
    BOARD_InitUSB();
    BOARD_BootClockHSRUN();
    BOARD_InitDebugConsole();

    while (1) {
        PRINTF("Hello Teensy\n");
    }
}
