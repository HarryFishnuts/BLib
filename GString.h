#ifndef __GSTRING_INCLUDE__
#define __GSTRING_INCLUDE__


/*************************************************************
* FILE: GString.h
* DATE: 2021 - 08 - 31
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	Primitive string renderer library
* CONTENTS:
*	- Includes
*	- Defs
*	- Functions
*
*************************************************************/

#include "GFont.h" //For font rendering

#define BL_GSTRING_SPACING_RATIO 0.15f
#define BL_GSTRING_NEWLINE_SCALE 0.35f

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
int BLInitGString( );

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
void BLTerminateGString( );

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
void BLRenderString(const BLByte* string, enum BL_GFONT_TYPE fType, float X, float Y, float S);

#endif
