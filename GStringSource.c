


/*************************************************************
* FILE: GStringSource.c
* DATE: 2021 - 08 - 31
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	Source file for primitive string rendering
* CONTENTS:
*	- Includes
* 	- Functions
*
*************************************************************/

#include "GString.h" // Header
#include <stdio.h>   // For I/O
#include <string.h>  // For string parsing related functions

/*************************************************************
* NAME: BLInitGString
* DATE: 2021 - 08 - 31
* PARAMS:
*	none
* RETURNS:
*	int, 1 for success, 0 for failure (need rendering context)
* NOTE:
*	Inits GFont
*************************************************************/
int BLInitGString( )
{
	return BLInitGFont( );
}

/*************************************************************
* NAME: BLTerminateGString
* DATE: 2021 - 08 - 31
* PARAMS:
*	none
* RETURNS:
*	void
* NOTE:
*	Terminates GFont
*************************************************************/
void BLTerminateGString( )
{
	BLTerminateGFont( );

	//end
	return;
}

/*************************************************************
* NAME: BLRenderString
* DATE: 2021 - 08 - 31
* PARAMS:
*	const BLByte* string -> string to render
*	enum BL_GFONT_TYPE fType -> type of font to render
*	float X -> top left X position
*	float Y -> top left Y position
*	float S -> draw scale
* RETURNS:
*	void
* NOTE:	N/A
*************************************************************/
void BLRenderString(const BLByte* string, enum BL_GFONT_TYPE fType, float X, float Y, float S)
{
	//create quad so that draw position is
	//not centered, but in fact top left corner
	const BLVert2f p0 = BLCreateVert2f(0, -1);
	const BLVert2f p1 = BLCreateVert2f(0,  0);
	const BLVert2f p2 = BLCreateVert2f(1,  0);
	const BLVert2f p3 = BLCreateVert2f(1, -1);
	BLQuad textQuad = BLCreateQuad(X, Y, p0, p1, p2, p3);

	//get string size
	int sLength = strlen(string);

	//aux variables for the for loop
	BLTextureHandle charHndl = NULL;
	BLByte          scanChar = NULL;

	//loop
	for(int i = 0; i < sLength; i++)
	{
		//get current character
		scanChar = string[i];

		//check if newline
		if(scanChar == '\n')
		{
			//reset X position
			textQuad.X = X;

			//increment drawY
			textQuad.Y -= S + (S * BL_GSTRING_NEWLINE_SCALE);
		}
		else
		{
			//if not newline, render

			//get texture handle
			charHndl = BLGetFontTextureHandle(scanChar, fType);

			//render texture
			BLRenderTextureQuad(charHndl, textQuad, S, 0);

			//increment drawX
			textQuad.X += S + (S * BL_GSTRING_SPACING_RATIO);
		}
	}
	
	//end
	return;
}