#ifndef __GFONT_INCLUDE__
#define __GFONT_INCLUDE__


/*************************************************************
* FILE: GFont.h
* DATE: 2021 - 08 - 29
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	Color indexer structure and font def header
* CONTENTS:
*	- Includes
*	- Defs
*	- Typedefs
*	- Enums
*	- Structs
*	- Functions
*
*************************************************************/

#include "GTexLib.h" // For color related struct

#define BL_GFONT_MAX_COLOR_INDEX 0xf

typedef uint8_t BLColorIndex;

/*************************************************************
* NAME: BLIndexedTexture
* DATE: 2021 - 08 - 29
* MEMBERS:
*	BLColor tColors -> colors available to index to
*	BLColorIndex tIndex[][] -> index array
* NOTE: N/A
*************************************************************/
typedef struct BLIndexedTexture
{
	BLColor tColors[BL_GFONT_MAX_COLOR_INDEX];
	BLColorIndex tIndex[BL_FIXEDTEX_SIZE_FONT][BL_FIXEDTEX_SIZE_FONT];
}BLIndexedTexture;

#endif