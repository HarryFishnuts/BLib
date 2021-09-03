#ifndef __WCORE_INCLUDE__
#define __WCORE_INCLUDE__


/*************************************************************
* FILE: WCore.h
* DATE: 2021 - 08 - 29
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	Basic window management library
* CONTENTS:
*	- Includes
*	- Defs
*	- Typedefs
*	- Enums
*	- Structs
*	- Functions
*
*************************************************************/

#include <stdint.h> // For consistent fixed size types
#include "GCore.h"  // For types and defs

#define BL_WINDOW_COUNT_MAX 16
#define BL_WINDOW_ERRHANDLE -1

typedef int16_t BLWindowHandle;

/*************************************************************
* NAME: BL_WINDOW_TYPE
* DATE: 2021 - 08 - 29
* NOTE: This enum is used for the BLCreateWindow function
*	The borderless and transparent window types are fixed
*	sized
*************************************************************/
enum BL_WINDOW_TYPE
{
	BL_WINDOW_TYPE_FIXED = 0,
	BL_WINDOW_TYPE_RESIZEABLE = 1,
	BL_WINDOW_TYPE_BORDERLESS = 2,
	BL_WINDOW_TYPE_TRANSPARENT = 3,
	BL_WINDOW_TYPE_BORDERLESS_AND_TRANSPARENT = 4
};

/*************************************************************
* NAME: BLInitWCore
* DATE: 2021 - 08 - 29
* PARAMS:
*	none
* RETURNS:
*	void
* NOTE:
*	This function allocates various backend
*	variables for behind-the-scenes management
*	so that the user doesn't have to
*************************************************************/
void BLInitWCore( );

/*************************************************************
* NAME: BLTerminateWCore
* DATE: 2021 - 08 - 29
* PARAMS:
*	none
* RETURNS:
*	void
* NOTE:
*	This function cleans up everything that the BL WCore
*	module had initialized
*************************************************************/
void BLTerminateWCore( );

/*************************************************************
* NAME: BLCreateWindow
* DATE: 2021 - 08 - 29
* PARAMS:
*	enum BL_WINDOW_TYPE winType -> window type
*	const char* title -> title of window
*	BLUInt x -> X position of window on monitor
*	BLUInt y -> Y position of window on monitor
*	BLUInt w -> width of monitor
*	BLUInt h -> height of monitor
* RETURNS:
*	BLWindowHandle to access window object through the
*	BLib library (BL_WINDOW_ERRHANDLE if failed)
* NOTE:
*	GCore will render to LATEST created window after this
*	function call, please call BLRenderSetWindowContext if
*	needed otherwise
*************************************************************/
BLWindowHandle BLCreateWindow(enum BL_WINDOW_TYPE winType, const char* title, BLUInt x, BLUInt y, BLUInt w, BLUInt h);

/*************************************************************
* NAME: BLDestroyWindow
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLWindowHandle winHndl -> window to destroy
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLDestroyWindow(BLWindowHandle winHndl);

/*************************************************************
* NAME: BLGetWindowCount
* DATE: 2021 - 08 - 29
* PARAMS:
*	none
* RETURNS:
*	BLUInt which holds how many windows BL is currently
*	in charge of
* NOTE: N/A
*************************************************************/
BLUInt BLGetWindowCount( );

/*************************************************************
* NAME: BLRenderSetWindowContext
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLWindowHandle winHndl -> window to set
* RETURNS:
*	void
* NOTE:
*	This function sets which window for BL's GCore module
*	to render to
*************************************************************/
void BLRenderSetWindowContext(BLWindowHandle winHndl);

/*************************************************************
* NAME: BLRenderGetWindowContext
* DATE: 2021 - 08 - 29
* PARAMS:
*	void
* RETURNS:
*	BLWindowHandle of which window is currently rendering
*	(BL_WINDOW_ERRHANDLE if could not find window)
* NOTE: N/A
*************************************************************/
BLWindowHandle BLRenderGetWindowContext( );

/*************************************************************
* NAME: BLRenderSetViewPort
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLUInt x -> screenspace X position of viewport
*	BLUInt y -> screenspace Y position of viewport
*	BLUInt w -> width of viewport
*	BLUInt h -> height of viewport
* RETURNS:
*	void
* NOTE: 
*	Sets viewport of currently active window
*************************************************************/
void BLRenderSetViewPort(BLUInt x, BLUInt y, BLUInt w, BLUInt h);

/*************************************************************
* NAME: BLWindowGetDimensions
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLWindowHandle winHndl -> window to get dimensions of
* RETURNS:
*	BLRect with position and size of window
* NOTE: N/A
*************************************************************/
BLRect BLWindowGetDimensions(BLWindowHandle winHndl);

/*************************************************************
* NAME: BLWindowSetDimensions
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLWindowHandle winHndl -> window to set dimensions of
*	BLUInt sizeX -> width of window
*	BLUInt sizeY -> height of window
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLWindowSetDimensions(BLWindowHandle winHndl, BLUInt sizeX, BLUInt sizeY);

/*************************************************************
* NAME: BLWindowSetPosition
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLWindowHandle winHndl -> window to set position of
*	BLUInt sizeX -> X position of window
*	BLUInt sizeY -> Y position of window
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLWindowSetPosition(BLWindowHandle winHndl, BLUInt posX, BLUInt posY);

/*************************************************************
* NAME: BLWindowShouldClose
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLWindowHandle winHndl -> window to check if it should close
* RETURNS:
*	int, 1 for should close, 0 for stay open
* NOTE:
*	if INVALID handle is passed, will return -1
*************************************************************/
int BLWindowShouldClose(BLWindowHandle winHndl);

/*************************************************************
* NAME: BLWindowUpdate
* DATE: 2021 - 08 - 29
* PARAMS:
*	none
* RETURNS:
*	void
* NOTE:
*	To update all window states, it is recommended that this
*	function is called
*************************************************************/
void BLWindowUpdate( );

/*************************************************************
* NAME: BLWindowSwapBuffers
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLWindowHandle winHndl -> window to swap buffers
* RETURNS: void
* NOTE: N/A
*************************************************************/
void BLWindowSwapBuffers(BLWindowHandle winHndl);

/*************************************************************
* NAME: BLWindowGetMousePosition
* DATE: 2021 - 09 - 3
* PARAMS:
*	BLWindowHandle winHndl -> window to get mouse position
* RETURNS: void
* NOTE: N/A
*************************************************************/
BLVert2f BLWindowGetMousePosition(BLWindowHandle winHndl);

#endif