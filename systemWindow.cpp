#include "stdafx.h"
#include "gameNode.h"
#include "tileMap.h"
#include "baseType.h"
#include "actionWindow.h"
#include "stateWindow.h"
#include "petWindow.h"
#include "petInfoWindow.h"
#include "petSkillWindow.h"
#include "itemWindow.h"
#include "shopWindow.h"
#include "buyItemWindow.h"
#include "sellItemWindow.h"
#include "systemWindow.h"

menuType * systemWindow::inputHandle(tileMap * tileMap)
{
	if (PtInRect(&_sw.stringRc, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(false);
		tileMap->setIsPosibleClick(false);
		tileMap->setDelayClickCount(0);
		SOUNDMANAGER->play("window_up", 0.4f);
		_sw.isLogOutButton = true;
	}

	if (PtInRect(&_lw.returnRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(false);
		tileMap->setIsPosibleClick(false);
		tileMap->setDelayClickCount(0);
		SOUNDMANAGER->play("window_down", 0.4f);
		_isWindowOff = true;
	}

	if (_isWindowOff == true)
	{
		tileMap->setIsMouseOnPet(false);
		tileMap->setIsPosibleClick(false);
		tileMap->setDelayClickCount(0);
		SOUNDMANAGER->play("window_down", 0.4f);
		return new baseType();
	}

	if (PtInRect(&_lw.decideRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(false);
		tileMap->setIsPosibleClick(false);
		tileMap->setDelayClickCount(0);
		SOUNDMANAGER->play("window_down", 0.4f);
		RENDERMANAGER->deleteAll();
		SCENEMANAGER->changeScene("캐릭터선택");
	}

	return nullptr;
}

void systemWindow::update(tileMap * tileMap)
{
	_sw.rc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - _sw.img->getWidth() / 2, CAMERAMANAGER->getCameraBOTTOM() - _sw.img->getHeight() / 2 - 24,
		_sw.img->getWidth(), _sw.img->getHeight());
	_sw.stringRc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - _sw.img->getWidth() / 2, CAMERAMANAGER->getCameraBOTTOM() - _sw.img->getHeight() / 2 - 24,
		200, 30);
	
	if (_sw.isLogOutButton == true)
	{
		_lw.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(), _lw.img->getWidth(), _lw.img->getHeight());
		_lw.decideRect = RectMake(CAMERAMANAGER->getCameraCenterX() - 108, CAMERAMANAGER->getCameraCenterY() + 2, 96, 30);
		_lw.returnRect = RectMake(CAMERAMANAGER->getCameraCenterX() + 13, CAMERAMANAGER->getCameraCenterY() + 2, 97, 30);
	}

	if (_sw.isLogOutButton == false)
	{
		_lw.rc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 500, CAMERAMANAGER->getCameraTOP() - 500, _lw.img->getWidth(), _lw.img->getHeight());
		_lw.decideRect = RectMake(CAMERAMANAGER->getCameraRIGHT() + 550, CAMERAMANAGER->getCameraTOP() - 500, 96, 30);
		_lw.returnRect = RectMake(CAMERAMANAGER->getCameraRIGHT() + 500, CAMERAMANAGER->getCameraTOP() - 500, 97, 30);
	}

	if (PtInRect(&_sw.rc, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())) ||
		PtInRect(&_lw.rc, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(true);
	}

	else if (PtInRect(&_sw.rc, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())) == false &&
		PtInRect(&_lw.rc, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())) == false)
	{
		tileMap->setIsMouseOnPet(false);
	}

	if (tileMap->getIsPlayerMove() == true)
	{
		_isWindowOff = true;
	}
}

void systemWindow::enter(tileMap * tileMap)
{
	_sw.img = IMAGEMANAGER->findImage("inputWindow2");
	_lw.img = IMAGEMANAGER->findImage("inputWindow");
	_sw.isLogOutButton = false;
	_isWindowOff = false;
}

void systemWindow::render(tileMap * tileMap)
{
	IMAGEMANAGER->alphaRender("inputWindowBack", getMemDC(), (_sw.rc.left + _sw.rc.right) / 2 - IMAGEMANAGER->findImage("inputWindowBack")->getWidth() / 2,
		(_sw.rc.top + _sw.rc.bottom) / 2 - IMAGEMANAGER->findImage("inputWindowBack")->getHeight() / 2, 200);
	_sw.img->render(getMemDC(), _sw.rc.left, _sw.rc.top);

	if (_sw.isLogOutButton == true)
	{
		IMAGEMANAGER->alphaRender("inputWindowBack", getMemDC(), (_lw.rc.left + _lw.rc.right) / 2 - IMAGEMANAGER->findImage("inputWindowBack")->getWidth() / 2,
			(_lw.rc.top + _lw.rc.bottom) / 2 - IMAGEMANAGER->findImage("inputWindowBack")->getHeight() / 2, 200);
		_lw.img->render(getMemDC(), _lw.rc.left, _lw.rc.top);
	}


	HPEN myPen = CreatePen(PS_DASH, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	if (PtInRect(&_sw.stringRc, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _sw.stringRc);
	}

	if (PtInRect(&_lw.returnRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _lw.returnRect);
	}

	if (PtInRect(&_lw.decideRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _lw.decideRect);
	}


	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);

	//머니 띄우기
	HFONT font2 = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY목각파임B"));
	HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), font2);
	SetBkMode(getMemDC(), TRANSPARENT);

	SetTextColor(getMemDC(), RGB(230, 20, 20));
	DrawText(getMemDC(), TEXT("로그아웃"), strlen(TEXT("로그아웃")),
		&_sw.stringRc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	if (_sw.isLogOutButton == true)
	{
		RECT rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY() - 24, 250, 30);
		SetTextColor(getMemDC(), RGB(230, 230, 230));
		DrawText(getMemDC(), TEXT("로그아웃하시겠습니까?"), strlen(TEXT("로그아웃하시겠습니까?")),
			&rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		SetTextColor(getMemDC(), RGB(20, 20, 230));
		DrawText(getMemDC(), TEXT("확인"), strlen(TEXT("확인")),
			&_lw.decideRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		SetTextColor(getMemDC(), RGB(230, 20, 20));
		DrawText(getMemDC(), TEXT("취소"), strlen(TEXT("취소")),
			&_lw.returnRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	SelectObject(getMemDC(), oldFont2);
	DeleteObject(font2);
	SetBkMode(getMemDC(), OPAQUE);
}

void systemWindow::exit(tileMap * tileMap)
{

}
