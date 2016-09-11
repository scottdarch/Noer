/*
 * Clementine! NO!                                                   ^ ^
 *                                                                   o o
 *                                                                    m
 * ----------------------------------------------------------------------------
 */
#pragma once

#ifndef __AVR_ATtiny45__
#define __AVR_ATtiny45__
#endif

#define F_CPU 1000000UL
#define F_CPU_KHZ (F_CPU / 1000)
#define TWI_FAST_MODE

#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

// IO HELPERS
#define PIN_INIT_OUTPUT(NAME) PIN_##NAME##_DDRx |= (1 << PIN_##NAME##_DDRxn)
#define PIN_INIT_INPUT(NAME) PIN_##NAME##_DDRx &= ~(1 << PIN_##NAME##_DDRxn)
#define PIN_DISABLE_PULLUP(NAME) PIN_##NAME##_PORTx &= ~(1 << PIN_##NAME##_PORTxn)
#define PIN_OUT_HIGH(NAME) PIN_##NAME##_PORTx |= (1 << PIN_##NAME##_PORTxn)
#define PIN_OUT_LOW(NAME) PIN_##NAME##_PORTx &= ~(1 << PIN_##NAME##_PORTxn)
#define PIN_OUT_TOGGLE(NAME) PIN_##NAME##_PORTx ^= (1 << PIN_##NAME##_PORTxn)
#define PIN_IN_IS_HIGH(NAME) (PIN_##NAME##_PINx & (1 << PIN_##NAME##_PINxn))

//              +---+
//   |RESET,PB5 |   | VCC
//          PB3 |   | PB2,SCL,INT0
// AUD_KEY0,PB4 |   | PB1,STAT
//          GND |   | PB0,SDA
//              +---+

// +--[SOUND TRIGGER GPIO]----------------------------------------------------+
#define PIN_SOUND_TRIGGER_PORTx PORTB
#define PIN_SOUND_TRIGGER_PORTxn PB4
#define PIN_SOUND_TRIGGER_DDRx DDRB
#define PIN_SOUND_TRIGGER_DDRxn DDB4

// +--[RANGE THRESHOLD DETECT]------------------------------------------------+
#define PIN_RANGE_THRESH_DETECT_PORTx PORTB
#define PIN_RANGE_THRESH_DETECT_PORTxn PB2
#define PIN_RANGE_THRESH_DETECT_DDRx DDRB
#define PIN_RANGE_THRESH_DETECT_DDRxn DDB2

// +--[STATUS LED]------------------------------------------------------------+
#define PIN_LED_STATUS_PORTx PORTB
#define PIN_LED_STATUS_PORTxn PB1
#define PIN_LED_STATUS_DDRx DDRB
#define PIN_LED_STATUS_DDRxn DDB1

// +--[TWI/USI]---------------------------------------------------------------+
#define PIN_USI_SDA_PORTx PORTB
#define PIN_USI_SDA_PORTxn PB0
#define PIN_USI_SDA_DDRx DDRB
#define PIN_USI_SDA_DDRxn DDB0

#define PIN_USI_SCL_PORTx PORTB
#define PIN_USI_SCL_PORTxn PB2
#define PIN_USI_SCL_DDRx DDRB
#define PIN_USI_SCL_DDRxn DDB2
#define PIN_USI_SCL_PINx PINB
#define PIN_USI_SCL_PINxn PINB2
