/*
 * game.h
 *
 * Created: 22/05/2018 21:21:45
 *  Author: Tudor
 */ 


#ifndef GAME_H_
#define GAME_H_

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "gamepad.h"
#include "lcd.h"
#include "rgb_led_matrix.h"

/*****************************************************************************\
 * API Game                                                                  *
\*****************************************************************************/

/* Number of game modes */
#define GAME_MODES 4

/* Game modes */
#define MATCH_ME 0
#define HAMMERING_HANDS 1
#define GREEN_HAMMERING_HANDS 2
#define BLUE_CENTER_SHOT 3

/* Number of rounds */
#define MATCH_ME_ROUNDS 10
#define HAMMERING_HANDS_ROUNDS 10
#define GREEN_HAMMERING_HANDS_ROUNDS 10
#define BLUE_CENTER_SHOT_ROUNDS 20

/* Reaction time for Hammering Hands game modes (measured in ms) */
#define HAMMERING_HANDS_REACTION_TIME 300
#define GREEN_HAMMERING_HANDS_REACTION_TIME 500
#define BLUE_CENTER_SHOT_REACTION_TIME 1000

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