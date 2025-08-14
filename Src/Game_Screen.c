/*
 * Game_Screen.c
 *
 *  Created on: Jul 17, 2025
 *      Author: steve
 */

#include "Game_screen.h"
#include "GUI_Icons.h"
#include "Breakout.h"

#define NUM_GAMES   2
#define GAME_X      20
#define GAME_Y      50
#define GAME_W      280
#define GAME_H      30
#define GAME_SPACE  10

extern uint16_t xValue;
extern uint16_t yValue;
extern uint32_t readValue[2];

int selectedGame = 0;
int previousGame = 0;
uint32_t GamelastMoveTime = 0;

extern int buttonState;
extern int lastButtonState;

const char* game_label[NUM_GAMES] = {
	  "Game 1: Breakout",
	  "Game 2: Test",
	};

	void game_screen(){
		ILI9341_WriteString(10, 10 , "Please Select A Game:", Font_11x18, ILI9341_BLACK, ILI9341_WHITE);

		games();
	}


	void game_border(int gameIdy) {
	    int x = GAME_X;
	    int y = GAME_Y + gameIdy * (GAME_H + GAME_SPACE);

	    for (int i = x - 5; i < x + GAME_W + 5; i++) {
	        ILI9341_DrawPixel(i, y - 5, ILI9341_WHITE);
	        ILI9341_DrawPixel(i, y + GAME_H + 5, ILI9341_WHITE);
	    }
	    for (int j = y - 5; j < y + GAME_H + 5; j++) {
	        ILI9341_DrawPixel(x - 5, j, ILI9341_WHITE);
	        ILI9341_DrawPixel(x + GAME_W + 5, j, ILI9341_WHITE);
	    }
	}

	void clear_game_border(int gameIdy) {
	    int x = GAME_X;
	    int y = GAME_Y + gameIdy * (GAME_H + GAME_SPACE);

	    for (int i = x - 5; i < x + GAME_W + 5; i++) {
	        ILI9341_DrawPixel(i, y - 5, ILI9341_BLACK);
	        ILI9341_DrawPixel(i, y + GAME_H + 5, ILI9341_BLACK);
	    }
	    for (int j = y - 5; j < y + GAME_H + 5; j++) {
	        ILI9341_DrawPixel(x - 5, j, ILI9341_BLACK);
	        ILI9341_DrawPixel(x + GAME_W + 5, j, ILI9341_BLACK);
	    }
	}

	void games(void) {
		clear_game_border(previousGame);
		for (int i = 0; i < NUM_GAMES; i++) {
		    int x = GAME_X;
		    int y = GAME_Y + i * (GAME_H + GAME_SPACE);
	        ILI9341_FillRectangle(x, y, GAME_W, GAME_H, ILI9341_GREEN);

	        int textY = y + (GAME_H - Font_7x10.height) / 2;
	        ILI9341_WriteString(x, textY,
	                            game_label[i],
	                            Font_7x10,
	                            ILI9341_WHITE,
								ILI9341_GREEN);
	    }
	    game_border(selectedGame);
	}

	void game_select() {
	    uint16_t joyY = readValue[1];

	    int deadzone = 300;
	    int center = 2048;

	    if (HAL_GetTick() - GamelastMoveTime > 200) {
	        if (joyY > center + deadzone && selectedGame < NUM_GAMES - 1) {
	        	previousGame = selectedGame;
	            selectedGame++;
	            GamelastMoveTime = HAL_GetTick();
	            games();
	        } else if (joyY < center - deadzone && selectedGame > 0) {
	        	previousGame = selectedGame;
	            selectedGame--;
	            GamelastMoveTime = HAL_GetTick();
	            games();
	        }
	    }
	    game_buttons();
	}


	void game2(){
		ILI9341_WriteString(10, 10 , "Game 2", Font_11x18, ILI9341_BLACK, ILI9341_WHITE);

	}

	void game_buttons(){
			if (btnA.state == HIGH && btnA.lastState == LOW) {
					switch (selectedGame) {
						case 0:
							gameState = STATE_GAME_1;
							ILI9341_FillScreen(ILI9341_BLACK);
							HAL_Delay(1000);
							initBreakout();
							break;
						case 1:
							gameState = STATE_GAME_2;
							ILI9341_FillScreen(ILI9341_BLACK);
							game2();
							break;
					}
			}


			if (btnB.state == HIGH && btnB.lastState == LOW) {
			    if (appState == STATE_GAME_SELECT && gameState == GAME_MENU) {
			        appState = STATE_MENU;
			        screen();
			        icons();
			    }
			}
		}



