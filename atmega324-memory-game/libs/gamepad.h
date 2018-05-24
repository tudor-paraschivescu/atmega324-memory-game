/*
 * gamepad.h
 *
 * Created: 22/05/2018 18:53:56
 *  Author: Tudor
 */ 


#ifndef GAMEPAD_H_
#define GAMEPAD_H_

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "lcd.h"

/*****************************************************************************\
 * Parameters of the gamepad                                                 *
\*****************************************************************************/

/* Registers for the buttons */
#define GAMEPAD_DDR              DDRD
#define GAMEPAD_PORT             PORTD
#define GAMEPAD_PIN              PIND
#define GAMEPAD_PCIE             PCIE3
#define GAMEPAD_PCMSK            PCMSK3

/* Pins for the buttons of the gamepad */
#define GAMEPAD_PIN_UP				PD4
#define GAMEPAD_PIN_DOWN			PD1
#define GAMEPAD_PIN_LEFT			PD0
#define GAMEPAD_PIN_RIGHT			PD5
#define GAMEPAD_PIN_CHANGE_GAME		PD6

/* Pin Change Interrupts for the buttons of the gamepad */
#define GAMEPAD_PCINT_UP			PCINT28
#define GAMEPAD_PCINT_DOWN			PCINT25
#define GAMEPAD_PCINT_LEFT			PCINT24
#define GAMEPAD_PCINT_RIGHT			PCINT29
#define GAMEPAD_PCINT_CHANGE_GAME	PCINT30

/*****************************************************************************\
 * API Gamepad                                                               *
\*****************************************************************************/

/* Initialize the gamepad. */
void gamepad_init(void);

/* Check if UP button is pressed */
int gamepad_is_up_pressed(void);

/* Check if DOWN button is pressed */
int gamepad_is_down_pressed(void);

/* Check if LEFT button is pressed */
int gamepad_is_left_pressed(void);

/* Check if RIGHT button is pressed */
int gamepad_is_right_pressed(void);

/* Check if CHANGE GAME button is pressed */
int gamepad_is_game_pressed(void);

#endif /* GAMEPAD_H_ */