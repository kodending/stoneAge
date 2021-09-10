#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "imageManager.h"
#include "txtData.h"
#include "timeManager.h"
#include "cameraManager.h"
#include "effectManager.h"
#include "sceneManager.h"
#include "soundManager.h"
//#include "keyAniManager.h"
#include "iniDataManager.h"
#include "renderManager.h"
#include "streamManager.h"
#include "miniMap.h"
#include "UIUIManager.h"
#include <vector>


using namespace std;
using namespace SUNFL_UTIL;

//==================================
// ## 매크로 처리 ## 21.04.23 ##
//==================================

#define WINNAME (LPTSTR)(TEXT("stoneAge 모작"))
#define WINSTARTX 2000 //윈도우 창 시작좌표 (left)
#define WINSTARTY 50	//윈도우 창 시작좌표 (top)
#define WINSIZEX 800	//윈도우 가로크기 // 맵툴 : 1024  // 인게임 : 800
#define WINSIZEY 600	//윈도우 세로크기 // 맵툴 : 800	// 인게임 : 600
#define BACKGROUNDX 4096
#define BACKGROUNDY 4096
#define CAMERAX WINSIZEX
#define CAMERAY	WINSIZEY

#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND				randomFunction::getSingleton()
#define KEYMANAGER		keyManager::getSingleton()
#define IMAGEMANAGER	imageManager::getSingleton()
#define TIMEMANAGER		timeManager::getSingleton()
#define CAMERAMANAGER	cameraManager::getSingleton()
#define EFFECTMANAGER	effectManager::getSingleton()
#define SCENEMANAGER	sceneManager::getSingleton()
#define SOUNDMANAGER	soundManager::getSingleton()
//#define KEYANIMANAGER	keyAniManager::getSingleton()
#define RENDERMANAGER	renderManager::getSingleton()
#define TXTDATA			txtData::getSingleton()
#define INIDATA			iniDataManager::getSingleton()
#define STREAMMANAGER	streamManager::getSingleton()
#define MINIMAP			miniMap::getSingleton()
#define UIMANAGER		UIUIManager::getSingleton()

#define SAFE_DELETE(p) {if(p) {delete(p); (p) = nullptr;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p) = NULL;}}

//==================================
// ## extern ## 21.04.28 ##
//==================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;
extern BOOL _leftButtonDown;