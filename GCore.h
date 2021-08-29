#ifndef __GCORE_INCLUDE__
#define __GCORE_INCLUDE__


/*************************************************************
* FILE: GCore.h
* DATE: 2021 - 08 - 27
* DEVS: Bailey Jia-Tao Brown
* DESC:
*	Basic rendering helper library
* CONTENTS:
*	- Includes
*	- Defs
*	- Typedefs
*	- Enums
*	- Structs
*	- Functions
* 
*************************************************************/

#include <stdint.h> // for consistent byte sizes

#define BL_ERR_FIXEDTEX_TYPE_ERR "FixedTexType Err\n"

#define BL_FIXEDTEX_SIZE_FONT  5  //5x5 font textures
#define BL_FIXEDTEX_SIZE_SMALL 8  //8x8 basic textures
#define BL_FIXEDTEX_SIZE_LARGE 16 //16x16 detailed textures
#define BL_FIXEDTEX_COLOR_CHANNELS 4 //4 channels, RGBA

typedef uint8_t  BLByte;
typedef int32_t  BLInt;
typedef uint16_t BLShort;
typedef uint32_t BLTextureHandle;
typedef uint32_t BLUInt;

/*************************************************************
* NAME: BL_TARGET_FIXEDTEX_TYPE
* DATE: 2021 - 08 - 27
* NOTE: This enum is used for the BLCreateTexHandleFixed function
*************************************************************/
enum BL_TARGET_FIXEDTEX_TYPE
{
	BL_TARGET_FIXEDTEX_TYPE_FONT  = 0,
	BL_TARGET_FIXEDTEX_TYPE_SMALL = 1,
	BL_TARGET_FIXEDTEX_TYPE_LARGE = 2
};

/*************************************************************
* NAME: BLVert2f
* DATE: 2021 - 08 - 27
* MEMBERS:
*	float X	-> holds X position
*	float Y	-> holds Y position
* NOTE: N/A
*************************************************************/
typedef struct BLVert2f
{
	float X;
	float Y;
} BLVert2f;

/*************************************************************
* NAME: BLRect
* DATE: 2021 - 08 - 27
* MEMBERS:
*	float X	     -> holds X position
*	float Y	     -> holds Y position
*	float width	 -> holds width
*	float height -> holds height
* NOTE: N/A
*************************************************************/
typedef struct BLRect
{
	float X;
	float Y;
	float width;
	float height;
} BLRect;

/*************************************************************
* NAME: BLQuad
* DATE: 2021 - 08 - 27
* MEMBERS:
*	float X	    -> holds X position
*	float Y	    -> holds Y position
*	BLVert2f p0 -> bottom left vertex
*	BLVert2f p1 -> top left vertex
*	BLVert2f p2 -> top right vertex
*	BLVert2f p3 -> bottom right vertex
* NOTE: N/A
*************************************************************/
typedef struct BLQuad
{
	float X;
	float Y;

	BLVert2f p0;
	BLVert2f p1;
	BLVert2f p2;
	BLVert2f p3;
} BLQuad;

/*************************************************************
* NAME: BLFixedTexFont
* DATE: 2021 - 08 - 27
* MEMBERS:
*	BLByte data [][][] -> Holds RGBA color data in bytes
* NOTE: Size is 5x5
*************************************************************/
typedef struct BLFixedTexFont
{
	BLByte data [BL_FIXEDTEX_SIZE_FONT][BL_FIXEDTEX_SIZE_FONT][BL_FIXEDTEX_COLOR_CHANNELS];
} BLFixedTexFont;

/*************************************************************
* NAME: BLFixedTexSmall
* DATE: 2021 - 08 - 27
* MEMBERS:
*	BLByte data [][][] -> Holds RGBA color data in bytes
* NOTE: Size is 8x8
*************************************************************/
typedef struct BLFixedTexSmall
{
	BLByte data[BL_FIXEDTEX_SIZE_SMALL][BL_FIXEDTEX_SIZE_SMALL][BL_FIXEDTEX_COLOR_CHANNELS];
} BLFixedTexSmall;

/*************************************************************
* NAME: BLFixedTexLarge
* DATE: 2021 - 08 - 27
* MEMBERS:
*	BLByte data [][][] -> Holds RGBA color data in bytes
* NOTE: Size is 16x16
*************************************************************/
typedef struct BLFixedTexLarge
{
	BLByte data[BL_FIXEDTEX_SIZE_LARGE][BL_FIXEDTEX_SIZE_LARGE][BL_FIXEDTEX_COLOR_CHANNELS];
} BLFixedTexLarge;

/*************************************************************
* NAME: BLCreateVert2f
* DATE: 2021 - 08 - 27
* PARAMS:
*	float X -> x position
*	float Y -> y position
* RETURNS:
*	BLVert2f created from PARAMS
* NOTE: N/A
*************************************************************/
BLVert2f BLCreateVert2f(float X, float Y);

/*************************************************************
* NAME: BLCreateRect
* DATE: 2021 - 08 - 27
* PARAMS:
*	float X -> x position
*	float Y -> y position
*	float width  -> rect width
*	float height -> rect height
* RETURNS:
*	BLRect created from PARAMS
* NOTE: N/A
*************************************************************/
BLRect BLCreateRect(float X, float Y, float width, float height);

/*************************************************************
* NAME: BLCreateQuad
* DATE: 2021 - 08 - 27
* PARAMS:
*	float X	    -> X position
*	float Y	    -> Y position
*	BLVert2f p0 -> bottom left vertex
*	BLVert2f p1 -> top left vertex
*	BLVert2f p2 -> top right vertex
*	BLVert2f p3 -> bottom right vertex
* RETURNS:
*	BLQuad created from PARAMS
* NOTE: This function is such a pain in the ass
*************************************************************/
BLQuad BLCreateQuad(float X, float Y, BLVert2f p0, BLVert2f p1, BLVert2f p2, BLVert2f p3);

/*************************************************************
* NAME: BLCreateFixedTexFont
* DATE: 2021 - 08 - 27
* PARAMS:
*	BLByte R -> R value
*	BLByte G -> G value
*	BLByte B -> B value
*	BLByte A -> A value
* RETURNS:
*	BLFixedTexFont created from PARAMS
* NOTE: N/A
*************************************************************/
BLFixedTexFont BLCreateFixedTexFont(BLByte R, BLByte G, BLByte B, BLByte A);

/*************************************************************
* NAME: BLCreateFixedTexSmall
* DATE: 2021 - 08 - 27
* PARAMS:
*	BLByte R -> R value
*	BLByte G -> G value
*	BLByte B -> B value
*	BLByte A -> A value
* RETURNS:
*	BLFixedTexSmall created from PARAMS
* NOTE: N/A
*************************************************************/
BLFixedTexSmall BLCreateFixedTexSmall(BLByte R, BLByte G, BLByte B, BLByte A);

/*************************************************************
* NAME: BLCreateFixedTexLarge
* DATE: 2021 - 08 - 27
* PARAMS:
*	BLByte R -> R value
*	BLByte G -> G value
*	BLByte B -> B value
*	BLByte A -> A value
* RETURNS:
*	BLFixedTexLarge created from PARAMS
* NOTE: N/A
*************************************************************/
BLFixedTexLarge BLCreateFixedTexLarge(BLByte R, BLByte G, BLByte B, BLByte A);

/*************************************************************
* NAME: BLCreateTexHandleFixed
* DATE: 2021 - 08 - 28
* PARAMS:
*	void* fixedTexture                -> pointer to fixedTexture struct
*	enum BL_TARGET_FIXEDTEX_TYPE type -> specifies what kind of fixedTexture
* RETURNS:
*	BLTextureHandle generated by openGL (GLuint)
* NOTE: fixedTexture can be freed after use of this function
*************************************************************/
BLTextureHandle BLCreateTexHandleFixed(void* fixedTexture, enum BL_TARGET_FIXEDTEX_TYPE type);

/*************************************************************
* NAME: BLDestroyTexHandle
* DATE: 2021 - 08 - 28
* PARAMS:
*	BLTextureHandle texToFree -> frees texture from GPU (via openGL)
* RETURNS:
*	void
* NOTE: N/A
*************************************************************/
void BLDestroyTexHandle(BLTextureHandle texToFree);

/*************************************************************
* NAME: BLCreateTexHandleFree
* DATE: 2021 - 08 - 28
* PARAMS:
*	void* textureData -> data to send to OpenGL
*	BLUInt texSizeHeight -> height of texture
*	BLUInt texSizeWidth  -> width of texture
* RETURNS:
*	BLTextureHandle generated by openGL (GLuint)
* NOTE: 
*	texture data has to be RGBA with each channel a byte large
*	texture data can be freed after use of this function
*************************************************************/
BLTextureHandle BLCreateTexHandleFree(void* textureData, BLUInt texSizeHeight, BLUInt texSizeWidth);

/*************************************************************
* NAME: BLRenderTextureSquare
* DATE: 2021 - 08 - 28
* PARAMS:
*	BLTextureHandle texHndl -> texture handle
*	float posX  -> X position of texture center
*	float posY  -> Y position of texture center
*	float scale -> scale of texture
*	float angle -> angle of texture (in degrees)
* RETURNS: void
* NOTE: N/A
*************************************************************/
void BLRenderTextureSquare(BLTextureHandle texHndl, float posX, float posY, float scale, float angle);

/*************************************************************
* NAME: BLRenderTextureRect
* DATE: 2021 - 08 - 28
* PARAMS:
*	BLTextureHandle texHndl -> texture handle
*	BLRect texRect -> rectangle which describes the texture's scale in relative to a 1x1 square
*	float scale -> scale of texture
*	float angle -> angle of texture (in degrees around the center)
* RETURNS: void
* NOTE: N/A
*************************************************************/
void BLRenderTextureRect(BLTextureHandle texHndl, BLRect texRect, float scale, float angle);

/*************************************************************
* NAME: BLRenderTextureQuad
* DATE: 2021 - 08 - 28
* PARAMS:
*	BLTextureHandle texHndl -> texture handle
*	BLRect texRect -> quad which describes the worldspace position that the texture
*	is the be drawn (the quad is expected to be normalized)
*	float scale -> scale of texture
*	float angle -> angle of texture (in degrees)
* RETURNS: void
* NOTE: N/A
*************************************************************/
void BLRenderTextureQuad(BLTextureHandle texHndl, BLQuad texQuad, float scale, float angle);

/*************************************************************
* NAME: BLClearBuffers
* DATE: 2021 - 08 - 29
* PARAMS:
*	BLByte R -> clear color R
*	BLByte G -> clear color G
*	BLByte B -> clear color B
*	BLByte A -> clear color A
* RETURNS: void
* NOTE: 
*	Clear depth and color buffer
*************************************************************/
void BLClearBuffers(BLByte R, BLByte G, BLByte B, BLByte A);

#endif