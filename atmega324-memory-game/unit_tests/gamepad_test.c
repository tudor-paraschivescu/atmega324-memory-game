/*
 * gamepad_test.c
 *
 * Created: 22/05/2018 21:25:16
 *  Author: Tudor
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "../libs/gamepad.h"
#include "../libs/lcd.h"

static char message[16];

int test_gamepad(void)
{
	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;
	int change_game = 0;

	LCD_init();
	LCD_toggleBacklight();
	gamepad_init();

	sprintf(message, "Nothing to see");
	LCD_print(message);

	while (1) {
		if (gamepad_is_up_pressed()) {
			while (gamepad_is_up_pressed());
			sprintf(message, "UP:    %d", ++up);
			LCD_writeInstr(LCD_INSTR_clearDisplay);
			LCD_print(message);
		} else if (gamepad_is_down_pressed()) {
			while (gamepad_is_down_pressed());
			sprintf(message, "DOWN:  %d", ++down);
			LCD_writeInstr(LCD_INSTR_clearDisplay);
			LCD_print(message);
		} else if (gamepad_is_left_pressed()) {
			while (gamepad_is_left_pressed());
			sprintf(message, "LEFT:  %d", ++left);
			LCD_writeInstr(LCD_INSTR_clearDisplay);
			LCD_print(message);
		} else if (gamepad_is_right_pressed()) {
			while (gamepad_is_right_pressed());
			sprintf(message, "RIGHT: %d", ++right);
			LCD_writeInstr(LCD_INSTR_clearDisplay);
			LCD_print(message);
		} else if (gamepad_is_game_pressed()) {
			while (gamepad_is_game_pressed());
			sprintf(message, "GAME:  %d", ++change_game);
			LCD_writeInstr(LCD_INSTR_clearDisplay);
			LCD_print(message);
		}
	}
}