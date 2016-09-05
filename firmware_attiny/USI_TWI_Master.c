/*****************************************************************************
*
* Atmel Corporation
*
* File              : USI_TWI_Master.c
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
*                     the USI_TWI_Transceive() function. The transceive function
*                     returns a status byte, which can be used to evaluate the
*                     success of the transmission.
*
****************************************************************************/
#include "USI_TWI_Master.h"
#include <util/delay.h>

static unsigned char USI_TWI_Master_Transfer(unsigned char);
static unsigned char USI_TWI_Master_Stop(TWIPeripheral *self);

// +--------------------------------------------------------------------------+
// | PUBLIC
// +--------------------------------------------------------------------------+
static unsigned char USI_TWI_Get_State_Info(TWIPeripheral *self)
{
    return (self->_state.errorState); // Return error state.
}

static bool USI_TWI_Start_Transceiver_With_Data(TWIPeripheral *self, unsigned char *msg,
                                                unsigned char msg_size)
{
    unsigned char tempUSISR_8bit =
        (1 << USISIF) | (1 << USIOIF) | (1 << USIPF) |
        (1 << USIDC) |    // Prepare register value to: Clear flags, and
        (0x0 << USICNT0); // set USI to shift 8 bits i.e. count 16 clock edges.
    unsigned char tempUSISR_1bit =
        (1 << USISIF) | (1 << USIOIF) | (1 << USIPF) |
        (1 << USIDC) |    // Prepare register value to: Clear flags, and
        (0xE << USICNT0); // set USI to shift 1 bit i.e. count 2 clock edges.

    self->_state.errorState  = 0;
    self->_state.addressMode = true;

#ifdef PARAM_VERIFICATION
    if (msg > (unsigned char *)RAMEND) // Test if address is outside SRAM space
    {
        self->_state.errorState = USI_TWI_DATA_OUT_OF_BOUND;
        return (false);
    }
    if (msg_size <= 1) // Test if the transmission buffer is empty
    {
        self->_state.errorState = USI_TWI_NO_DATA;
        return (false);
    }
#endif

#ifdef NOISE_TESTING // Test if any unexpected conditions have arrived prior to this execution.
    if (USISR & (1 << USISIF)) {
        self->_state.errorState = USI_TWI_UE_START_CON;
        return (false);
    }
    if (USISR & (1 << USIPF)) {
        self->_state.errorState = USI_TWI_UE_STOP_CON;
        return (false);
    }
    if (USISR & (1 << USIDC)) {
        self->_state.errorState = USI_TWI_UE_DATA_COL;
        return (false);
    }
#endif

    if (!(*msg & (1 << TWI_READ_BIT))) // The LSB in the address byte determines if is a masterRead
                                       // or masterWrite operation.
    {
        self->_state.masterWriteDataMode = true;
    }

    /* Release SCL to ensure that (repeated) Start can be performed */
    PORT_USI |= (1 << PIN_USI_SCL); // Release SCL.
    while (!(PIN_USI & (1 << PIN_USI_SCL)))
        ; // Verify that SCL becomes high.
#ifdef TWI_FAST_MODE
    _delay_us(T4_TWI / 4); // Delay for T4TWI if TWI_FAST_MODE
#else
    _delay_us(T2_TWI / 4); // Delay for T2TWI if TWI_STANDARD_MODE
#endif

    /* Generate Start Condition */
    PORT_USI &= ~(1 << PIN_USI_SDA); // Force SDA LOW.
    _delay_us(T4_TWI / 4);
    PORT_USI &= ~(1 << PIN_USI_SCL); // Pull SCL LOW.
    PORT_USI |= (1 << PIN_USI_SDA);  // Release SDA.

#ifdef SIGNAL_VERIFY
    if (!(USISR & (1 << USISIF))) {
        self->_state.errorState = USI_TWI_MISSING_START_CON;
        return (false);
    }
#endif

    /*Write address and Read/Write data */
    do {
        /* If masterWrite cycle (or inital address tranmission)*/
        if (self->_state.addressMode || self->_state.masterWriteDataMode) {
            /* Write a byte */
            PORT_USI &= ~(1 << PIN_USI_SCL);         // Pull SCL LOW.
            USIDR = *(msg++);                        // Setup data.
            USI_TWI_Master_Transfer(tempUSISR_8bit); // Send 8 bits on bus.

            /* Clock and verify (N)ACK from slave */
            DDR_USI &= ~(1 << PIN_USI_SDA); // Enable SDA as input.
            if (USI_TWI_Master_Transfer(tempUSISR_1bit) & (1 << TWI_NACK_BIT)) {
                if (self->_state.addressMode)
                    self->_state.errorState = USI_TWI_NO_ACK_ON_ADDRESS;
                else
                    self->_state.errorState = USI_TWI_NO_ACK_ON_DATA;
                return (false);
            }
            self->_state.addressMode = false; // Only perform address transmission once.
        }
        /* Else masterRead cycle*/
        else {
            /* Read a data byte */
            DDR_USI &= ~(1 << PIN_USI_SDA); // Enable SDA as input.
            *(msg++) = USI_TWI_Master_Transfer(tempUSISR_8bit);

            /* Prepare to generate ACK (or NACK in case of End Of Transmission) */
            if (msg_size == 1) // If transmission of last byte was performed.
            {
                USIDR = 0xFF; // Load NACK to confirm End Of Transmission.
            } else {
                USIDR = 0x00; // Load ACK. Set data register bit 7 (output for SDA) low.
            }
            USI_TWI_Master_Transfer(tempUSISR_1bit); // Generate ACK/NACK.
        }
    } while (--msg_size); // Until all data sent/received.

    USI_TWI_Master_Stop(self); // Send a STOP condition on the TWI bus.

    /* Transmission successfully completed*/
    return true;
}

TWIPeripheral *twi_peripheral_init(TWIPeripheral *peripheral)
{
    if (peripheral) {
        peripheral->get_state_info  = USI_TWI_Get_State_Info;
        peripheral->start_with_data = USI_TWI_Start_Transceiver_With_Data;

        PORT_USI |= (1 << PIN_USI_SDA); // Enable pullup on SDA, to set high as released state.
        PORT_USI |= (1 << PIN_USI_SCL); // Enable pullup on SCL, to set high as released state.

        DDR_USI |= (1 << PIN_USI_SCL); // Enable SCL as output.
        DDR_USI |= (1 << PIN_USI_SDA); // Enable SDA as output.

        USIDR = 0xFF;                           // Preload dataregister with "released level" data.
        USICR = (0 << USISIE) | (0 << USIOIE) | // Disable Interrupts.
                (1 << USIWM1) | (0 << USIWM0) | // Set USI in Two-wire mode.
                (1 << USICS1) | (0 << USICS0) |
                (1 << USICLK) | // Software stobe as counter clock source
                (0 << USITC);
        USISR = (1 << USISIF) | (1 << USIOIF) | (1 << USIPF) | (1 << USIDC) | // Clear flags,
                (0x0 << USICNT0);                                             // and reset counter.
    }
    return peripheral;
}

// +--------------------------------------------------------------------------+
// | PRIVATE
// +--------------------------------------------------------------------------+
/*---------------------------------------------------------------
 Core function for shifting data in and out from the USI.
 Data to be sent has to be placed into the USIDR prior to calling
 this function. Data read, will be return'ed from the function.
---------------------------------------------------------------*/
static unsigned char USI_TWI_Master_Transfer(unsigned char temp)
{
    USISR = temp;                                          // Set USISR according to temp.
                                                           // Prepare clocking.
    temp = (0 << USISIE) | (0 << USIOIE) |                 // Interrupts disabled
           (1 << USIWM1) | (0 << USIWM0) |                 // Set USI in Two-wire mode.
           (1 << USICS1) | (0 << USICS0) | (1 << USICLK) | // Software clock strobe as source.
           (1 << USITC);                                   // Toggle Clock Port.
    do {
        _delay_us(T2_TWI / 4);
        USICR = temp; // Generate positve SCL edge.
        while (!(PIN_USI & (1 << PIN_USI_SCL)))
            ; // Wait for SCL to go high.
        _delay_us(T4_TWI / 4);
        USICR = temp;                   // Generate negative SCL edge.
    } while (!(USISR & (1 << USIOIF))); // Check for transfer complete.

    _delay_us(T2_TWI / 4);
    temp  = USIDR;                 // Read out data.
    USIDR = 0xFF;                  // Release SDA.
    DDR_USI |= (1 << PIN_USI_SDA); // Enable SDA as output.

    return temp; // Return the data from the USIDR
}

/*---------------------------------------------------------------
 Function for generating a TWI Stop Condition. Used to release
 the TWI bus.
---------------------------------------------------------------*/
static unsigned char USI_TWI_Master_Stop(TWIPeripheral *self)
{
    PORT_USI &= ~(1 << PIN_USI_SDA); // Pull SDA low.
    PORT_USI |= (1 << PIN_USI_SCL);  // Release SCL.
    while (!(PIN_USI & (1 << PIN_USI_SCL)))
        ; // Wait for SCL to go high.
    _delay_us(T4_TWI / 4);
    PORT_USI |= (1 << PIN_USI_SDA); // Release SDA.
    _delay_us(T2_TWI / 4);

#ifdef SIGNAL_VERIFY
    if (!(USISR & (1 << USIPF))) {
        self->_state.errorState = USI_TWI_MISSING_STOP_CON;
        return (false);
    }
#endif

    return (true);
}
