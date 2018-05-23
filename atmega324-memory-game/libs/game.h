/*
 * game.h
 *
 * Created: 22/05/2018 21:21:45
 *  Author: Tudor
 */ 


#ifndef GAME_H_
#define GAME_H_

#include <stdlib.h>

#include "gamepad.h"
#include "lcd.h"
#include "rgb_led_matrix.h"

/*****************************************************************************\
 * API Game                                                                  *
\*****************************************************************************/

/* Number of game modes */
#define GAME_MODES 1

/* Game modes */
#define MATCH_ME 0

/* Number of rounds */
#define MATCH_ME_ROUNDS 10

/* Initialize the game */
void game_init(void);

/* Load a new game */
void game_start(void);

/* Start MATCH ME game mode - single player*/
void game_match_me(void);

/* Start HAMMERING HANDS game mode - single player*/
void game_hammering_hands(void);

/* Start GREEN HAMMERING HANDS game mode - single player*/
void game_green_hammering_hands(void);

/* Start CENTER SHOT game mode - multiplayer*/
void game_center_shot(void);

/* Start BLUE CENTER SHOT game mode - multiplayer*/
void game_blue_center_shot(void);

#endif /* GAME_H_ */