/*
 * Game_Screen.h
 *
 *  Created on: Jul 17, 2025
 *      Author: steve
 */

#ifndef INC_GAME_SCREEN_H_
#define INC_GAME_SCREEN_H_

#include "stm32f4xx_hal.h"
#include "main.h"
#include "ili9341.h"
#include "fonts.h"
#include <string.h>
#include <stdio.h>



void game_screen(void);
void game_border(int);
void games(void);
void game_select(void);
void game_buttons(void);
void game1(void);
void game2(void);


#endif /* INC_GAME_SCREEN_H_ */
