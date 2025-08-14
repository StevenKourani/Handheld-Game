/*
 * Music_Screen.c
 *
 *  Created on: Jul 21, 2025
 *      Author: steve
 */


#include "Sound_screen.h"
#include "GUI_Icons.h"

#define NUM_SOUNDS	 3
#define SOUND_X      20
#define SOUND_Y      50
#define SOUND_W      280
#define SOUND_H      30
#define SOUND_SPACE  10

extern uint16_t xValue;
extern uint16_t yValue;
extern uint32_t readValue[2];

int selectedSound = 0;
int previousSound = 0;
uint32_t SoundlastMoveTime = 0;

extern int buttonState;
extern int lastButtonState;
extern TIM_HandleTypeDef htim2;

const char* sound_label[NUM_SOUNDS] = {
	  "LOW Sound",
	  "Medium Sound",
	  "Loud Sound",
	};

	void sound_screen(){
		ILI9341_WriteString(10, 10 , "Change Sound:", Font_11x18, ILI9341_BLACK, ILI9341_WHITE);

		sounds();
	}

	void sound_border(int soundIdy) {
		    int x = SOUND_X;
		    int y = SOUND_Y + soundIdy * (SOUND_H + SOUND_SPACE);

		    for (int i = x - 5; i < x + SOUND_W + 5; i++) {
		        ILI9341_DrawPixel(i, y - 5, ILI9341_WHITE);
		        ILI9341_DrawPixel(i, y + SOUND_H + 5, ILI9341_WHITE);
		    }
		    for (int j = y - 5; j < y + SOUND_H + 5; j++) {
		        ILI9341_DrawPixel(x - 5, j, ILI9341_WHITE);
		        ILI9341_DrawPixel(x + SOUND_W + 5, j, ILI9341_WHITE);
		    }
		}

		void clear_sound_border(int soundIdy) {
		    int x = SOUND_X;
		    int y = SOUND_Y + soundIdy * (SOUND_H + SOUND_SPACE);

		    for (int i = x - 5; i < x + SOUND_W + 5; i++) {
		        ILI9341_DrawPixel(i, y - 5, ILI9341_BLACK);
		        ILI9341_DrawPixel(i, y + SOUND_H + 5, ILI9341_BLACK);
		    }
		    for (int j = y - 5; j < y + SOUND_H + 5; j++) {
		        ILI9341_DrawPixel(x - 5, j, ILI9341_BLACK);
		        ILI9341_DrawPixel(x + SOUND_W + 5, j, ILI9341_BLACK);
		    }
		}

		void sound1(){
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, htim2.Init.Period/2);
			//HAL_Delay(500);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);
		}

		void sound2(){

		}

		void sound3(){

		}

		void sounds(void) {
			clear_sound_border(previousSound);
			for (int i = 0; i < NUM_SOUNDS; i++) {
			    int x = SOUND_X;
			    int y = SOUND_Y + i * (SOUND_H + SOUND_SPACE);
		        ILI9341_FillRectangle(x, y, SOUND_W, SOUND_H, ILI9341_GREEN);

		        int textY = y + (SOUND_H - Font_7x10.height) / 2;
		        ILI9341_WriteString(x, textY,
		                            sound_label[i],
		                            Font_7x10,
		                            ILI9341_WHITE,
									ILI9341_GREEN);
		    }
		    sound_border(selectedSound);
		}


		void sound_select() {
		    uint16_t joyY = readValue[1];

		    int deadzone = 300;
		    int center = 2048;

		    if (HAL_GetTick() - SoundlastMoveTime > 200) {
		        if (joyY > center + deadzone && selectedSound < NUM_SOUNDS - 1) {
		        	previousSound = selectedSound;
		            selectedSound++;
		            SoundlastMoveTime = HAL_GetTick();
		            sounds();
		        } else if (joyY < center - deadzone && selectedSound > 0) {
		        	previousSound = selectedSound;
		            selectedSound--;
		            SoundlastMoveTime = HAL_GetTick();
		            sounds();
		        }
		    }
		    sound_buttons();
		}



		void sound_buttons(){

				if (btnA.state == HIGH && btnA.lastState == LOW) {
					        switch (selectedSound) {
					            case 0:
					            	soundState = STATE_SOUND_1;
					            	sound1();
					                break;
					            case 1:
					            	gameState = STATE_SOUND_2;
					                break;
					            case 2:
									gameState = STATE_SOUND_3;
									break;
					        }
				}


				if (btnB.state == HIGH && btnB.lastState == LOW) {
				    if (appState == STATE_SOUND && soundState != SOUND_MENU) {
				        soundState = SOUND_MENU;
				        screen();
				        sound_screen();
				    } else if (appState == STATE_SOUND && soundState == SOUND_MENU) {
				        appState = STATE_MENU;
				        screen();
				        icons();
				    }
				}
			}

