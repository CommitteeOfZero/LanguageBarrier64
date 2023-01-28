#ifndef __GAMETEXT_H__
#define __GAMETEXT_H__

#include <cstdint>
#include "LanguageBarrier.h"
#include <xmmintrin.h>
#ifndef GAMETEXT_H_IMPORT
#define GAMETEXT_H_IMPORT extern
#endif


struct CHNSurface;
struct CVector4;
struct ShaderInfoCHN;


namespace lb {
LB_GLOBAL uint8_t FIRST_FONT_ID;
LB_GLOBAL float COORDS_MULTIPLIER;
LB_GLOBAL uint8_t FONT_CELL_WIDTH;
LB_GLOBAL uint8_t FONT_CELL_HEIGHT;
LB_GLOBAL uint8_t FONT_ROW_LENGTH;
static const uint16_t TOTAL_NUM_FONT_CELLS = 8000;
LB_GLOBAL uint16_t GLYPH_RANGE_FULLWIDTH_START;
// TODO: make this JSON-configurable in some manner
static const uint16_t MAX_PROCESSED_STRING_LENGTH = 2000;
LB_GLOBAL uint16_t DEFAULT_LINE_LENGTH;
LB_GLOBAL uint16_t DEFAULT_MAX_CHARACTERS;
LB_GLOBAL float SGHD_LINK_UNDERLINE_GLYPH_X;
LB_GLOBAL float SGHD_LINK_UNDERLINE_GLYPH_Y;
// Careful: this also messes with the speaker markers (for spoken lines) and
// highlight in the backlog
// Taken care of with ccBacklogNamePosAdjustHook
LB_GLOBAL int DIALOGUE_REDESIGN_YOFFSET_SHIFT;
LB_GLOBAL int DIALOGUE_REDESIGN_LINEHEIGHT_SHIFT;
LB_GLOBAL bool HAS_BACKLOG_UNDERLINE;
LB_GLOBAL int8_t BACKLOG_HIGHLIGHT_DEFAULT_HEIGHT;
LB_GLOBAL int8_t BACKLOG_HIGHLIGHT_HEIGHT_SHIFT;
LB_GLOBAL float OUTLINE_PADDING;
LB_GLOBAL uint8_t OUTLINE_CELL_WIDTH;
LB_GLOBAL uint8_t OUTLINE_CELL_HEIGHT;
// arbitrarily chosen; I hope the game doesn't try to use this
LB_GLOBAL uint16_t OUTLINE_TEXTURE_ID;
static const int LINECOUNT_DISABLE_OR_ERROR = 0xFF;
static const uint8_t NOT_A_LINK = 0xFF;
LB_GLOBAL int SGHD_PHONE_X_PADDING;
LB_GLOBAL uint16_t GLYPH_ID_FULLWIDTH_SPACE;
LB_GLOBAL uint16_t GLYPH_ID_HALFWIDTH_SPACE;
LB_GLOBAL bool HAS_DOUBLE_GET_SC3_STRING_DISPLAY_WIDTH;
LB_GLOBAL bool HAS_DRAW_PHONE_TEXT;
LB_GLOBAL bool HAS_SGHD_PHONE;
LB_GLOBAL bool HAS_GET_SC3_STRING_LINE_COUNT;
LB_GLOBAL bool HAS_RINE;
LB_GLOBAL bool RINE_BLACK_NAMES;
LB_GLOBAL bool NEEDS_CLEARLIST_TEXT_POSITION_ADJUST;
LB_GLOBAL bool NEEDS_CC_BACKLOG_NAME_POS_ADJUST;
LB_GLOBAL bool IMPROVE_DIALOGUE_OUTLINES;
LB_GLOBAL bool HAS_SPLIT_FONT;
LB_GLOBAL bool TIP_REIMPL;
LB_GLOBAL int TIP_REIMPL_GLYPH_SIZE;
LB_GLOBAL int TIP_REIMPL_LINE_LENGTH;
LB_GLOBAL bool CC_BACKLOG_HIGHLIGHT;
LB_GLOBAL float CC_BACKLOG_HIGHLIGHT_SPRITE_Y;
LB_GLOBAL float CC_BACKLOG_HIGHLIGHT_SPRITE_HEIGHT;
LB_GLOBAL float CC_BACKLOG_HIGHLIGHT_HEIGHT_SHIFT;
LB_GLOBAL float CC_BACKLOG_HIGHLIGHT_YOFFSET_SHIFT;

GAMETEXT_H_IMPORT int* BacklogLineSave;
GAMETEXT_H_IMPORT int* BacklogDispLinePos;
GAMETEXT_H_IMPORT int* BacklogLineBufSize;
GAMETEXT_H_IMPORT int16_t* BacklogTextPos;
GAMETEXT_H_IMPORT int* BacklogLineBufUse;
GAMETEXT_H_IMPORT uint16_t* BacklogText;
GAMETEXT_H_IMPORT int* BacklogDispCurPosSX;
GAMETEXT_H_IMPORT int* BacklogDispCurPosEY;
GAMETEXT_H_IMPORT int* BacklogLineBufStartp;
GAMETEXT_H_IMPORT unsigned char* BacklogTextSize;
GAMETEXT_H_IMPORT int* BacklogLineBufEndp;
GAMETEXT_H_IMPORT int* BacklogBufStartp;
GAMETEXT_H_IMPORT int* MesFontColor;
GAMETEXT_H_IMPORT int* BacklogBufUse;
GAMETEXT_H_IMPORT int* BacklogDispCurPosEX;
GAMETEXT_H_IMPORT int* BacklogDispLineSize;
GAMETEXT_H_IMPORT int* BacklogDispPos;
GAMETEXT_H_IMPORT int* dword_948628;
GAMETEXT_H_IMPORT uint8_t* BacklogTextCo;
GAMETEXT_H_IMPORT int* BacklogLineVoice;
GAMETEXT_H_IMPORT int* BacklogDispLinePosY;
GAMETEXT_H_IMPORT int* BacklogDispCurPosSY;
GAMETEXT_H_IMPORT int* BacklogDispCurPosSY;

struct CHNDialoguePage_t;

extern  CHNDialoguePage_t* gameExeDialoguePages_CHNDialoguePage_t;

void gameTextInit();
void fixSkipRN();
void fixLeadingZeroes();
int __cdecl getSc3StringDisplayWidthHook(char* sc3string,
                                         unsigned int maxCharacters,
                                         int baseGlyphSize);
int __cdecl drawSpriteHook(int textureId, float spriteX, float spriteY,
                           float spriteWidth, float spriteHeight,
                           float displayX, float displayY, int color,
                           int opacity, int shaderId);

int __cdecl drawSpriteCHNHook(int textureId, float spriteX, float spriteY,
                           float spriteWidth, float spriteHeight,
                           float displayX, float displayY, int color,
                           int opacity);
void __fastcall sub_140045C30(__int64 a1, float a2, float a3, float a4,
                                char* a5, unsigned int a6, unsigned int a7,
                                float a8, float a9, unsigned int a11);

__int64 __fastcall drawSpriteMaskCHNHook(__int64 a1, __int64 a2, float a3,
                                         float a4, float a5, float a6, float a7,
                                         float a8, float a9, float a10, float a11,
                                         float a12, int a13, int a14);

__int64 __fastcall drawSpriteMask2CHNHook(__int64 a1, __int64 a2, float a3,
                                          float a4, float a5, float a6,
                                          float a7, float a8, float a9,
                                          float a10, int a11, float a12,
                                          int a13, int a14, int a15, int a16);

void drawSpriteMaskCHNInternalHook(__int64 a1, CHNSurface** a2, __int64 a3,
                                   int a4, CVector4* a5, CVector4* a6,
                                   CVector4* a7, float a8, char a9,
                                   ShaderInfoCHN* a10, __int16 a11);
void __fastcall sub_1400443B0(__int64 a1, __int64 a2, __int64 a3, int a4,
                                 int a5, int a6, int a7);

__int64 __fastcall ChatLayout(unsigned int a1, char* a2, unsigned int a3);
__int64 __fastcall ChatLayout2(char* a2, unsigned int a1, unsigned int a3);
}  // namespace lb


extern "C" {
inline uint8_t widths[lb::TOTAL_NUM_FONT_CELLS];
inline uintptr_t gameExeDialogueLayoutWidthLookup1Return;
inline uintptr_t gameExeDialogueLayoutWidthLookup2Return;
inline uintptr_t gameExeDialogueLayoutWidthLookup3Return;
inline uintptr_t gameExeDialogueLayoutWidthLookup4Return;
inline uintptr_t gameExeLineHeight;
inline int gameExeTipContentHeight;
inline uintptr_t gameExeSetTipContentHeightReturn;
inline uintptr_t gameExeSetTipContentHeight2Return;
inline uintptr_t gameExeSkipCHN;
inline uintptr_t gameExeSkipCHNOffset;
inline uintptr_t gameExeSetTipCountReturn;
inline uintptr_t gameExeSetTipCountReturn2;
inline uintptr_t gameExeSetTipCountReturn3;
inline uintptr_t BlueSkyPromptFixReturn;
inline uintptr_t gameExeRsi;

}

#endif  // !__GAMETEXT_H__
