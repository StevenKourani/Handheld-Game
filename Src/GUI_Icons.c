
#include "Sound_Screen.h"
#include "GUI_Icons.h"
#include "Game_Screen.h"
#include "game_icon.h"

#define NUM_ICONS   3
#define ICON_X      30
#define ICON_Y      70
#define ICON_RADIUS 12
#define ICON_W 		70
#define ICON_H 		70
#define ICON_SPACE  20

#define ICON_BORDER_THICKNESS 3

extern uint16_t xValue;
extern uint16_t yValue;
extern uint32_t readValue[2];

int selectedIcon = 0;
int previousIcon = 0;
uint32_t IconlastMoveTime = 0;

extern int buttonState;
extern int lastButtonState;

const uint16_t music_icon_24x24[];
const uint16_t gear_icon_24x24[];


const char* iconLabels[NUM_ICONS] = {
	  "Games",
	  "Music",
	  "Settings"
	};

const uint16_t* iconBitmaps[NUM_ICONS] = {
    game_icon,
	music_icon_24x24,
	gear_icon_24x24
};

uint16_t iconColors[NUM_ICONS] = {
    0x081F, // Teal
    0xFD20, // Orange
    0x7BEF  // Light Gray
};

void screen() {

	ILI9341_FillScreen(ILI9341_BLACK);



    ILI9341_FillRoundedRect(10, 210, 300, 30, 12, 0x3186);

    ILI9341_WriteString(171, 231, "(A) Select", Font_7x10, ILI9341_BLACK, 0x3186);
    ILI9341_WriteString(170, 230, "(A) Select", Font_7x10, ILI9341_WHITE, 0x3186);
    ILI9341_WriteString(251, 231, "(B) Back", Font_7x10, ILI9341_BLACK, 0x3186);
    ILI9341_WriteString(250, 230, "(B) Back", Font_7x10, ILI9341_WHITE, 0x3186);
}

//	void screen(){
//		ILI9341_FillScreen(ILI9341_BLACK);
//
//		for(int x = 0; x < ILI9341_WIDTH; x++) {
//			ILI9341_DrawPixel(x, 0, ILI9341_RED);
//			ILI9341_DrawPixel(x, ILI9341_HEIGHT-21, ILI9341_RED);
//		}
//
//		for(int y = 0; y < ILI9341_HEIGHT-20; y++) {
//			ILI9341_DrawPixel(0, y, ILI9341_RED);
//			ILI9341_DrawPixel(ILI9341_WIDTH-1, y, ILI9341_RED);
//		}
//
//
//		ILI9341_FillRectangle(0, 220, 319, 20, ILI9341_WHITE);
//		ILI9341_WriteString(170, 230, "(A) Select", Font_7x10, ILI9341_BLACK, ILI9341_WHITE);
//		ILI9341_WriteString(250, 230, "(B) Back", Font_7x10, ILI9341_BLACK, ILI9341_WHITE);
//
//	}





	void icon_border(int iconIdx) {
	    int x = ICON_X + iconIdx * (ICON_W + ICON_SPACE) - 4;
	    int y = ICON_Y - 4;
	    int w = ICON_W + 8; // icon + border left & right
	    int h = ICON_H + 8;
	    uint8_t radius = 14; // Must be less than (w/2) and (h/2)

	    ILI9341_DrawRoundedRectOutline(x, y, w, h, radius, ILI9341_WHITE);
	}

	void clear_border(int iconIdx) {
	    int x = ICON_X + iconIdx * (ICON_W + ICON_SPACE) - 4;
	    int y = ICON_Y - 4;
	    int w = ICON_W + 8;
	    int h = ICON_H + 8;
	    uint8_t radius = 14;

	    ILI9341_DrawRoundedRectOutline(x, y, w, h, radius, ILI9341_BLACK);
	}

	void icons(void) {
	    clear_border(previousIcon);
	    for (int i = 0; i < NUM_ICONS; i++) {
	        int x = ICON_X + i * (ICON_W + ICON_SPACE);
	        int y = ICON_Y;
	        // Draw rounded rectangle with theme color
	        ILI9341_FillRoundedRect(x, y, ICON_W, ICON_H, ICON_RADIUS, iconColors[i]);

	        // Draw small image/icon in center
	        ILI9341_DrawImage(x + (ICON_W-40)/2, y + 10, 40, 40, iconBitmaps[i]);

	        // Draw label below
	        int textX = x + (ICON_W - strlen(iconLabels[i]) * Font_7x10.width) / 2;
	        int textY = y + ICON_H - 18;
	        ILI9341_WriteString(textX, textY, iconLabels[i], Font_7x10, ILI9341_WHITE, iconColors[i]);
	    }
	    icon_border(selectedIcon);
	}


	void setting_screen(){
				ILI9341_WriteString(100, 100, "Setting", Font_7x10, ILI9341_WHITE, ILI9341_BLACK);
			}

	void icon_select() {
	    uint16_t joyX = readValue[0];

	    int deadzone = 300;
	    int center = 2048;

	    if (HAL_GetTick() - IconlastMoveTime > 50) {
	        if (joyX > center + deadzone && selectedIcon < NUM_ICONS - 1) {
	            previousIcon = selectedIcon;
	        	selectedIcon++;
	            IconlastMoveTime = HAL_GetTick();
	            icons();
	        } else if (joyX < center - deadzone && selectedIcon > 0) {
	            previousIcon = selectedIcon;
	        	selectedIcon--;
	            IconlastMoveTime = HAL_GetTick();
	            icons();
	        }
	    }

	    icon_buttons();

	}

	void icon_buttons(){

		if (btnA.state == HIGH && btnA.lastState == LOW) {
			        switch (selectedIcon) {
			            case 0:
			                appState = STATE_GAME_SELECT;
			                screen();
			                game_screen();
			                break;
			            case 1:
			                appState = STATE_SOUND;
			                screen();
			                sound_screen();
			                break;
			            case 2:
			                appState = STATE_SETTINGS;
			                screen();
			                setting_screen();
			                break;
			        }
		}


		if (btnB.state == HIGH && btnB.lastState == LOW) {
			if (appState == STATE_SOUND || appState == STATE_SETTINGS) {
				appState = STATE_MENU;
				screen();
				icons();
			}
		}
	}

