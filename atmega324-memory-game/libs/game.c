/*
 * game.c
 *
 * Created: 22/05/2018 21:21:55
 *  Author: Tudor
 */ 

#include "game.h"

/* the current game mode. At the beginning, no game was selected */
volatile int current_game_mode = -1;

/* Names of the game modes */
const char game_modes[GAME_MODES][16] = { "MATCH ME" };

ISR(PCINT3_vect)
{
	if (gamepad_is_game_pressed()) {
		while (gamepad_is_game_pressed());

		/* go to next game */
		current_game_mode += 1;
		if (current_game_mode >= GAME_MODES) {
			current_game_mode = -1;
		}
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
	PCICR |= (1 << PCIE3);
	PCMSK3 |= (1 << GAMEPAD_PIN_CHANGE_GAME);
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

			switch (current_game_mode) {
				case MATCH_ME:
					game_match_me();
			}

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
	int line, i, j, k, lost;
	int lines[MATCH_ME_ROUNDS];
	char msg[16];

	_delay_ms(2000);

	for (i = 0; i < MATCH_ME_ROUNDS; i++) {
		/* print round */
		sprintf(msg, "ROUND %d", i + 1);
		LCD_print2("MATCH ME", msg);

		/* generate a random number to select the side */
		line = rand() % 4;
		lines[i] = line;

		for (j = 0; j <= i; j++) {
			switch (lines[j]) {
				case 0:
				/* UP side */
				RGB_matrix_turn_on_blue(1, 2);
				_delay_ms(500);
				RGB_matrix_turn_off(1, 2);
				break;
			
				case 1:
				/* DOWN side */
				RGB_matrix_turn_on_blue(3, 2);
				_delay_ms(500);
				RGB_matrix_turn_off(3, 2);
				break;

				case 2:
				/* LEFT side */
				RGB_matrix_turn_on_blue(2, 1);
				_delay_ms(500);
				RGB_matrix_turn_off(2, 1);
				break;

				case 3:
				/* RIGHT side */
				RGB_matrix_turn_on_blue(2, 3);
				_delay_ms(500);
				RGB_matrix_turn_off(2, 3);
				break;
			}

			_delay_ms(500);
		}

		j = 0;
		lost = 0;

		while (1) {
			switch (lines[j]) {
			case 0:
				/* UP side */
				if (gamepad_is_up_pressed()) {
					while (gamepad_is_up_pressed());
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
					while (gamepad_is_down_pressed());
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
					while (gamepad_is_left_pressed());
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
					while (gamepad_is_right_pressed());
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
			LCD_print2("MATCH ME", msg);

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
		LCD_print2("MATCH ME", "VICTORY !!!");
	} else {
		LCD_print2("MATCH ME", "YOU LOST");
	}

	_delay_ms(3000);
}

void game_hammering_hands(void)
{
	//TODO
}

void game_green_hammering_hands(void)
{
	//TODO
}

void game_center_shot(void)
{
	//TODO
}

void game_blue_center_shot(void)
{
	//TODO
}
