


/*************************************************************
* FILE: GFontSource.c
* DATE: 2021 - 08 - 28
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	Source file for basic color index texture and font/letter
*	rendering
* CONTENTS:
*	- Includes
*	- Backend struct defs
*	- Backend objects
*	- Functions
*
*************************************************************/

#include "GFont.h"  // Header

#include <stdio.h>  // I/O
#include <stdlib.h> // Memory management

typedef BLFontSet
{
	
}

/*************************************************************
* NAME: BLEditITexColor
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLIndexedTexture* iTexPtr -> iTex to edit
*	BLColor iColor -> color to set index
*	BLCIndex index -> index for color
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLEditITexColor(BLIndexedTexture* iTexPtr, BLColor iColor, BLCIndex index)
{
	iTexPtr->tColors[(int)index] = iColor;

	//end
	return;
}

/*************************************************************
* NAME: BLEditITexIndex
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLIndexedTexture* iTexPtr -> iTex to edit
*	BLUInt iX -> index X position
*	BLUInt iY -> index Y position
*	BLCIndex value -> index value
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLEditITexIndex(BLIndexedTexture* iTexPtr, BLUInt iX, BLUInt iY, BLCIndex value)
{
	iTexPtr->tIndex[(int)iX][(int)iY] = value;

	//end
	return;
}

/*************************************************************
* NAME: BLEditITexIndexArray
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLIndexedTexture* iTexPtr -> iTex to edit
*	BLUInt* arrX -> array of index X position
*	BLUInt* arrY -> array of index Y position
*	BLUInt arrSize -> size of arrX and arrY arrays
*	BLCIndex value -> index value
* RETURNS:
*	void
* NOTE:
*	arrX and arrY MUST be the same size
*************************************************************/
void BLEditITexIndexArray(BLIndexedTexture* iTexPtr, BLUInt* arrX, BLUInt* arrY, BLUInt arrSize, BLCIndex value)
{
	for(int i = 0; i < (int)arrSize; i++)
	{
		iTexPtr->tIndex[(int)arrX[i]][(int)arrY[i]] = value;
	}

	//end
	return;
}

/*************************************************************
* NAME: BLEditITexIndexArray
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLIndexedTexture* iTexPtr -> iTex to edit
*	BLVert2i* vArr -> vertex array
*	BLUInt arrSize -> size of vertex array
*	BLCIndex value -> index value
* RETURNS:
*	void
* NOTE:
*	this function makes BLEditITexIndexArray obsolete
*************************************************************/
void BLEditITexIndexArrayVert(BLIndexedTexture* iTexPtr, BLVert2i* vArr, BLUInt size, BLCIndex value)
{
	for(int i = 0; i < (int)size; i++)
	{
		iTexPtr->tIndex[(int)vArr[i].X][(int)vArr[i].Y] = value;
	}

	//end
	return;
}

/*************************************************************
* NAME: BLCompileITex
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLIndexedTexture iTex -> ITex data to compile
* RETURNS:
*	BLFixedTexFont created from ITex
* NOTE: N/A
*************************************************************/
BLFixedTexFont BLCompileITex(BLIndexedTexture iTex)
{
	//object to return
	BLFixedTexFont fontTex;

	//loop through each pixel
	for(int i = 0; i < BL_FIXEDTEX_SIZE_FONT; i++)
	{
		for(int j = 0; j < BL_FIXEDTEX_SIZE_FONT; j++)
		{
			BLEditTexDrawPixFixed(&fontTex, iTex.tColors[(int)iTex.tIndex[i][j]], BL_TARGET_TEXEDIT_TYPE_FONT, i, j);
		}
	}

	//end
	return fontTex;
}