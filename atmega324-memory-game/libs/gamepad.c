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
	if (!(GAMEPAD_PIN & (1 << GAMEPAD_PIN_UP))) {
		/* wait for the button press to end */
		while (!(GAMEPAD_PIN & (1 << GAMEPAD_PIN_UP)));
		return 1;
	}

	return 0;
}

int gamepad_is_down_pressed(void)
{
	if (!(GAMEPAD_PIN & (1 << GAMEPAD_PIN_DOWN))) {
		/* wait for the button press to end */
		while (!(GAMEPAD_PIN & (1 << GAMEPAD_PIN_DOWN)));
		return 1;
	}

	return 0;
}

int gamepad_is_left_pressed(void)
{
	if (!(GAMEPAD_PIN & (1 << GAMEPAD_PIN_LEFT))) {
		/* wait for the button press to end */
		while (!(GAMEPAD_PIN & (1 << GAMEPAD_PIN_LEFT)));
		return 1;
	}

	return 0;
}

int gamepad_is_right_pressed(void)
{
	if (!(GAMEPAD_PIN & (1 << GAMEPAD_PIN_RIGHT))) {
		/* wait for the button press to end */
		while (!(GAMEPAD_PIN & (1 << GAMEPAD_PIN_RIGHT)));
		return 1;
	}

	return 0;
}

int gamepad_is_game_pressed(void)
{
	if (!(GAMEPAD_PIN & (1 << GAMEPAD_PIN_CHANGE_GAME))) {
		/* wait for the button press to end */
		while (!(GAMEPAD_PIN & (1 << GAMEPAD_PIN_CHANGE_GAME)));
		return 1;
	}

	return 0;
}