#ifndef __GTEXLIB_INCLUDE__
#define __GTEXLIB_INCLUDE__


/*************************************************************
* FILE: GTexLib.h
* DATE: 2021 - 08 - 28
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	Extended texture manipulation library
* CONTENTS:
*	- Includes
*	- Defs
*	- Enums
*	- Structs
*	- Functions
*
*************************************************************/

#include "GCore.h"

#define BL_FIXEDTEX_SIZE_DETAIL 32

/*************************************************************
* NAME: BL_TARGET_TEXEDIT_TYPE
* DATE: 2021 - 08 - 27
* NOTE: This enum is used for the BLCreateTexHandleFixed function
*************************************************************/
enum BL_TARGET_TEXEDIT_TYPE
{
	BL_TARGET_TEXEDIT_TYPE_FONT   = 0,
	BL_TARGET_TEXEDIT_TYPE_SMALL  = 1,
	BL_TARGET_TEXEDIT_TYPE_LARGE  = 2,
	BL_TARGET_TEXEDIT_TYPE_DETAIL = 3
};

/*************************************************************
* NAME: BLColor
* DATE: 2021 - 08 - 28
* MEMBERS:
*	BLByte R;
*	BLByte G;
*	BLByte B;
*	BLByte A;
* NOTE:
*************************************************************/
typedef struct BLColor
{
	BLByte R;
	BLByte G;
	BLByte B;
	BLByte A;
} BLColor;

/*************************************************************
* NAME: BLFixedTexDetail
* DATE: 2021 - 08 - 28
* MEMBERS:
*	BLByte data [][][] -> Holds RGBA color data in bytes
* NOTE: Size is 32x32
*************************************************************/
typedef struct BLFixedTexDetail
{
	BLByte data[BL_FIXEDTEX_SIZE_DETAIL][BL_FIXEDTEX_SIZE_DETAIL][BL_FIXEDTEX_COLOR_CHANNELS];
} BLFixedTexDetail;

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
BLColor BLCreateColor(BLByte R, BLByte G, BLByte B, BLByte A);

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
BLFixedTexDetail BLCreateFixedTexDetail(BLByte R, BLByte G, BLByte B, BLByte A);

/*************************************************************
* NAME: BLEditTexDrawPixFixed
* DATE: 2021 - 08 - 28
* PARAMS:
*	void* fixedTex    -> texture to draw Pixel on
*	BLColor drawColor -> color to draw Pixel
*	enum BL_TARGET_TEXEDIT_TYPE texType -> type of fixed textre
*	BLUInt x -> Pixel X position (0 Indexed)
*	BLUInt y -> Pixel Y position (0 Indexed)
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLEditTexDrawPixFixed(void* fixedTex, BLColor drawColor, enum BL_TARGET_TEXEDIT_TYPE texType, BLUInt x, BLUInt y);

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
void BLEditTexDrawLineFixed(void* fixedTex, BLColor drawColor, enum BL_TARGET_TEXEDIT_TYPE texType, BLUInt x1, BLUInt y1, BLUInt x2, BLUInt y2);

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
void BLEditTexDrawRectFixed(void* fixedTex, BLColor drawColor, enum BL_TARGET_TEXEDIT_TYPE texType, BLRect fillRect);

/*************************************************************
* NAME: BLEditTexGetPixColorFixed
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
BLColor BLEditTexGetPixColorFixed(void* fixedTex, enum BL_TARGET_TEXEDIT_TYPE texType, BLUInt x, BLUInt y);

#endif