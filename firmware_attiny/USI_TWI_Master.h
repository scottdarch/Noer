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
#include <avr/io.h>
//********** Defines **********//

#ifdef TWI_FAST_MODE                          // TWI FAST mode timing limits. SCL = 100-400kHz
#define T2_TWI ((F_CPU_KHZ * 1300) / 1000000) + 1 // >1,3us
#define T4_TWI ((F_CPU_KHZ * 600) / 1000000) + 1  // >0,6us

#else                                         // TWI STANDARD mode timing limits. SCL <= 100kHz
#define T2_TWI ((F_CPU_KHZ * 4700) / 1000000) + 1 // >4,7us
#define T4_TWI ((F_CPU_KHZ * 4000) / 1000000) + 1 // >4,0us
#endif

// Defines controling code generating
//#define PARAM_VERIFICATION
//#define NOISE_TESTING
//#define SIGNAL_VERIFY

// USI_TWI messages and flags and bit masks
//#define SUCCESS   7
//#define MSG       0
/****************************************************************************
  Bit and byte definitions
****************************************************************************/
#define TWI_READ_BIT 0 // Bit position for R/W bit in "address byte".
#define TWI_ADR_BITS 1 // Bit position for LSB of the slave address bits in the init byte.
#define TWI_NACK_BIT 0 // Bit position for (N)ACK bit.

#define USI_TWI_NO_DATA 0x00           // Transmission buffer is empty
#define USI_TWI_DATA_OUT_OF_BOUND 0x01 // Transmission buffer is outside SRAM space
#define USI_TWI_UE_START_CON 0x02      // Unexpected Start Condition
#define USI_TWI_UE_STOP_CON 0x03       // Unexpected Stop Condition
#define USI_TWI_UE_DATA_COL 0x04       // Unexpected Data Collision (arbitration)
#define USI_TWI_NO_ACK_ON_DATA 0x05    // The slave did not acknowledge  all data
#define USI_TWI_NO_ACK_ON_ADDRESS 0x06 // The slave did not acknowledge  the address
#define USI_TWI_MISSING_START_CON 0x07 // Generated Start Condition not detected on bus
#define USI_TWI_MISSING_STOP_CON 0x08  // Generated Stop Condition not detected on bus

//********** Prototypes **********//

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

TWIPeripheral *twi_peripheral_init(TWIPeripheral *peripheral);
