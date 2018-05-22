/*
 * gamepad.c
 *
 * Created: 22/05/2018 18:54:07
 *  Author: Tudor
 */ 

#include "gamepad.h"

void gamepad_init(void)
{	
	/* set the pins that are connected to the buttons as input pins */
	GAMEPAD_DDR &= ~(1 << GAMEPAD_PIN_UP) & ~(1 << GAMEPAD_PIN_DOWN)
			& ~(1 << GAMEPAD_PIN_LEFT) & ~(1 << GAMEPAD_PIN_RIGHT)
			& ~(1 << GAMEPAD_PIN_CHANGE_GAME);

	/* activate the pull-up resistances */
	GAMEPAD_PORT |= (1 << GAMEPAD_PIN_UP) | (1 << GAMEPAD_PIN_DOWN)
			| (1 << GAMEPAD_PIN_LEFT) | (1 << GAMEPAD_PIN_RIGHT)
			| (1 << GAMEPAD_PIN_CHANGE_GAME);
}

int gamepad_is_up_pressed(void)
{
	return !(GAMEPAD_PIN & (1 << GAMEPAD_PIN_UP));
}

int gamepad_is_down_pressed(void)
{
	return !(GAMEPAD_PIN & (1 << GAMEPAD_PIN_DOWN));
}

int gamepad_is_left_pressed(void)
{
	return !(GAMEPAD_PIN & (1 << GAMEPAD_PIN_LEFT));
}

int gamepad_is_right_pressed(void)
{
	return !(GAMEPAD_PIN & (1 << GAMEPAD_PIN_RIGHT));
}

int gamepad_is_game_pressed(void)
{
	return !(GAMEPAD_PIN & (1 << GAMEPAD_PIN_CHANGE_GAME));
}