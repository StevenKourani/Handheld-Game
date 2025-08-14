/*
 * Breakout.c
 *
 *  Created on: Jul 17, 2025
 *      Author: steve
 */

#include "Breakout.h"
#include "Game_screen.h"
#include "Sound_Screen.h"
#include "GUI_Icons.h"

//Basic setup
#define HEIGHT 240
#define WIDTH 320
#define ROWS 5
#define COLS 11
#define RADIUS 5
#define LIVES 3

//Paddle
#define paddleHeight 10
#define paddleWidth 40


//Bricks
#define BRICK_W 25
#define BRICK_H 12
#define COL_GAP 3
#define ROW_GAP 4

//Ball
#define RADIUS 5

int lives = LIVES;
int score = 0;

int ballx = 160;
int bally = 218;
int prevballx = 160;
int prevbally = 218;
int ballVx = 5;
int ballVy = 5;

int paddleX = (WIDTH - paddleWidth)/2 ;
int prevpaddleX = (WIDTH - paddleWidth)/2;

int bricks[ROWS][COLS];

extern uint16_t xValue;
extern uint16_t yValue;
extern uint32_t readValue[2];

uint32_t lastPaddleTime = 0;
uint32_t lastBallTime = 0;


extern int buttonState;
extern int lastButtonState;

	void initBreakout(){
		initPaddle();
		initBall(ballx,bally, ILI9341_WHITE);
		initScoreboard();
		initBricks();
		lives = LIVES;
		score = 0;
	}


	void initPaddle(){
		paddleX = (WIDTH - paddleWidth)/2;
		prevpaddleX = paddleX;
		ILI9341_FillRectangle(paddleX , HEIGHT - paddleHeight - 5, paddleWidth, paddleHeight, ILI9341_WHITE);
	 }

	void initBall(int ballx, int bally, uint16_t color){
		for (int dy = -RADIUS; dy <= RADIUS; dy++) {
		        for (int dx = -RADIUS; dx <= RADIUS; dx++) {
		            if ((dx*dx + dy*dy) <= (RADIUS*RADIUS)) {
		                ILI9341_DrawPixel(ballx + dx, bally + dy, color);
		            }
		        }
		    }
		}

	void initScoreboard(){
		ILI9341_FillRectangle(0, 0, 320, 30, ILI9341_WHITE);
		ILI9341_WriteString(20, 10, "Score: ", Font_7x10, ILI9341_BLACK, ILI9341_WHITE);
		ILI9341_WriteString(170, 10, "Lives: ", Font_7x10, ILI9341_BLACK, ILI9341_WHITE);
	}


	void initBricks(){
		int totalWidth = (COLS * BRICK_W) + ((COLS - 1) * COL_GAP);
		int xStart = (WIDTH - totalWidth) / 2;
		int ybrick = 50;

		for (int i = 0; i < ROWS; i++) {
		    int xbrick = xStart;
		    for (int j = 0; j < COLS; j++) {
		    	bricks[i][j] = 1;
		        uint16_t color;
		        if (i == 0) color = ILI9341_GREEN;
		        else if (i == 1) color = ILI9341_BLUE;
		        else if (i == 2) color = ILI9341_YELLOW;
		        else if (i == 3) color = ILI9341_RED;
		        else if (i == 4) color = ILI9341_CYAN;

		        ILI9341_FillRectangle(xbrick, ybrick, BRICK_W, BRICK_H, color);

		        xbrick += BRICK_W + COL_GAP;
		    }
		    ybrick += BRICK_H + ROW_GAP;
		}

	}


	void updatePaddle(){
		uint16_t joyX = readValue[0];

		int deadzone = 300;
		int center = 2048;

		if (HAL_GetTick() - lastPaddleTime > 50) {
			if (joyX > center + deadzone ) {
				paddleX += 10;
				if (paddleX > WIDTH - paddleWidth) paddleX = WIDTH - paddleWidth;
				lastPaddleTime = HAL_GetTick();
				ILI9341_FillRectangle(prevpaddleX , HEIGHT - paddleHeight - 5, paddleWidth, paddleHeight, ILI9341_BLACK);
				prevpaddleX = paddleX;
				ILI9341_FillRectangle(paddleX , HEIGHT - paddleHeight - 5, paddleWidth, paddleHeight, ILI9341_WHITE);

			} else if (joyX < center - deadzone) {
				paddleX -= 10;
				if (paddleX < 0) paddleX = 0;
				lastPaddleTime = HAL_GetTick();
				ILI9341_FillRectangle(prevpaddleX , HEIGHT - paddleHeight - 5, paddleWidth, paddleHeight, ILI9341_BLACK);
				prevpaddleX = paddleX;
				ILI9341_FillRectangle(paddleX , HEIGHT - paddleHeight - 5, paddleWidth, paddleHeight, ILI9341_WHITE);

			}

		}
	}

	void updateBall(){
	    if (HAL_GetTick() - lastBallTime > 50) {
	        initBall(prevballx, prevbally, ILI9341_BLACK);

	        ballx += ballVx;
	        bally += ballVy;

	        if (ballx - RADIUS <= 0 || ballx + RADIUS >= WIDTH) {
	            ballVx = -ballVx;
	        }
	        if (bally - RADIUS <= 30) {
	            ballVy = -ballVy;
	        }
	        else if (bally + RADIUS >= HEIGHT) {
	        	if(lives > 0){
	        		lives -= 1;
					GameOver();
					ILI9341_FillRectangle(paddleX , HEIGHT - paddleHeight - 5, paddleWidth, paddleHeight, ILI9341_BLACK);
					initPaddle();
					initBall(prevballx, prevbally, ILI9341_BLACK);

					ballx = 160;
					bally = 218;
					prevballx = ballx;
					prevbally = bally;
					ballVx = 5;
					ballVy = -5;

					initBall(ballx, bally, ILI9341_WHITE);
					lastBallTime = HAL_GetTick();
					HAL_Delay(500);
					return;
	        	}
	        }

	        initBall(ballx, bally, ILI9341_WHITE);

	        prevballx = ballx;
	        prevbally = bally;

	        lastBallTime = HAL_GetTick();
	    }
	}

	void detectCollision(){
	    int totalWidth = (COLS * BRICK_W) + ((COLS - 1) * COL_GAP);
	    int xStart = (WIDTH - totalWidth) / 2;
		for (int i = 0; i < ROWS; i++) {
			int ybrick = 50 + i * (BRICK_H + ROW_GAP);
			for (int j = 0; j < COLS; j++) {
				int xbrick = xStart + j * (BRICK_W + COL_GAP);
				if (bricks[i][j] == 1) {
					if (ballx + RADIUS > xbrick && ballx - RADIUS < xbrick + BRICK_W &&
						bally + RADIUS > ybrick && bally - RADIUS < ybrick + BRICK_H) {
						bricks[i][j] = 0;
						score += 10;
						ILI9341_FillRectangle(xbrick, ybrick, BRICK_W, BRICK_H, ILI9341_BLACK);

						ballVy = -ballVy;
					}
				}
			}
		}

		if (ballVy > 0 &&
		    ballx + RADIUS >= paddleX &&
		    ballx - RADIUS <= paddleX + paddleWidth &&
		    bally + RADIUS >= HEIGHT - paddleHeight - 5 &&
		    bally + RADIUS <= HEIGHT - 5)
		{
		    ballVy = -ballVy;
		    bally = HEIGHT - paddleHeight - 5 - RADIUS;
		}
	}

	void GameOver(){
		int bricksCleared = 1;
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				if(bricks[i][j] != 0) {
					bricksCleared = 0;
				    break;
				}
			}

			if(!bricksCleared) break;
		}

		if(bricksCleared) {
			ballVx = 0;
			ballVy = 0;
			ILI9341_FillRectangle(50, 50, 80, 80, ILI9341_WHITE);
			ILI9341_WriteString(60, 60, "Congrats", Font_7x10, ILI9341_BLACK, ILI9341_WHITE);
		}

		if(lives == 0){
			ballVx = 0;
			ballVy = 0;
			ILI9341_FillRectangle(50, 50, 80, 80, ILI9341_WHITE);
			ILI9341_WriteString(60, 60, "Game Over", Font_7x10, ILI9341_BLACK, ILI9341_WHITE);

		}
	}



	void updateScoreboard(){
		char str_score[12];
		char str_lives[12];


	    sprintf(str_score, "%d", score);
	    sprintf(str_lives, "%d", lives);

		ILI9341_WriteString(60, 10, str_score, Font_7x10, ILI9341_BLACK, ILI9341_WHITE);
		ILI9341_WriteString(210, 10, str_lives, Font_7x10, ILI9341_BLACK, ILI9341_WHITE);
	}

	void game1_buttons(){

			if (btnA.state == HIGH && btnA.lastState == LOW) {
				  return;
			}


			if (btnB.state == HIGH && btnB.lastState == LOW) {
			    if (appState == STATE_GAME_SELECT && gameState == STATE_GAME_1) {
			    	gameState = GAME_MENU;
			        screen();
			        game_screen();
			    }
			}
		}



