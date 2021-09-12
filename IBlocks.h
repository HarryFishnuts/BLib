#ifndef __IBLOCKS_INCLUDE__
#define __IBLOCKS_INCLUDE__

/*************************************************************
* FILE: IBlocks.h
* DATE: 2021 - 09 - 06
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	Extended user interface library
* CONTENTS:
*	- Includes
*	- Defs
*	- Enums
*	- Structs
*	- Functions
*
*************************************************************/

#include "ICore.h"

#define BL_BLOCK_TEXT_MAX    0x80
#define BL_TEXFIELD_TEXT_MAX 0xf0
#define BL_BUTTON_TEXT_MAX   0x20

typedef BLShort BLBlockHandle;

/*************************************************************
* NAME: BL_BLOCK_TYPE
* DATE: 2021 - 09 - 12
* NOTE: This enum determines what kind of block a certain
* data is associated with
*************************************************************/
enum BL_BLOCK_TYPE
{
	BL_BLOCK_TYPE_BLOCK     = 0,
	BL_BLOCK_TYPE_TEXTFIELD = 1,
	BL_BLOCK_TYPE_BUTTON    = 2
};

/*************************************************************
* NAME: BL_BLOCK_TYPE
* DATE: 2021 - 09 - 12
* NOTE: This enum determines how a block is to be rendered
*************************************************************/
enum BL_BLOCK_LOOK
{
	BL_BLOCK_LOOK_SOLID = 0,
	BL_BLOCK_LOOK_TEXTURE = 1,
	BL_BLOCK_LOOK_GRADIENT = 2
};

/*************************************************************
* NAME: BLBlock
* DATE: 2021 - 09 - 12
* MEMBERS:
*	enum BL_BLOCK_LOOK bLook -> the way the block is rendered
*	BLRecti bDims         -> the dims of the block
*	BLColor color0        -> leftside color of gradient (primary color
	if block is solid)
	BLColor color1        -> rightside color of gradient
	BLTextureHandle tHndl -> texture of BLBlock (if applicable)
	int hasText           -> 1 for has text, 0 for no text
	int textScale         -> scale of text
	BLByte bText[]        -> text buffer for text
* NOTE: N/A
*************************************************************/
typedef struct BLBlock
{
	enum BL_BLOCK_LOOK bLook;
	BLRecti            bDims;
	BLColor            color0;
	BLColor            color1;
	BLTextureHandle    tHndl;
	int                hasText;
	int                textScale;
	BLByte             bText[BL_BLOCK_TEXT_MAX];
} BLBlock;

/*************************************************************
* NAME: BLTextField
* DATE: 2021 - 09 - 12
* MEMBERS:
*	enum BL_GFONT_TYPE fType -> type of text to render
*	int    textScale    -> scale of text
*	int    hasTextClamp -> 1 for use textClamp, 0 for no clamp
*	int    textClamp    -> max amount of text
*	BLByte bText[]      -> text to render
*	BLRecti dims -> dimensions
* NOTE: N/A
*************************************************************/
typedef struct BLTextField
{
	enum BL_GFONT_TYPE fType;
	int    textScale;
	int    hasTextClamp;
	int    textClamp;
	BLByte bText[BL_TEXFIELD_TEXT_MAX];
	BLRecti dims;
} BLTextField;

/*************************************************************
* NAME: BLButton
* DATE: 2021 - 09 - 12
* MEMBERS:
*	enum BL_GFONT_TYPE fType -> type of text to render
*	int    textScale    -> scale of text
*	int    hasTextClamp -> 1 for use textClamp, 0 for no clamp
*	int    textClamp    -> max amount of text
*	BLByte bText[]      -> text to render
*	BLRecti dims -> dimensions
* NOTE: N/A
*************************************************************/
typedef struct BLButton
{
	int hasBorder;
	int borderSize;
	BLColor fg;
	BLColor bg;
	int hasText;
	int hasTextClamp;
	int textClamp;
	int textScale;
	BLByte bText[BL_BUTTON_TEXT_MAX];
	float hoverScale;
	float clickScale;
};




#endif
