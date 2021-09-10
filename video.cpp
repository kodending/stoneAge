#include "stdafx.h"
#include "video.h"


video::video()
{
}

video::~video()
{
}

HRESULT video::init()
{

	return S_OK;
}

void video::release()
{
	if (_hWndAVI)
	{
		MCIWndClose(_hWndAVI);
		MCIWndDestroy(_hWndAVI);
		_hWndAVI = 0;
	}
}

HRESULT video::setVideo(const char * fileName)
{

	const char* str = fileName;
	_fileName = str;
	// hWndAVI 생성
	_hWndAVI = MCIWndCreate(_hWnd, _hInstance,
		MCIWNDF_NOTIFYANSI | MCIWNDF_NOMENU | MCIWNDF_NOTIFYALL | MCIWNDF_NOPLAYBAR,
		_fileName);

	MCIWndClose(_hWndAVI);


	return S_OK;
}

void video::playVideo()
{

	MCIWndOpen(_hWndAVI, _fileName, 0);
	if (_hWndAVI)
	{
		RECT rc;
		GetClientRect(_hWnd, &rc);
		SetWindowPos(_hWndAVI, NULL, 0, 0, rc.right, rc.bottom, SWP_NOZORDER);
		MCIWndPlay(_hWndAVI);
	}
}

void video::closeVideo(void)
{
	if (_hWndAVI)
	{
		MCIWndClose(_hWndAVI);
	
	}

}

void video::deletVideo()
{
	if (_hWndAVI)
	{
		MCIWndClose(_hWndAVI);
		MCIWndDestroy(_hWndAVI);
		_hWndAVI = 0;
	}
}

void video::langsVideo(const char * fileName)
{
	

}

void video::startVideo(const char * fileName)
{
	const char* str = fileName;

	// hWndAVI 생성
	_hWndAVI = MCIWndCreate(_hWnd, _hInstance,
		MCIWNDF_NOTIFYANSI | MCIWNDF_NOMENU | MCIWNDF_NOTIFYALL | MCIWNDF_NOPLAYBAR,
		fileName);

	// 사이즈 맞춤
	if (_hWndAVI)
	{
		RECT rc;
		GetClientRect(_hWnd, &rc);
		SetWindowPos(_hWndAVI, NULL, 0, 0, rc.right, rc.bottom, SWP_NOZORDER);
		MCIWndPlay(_hWndAVI);
	}

}
