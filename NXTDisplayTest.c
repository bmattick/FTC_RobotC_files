#include "CreateOptionScreen.h"
#include "WaitForButtonPress.h"

/*
the CreateScreen function creates a screen with 6 selections and returns the selected value (1 - 6)
To make a new screen:
1.  initiate a new variable, type SCREENDATA (the structure is defined in the CreateOptionScreen.h file)
2.  define a title line (*.screenTitle)
3.  define up to 6 options (*.optName#) (#: 1 to 6)
4.  pass the screenData variable and the page number (1, if the options do not span multiple pages)
** if you have less then 6 options, give the unused options a blank string
** don't put any blank strings between defined options

Use the grey left and right buttons on the NXT to select an option.  The function returns the integer value
of the selected option (in the order that the option appear on the list)

The selection screen can span over multiple screens (if more than 6 options are needed), using the following steps:
FIRST SCREEN:
1.  Options 1 - 5 CANNOT be blank
2.  Use the constant string sNEXT as screenData.optName6
3.  Pass a page number of 1 to CreateScreen()
SECOND SCREEN +:
1.  Use the constant string sBACK as screenData.optName1
2.  Options 2 - 5 CANNOT be blank
3.  Use the constant string sNEXT as screenData.optName6
3.  Pass the page number to CreateScreen() (2, 3, etc)
LAST SCREEEN:
1.  USe the constant string sBACK as screenData.optName1
3.  Pass the page number to CreateScreen() (2, 3, etc)

A SpanScreen function includes references to all of the screens that are to be spanned.  If the constant NEXT or BACK
are returned from the CreateScreen() function, the page number is increased or decreased and the loop is started over,
using IF statements to reference the next or previous page number.  If a selection other than NEXT or BACK is selected,
it is returned.

*/

int GetOptVal_StartPosition() {
	SCREENDATA screenData;
	screenData.screenTitle = "Start Position";
	screenData.optName1 = "Ramp";
	screenData.optName2 = "Red Zn Face L";
	screenData.optName3 = "Red Zn Face R";
	screenData.optName4 = "Red Zn Face Fr";
	screenData.optName5 = "";
	screenData.optName6 = "";
	return (CreateScreen (screenData, 1));
}

int GetOptVal_PowerSettings_pg1() {
	SCREENDATA screenData;
	screenData.screenTitle = "Power Lvl - p1";
	screenData.optName1 = "0%";
	screenData.optName2 = "15%";
	screenData.optName3 = "20%";
	screenData.optName4 = "35%";
	screenData.optName5 = "50%";
	screenData.optName6 = sNEXT;
	return (CreateScreen (screenData, 1));
}

int GetOptVal_PowerSettings_pg2() {
	SCREENDATA screenData;
	screenData.screenTitle = "Power Lvl - p2";
	screenData.optName1 = sBACK;
	screenData.optName2 = "65%";
	screenData.optName3 = "75%";
	screenData.optName4 = "100%";
	screenData.optName5 = "110%";
	screenData.optName6 = sNEXT;
	return (CreateScreen (screenData, 2));
}

int GetOptVal_PowerSettings_pg3() {
	SCREENDATA screenData;
	screenData.screenTitle = "Power Lvl - p3";
	screenData.optName1 = sBACK;
	screenData.optName2 = "125%";
	screenData.optName3 = "150%";
	screenData.optName4 = "200%";
	screenData.optName5 = "";
	screenData.optName6 = "";
	return (CreateScreen (screenData, 3));
}

int GetOptVal_PowerSettings_SpanScreens() {

	int optSel = 0; int pageNum = 1;

	while (true) {

		if (pageNum == 1) {
			optSel = GetOptVal_PowerSettings_pg1();
			if (optSel == NEXT) {pageNum ++; continue;} else if (optSel == BACK) {pageNum --; continue;} else {return optSel;}
		}
		if (pageNum == 2) {
			optSel = GetOptVal_PowerSettings_pg2();
			if (optSel == NEXT) {pageNum ++; continue;} else if (optSel == BACK) {pageNum --; continue;} else {return optSel;}
		}
		if (pageNum == 3) {
			optSel = GetOptVal_PowerSettings_pg3();
			if (optSel == NEXT) {pageNum ++; continue;} else if (optSel == BACK) {pageNum --; continue;} else {return optSel;}
		}
	}
}

int GetOptVal_IR_Approach() {
	SCREENDATA screenData;
	screenData.screenTitle = "IR Approach";
	screenData.optName1 = "Front";
	screenData.optName2 = "Front Side";
	screenData.optName3 = "Rear";
	screenData.optName4 = "";
	screenData.optName5 = "";
	screenData.optName6 = "";
	return (CreateScreen (screenData, 1));
}

task main()
{
	int optSel1 = GetOptVal_StartPosition();
	int optSel2 = GetOptVal_PowerSettings_SpanScreens();
	int optSel3 = GetOptVal_IR_Approach();

	eraseDisplay();
	displayCenteredTextLine(1, "Option 1: %2d", optSel1);
	displayCenteredTextLine(2, "Option 2: %2d", optSel2);
	displayCenteredTextLine(3, "Option 3: %2d", optSel3);

	WAIT_SCREEN ws;
	ws.line6 = "Last Screen";
	ws.line7 = "...";
	WaitForButtonPress(ws);
}
