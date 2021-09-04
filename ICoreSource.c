

/*************************************************************
* FILE: ICoreSource.c
* DATE: 2021 - 09 - 2
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	Source file for primitive user interface library
* CONTENTS:
*	- Includes
*	- File-Specifc functions
*	- Functions
*
*************************************************************/

#include <stdio.h>   // I/O
#include <Windows.h> // OpenGL dependancy
#include <WinUser.h> // Mouse input
#include <gl/GL.h>   // For rendering
#include <gl/GLU.h>  // For projection related functions

#include "ICore.h"   // Header

/*************************************************************
* NAME: BLHelperSetupProjectionMatrix
* DATE: 2021 - 09 - 2
* PARAMS:
*	none
* RETURNS:
*	void
* NOTE:
*	FILE SPECIFIC FUNCTION
*	This function sets up the projection matrix based on the
*	viewport dimensions
*************************************************************/
static inline void BLHelperSetupProjectionMatrix( )
{
	//var to get viewport dimensions
	//0 -> X, 1 -> Y, 2 -> width, 3 -> height
	int viewPortDimensions[4];
	glGetIntegerv(GL_VIEWPORT, viewPortDimensions);

	//set matrix mode and clear
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity( );

	//set so that modelspace maps to screenspace
	gluOrtho2D(0, viewPortDimensions[2], 0, viewPortDimensions[3]);

	//end
	return;
}

/*************************************************************
* NAME: BLHelperSetupTexEnv
* DATE: 2021 - 09 - 2
* PARAMS:
*	BLTextureHandle texHandle -> texture handle to setup
* RETURNS:
*	void
* NOTE:
*	FILE SPECIFIC FUNCTION
*	Call this function before a render pass to set up the
*	texture environment
*************************************************************/
static inline void BLHelperSetupTexEnv(BLTextureHandle texHandle)
{
	glShadeModel(GL_FLAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, (GLuint)texHandle);
	glEnable(GL_TEXTURE_2D);
	return;
}

/*************************************************************
* NAME: BLCreateRecti
* DATE: 2021 - 09 - 2
* PARAMS:
*	BLInt X -> screenspace X
*	BLInt Y -> screenspace Y
*	BLInt W -> width (pixels)
*	BLInt H -> height (pixels)
* RETURNS:
*	BLRecti created from params
* NOTE: N/A
*************************************************************/
BLRecti BLCreateRecti(BLInt X, BLInt Y, BLInt W, BLInt H)
{
	BLRecti rect = { X, Y, W, H };
	return rect;
}

/*************************************************************
* NAME: BLScaleRecti
* DATE: 2021 - 09 - 2
* PARAMS:
*	BLRecti tRect -> rect to scale
*	float scale -> how much to scale rect
* RETURNS:
*	scaled version of tRect
* NOTE:
*	Returned rectangle is scale from the CENTER
*************************************************************/
BLRecti BLScaleRecti(BLRecti tRect, float scale)
{
	//get scaled W and H
	float scaledW = (float)tRect.W * scale;
	float scaledH = (float)tRect.H * scale;

	//get difference
	float wDiff = scaledW - (float)tRect.W;
	float hDiff = scaledH - (float)tRect.H;

	//move x and y by half of difference
	float newX = (float)tRect.X - (wDiff / 2.0f);
	float newY = (float)tRect.Y - (wDiff / 2.0f);

	//get viewport dimensions for clamping
	//0 -> X, 1 -> Y, 2 -> width, 3 -> height
	int viewPortDimensions[4];
	glGetIntegerv(GL_VIEWPORT, viewPortDimensions);

	//end
	return BLCreateRecti((BLInt)newX, (BLInt)newY, (BLInt)scaledW, (BLInt)scaledH);
}

/*************************************************************
* NAME: BLCenterRecti
* DATE: 2021 - 09 - 3
* PARAMS:
*	BLRecti tRect -> rect to center
*	enum BL_CENTER_TYPE cType -> which dims to center
* RETURNS:
*	centered version of tRect
* NOTE:
*	Returned rectangle is now position in the center
*	of the screen
*************************************************************/
BLRecti BLCenterRecti(BLRecti tRect, enum BL_CENTER_TYPE cType)
{
	//get viewport dimensions for centering
	//0 -> X, 1 -> Y, 2 -> width, 3 -> height
	int viewPortDimensions[4];
	glGetIntegerv(GL_VIEWPORT, viewPortDimensions);

	//centered rect
	BLRecti cRect;

	//precalculate centered dimensions
	BLInt centerX = viewPortDimensions[2] / 2;
	BLInt centerY = viewPortDimensions[3] / 2;
	BLInt rCentX = centerX - (tRect.W / 2);
	BLInt rCentY = centerY - (tRect.H / 2);

	//center cRect
	switch (cType)
	{
	case BL_CENTER_TYPE_X:

		cRect = BLCreateRecti(rCentX, tRect.Y, tRect.W, tRect.H);
		return cRect;

	case BL_CENTER_TYPE_Y:

		cRect = BLCreateRecti(tRect.X, rCentY, tRect.W, tRect.H);
		return cRect;

	case BL_CENTER_TYPE_BOTH:

		cRect = BLCreateRecti(rCentX, rCentY, tRect.W, tRect.H);
		return cRect;

	default:
		break;
	}

	//end
	return tRect;
}

/*************************************************************
* NAME: BLInitICore
* DATE: 2021 - 09 - 2
* PARAMS:
*	none
* RETURNS:
*	int, 1 for success, 0 for failure (need rendering context!)
* NOTE: N/A
*************************************************************/
int BLInitICore( )
{
	BLInitGFont( );
}

/*************************************************************
* NAME: BLTerminateICore
* DATE: 2021 - 09 - 2
* PARAMS:
*	none
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLTerminateICore( )
{
	BLTerminateGFont( );
}

/*************************************************************
* NAME: BLIRenderBox
* DATE: 2021 - 09 - 2
* PARAMS:
*	BLRect bounds -> screenspace coords for rectangle
*	BLColor color -> render color
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLIRenderBox(BLRecti bounds, BLColor color)
{
	//set up projection matrix to match up with screenspace
	BLHelperSetupProjectionMatrix( );

	//load modelview and reset matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity( );

	//normailze each color
	const GLfloat rNorm = (GLfloat)color.R / 255.0;
	const GLfloat gNorm = (GLfloat)color.G / 255.0;
	const GLfloat bNorm = (GLfloat)color.B / 255.0;
	const GLfloat aNorm = (GLfloat)color.A / 255.0;

	//set draw color
	glColor4f(rNorm, gNorm, bNorm, aNorm);

	//precalculate box coords
	const GLfloat bX = (GLfloat)bounds.X; //bottom x
	const GLfloat bY = (GLfloat)bounds.Y; //bottom y
	const GLfloat tX = (GLfloat)(bounds.X + bounds.W); //top x
	const GLfloat tY = (GLfloat)(bounds.Y + bounds.H); //top y

	//render (disable textures)
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);

	glVertex2f(bX, bY); //bottom left
	glVertex2f(bX, tY); //top left
	glVertex2f(tX, tY); //top right
	glVertex2f(tX, bY); //bottom right

	glEnd( );

	glDisable(GL_BLEND);

	//end
	return;
}

/*************************************************************
* NAME: BLIRenderBoxOutlined
* DATE: 2021 - 09 - 2
* PARAMS:
*	BLRect bounds -> screenspace coords for rectangle
*	BLColor bColor -> render color
*	BLUInt  oSize -> outline size (in pixels)
*	BLColor oColor -> outline color
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLIRenderBoxOutlined(BLRecti bounds, BLColor bColor, BLUInt oSize, BLColor oColor)
{
	//create inner box
	BLRecti boxInner = { bounds.X + oSize, bounds.Y + oSize, bounds.W - (oSize * 2), bounds.H - (oSize * 2) };

	//render outer box
	BLIRenderBox(bounds, oColor);

	//render inner box
	BLIRenderBox(boxInner, bColor);

	//end
	return;
}

/*************************************************************
* NAME: BLIRenderBoxTextured
* DATE: 2021 - 09 - 2
* PARAMS:
*	BLRect bounds -> screenspace coords for rectangle
*	BLTextureHandle tHndl -> texture to render
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLIRenderBoxTextured(BLRecti bounds, BLTextureHandle tHndl)
{
	//set up projection matrix to match up with screenspace
	BLHelperSetupProjectionMatrix( );

	//bind texture
	BLHelperSetupTexEnv(tHndl);

	//load modelview and reset matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//precalculate box coords
	const GLfloat bX = (GLfloat)bounds.X; //bottom x
	const GLfloat bY = (GLfloat)bounds.Y; //bottom y
	const GLfloat tX = (GLfloat)(bounds.X + bounds.W); //top x
	const GLfloat tY = (GLfloat)(bounds.Y + bounds.H); //top y

	//render (with texture)
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex2f(bX, bY);
	glTexCoord2f(0.0, 1.0); glVertex2f(bX, tY);
	glTexCoord2f(1.0, 1.0); glVertex2f(tX, tY);
	glTexCoord2f(1.0, 0.0); glVertex2f(tX, bY);

	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	//end
	return;

}

/*************************************************************
* NAME: BLIRenderBoxGradient
* DATE: 2021 - 09 - 2
* PARAMS:
*	BLRect bounds -> screenspace coords for rectangle
*	BLColor colorRight -> rightside color of box
*	BLColor colorLeft  -> leftside color of box
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLIRenderBoxGradient(BLRecti bounds, BLColor colorRight, BLColor colorLeft)
{
	//set up projection matrix to match up with screenspace
	BLHelperSetupProjectionMatrix( );

	//load modelview and reset matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//normailze each color (right side)
	const GLfloat rrNorm = (GLfloat)colorRight.R / 255.0;
	const GLfloat rgNorm = (GLfloat)colorRight.G / 255.0;
	const GLfloat rbNorm = (GLfloat)colorRight.B / 255.0;
	const GLfloat raNorm = (GLfloat)colorRight.A / 255.0;

	//normailze each color (left side)
	const GLfloat lrNorm = (GLfloat)colorLeft.R / 255.0;
	const GLfloat lgNorm = (GLfloat)colorLeft.G / 255.0;
	const GLfloat lbNorm = (GLfloat)colorLeft.B / 255.0;
	const GLfloat laNorm = (GLfloat)colorLeft.A / 255.0;

	//precalculate box coords
	const GLfloat bX = (GLfloat)bounds.X; //bottom x
	const GLfloat bY = (GLfloat)bounds.Y; //bottom y
	const GLfloat tX = (GLfloat)(bounds.X + bounds.W); //top x
	const GLfloat tY = (GLfloat)(bounds.Y + bounds.H); //top y

	//render (disable textures)
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);

	glColor4f(lrNorm, lgNorm, lbNorm, laNorm); glVertex2f(bX, bY); //bottom left     color left
	glColor4f(lrNorm, lgNorm, lbNorm, laNorm); glVertex2f(bX, tY); //top left        color left
	glColor4f(rrNorm, rgNorm, rbNorm, raNorm); glVertex2f(tX, tY); //top right       color right
	glColor4f(rrNorm, rgNorm, rbNorm, raNorm); glVertex2f(tX, bY); //bottom right    color right

	glEnd();

	glDisable(GL_BLEND);

	//end
	return;
}

/*************************************************************
* NAME: BLIRenderString
* DATE: 2021 - 09 - 2
* PARAMS:
*	const BLByte* str -> string to render
*	BLUInt tX -> top left X position
*	BLUInt tY -> top left Y position
*	BLUInt scale -> scale of each letter (in pixels)
*	enum BL_GFONT_TYPE sType -> type of font to render
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLIRenderString(const BLByte* str, BLUInt tX, BLUInt tY, BLUInt scale, enum BL_GFONT_TYPE sType)
{
	//get length
	const int sLen = strlen(str);

	//rect dims for drawing
	BLRecti drawRect = BLCreateRecti(tX - scale, tY - scale, scale, scale);

	//tex handle
	BLTextureHandle cHndl;

	//render loop
	for(int i = 0; i < sLen; i++)
	{
		//check for newline
		if(str[i] == '\n')
		{
			//reset x and increment Y
			drawRect.X = tX - scale;
			drawRect.Y = drawRect.Y - (BLUInt)((float)scale * BL_ICORE_NEWLINE_SCALE);
		}
		else
		{
			//draw rect
			cHndl = BLGetFontTextureHandle(str[i], sType);
			BLIRenderBoxTextured(drawRect, cHndl);

			//increment x
			drawRect.X = drawRect.X + (BLUInt)((float)scale * BL_ICORE_SPACE_SCALE);
		}
	}

	//end
	return;
}

/*************************************************************
* NAME: BLIRenderStringCentered
* DATE: 2021 - 09 - 2
* PARAMS:
*	const BLByte* str -> string to render
*	BLRecti rBounds   -> bounds of string
*	BLUInt scale -> scale of each letter (in pixels)
*	enum BL_GFONT_TYPE sType -> type of font to render
* RETURNS:
*	void
* NOTE:
*	If not newlined properly, string will write outside of bounds
*	it is expected that the string has been newlined correctly to
*	fit the bounds
*************************************************************/
void BLIRenderStringCentered(const BLByte* str, BLRecti rBounds, BLUInt scale, enum BL_GFONT_TYPE sType)
{
	//get center of rBounds
	BLInt centerX = rBounds.X + (rBounds.W / 2);
	BLInt centerY = rBounds.Y + (rBounds.H / 2);

	//get string length
	int sLen = strlen(str);

	//create newline buffer
	BLByte nlBuff[BL_ICORE_LINE_COUNT][BL_ICORE_LINE_BUF_SIZE];

	//empty buffer
	for(int i = 0; i < BL_ICORE_LINE_COUNT; i++)
	{
		for(int j = 0; j < BL_ICORE_LINE_BUF_SIZE; j++)
		{
			nlBuff[i][j] = (BLByte)NULL;
		}
	}

	//break str into newline
	int lineCount = 0;
	int lineIndex = 0;

	for(int i = 0; i < sLen; i++)
	{
		//check if newline
		if(str[i] == '\n')
		{
			//increment count and reset
			//line index
			lineCount++;
			lineIndex = 0;
		}
		else
		{
			//write to nlBuf
			nlBuff[lineCount][lineIndex] = str[i];

			//increment line index
			lineIndex++;
		}
	}

	//setup draw position vars
	BLInt drawX = 0;
	BLInt drawY = 0;

	//set draw Y
	drawY = centerY + ((lineCount * (scale * BL_ICORE_NEWLINE_SCALE)) / 2);

	//render each line
	for(int i = 0; i < lineCount + 1; i++)
	{
		//first, get char count
		int lineCharCount = strlen(nlBuff[i]) - 1;
		
		//get size
		int lineSize = scale * 1.5;
		for(int j = 0; j < lineCharCount; j++)
		{
			//check if space char
			if(nlBuff[i][j] == ' ')
			{
				lineSize += scale * BL_ICORE_SPACE_SCALE;
			}
			else
			{
				lineSize += scale;
			}
		}

		//calculate starting position (drawX)
		drawX = centerX - (lineSize / 2);

		//draw string
		//remember: BLIRenderString renders from the top left, which i need to eliminate
		BLIRenderString(nlBuff[i], drawX, drawY + (scale / 2), scale, sType);

		//newline
		drawY -= scale * BL_ICORE_NEWLINE_SCALE;
	}
}

/*************************************************************
* NAME: BLIRenderStringRect
* DATE: 2021 - 09 - 2
* PARAMS:
*	const BLByte* str -> string to render
*	BLRecti rBounds -> bounds of the string to render
*	BLUInt scale -> scale of each letter (in pixels)
*	enum BL_GFONT_TYPE sType -> type of font to render
* RETURNS:
*	int, 1 for success, 0 for string out of rect bounds
* NOTE: N/A
*************************************************************/
int BLIRenderStringRect(const BLByte* str, BLRecti rBounds, BLUInt scale, enum BL_GFONT_TYPE sType)
{
	//get string length
	const int sLen = strlen(str);

	//create buffer for word seperation
	char wBuf[BL_ICORE_STRING_WORD_COUNT][BL_ICORE_WORD_BUF_SIZE];

	//zero memory
	for(int i = 0; i < BL_ICORE_STRING_WORD_COUNT; i++)
	{
		for(int j = 0; j < BL_ICORE_WORD_BUF_SIZE; j++)
		{
			wBuf[i][j] = (char)NULL;
		}
	}

	//word counter and index
	int wCount = 0;
	int wIndex = 0;

	//break string into words
	for(int i = 0; i < sLen; i++)
	{
		if(str[i] == ' ')
		{
			//keep space
			wBuf[wCount][wIndex] = ' ';

			//increment and reset
			wCount++;
			wIndex = 0;
		}
		else
		{
			wBuf[wCount][wIndex] = str[i];
			wIndex++;
		}
	}

	//increment word count
	wCount++;

	//create rect for drawing
	BLRecti drawrect = BLCreateRecti(rBounds.X, rBounds.Y + rBounds.H - scale, scale, scale);

	//loop through every word
	for(int i = 0; i < wCount; i++)
	{
		//check if word is too big
		if(drawrect.X + (strlen(wBuf[i]) * scale) > rBounds.X + rBounds.W)
		{
			//newline
			drawrect.Y -= scale * BL_ICORE_NEWLINE_SCALE;

			//reset X
			drawrect.X = rBounds.X;

			//check if newline is too far
			if(drawrect.Y < rBounds.Y)
			{
				//end
				return 0;
			}
		}
		
		//create tex handle
		BLTextureHandle cHndl;

		//render loop
		for (int j = 0; j < strlen(wBuf[i]); j++)
		{

			//check for newline
			if (wBuf[i][j] == '\n')
			{
				//reset x and increment Y
				drawrect.X = rBounds.X;
				drawrect.Y = drawrect.Y - (BLUInt)((float)scale * BL_ICORE_NEWLINE_SCALE);

				//check if newline is too far
				if (drawrect.Y < rBounds.Y)
				{
					//end
					return 0;
				}
			}
			else
			{
				//draw rect
				cHndl = BLGetFontTextureHandle(wBuf[i][j], sType);
				BLIRenderBoxTextured(drawrect, cHndl);

				//increment x
				drawrect.X = drawrect.X + (BLUInt)((float)scale * BL_ICORE_SPACE_SCALE);
			}
		}
	}

	return 1;
}

/*************************************************************
* NAME: BLIRenderStringRectBorder
* DATE: 2021 - 09 - 2
* PARAMS:
*	const BLByte* str -> string to render
*	BLRecti rBounds -> bounds of the string to render
*	BLUInt scale    -> scale of each letter (in pixels)
*	BLUInt border   -> border (in pixels)
*	enum BL_GFONT_TYPE sType -> type of font to render
* RETURNS:
*	int, 1 for success, 0 for string out of rect bounds
* NOTE: N/A
*************************************************************/
int BLIRenderStringRectBorder(const BLByte* str, BLRecti rBounds, BLUInt scale, BLUInt border, enum BL_GFONT_TYPE sType)
{
	//inner rect
	BLRecti iRect = BLCreateRecti(rBounds.X + border, rBounds.Y + border, rBounds.W - (border * 2), rBounds.H - (border * 2));

	//draw text
	int rVal = BLIRenderStringRect(str, iRect, scale, sType);

	//end
	return rVal;
}

/*************************************************************
* NAME: BLICheckMouseOverlap
* DATE: 2021 - 09 - 3
* PARAMS:
*	BLWindowHandle wHndl -> window to check
*	BLRecti rBounds      -> bounds to check
* RETURNS:
*	int, 1 for in bounds, 0 for out of bounds
* NOTE: N/A
*************************************************************/
int BLICheckMouseOverlap(BLWindowHandle wHndl, BLRecti rBounds)
{
	//get mouse position
	BLVert2f mousePos = BLWindowGetMousePosition(wHndl);

	//inverse Y
	int viewPortDimensions[4]; //index 3 is height
	glGetIntegerv(GL_VIEWPORT, viewPortDimensions);
	mousePos.Y = viewPortDimensions[3] - mousePos.Y;

	//cast to int
	BLInt mX = (BLInt)mousePos.X;
	BLInt mY = (BLInt)mousePos.Y;

	//get bounds
	BLInt lx = rBounds.X;             //left X
	BLInt rx = rBounds.X + rBounds.W; //right X
	BLInt by = rBounds.Y;             //bottom Y
	BLInt ty = rBounds.Y + rBounds.H; //top Y

	//check if in bounds
	if(mX > lx && mX < rx)
	{
		if(mY > by && mY < ty)
		{
			//end
			return 1;
		}
	}

	//fail
	return 0;
}

/*************************************************************
* NAME: BLICheckMouseLeftDown
* DATE: 2021 - 09 - 3
* PARAMS:
*	none
* RETURNS:
*	int, 1 for mouse down, 0 for mouse up
* NOTE:
*	Checks if left mouse button is down
*************************************************************/
int BLICheckMouseLeftDown( )
{
	if(GetKeyState(VK_LBUTTON) < 0)
	{
		return 1;
	}

	return 0;
}

/*************************************************************
* NAME: BLICheckMouseRightDown
* DATE: 2021 - 09 - 3
* PARAMS:
*	none
* RETURNS:
*	int, 1 for mouse down, 0 for mouse up
* NOTE:
*	Checks if right mouse button is down
*************************************************************/
int BLICheckMouseRightDown( )
{
	if (GetKeyState(VK_RBUTTON) < 0)
	{
		return 1;
	}

	return 0;
}

/*************************************************************
* NAME: BLICheckKeyDownAlphaNumeric
* DATE: 2021 - 09 - 3
* PARAMS:
*	none
* RETURNS:
*	char, mapping to which key is down (UPPERCASE)
* NOTE:
*	Only includes all numbers and letters
*	If no key down, return NULL
*	This should NOT be used for typing! only handling keyboard
*	inputs
*************************************************************/
BLByte BLICheckKeyDownAlphaNumeric( )
{
	//check all letters
	//65 - 90 map to A-Z in VK_BUTTONS
	for(int i = 65; i < 91; i++)
	{
		if(GetKeyState(i) < 0)
		{
			return (BLByte)i;
		}
	}

	//check all numbers
	//48 - 57 map to 0 - 9 in VK_BUTTONS
	for(int i = 48; i < 57; i++)
	{
		if(GetKeyState(i) < 0)
		{
			return (BLByte)i;
		}
	}

	//check enter key
	if(GetKeyState(VK_RETURN) < 0)
	{
		return (BLByte)'\n';
	}

	//check space key
	if(GetKeyState(VK_SPACE) < 0)
	{
		return (BLByte)' ';
	}

	//no key, end
	return NULL;
}

/*************************************************************
* NAME: BLICheckKeyPushedAlphaNumeric
* DATE: 2021 - 09 - 3
* PARAMS:
*	none
* RETURNS:
*	char, mapping to which key is newly pushed down (UPPERCASE)
* NOTE:
*	Only includes all numbers and letters
*	If no key down, return NULL
*	This function returns a NEWLY pressed down key. This function
*	is meant for typing related events!
*************************************************************/
static BLByte lastPressed = NULL;
BLByte BLICheckKeyPushedAlphaNumeric( )
{
	//get current key down
	BLByte currentPressed = BLICheckKeyDownAlphaNumeric( );

	//if key down is the same as last time, returns NULL
	if(currentPressed == lastPressed)
	{
		return NULL;
	}
	else
	{
		//else, return new key down, update last pressed
		lastPressed = currentPressed;
		return currentPressed;
	}
}

/*************************************************************
* NAME: BLIGetNextChar
* DATE: 2021 - 09 - 3
* PARAMS:
*	none
* RETURNS:
*	char, mapping to which key is pushed down (UPPERCASE)
* NOTE:
*	This function covers ALL CHARS, however, it is not recommended
*	for typing related purposes, rather, input purposes
*************************************************************/
BLByte BLIGetCharDown()
{
	//check all letters
	//65 - 90 map to A-Z in VK_BUTTONS
	for (int i = 65; i < 91; i++)
	{
		if (GetKeyState(i) < 0)
		{
			return (BLByte)i;
		}
	}

	//check all numbers
	//48 - 57 map to 0 - 9 in VK_BUTTONS
	BLByte cNum = NULL;
	for (int i = 48; i < 57; i++)
	{
		if (GetKeyState(i) < 0)
		{
			cNum = (BLByte)i;
		}
	}

	//check if shifted
	int isShifted = GetKeyState(VK_SHIFT);

	//check all number special characters
	if(isShifted && cNum != NULL)
	{
		switch (cNum)
		{
		case '1':
			return '!';

		case '2':
			return '@';

		case '3':
			return '#';

		case '4':
			return '$';

		case '5':
			return '%';

		case '6':
			return '^';

		case '7':
			return '&';

		case '8':
			return '*';

		case '9':
			return '(';

		case '0':
			return ')';

		default:
			break;
		}
	}

	//if number
	if(cNum != NULL)
	{
		return cNum;
	}

	//other special characters
	BLByte specChar = NULL;
	if(GetKeyState(VK_OEM_PLUS))
	{
		specChar = '=';
	}
	if(GetKeyState(VK_OEM_MINUS))
	{
		specChar = '-';
	}
	if (GetKeyState(VK_OEM_COMMA))
	{
		specChar = ',';
	}
	if (GetKeyState(VK_OEM_PERIOD))
	{
		specChar = '.';
	}
	if (GetKeyState(VK_OEM_2))
	{
		specChar = '/';
	}
	if (GetKeyState(VK_OEM_3))
	{
		specChar = '`';
	}
	if (GetKeyState(VK_OEM_4))
	{
		specChar = '[';
	}
	if (GetKeyState(VK_OEM_5))
	{
		specChar = '\\';
	}
	if (GetKeyState(VK_OEM_6))
	{
		specChar = ']';
	}
	if (GetKeyState(VK_OEM_7))
	{
		specChar = '\'';
	}
	if (GetKeyState(VK_OEM_8))
	{
		specChar = ';';
	}

	//if shifted
	if(isShifted && specChar != NULL)
	{
		switch (specChar)
		{
		case '=':
			return '+';

		case '-':
			return '_';

		case ',':
			return '<';

		case '.':
			return '>';

		case '/':
			return '?';

		case '`':
			return '~';

		case '[':
			return '{';

		case '\\':
			return '|';

		case ']':
			return '}';

		case '\'':
			return '"';

		case ';':
			return ':';

		default:
			break;
		}
	}

	//special character
	if(specChar != NULL)
	{
		return specChar;
	}

	//other characters
	if(GetKeyState(VK_RETURN))
	{
		return '\n';
	}
	if(GetKeyState(VK_SPACE))
	{
		return ' ';
	}

	//no key down
	return NULL;
}