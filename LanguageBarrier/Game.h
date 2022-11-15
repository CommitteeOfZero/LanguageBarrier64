#ifndef __GAME_H__
#define __GAME_H__

#include <cstdint>
#include "LanguageBarrier.h"
#include <d3d11.h>

#ifndef GAME_H_IMPORT
#define GAME_H_IMPORT extern
#endif

#pragma pack(push, 1)
struct mpkObject {
  char field_0;
  char filename[11];
  int fileCount;
  char gap10[919];
  char field_C;
};

struct mgsVFSObject {
  char gap0[8];
  char archiveName[16];
  char gap1[10664];
};

struct mgsFileLoader {
  uint32_t unk01;
  uint32_t unk02;
  uint32_t fileId;
  uint32_t loadMode;
  char fileName[64];
  char gap0[228];
  mgsVFSObject* vfsObject;
};
struct CRIFileInfoData;
struct MgsFileLoader64 {
  void* gap0;
  int byte8;
  int intC;
  unsigned int unsigned_int10;
  uint32_t dword14;
  char fileName[264];
  __int64 int64120;
  uint64_t qword128;
  uint64_t qword130;
  uint8_t byte138;
  uint8_t byte139[7];
  CRIFileInfoData* qword140;
  uint8_t gap148[16];
  uint64_t qword158;
};

struct CHND3D11State {
  D3D_FEATURE_LEVEL d3d_feature_level14;
  uint8_t gap4[12];
  void* ppFactory;
  uint8_t gap18[8];
  IDXGIAdapter* adapter;
  ID3D11Device* pid3d11deviceC;
  ID3D11DeviceContext* pid3d11devicecontext18;
};

struct MgsD3D11State {
  uint8_t gap0[12];
  ID3D11Device* pid3d11deviceC;
  IDXGISwapChain* pidxgiswapchain10;
  D3D_FEATURE_LEVEL d3d_feature_level14;
  ID3D11DeviceContext* pid3d11devicecontext18;
  ID3D11DeviceContext* pid3d11deferredcontext1;
  ID3D11DeviceContext* pid3d11deferredcontext2;
};
extern MgsD3D11State* gameExePMgsD3D11State;
extern CHND3D11State* gameExePChnD3D11State;

struct __declspec(align(4)) SurfaceStructRN {
  uint8_t gap_0[4];
  char field_4;
  uint8_t gap_5;
  uint16_t field_6;
  uint8_t gap_8[2];
  char field_A;
  uint8_t gap_B;
  uint32_t field_C;
  char field_10;
  uint8_t gap_11[3];
  uint32_t field_14;
  signed int field_18;
  uint32_t field_1C;
  char field_20;
  uint8_t gap_21[3];
  signed int field_24;
  signed __int16 field_28;
  uint8_t gap_2A[2];
  signed int field_2C;
  signed int field_30;
  signed int field_34;
  UINT width;
  UINT height;
  int field_40;
  int field_44;
  float field_48;
  float field_4C;
  signed int field_50;
  uint8_t gap_54[80];
  char field_A4;
  uint8_t gap_A5[15];
  ID3D11Texture2D* texPtr[4];
  ID3D11Texture2D* texPtr2[4];
  uint8_t gap_C4[16];
  ID3D11ShaderResourceView* shaderRscView;
  uint32_t field_E8;
  signed int field_EC;
  signed int field_F0;
  uint8_t gap_F4[64];
  uint32_t field_134;
  uint32_t field_138;
  uint32_t field_13C;
};

struct __declspec(align(4)) SurfaceStructRND {
  uint8_t gap_0[4];
  char field_4;
  uint8_t gap_5;
  uint16_t field_6;
  uint8_t gap_8[2];
  char field_A;
  uint8_t gap_B;
  uint32_t field_C;
  char field_10;
  uint8_t gap_11[3];
  uint32_t field_14;
  signed int field_18;
  uint32_t field_1C;
  char field_20;
  uint8_t gap_21[3];
  signed int field_24;
  signed __int16 field_28;
  uint8_t gap_2A[2];
  signed int field_2C;
  signed int width;
  signed int height;
  UINT field_40;
  UINT field_44;
  char gap40[108];
  ID3D11Texture2D* texPtr[4];
  ID3D11ShaderResourceView* shaderRscView2;
  ID3D11ShaderResourceView* shaderRscView;

  ID3D11Texture2D* gap_C4[3];
  uint32_t field_E8;
  signed int field_EC;
  signed int field_F0;
  uint8_t gap_F4[50];
  uint32_t field_134;
  uint32_t field_138;
  uint32_t field_13C;
};

struct __declspec(align(8)) ShaderInfoCHN {
  uint64_t byte0;
  char qword8[16];
  uint64_t qword18;
  uint64_t qword20;
  uint8_t byte28;
  uint8_t byte29[3];
  uint64_t qword2C;
  uint32_t gap34;
  uint64_t qword38;
  uint32_t dword40;
  uint32_t dword44;

  uint64_t qword48;
  uint32_t dword50;
  uint32_t dword54;
  uint64_t qword58;
  uint8_t gap60[4];
  uint32_t dword64;
  uint64_t qword68;
  uint64_t qword70;
  uint8_t gap78[8];
  uint64_t qword80;
  uint64_t qword88;
  uint64_t qword90;
  uint64_t qword98;
  uint64_t qwordA0;
  uint64_t qwordA8;
  uint64_t qwordB0;
  uint64_t qwordB8;
  uint64_t qwordC0;
  ID3D11Resource* shaderPtr;
  uint64_t qwordD0;
  uint64_t qwordD8;
  uint64_t qwordE0;
};


struct CHNSurface {
  uint64_t qword0;
  uint8_t byte8;
  __declspec(align(8)) char char10;
  __declspec(align(16)) uint64_t qword20;
  uint64_t qword28;
  uint8_t gap_30[2];
  uint8_t field_32;
  uint8_t gap_33;
  uint16_t word34;
  uint8_t byte36;
  uint8_t byte37;
  uint8_t byte38;
  uint8_t byte39;
  uint8_t byte3A;
  uint8_t byte3B;
  uint32_t dword3C;
  uint8_t field_40;
  uint8_t field_41;
  uint8_t byte42;
  uint8_t byte43;
  uint32_t field_44;
  uint8_t gap_48[4];
  uint32_t field_4C;
  uint32_t field_50;
  uint8_t gap_54;
  uint8_t field_55;
  uint8_t byte56;
  uint8_t byte57;
  uint32_t field_58;
  uint32_t field_5C;
  uint64_t qword60;
  uint16_t field_68;
  uint16_t field_6A;
  uint16_t field_6C;
  uint16_t field_6E;
  uint16_t field_70;
  uint16_t field_72;
  uint16_t field_74;
  uint16_t field_76;
  uint16_t word78;
  uint8_t gap7A[30];
  uint64_t qword98;
  uint8_t gap_A0[128];
  uint64_t field_120;
  ID3D11Texture2D* texPtr[4];
  ID3D11Texture2D* field_148[2];
  uint64_t field_158;
  uint64_t field_160;
  uint64_t field_168;
  uint64_t field_170;
  uint64_t field_178;
  uint64_t field_180;
  ID3D11ShaderResourceView* shaderRscView[4];
};

#pragma pack(pop)


struct DDSFile;

struct DDSInfo {
  uint32_t field_0;
  uint32_t field_4;
  int field_8;
  uint32_t field_C;
  uint32_t width;
  uint32_t height;
  uint32_t bytesSize;
  uint8_t byte1C;
};
__int64 __fastcall CreateDDSInfoCHN(DDSFile* a1, __int64 a2, DDSInfo* a3);

typedef BOOL(__cdecl* GetFlagProc)(int flagId);
typedef void(__cdecl* SetFlagProc)(int flagId, BOOL value);
typedef BOOL(__cdecl* ChkViewDicProc)(int tipId, int unknown);

struct CVector4;
typedef __int64( __fastcall* DrawSpriteInternal2Proc)(
    __int64 a1, CHNSurface** a2,
                                                   __int64 a3, __int64 a4,
                                                   CVector4* a5, CVector4* a6,
                                                   CVector4* a7, float a8,
                                                   char a9, ShaderInfoCHN* a10,
                                                   unsigned __int16 a11);
struct CVector4 {
  float x, y, z, w;
};



struct  CRIFileInfoData {
  uint8_t gap_0[8];
  char name[10];
  uint8_t gap12[46030];
};

extern CRIFileInfoData* criFileInfo;

extern void* surfaceArray;
struct ShaderInfoCHN;

extern ShaderInfoCHN* pixelShaderArray;
extern ShaderInfoCHN* pixelShaderArray2;

namespace lb {
// DEFAULT VALUES!
LB_GLOBAL uint32_t BGM_CLEAR;
LB_GLOBAL uint8_t MPK_ID_SCRIPT_MPK;
LB_GLOBAL uint8_t MPK_ID_BGM_MPK;
LB_GLOBAL uint8_t AUDIO_PLAYER_ID_BGM1;
LB_GLOBAL uint32_t C0DATA_MOUNT_ID;

GAME_H_IMPORT GetFlagProc gameExeGetFlag;
GAME_H_IMPORT SetFlagProc gameExeSetFlag;
GAME_H_IMPORT ChkViewDicProc gameExeChkViewDic;

GAME_H_IMPORT int* gameExeScrWork;



void gameInit();
void gameLoadTexture(uint16_t textureId, void* buffer, size_t sz);
void __cdecl setAreaParamsHook(int areaId, short params[24]);

mpkObject* gameMountMpk(char const* mountpoint, char const* directory,
                        char const* filename);
void gameSetBgm(uint32_t fileId, bool shouldLoop);
uint32_t gameGetBgm();
bool gameGetBgmShouldLoop();
void gameSetBgmShouldPlay(bool shouldPlay);
bool gameGetBgmShouldPlay();
void gameSetBgmPaused(bool paused);
bool gameGetBgmIsPlaying();

struct SurfaceWrapper {
  static int game;

  static void* ptr(void* surfaceArray, int id) {
    switch (game) {
      case 0: {
        SurfaceStructRN* surfaceArrayRN = (SurfaceStructRN*)surfaceArray;
        return &surfaceArrayRN[id];
      }
        break;
      case 1: {
        SurfaceStructRND* surfaceArrayRND = (SurfaceStructRND*)surfaceArray;
        return &surfaceArrayRND[id];
      }
        break;
      case 2: {
        CHNSurface* surfaceArrayRND = (CHNSurface*)surfaceArray;
        return &surfaceArrayRND[id];

      } break;
    }
  };

  static ID3D11Texture2D* getTexPtr(void* surfaceArray, int id, int subindex) {
  

        switch (game) {
      case 0: {
        SurfaceStructRN* surfaceArrayRN = (SurfaceStructRN*)surfaceArray;
        return surfaceArrayRN[id].texPtr[subindex];
      } break;
      case 1: {
        SurfaceStructRND* surfaceArrayRND = (SurfaceStructRND*)surfaceArray;
        return surfaceArrayRND[id].texPtr[subindex];
      } break;
      case 2: {
        CHNSurface* surfaceArrayRND = (CHNSurface*)surfaceArray;
        return surfaceArrayRND[id].field_148[subindex];

      } break;
    }

  }

  static int width(void* surfaceArray, int id) {
    if (!game) {
      SurfaceStructRN* surfaceArrayRN = (SurfaceStructRN*)surfaceArray;
      return surfaceArrayRN[id].width;
    } else {
      SurfaceStructRND* surfaceArrayRND = (SurfaceStructRND*)surfaceArray;
      return surfaceArrayRND[id].width;
    }
  }

  static void setHeight(void* surfaceArray, int id, int height) {
    switch (game) {
      case 0: {
        SurfaceStructRN* surfaceArrayRN = (SurfaceStructRN*)surfaceArray;
        surfaceArrayRN[id].height = height;
      } break;
      case 1: {
        SurfaceStructRND* surfaceArrayRND = (SurfaceStructRND*)surfaceArray;
        surfaceArrayRND[id].height = height;
      } break;
      case 2: {
        CHNSurface* surfaceArrayRND = (CHNSurface*)surfaceArray;
        surfaceArrayRND[id].field_6A = height;
        surfaceArrayRND[id].field_74 = height;
        surfaceArrayRND[id].word78 = height;

      } break;
    }
  }

  static void setWidth(void* surfaceArray, int id, int width) {
    switch (game) {
      case 0: {
        SurfaceStructRN* surfaceArrayRN = (SurfaceStructRN*)surfaceArray;
        surfaceArrayRN[id].width = width;
      } break;
      case 1: {
        SurfaceStructRND* surfaceArrayRND = (SurfaceStructRND*)surfaceArray;
        surfaceArrayRND[id].width = width;
      } break;
      case 2: {
        CHNSurface* surfaceArrayRND = (CHNSurface*)surfaceArray;
        surfaceArrayRND[id].field_68 = width;
        surfaceArrayRND[id].field_72 = width;

      } break;
    }
  }
  static void setField_40(void* surfaceArray, int id, int field_40) {
    switch (game) {
      case 0: {
        SurfaceStructRN* surfaceArrayRN = (SurfaceStructRN*)surfaceArray;
        surfaceArrayRN[id].field_40 = field_40;
      } break;
      case 1: {
        SurfaceStructRND* surfaceArrayRND = (SurfaceStructRND*)surfaceArray;
        surfaceArrayRND[id].field_40 = field_40;
      } break;
      case 2: {
        CHNSurface* surfaceArrayRND = (CHNSurface*)surfaceArray;
        surfaceArrayRND[id].field_6C = field_40;
        surfaceArrayRND[id].field_72 = field_40;
        surfaceArrayRND[id].field_76 = field_40;


      } break;
    }

  }
  static void setField_44(void* surfaceArray, int id, int field_44) {
    switch (game) {
      case 0: {
        SurfaceStructRN* surfaceArrayRN = (SurfaceStructRN*)surfaceArray;
        surfaceArrayRN[id].field_44 = field_44;
      } break;
      case 1: {
        SurfaceStructRND* surfaceArrayRND = (SurfaceStructRND*)surfaceArray;
        surfaceArrayRND[id].field_44 = field_44;
      } break;
      case 2: {
        CHNSurface* surfaceArrayRND = (CHNSurface*)surfaceArray;
        surfaceArrayRND[id].field_6E = field_44;

      } break;
    }

  }
  static void setShaderRscView(void* surfaceArray, int id,
                               ID3D11ShaderResourceView* rscView) {
    switch (game) {
      case 0: {
        SurfaceStructRN* surfaceArrayRN = (SurfaceStructRN*)surfaceArray;
        surfaceArrayRN[id].shaderRscView = rscView;
      } break;
      case 1: {
        SurfaceStructRND* surfaceArrayRND = (SurfaceStructRND*)surfaceArray;
        surfaceArrayRND[id].shaderRscView = rscView;
      } break;
      case 2: {
        CHNSurface* surfaceArrayRND = (CHNSurface*)surfaceArray;
        surfaceArrayRND[id].shaderRscView[0] = rscView;

      } break;
    }
  }
  static void setTexPtr(void* surfaceArray, int id, int subIndex,
                        ID3D11Texture2D* texPtr) {
    switch (game) {
      case 0: {
        SurfaceStructRN* surfaceArrayRN = (SurfaceStructRN*)surfaceArray;
        surfaceArrayRN[id].texPtr[subIndex] = texPtr;
      } break;
      case 1: {
        SurfaceStructRND* surfaceArrayRND = (SurfaceStructRND*)surfaceArray;
        surfaceArrayRND[id].texPtr[subIndex] = texPtr;
      } break;
      case 2: {
        CHNSurface* surfaceArrayRND = (CHNSurface*)surfaceArray;
        surfaceArrayRND[id].texPtr[subIndex] = texPtr;

      } break;
    }
  }
  static int height(void* surfaceArray, int id) {
    if (!game) {
      SurfaceStructRN* surfaceArrayRN = (SurfaceStructRN*)surfaceArray;
      return surfaceArrayRN[id].height;
    } else {
      SurfaceStructRND* surfaceArrayRND = (SurfaceStructRND*)surfaceArray;
      return surfaceArrayRND[id].height;
    }
  }
};
}  // namespace lb

#endif  // !__GAME_H__
