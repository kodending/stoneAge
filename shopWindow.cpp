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

menuType * shopWindow::inputHandle(tileMap * tileMap)
{
	if (tileMap->_isClickArmorNPC == false && tileMap->_isClickWeaponNPC == false)
	{
		SOUNDMANAGER->play("window_down", 0.4f);
		return new baseType();
	}

	if (PtInRect(&_shopWindow.exitRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(false);
		tileMap->setIsPosibleClick(false);
		tileMap->setDelayClickCount(0);
		tileMap->_isClickArmorNPC = false;
		tileMap->_isClickWeaponNPC = false;
		SOUNDMANAGER->play("window_down", 0.4f);
		return new baseType();
	}

	if (PtInRect(&_shopWindow.buyRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		SOUNDMANAGER->play("window_up", 0.4f);
		return new buyItemWindow();
	}

	if (PtInRect(&_shopWindow.sellRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		SOUNDMANAGER->play("window_up", 0.4f);
		return new sellItemWindow();
	}

	return nullptr;
}

void shopWindow::update(tileMap * tileMap)
{
	updateRect(tileMap);

	if (PtInRect(&_shopWindow.frontRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(true);
	}

	else tileMap->setIsMouseOnPet(false);

	//움직임상태가되면 인풋핸들다시한번더 보게끔
	if (tileMap->getIsPlayerMove() == true)
	{
		tileMap->_isClickArmorNPC = false;
		tileMap->_isClickWeaponNPC = false;
		tileMap->InputHandle();
	}
}

void shopWindow::enter(tileMap * tileMap)
{
	_shopWindow.frontImg = IMAGEMANAGER->findImage("mainMenu");
	_shopWindow.backImg = IMAGEMANAGER->findImage("mainMenuBack");
}

void shopWindow::render(tileMap * tileMap)
{
	_shopWindow.backImg->alphaRender(getMemDC(), CAMERAMANAGER->getCameraCenterX() - _shopWindow.backImg->getWidth() / 2,
		CAMERAMANAGER->getCameraCenterY() - _shopWindow.backImg->getHeight() / 2, 200);
	_shopWindow.frontImg->render(getMemDC(), CAMERAMANAGER->getCameraCenterX() - _shopWindow.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraCenterY() - _shopWindow.frontImg->getHeight() / 2);
	IMAGEMANAGER->render("button", getMemDC(), _shopWindow.buyRect.left, _shopWindow.buyRect.top);
	IMAGEMANAGER->render("button", getMemDC(), _shopWindow.sellRect.left, _shopWindow.sellRect.top);
	IMAGEMANAGER->render("button", getMemDC(), _shopWindow.exitRect.left, _shopWindow.exitRect.top);



	textRender(tileMap);
	PtInRender(tileMap);
}

void shopWindow::exit(tileMap * tileMap)
{
}

void shopWindow::updateRect(tileMap * tileMap)
{
	_shopWindow.frontRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(),
		_shopWindow.frontImg->getWidth(), _shopWindow.frontImg->getHeight());
	_shopWindow.buyRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY() - 46,
		IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
	_shopWindow.sellRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(),
		IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
	_shopWindow.exitRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY() + 46,
		IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
}

void shopWindow::textRender(tileMap * tileMap)
{
	//머니 띄우기
	HFONT font2 = CreateFont(20, 0, 0, 0, 600, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY목각파임B"));
	HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), font2);
	SetBkMode(getMemDC(), TRANSPARENT);

	SetTextColor(getMemDC(), RGB(0, 0, 255));
	DrawText(getMemDC(), TEXT("사다"), strlen(TEXT("사다")),	&_shopWindow.buyRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SetTextColor(getMemDC(), RGB(255, 0, 0));
	DrawText(getMemDC(), TEXT("팔다"), strlen(TEXT("팔다")), &_shopWindow.sellRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	DrawText(getMemDC(), TEXT("닫기"), strlen(TEXT("닫기")), &_shopWindow.exitRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SelectObject(getMemDC(), oldFont2);
	DeleteObject(font2);
	SetBkMode(getMemDC(), OPAQUE);
}

void shopWindow::PtInRender(tileMap * tileMap)
{
	HPEN myPen = CreatePen(PS_DASH, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	if (PtInRect(&_shopWindow.buyRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _shopWindow.buyRect);
	}

	if (PtInRect(&_shopWindow.sellRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _shopWindow.sellRect);
	}

	if (PtInRect(&_shopWindow.exitRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _shopWindow.exitRect);
	}


	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}
