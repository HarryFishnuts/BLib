


/*************************************************************
* FILE: GTexLibSource.c
* DATE: 2021 - 08 - 28
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	Source file for extended texture manipulation library
* CONTENTS:
*	- Includes
*	- Defs
*	- Enums
*	- Structs
*	- Functions
*
*************************************************************/

#include "GTexLib.h" // Header

#include <stdio.h>  // I/O
#include <stdlib.h> // Memory management
#include <math.h>   // Math

/*************************************************************
* NAME: BLCreateColor
* DATE: 2021 - 08 - 28
* PARAMS:
*	BLByte R -> R value
*	BLByte G -> G value
*	BLByte B -> B value
*	BLByte A -> A value
* RETURNS:
*	BLColor created from PARAMS
* NOTE: N/A
*************************************************************/
BLColor BLCreateColor(BLByte R, BLByte G, BLByte B, BLByte A)
{
	BLColor color = { R, G, B, A };
	return color;
}

/*************************************************************
* NAME: BLCreateFixedTexDetail
* DATE: 2021 - 08 - 28
* PARAMS:
*	BLByte R -> R value
*	BLByte G -> G value
*	BLByte B -> B value
*	BLByte A -> A value
* RETURNS:
*	BLFixedTexDetail created from PARAMS
* NOTE: N/A
*************************************************************/
BLFixedTexDetail BLCreateFixedTexDetail(BLByte R, BLByte G, BLByte B, BLByte A)
{
	BLFixedTexDetail texDetail;
	for(int i = 0; i < BL_FIXEDTEX_SIZE_DETAIL; i++)
	{
		for(int j = 0; j < BL_FIXEDTEX_SIZE_DETAIL; j++)
		{
			texDetail.data[i][j][0] = R;
			texDetail.data[i][j][1] = G;
			texDetail.data[i][j][2] = B;
			texDetail.data[i][j][3] = A;
		}
	}

	return texDetail;
}

/*************************************************************
* NAME: BLEditTexDrawPixFixed
* DATE: 2021 - 08 - 28
* PARAMS:
*	void* fixedTex    -> texture to draw Pixel on
*	BLColor drawColor -> color to draw Pixel
*	enum BL_TARGET_TEXEDIT_TYPE texType -> type of fixed textre
*	BLUInt x -> Pixel X position
*	BLUInt y -> Pixel Y position
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLEditTexDrawPixFixed(void* fixedTex, BLColor drawColor, enum BL_TARGET_TEXEDIT_TYPE texType, BLUInt x, BLUInt y)
{
	//Vars for texture editing
	BLFixedTexFont*   texFont;
	BLFixedTexSmall*  texSmall;
	BLFixedTexLarge*  texLarge;
	BLFixedTexDetail* texDetail;

	//switch statement based on texType param
	switch (texType)
	{
	case BL_TARGET_TEXEDIT_TYPE_FONT:

		//clamp
		if(x > BL_FIXEDTEX_SIZE_FONT - 1 || y > BL_FIXEDTEX_SIZE_FONT - 1)
		{
			break;
		}

		//fixedTex font editing
		texFont = fixedTex;

		texFont->data[y][x][0] = drawColor.R;
		texFont->data[y][x][1] = drawColor.G;
		texFont->data[y][x][2] = drawColor.B;
		texFont->data[y][x][3] = drawColor.A;

		break;

	case BL_TARGET_TEXEDIT_TYPE_SMALL:

		//clamp
		if (x > BL_FIXEDTEX_SIZE_SMALL - 1 || y > BL_FIXEDTEX_SIZE_SMALL - 1)
		{
			break;
		}

		//fixedTex small editing
		texSmall = fixedTex;

		texSmall->data[y][x][0] = drawColor.R;
		texSmall->data[y][x][1] = drawColor.G;
		texSmall->data[y][x][2] = drawColor.B;
		texSmall->data[y][x][3] = drawColor.A;

		break;

	case BL_TARGET_TEXEDIT_TYPE_LARGE:

		//clamp
		if (x > BL_FIXEDTEX_SIZE_LARGE - 1 || y > BL_FIXEDTEX_SIZE_LARGE - 1)
		{
			break;
		}

		//fixedTex large editing
		texLarge = fixedTex;

		texLarge->data[y][x][0] = drawColor.R;
		texLarge->data[y][x][1] = drawColor.G;
		texLarge->data[y][x][2] = drawColor.B;
		texLarge->data[y][x][3] = drawColor.A;

		break;

	case BL_TARGET_TEXEDIT_TYPE_DETAIL:

		//clamp
		if (x > BL_FIXEDTEX_SIZE_DETAIL - 1 || y > BL_FIXEDTEX_SIZE_DETAIL - 1)
		{
			break;
		}

		//fixedTex detail editing
		texDetail = fixedTex;

		texDetail->data[y][x][0] = drawColor.R;
		texDetail->data[y][x][1] = drawColor.G;
		texDetail->data[y][x][2] = drawColor.B;
		texDetail->data[y][x][3] = drawColor.A;

		break;

	default:

		break;
	}

	//end
	return;
}

/*************************************************************
* NAME: BLEditTexDrawLineFixed
* DATE: 2021 - 08 - 28
* PARAMS:
*	void* fixedTex    -> texture to draw Pixel on
*	BLColor drawColor -> color to draw Pixel
*	enum BL_TARGET_TEXEDIT_TYPE texType -> type of fixed textre
*	BLUInt x1 -> Pixel X position of first vertex (0 Indexed)
*	BLUInt y1 -> Pixel Y position of first vertex (0 Indexed)
*	BLUInt x2 -> Pixel X position of second vertex (0 Indexed)
*	BLUInt y1 -> Pixel Y position of second vertex (0 Indexed)
* RETURNS:
*	void
* NOTE: This function is VERY slow when called alot, try to use sparsely
* or use precalculated textures
*************************************************************/
void BLEditTexDrawLineFixed(void* fixedTex, BLColor drawColor, enum BL_TARGET_TEXEDIT_TYPE texType, BLUInt x1, BLUInt y1, BLUInt x2, BLUInt y2)
{
	//get difference and magnitude
	const float deltaX = (float)x2 - (float)x1;
	const float deltaY = (float)y2 - (float)y1;
	
	const float magnitude = sqrtf( powf(deltaX, 2)  +  powf(deltaY, 2) );

	//get step size
	const float stepX = deltaX / magnitude;
	const float stepY = deltaY / magnitude;

	//set up draw variables
	float drawX = (float)x1;
	float drawY = (float)y1;

	//draw line (some margin of error)
	for (int i = 0; i <= magnitude; i++)
	{
		//set pixel
		BLEditTexDrawPixFixed(fixedTex, drawColor, texType, (BLUInt)drawX, (BLUInt)drawY);

		//increment draw position
		drawX += stepX;
		drawY += stepY;
	}

	//to correct for line drawing error, fill in
	//vertex end pixels
	BLEditTexDrawPixFixed(fixedTex, drawColor, texType, x1, y1);
	BLEditTexDrawPixFixed(fixedTex, drawColor, texType, x2, y2);

	//end
	return;
}

/*************************************************************
* NAME: BLEditTexDrawRectFixed
* DATE: 2021 - 08 - 28
* PARAMS:
*	void* fixedTex    -> texture to draw Pixel on
*	BLColor drawColor -> color to draw Pixel
*	enum BL_TARGET_TEXEDIT_TYPE texType -> type of fixed textre
*	BLRect fillRect   -> rect to fill drawColor
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLEditTexDrawRectFixed(void* fixedTex, BLColor drawColor, enum BL_TARGET_TEXEDIT_TYPE texType, BLRect fillRect)
{
	//precalculate end points for drawing
	const int endX = fillRect.X + fillRect.width;
	const int endY = fillRect.Y + fillRect.height;

	//fill rect
	for(int i = fillRect.X; i < endX; i++)
	{
		for(int j = fillRect.Y; j < endY; j++)
		{
			BLEditTexDrawPixFixed(fixedTex, drawColor, texType, i, j);
		}
	}

	//end
	return;
}

/*************************************************************
* NAME: BLEditTexGetPixColor
* DATE: 2021 - 08 - 28
* PARAMS:
*	void* fixedTex    -> texture to get Pixel from
*	enum BL_TARGET_TEXEDIT_TYPE texType -> type of fixed textre
*	BLUInt x -> X position of Pixel
*	BLUInt y -> Y position of Pixel
* RETURNS:
*	BLColor of pixel (color will be returned as [255, 0, 255, 255] if pix is out of bounds)
* NOTE: N/A
*************************************************************/
BLColor BLEditTexGetPixColorFixed(void* fixedTex, enum BL_TARGET_TEXEDIT_TYPE texType, BLUInt x, BLUInt y)
{
	//return color (set to Err color)
	BLColor returnCol = BLCreateColor(255, 0, 255, 255);

	//Vars for texture editing
	BLFixedTexFont* texFont;
	BLFixedTexSmall* texSmall;
	BLFixedTexLarge* texLarge;
	BLFixedTexDetail* texDetail;

	//switch based on texType
	switch (texType)
	{
	case BL_TARGET_TEXEDIT_TYPE_FONT:

		//set data
		texFont = fixedTex;

		//copy data
		returnCol.R = texFont->data[x][y][0];
		returnCol.G = texFont->data[x][y][1];
		returnCol.B = texFont->data[x][y][2];
		returnCol.A = texFont->data[x][y][3];

		//end
		break;

	case BL_TARGET_TEXEDIT_TYPE_SMALL:

		//set data
		texSmall = fixedTex;

		//copy data
		returnCol.R = texSmall->data[x][y][0];
		returnCol.G = texSmall->data[x][y][1];
		returnCol.B = texSmall->data[x][y][2];
		returnCol.A = texSmall->data[x][y][3];

		//end
		break;

	case BL_TARGET_TEXEDIT_TYPE_LARGE:

		//set data
		texLarge = fixedTex;

		//copy data
		returnCol.R = texLarge->data[x][y][0];
		returnCol.G = texLarge->data[x][y][1];
		returnCol.B = texLarge->data[x][y][2];
		returnCol.A = texLarge->data[x][y][3];

		//end
		break;

	case BL_TARGET_TEXEDIT_TYPE_DETAIL:

		//set data
		texDetail = fixedTex;

		//copy data
		returnCol.R = texDetail->data[x][y][0];
		returnCol.G = texDetail->data[x][y][1];
		returnCol.B = texDetail->data[x][y][2];
		returnCol.A = texDetail->data[x][y][3];

		//end
		break;

	default:

		//return err-color
		break;
	}

	//end
	return returnCol;
}