/*
 * Music_Screen.h
 *
 *  Created on: Jul 21, 2025
 *      Author: steve
 */

#ifndef INC_SOUND_SCREEN_H_
#define INC_SOUND_SCREEN_H_

#include "stm32f4xx_hal.h"
#include "main.h"
#include "ili9341.h"
#include "fonts.h"
#include <string.h>
#include <stdio.h>



void sound_screen(void);
void sound_border(int);
void sounds(void);
void sound_select(void);
void sound_buttons(void);
void playSound(void);
void sound1(void);
void sound2(void);
void sound3(void);

#endif /* INC_SOUND_SCREEN_H_ */
