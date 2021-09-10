#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		CAMERAMANAGER->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		SOUNDMANAGER->init();
		//KEYANIMANAGER->init();
		RENDERMANAGER->init();
		TXTDATA->init();
		INIDATA->init();
		STREAMMANAGER->init();
		MINIMAP->init();
		UIMANAGER->init();
	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
		
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();

		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		TXTDATA->release();
		TXTDATA->releaseSingleton();

		INIDATA->release();
		INIDATA->releaseSingleton();

		STREAMMANAGER->release();
		STREAMMANAGER->releaseSingleton();

		MINIMAP->release();
		MINIMAP->releaseSingleton();

		UIMANAGER->release();
		UIMANAGER->releaseSingleton();

		RENDERMANAGER->release();
		RENDERMANAGER->releaseSingleton();
	}
	

	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	
}

void gameNode::render()
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC         hdc; //얘 찐 중요합니...

	//마우스 커서 없애는 함수////////////////
	HCURSOR hHandCursor = ::LoadCursor(NULL, IDC_SIZE);

	SetCursor(hHandCursor);
	////////////////////////////


	switch (iMessage)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			this->render();

			EndPaint(hWnd, &ps);
		break;
		case WM_TIMER:
			this->update();
		break;
		//마우스 움직이면 여기서 메세지 발생
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));

		break;

		case WM_COMMAND:
		break;

		case WM_KEYDOWN:

			switch (wParam)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
				break;
			}
		break;


			//윈도우 창 부쉬는(?) 
		case WM_DESTROY:
		//윈도우 종료함수
			PostQuitMessage(0);
		return 0;
	}


	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
	
}
