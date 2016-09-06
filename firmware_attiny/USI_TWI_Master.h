/*****************************************************************************
*
* Atmel Corporation
*
* File              : USI_TWI_Master.h
* Compiler          : AVRGCC Toolchain version 3.4.2
* Revision          : $Revision: 992 $
* Date              : $Date: 2013-11-07 $
* Updated by        : $Author: Atmel $
*
* Support mail      : avr@atmel.com
*
* Supported devices : All device with USI module can be used.
*                     The example is written for the ATmega169, ATtiny26 and ATtiny2313
*
* AppNote           : AVR310 - Using the USI module as a TWI Master
*
* Description       : This is an implementation of an TWI master using
*                     the USI module as basis. The implementation assumes the AVR to
*                     be the only TWI master in the system and can therefore not be
*                     used in a multi-master system.
* Usage             : Initialize the USI module by calling the USI_TWI_Master_Initialise()
*                     function. Hence messages/data are transceived on the bus using
*                     the USI_TWI_Start_Transceiver_With_Data() function. If the transceiver
*                     returns with a fail, then use USI_TWI_Get_Status_Info to evaluate the
*                     couse of the failure.
*
****************************************************************************/
#pragma once

#include "mcu.h"

typedef enum {
    USI_TWI_NO_DATA,
    USI_TWI_SENDING_ADDRESS,       //< Transmission buffer is empty
    USI_TWI_WRITING_DATA,          //< Sending data to the peripheral.
    USI_TWI_READING_DATA,          //< Reading data from a peripheral.
    USI_TWI_ERR_DATA_OUT_OF_BOUND, //< Transmission buffer is outside SRAM space
    USI_TWI_ERR_UE_START_CON,      //< Unexpected Start Condition
    USI_TWI_ERR_UE_STOP_CON,       //< Unexpected Stop Condition
    USI_TWI_ERR_UE_DATA_COL,       //< Unexpected Data Collision (arbitration)
    USI_TWI_ERR_NO_ACK_ON_DATA,    //< The slave did not acknowledge  all data
    USI_TWI_ERR_NO_ACK_ON_ADDRESS, //< The slave did not acknowledge  the address
    USI_TWI_ERR_MISSING_START_CON, //< Generated Start Condition not detected on bus
    USI_TWI_ERR_MISSING_STOP_CON   //< Generated Stop Condition not detected on bus
} USI_TWI_state;

struct TWIPeripheral_t;

/**
 * Abstraction for a single TWI peripheral on a TWI bus.
 */
typedef struct TWIPeripheral_t {

    /**
     * USI Transmit and receive function. LSB of first byte in data
     * indicates if a read or write cycle is performed. If set a read
     * operation is performed.
     *
     * Function generates (Repeated) Start Condition, sends address and
     * R/W, Reads/Writes Data, and verifies/sends ACK.
     *
     * @param  self    The object to apply the method to.
     * @param  read    If true then data will be read from the peripheral else
     *                 data will be written to the peripheral.
     * @return true if successful or or false on error. Use get_state_info to
     *         obtain an error code.
     */
    bool (*start_with_data)(struct TWIPeripheral_t *self, bool read, uint8_t *msg,
                            unsigned char msg_size);

    /**
     * The current state of the driver.
     */
    USI_TWI_state state;

    // +--[PRIVATE]-----------------------------------------------------------+
    uint8_t _device_address;

} TWIPeripheral;

/**
 * Initialize a TWIPeripheral object.
 * TODO: provide the peripheral bus and address to this method.
 * @param   peripheral      The object to initialize.
 * @param   device_address  The device address on the I2C bus.
 * @return The peripheral pointer provided as a parameter.
 */
TWIPeripheral *twi_peripheral_init(TWIPeripheral *peripheral, uint8_t device_address);
