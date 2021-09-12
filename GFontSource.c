


/*************************************************************
* FILE: GFontSource.c
* DATE: 2021 - 08 - 28
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	Source file for basic color index texture and font/letter
*	rendering
* CONTENTS:
*	- Includes
* 	- Functions
*	- Backend struct defs
*	- Backend objects
*
*************************************************************/


#include <stdio.h>  // I/O
#include <stdlib.h> // Memory management
#include <string.h> // For string parsing
#include <glfw3.h>  // For making sure a window context exists

#include "GFont.h"  // Header

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
	for(int i = 0; i < (int)strSize; i += 2)
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
*	BLIndexedTexture made from a given VStr
* NOTE: N/A
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
BLFixedTexFont BLCreateFontVStr(const BLByte* VSTR, BLColor bg, BLColor fg)
{
	//font texture
	BLFixedTexFont texFont;

	//create iTex object
	BLIndexedTexture iTex = BLCreateIndexedTextureVStr(VSTR, bg, fg);

	//compile iTex and send to texFont
	texFont = BLCompileITex(iTex);

	//end
	return texFont;
}

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
BLTextureHandle BLCreateTexHandleVStr(const BLByte* VSTR, BLColor bg, BLColor fg)
{
	//generate FTex
	BLFixedTexFont fTex = BLCreateFontVStr(VSTR, bg, fg);

	//send FTex down to openGL
	BLTextureHandle texHndl = BLCreateTexHandleFixed(&fTex, BL_TARGET_FIXEDTEX_TYPE_FONT);

	//end
	return texHndl;
}

/*************************************************************
* NAME: BLFontSet
* DATE: 2021 - 08 - 30
* MEMBERS:
* NOTE: File specific struct
*************************************************************/
typedef struct BLFontSet
{
	BLTextureHandle fTexList[BL_GFONT_FONT_COUNT];
}BLFontSet;

/*************************************************************
* NAME: BLFonts
* DATE: 2021 - 08 - 30
* MEMBERS:
* NOTE: File specific struct, there should only be one
* instance of this struct at ALL times
*************************************************************/
typedef struct BLFonts
{
	BLFontSet fonts[BL_GFONT_FONTSET_COUNT];
}BLFonts;

/*************************************************************
* NAME: allFonts (object)
* DATE: 2021 - 08 - 30
* USE:
*	This is an instance of the BLFonts struct used to hold
*	all predifined letters for rendering
* NOTE: N/A
*************************************************************/
static BLFonts* allFonts = NULL;

/*************************************************************
* NAME: BLHelperCreateFontSet
* DATE: 2021 - 08 - 30
* PARAMS:
*	BLColor fColor -> color of font
* RETURNS:
*	BLFontSet
* NOTE:
*	This function fills a fontset
*************************************************************/
static inline BLFontSet BLHelperCreateFontSet(BLColor fColor)
{
	//fontset object for filling
	BLFontSet fontSet;

	//get pointer to fontSet's fTexList member
	BLTextureHandle* tBuf = fontSet.fTexList;

	//counter var
	int counter = 0;

	//define local macro
	#define BLFillTBuf(vStr) tBuf[counter] = BLCreateTexHandleVStr(vStr, BLCreateColor(0, 0, 0, 0), fColor); counter++;
	
	//fill numbers
	BLFillTBuf(BL_VSTR_ZERO ); // 0
	BLFillTBuf(BL_VSTR_ONE  ); // 1
	BLFillTBuf(BL_VSTR_TWO  ); // 2
	BLFillTBuf(BL_VSTR_THREE); // 3
	BLFillTBuf(BL_VSTR_FOUR ); // 4
	BLFillTBuf(BL_VSTR_FIVE ); // 5
	BLFillTBuf(BL_VSTR_SIX  ); // 6
	BLFillTBuf(BL_VSTR_SEVEN); // 7
	BLFillTBuf(BL_VSTR_EIGHT); // 8
	BLFillTBuf(BL_VSTR_NINE ); // 9

	//letters
	BLFillTBuf(BL_VSTR_A);	BLFillTBuf(BL_VSTR_B); // 11
	BLFillTBuf(BL_VSTR_C);	BLFillTBuf(BL_VSTR_D); // 13
	BLFillTBuf(BL_VSTR_E);	BLFillTBuf(BL_VSTR_F); // 15
	BLFillTBuf(BL_VSTR_G);	BLFillTBuf(BL_VSTR_H); // 17
	BLFillTBuf(BL_VSTR_I);	BLFillTBuf(BL_VSTR_J); // 19
	BLFillTBuf(BL_VSTR_K);	BLFillTBuf(BL_VSTR_L); // 21
	BLFillTBuf(BL_VSTR_M);	BLFillTBuf(BL_VSTR_N); // 23
	BLFillTBuf(BL_VSTR_O);	BLFillTBuf(BL_VSTR_P); // 25
	BLFillTBuf(BL_VSTR_Q);	BLFillTBuf(BL_VSTR_R); // 27
	BLFillTBuf(BL_VSTR_S);	BLFillTBuf(BL_VSTR_T); // 29
	BLFillTBuf(BL_VSTR_U);	BLFillTBuf(BL_VSTR_V); // 31
	BLFillTBuf(BL_VSTR_W);	BLFillTBuf(BL_VSTR_X); // 33
	BLFillTBuf(BL_VSTR_Y);	BLFillTBuf(BL_VSTR_Z); // 35

	//symbols
	BLFillTBuf(BL_VSTR_SPACE     ); // 36
	BLFillTBuf(BL_VSTR_EXCLAIM   ); // 37
	BLFillTBuf(BL_VSTR_HASHTAG   ); // 38
	BLFillTBuf(BL_VSTR_DOLLAR    ); // 39
	BLFillTBuf(BL_VSTR_PERCENT   ); // 40
	BLFillTBuf(BL_VSTR_AND       ); // 41
	BLFillTBuf(BL_VSTR_APOSTROPHE); // 42
	BLFillTBuf(BL_VSTR_BRACEOPEN ); // 43
	BLFillTBuf(BL_VSTR_BRACECLOSE); // 44
	BLFillTBuf(BL_VSTR_ASTERISK  ); // 45
	BLFillTBuf(BL_VSTR_PLUS      ); // 46
	BLFillTBuf(BL_VSTR_COMMA     ); // 47
	BLFillTBuf(BL_VSTR_MINUS     ); // 48
	BLFillTBuf(BL_VSTR_PERIOD    ); // 49
	BLFillTBuf(BL_VSTR_SLASH     ); // 50

	//extra symbols
	BLFillTBuf(BL_VSTR_QUESTION  ); //51
	BLFillTBuf(BL_VSTR_OPEN_JAG  ); //52
	BLFillTBuf(BL_VSTR_CLOSE_JAG ); //53
	BLFillTBuf(BL_VSTR_COLON     ); //54
	BLFillTBuf(BL_VSTR_EQUAL     ); //55
	BLFillTBuf(BL_VSTR_SEMICOLON ); //56
	BLFillTBuf(BL_VSTR_QUOTE     ); //57
	BLFillTBuf(BL_VSTR_OPEN_BOX  ); //58
	BLFillTBuf(BL_VSTR_CLOSE_BOX ); //59
	BLFillTBuf(BL_VSTR_OPEN_CURL ); //60
	BLFillTBuf(BL_VSTR_CLOSE_CURL); //61

	//undefine macro
	#undef BLFillTBuf

	//end
	return fontSet;
}

/*************************************************************
* NAME: BLHelperConvertASCIItoBTIS
* DATE: 2021 - 08 - 30
* PARAMS:
*	BLByte aChar -> character to convert
* RETURNS:
*	BLFChar as a converted char index into a fontset struct
* NOTE:
*	This function fills a fontset
*************************************************************/
static inline BLFChar BLHelperConvertASCIItoBTIS(BLByte aChar)
{
	//get integer value of ascii character
	int aIndex = (int)aChar;

	//conversion

	//number condition
	if(aIndex > 47 && aIndex < 58) 
	{
		return (BLFChar)(aIndex - 48);
	}

	//lowercase condition
	if(aIndex > 96 && aIndex < 123)
	{
		aIndex -= 32; //convert to uppercase
	}

	//uppercase condition
	if(aIndex > 64 && aIndex < 91)
	{
		return (BLFChar)(aIndex - 55);
	}

	//symbol condition 0 
	if(aIndex > 31 && aIndex < 34)
	{
		return (BLFChar)(aIndex + 4);
	}

	//symbol condition 1
	if (aIndex > 34 && aIndex < 48)
	{
		return (BLFChar)(aIndex + 3);
	}

	//extra symbols
	switch (aIndex)
	{
	case '?':
		return 51;

	case '<':
		return 52;

	case '>':
		return 53;

	case ':':
		return 54;

	case '=':
		return 55;

	case ';':
		return 56;

	case '"':
		return 57;

	case '[':
		return 58;

	case ']':
		return 59;

	case '{':
		return 60;

	case '}':
		return 61;

	default:

		break;
	}

	//symbol discard (no double quotation in BTIS)

	//err type
	return (BLFChar)36;
}

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
int BLInitGFont( )
{
	//check for rendering context
	GLFWwindow* context = glfwGetCurrentContext( );

	//check if null
	if(context == NULL)
	{
		fprintf(stderr, "Cannot run BLInitGFont: No rendering context!\n");
		return 0;
	}

	//see if already init
	if(allFonts != NULL)
	{
		fprintf(stderr, "GFont already init!\n");
		return 0;
	}

	//init allFonts
	allFonts = calloc(1, sizeof(BLFonts));

	//check if null
	if(allFonts == NULL)
	{
		fprintf(stderr, "Cannot Init GFonts: memory err\n");
		return 0;
	}

	//generate fontsets
	allFonts->fonts[0] = BLHelperCreateFontSet(BLCreateColor(BL_GFONT_WHITE   ));
	allFonts->fonts[1] = BLHelperCreateFontSet(BLCreateColor(BL_GFONT_BLACK   ));
	allFonts->fonts[2] = BLHelperCreateFontSet(BLCreateColor(BL_GFONT_BURGUNDY));
	allFonts->fonts[3] = BLHelperCreateFontSet(BLCreateColor(BL_GFONT_NAVY    ));
	allFonts->fonts[4] = BLHelperCreateFontSet(BLCreateColor(BL_GFONT_TAN     ));

	//end
	return 1;
}

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
void BLTerminateGFont()
{
	//free all textures from openGL
	for(int i = 0; i < BL_GFONT_FONTSET_COUNT; i++)
	{
		for(int j = 0; j < BL_GFONT_FONT_COUNT; j++)
		{
			BLDestroyTexHandle(allFonts->fonts[i].fTexList[j]);
		}
	}

	//free allfonts
	free(allFonts);

	//end
	return;
}

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
BLTextureHandle BLGetFontTextureHandle(BLByte character, enum BL_GFONT_TYPE fType)
{
	//texture handle
	BLTextureHandle texHndl;

	//check if null
	if(allFonts == NULL)
	{
		fprintf(stderr, "allfont was null!\n");
		return NULL;
	}

	//switch based on fType
	switch (fType)
	{
	case BL_GFONT_TYPE_WHITE:

		return allFonts->fonts[0].fTexList[(int)BLHelperConvertASCIItoBTIS(character)];

	case BL_GFONT_TYPE_BLACK:

		return allFonts->fonts[1].fTexList[(int)BLHelperConvertASCIItoBTIS(character)];

	case BL_GFONT_TYPE_BURGUNDY:

		return allFonts->fonts[2].fTexList[(int)BLHelperConvertASCIItoBTIS(character)];

	case BL_GFONT_TYPE_NAVY:

		return allFonts->fonts[3].fTexList[(int)BLHelperConvertASCIItoBTIS(character)];

	case BL_GFONT_TYPE_TAN:

		return allFonts->fonts[4].fTexList[(int)BLHelperConvertASCIItoBTIS(character)];


	default:
		break;
	}

	return NULL;
}

/*************************************************************
* NAME: BLPrintAllFontsTextureHandles
* DATE: 2021 - 09 - 2
* PARAMS:
*	void
* RETURNS:
*	void
* NOTE:
*	Prints out all texture handles
*************************************************************/
void BLPrintAllFontsTextureHandles( )
{
	for(int i = 0; i < BL_GFONT_FONTSET_COUNT; i++)
	{
		for(int j = 0; j < BL_GFONT_FONT_COUNT; j++)
		{
			printf("FONTSET: %d\tFONTNUM: %d\tHANDLE: %d\n", i, j, allFonts->fonts[i].fTexList[j]);
		}
	}
}