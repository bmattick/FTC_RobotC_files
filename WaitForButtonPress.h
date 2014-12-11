#ifndef _WAITFORBTNPRESS_
#define _WAITFORBTNPRESS_

typedef struct {
	string line6;
	string line7;
} WAIT_SCREEN;

WAIT_SCREEN waitScreen;

void WaitForButtonPress (WAIT_SCREEN ws) {

	if (ws.line6 == "") {
		ws.line6 = "Press Orange Btn";
		ws.line7 = "to continue";
	}

	displayCenteredTextLine(6, "%s", ws.line6);
	displayCenteredTextLine(7, "%s", ws.line7);
	while (true) {
		wait1Msec(250);
		if (nNxtButtonPressed == 3) {
			break;
		}
	}
}

#endif
