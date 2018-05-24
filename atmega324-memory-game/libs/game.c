/*
 * game.c
 *
 * Created: 22/05/2018 21:21:55
 *  Author: Tudor
 */ 

#include "game.h"

/* the current game mode. At the beginning, no game was selected */
volatile int current_game_mode = -1;

/* signals if a game ended */
volatile int game_end = 1;

/* Names of the game modes */
const char game_modes[GAME_MODES][16] = {
		"MATCH ME",
		"HAMMERING HANDS",
		"GREEN HAMM HANDS",
		"BLUE CENTER SHOT"
};

/* variables used in hammering hands game mode */
volatile int hh_correct = 0;	/* signals press of the correct button */
volatile int hh_button;			/* stores the button that should be pressed */
volatile int hh_row, hh_col;	/* coords of LED */

/* variables used in blue center shot game mode */
volatile int scores[4] = { 0, 0, 0, 0 };	/* UP, DOWN, LEFT, RIGHT */
volatile int is_blue = 0;
volatile int player = -1;
volatile int bcs_row, bcs_col;

static void get_row_and_col(int nr, volatile int *row, volatile int *col)
{
	switch (nr) {
		case 0:
		/* UP side */
		*row = 1;
		*col = 2;
		break;
		
		case 1:
		/* DOWN side */
		*row = 3;
		*col = 2;
		break;

		case 2:
		/* LEFT side */
		*row = 2;
		*col = 1;
		break;

		case 3:
		/* RIGHT side */
		*row = 2;
		*col = 3;
		break;
	}
}

ISR(PCINT3_vect)
{
	if (current_game_mode == HAMMERING_HANDS && !game_end) {
		switch (hh_button) {
		case 0:
			/* UP side */
			if (gamepad_is_up_pressed()) {
				hh_correct = 1;
			}
			break;
			
		case 1:
			/* DOWN side */
			if (gamepad_is_down_pressed()) {
				hh_correct = 1;
			}
			break;

		case 2:
			/* LEFT side */
			if (gamepad_is_left_pressed()) {
				hh_correct = 1;
			}
			break;

		case 3:
			/* RIGHT side */
			if (gamepad_is_right_pressed()) {
				hh_correct = 1;
			}
			break;
		}

		/* disable interrupts so you cannot press more than one button */
		cli();

		if (hh_correct) {
			/* turn off the LED that showed what button to press */
			RGB_matrix_turn_off(hh_row, hh_col);

			/* turn all lights green */
			for (int k = 1; k <= LED_MATRIX_HEIGHT; k++) {
				RGB_matrix_turn_on_green(k, k);
			}
		}

	} else if (current_game_mode == GREEN_HAMMERING_HANDS && !game_end) {
		switch (hh_button) {
		case -1:
			/* no button should have been pressed */
			hh_correct = -1;
			break;

		case 0:
			/* UP side */
			if (gamepad_is_up_pressed()) {
				hh_correct = 1;
			}
			break;
			
		case 1:
			/* DOWN side */
			if (gamepad_is_down_pressed()) {
				hh_correct = 1;
			}
			break;

		case 2:
			/* LEFT side */
			if (gamepad_is_left_pressed()) {
				hh_correct = 1;
			}
			break;

		case 3:
			/* RIGHT side */
			if (gamepad_is_right_pressed()) {
				hh_correct = 1;
			}
			break;
		}
		
		if (hh_correct) {
			/* turn off the LED that showed what button to press */
			RGB_matrix_turn_off(hh_row, hh_col);

			/* disable interrupts so you cannot press more than one button */
			cli();

			if (hh_correct == -1) {
				/* turn all lights red */
				for (int k = 1; k <= LED_MATRIX_HEIGHT; k++) {
					RGB_matrix_turn_on_red(k, k);
				}
				
			} else if (hh_correct == 1) {
				/* turn all lights green */
				for (int k = 1; k <= LED_MATRIX_HEIGHT; k++) {
					RGB_matrix_turn_on_green(k, k);
				}
			}
		}

	} else if (current_game_mode == BLUE_CENTER_SHOT && !game_end) {
		/* disable interrupts and take into account only first player */
		cli();

		/* find the player who pressed the button */
		if (gamepad_is_up_pressed()) {
			player = 0;
		} else if (gamepad_is_down_pressed()) {
			player = 1;
		} else if (gamepad_is_left_pressed()) {
			player = 2;
		} else if (gamepad_is_right_pressed()) {
			player = 3;
		}

		if (player != -1) {
			/* turn off center LED */
			RGB_matrix_turn_off(2, 2);
			_delay_ms(10);

			/* update score */
			if (is_blue) {
				scores[player] += 1;
			} else {
				scores[player] -= 1;
			}

			/* signal correct/wrong answer */
			get_row_and_col(player, &bcs_row, &bcs_col);
			if (is_blue) {
				RGB_matrix_turn_on_green(bcs_row, bcs_col);
			} else {
				RGB_matrix_turn_on_red(bcs_row, bcs_col);
			}
		}

	} else if (gamepad_is_game_pressed() && game_end) {
		/* go to next game */
		current_game_mode += 1;
		if (current_game_mode >= GAME_MODES) {
			current_game_mode = -1;
		}
		
		/* try to limit button bounce */
		_delay_ms(50);
	}
}

void game_init(void)
{
	/* initialize LCD */
	LCD_init();
	LCD_toggleBacklight();
	LCD_print2("Let's play!", "   Press GAME...");

	/* initialize LED matrix */
	RGB_matrix_init();
	
	/* initialize gamepad */
	gamepad_init();

	/* enable interrupts */
	sei();
	
	/* activate interrupts */
	PCICR |= (1 << GAMEPAD_PCIE);
	GAMEPAD_PCMSK |= (1 << GAMEPAD_PCINT_CHANGE_GAME) | (1 << GAMEPAD_PCINT_UP)
			| (1 << GAMEPAD_PCINT_DOWN) | (1 << GAMEPAD_PCINT_LEFT)
			| (1 << GAMEPAD_PCINT_RIGHT);
}

void game_start(void)
{
	int i;

	while (1) {
		switch (current_game_mode) {
		case -1:
			break;

		default:
			/* disable interrupts so the game cannot be changed */
			cli();

			/* show message that the game will be starting in 3 */
			LCD_print2(game_modes[current_game_mode], "Starts in 3");

			/* turn all lights red */
			for (i = 1; i <= LED_MATRIX_HEIGHT; i++) {
				RGB_matrix_turn_on_red(i, i);
			}

			_delay_ms(1000);
			
			/* show message that the game will be starting in 2 */
			LCD_print2(game_modes[current_game_mode], "Starts in 3 2");

			/* turn off first light */
			RGB_matrix_turn_off(1, 1);

			_delay_ms(1000);

			/* show message that the game will be starting in 1 */
			LCD_print2(game_modes[current_game_mode], "Starts in 3 2 1");

			/* turn off second light */
			RGB_matrix_turn_off(2, 2);

			_delay_ms(1000);

			/* show message that the game is playing */
			LCD_print2(game_modes[current_game_mode], "is played");

			/* turn off last column */
			RGB_matrix_turn_off(3, 3);

			/* the game is on */
			game_end = 0;

			switch (current_game_mode) {
				case MATCH_ME:
					game_match_me();
					break;

				case HAMMERING_HANDS:
					game_hammering_hands();
					break;

				case GREEN_HAMMERING_HANDS:
					game_green_hammering_hands();
					break;

				case BLUE_CENTER_SHOT:
					game_blue_center_shot();
					break;
			}

			/* the game ended */
			game_end = 1;

			LCD_print2("You have 5s to", "change the game!");

			/* enable interrupts */
			sei();

			_delay_ms(5000);

			if (current_game_mode == -1) {
				LCD_print2("Let's play!", "   Press GAME...");
			}
		}
	}
}

void game_match_me(void)
{
	int i, j, k, lost, row = 0, col = 0;
	int lines[MATCH_ME_ROUNDS];
	char msg[16];

	_delay_ms(2000);

	for (i = 0; i < MATCH_ME_ROUNDS; i++) {
		/* print round */
		sprintf(msg, "ROUND %d", i + 1);
		LCD_print2(game_modes[MATCH_ME], msg);

		/* generate a random number to select the side */
		lines[i] = rand() % 4;

		for (j = 0; j <= i; j++) {
			get_row_and_col(lines[j], &row, &col);

			RGB_matrix_turn_on_blue(row, col);
			_delay_ms(500);

			RGB_matrix_turn_off(row, col);
			_delay_ms(500);
		}

		j = 0;
		lost = 0;

		while (1) {
			switch (lines[j]) {
			case 0:
				/* UP side */
				if (gamepad_is_up_pressed()) {
					j++;	/* go to next press */
				} else if (gamepad_is_down_pressed()
						|| gamepad_is_left_pressed()
						|| gamepad_is_right_pressed()) {
					lost = 1;
				}
				break;
				
			case 1:
				/* DOWN side */
				if (gamepad_is_down_pressed()) {
					j++;	/* go to next press */
				} else if (gamepad_is_up_pressed()
						|| gamepad_is_left_pressed()
						|| gamepad_is_right_pressed()) {
					lost = 1;
				}
				break;

			case 2:
				/* LEFT side */
				if (gamepad_is_left_pressed()) {
					j++;	/* go to next press */
				} else if (gamepad_is_up_pressed()
						|| gamepad_is_down_pressed()
						|| gamepad_is_right_pressed()) {
					lost = 1;
				}
				break;

			case 3:
				/* RIGHT side */
				if (gamepad_is_right_pressed()) {
					j++;	/* go to next press */
				} else if (gamepad_is_up_pressed()
						|| gamepad_is_down_pressed()
						|| gamepad_is_left_pressed()) {
					lost = 1;
				}
				break;
			}

			/* small delay as the buttons are not pressed that fast */
			_delay_ms(20);

			if (j > i) {
				/* the sequence was correct */
				break;			
			}

			if (lost) {
				/* a button was wrongly pressed */
				break;
			}
		}

		if (!lost) {
			sprintf(msg, "ROUND %d PASSED", i + 1);
			LCD_print2(game_modes[MATCH_ME], msg);

			/* turn all lights green */
			for (k = 1; k <= LED_MATRIX_HEIGHT; k++) {
				RGB_matrix_turn_on_green(k, k);
			}
		} else {
			/* turn all lights red */
			for (k = 1; k <= LED_MATRIX_HEIGHT; k++) {
				RGB_matrix_turn_on_red(k, k);
			}
		}

		_delay_ms(500);

		/* turn off the lights */
		for (k = 1; k <= LED_MATRIX_HEIGHT; k++) {
			RGB_matrix_turn_off(k, k);
		}

		if (lost) {
			break;
		}
		
		_delay_ms(1500);
	}

	if (!lost) {
		LCD_print2(game_modes[MATCH_ME], "VICTORY !!!");
	} else {
		LCD_print2(game_modes[MATCH_ME], "YOU LOST");
	}

	_delay_ms(3000);
}

void game_hammering_hands(void)
{
	int line, i, k;
	char msg[16];

	for (i = 1; i <= HAMMERING_HANDS_ROUNDS; i++) {
		/* print round */
		sprintf(msg, "ROUND %d", i);
		LCD_print2(game_modes[HAMMERING_HANDS], msg);

		_delay_ms(1500);

		hh_correct = 0;

		/* generate a random number to select the side */
		line = rand() % 4;
		hh_button = line;

		get_row_and_col(line, &hh_row, &hh_col);

		/* enable interrupts */
		sei();

		/* signal the button to press */
		RGB_matrix_turn_on_blue(hh_row, hh_col);
		_delay_ms(HAMMERING_HANDS_REACTION_TIME);

		/* disable interrupts */
		cli();

		if (!hh_correct) {
			/* turn off the LED that showed what button to press */
			RGB_matrix_turn_off(hh_row, hh_col);

			/* turn all lights red */
			for (k = 1; k <= LED_MATRIX_HEIGHT; k++) {
				RGB_matrix_turn_on_red(k, k);
			}
		}

		_delay_ms(500);

		/* turn off the lights */
		for (k = 1; k <= LED_MATRIX_HEIGHT; k++) {
			RGB_matrix_turn_off(k, k);
		}

		if (!hh_correct) {
			break;
		}
	}

	if (hh_correct) {
		LCD_print2(game_modes[HAMMERING_HANDS], "VICTORY !!!");
	} else {
		LCD_print2(game_modes[HAMMERING_HANDS], "YOU LOST");
	}

	_delay_ms(3000);
}

void game_green_hammering_hands(void)
{
	int line, i, j, k, wrong;
	char msg[16];

	for (i = 1; i <= GREEN_HAMMERING_HANDS_ROUNDS; i++) {
		/* print round */
		sprintf(msg, "ROUND %d", i);
		LCD_print2(game_modes[GREEN_HAMMERING_HANDS], msg);

		_delay_ms(1500);

		hh_correct = 0;
		hh_button = -1;

		/* generate a random number to select wrong sides */
		wrong = rand() % 5;
		
		/* light up sides of different colors than green */
		for (j = 0; j < wrong; j++) {
			/* enable interrupts */
			sei();

			line = rand() % 4;
			get_row_and_col(line, &hh_row, &hh_col);

			/* signal the button not to press */
			if (j % 2) {
				RGB_matrix_turn_on_blue(hh_row, hh_col);
			} else {
				RGB_matrix_turn_on_red(hh_row, hh_col);
			}
			
			_delay_ms(GREEN_HAMMERING_HANDS_REACTION_TIME);

			if (hh_correct == 0) {
				RGB_matrix_turn_off(hh_row, hh_col);
			} else if (hh_correct == -1) {
				_delay_ms(500);

				/* turn off the lights */
				for (k = 1; k <= LED_MATRIX_HEIGHT; k++) {
					RGB_matrix_turn_off(k, k);
				}

				break;
			}

			/* disable interrupts */
			cli();

			_delay_ms(1000);
		}

		if (hh_correct == -1) {
			break;
		}

		/* generate a random number to select the side */
		line = rand() % 4;
		hh_button = line;
		get_row_and_col(line, &hh_row, &hh_col);

		/* enable interrupts */
		sei();

		/* signal the button to press */
		RGB_matrix_turn_on_green(hh_row, hh_col);
		_delay_ms(GREEN_HAMMERING_HANDS_REACTION_TIME);

		/* disable interrupts */
		cli();

		if (hh_correct != 1) {
			/* turn off the LED that showed what button to press */
			RGB_matrix_turn_off(hh_row, hh_col);

			/* turn all lights red */
			for (k = 1; k <= LED_MATRIX_HEIGHT; k++) {
				RGB_matrix_turn_on_red(k, k);
			}
		}

		_delay_ms(500);

		/* turn off the lights */
		for (k = 1; k <= LED_MATRIX_HEIGHT; k++) {
			RGB_matrix_turn_off(k, k);
		}

		if (hh_correct != 1) {
			break;
		}
	}

	if (hh_correct == 1) {
		LCD_print2(game_modes[GREEN_HAMMERING_HANDS], "VICTORY !!!");
	} else {
		LCD_print2(game_modes[GREEN_HAMMERING_HANDS], "YOU LOST");
	}

	_delay_ms(3000);
}

void print_score()
{
	char msg1[16], msg2[16], aux[16];
	int i, len;

	/* scores for UP and DOWN */
	sprintf(msg1, "U %d", scores[0]);
	sprintf(aux, "%d D", scores[1]);

	/* format the space between scores */
	len = 16 - strlen(msg1) - strlen(aux);
	for (i = 0; i < len; i++) {
		strcat(msg1, " ");
	}
	strcat(msg1, aux);

	/* scores for LEFT and RIGHT */
	sprintf(msg2, "L %d", scores[2]);
	sprintf(aux, "%d R", scores[3]);

	/* format the space between scores */
	len = 16 - strlen(msg2) - strlen(aux);
	for (i = 0; i < len; i++) {
		strcat(msg2, " ");
	}
	strcat(msg2, aux);

	LCD_print2(msg1, msg2);
}

char get_player_name(int nr)
{
	switch (nr) {
	case 0:
		return 'U';
	case 1:
		return 'D';
	case 2:
		return 'L';
	case 3:
		return 'R';
	default:
		return '-';
	}
}

void game_center_shot(void)
{
}

void game_blue_center_shot(void)
{
	int color, i, max = INT_MIN;
	char msg[16], aux[16];

	/* reset scores */
	for (i = 0; i < 4; i++)
		scores[i] = 0;

	for (i = 1; i <= BLUE_CENTER_SHOT_ROUNDS; i++) {
		/* show score */
		print_score();
		_delay_ms(1000);

		/* initialise round */
		is_blue = 0;
		player = -1;

		/* generate a random number to select the color */
		color = rand() % 3;

		switch (color) {
		case 0:
			RGB_matrix_turn_on_red(2, 2);
			break;

		case 1:
			RGB_matrix_turn_on_green(2, 2);
			break;

		case 2:
			is_blue = 1;
			RGB_matrix_turn_on_blue(2, 2);
			break;
		}

		/* enable interrupts */
		sei();

		/* signal the button to press */
		_delay_ms(BLUE_CENTER_SHOT_REACTION_TIME);

		if (player == -1) {
			/* disable interrupts */
			cli();

			/* nobody pressed any button */
			RGB_matrix_turn_off(2, 2);	
		} else {
			_delay_ms(500);
			RGB_matrix_turn_off(bcs_row, bcs_col);
		}

		_delay_ms(500);
	}

	/* find max value */
	for (i = 0; i < 4; i++) {
		if (scores[i] > max) {
			max = scores[i];
		}
	}

	/* find winners */
	int winners[4] = { -1, -1, -1, -1 };
	int j = 0;
	for (i = 0; i < 4; i++) {
		if (scores[i] == max) {
			winners[j++] = i;
		}
	}
	
	if (winners[1] == -1) {
		/* there is only one winner */
		sprintf(msg, "WINNER: %c w/ %d", get_player_name(winners[0]), max);
	} else {
		/* there are more winners */
		sprintf(msg, "WINNERS: ");
		for (i = 0; winners[i] != -1; i++) {
			sprintf(aux, "%c ", get_player_name(winners[i]));
			strcat(msg, aux);
		}
	}

	LCD_print2(game_modes[BLUE_CENTER_SHOT], msg);
	_delay_ms(5000);
}
