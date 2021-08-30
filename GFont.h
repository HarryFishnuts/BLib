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

typedef uint8_t BLCIndex;

/*************************************************************
* IMPORTANT:
*	BLFChar is NOT meant to represent ASCII
*	Instead, it is meant to represent the BTIS (Bailey's Text Indexing Sequence)
* 
*	MAIN DIFFERENCES BETWEEN ASCII AND BTIS:
*	BLFChar is signed
*	BTIS follows the following sequence:
*		[00 - 09] numerical (0 - 10)
*		[10 - 36] letters   (A - Z)
*		[37 - 51] symbols
*	
*	NOTE THAT THE SYMBOLS SEQUENCE IN BTIS DIRECTLY MAPS TO
*	THE VALUES [32 - 47] IN ASCII
* 
*	ALL BTIS VALUES AND THEIR ASCII COUNTERPARTS IN ORDER:
* 
*	|	0.  0	|   11. B	|   22. M	|   34. X	|   45. )	|
*	|	1.  1	|   12. C	|   23. N	|   35. Y	|   46. *	|
*	|	2.  2	|   13. D	|   24. O	|   36. Z	|   47. +	|
*	|	3.  3	|   14. E	|   25. P	|   37.		|   48. ,	|
*	|	4.  4	|   15. F	|   26. Q	|   38. !	|   49. -	|
*	|	5.  5	|   16. G	|   27. R	|   39. #	|   50. .	|
*	|	6.  6	|   17. H	|   28. S	|   40. $	|   51. /	|
*	|	7.  7	|   18. I	|   30. T	|   41. %	|			|
*	|	8.  8	|   19. J	|   31. U	|   42. &	|			|
*	|	9.  9	|   20. K	|   32. V	|   43. '	|			|
*	|	10. A	|   21. L	|   33. W	|   44. (	|			|
*************************************************************/
typedef int8_t BLFChar;

/*************************************************************
* NAME: BLVert2i
* DATE: 2021 - 08 - 29
* MEMBERS:
*	BLInt X -> X value
*	BLInt Y -> Y value
* NOTE: N/A
*************************************************************/
typedef struct BLVert2i
{
	BLInt X;
	BLInt Y;
}BLVert2i;

/*************************************************************
* NAME: BLIndexedTexture
* DATE: 2021 - 08 - 29
* MEMBERS:
*	BLColor tColors -> colors available to index to
*	BLColorIndex tIndex[][] -> index array
* NOTE: 
*	iTextures have no associated Create function
*************************************************************/
typedef struct BLIndexedTexture
{
	BLColor tColors[BL_GFONT_MAX_COLOR_INDEX];
	BLCIndex tIndex[BL_FIXEDTEX_SIZE_FONT][BL_FIXEDTEX_SIZE_FONT];
}BLIndexedTexture;

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
void BLEditITexColor(BLIndexedTexture* iTexPtr, BLColor iColor, BLCIndex index);

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
void BLEditITexIndex(BLIndexedTexture* iTexPtr, BLUInt iX, BLUInt iY, BLCIndex value);

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
void BLEditITexIndexArray(BLIndexedTexture* iTexPtr, BLUInt* arrX, BLUInt* arrY, BLUInt arrSize, BLCIndex value);

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
void BLEditITexIndexArrayVert(BLIndexedTexture* iTexPtr, BLVert2i* vArr, BLUInt size, BLCIndex value);

/*************************************************************
* NAME: BLCompileITex
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLIndexedTexture iTex -> ITex data to compile
* RETURNS:
*	BLFixedTexFont created from ITex
* NOTE: N/A
*************************************************************/
BLFixedTexFont BLCompileITex(BLIndexedTexture iTex);

/*************************************************************
* NAME: BLInitGFont
* DATE: 2021 - 08 - 29
* PARAMS:
*	none
* RETURNS:
*	void
* NOTE:
*	Generates 4 fontsets, takes up a considerable amount of
*	space in memory
*************************************************************/
void BLInitGFont( );

/*************************************************************
* NAME: BLTerminateGFont
* DATE: 2021 - 08 - 29
* PARAMS:
*	none
* RETURNS:
*	void
* NOTE:
*	Frees all GFont memory from both CPU and GPU
*************************************************************/
void BLTerminateGFont( );

#endif