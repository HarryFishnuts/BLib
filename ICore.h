#ifndef __ICORE_INCLUDE__
#define __ICORE_INCLUDE__


/*************************************************************
* FILE: ICore.h
* DATE: 2021 - 09 - 22
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	Primitive user interface library
* CONTENTS:
*	- Includes
*	- Defs
*	- Enums
*	- Structs
*	- Functions
*
*************************************************************/

#include "GFont.h"

#define BL_ICORE_NEWLINE_SCALE     1.5f
#define BL_ICORE_SPACE_SCALE       1.15f
#define BL_ICORE_WORD_BUF_SIZE     0x40
#define BL_ICORE_STRING_WORD_COUNT 0x80

/*************************************************************
* NAME: BLRecti
* DATE: 2021 - 09 - 2
* MEMBERS:
*	BLInt X -> X position
*	BLInt Y -> Y position
* NOTE: N/A
*************************************************************/
typedef struct BLRecti
{
	BLUInt X;
	BLUInt Y;
	BLUInt W;
	BLUInt H;
}BLRecti;

/*************************************************************
* NAME: BLInitICore
* DATE: 2021 - 09 - 2
* PARAMS:
*	none
* RETURNS:
*	int, 1 for success, 0 for failure (need rendering context!)
* NOTE: N/A
*************************************************************/
int BLInitICore( );

/*************************************************************
* NAME: BLTerminateICore
* DATE: 2021 - 09 - 2
* PARAMS:
*	none
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLTerminateICore( );

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
BLRecti BLCreateRecti(BLUInt X, BLUInt Y, BLUInt W, BLUInt H);

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
BLRecti BLScaleRecti(BLRecti tRect, float scale);

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
void BLIRenderBox(BLRecti bounds, BLColor color);

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
void BLIRenderBoxOutlined(BLRecti bounds, BLColor bColor, BLUInt oSize, BLColor oColor);

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
void BLIRenderBoxTextured(BLRecti bounds, BLTextureHandle tHndl);

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
void BLIRenderBoxGradient(BLRecti bounds, BLColor colorRight, BLColor colorLeft);

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
void BLIRenderString(const BLByte* str, BLUInt tX, BLUInt tY, BLUInt scale, enum BL_GFONT_TYPE sType);

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
int BLIRenderStringRect(const BLByte* str, BLRecti rBounds, BLUInt scale, enum BL_GFONT_TYPE sType);

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
int BLIRenderStringRectBorder(const BLByte* str, BLRecti rBounds, BLUInt scale, BLUInt border, enum BL_GFONT_TYPE sType);

#endif
