#include "CriManaMod.h"
#include <csri/csri.h>
#include <stb_vorbis.h>
#include <emmintrin.h>
#include <fstream>
#include <unordered_map>
#include "Config.h"
#include "Game.h"
#include "LanguageBarrier.h"
#include "SigScan.h"
#include "DirectXTex.h"
#include "directxtk/SpriteBatch.h"
#include "ass/ass.h"
#include "directxtk/CommonStates.h"
#define FLOATING_POINT
#define OUTSIDE_SPEEX
#define RANDOM_PREFIX lb_speexdsp_
#include <d3d11_1.h>

#include "contrib/speexdsp/speex_resampler.h"
#include "GameText.h"

typedef struct {
  uint8_t* imageptr;
  uint32_t bufsize;
  uint32_t line_pitch;
  uint32_t line_size;
  uint32_t num_lines;
} CriManaImageBufferInfo;

typedef struct {
  int32_t frame_no;
  int32_t frame_no_per_file;
  uint32_t width;
  uint32_t height;
  uint32_t disp_width;
  uint32_t disp_height;
  uint32_t framerate;
  uint32_t framerate_n;
  uint32_t framerate_d;
  uint32_t total_frames_per_file;
  uint64_t time;
  uint64_t time_per_file;
  uint64_t tunit;
  uint32_t cnt_concatenated_movie;
  int32_t num_images;
  CriManaImageBufferInfo image_info[4];
  int32_t csc_flag;
  uint32_t alpha_type;
  uint32_t ref_result;
  void* details_ptr[2];
  uint32_t color_conv;
  uint32_t cnt_skipped_frames;
  uint32_t reserved[1];
} CriManaFrameInfo;

typedef struct {
  signed int field_0;
  char gap_4[4];
  char initialized;
  char gap_9[2];
  char field_B;
  unsigned __int8 pauseFlag;
  char gap_D[5];
  unsigned __int8 loopFlag;
  __declspec(align(2)) char gap_14[4];
  float volume;
  char gap_1C[16];
  int field_2C;
  int field_30;
  char gap_34[4];
  int field_38;
  int field_3C;
  int field_40;
  int field_44;
  char gap_48[40];
  int movieIdInCpk;
  char gap_74[4];
  char moviePath[256];
  void* movieDataPtr;
  char gap_17C[4];
  int movieDataSize;
  char gap_184[24];
  mgsVFSObject* mgsFilePtr;
  char gap_1A0[2728];
  int field_C48;
  char gap_C4C[4];
  int field_C50;
  char gap_C54[124];
  int field_CD0;
  void* criManaPlayer;
  int criManaPlayerStatus;
  char gap_CDC[4];
  CriManaFrameInfo criManaFrameInfo;
  char gap_D9C[3020];
} MgsMoviePlayerObj_t;

// partial
typedef struct {
  char gap0[8];
  char byte8;
  char gap9[2];
  char byteB;
  char gapC[12];
  uint32_t dword18;
  char gap1C[3118];
  uint16_t unsigned___int16C4A;
  char gapC4C[124];
  uint32_t dwordCC8;
  uint32_t dwordCCC;
  char gapCD0[8];
  CriManaFrameInfo criManaFrameInfo;
} MgsMoviePlayerRNDObj_t;

struct __declspec(align(8)) mgsMoviePlayerObjCHN {
  uint8_t gap_0[8];
  char byte_8;
  uint8_t gap_9;
  char byte_a;
  char byte_b;
  uint8_t gap_C;
  char byte_d;
  char byte_e;
  char byte_f;
  char byte_10;
  uint8_t gap_11[3];
  uint8_t byte_14;
  uint8_t byte_15;
  char byte_16;
  uint8_t gap_17[5];
  __int16 word_1c;
  uint8_t gap_1E[2];
  uint16_t word_20;
  uint8_t gap_22[6];
  int dword_28;
  int dword_2c;
  __int64 dqword_30;
  __int64 dqword_38;
  __int64 qword_40;
  uint64_t qword_48;
  __int64 qword_50;
  uint8_t gap_58[3210];
  __int16 word_ce2;
  uint16_t word_ce4;
  uint16_t word_ce6;
  uint8_t gap_CE8[136];
  __int64 qword_d70;
  uint8_t gap_D78[88];
  uint32_t dword_dd0;
  uint8_t gap_DD4[4];
  uint64_t qword_dd8;
  int dword_de0;
  uint8_t gap_DE4[4];
  CriManaFrameInfo criManaFrameInfo;
  uint8_t gapEB8[8];
  __int64 qword_ec0;
  uint8_t gap_EC8[52];
  uint32_t dword_efc;
  int dword_f00;
  char gap_f04[852];
};

struct CriManaModState_t {
  uint32_t lastFrameNum = 0;
  bool keepLastFrame = false;
  double time = 0;
  bool copy = false;
  ID3D11Texture2D* stagingTexture = NULL;
  ID3D11Texture2D* subsTexture = NULL;
  ID3D11ShaderResourceView* subRscView = nullptr;
  csri_inst* csri = NULL;
};

static std::unordered_map<void*, CriManaModState_t*> stateMap;
std::shared_ptr<CriManaModState_t> state = nullptr;

uint32_t RENDER_TARGET_SURF_ID = 203;

typedef int(__thiscall* MgsMovieCPlayerPlayProc)(void* pThis, int a2, int a3,
                                                 char* movieFileName);
static MgsMovieCPlayerPlayProc gameExeMgsMovieCPlayerPlay = NULL;
static MgsMovieCPlayerPlayProc gameExeMgsMovieCPlayerPlayReal = NULL;

typedef int(__thiscall* MgsMovieCPlayerPlayByIdProc)(void* pThis, int a1,
                                                     int id, int a3);
static MgsMovieCPlayerPlayByIdProc gameExeMgsMovieCPlayerPlayById = NULL;
static MgsMovieCPlayerPlayByIdProc gameExeMgsMovieCPlayerPlayByIdReal = NULL;

typedef int(__thiscall* MgsMovieCPlayerStopProc)(void* pThis);
static MgsMovieCPlayerStopProc gameExeMgsMovieCPlayerStop = NULL;
static MgsMovieCPlayerStopProc gameExeMgsMovieCPlayerStopReal = NULL;

typedef int(__thiscall* MgsMovieCPlayerRenderProc)(void* pThis);
static MgsMovieCPlayerRenderProc gameExeMgsMovieCPlayerRender = NULL;
static MgsMovieCPlayerRenderProc gameExeMgsMovieCPlayerRenderReal = NULL;

typedef int(__cdecl* DrawMovieFrameProc)(int tint, int opacity);
static DrawMovieFrameProc gameExeDrawMovieFrame = NULL;
static DrawMovieFrameProc gameExeDrawMovieFrameReal = NULL;

typedef int(__cdecl* DrawMovieFrameRNDProc)(int unk1, int tint, int opacity);
static DrawMovieFrameRNDProc gameExeDrawMovieFrameRND = NULL;
static DrawMovieFrameRNDProc gameExeDrawMovieFrameRNDReal = NULL;

int VideoPlayerObjVariant = 0;

namespace lb {
int __fastcall mgsMovieCPlayerPlayHook(void* pThis, void* dummy, int a2, int a3,
                                       char* movieFileName);
int __fastcall mgsMovieCPlayerPlayByIdHook(void* pThis, void* dummy, int a2,
                                           int id);
int __fastcall mgsMovieCPlayerStopHook(void* pThis);
int __fastcall mgsMovieCPlayerRenderHook(void* pThis);
int __cdecl drawMovieFrameHook(int tint, int opacity);
int __cdecl drawMovieFrameHookRND(int unk1, int tint, int opacity);

bool criManaModInit() {
  if (config["patch"].count("fmv") != 1) {
    LanguageBarrierLog(
        "No FMV mods in patch configuration, not hooking CriMana...");
    return true;
  }

  if (true) {
    VideoPlayerObjVariant = 1;

    if (!scanCreateEnableHook("game", "mgsMovieCPlayerPlayById",
                              (uintptr_t*)&gameExeMgsMovieCPlayerPlayById,
                              (LPVOID)&mgsMovieCPlayerPlayByIdHook,
                              (LPVOID*)&gameExeMgsMovieCPlayerPlayByIdReal) ||
        !scanCreateEnableHook("game", "drawMovieFrame",
                              (uintptr_t*)&gameExeDrawMovieFrameRND,
                              (LPVOID)&drawMovieFrameHookRND,
                              (LPVOID*)&gameExeDrawMovieFrameRNDReal))
      return false;
  } else {
    if (!scanCreateEnableHook("game", "mgsMovieCPlayerPlay",
                              (uintptr_t*)&gameExeMgsMovieCPlayerPlay,
                              (LPVOID)&mgsMovieCPlayerPlayHook,
                              (LPVOID*)&gameExeMgsMovieCPlayerPlayReal) ||
        !scanCreateEnableHook(
            "game", "drawMovieFrame", (uintptr_t*)&gameExeDrawMovieFrame,
            (LPVOID)&drawMovieFrameHook, (LPVOID*)&gameExeDrawMovieFrameReal))
      return false;
  }

  if (!scanCreateEnableHook("game", "mgsMovieCPlayerStop",
                            (uintptr_t*)&gameExeMgsMovieCPlayerStop,
                            (LPVOID)&mgsMovieCPlayerStopHook,
                            (LPVOID*)&gameExeMgsMovieCPlayerStopReal) ||
      !scanCreateEnableHook("game", "mgsMovieCPlayerRender",
                            (uintptr_t*)&gameExeMgsMovieCPlayerRender,
                            (LPVOID)&mgsMovieCPlayerRenderHook,
                            (LPVOID*)&gameExeMgsMovieCPlayerRenderReal))
    return false;

  if (config["patch"]["fmv"].count("fonts") == 1) {
    for (auto font : config["patch"]["fmv"]["fonts"]) {
      std::stringstream ss;
      ss << "languagebarrier\\subs\\fonts\\" << font.get<std::string>();
      std::string path = ss.str();
      AddFontResourceExA(path.c_str(), FR_PRIVATE, NULL);
    }
  }

  return true;
}

static __m128i MaskFF000000 = _mm_set1_epi32(0xFFFFFF00);

void drawSubs(bool deferred) {
  if (!state->keepLastFrame) {
    ID3D11DeviceContext* test = gameExePChnD3D11State->pid3d11devicecontext18;
    if (deferred) {
      ID3D11CommandList* pCommandList;
      test = (gameExePChnD3D11State->pid3d11devicecontext20)[*(
          uint32_t*)gameExeD3D11DeferredContextIndex];

      test->CopyResource(state->stagingTexture,
                         lb::SurfaceWrapper::getTexPtr(
                             surfaceArray, RENDER_TARGET_SURF_ID, 0));

      D3D11_MAPPED_SUBRESOURCE rsc;
      memset(&rsc, 0, sizeof(D3D11_MAPPED_SUBRESOURCE));
      HRESULT hr = gameExePChnD3D11State->pid3d11devicecontext18->Map(
          state->stagingTexture, 0, D3D11_MAP_READ_WRITE, 0, &rsc);

      uint8_t* imagePtr = (uint8_t*)rsc.pData;
      csri_frame frame;
      frame.planes[0] = imagePtr;
      frame.strides[0] = rsc.RowPitch;
      frame.pixfmt = CSRI_F_RGB_;
      csri_fmt format = {
          frame.pixfmt,
          lb::SurfaceWrapper::width(surfaceArray, RENDER_TARGET_SURF_ID),
          lb::SurfaceWrapper::height(surfaceArray, RENDER_TARGET_SURF_ID)};

      if (csri_request_fmt(state->csri, &format) == 0) {
        csri_render(state->csri, &frame, state->time);
      }

      auto m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(test);
      
      gameExePChnD3D11State->pid3d11devicecontext18->Unmap(
          state->stagingTexture, 0);
      gameExePChnD3D11State->pid3d11devicecontext18->CopyResource(
          state->subsTexture, state->stagingTexture);

      ID3D11RasterizerState* rsState;

      SurfaceWrapper::setTexPtr(surfaceArray, 401, 0, state->subsTexture);
      SurfaceWrapper::setShaderRscView(surfaceArray, 401,state->subRscView);
      SurfaceWrapper::setField_40(surfaceArray, 401, 1920);
      SurfaceWrapper::setField_44(surfaceArray, 401, 1080);
      SurfaceWrapper::setWidth(surfaceArray, 401, 1920);
      SurfaceWrapper::setHeight(surfaceArray, 401, 1080);
      SurfaceWrapper::setEnabled(surfaceArray, 401, 1);


      lb::drawSpriteCHNHook(401, 0, 0, 1920, 1080, 0, 0,
                            16777215, 256);


    }
  }
}

int __cdecl drawMovieFrameHookRND(int unk1, int tint, int opacity) {
  int ret = gameExeDrawMovieFrameRNDReal(unk1, tint, opacity);
  if(state!=nullptr)drawSubs(true);
  return ret;
}

int __cdecl drawMovieFrameHook(int tint, int opacity) {
  int ret = gameExeDrawMovieFrameReal(tint, opacity);
  drawSubs(false);
  return ret;
}

int __fastcall mgsMovieCPlayerPlayByIdHook(void* pThis, void* a1, int id,
                                           int a3) {
  std::string subFileName;

  char name[256];


  std::string movieFileName = std::to_string(id);
  // note: case sensitive
  if (config["patch"]["fmv"].count("subs") == 1 &&
      config["patch"]["fmv"]["subs"].count(movieFileName) == 1)
    subFileName =
        config["patch"]["fmv"]["subs"][movieFileName].get<std::string>();

  if (!subFileName.empty() && *gameExeCurrentLanguage == 1) {
    std::stringstream ssSubPath;
    ssSubPath << "languagebarrier\\subs\\" << subFileName;
    std::string subPath = ssSubPath.str();
    std::stringstream logstr;
    logstr << "Using sub track " << subPath << " if available.";
    LanguageBarrierLog(logstr.str());

    std::ifstream in(subPath, std::ios::in | std::ios::binary);
    if (in.good()) {
      in.seekg(0, std::ios::end);
      std::string sub(in.tellg(), 0);
      in.seekg(0, std::ios::beg);
      in.read(&sub[0], sub.size());

      if (state != nullptr) {
        if (state->csri) {
          csri_close(state->csri);
        }
        if (state->stagingTexture) {
          state->stagingTexture->Release();
        }
        if (state->subsTexture) {
          state->subsTexture->Release();
        }
      }

      state = std::make_shared<CriManaModState_t>();

      D3D11_TEXTURE2D_DESC desc;
      memset(&desc, 0, sizeof(D3D11_TEXTURE2D_DESC));
      lb::SurfaceWrapper::getTexPtr(surfaceArray, RENDER_TARGET_SURF_ID, 0)
          ->GetDesc(&desc);
      desc.Usage = D3D11_USAGE_STAGING;
      desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
      desc.BindFlags = 0;

      gameExePChnD3D11State->pid3d11deviceC->CreateTexture2D(
          &desc, 0, &state->stagingTexture);

      desc.Usage = D3D11_USAGE_DYNAMIC;
      desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
      desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

      gameExePChnD3D11State->pid3d11deviceC->CreateTexture2D(
          &desc, 0, &state->subsTexture);

      D3D11_SHADER_RESOURCE_VIEW_DESC rsc;
      lb::SurfaceWrapper::getResourceView(surfaceArray, RENDER_TARGET_SURF_ID,
                                          0)
          ->GetDesc(&rsc);
      gameExePChnD3D11State->pid3d11deviceC->CreateShaderResourceView(
          state->subsTexture, &rsc, &state->subRscView);
      state->csri =
          csri_open_mem(csri_renderer_default(), &sub[0], sub.size(), NULL);
    }
    in.close();
  } else
    state = nullptr;
  return gameExeMgsMovieCPlayerPlayByIdReal(pThis, (int)a1, id, a3);
}

int __fastcall mgsMovieCPlayerPlayHook(void* pThis, void* dummy, int a2, int a3,
                                       char* movieFileName) {
  std::string subFileName;

  // note: case sensitive
  if (config["patch"]["fmv"].count("subs") == 1 &&
      config["patch"]["fmv"]["subs"].count(movieFileName) == 1)
    subFileName =
        config["patch"]["fmv"]["subs"][movieFileName].get<std::string>();

  if (!subFileName.empty() && *gameExeCurrentLanguage == 1) {
    std::stringstream ssSubPath;
    ssSubPath << "languagebarrier\\subs\\" << subFileName;
    std::string subPath = ssSubPath.str();
    std::stringstream logstr;
    logstr << "Using sub track " << subPath << " if available.";
    LanguageBarrierLog(logstr.str());

    std::ifstream in(subPath, std::ios::in | std::ios::binary);
    if (in.good()) {
      in.seekg(0, std::ios::end);
      std::string sub(in.tellg(), 0);
      in.seekg(0, std::ios::beg);
      in.read(&sub[0], sub.size());
      state = std::make_shared<CriManaModState_t>();
      D3D11_TEXTURE2D_DESC desc;
      memset(&desc, 0, sizeof(D3D11_TEXTURE2D_DESC));
      lb::SurfaceWrapper::getTexPtr(surfaceArray, RENDER_TARGET_SURF_ID, 0)
          ->GetDesc(&desc);
      desc.Usage = D3D11_USAGE_STAGING;
      desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
      desc.BindFlags = 0;

      gameExePMgsD3D11State->pid3d11deviceC->CreateTexture2D(
          &desc, 0, &state->stagingTexture);

      state->csri =
          csri_open_mem(csri_renderer_default(), &sub[0], sub.size(), NULL);
    }
    in.close();
  }

  return gameExeMgsMovieCPlayerPlayReal(pThis, a2, a3, movieFileName);
}

int __fastcall mgsMovieCPlayerStopHook(void* pThis) {
  return gameExeMgsMovieCPlayerStopReal(pThis);
}

int __fastcall mgsMovieCPlayerRenderHook(void* pThis) {
  CriManaFrameInfo* frameInfo;
  if (VideoPlayerObjVariant) {
    mgsMoviePlayerObjCHN* obj = (mgsMoviePlayerObjCHN*)pThis;
    frameInfo = &obj->criManaFrameInfo;
  } else {
    MgsMoviePlayerObj_t* obj = (MgsMoviePlayerObj_t*)pThis;
    frameInfo = &obj->criManaFrameInfo;
  }

  if (state==nullptr || state->csri == NULL) return gameExeMgsMovieCPlayerRenderReal(pThis);

  double time =
      ((double)frameInfo->framerate_d * (double)frameInfo->frame_no) /
      (double)frameInfo->framerate_n;

  state->keepLastFrame = frameInfo->frame_no == state->lastFrameNum;

  state->lastFrameNum = frameInfo->frame_no;
  state->time = time;

  return gameExeMgsMovieCPlayerRenderReal(pThis);
}
}  // namespace lb