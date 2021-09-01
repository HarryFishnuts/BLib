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
#define BL_GFONT_MAX_VBUF_SIZE   0x80
#define BL_GFONT_FONT_COUNT      0x40
#define BL_GFONT_FONTSET_COUNT   5

#define BL_GFONT_WHITE    255, 255, 255, 255
#define BL_GFONT_BLACK    000, 000, 000, 255
#define BL_GFONT_BURGUNDY 100, 000, 020, 255
#define BL_GFONT_NAVY     000, 040, 100, 255
#define BL_GFONT_TAN      210, 180, 120, 255

#define BL_VSTR_A "10111213243332313022"
#define BL_VSTR_B "101112131424333122203034"
#define BL_VSTR_C "11121324342030"
#define BL_VSTR_D "101112131424344342413020"
#define BL_VSTR_E "1011121314243422322030"
#define BL_VSTR_F "101112131424342232"
#define BL_VSTR_G "2030111213243444324241"
#define BL_VSTR_H "1011121314303132333422"
#define BL_VSTR_I "142434102030212223"
#define BL_VSTR_J "1120313233342414"
#define BL_VSTR_K "10111213143031333422"
#define BL_VSTR_L "10111213142030"
#define BL_VSTR_M "00010213223342414044044303"
#define BL_VSTR_N "101112131423324443424140"
#define BL_VSTR_O "010203414243102030142434"
#define BL_VSTR_P "10111213142434333222"
#define BL_VSTR_Q "01020342431020142434223140"
#define BL_VSTR_R "10111213142433223140"
#define BL_VSTR_S "102031322212132434"
#define BL_VSTR_T "20212223241434"
#define BL_VSTR_U "1413121120313233341030"
#define BL_VSTR_V "141312112031323334"
#define BL_VSTR_W "0403021021304142434401"
#define BL_VSTR_X "04312231400011334413"
#define BL_VSTR_Y "14133433222120"
#define BL_VSTR_Z "142434332211102030"

#define BL_VSTR_ZERO  "141312112031323334103024"
#define BL_VSTR_ONE   "1324232221201030"
#define BL_VSTR_TWO   "1424343332221211102030"
#define BL_VSTR_THREE "142434332231302010"
#define BL_VSTR_FOUR  "141312223233343130"
#define BL_VSTR_FIVE  "1020313222121324341430"
#define BL_VSTR_SIX   "142434131211102030313222"
#define BL_VSTR_SEVEN "1424343222212033"
#define BL_VSTR_EIGHT "14131211203132333410302422"
#define BL_VSTR_NINE  "14131231323334302422"

#define BL_VSTR_SPACE      ""
#define BL_VSTR_EXCLAIM    "24232220"
#define BL_VSTR_HASHTAG    "01031413121110232134333231304341"
#define BL_VSTR_DOLLAR     ""
#define BL_VSTR_PERCENT    "00112233440440"
#define BL_VSTR_AND        ""
#define BL_VSTR_APOSTROPHE "2423"
#define BL_VSTR_BRACEOPEN  "2413121120"
#define BL_VSTR_BRACECLOSE "2433323120"
#define BL_VSTR_ASTERISK   "2423221333"
#define BL_VSTR_PLUS       "021222324224232120"
#define BL_VSTR_COMMA      "2110"
#define BL_VSTR_MINUS      "0212223242"
#define BL_VSTR_PERIOD     "11102120"
#define BL_VSTR_SLASH      "3433221110"

#define BL_VSTR_QUESTION  "14243433232220"
#define BL_VSTR_OPEN_JAG  "3423122130"
#define BL_VSTR_CLOSE_JAG "1423322110"

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
*		[10 - 35] letters   (A - Z)
*		[37 - 50] symbols
*		[51+    ] extra symbols
*	
*	NOTE THAT THE SYMBOLS SEQUENCE IN BTIS DIRECTLY MAPS TO
*	THE VALUES [32 - 47] IN ASCII
* 
*	ALL BTIS VALUES AND THEIR ASCII COUNTERPARTS IN ORDER:
* 
*	|	0.  0	|   11. B	|   22. M	|   33. X	|   44. )	|
*	|	1.  1	|   12. C	|   23. N	|   34. Y	|   45. *	|
*	|	2.  2	|   13. D	|   24. O	|   35. Z	|   46. +	|
*	|	3.  3	|   14. E	|   25. P	|   36.		|   47. ,	|
*	|	4.  4	|   15. F	|   26. Q	|   37. !	|   48. -	|
*	|	5.  5	|   16. G	|   27. R	|   38. #	|   49. .	|
*	|	6.  6	|   17. H	|   28. S	|   39. $	|   50. /	|
*	|	7.  7	|   18. I	|   39. T	|   40. %	|   51. ?	|
*	|	8.  8	|   19. J	|   30. U	|   41. &	|   52. <	|
*	|	9.  9	|   20. K	|   31. V	|   42. '	|   53. >	|
*	|	10. A	|   21. L	|   32. W	|   43. (	|			|
*************************************************************/
typedef int8_t BLFChar;

/*************************************************************
* NAME: BL_GFONT_TYPE
* DATE: 2021 - 08 - 30
* NOTE: N/A
*************************************************************/
enum BL_GFONT_TYPE
{
	BL_GFONT_TYPE_WHITE    = 0,
	BL_GFONT_TYPE_BLACK    = 1,
	BL_GFONT_TYPE_BURGUNDY = 2,
	BL_GFONT_TYPE_NAVY     = 3,
	BL_GFONT_TYPE_TAN      = 4
};

/*************************************************************
* NAME: BLVert2i
* DATE: 2021 - 08 - 29
* MEMBERS:
*	BLInt X -> X position
*	BLInt Y -> Y position
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
* NOTE: N/A
*************************************************************/
typedef struct BLIndexedTexture
{
	BLColor tColors[BL_GFONT_MAX_COLOR_INDEX];
	BLCIndex tIndex[BL_FIXEDTEX_SIZE_FONT][BL_FIXEDTEX_SIZE_FONT];
}BLIndexedTexture;

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
BLIndexedTexture BLCreateIndexedTexture();

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
int BLCreateArrayVertFromString(BLVert2i* vBuffer, const BLByte* str, BLUInt strSize);

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
void BLEditITexIndexVStr(BLIndexedTexture* iTexPtr, const BLByte* VSTR);

/*************************************************************
* NAME: BLCreateIndexedTextureVStr
* DATE: 2021 - 08 - 30
* PARAMS:
*	const BLByte* VSTR -> VSTR to read from
*	BLColor bg -> background color
*	BLColor fg -> foreground color
* RETURNS:
*	BLIndexedTexture made from a given VStr
* NOTE: N/A
*************************************************************/
BLIndexedTexture BLCreateIndexedTextureVStr(const BLByte* VSTR, BLColor bg, BLColor fg);

/*************************************************************
* NAME: BLCreateFontVStr
* DATE: 2021 - 08 - 30
* PARAMS:
*	const BLByte* VSTR -> VSTR to read from
*	BLColor bg -> background color
*	BLColor fg -> foreground color
* RETURNS:
*	BLFixedTexFont created from VStr
* NOTE: N/A
*************************************************************/
BLFixedTexFont BLCreateFontVStr(const BLByte* VSTR, BLColor bg, BLColor fg);

/*************************************************************
* NAME: BLCreateTexHandleVStr
* DATE: 2021 - 08 - 30
* PARAMS:
*	const BLByte* VSTR -> VSTR to read from
*	BLColor bg -> background color
*	BLColor fg -> foreground color
* RETURNS:
*	BLTextureHandle created from VStr
* NOTE: N/A
*************************************************************/
BLTextureHandle BLCreateTexHandleVStr(const BLByte* VSTR, BLColor bg, BLColor fg);

/*************************************************************
* NAME: BLInitGFont
* DATE: 2021 - 08 - 30
* PARAMS:
*	none
* RETURNS:
*	int, 1 for success, 0 for failure (need rendering context)
* NOTE:
*	Generates 4 fontsets, takes up a considerable amount of
*	space in memory
*	Requires an ACTIVE window to run!
*************************************************************/
int BLInitGFont( );

/*************************************************************
* NAME: BLTerminateGFont
* DATE: 2021 - 08 - 30
* PARAMS:
*	none
* RETURNS:
*	void
* NOTE:
*	Frees all GFont memory from both CPU and GPU
*************************************************************/
void BLTerminateGFont( );

/*************************************************************
* NAME: BLGetFontTextureHandle
* DATE: 2021 - 08 - 30
* PARAMS:
*	BLByte character -> ASCII equiv of BTIS character
* RETURNS:
*	BLTextureHandle of pre-generated font texture
* NOTE:
*	Call BLInitGFont to use this function
*************************************************************/
BLTextureHandle BLGetFontTextureHandle(BLByte character, enum BL_GFONT_TYPE fType);

#endif