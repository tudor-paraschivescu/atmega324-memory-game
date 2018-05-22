/*
 * rgb_led_matrix.c
 *
 * Created: 22/05/2018 15:02:36
 *  Author: Tudor
 */ 

#include "rgb_led_matrix.h"

/* Set cathode to GND for the given column */
static void set_cathode(int col)
{
	switch (col) {
		case 1:
		MATRIX_C_PORT &= ~(1 << MATRIX_C_COL1);
		break;

		case 2:
		MATRIX_C_PORT &= ~(1 << MATRIX_C_COL2);
		break;

		case 3:
		MATRIX_C_PORT &= ~(1 << MATRIX_C_COL3);
		break;
	}
}

/* Set cathode to Vcc for the given column */
static void unset_cathode(int col)
{
	switch (col) {
		case 1:
		MATRIX_C_PORT |= (1 << MATRIX_C_COL1);
		break;

		case 2:
		MATRIX_C_PORT |= (1 << MATRIX_C_COL2);
		break;

		case 3:
		MATRIX_C_PORT |= (1 << MATRIX_C_COL3);
		break;
	}
}

void RGB_matrix_init(void)
{
	/* initializations */
	int i, j;

	/* set RED rows as output pins */
	MATRIX_R_ROW1_DDR |= (1 << MATRIX_R_ROW1);
	MATRIX_R_ROW2_DDR |= (1 << MATRIX_R_ROW2);
	MATRIX_R_ROW3_DDR |= (1 << MATRIX_R_ROW3);

	/* set GREEN rows as output pins  */
	MATRIX_G_ROW1_DDR |= (1 << MATRIX_G_ROW1);
	MATRIX_G_ROW2_DDR |= (1 << MATRIX_G_ROW2);
	MATRIX_G_ROW3_DDR |= (1 << MATRIX_G_ROW3);

	/* set BLUE rows as output pins */
	MATRIX_B_ROW1_DDR |= (1 << MATRIX_B_ROW1);
	MATRIX_B_ROW2_DDR |= (1 << MATRIX_B_ROW2);
	MATRIX_B_ROW3_DDR |= (1 << MATRIX_B_ROW3);

	/* set CATHODE columns as output pins */
	MATRIX_C_DDR |= (1 << MATRIX_C_COL1)
			| (1 << MATRIX_C_COL2)
			| (1 << MATRIX_C_COL3);

	/* turn off all lights */
	for (i = 1; i <= LED_MATRIX_HEIGHT; i++) {
		for (j = 1; j <= LED_MATRIX_WIDTH; j++) {
			RGB_matrix_turn_off(i, j);
		}
	}
}

void RGB_matrix_turn_on_red(int row, int col)
{
	/* set red color on the given row */
	switch (row) {
	case 1:
		MATRIX_R_ROW1_PORT |= (1 << MATRIX_R_ROW1);
		break;

	case 2:
		MATRIX_R_ROW2_PORT |= (1 << MATRIX_R_ROW2);
		break;

	case 3:
		MATRIX_R_ROW3_PORT |= (1 << MATRIX_R_ROW3);
		break;
	}

	/* set the cathode on the given column */
	set_cathode(col);
}

void RGB_matrix_turn_on_green(int row, int col)
{
	/* set green color on the given row */
	switch (row) {
	case 1:
		MATRIX_G_ROW1_PORT |= (1 << MATRIX_G_ROW1);
		break;

	case 2:
		MATRIX_G_ROW2_PORT |= (1 << MATRIX_G_ROW2);
		break;

	case 3:
		MATRIX_G_ROW3_PORT |= (1 << MATRIX_G_ROW3);
		break;
	}

	/* set the cathode on the given column */
	set_cathode(col);
}

void RGB_matrix_turn_on_blue(int row, int col)
{
	/* set blue color on the given row */
	switch (row) {
	case 1:
		MATRIX_B_ROW1_PORT |= (1 << MATRIX_B_ROW1);
		break;

	case 2:
		MATRIX_B_ROW2_PORT |= (1 << MATRIX_B_ROW2);
		break;

	case 3:
		MATRIX_B_ROW3_PORT |= (1 << MATRIX_B_ROW3);
		break;
	}

	/* set the cathode on the given column */
	set_cathode(col);
}

void RGB_matrix_turn_off(int row, int col)
{
	/* switch off all lights on the given row */
	switch (row) {
		case 1:
		MATRIX_R_ROW1_PORT &= ~(1 << MATRIX_R_ROW1);
		MATRIX_G_ROW1_PORT &= ~(1 << MATRIX_G_ROW1);
		MATRIX_B_ROW1_PORT &= ~(1 << MATRIX_B_ROW1);
		break;

		case 2:
		MATRIX_R_ROW2_PORT &= ~(1 << MATRIX_R_ROW2);
		MATRIX_G_ROW2_PORT &= ~(1 << MATRIX_G_ROW2);
		MATRIX_B_ROW2_PORT &= ~(1 << MATRIX_B_ROW2);
		break;

		case 3:
		MATRIX_R_ROW3_PORT &= ~(1 << MATRIX_R_ROW3);
		MATRIX_G_ROW3_PORT &= ~(1 << MATRIX_G_ROW3);
		MATRIX_B_ROW3_PORT &= ~(1 << MATRIX_B_ROW3);
		break;
	}

	/* unset the cathode on the given column */
	unset_cathode(col);
}