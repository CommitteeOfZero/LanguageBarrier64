#include "GameText.h"
#include <fstream>
#include <list>
#include <sstream>
#include <vector>
#include <intrin.h>
#include "Config.h"
#include "Game.h"
#include "LanguageBarrier.h"
#include "Script.h"
#include "SigScan.h"
#include "TextRendering.h"
#include <string_view>
#include <string>

namespace lb
{

struct CHNDialoguePage_t {
  int field_0;
  int field_4;
  int drawNextPageNow;
  int pageLength;
  int field_10;
  char field_14;
  char field_15;
  char field_16;
  char field_17;
  int field_18;
  int field_1C;
  int field_20;
  int field_24;
  int field_28;
  int field_2C;
  int field_30;
  int field_34;
  int field_38;
  int field_40;
  int field_44;
  int fontNumber[2400];
  int charColor[2400];
  int charOutlineColor[2400];
  char glyphCol[2400];
  char glyphRow[2400];
  char glyphOrigWidth[2400];
  char glyphOrigHeight[2400];
  __int16 charDisplayX[2400];
  __int16 charDisplayY[2400];
  __int16 glyphDisplayWidth[2400];
  __int16 glyphDisplayHeight[2400];
  char field_BBBC[2400];
  int field_C38C[2400];
  char charDisplayOpacity[2400];
};
 CHNDialoguePage_t* gameExeDialoguePages_CHNDialoguePage_t = NULL;

void __cdecl chnDrawDialogueHook(int fontNumber, int pageNumber,
                                 uint32_t opacity, int xOffset, int yOffset) {
  CHNDialoguePage_t* page = &gameExeDialoguePages_CHNDialoguePage_t[pageNumber];
 
  bool newline = true;
  float displayStartX = (page->charDisplayX[0] + xOffset) * lb::COORDS_MULTIPLIER;
  float displayStartY = (page->charDisplayY[0] + yOffset) * lb::COORDS_MULTIPLIER;
  int firstCharacter = 0;
  auto  meow =  0x11984i64 * pageNumber;
  for (int i = 0; i < page->pageLength; i++) {
    if (fontNumber == page->fontNumber[i]) {
      int glyphSize = page->glyphDisplayHeight[i];
      if (i == 0 ||
          i > 0 && (page->charDisplayY[i] - page->charDisplayY[i - 1]) >
                       page->glyphDisplayHeight[i]) {
        newline = true;
        firstCharacter = i;
      } else
        newline = false;
      if (newline == false) {
        __int16 fontSize = page->glyphDisplayHeight[i] * 1.5f;
        uint32_t currentChar =
            page->glyphCol[i - 1] +
            page->glyphRow[i - 1] * TextRendering::Get().GLYPHS_PER_ROW;
        auto glyphInfo = TextRendering::Get()
                             .getFont(fontSize, false)
                             ->getGlyphInfo(currentChar, Regular);
        displayStartX += glyphInfo->advance;
      } else {
        displayStartX = (page->charDisplayX[i] + xOffset) * lb::COORDS_MULTIPLIER;
      }
      uint32_t _opacity = (page->charDisplayOpacity[i] * opacity) >> 8;
      if (page->charOutlineColor[i] != -1) {
        {
          uint32_t currentChar =
              page->glyphCol[i] +
              page->glyphRow[i] * TextRendering::Get().GLYPHS_PER_ROW;
          wchar_t cChar = TextRendering::Get().fullCharMap[currentChar];
          const auto glyphInfo =
              TextRendering::Get()
                  .getFont(page->glyphDisplayHeight[i] * 1.5f, false)
                  ->getGlyphInfo(currentChar, FontType::Regular);
          displayStartY = (page->charDisplayY[firstCharacter] + yOffset) * 1.5f;
          __int16 fontSize = page->glyphDisplayHeight[i] * 1.5f;
          float yOffset = -6.0f * fontSize / 48.0f;
          TextRendering::Get().replaceFontSurface(fontSize);
          if (glyphInfo->width && glyphInfo->rows)
            lb::drawSpriteCHNHook(
                TextRendering::Get().FONT_TEXTURE_ID, glyphInfo->x,
                glyphInfo->y, glyphInfo->width, glyphInfo->rows,
                round(displayStartX + glyphInfo->left+1.5),
                round(yOffset + displayStartY + fontSize - glyphInfo->top+1.5),
                page->charOutlineColor[i], _opacity);
        }
      }
      {
        auto glyphsPerRow = TextRendering::Get().GLYPHS_PER_ROW;
        uint32_t currentChar =
            page->glyphCol[i] + page->glyphRow[i] * glyphsPerRow;
        auto glyphInfo = TextRendering::Get()
                             .getFont(page->glyphDisplayHeight[i] * 1.5f, false)
                             ->getGlyphInfo(currentChar, FontType::Regular);
        displayStartY = (page->charDisplayY[firstCharacter] + yOffset) * 1.5f;
        float xRatio = ((float)page->glyphDisplayWidth[i] /
                        (float)page->glyphOrigWidth[i]);
        TextRendering::Get().replaceFontSurface(page->glyphDisplayHeight[i] *
                                                1.5);
        __int16 fontSize = page->glyphDisplayHeight[i] * 1.5f;
        float yOffset = -6.0f * fontSize / 48.0f;
        if (glyphInfo->width && glyphInfo->rows)
          drawSpriteCHNHook(
              TextRendering::Get().FONT_TEXTURE_ID, glyphInfo->x, glyphInfo->y,
              glyphInfo->width, glyphInfo->rows,
              round(displayStartX + glyphInfo->left),
              round(yOffset + displayStartY + fontSize - glyphInfo->top),
              page->charColor[i], _opacity);
        page->field_20 = (displayStartX + glyphInfo->advance) / 1.5f;
      }
    }
  }
};

}  // namespace lb