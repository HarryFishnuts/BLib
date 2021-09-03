


/*************************************************************
* FILE: WCoreSource.c
* DATE: 2021 - 08 - 29
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	Source file for basic window handling functions
* CONTENTS:
*	- Includes
*	- Backend struct defs
*	- Backend objects
*	- Functions
*
*************************************************************/

#include "WCore.h"   // Header

#include <stdio.h>   // I/O
#include <stdlib.h>  // For memory management

#include <glfw3.h>   // For window management

#include <Windows.h> // OpenGL dependancy
#include <gl/GL.h>   // Viewport related functions

/*************************************************************
* NAME: BLWindowList
* DATE: 2021 - 08 - 29
* MEMBERS:
*	float X	-> holds X position
*	float Y	-> holds Y position
* NOTE: 
*	There should only be one instance of this struct at ALL times
*************************************************************/
typedef struct BLWindowList
{
	BLUInt         windowCount;
	GLFWwindow*    glWinArr[BL_WINDOW_COUNT_MAX];
}BLWindowList;

/*************************************************************
* NAME: windowList (object)
* DATE: 2021 - 08 - 29
* USE:
*	This is an instance of the BLWindowList struct used for
*	managing all GLFWwindows
* NOTE: N/A
*************************************************************/
static BLWindowList* windowList = NULL;

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
void BLInitWCore( )
{
	//init GLFW
	glfwInit( );

	//check if already init
	if(windowList != NULL)
	{
		fprintf(stderr, "WCore was already init!\n");
	}

	//initialize windowList
	windowList = calloc(1, sizeof(BLWindowList));

	//check if null
	if(windowList == NULL)
	{
		fprintf(stderr, "Windowlist failed to init!\n");
	}

	//end
	return;
}

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
void BLTerminateWCore( )
{
	//terminate GLFW
	glfwTerminate( );

	//free windowList
	free(windowList);

	//end
	return;
}

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
BLWindowHandle BLCreateWindow(enum BL_WINDOW_TYPE winType, const char* title, BLUInt x, BLUInt y, BLUInt w, BLUInt h)
{
	//set window hints
	switch (winType)
	{
	case BL_WINDOW_TYPE_FIXED:

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);               // resize params
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE );               // border params
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE); // transparency params
		break;

	case BL_WINDOW_TYPE_RESIZEABLE:

		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);                // resize params
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);                // border params
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE); // transparency params
		break;

	case BL_WINDOW_TYPE_BORDERLESS:

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);               // resize params
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);               // border params
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE); // transparency params
		break;

	case BL_WINDOW_TYPE_TRANSPARENT:

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);              // resize params
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);               // border params
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // transparency params
		break;

	case BL_WINDOW_TYPE_BORDERLESS_AND_TRANSPARENT:

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);              // resize params
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);              // border params
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // transparency params
		break;

	default:
		break;
	}

	//find empty window spot
	for(int i = 0; i < BL_WINDOW_COUNT_MAX; i++)
	{
		//if found empty window spot
		if(windowList->glWinArr[i] == NULL)
		{
			//get GLFW to create window
			windowList->glWinArr[i] = glfwCreateWindow(w, h, title, NULL, NULL);

			//set rendering context to created window
			glfwMakeContextCurrent(windowList->glWinArr[i]);

			//increment window count
			windowList->windowCount++;

			//return window handle
			return (BLWindowHandle)i;
		}
	}

	//if exited loop, no window created, end
	return (BLWindowHandle)BL_WINDOW_ERRHANDLE;
}

/*************************************************************
* NAME: BLDestroyWindow
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLWindowHandle winHndl -> window to destroy
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLDestroyWindow(BLWindowHandle winHndl)
{
	//get GLFW to destroy window
	glfwDestroyWindow(windowList->glWinArr[(int)winHndl]);

	//set window ptr to NULL
	windowList->glWinArr[(int)winHndl] = NULL;

	//decrement window count
	windowList->windowCount--;

	//end
	return;
}

/*************************************************************
* NAME: BLGetWindowCount
* DATE: 2021 - 08 - 29
* PARAMS:
*	none
* RETURNS:
*	int which holds how many windows BL is currently
*	in charge of
* NOTE: N/A
*************************************************************/
BLUInt BLGetWindowCount()
{
	return windowList->windowCount;
}

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
void BLRenderSetWindowContext(BLWindowHandle winHndl)
{
	//get GLFW to change the rendering context
	glfwMakeContextCurrent(windowList->glWinArr[(int)winHndl]);

	//end
	return;
}

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
BLWindowHandle BLRenderGetWindowContext( )
{
	//get current GLFW window pointer to search for
	GLFWwindow* scanWin = glfwGetCurrentContext( );

	//search
	for(int i = 0; i < BL_WINDOW_COUNT_MAX; i++)
	{
		//found window
		if(windowList->glWinArr[i] == scanWin)
		{
			//return handle
			return (BLWindowHandle)i;
		}
	}

	//if exited for loop, no matching window found
	return BL_WINDOW_ERRHANDLE;
}

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
void BLRenderSetViewPort(BLUInt x, BLUInt y, BLUInt w, BLUInt h)
{
	glViewport(x, y, w, h);
}

/*************************************************************
* NAME: BLWindowGetDimensions
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLWindowHandle winHndl -> window to get dimensions of
* RETURNS:
*	BLRect with position and size of window
* NOTE: N/A
*************************************************************/
BLRect BLWindowGetDimensions(BLWindowHandle winHndl)
{
	//return struct
	BLRect windowDims;

	//vars for GLFW functions
	int winX;
	int winY;
	int winW;
	int winH;

	//get window position and size via GLFW
	glfwGetWindowPos (windowList->glWinArr[(int)winHndl] , &winX , &winY);
	glfwGetWindowSize(windowList->glWinArr[(int)winHndl] , &winW , &winH);

	//pack data into windowDims
	windowDims = BLCreateRect((float)winX, (float)winY, (float)winW, (float)winH);

	//end
	return windowDims;
}

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
void BLWindowSetDimensions(BLWindowHandle winHndl, BLUInt sizeX, BLUInt sizeY)
{
	glfwSetWindowSize(windowList->glWinArr[(int)winHndl], (int)sizeX, (int)sizeY);
	return;
}

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
void BLWindowSetPosition(BLWindowHandle winHndl, BLUInt posX, BLUInt posY)
{
	glfwSetWindowPos(windowList->glWinArr[(int)winHndl], (int)posX, (int)posY);
	return;
}

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
int BLWindowShouldClose(BLWindowHandle winHndl)
{
	//create GLFW window object
	GLFWwindow* glWin;

	//check if Hndl is valid
	if((glWin = windowList->glWinArr[(int)winHndl]) != NULL)
	{
		return glfwWindowShouldClose(glWin);
	}

	//err
	return -1;
}

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
void BLWindowUpdate( )
{
	//get GLFW to poll events
	glfwPollEvents( );

	//end
	return;
}

/*************************************************************
* NAME: BLWindowSwapBuffers
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLWindowHandle winHndl -> window to swap buffers
* RETURNS: void
* NOTE: N/A
*************************************************************/
void BLWindowSwapBuffers(BLWindowHandle winHndl)
{
	//create GLFW window object
	GLFWwindow* glWin;

	//set glWin (make sure valid winHndl)
	if((glWin = windowList->glWinArr[(int)winHndl]) != NULL)
	{
		glfwSwapBuffers(glWin);
	}

	//end
	return;
}