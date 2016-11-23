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

#include "fsl_i2c.h"

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

#define VL6180X_I2C_ADDRESS 0x29

#define VL6180X_REG_IDENTIFICATION__MODEL_ID 0x000

i2c_master_handle_t _sensor_bus;
i2c_master_config_t _sensor_bus_config;
i2c_master_transfer_t _sensor_bus_tranfer;

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
    BOARD_InitVL6180();
    BOARD_InitUSB();
    BOARD_BootClockHSRUN();
    BOARD_InitDebugConsole();

    PRINTF("FRDMK66 is pretty cool\n");
    GPIO_WritePinOutput(BOARD_INITVL6180_I2C1_CS_GPIO, BOARD_INITVL6180_I2C1_CS_GPIO_PIN, 1U);
    BOARD_INITVL6180_I2C1_CS_GPIO->PDDR |= (1U << BOARD_INITVL6180_I2C1_CS_GPIO_PIN);

    GPIO_WritePinOutput(BOARD_INITVL6180_TOF_RDY_GPIO, BOARD_INITVL6180_TOF_RDY_GPIO_PIN, 1U);
    BOARD_INITVL6180_TOF_RDY_GPIO->PDDR |= (1U << BOARD_INITVL6180_TOF_RDY_GPIO_PIN);

    LED_RED_INIT(0);
    LED_BLUE_INIT(1);

    I2C_MasterGetDefaultConfig(&_sensor_bus_config);
    _sensor_bus_config.baudRate_Bps    = 400000U;
    _sensor_bus_config.enableHighDrive = false;
    _sensor_bus_config.enableMaster    = true;

    I2C_MasterInit(I2C1, &_sensor_bus_config, CLOCK_GetFreq(I2C1_CLK_SRC));

    memset(&_sensor_bus_tranfer, 0, sizeof(_sensor_bus_tranfer));
    memset(&_sensor_bus, 0, sizeof(_sensor_bus));
    uint16_t addr    = VL6180X_REG_IDENTIFICATION__MODEL_ID;
    uint8_t model_id = 0;
    VL6180X_ID id;

    _sensor_bus_tranfer.slaveAddress   = VL6180X_I2C_ADDRESS;
    _sensor_bus_tranfer.subaddress     = 0;
    _sensor_bus_tranfer.subaddressSize = 0;

    LED_RED_OFF();

    while (1) {
        LED_BLUE_ON();
        _sensor_bus_tranfer.direction = kI2C_Write;
        _sensor_bus_tranfer.flags     = kI2C_TransferNoStopFlag;
        _sensor_bus_tranfer.data      = (uint8_t *)&addr;
        _sensor_bus_tranfer.dataSize = 2;
        I2C_MasterTransferBlocking(I2C1, &_sensor_bus_tranfer);
        _sensor_bus_tranfer.direction = kI2C_Read;
        _sensor_bus_tranfer.flags     = kI2C_TransferRepeatedStartFlag;
        _sensor_bus_tranfer.data      = (uint8_t *)&model_id;
        _sensor_bus_tranfer.dataSize = 1;
        I2C_MasterTransferBlocking(I2C1, &_sensor_bus_tranfer);

        PRINTF("ID:%X\n", model_id);

        Delay(100);
        LED_BLUE_OFF();
        Delay(100);
    }
}
