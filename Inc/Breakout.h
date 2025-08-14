/*
 * Breakout.h
 *
 *  Created on: Jul 17, 2025
 *      Author: steve
 */

#ifndef INC_BREAKOUT_H_
#define INC_BREAKOUT_H_

#include "stm32f4xx_hal.h"
#include "main.h"
#include "ili9341.h"
#include "fonts.h"
#include <string.h>
#include <stdio.h>

//initialize screen
void initBreakout(void);
void initPaddle();
void initBall(int,int, uint16_t);
void initBricks();
void initScoreboard();

//movement update
void updatePaddle();
void updateBall();
void updateScoreboard();
void detectCollision();
void game1_buttons();
void GameOver();
void pauseGame();


#endif /* INC_BREAKOUT_H_ */
