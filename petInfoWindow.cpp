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

menuType * petInfoWindow::inputHandle(tileMap * tileMap)
{
	if (PtInRect(&_petInfo.returnRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(false);
		tileMap->setIsPosibleClick(false);
		tileMap->setDelayClickCount(0);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new petWindow();
	}

	//½ºÅ³Á¤º¸¸¦ ´­·¶À»¶§
	if (PtInRect(&_petInfo.skiilRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		int loginPlayer1 = INIDATA->loadDataInterger("Ä³¸¯ÅÍ", "ÇÃ·¹ÀÌ¾î1", "·Î±×ÀÎ");
		int loginPlayer2 = INIDATA->loadDataInterger("Ä³¸¯ÅÍ", "ÇÃ·¹ÀÌ¾î2", "·Î±×ÀÎ");
		char petPage[256];

		if (loginPlayer1 == (int)INFO_YES)
		{
			INIDATA->addData("ÆêÆäÀÌÁö", "ÇöÀçÆäÀÌÁö", _itoa(_petInfo.petInfoCurrentPage, petPage, 10));
			INIDATA->iniSave("ÇÃ·¹ÀÌ¾î1_Æê");
		}

		if (loginPlayer2 == (int)INFO_YES)
		{
			INIDATA->addData("ÆêÆäÀÌÁö", "ÇöÀçÆäÀÌÁö", _itoa(_petInfo.petInfoCurrentPage, petPage, 10));
			INIDATA->iniSave("ÇÃ·¹ÀÌ¾î2_Æê");
		}
		SOUNDMANAGER->play("window_up", 0.4f);
		return new petSkillWindow();
	}

	//¿À¸¥ÂÊ¹öÆ°À» ´­·¶À»¶§
	if (PtInRect(&_petInfo.rightButtonRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		_petInfo.petInfoCurrentPage++;

		if (_petInfo.petInfoCurrentPage > _petInfo.petInfoMaxPage)
		{
			_petInfo.petInfoCurrentPage = 1;
		}
	}

	//¿ÞÂÊ¹öÆ°À» ´­·¶À»¶§
	if (PtInRect(&_petInfo.leftButtonRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		_petInfo.petInfoCurrentPage--;

		if (_petInfo.petInfoCurrentPage < 1)
		{
			_petInfo.petInfoCurrentPage = _petInfo.petInfoMaxPage;
		}
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

	return nullptr;
}

void petInfoWindow::update(tileMap * tileMap)
{
	writeIniData();
	petFrameUpdate();

	_petInfo.frontRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + _petInfo.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _petInfo.frontImg->getHeight() / 2,
		_petInfo.frontImg->getWidth(), _petInfo.frontImg->getHeight());
	_petInfo.backRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + _petInfo.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _petInfo.frontImg->getHeight() / 2,
		_petInfo.backImg->getWidth(), _petInfo.backImg->getHeight());
	_petInfo.petNameChangeButtonRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 102, CAMERAMANAGER->getCameraTOP() + 77,
		114, 20);
	_petInfo.leftButtonRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 72, CAMERAMANAGER->getCameraTOP() + 345,
		40, 21);
	_petInfo.rightButtonRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 122, CAMERAMANAGER->getCameraTOP() + 345,
		40, 21);
	_petInfo.skiilRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 222, CAMERAMANAGER->getCameraTOP() + 345,
		115, 21);
	_petInfo.returnRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 337, CAMERAMANAGER->getCameraTOP() + 345,
		96, 21);
	_petInfo.petImgRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 365, CAMERAMANAGER->getCameraTOP() + 120,
		_petInfo.petImg->getFrameWidth(), _petInfo.petImg->getFrameHeight());
	

	if (PtInRect(&_petInfo.frontRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(true);
	}

	else tileMap->setIsMouseOnPet(false);
}

void petInfoWindow::enter(tileMap * tileMap)
{
	_petInfo.backImg = IMAGEMANAGER->findImage("petInfoWindowBack");
	_petInfo.frontImg = IMAGEMANAGER->findImage("petInfoWindow");
	_petInfo.petCurrentFrameX = 0;
	_petInfo.petCurrentFrameY = (int)DIR_SEVEN;
	_petInfo.petInfoCurrentPage = 1;

	_elapsedTime = 0;
}

void petInfoWindow::render(tileMap * tileMap)
{
	_petInfo.backImg->alphaRender(getMemDC(), _petInfo.backRect.left, _petInfo.backRect.top, 200);
	_petInfo.frontImg->render(getMemDC(), _petInfo.frontRect.left, _petInfo.frontRect.top);

	petInfoRender();

	//·ºÆ® ¸¶¿ì½º ¿Ã·ÈÀ»¶§ ÃÊ·Ï»ö±×¸®±â
	HPEN myPen = CreatePen(PS_DASH, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	if (PtInRect(&_petInfo.petNameChangeButtonRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _petInfo.petNameChangeButtonRect);
	}

	if (PtInRect(&_petInfo.leftButtonRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _petInfo.leftButtonRect);
	}

	if (PtInRect(&_petInfo.rightButtonRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _petInfo.rightButtonRect);
	}

	if (PtInRect(&_petInfo.skiilRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _petInfo.skiilRect);
	}

	if (PtInRect(&_petInfo.returnRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _petInfo.returnRect);
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void petInfoWindow::exit(tileMap * tileMap)
{
}

void petInfoWindow::writeIniData()
{
	int loginPlayer1 = INIDATA->loadDataInterger("Ä³¸¯ÅÍ", "ÇÃ·¹ÀÌ¾î1", "·Î±×ÀÎ");
	int loginPlayer2 = INIDATA->loadDataInterger("Ä³¸¯ÅÍ", "ÇÃ·¹ÀÌ¾î2", "·Î±×ÀÎ");

	//ÀüÃ¼ÆäÀÌÁö¼³Á¤
	if (loginPlayer1 == (int)INFO_YES)
	{
		string pet1 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "ÀÖ¾î?");
		string pet2 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "ÀÖ¾î?");
		string pet3 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "ÀÖ¾î?");
		string pet4 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "ÀÖ¾î?");
		string pet5 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "ÀÖ¾î?");

		if (pet1 == "ÀÖ¾î") 	_petInfo.petInfoMaxPage = 1;
		if (pet2 == "ÀÖ¾î") 	_petInfo.petInfoMaxPage = 2;
		if (pet3 == "ÀÖ¾î") 	_petInfo.petInfoMaxPage = 3;
		if (pet4 == "ÀÖ¾î") 	_petInfo.petInfoMaxPage = 4;
		if (pet5 == "ÀÖ¾î") 	_petInfo.petInfoMaxPage = 5;
	}

	if (loginPlayer2 == (int)INFO_YES)
	{
		string pet1 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "ÀÖ¾î?");
		string pet2 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "ÀÖ¾î?");
		string pet3 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "ÀÖ¾î?");
		string pet4 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "ÀÖ¾î?");
		string pet5 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "ÀÖ¾î?");

		if (pet1 == "ÀÖ¾î") 	_petInfo.petInfoMaxPage = 1;
		if (pet2 == "ÀÖ¾î") 	_petInfo.petInfoMaxPage = 2;
		if (pet3 == "ÀÖ¾î") 	_petInfo.petInfoMaxPage = 3;
		if (pet4 == "ÀÖ¾î") 	_petInfo.petInfoMaxPage = 4;
		if (pet5 == "ÀÖ¾î") 	_petInfo.petInfoMaxPage = 5;
	}

	//ÆêÁ¤º¸Ã¢ ºÒ·¯¿À±â
	if (loginPlayer1 == (int)INFO_YES)
	{
		if (_petInfo.petInfoCurrentPage == 1)
		{
			_petInfo.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "ÀÌ¸§");
			_petInfo.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "Á¾·ù");
			_petInfo.petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "·¹º§");
			_petInfo.currentEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "ÇöÀç°æÇèÄ¡");
			_petInfo.nextEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "´ÙÀ½°æÇèÄ¡");
			_petInfo.currentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "ÇöÀçÃ¼·Â");
			_petInfo.totalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "ÀüÃ¼Ã¼·Â");
			_petInfo.attackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "°ø°Ý·Â");
			_petInfo.defensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "¹æ¾î·Â");
			_petInfo.speedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "¼ø¹ß·Â");
			_petInfo.loyality = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "Ãæ¼ºµµ");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "Áö¼Ó¼º");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "¼ö¼Ó¼º");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "È­¼Ó¼º");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "Ç³¼Ó¼º");
		}

		if (_petInfo.petInfoCurrentPage == 2)
		{
			_petInfo.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "ÀÌ¸§");
			_petInfo.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "Á¾·ù");
			_petInfo.petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "·¹º§");
			_petInfo.currentEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "ÇöÀç°æÇèÄ¡");
			_petInfo.nextEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "´ÙÀ½°æÇèÄ¡");
			_petInfo.currentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "ÇöÀçÃ¼·Â");
			_petInfo.totalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "ÀüÃ¼Ã¼·Â");
			_petInfo.attackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "°ø°Ý·Â");
			_petInfo.defensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "¹æ¾î·Â");
			_petInfo.speedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "¼ø¹ß·Â");
			_petInfo.loyality = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "Ãæ¼ºµµ");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "Áö¼Ó¼º");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "¼ö¼Ó¼º");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "È­¼Ó¼º");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "Ç³¼Ó¼º");
		}

		if (_petInfo.petInfoCurrentPage == 3)
		{
			_petInfo.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "ÀÌ¸§");
			_petInfo.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "Á¾·ù");
			_petInfo.petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "·¹º§");
			_petInfo.currentEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "ÇöÀç°æÇèÄ¡");
			_petInfo.nextEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "´ÙÀ½°æÇèÄ¡");
			_petInfo.currentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "ÇöÀçÃ¼·Â");
			_petInfo.totalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "ÀüÃ¼Ã¼·Â");
			_petInfo.attackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "°ø°Ý·Â");
			_petInfo.defensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "¹æ¾î·Â");
			_petInfo.speedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "¼ø¹ß·Â");
			_petInfo.loyality = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "Ãæ¼ºµµ");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "Áö¼Ó¼º");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "¼ö¼Ó¼º");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "È­¼Ó¼º");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "Ç³¼Ó¼º");
		}

		if (_petInfo.petInfoCurrentPage == 4)
		{
			_petInfo.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "ÀÌ¸§");
			_petInfo.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "Á¾·ù");
			_petInfo.petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "·¹º§");
			_petInfo.currentEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "ÇöÀç°æÇèÄ¡");
			_petInfo.nextEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "´ÙÀ½°æÇèÄ¡");
			_petInfo.currentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "ÇöÀçÃ¼·Â");
			_petInfo.totalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "ÀüÃ¼Ã¼·Â");
			_petInfo.attackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "°ø°Ý·Â");
			_petInfo.defensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "¹æ¾î·Â");
			_petInfo.speedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "¼ø¹ß·Â");
			_petInfo.loyality = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "Ãæ¼ºµµ");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "Áö¼Ó¼º");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "¼ö¼Ó¼º");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "È­¼Ó¼º");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "Ç³¼Ó¼º");
		}

		if (_petInfo.petInfoCurrentPage == 5)
		{
			_petInfo.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "ÀÌ¸§");
			_petInfo.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "Á¾·ù");
			_petInfo.petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "·¹º§");
			_petInfo.currentEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "ÇöÀç°æÇèÄ¡");
			_petInfo.nextEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "´ÙÀ½°æÇèÄ¡");
			_petInfo.currentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "ÇöÀçÃ¼·Â");
			_petInfo.totalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "ÀüÃ¼Ã¼·Â");
			_petInfo.attackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "°ø°Ý·Â");
			_petInfo.defensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "¹æ¾î·Â");
			_petInfo.speedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "¼ø¹ß·Â");
			_petInfo.loyality = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "Ãæ¼ºµµ");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "Áö¼Ó¼º");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "¼ö¼Ó¼º");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "È­¼Ó¼º");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "Ç³¼Ó¼º");
		}
	}

	if (loginPlayer2 == (int)INFO_YES)
	{
		if (_petInfo.petInfoCurrentPage == 1)
		{
			_petInfo.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "ÀÌ¸§");
			_petInfo.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "Á¾·ù");
			_petInfo.petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "·¹º§");
			_petInfo.currentEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "ÇöÀç°æÇèÄ¡");
			_petInfo.nextEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "´ÙÀ½°æÇèÄ¡");
			_petInfo.currentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "ÇöÀçÃ¼·Â");
			_petInfo.totalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "ÀüÃ¼Ã¼·Â");
			_petInfo.attackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "°ø°Ý·Â");
			_petInfo.defensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "¹æ¾î·Â");
			_petInfo.speedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "¼ø¹ß·Â");
			_petInfo.loyality = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "Ãæ¼ºµµ");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "Áö¼Ó¼º");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "¼ö¼Ó¼º");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "È­¼Ó¼º");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "Ç³¼Ó¼º");
		}

		if (_petInfo.petInfoCurrentPage == 2)
		{
			_petInfo.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "ÀÌ¸§");
			_petInfo.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "Á¾·ù");
			_petInfo.petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "·¹º§");
			_petInfo.currentEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "ÇöÀç°æÇèÄ¡");
			_petInfo.nextEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "´ÙÀ½°æÇèÄ¡");
			_petInfo.currentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "ÇöÀçÃ¼·Â");
			_petInfo.totalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "ÀüÃ¼Ã¼·Â");
			_petInfo.attackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "°ø°Ý·Â");
			_petInfo.defensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "¹æ¾î·Â");
			_petInfo.speedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "¼ø¹ß·Â");
			_petInfo.loyality = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "Ãæ¼ºµµ");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "Áö¼Ó¼º");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "¼ö¼Ó¼º");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "È­¼Ó¼º");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "Ç³¼Ó¼º");
		}

		if (_petInfo.petInfoCurrentPage == 3)
		{
			_petInfo.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "ÀÌ¸§");
			_petInfo.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "Á¾·ù");
			_petInfo.petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "·¹º§");
			_petInfo.currentEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "ÇöÀç°æÇèÄ¡");
			_petInfo.nextEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "´ÙÀ½°æÇèÄ¡");
			_petInfo.currentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "ÇöÀçÃ¼·Â");
			_petInfo.totalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "ÀüÃ¼Ã¼·Â");
			_petInfo.attackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "°ø°Ý·Â");
			_petInfo.defensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "¹æ¾î·Â");
			_petInfo.speedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "¼ø¹ß·Â");
			_petInfo.loyality = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "Ãæ¼ºµµ");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "Áö¼Ó¼º");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "¼ö¼Ó¼º");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "È­¼Ó¼º");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "Ç³¼Ó¼º");
		}

		if (_petInfo.petInfoCurrentPage == 4)
		{
			_petInfo.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "ÀÌ¸§");
			_petInfo.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "Á¾·ù");
			_petInfo.petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "·¹º§");
			_petInfo.currentEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "ÇöÀç°æÇèÄ¡");
			_petInfo.nextEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "´ÙÀ½°æÇèÄ¡");
			_petInfo.currentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "ÇöÀçÃ¼·Â");
			_petInfo.totalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "ÀüÃ¼Ã¼·Â");
			_petInfo.attackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "°ø°Ý·Â");
			_petInfo.defensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "¹æ¾î·Â");
			_petInfo.speedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "¼ø¹ß·Â");
			_petInfo.loyality = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "Ãæ¼ºµµ");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "Áö¼Ó¼º");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "¼ö¼Ó¼º");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "È­¼Ó¼º");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "Ç³¼Ó¼º");
		}

		if (_petInfo.petInfoCurrentPage == 5)
		{
			_petInfo.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "ÀÌ¸§");
			_petInfo.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "Á¾·ù");
			_petInfo.petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "·¹º§");
			_petInfo.currentEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "ÇöÀç°æÇèÄ¡");
			_petInfo.nextEXP = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "´ÙÀ½°æÇèÄ¡");
			_petInfo.currentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "ÇöÀçÃ¼·Â");
			_petInfo.totalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "ÀüÃ¼Ã¼·Â");
			_petInfo.attackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "°ø°Ý·Â");
			_petInfo.defensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "¹æ¾î·Â");
			_petInfo.speedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "¼ø¹ß·Â");
			_petInfo.loyality = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "Ãæ¼ºµµ");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "Áö¼Ó¼º");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "¼ö¼Ó¼º");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "È­¼Ó¼º");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "Ç³¼Ó¼º");
		}
	}

	//ÆêÀÌ¹ÌÁöºÒ·¯¿À±â
	if (_petInfo.petType == (int)DURI)			 _petInfo.petImg = IMAGEMANAGER->findImage("duri_stand");
	if (_petInfo.petType == (int)SPOTTEDURI)	 _petInfo.petImg = IMAGEMANAGER->findImage("spottedUri_stand");
	if (_petInfo.petType == (int)URI)			 _petInfo.petImg = IMAGEMANAGER->findImage("uri_stand");
	if (_petInfo.petType == (int)MAMONAS)		 _petInfo.petImg = IMAGEMANAGER->findImage("mamonas_stand");
	if (_petInfo.petType == (int)MANMO)			 _petInfo.petImg = IMAGEMANAGER->findImage("manmo_stand");
	if (_petInfo.petType == (int)MANMOR)		 _petInfo.petImg = IMAGEMANAGER->findImage("manmor_stand");
	if (_petInfo.petType == (int)GOLROS)		 _petInfo.petImg = IMAGEMANAGER->findImage("golros_stand");
	if (_petInfo.petType == (int)MOGAROS)		 _petInfo.petImg = IMAGEMANAGER->findImage("mogaros_stand");
	if (_petInfo.petType == (int)OGAROS)		 _petInfo.petImg = IMAGEMANAGER->findImage("ogaros_stand");
	if (_petInfo.petType == (int)GORGOR)		 _petInfo.petImg = IMAGEMANAGER->findImage("gorgor_stand");
	if (_petInfo.petType == (int)NORNOR)		 _petInfo.petImg = IMAGEMANAGER->findImage("nornor_stand");
	if (_petInfo.petType == (int)VERGA)			 _petInfo.petImg = IMAGEMANAGER->findImage("verga_stand");
	if (_petInfo.petType == (int)VERURU)		 _petInfo.petImg = IMAGEMANAGER->findImage("veruru_stand");
	if (_petInfo.petType == (int)BANBORO)		 _petInfo.petImg = IMAGEMANAGER->findImage("banboro_stand");
	if (_petInfo.petType == (int)BANGINO)		 _petInfo.petImg = IMAGEMANAGER->findImage("bangino_stand");
	if (_petInfo.petType == (int)BURDON)		 _petInfo.petImg = IMAGEMANAGER->findImage("burdon_stand");
	if (_petInfo.petType == (int)RIBINO)		 _petInfo.petImg = IMAGEMANAGER->findImage("ribino_stand");
	if (_petInfo.petType == (int)YANGIRO)		 _petInfo.petImg = IMAGEMANAGER->findImage("yangiro_stand");

	//Áö¼Ó¼º
	for (int i = 0; i < _petInfo.attributeLandCount; ++i)
	{
		_arrayAttributeLand[i].img = IMAGEMANAGER->findImage("playerAttribute");
		_arrayAttributeLand[i].rc = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 363 + i * 8, CAMERAMANAGER->getCameraTOP() + 217,
			8, 12);
		_arrayAttributeLand[i].currentFrameX = 2;
		_arrayAttributeLand[i].currentFrameY = 0;
	}

	//¼ö¼Ó¼º
	for (int i = 0; i < _petInfo.attributeWaterCount; ++i)
	{
		_arrayAttributeWater[i].img = IMAGEMANAGER->findImage("playerAttribute");
		_arrayAttributeWater[i].rc = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 363 + i * 8, CAMERAMANAGER->getCameraTOP() + 245,
			8, 12);
		_arrayAttributeWater[i].currentFrameX = 0;
		_arrayAttributeWater[i].currentFrameY = 0;
	}

	//È­¼Ó¼º
	for (int i = 0; i < _petInfo.attributeFireCount; ++i)
	{
		_arrayAttributeFire[i].img = IMAGEMANAGER->findImage("playerAttribute");
		_arrayAttributeFire[i].rc = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 363 + i * 8, CAMERAMANAGER->getCameraTOP() + 273,
			8, 12);
		_arrayAttributeFire[i].currentFrameX = 1;
		_arrayAttributeFire[i].currentFrameY = 0;
	}

	//Ç³¼Ó¼º
	for (int i = 0; i < _petInfo.attributeWindCount; ++i)
	{
		_arrayAttributeWind[i].img = IMAGEMANAGER->findImage("playerAttribute");
		_arrayAttributeWind[i].rc = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 363 + i * 8, CAMERAMANAGER->getCameraTOP() + 301,
			8, 12);
		_arrayAttributeWind[i].currentFrameX = 3;
		_arrayAttributeWind[i].currentFrameY = 0;
	}
}

void petInfoWindow::petInfoRender()
{
	//Æê ÀÌ¸§ ¶ç¿ì´Â°÷
	HFONT font3 = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY¸ñ°¢ÆÄÀÓB"));
	HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), font3);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 60, CAMERAMANAGER->getCameraTOP() + 40,
		_petInfo.petName.c_str(), strlen(_petInfo.petName.c_str()));
	
	SelectObject(getMemDC(), oldFont3);
	DeleteObject(font3);
	SetBkMode(getMemDC(), OPAQUE);

	//Æê Á¤º¸ ¶ç¿ì´Â°÷
	HFONT font2 = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("¸¼Àº°íµñ"));
	HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), font2);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	char level[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 85, CAMERAMANAGER->getCameraTOP() + 98,
		_itoa(_petInfo.petLevel, level, 10), strlen(_itoa(_petInfo.petLevel, level, 10)));

	char curretEXP[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 123,
		_itoa(_petInfo.currentEXP, curretEXP, 10), strlen(_itoa(_petInfo.currentEXP, curretEXP, 10)));

	char nextEXP[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 153,
		_itoa(_petInfo.nextEXP, nextEXP, 10), strlen(_itoa(_petInfo.nextEXP, nextEXP, 10)));

	char currentStamina[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 85, CAMERAMANAGER->getCameraTOP() + 181,
		_itoa(_petInfo.currentStamina, currentStamina, 10), strlen(_itoa(_petInfo.currentStamina, currentStamina, 10)));

	char totalStamina[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 143, CAMERAMANAGER->getCameraTOP() + 181,
		_itoa(_petInfo.totalStamina, totalStamina, 10), strlen(_itoa(_petInfo.totalStamina, totalStamina, 10)));

	char attackPower[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 85, CAMERAMANAGER->getCameraTOP() + 208,
		_itoa(_petInfo.attackPower, attackPower, 10), strlen(_itoa(_petInfo.attackPower, attackPower, 10)));

	char defensePower[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 85, CAMERAMANAGER->getCameraTOP() + 236,
		_itoa(_petInfo.defensePower, defensePower, 10), strlen(_itoa(_petInfo.defensePower, defensePower, 10)));

	char speedPower[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 85, CAMERAMANAGER->getCameraTOP() + 263,
		_itoa(_petInfo.speedPower, speedPower, 10), strlen(_itoa(_petInfo.speedPower, speedPower, 10)));

	char loyality[256];
	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 85, CAMERAMANAGER->getCameraTOP() + 291,
		_itoa(_petInfo.loyality, loyality, 10), strlen(_itoa(_petInfo.loyality, loyality, 10)));

	SelectObject(getMemDC(), oldFont2);
	DeleteObject(font2);
	SetBkMode(getMemDC(), OPAQUE);

	//Áö¼Ó¼º
	for (int i = 0; i < _petInfo.attributeLandCount; ++i)
	{
		_arrayAttributeLand[i].img->frameRender(getMemDC(), _arrayAttributeLand[i].rc.left, _arrayAttributeLand[i].rc.top,
			_arrayAttributeLand[i].currentFrameX, _arrayAttributeLand[i].currentFrameY);
	}

	//¼ö¼Ó¼º
	for (int i = 0; i < _petInfo.attributeWaterCount; ++i)
	{
		_arrayAttributeWater[i].img->frameRender(getMemDC(), _arrayAttributeWater[i].rc.left, _arrayAttributeWater[i].rc.top,
			_arrayAttributeWater[i].currentFrameX, _arrayAttributeWater[i].currentFrameY);
	}

	//È­¼Ó¼º
	for (int i = 0; i < _petInfo.attributeFireCount; ++i)
	{
		_arrayAttributeFire[i].img->frameRender(getMemDC(), _arrayAttributeFire[i].rc.left, _arrayAttributeFire[i].rc.top,
			_arrayAttributeFire[i].currentFrameX, _arrayAttributeFire[i].currentFrameY);
	}

	//Ç³¼Ó¼º
	for (int i = 0; i < _petInfo.attributeWindCount; ++i)
	{
		_arrayAttributeWind[i].img->frameRender(getMemDC(), _arrayAttributeWind[i].rc.left, _arrayAttributeWind[i].rc.top,
			_arrayAttributeWind[i].currentFrameX, _arrayAttributeWind[i].currentFrameY);
	}

	_petInfo.petImg->frameRender(getMemDC(), _petInfo.petImgRect.left, _petInfo.petImgRect.top, _petInfo.petCurrentFrameX, _petInfo.petCurrentFrameY);
}

void petInfoWindow::petFrameUpdate()
{
	_elapsedTime += TIMEMANAGER->getElapsedTime();

	if (_elapsedTime >= 0.15f)
	{
		_elapsedTime -= 0.15f;

		_petInfo.petCurrentFrameX++;

		if (_petInfo.petCurrentFrameX > _petInfo.petImg->getMaxFrameX())
		{
			_petInfo.petCurrentFrameX = 0;
		}
	}
}
