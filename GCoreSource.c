


/*************************************************************
* FILE: GCoreSource.c
* DATE: 2021 - 08 - 28
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	Source file for basic rendering functions
* CONTENTS:
*	- Includes
*	- File-Specifc functions
*	- Functions
*
*************************************************************/

#include "GCore.h" // Header

#include <stdio.h>  // For I/O
#include <stdlib.h> // For memory management

#include <Windows.h> // OpenGL dependency
#include <gl/GL.h>   // Graphics library
#include <gl/GLU.h>  // Projection related functions

/*************************************************************
* NAME: BLHelperSetupTexEnv
* DATE: 2021 - 08 - 28
* PARAMS:
*	BLTextureHandle texHandle -> texture handle to setup
* RETURNS:
*	void
* NOTE: 
*	FILE SPECIFIC FUNCTION
*	Call this function before a render pass to set up the
*	texture environment
*************************************************************/
static inline void BLHelperSetupTexEnv( BLTextureHandle texHandle)
{
	glShadeModel(GL_FLAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, (GLuint)texHandle);
	glEnable(GL_TEXTURE_2D);
	return;
}

/*************************************************************
* NAME: BLHelperSetupProjectionMatrix
* DATE: 2021 - 08 - 29
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

	//get aspect ratio
	const float aspectRatio = (float)viewPortDimensions[2] / (float)viewPortDimensions[3];

	//set projection matrix
	gluOrtho2D(-aspectRatio, aspectRatio, -1, 1);

	//end
	return;
}


/*************************************************************
* NAME: BLCreateVert2f
* DATE: 2021 - 08 - 27
* PARAMS:
*	float X -> x position
*	float Y -> y position
* RETURNS:
*	BLVert2f created from PARAMS
* NOTE: N/A
*************************************************************/
BLVert2f BLCreateVert2f(float X, float Y)
{
	BLVert2f rV = { X, Y };
	return rV;
}

/*************************************************************
* NAME: BLCreateRect
* DATE: 2021 - 08 - 27
* PARAMS:
*	float X -> x position
*	float Y -> y position
*	float width  -> rect width
*	float height -> rect height
* RETURNS:
*	BLRect created from PARAMS
* NOTE: N/A
*************************************************************/
BLRect BLCreateRect(float X, float Y, float width, float height)
{
	BLRect rect = { X, Y , width, height };
	return rect;
}

/*************************************************************
* NAME: BLCreateQuad
* DATE: 2021 - 08 - 27
* PARAMS:
*	float X	    -> X position
*	float Y	    -> Y position
*	BLVert2f p0 -> bottom left vertex
*	BLVert2f p1 -> top left vertex
*	BLVert2f p2 -> top right vertex
*	BLVert2f p3 -> bottom right vertex
* RETURNS:
*	BLQuad created from PARAMS
* NOTE: This function is such a pain in the ass
*************************************************************/
BLQuad BLCreateQuad(float X, float Y, BLVert2f p0, BLVert2f p1, BLVert2f p2, BLVert2f p3)
{
	BLQuad quad = { X, Y , p0, p1, p2, p3 };
	return quad;
}

/*************************************************************
* NAME: BLCreateFixedTexFont
* DATE: 2021 - 08 - 27
* PARAMS:
*	BLByte R -> R value
*	BLByte G -> G value
*	BLByte B -> B value
*	BLByte A -> A value
* RETURNS:
*	BLFixedTexFont created from PARAMS
* NOTE: N/A
*************************************************************/
BLFixedTexFont BLCreateFixedTexFont(BLByte R, BLByte G, BLByte B, BLByte A)
{
	BLFixedTexFont bFont;
	for (int i = 0; i < BL_FIXEDTEX_SIZE_FONT; i++)
	{
		for (int j = 0; j < BL_FIXEDTEX_SIZE_FONT; j++)
		{
			bFont.data[i][j][0] = R;
			bFont.data[i][j][1] = G;
			bFont.data[i][j][2] = B;
			bFont.data[i][j][3] = A;
		}
	}
	return bFont;
}

/*************************************************************
* NAME: BLCreateFixedTexSmall
* DATE: 2021 - 08 - 27
* PARAMS:
*	BLByte R -> R value
*	BLByte G -> G value
*	BLByte B -> B value
*	BLByte A -> A value
* RETURNS:
*	BLFixedTexSmall created from PARAMS
* NOTE: N/A
*************************************************************/
BLFixedTexSmall BLCreateFixedTexSmall(BLByte R, BLByte G, BLByte B, BLByte A)
{
	BLFixedTexSmall bSmall;
	for (int i = 0; i < BL_FIXEDTEX_SIZE_SMALL; i++)
	{
		for (int j = 0; j < BL_FIXEDTEX_SIZE_SMALL; j++)
		{
			bSmall.data[i][j][0] = R;
			bSmall.data[i][j][1] = G;
			bSmall.data[i][j][2] = B;
			bSmall.data[i][j][3] = A;
		}
	}

	return bSmall;
}

/*************************************************************
* NAME: BLCreateFixedTexLarge
* DATE: 2021 - 08 - 27
* PARAMS:
*	BLByte R -> R value
*	BLByte G -> G value
*	BLByte B -> B value
*	BLByte A -> A value
* RETURNS:
*	BLFixedTexLarge created from PARAMS
* NOTE: N/A
*************************************************************/
BLFixedTexLarge BLCreateFixedTexLarge(BLByte R, BLByte G, BLByte B, BLByte A)
{
	BLFixedTexLarge bLarge;
	for (int i = 0; i < BL_FIXEDTEX_SIZE_LARGE; i++)
	{
		for (int j = 0; j < BL_FIXEDTEX_SIZE_LARGE; j++)
		{
			bLarge.data[i][j][0] = R;
			bLarge.data[i][j][1] = G;
			bLarge.data[i][j][2] = B;
			bLarge.data[i][j][3] = A;
		}
	}

	return bLarge;
}

/*************************************************************
* NAME: BLCreateTexHandleFree
* DATE: 2021 - 08 - 28
* PARAMS:
*	void* textureData -> data to send to OpenGL
*	BLUInt texSizeHeight -> height of texture
*	BLUInt texSizeWidth  -> width of texture
* RETURNS:
*	BLTextureHandle generated by openGL (GLuint)
* NOTE:
*	texture data has to be RGBA with each channel a byte large
*	texture data can be freed after use of this function
*	THIS FUNCTION IS A DEPENDENCY TO BLCreateTexHandleFixed
*************************************************************/
BLTextureHandle BLCreateTexHandleFree(void* textureData, BLUInt texSizeHeight, BLUInt texSizeWidth)
{
	//variable to return
	BLTextureHandle texHndl;

	//create texName and generate texture
	GLuint texName;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texName);

	//bind texture
	glBindTexture(GL_TEXTURE_2D, texName);

	//set texture wrap parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//pack data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texSizeWidth, texSizeHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

	//end
	texHndl = texName;
	return texHndl;
}

/*************************************************************
* NAME: BLCreateTexHandleFixed
* DATE: 2021 - 08 - 28
* PARAMS:
*	void* fixedTexture                -> pointer to fixedTexture struct
*	enum BL_TARGET_FIXEDTEX_TYPE type -> specifies what kind of fixedTexture
* RETURNS:
*	BLTextureHandle generated by openGL (GLuint)
* NOTE: fixedTexture can be freed after use of this function
*************************************************************/
BLTextureHandle BLCreateTexHandleFixed(void* fixedTexture, enum BL_TARGET_FIXEDTEX_TYPE type)
{
	BLTextureHandle texHndl;

	switch (type)
	{
	case BL_TARGET_FIXEDTEX_TYPE_FONT:
		
		texHndl = BLCreateTexHandleFree(fixedTexture, BL_FIXEDTEX_SIZE_FONT, BL_FIXEDTEX_SIZE_FONT);
		break;

	case BL_TARGET_FIXEDTEX_TYPE_SMALL:

		texHndl = BLCreateTexHandleFree(fixedTexture, BL_FIXEDTEX_SIZE_SMALL, BL_FIXEDTEX_SIZE_SMALL);
		break;
	case BL_TARGET_FIXEDTEX_TYPE_LARGE:

		texHndl = BLCreateTexHandleFree(fixedTexture, BL_FIXEDTEX_SIZE_LARGE, BL_FIXEDTEX_SIZE_LARGE);
		break;
	default:

		return NULL;
	}

	return texHndl;
}

/*************************************************************
* NAME: BLDestroyTexHandle
* DATE: 2021 - 08 - 28
* PARAMS:
*	BLTextureHandle texToFree -> frees texture from GPU (via openGL)
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLDestroyTexHandle(BLTextureHandle texToFree)
{
	glDeleteTextures(1, &texToFree);
	return;
}

/*************************************************************
* NAME: BLRenderTextureSquare
* DATE: 2021 - 08 - 28
* PARAMS:
*	BLTextureHandle texHndl -> texture handle
*	float posX  -> X position of texture center
*	float posY  -> Y position of texture center
*	float scale -> scale of texture
*	float angle -> angle of texture (in degrees)
* RETURNS: void
* NOTE: N/A
*************************************************************/
void BLRenderTextureSquare(BLTextureHandle texHndl, float posX, float posY, float scale, float angle)
{
	//set up texture environment
	BLHelperSetupTexEnv(texHndl);

	//set up projection matrix
	BLHelperSetupProjectionMatrix( );

	//reset object position
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity( );

	//APPLY OFFSETS IN THIS ORDER:
	//	1. Scale
	//	2. Rotate
	//	3. Translate
	glTranslatef(posX, posY, 0);
	glRotatef(angle, 0, 0, 1);
	glScalef(scale, scale, scale);

	//draw square
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, -1.0);
	glTexCoord2f(0.0, 1.0); glVertex2f(-1.0,  1.0);
	glTexCoord2f(1.0, 1.0); glVertex2f( 1.0,  1.0);
	glTexCoord2f(1.0, 0.0); glVertex2f( 1.0, -1.0);

	glEnd( );

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	//end
	return;
}

/*************************************************************
* NAME: BLRenderTextureRect
* DATE: 2021 - 08 - 28
* PARAMS:
*	BLTextureHandle texHndl -> texture handle
*	BLRect texRect -> rectangle which describes the texture's scale in relative to a 1x1 square
*	float scale -> scale of texture
*	float angle -> angle of texture (in degrees around the center)
* RETURNS: void
* NOTE: N/A
*************************************************************/
void BLRenderTextureRect(BLTextureHandle texHndl, BLRect texRect, float scale, float angle)
{
	//grab rectangle dimenstions
	const float scaleX = texRect.width;
	const float scaleY = texRect.height;

	//set up texture environment
	BLHelperSetupTexEnv(texHndl);

	//set up projection matrix
	BLHelperSetupProjectionMatrix();

	//reset object position
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity( );

	//APPLY OFFSETS IN THIS ORDER:
	//	1. Scale
	//	2. Rotate
	//	3. Translate
	glTranslatef(texRect.X, texRect.Y, 0);
	glRotatef(angle, 0, 0, 1);
	glScalef(scale, scale, scale);

	//draw rectangle
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(-1 * scaleX, -1 * scaleY);
	glTexCoord2f(0, 1); glVertex2f(-1 * scaleX,  1 * scaleY);
	glTexCoord2f(1, 1); glVertex2f( 1 * scaleX,  1 * scaleY);
	glTexCoord2f(1, 0); glVertex2f( 1 * scaleX, -1 * scaleY);

	glEnd( );
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	//end
	return;
}

/*************************************************************
* NAME: BLRenderTextureQuad
* DATE: 2021 - 08 - 28
* PARAMS:
*	BLTextureHandle texHndl -> texture handle
*	BLRect texRect -> quad which describes the worldspace position that the texture
*	is the be drawn (the quad is expected to be normalized)
*	float scale -> scale of texture
*	float angle -> angle of texture (in degrees)
* RETURNS: void
* NOTE: N/A
*************************************************************/
void BLRenderTextureQuad(BLTextureHandle texHndl, BLQuad texQuad, float scale, float angle)
{
	//set up texture environment
	BLHelperSetupTexEnv(texHndl);

	//set up projection matrix
	BLHelperSetupProjectionMatrix();

	//reset object position
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity( );

	//APPLY OFFSETS IN THIS ORDER:
	//	1. Scale
	//	2. Rotate
	//	3. Translate
	glTranslatef(texQuad.X, texQuad.Y, 0);
	glRotatef(angle, 0, 0, 1);
	glScalef(scale, scale, scale);

	//draw quad
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(texQuad.p0.X, texQuad.p0.Y);
	glTexCoord2f(0, 1); glVertex2f(texQuad.p1.X, texQuad.p1.Y);
	glTexCoord2f(1, 1); glVertex2f(texQuad.p2.X, texQuad.p2.Y);
	glTexCoord2f(1, 0); glVertex2f(texQuad.p3.X, texQuad.p3.Y);

	glEnd( );
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	//end
	return;
}

/*************************************************************
* NAME: BLClearBuffers
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLByte R -> clear color R
*	BLByte G -> clear color G
*	BLByte B -> clear color B
*	BLByte A -> clear color A
* RETURNS: void
* NOTE:
*	Clear depth and color buffer
*************************************************************/
void BLClearBuffers(BLByte R, BLByte G, BLByte B, BLByte A)
{
	//normalize clear colors
	const float clearR = (float)R / 255.0f;
	const float clearG = (float)G / 255.0f;
	const float clearB = (float)B / 255.0f;
	const float clearA = (float)A / 255.0f;
	
	//set openGL clear color
	glClearColor(clearR, clearG, clearB, clearA);

	//clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//end
	return;
}