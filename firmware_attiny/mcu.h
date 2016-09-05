/*
 * Clementine! NO!                                                   ^ ^
 *                                                                   o o
 *                                                                    m
 * ----------------------------------------------------------------------------
 */
#pragma once

#define __AVR_ATtiny45__
#define F_CPU 8000.0 // [kHz]
#define TWI_FAST_MODE

#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

// IO HELPERS
#define PIN_INIT_OUTPUT(NAME) PIN_##NAME##_DDRx |= (1 << PIN_##NAME##_DDRxn)
#define PIN_OUT_HIGH(NAME) PIN_##NAME##_PORTx |= (1 << PIN_##NAME##_PORTxn)
#define PIN_OUT_LOW(NAME) PIN_##NAME##_PORTx &= ~(1 << PIN_##NAME##_PORTxn)

// +--[SOUND TRIGGER GPIO]----------------------------------------------------+
#define PIN_SOUND_TRIGGER_PORTx PORTB
#define PIN_SOUND_TRIGGER_PORTxn PORTB4
#define PIN_SOUND_TRIGGER_DDRx DDRB
#define PIN_SOUND_TRIGGER_DDRxn DDB4

// +--[AUDIO PERIPHERALS ENABLE]----------------------------------------------+
#define PIN_SOUND_ENABLE_PORTx PORTB
#define PIN_SOUND_ENABLE_PORTxn PORTB3
#define PIN_SOUND_ENABLE_DDRx DDRB
#define PIN_SOUND_ENABLE_DDRxn DDB3

// +--[STATUS LED]------------------------------------------------------------+
#define PIN_LED_STATUS_PORTx PORTB
#define PIN_LED_STATUS_PORTxn PINB1
#define PIN_LED_STATUS_DDRx DDRB
#define PIN_LED_STATUS_DDRxn DDB1

// +--[TWI/USI]---------------------------------------------------------------+
#define DDR_USI DDRB
#define PORT_USI PORTB
#define PIN_USI PINB
#define PORT_USI_SDA PORTB0
#define PORT_USI_SCL PORTB2
#define PIN_USI_SDA PINB0
#define PIN_USI_SCL PINB2
