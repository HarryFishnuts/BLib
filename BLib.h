#ifndef __BLIB_INCLUDE__
#define __BLIB_INCLUDE__


/*************************************************************
* FILE: BLib.h
* DATE: 2021 - 08 - 29
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	BLib master file
* CONTENTS:
*	- Includes
*
*************************************************************/

#include "GCore.h"   // Basic graphics
#include "GTexLib.h" // Texture editing
#include "GFont.h"   // Basic fonts
#include "ICore.h"   // Basic user interface

#include "WCore.h"   // Basic window handling

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
BLWindowHandle BLibInit(BLUInt width, BLUInt height);

#endif 
