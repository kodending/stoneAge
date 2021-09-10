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

menuType * baseType::inputHandle(tileMap * tileMap)
{
	//왼쪽 메뉴창 선택했을경우
	if (PtInRect(&_baseRight.actionRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnBaseRight(false);
		tileMap->setIsPosibleClick(false);
		tileMap->setDelayClickCount(0);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new actionWindow();
	}

	if (PtInRect(&tileMap->getMenuStateRect(), PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		SOUNDMANAGER->play("window_up", 0.4f);
		return new stateWindow();
	}

	if (PtInRect(&tileMap->getMenuPetRect(), PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		SOUNDMANAGER->play("window_up", 0.4f);
		return new petWindow();
	}

	if (PtInRect(&tileMap->getMenuItemRect(), PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		SOUNDMANAGER->play("window_up", 0.4f);
		return new itemWindow();
	}

	if (tileMap->_isClickArmorNPC == true)
	{
		SOUNDMANAGER->play("window_up", 0.4f);
		return new shopWindow();
	}

	if (tileMap->_isClickWeaponNPC == true)
	{
		SOUNDMANAGER->play("window_up", 0.4f);
		return new shopWindow();
	}

	if (PtInRect(&tileMap->getMenuSystemRect(), PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnBaseRight(false);
		tileMap->setIsPosibleClick(false);
		tileMap->setDelayClickCount(0);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new systemWindow();
	}

	return nullptr;
}

void baseType::update(tileMap * tileMap)
{
	_baseLeft.frontRect = RectMake(CAMERAMANAGER->getCameraLEFT(), CAMERAMANAGER->getCameraTOP(),
		_baseLeft.img->getWidth(), _baseLeft.img->getHeight());
	_baseRight.frontRect = RectMake(CAMERAMANAGER->getCameraRIGHT() - _baseRight.img->getWidth(), CAMERAMANAGER->getCameraTOP(),
		_baseRight.img->getWidth(), _baseRight.img->getHeight());
	_baseLeft.menuRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 24, CAMERAMANAGER->getCameraTOP() + 24,
		36, 38);
	_baseLeft.mailTradeRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 64, CAMERAMANAGER->getCameraTOP() + 24,
		36, 38);
	_baseLeft.partyRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 102, CAMERAMANAGER->getCameraTOP() + 24,
		37, 38);
	_baseLeft.dealRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 141, CAMERAMANAGER->getCameraTOP() + 24,
		38, 38);
	_baseLeft.tribeRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 182, CAMERAMANAGER->getCameraTOP() + 24,
		38, 38);
	_baseLeft.marketRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 220, CAMERAMANAGER->getCameraTOP() + 24,
		36, 38);
	_baseRight.fightRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 172, CAMERAMANAGER->getCameraTOP() + 24,
		33, 35);
	_baseRight.matchRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 134, CAMERAMANAGER->getCameraTOP() + 24,
		34, 36);
	_baseRight.questRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 96, CAMERAMANAGER->getCameraTOP() + 24,
		34, 36);
	_baseRight.actionRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 37, CAMERAMANAGER->getCameraTOP() + 60,
		66, 18);

	if (PtInRect(&_baseLeft.frontRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnBaseLeft(true);
	}

	else tileMap->setIsMouseOnBaseLeft(false);

	if (PtInRect(&_baseRight.frontRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnBaseRight(true);
	}

	else tileMap->setIsMouseOnBaseRight(false);
}

void baseType::enter(tileMap * tileMap)
{
	_baseLeft.img = IMAGEMANAGER->findImage("baseLeft");
	_baseRight.img = IMAGEMANAGER->findImage("baseRight");
	_baseLeft.frontRect = RectMake(CAMERAMANAGER->getCameraLEFT(), CAMERAMANAGER->getCameraTOP(),
		_baseLeft.img->getWidth(), _baseLeft.img->getHeight());
	_baseRight.frontRect = RectMake(CAMERAMANAGER->getCameraRIGHT() - _baseRight.img->getWidth(), CAMERAMANAGER->getCameraTOP(),
		_baseRight.img->getWidth(), _baseRight.img->getHeight());
	_baseLeft.menuRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 24, CAMERAMANAGER->getCameraTOP() + 24,
		36, 38);
	_baseLeft.mailTradeRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 64, CAMERAMANAGER->getCameraTOP() + 24,
		36, 38);
	_baseLeft.partyRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 102, CAMERAMANAGER->getCameraTOP() + 24,
		37, 38);
	_baseLeft.dealRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 141, CAMERAMANAGER->getCameraTOP() + 24,
		38, 38);
	_baseLeft.tribeRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 182, CAMERAMANAGER->getCameraTOP() + 24,
		38, 38);
	_baseLeft.marketRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 220, CAMERAMANAGER->getCameraTOP() + 24,
		36, 38);
	_baseRight.fightRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 172, CAMERAMANAGER->getCameraTOP() + 24,
		33, 35);
	_baseRight.matchRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 134, CAMERAMANAGER->getCameraTOP() + 24,
		34, 36);
	_baseRight.questRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 96, CAMERAMANAGER->getCameraTOP() + 24,
		34, 36);
	_baseRight.actionRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 37, CAMERAMANAGER->getCameraTOP() + 60,
		66, 18);
}

void baseType::render(tileMap * tileMap)
{
	_baseLeft.img->render(getMemDC(), _baseLeft.frontRect.left, _baseLeft.frontRect.top);
	_baseRight.img->render(getMemDC(), _baseRight.frontRect.left, _baseRight.frontRect.top);

	HPEN myPen = CreatePen(PS_DASH, 3, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	if (PtInRect(&_baseLeft.menuRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _baseLeft.menuRect);
	}

	if (PtInRect(&_baseLeft.mailTradeRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _baseLeft.mailTradeRect);
	}

	if (PtInRect(&_baseLeft.partyRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _baseLeft.partyRect);
	}

	if (PtInRect(&_baseLeft.dealRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _baseLeft.dealRect);
	}

	if (PtInRect(&_baseLeft.tribeRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _baseLeft.tribeRect);
	}

	if (PtInRect(&_baseLeft.marketRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _baseLeft.marketRect);
	}

	if (PtInRect(&_baseRight.fightRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _baseRight.fightRect);
	}

	if (PtInRect(&_baseRight.matchRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _baseRight.matchRect);
	}

	if (PtInRect(&_baseRight.questRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _baseRight.questRect);
	}

	if (PtInRect(&_baseRight.actionRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _baseRight.actionRect);
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void baseType::exit(tileMap * tileMap)
{
}

