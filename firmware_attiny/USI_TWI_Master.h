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
     * @param  self	The object to apply the method to.
     * @return true if successful or or false on error. Use get_state_info to
     *         obtain an error code.
     */
    bool (*start_with_data)(struct TWIPeripheral_t *self, unsigned char *msg,
                            unsigned char msg_size);

    /**
     * Retrieve the last error code.
     */
    unsigned char (*get_state_info)(struct TWIPeripheral_t *self);

    // +--[PRIVATE]-----------------------------------------------------------+
    union USI_TWI_state {
        unsigned char
            errorState; // Can reuse the TWI_state for error states due to that it will not be
                        // need if there exists an error.
        struct {
            unsigned char addressMode : 1;
            unsigned char masterWriteDataMode : 1;
            unsigned char unused : 6;
        };
    } _state;
} TWIPeripheral;

/**
 * Initialize a TWIPeripheral object.
 * TODO: provide the peripheral bus and address to this method.
 * @param  peripheral	The object to initialize.
 * @return The peripheral pointer provided as a parameter.
 */
TWIPeripheral *twi_peripheral_init(TWIPeripheral *peripheral);
