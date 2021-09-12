

/*************************************************************
* FILE: ICoreSource.c
* DATE: 2021 - 09 - 12
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	BLib header source file
* CONTENTS:
*	- Includes
*	- Functions
*
*************************************************************/

#include "BLib.h"  // Header

#include "glfw3.h" // Screen related functions

/*************************************************************
* NAME: BLibInit
* DATE: 2021 - 09 - 12
* PARAMS:
*	BLUInt width  -> width of main window
*	BLUInt height -> height of main window
*
* RETURNS:
*	WindowHandle of main window
* NOTE:
*	Inits all BLib modules and creates a main window context
	for all font and rendering.
*************************************************************/
BLWindowHandle BLibInit(BLUInt width, BLUInt height)
{
	//init window library
	BLInitWCore( );

	//get monitor dimensions to center window
	const GLFWvidmode* mVidMode;
	mVidMode = glfwGetVideoMode(glfwGetPrimaryMonitor( ));

	//calculate positions
	int wPosX = (mVidMode->width  / 2) + width  / 2;
	int wPosY = (mVidMode->height / 2) + height / 2;

	//create window
	BLWindowHandle mainWin = BLCreateWindow(BL_WINDOW_TYPE_FIXED, "BL Main Window", wPosX, wPosY, width, height);

	//init fonts
	BLInitGFont( );
	BLInitICore( );

	//return window
	return mainWin;
}