

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

#include "ICore.h"   // Header
#include <stdio.h>   // I/O
#include <Windows.h> // OpenGL dependancy
#include <gl/GL.h>   // For rendering
#include <gl/GLU.h>  // For projection related functions

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
static inline void BLHelperSetupProjectionMatrix()
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
*	BLUInt X -> screenspace X
*	BLUInt Y -> screenspace Y
*	BLUInt W -> width (pixels)
*	BLUInt H -> height (pixels)
* RETURNS:
*	BLRecti created from params
* NOTE: N/A
*************************************************************/
BLRecti BLCreateRecti(BLUInt X, BLUInt Y, BLUInt W, BLUInt H)
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

	//clamp low
	if(newX < 0)
	{
		newX = 0;
	}
	if(newY < 0)
	{
		newY = 0;
	}

	//clamp high
	if(newX + scaledW > (float)viewPortDimensions[2])
	{
		scaledW = (float)viewPortDimensions[2];
	}
	if(newY + scaledH > (float)viewPortDimensions[3])
	{
		scaledH = (float)viewPortDimensions[3];
	}

	//end
	return BLCreateRecti((BLUInt)newX, (BLUInt)newY, (BLUInt)scaledW, (BLUInt)scaledH);
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