/*
 * rgb_led_matrix.h
 *
 * Created: 22/05/2018 15:02:05
 *  Author: Tudor
 */ 

#ifndef RGB_LED_MATRIX_H_
#define RGB_LED_MATRIX_H_

#include <avr/io.h>

/*****************************************************************************\
 * Parameters of the 3x3 matrix                                              *
\*****************************************************************************/

/* Height and width of the matrix */
#define LED_MATRIX_HEIGHT 3
#define LED_MATRIX_WIDTH 3

/* DDR registers for each color and each matrix row */
#define MATRIX_R_ROW1_DDR DDRB
#define MATRIX_R_ROW2_DDR DDRB
#define MATRIX_R_ROW3_DDR DDRB
#define MATRIX_G_ROW1_DDR DDRB
#define MATRIX_G_ROW2_DDR DDRB
#define MATRIX_G_ROW3_DDR DDRB
#define MATRIX_B_ROW1_DDR DDRA
#define MATRIX_B_ROW2_DDR DDRB
#define MATRIX_B_ROW3_DDR DDRB

/* PORT registers for each color and each matrix row */	
#define MATRIX_R_ROW1_PORT PORTB
#define MATRIX_R_ROW2_PORT PORTB
#define MATRIX_R_ROW3_PORT PORTB
#define MATRIX_G_ROW1_PORT PORTB
#define MATRIX_G_ROW2_PORT PORTB
#define MATRIX_G_ROW3_PORT PORTB
#define MATRIX_B_ROW1_PORT PORTA
#define MATRIX_B_ROW2_PORT PORTB
#define MATRIX_B_ROW3_PORT PORTB

/* Pins of each color row of the matrix */
#define MATRIX_R_ROW1 PB1
#define MATRIX_G_ROW1 PB0
#define MATRIX_B_ROW1 PA0 
#define MATRIX_R_ROW2 PB4
#define MATRIX_G_ROW2 PB3
#define MATRIX_B_ROW2 PB2
#define MATRIX_R_ROW3 PB7
#define MATRIX_G_ROW3 PB6
#define MATRIX_B_ROW3 PB5

/* Registers for the column cathodes */
#define MATRIX_C_DDR             DDRA
#define MATRIX_C_PORT            PORTA

/* Pins of each cathode column of the matrix */
#define MATRIX_C_COL1 PA1
#define MATRIX_C_COL2 PA2
#define MATRIX_C_COL3 PA3

/*****************************************************************************\
 * API RGB Matrix                                                            *
\*****************************************************************************/

/* Initialize the RGB matrix.
 * Must be called only once at the beginning,
 * before playing with other matrix functions.
 */
void RGB_matrix_init(void);

/* Turn on in red the LED at a certain row and column.
 * NOTE: Row/Column indexing starts at 1. */
void RGB_matrix_turn_on_red(int row, int col);

/* Turn on in green the LED at a certain row and column.
 * NOTE: Row/Column indexing starts at 1. */
void RGB_matrix_turn_on_green(int row, int col);

/* Turn on in blue the LED at a certain row and column.
 * NOTE: Row/Column indexing starts at 1. */
void RGB_matrix_turn_on_blue(int row, int col);

/* Turn off the a certain LED.
 * NOTE: Column indexing starts at 1. */
void RGB_matrix_turn_off(int row, int col);

#endif /* RGB_LED_MATRIX_H_ */