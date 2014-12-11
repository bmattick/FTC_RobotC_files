#ifndef _CREATEOPTSCREEN_
#define _CREATEOPTSCREEN_

#include "WaitForButtonPress.h"

typedef enum CMD {
	DIR_UP,
	DIR_DOWN,
	DIR_NONE,
} CMD;

typedef enum NXT_BTN {
	RIGHT_BTN = 1,
	LEFT_BTN = 2,
	CENTER_BTN = 3,
	DOWN_BTN = 4
} NXT_BTN;

typedef struct {
	string screenTitle;
	string optName1;
	string optName2;
	string optName3;
	string optName4;
	string optName5;
	string optName6;
} SCREENDATA;

const int NEXT = 100; const int BACK = -100;
const string sNEXT = "->NEXT"; const string sBACK = "<-BACK";
string sDisplayOptionSel = "";

void DrawSel (CMD dir, int crntSel) {
	fillEllipse(4, crntSel, 9, crntSel - 5);
	if (dir == DIR_DOWN) {
		eraseEllipse(4, crntSel + 8, 9, crntSel + 3);
	}
	if (dir == DIR_UP) {
		eraseEllipse(4, crntSel - 13, 9, crntSel - 8);
	}
}

void DisplaySelectedOption (int optionValue, SCREENDATA screenData) {

	switch (optionValue) {
	case 1:
		sDisplayOptionSel = screenData.optName1; break;
	case 2:
		sDisplayOptionSel = screenData.optName2;	break;
	case 3:
		sDisplayOptionSel = screenData.optName3;	break;
	case 4:
		sDisplayOptionSel = screenData.optName4;	break;
	case 5:
		sDisplayOptionSel = screenData.optName5;	break;
	case 6:
		sDisplayOptionSel = screenData.optName6;	break;
	default:
		break;
	}
}

int CountOptions (SCREENDATA screenData) {

	int i = 0;

	if (screenData.optName1 != "") {i++;}
	if (screenData.optName2 != "") {i++;}
	if (screenData.optName3 != "") {i++;}
	if (screenData.optName4 != "") {i++;}
	if (screenData.optName5 != "") {i++;}
	if (screenData.optName6 != "") {i++;}

	return i;
}

int CreateScreen (SCREENDATA screenData, int pgNum) {

	int selOption_TopPixel = 46;
	int selOptionNum = 0;
	int numOptions = CountOptions(screenData);

	eraseDisplay();

	displayCenteredTextLine(1, "%s", screenData.screenTitle);
	displayTextLine(2, "  %s", screenData.optName1);
	displayTextLine(3, "  %s", screenData.optName2);
	displayTextLine(4, "  %s", screenData.optName3);
	displayTextLine(5, "  %s", screenData.optName4);
	displayTextLine(6, "  %s", screenData.optName5);
	displayTextLine(7, "  %s", screenData.optName6);

	fillEllipse(4, selOption_TopPixel, 9, selOption_TopPixel - 5);

	CMD direction = DIR_NONE;

	while (true) {

		wait1Msec(250);

		if (nNxtButtonPressed == RIGHT_BTN && selOption_TopPixel > (54 - (8 * numOptions))) {
			direction = DIR_DOWN;
			selOption_TopPixel = selOption_TopPixel - 8;
			DrawSel (direction, selOption_TopPixel);
		}
		if (nNxtButtonPressed == LEFT_BTN && selOption_TopPixel < 46) {
			direction = DIR_UP;
			selOption_TopPixel = selOption_TopPixel + 8;
			DrawSel (direction, selOption_TopPixel);
		}
		if (nNxtButtonPressed == CENTER_BTN) {
			eraseDisplay();
			selOptionNum = (54 - selOption_TopPixel) / 8;

			DisplaySelectedOption(selOptionNum, screenData);

			if (sDisplayOptionSel == "->NEXT") {
				return NEXT;
			}

			if (sDisplayOptionSel == "<-BACK") {
				return BACK;
			}

			selOptionNum = selOptionNum + (4 * (pgNum - 1));

			displayCenteredTextLine(1, "%s", screenData.screenTitle);
			displayCenteredTextLine(3, "Opt %d selected", selOptionNum);
			displayCenteredTextLine(4, "%s", sDisplayOptionSel);

			WaitForButtonPress(waitScreen);

			return selOptionNum;
		}
	}
}

#endif
