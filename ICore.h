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
#include "WCore.h"

#define BL_ICORE_NEWLINE_SCALE     1.5f
#define BL_ICORE_SPACE_SCALE       1.15f

#define BL_ICORE_WORD_BUF_SIZE     0x40
#define BL_ICORE_STRING_WORD_COUNT 0x80

#define BL_ICORE_LINE_BUF_SIZE 0x80
#define BL_ICORE_LINE_COUNT    0x40

#define BL_ICORE_CHAR_MATCH_COUNT 0x20

/*************************************************************
* NAME: BL_CENTER_TYPE
* DATE: 2021 - 08 - 3
* NOTE: This enum is for the BLCenterRecti function,
* and specifies which dimensions to center
*************************************************************/
enum BL_CENTER_TYPE
{
	BL_CENTER_TYPE_X = 0,
	BL_CENTER_TYPE_Y = 1,
	BL_CENTER_TYPE_BOTH = 2
};

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
	BLInt X;
	BLInt Y;
	BLInt W;
	BLInt H;
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
*	BLInt X -> screenspace X
*	BLInt Y -> screenspace Y
*	BLInt W -> width (pixels)
*	BLInt H -> height (pixels)
* RETURNS:
*	BLRecti created from params
* NOTE: N/A
*************************************************************/
BLRecti BLCreateRecti(BLInt X, BLInt Y, BLInt W, BLInt H);

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
BLRecti BLCenterRecti(BLRecti tRect, enum BL_CENTER_TYPE cType);

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
void BLIRenderStringCentered(const BLByte* str, BLRecti rBounds, BLUInt scale, enum BL_GFONT_TYPE sType);

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
int BLICheckMouseOverlap(BLWindowHandle wHndl, BLRecti rBounds);

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
int BLICheckMouseLeftDown( );

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
int BLICheckMouseRightDown( );

/*************************************************************
* NAME: BLICheckKeyDownAlphaNumeric (DEPRECATED)
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
BLByte BLICheckKeyDownAlphaNumeric( );

/*************************************************************
* NAME: BLICheckKeyPushedAlphaNumeric (DEPRECATED)
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
BLByte BLICheckKeyPushedAlphaNumeric( );

/*************************************************************
* NAME: BLIGetCharDown
* DATE: 2021 - 09 - 3
* PARAMS:
*	none
* RETURNS:
*	char, mapping to which key is pushed down (UPPERCASE)
* NOTE:
*	This function covers ALL CHARS, however, it is not recommended
*	for typing related purposes, rather, input purposes
*************************************************************/
BLByte BLIGetCharDown( );

/*************************************************************
* NAME: BLIGetChar
* DATE: 2021 - 09 - 3
* PARAMS:
*	none
* RETURNS:
*	char, mapping to which key is newly pushed down, will return
*	a continuous stream of chars if key is held down
* NOTE:
*	This function covers ALL CHARS and is intended for
*	typing related purposes
*************************************************************/
BLByte BLIGetChar( );

#endif
