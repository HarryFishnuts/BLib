


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
#include <string.h> // For string parsing

/*************************************************************
* NAME: BLCreateIndexedTexture
* DATE: 2021 - 08 - 30
* PARAMS:
*	none
* RETURNS:
*	void
* NOTE:
*	This function ZEROS out the ITEX data so that no
*	garbage data seeps into it
*************************************************************/
BLIndexedTexture BLCreateIndexedTexture()
{
	//texture object to return
	BLIndexedTexture iTex;

	//clear indexes
	for(int i = 0; i < BL_FIXEDTEX_SIZE_FONT; i++)
	{
		for(int j = 0; j < BL_FIXEDTEX_SIZE_FONT; j++)
		{
			iTex.tIndex[i][j] = (BLCIndex)NULL;
		}
	}

	//clear colors
	for(int i = 0; i < BL_GFONT_MAX_COLOR_INDEX; i++)
	{
		iTex.tColors[i] = BLCreateColor(0, 0, 0, 0);
	}

	//end
	return iTex;
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

/*************************************************************
* NAME: BLCreateArrayVertFromString
* DATE: 2021 - 08 - 30
* PARAMS:
*	BLVert2i* vBuffer -> vert buffer to write to
*	const BLByte* str   -> string to parse from
*	BLUint strSize -> size of string
* RETURNS:
*	int, 1 for success, 0 for failure (string could not be parsed!)
* NOTE:
*	string should be a EVEN number long
*************************************************************/
int BLCreateArrayVertFromString(BLVert2i* vBuffer, const BLByte* str, BLUInt strSize)
{
	//counter var
	int vIndex = 0;

	//loop through string 2 bytes at a time
	for(int i = 0; i < strSize; i += 2)
	{
		//set X and Y values
		vBuffer[vIndex].X = (int)str[i + 0] - (int)'0';
		vBuffer[vIndex].Y = (int)str[i + 1] - (int)'0';

		//increment vIndex
		vIndex++;
	}

	//end
	return 1;
}

/*************************************************************
* NAME: BLEditITexIndexVStr
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLIndexedTexture* iTexPtr -> iTex to edit
*	const BLByte* VSTR -> string to parse
* RETURNS:
*	void
* NOTE:
*	Only use if YOU KNOW WHAT YOU ARE DOING
*************************************************************/
void BLEditITexIndexVStr(BLIndexedTexture* iTexPtr, const BLByte* VSTR)
{
	//vertex buffer
	BLVert2i vBuf[BL_GFONT_MAX_VBUF_SIZE];

	//clear vertex buffer
	for(int i = 0; i < BL_GFONT_MAX_VBUF_SIZE; i++)
	{
		vBuf[i].X = (BLInt)NULL;
		vBuf[i].Y = (BLInt)NULL;
	}

	//init vBuf
	BLCreateArrayVertFromString(vBuf, VSTR, strlen(VSTR));

	//write to iTex
	BLEditITexIndexArrayVert(iTexPtr, vBuf, strlen(VSTR) / 2, 1);

	//end
	return;
}

/*************************************************************
* NAME: BLCreateIndexedTextureVStr
* DATE: 2021 - 08 - 30
* PARAMS:
*	const BLByte* VSTR -> VSTR to read from
*	BLColor bg -> background color
*	BLColor fg -> foreground color
* RETURNS:
*	void
* NOTE:
*************************************************************/
BLIndexedTexture BLCreateIndexedTextureVStr(const BLByte* VSTR, BLColor bg, BLColor fg)
{
	//create iTex object
	BLIndexedTexture iTex = BLCreateIndexedTexture( );

	//set colors
	BLEditITexColor(&iTex, bg, 0);
	BLEditITexColor(&iTex, fg, 1);

	//draw VSTR
	BLEditITexIndexVStr(&iTex, VSTR);

	//end
	return iTex;
}