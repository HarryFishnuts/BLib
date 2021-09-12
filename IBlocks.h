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
	BLByte hasText        -> 1 for has text, 0 for no text
	BLUInt textScale      -> scale of text
	BLByte bText[]        -> text buffer for text
	BLByte hasBorder      -> 1 for border, 0 for no border
	BLUInt borderSize     -> size of border (in pixels)
* NOTE: N/A
*************************************************************/
typedef struct BLBlock
{
	enum BL_BLOCK_LOOK bLook;
	BLRecti            bDims;
	BLColor            color0;
	BLColor            color1;
	BLTextureHandle    tHndl;
	BLByte             hasText;
	BLUInt             textScale;
	BLByte             bText[BL_BLOCK_TEXT_MAX];
	BLByte             hasBorder;
	BLUInt             borderSize;
} BLBlock;

/*************************************************************
* NAME: BLTextField
* DATE: 2021 - 09 - 12
* MEMBERS:
*	enum BL_GFONT_TYPE fType -> type of text to render
*	BLUInt textScale    -> scale of text
*	BLByte hasTextClamp -> 1 for use textClamp, 0 for no clamp
*	BLUInt textClamp    -> max amount of text
*	BLByte bText[]      -> text to render
*	BLRecti dims -> dimensions
* NOTE: N/A
*************************************************************/
typedef struct BLTextField
{
	enum BL_GFONT_TYPE fType;
	BLUInt textScale;
	BLByte hasTextClamp;
	BLUInt textClamp;
	BLByte bText[BL_TEXFIELD_TEXT_MAX];
	BLRecti dims;
} BLTextField;

/*************************************************************
* NAME: BLButton
* DATE: 2021 - 09 - 12
* MEMBERS:
* 	BLByte  hasBorder  -> 1 for border, 0 for none
	BLUInt  borderSize -> border scale in pixels
	BLColor fg -> button color
	BLColor bg -> border color
	BLByte  hasText      -> 1 for text, 0 for no text
	BLByte  hasTextClamp -> 1 for texClamp, 0 for none
	BLUInt  textClamp    -> maximum text size
	BLUInt  textScale    -> text scale (in pixels)
	BLByte  bText[]      -> text buffer to render
	float   hoverScale   -> scale of button when overlapping
	with mouse
	float   clickScale   -> scale of button when clicked
	BLRecti dims -> dimensions
* NOTE: N/A
*************************************************************/
typedef struct BLButton
{
	BLByte hasBorder;
	BLUInt borderSize;
	BLColor fg;
	BLColor bg;
	BLByte hasText;
	BLByte hasTextClamp;
	BLUInt textClamp;
	BLUInt textScale;
	BLByte bText[BL_BUTTON_TEXT_MAX];
	float hoverScale;
	float clickScale;
	BLRecti dims;
};

/*************************************************************
* NAME: BLCreateRecti
* DATE: 2021 - 09 - 12
* PARAMS:
*	enum BL_BLOCK_LOOK bLook -> how the BLBlock will be rendered
*	BLRecti bDims  -> dims of the BLBlock
*	BLColor* bCols -> 2 BLColors, first being the main color,
* second being the border color. If the block is a gradient, the
* first is the left color, and second is the right color
*	BLUInt bSize  -> border size (in pixels), NULL for no border
*	BLUInt tScale -> text scale	
*	BLByte* tBuf  -> text buffer (must be null terminated)
* 
* RETURNS:
*	BLBlock create from params
* NOTE: N/A
*************************************************************/
BLBlock BLICreateBlock(enum BL_BLOCK_LOOK bLook, BLRecti bDims, BLColor* bCols, BLUInt bSize, BLUInt tScale, BLByte* tBuf);


#endif
