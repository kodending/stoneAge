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

menuType * stateWindow::inputHandle(tileMap * tileMap)
{
	if (PtInRect(&_stateWindow.exitRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnState(false);
		tileMap->setIsPosibleClick(false);
		tileMap->setDelayClickCount(0);
		SOUNDMANAGER->play("window_down", 0.4f);
		return new baseType();
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

	return nullptr;
}

void stateWindow::update(tileMap * tileMap)
{
	_stateWindow.frontRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + _stateWindow.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _stateWindow.frontImg->getHeight() / 2, _stateWindow.frontImg->getWidth(), _stateWindow.frontImg->getHeight());
	_stateWindow.backRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + _stateWindow.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _stateWindow.frontImg->getHeight() / 2, _stateWindow.backImg->getWidth(), _stateWindow.backImg->getHeight());
	_stateWindow.groupRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 82, CAMERAMANAGER->getCameraTOP() + 357,
		84, 16);
	_stateWindow.exitRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 200, CAMERAMANAGER->getCameraTOP() + 357,
		84, 16);

	for (int i = 0; i < tileMap->_playerInfo.attributeLand; ++i)
	{
		tileMap->_playerInfo._arrayAttributeLand[i].rc = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 190 + i * 8,
			CAMERAMANAGER->getCameraTOP() + 190, 8, 12);
		tileMap->_playerInfo._arrayAttributeLand[i].img = IMAGEMANAGER->findImage("playerAttribute");
		tileMap->_playerInfo._arrayAttributeLand[i].currentFrameX = 2;
		tileMap->_playerInfo._arrayAttributeLand[i].currentFrameY = 0;
	}

	for (int i = 0; i < tileMap->_playerInfo.attributeWater; ++i)
	{
		tileMap->_playerInfo._arrayAttributeWater[i].rc = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 190 + i * 8,
			CAMERAMANAGER->getCameraTOP() + 210, 8, 12);
		tileMap->_playerInfo._arrayAttributeWater[i].img = IMAGEMANAGER->findImage("playerAttribute");
		tileMap->_playerInfo._arrayAttributeWater[i].currentFrameX = 0;
		tileMap->_playerInfo._arrayAttributeWater[i].currentFrameY = 0;
	}

	for (int i = 0; i < tileMap->_playerInfo.attributeFire; ++i)
	{
		tileMap->_playerInfo._arrayAttributeFire[i].rc = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 190 + i * 8,
			CAMERAMANAGER->getCameraTOP() + 230, 8, 12);
		tileMap->_playerInfo._arrayAttributeFire[i].img = IMAGEMANAGER->findImage("playerAttribute");
		tileMap->_playerInfo._arrayAttributeFire[i].currentFrameX = 1;
		tileMap->_playerInfo._arrayAttributeFire[i].currentFrameY = 0;
	}

	for (int i = 0; i < tileMap->_playerInfo.attributeWind; ++i)
	{
		tileMap->_playerInfo._arrayAttributeWind[i].rc = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 190 + i * 8,
			CAMERAMANAGER->getCameraTOP() + 250, 8, 12);
		tileMap->_playerInfo._arrayAttributeWind[i].img = IMAGEMANAGER->findImage("playerAttribute");
		tileMap->_playerInfo._arrayAttributeWind[i].currentFrameX = 3;
		tileMap->_playerInfo._arrayAttributeWind[i].currentFrameY = 0;
	}

	if (PtInRect(&_stateWindow.frontRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnState(true);
	}

	else tileMap->setIsMouseOnState(false);
}

void stateWindow::enter(tileMap * tileMap)
{
	_stateWindow.backImg = IMAGEMANAGER->findImage("stateWindowBack");
	_stateWindow.frontImg = IMAGEMANAGER->findImage("stateWindow");
	_stateWindow.frontRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + _stateWindow.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _stateWindow.frontImg->getHeight() / 2, _stateWindow.frontImg->getWidth(), _stateWindow.frontImg->getHeight());
	_stateWindow.backRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + _stateWindow.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _stateWindow.frontImg->getHeight() / 2, _stateWindow.backImg->getWidth(), _stateWindow.backImg->getHeight());
	_stateWindow.groupRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 82, CAMERAMANAGER->getCameraTOP() + 357,
		83, 16);
	_stateWindow.exitRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 200, CAMERAMANAGER->getCameraTOP() + 357,
		83, 16);
	tileMap->setIsWriteInidata(false);
}

void stateWindow::render(tileMap * tileMap)
{
	_stateWindow.backImg->alphaRender(getMemDC(), _stateWindow.backRect.left, _stateWindow.backRect.top, 200);
	_stateWindow.frontImg->render(getMemDC(), _stateWindow.frontRect.left, _stateWindow.frontRect.top);

	if (tileMap->_playerInfo.type == (int)INFO_RED)
	{
		IMAGEMANAGER->frameRender("playerFaceSetting", getMemDC(), CAMERAMANAGER->getCameraLEFT() + 187, CAMERAMANAGER->getCameraTOP() + 87, 0, 0);
	}

	if (tileMap->_playerInfo.type == (int)INFO_BLUE)
	{
		IMAGEMANAGER->frameRender("playerFaceSetting", getMemDC(), CAMERAMANAGER->getCameraLEFT() + 187, CAMERAMANAGER->getCameraTOP() + 87, 1, 0);
	}

	for (int i = 0; i < tileMap->_playerInfo.attributeLand; ++i)
	{
		tileMap->_playerInfo._arrayAttributeLand[i].img->frameRender(getMemDC(), tileMap->_playerInfo._arrayAttributeLand[i].rc.left,
			tileMap->_playerInfo._arrayAttributeLand[i].rc.top,
			tileMap->_playerInfo._arrayAttributeLand[i].currentFrameX,
			tileMap->_playerInfo._arrayAttributeLand[i].currentFrameY);
	}

	for (int i = 0; i < tileMap->_playerInfo.attributeWater; ++i)
	{
		tileMap->_playerInfo._arrayAttributeWater[i].img->frameRender(getMemDC(), tileMap->_playerInfo._arrayAttributeWater[i].rc.left,
			tileMap->_playerInfo._arrayAttributeWater[i].rc.top,
			tileMap->_playerInfo._arrayAttributeWater[i].currentFrameX,
			tileMap->_playerInfo._arrayAttributeWater[i].currentFrameY);
	}

	for (int i = 0; i < tileMap->_playerInfo.attributeFire; ++i)
	{
		tileMap->_playerInfo._arrayAttributeFire[i].img->frameRender(getMemDC(), tileMap->_playerInfo._arrayAttributeFire[i].rc.left,
			tileMap->_playerInfo._arrayAttributeFire[i].rc.top,
			tileMap->_playerInfo._arrayAttributeFire[i].currentFrameX,
			tileMap->_playerInfo._arrayAttributeFire[i].currentFrameY);
	}

	for (int i = 0; i < tileMap->_playerInfo.attributeWind; ++i)
	{
		tileMap->_playerInfo._arrayAttributeWind[i].img->frameRender(getMemDC(), tileMap->_playerInfo._arrayAttributeWind[i].rc.left,
			tileMap->_playerInfo._arrayAttributeWind[i].rc.top,
			tileMap->_playerInfo._arrayAttributeWind[i].currentFrameX,
			tileMap->_playerInfo._arrayAttributeWind[i].currentFrameY);
	}

	HFONT font3 = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY¸ñ°¢ÆÄÀÓB"));
	HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), font3);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 80));

	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 32, CAMERAMANAGER->getCameraTOP() + 28, tileMap->_playerInfo.name.c_str(), strlen(tileMap->_playerInfo.name.c_str()));

	SelectObject(getMemDC(), oldFont3);
	DeleteObject(font3);
	SetBkMode(getMemDC(), OPAQUE);

	HFONT font2 = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("¸¼Àº°íµñ"));
	HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), font2);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	char level[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 75, CAMERAMANAGER->getCameraTOP() + 75, _itoa(tileMap->_playerInfo.level, level, 10),
		strlen(_itoa(tileMap->_playerInfo.level, level, 10)));

	char currentEXP[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 75, CAMERAMANAGER->getCameraTOP() + 95, _itoa(tileMap->_playerInfo.currentEXP, currentEXP, 10),
		strlen(_itoa(tileMap->_playerInfo.currentEXP, currentEXP, 10)));

	char nextEXP[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 75, CAMERAMANAGER->getCameraTOP() + 116, _itoa(tileMap->_playerInfo.nextEXP, nextEXP, 10),
		strlen(_itoa(tileMap->_playerInfo.nextEXP, nextEXP, 10)));

	char currentStamina[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 75, CAMERAMANAGER->getCameraTOP() + 138, _itoa(tileMap->_playerInfo.currentStamina, currentStamina, 10),
		strlen(_itoa(tileMap->_playerInfo.currentStamina, currentStamina, 10)));

	char totalStamina[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 129, CAMERAMANAGER->getCameraTOP() + 138, _itoa(tileMap->_playerInfo.totalStamina, totalStamina, 10),
		strlen(_itoa(tileMap->_playerInfo.totalStamina, totalStamina, 10)));

	char magicalEnergy[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 75, CAMERAMANAGER->getCameraTOP() + 161, _itoa(tileMap->_playerInfo.magicalEnergy, magicalEnergy, 10),
		strlen(_itoa(tileMap->_playerInfo.magicalEnergy, magicalEnergy, 10)));

	char attackPower[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 75, CAMERAMANAGER->getCameraTOP() + 181, _itoa(tileMap->_playerInfo.attackPower, attackPower, 10),
		strlen(_itoa(tileMap->_playerInfo.attackPower, attackPower, 10)));

	char defensePower[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 75, CAMERAMANAGER->getCameraTOP() + 204, _itoa(tileMap->_playerInfo.defensePower, defensePower, 10),
		strlen(_itoa(tileMap->_playerInfo.defensePower, defensePower, 10)));

	char speedPower[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 75, CAMERAMANAGER->getCameraTOP() + 225, _itoa(tileMap->_playerInfo.speedPower, speedPower, 10),
		strlen(_itoa(tileMap->_playerInfo.speedPower, speedPower, 10)));

	char charming[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 75, CAMERAMANAGER->getCameraTOP() + 247, _itoa(tileMap->_playerInfo.charming, charming, 10),
		strlen(_itoa(tileMap->_playerInfo.charming, charming, 10)));

	char playerStamina[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 85, CAMERAMANAGER->getCameraTOP() + 300, _itoa(tileMap->_playerInfo.playerStamina, playerStamina, 10),
		strlen(_itoa(tileMap->_playerInfo.playerStamina, playerStamina, 10)));

	char playerStrength[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 210, CAMERAMANAGER->getCameraTOP() + 300, _itoa(tileMap->_playerInfo.playerStrength, playerStrength, 10),
		strlen(_itoa(tileMap->_playerInfo.playerStrength, playerStrength, 10)));

	char playerHealth[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 85, CAMERAMANAGER->getCameraTOP() + 321, _itoa(tileMap->_playerInfo.playerHealth, playerHealth, 10),
		strlen(_itoa(tileMap->_playerInfo.playerHealth, playerHealth, 10)));

	char playerSpeed[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 210, CAMERAMANAGER->getCameraTOP() + 321, _itoa(tileMap->_playerInfo.playerSpeed, playerSpeed, 10),
		strlen(_itoa(tileMap->_playerInfo.playerSpeed, playerSpeed, 10)));

	SelectObject(getMemDC(), oldFont2);
	DeleteObject(font2);
	SetBkMode(getMemDC(), OPAQUE);

	HPEN myPen = CreatePen(PS_DASH, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	if (PtInRect(&_stateWindow.groupRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _stateWindow.groupRect);
	}

	if (PtInRect(&_stateWindow.exitRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _stateWindow.exitRect);
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void stateWindow::exit(tileMap * tileMap)
{

}
