/*
 * rgb_led_matrix_test.c
 *
 * Created: 22/05/2018 16:56:21
 *  Author: Tudor
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "../libs/rgb_led_matrix.h"

int test_rgb_led_matrix(void)
{
	/* initializations */
	int row, col;

	RGB_matrix_init();

	for(;;) {

		/* Test 1 red LED */
		for (row = 1; row <= LED_MATRIX_HEIGHT; row++) {
			for (col = 1; col <= LED_MATRIX_WIDTH; col++) {
				RGB_matrix_turn_on_red(row, col);
				_delay_ms(500);
				RGB_matrix_turn_off(row, col);
			}
		}

		/* Test 1 green LED */
		for (row = 1; row <= LED_MATRIX_HEIGHT; row++) {
			for (col = 1; col <= LED_MATRIX_WIDTH; col++) {
				RGB_matrix_turn_on_green(row, col);
				_delay_ms(500);
				RGB_matrix_turn_off(row, col);
			}
		}
		
		/* Test 1 blue LED */
		for (row = 1; row <= LED_MATRIX_HEIGHT; row++) {
			for (col = 1; col <= LED_MATRIX_WIDTH; col++) {
				RGB_matrix_turn_on_blue(row, col);
				_delay_ms(500);
				RGB_matrix_turn_off(row, col);
			}
		}

		_delay_ms(500);
	}
}
