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

menuType * petSkillWindow::inputHandle(tileMap * tileMap)
{
	if (PtInRect(&_petSkill.returnRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(false);
		tileMap->setIsPosibleClick(false);
		tileMap->setDelayClickCount(0);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new petInfoWindow();
	}

	//¿À¸¥ÂÊ¹öÆ°À» ´­·¶À»¶§
	if (PtInRect(&_petSkill.rightButtonRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		_petSkill.petInfoCurrentPage++;

		if (_petSkill.petInfoCurrentPage > _petSkill.petInfoMaxPage)
		{
			_petSkill.petInfoCurrentPage = 1;
		}
	}

	//¿ÞÂÊ¹öÆ°À» ´­·¶À»¶§
	if (PtInRect(&_petSkill.leftButtonRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		_petSkill.petInfoCurrentPage--;

		if (_petSkill.petInfoCurrentPage < 1)
		{
			_petSkill.petInfoCurrentPage = _petSkill.petInfoMaxPage;
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

void petSkillWindow::update(tileMap * tileMap)
{
	writeIniData();

	_petSkill.frontRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + _petSkill.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _petSkill.frontImg->getHeight() / 2,
		_petSkill.frontImg->getWidth(), _petSkill.frontImg->getHeight());

	_petSkill.backRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + _petSkill.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _petSkill.frontImg->getHeight() / 2,
		_petSkill.backImg->getWidth(), _petSkill.backImg->getHeight());

	_petSkill.leftButtonRect = RectMake(CAMERAMANAGER->getCameraLEFT() + 48, CAMERAMANAGER->getCameraTOP() + 355,
		36, 18);

	_petSkill.rightButtonRect = RectMake(CAMERAMANAGER->getCameraLEFT() + 97, CAMERAMANAGER->getCameraTOP() + 355,
		36, 18);

	_petSkill.returnRect = RectMake(CAMERAMANAGER->getCameraLEFT() + 165, CAMERAMANAGER->getCameraTOP() + 355,
		88, 18);

	if (PtInRect(&_petSkill.frontRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(true);
	}

	else tileMap->setIsMouseOnPet(false);
}

void petSkillWindow::enter(tileMap * tileMap)
{
	_petSkill.backImg = IMAGEMANAGER->findImage("petSkillWindowBack");
	_petSkill.frontImg = IMAGEMANAGER->findImage("petSkillWindow");


}

void petSkillWindow::render(tileMap * tileMap)
{
	_petSkill.backImg->alphaRender(getMemDC(), _petSkill.backRect.left, _petSkill.backRect.top, 200);
	_petSkill.frontImg->render(getMemDC(), _petSkill.frontRect.left, _petSkill.frontRect.top);

	petInfoRender();

	//·ºÆ® ¸¶¿ì½º ¿Ã·ÈÀ»¶§ ÃÊ·Ï»ö±×¸®±â
	HPEN myPen = CreatePen(PS_DASH, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	if (PtInRect(&_petSkill.leftButtonRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _petSkill.leftButtonRect);
	}

	if (PtInRect(&_petSkill.rightButtonRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _petSkill.rightButtonRect);
	}

	if (PtInRect(&_petSkill.returnRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _petSkill.returnRect);
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void petSkillWindow::exit(tileMap * tileMap)
{
}

void petSkillWindow::writeIniData()
{
	int loginPlayer1 = INIDATA->loadDataInterger("Ä³¸¯ÅÍ", "ÇÃ·¹ÀÌ¾î1", "·Î±×ÀÎ");
	int loginPlayer2 = INIDATA->loadDataInterger("Ä³¸¯ÅÍ", "ÇÃ·¹ÀÌ¾î2", "·Î±×ÀÎ");

	//Æê ¸Æ½ºÆäÀÌÁö, ÇöÀçÆäÀÌÁö ºÒ·¯¿À±â
	if (loginPlayer1 == (int)INFO_YES)
	{
		string pet1 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "ÀÖ¾î?");
		string pet2 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "ÀÖ¾î?");
		string pet3 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "ÀÖ¾î?");
		string pet4 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "ÀÖ¾î?");
		string pet5 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "ÀÖ¾î?");

		if (pet1 == "ÀÖ¾î") 	_petSkill.petInfoMaxPage = 1;
		if (pet2 == "ÀÖ¾î") 	_petSkill.petInfoMaxPage = 2;
		if (pet3 == "ÀÖ¾î") 	_petSkill.petInfoMaxPage = 3;
		if (pet4 == "ÀÖ¾î") 	_petSkill.petInfoMaxPage = 4;
		if (pet5 == "ÀÖ¾î") 	_petSkill.petInfoMaxPage = 5;

		int petCurrentpage = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "ÆêÆäÀÌÁö", "ÇöÀçÆäÀÌÁö");
		_petSkill.petInfoCurrentPage = petCurrentpage;
	}

	if (loginPlayer2 == (int)INFO_YES)
	{

	}
	

	//Æê ÇöÀçÆäÀÌÁö È®ÀÎÇÏ°í ÇöÀçÆäÀÌÁöÀÇ Æê ÀÌ¸§°ú ±â¼ú°¡Á®¿À±â
	if (loginPlayer1 == (int)INFO_YES)
	{
		if (_petSkill.petInfoCurrentPage == 1)
		{
			_petSkill.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "ÀÌ¸§");
			_petSkill.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "Á¾·ù");
			_petSkill.petSkill1 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "½ºÅ³1");
			_petSkill.petSkill2 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "½ºÅ³2");
			_petSkill.petSkill3 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "½ºÅ³3");
			_petSkill.petSkill4 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "½ºÅ³4");
			_petSkill.petSkill5 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "½ºÅ³5");
			_petSkill.petSkill6 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "½ºÅ³6");
		}

		if (_petSkill.petInfoCurrentPage == 2)
		{
			_petSkill.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "ÀÌ¸§");
			_petSkill.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "Á¾·ù");
			_petSkill.petSkill1 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "½ºÅ³1");
			_petSkill.petSkill2 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "½ºÅ³2");
			_petSkill.petSkill3 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "½ºÅ³3");
			_petSkill.petSkill4 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "½ºÅ³4");
			_petSkill.petSkill5 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "½ºÅ³5");
			_petSkill.petSkill6 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "½ºÅ³6");
		}

		if (_petSkill.petInfoCurrentPage == 3)
		{
			_petSkill.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "ÀÌ¸§");
			_petSkill.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "Á¾·ù");
			_petSkill.petSkill1 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "½ºÅ³1");
			_petSkill.petSkill2 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "½ºÅ³2");
			_petSkill.petSkill3 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "½ºÅ³3");
			_petSkill.petSkill4 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "½ºÅ³4");
			_petSkill.petSkill5 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "½ºÅ³5");
			_petSkill.petSkill6 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "½ºÅ³6");
		}

		if (_petSkill.petInfoCurrentPage == 4)
		{
			_petSkill.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "ÀÌ¸§");
			_petSkill.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "Á¾·ù");
			_petSkill.petSkill1 = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "½ºÅ³1");
			_petSkill.petSkill2 = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "½ºÅ³2");
			_petSkill.petSkill3 = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "½ºÅ³3");
			_petSkill.petSkill4 = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "½ºÅ³4");
			_petSkill.petSkill5 = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "½ºÅ³5");
			_petSkill.petSkill6 = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "½ºÅ³6");
		}

		if (_petSkill.petInfoCurrentPage == 5)
		{
			_petSkill.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "ÀÌ¸§");
			_petSkill.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "Á¾·ù");
			_petSkill.petSkill1 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "½ºÅ³1");
			_petSkill.petSkill2 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "½ºÅ³2");
			_petSkill.petSkill3 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "½ºÅ³3");
			_petSkill.petSkill4 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "½ºÅ³4");
			_petSkill.petSkill5 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "½ºÅ³5");
			_petSkill.petSkill6 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "½ºÅ³6");
		}
	}

	if (loginPlayer2 == (int)INFO_YES)
	{
		if (_petSkill.petInfoCurrentPage == 1)
		{
			_petSkill.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "ÀÌ¸§");
			_petSkill.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "Á¾·ù");
			_petSkill.petSkill1 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "½ºÅ³1");
			_petSkill.petSkill2 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "½ºÅ³2");
			_petSkill.petSkill3 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "½ºÅ³3");
			_petSkill.petSkill4 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "½ºÅ³4");
			_petSkill.petSkill5 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "½ºÅ³5");
			_petSkill.petSkill6 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "½ºÅ³6");
		}

		if (_petSkill.petInfoCurrentPage == 2)
		{
			_petSkill.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "ÀÌ¸§");
			_petSkill.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "Á¾·ù");
			_petSkill.petSkill1 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "½ºÅ³1");
			_petSkill.petSkill2 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "½ºÅ³2");
			_petSkill.petSkill3 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "½ºÅ³3");
			_petSkill.petSkill4 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "½ºÅ³4");
			_petSkill.petSkill5 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "½ºÅ³5");
			_petSkill.petSkill6 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "½ºÅ³6");
		}

		if (_petSkill.petInfoCurrentPage == 3)
		{
			_petSkill.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "ÀÌ¸§");
			_petSkill.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "Á¾·ù");
			_petSkill.petSkill1 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "½ºÅ³1");
			_petSkill.petSkill2 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "½ºÅ³2");
			_petSkill.petSkill3 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "½ºÅ³3");
			_petSkill.petSkill4 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "½ºÅ³4");
			_petSkill.petSkill5 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "½ºÅ³5");
			_petSkill.petSkill6 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "½ºÅ³6");
		}

		if (_petSkill.petInfoCurrentPage == 4)
		{
			_petSkill.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "ÀÌ¸§");
			_petSkill.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "Á¾·ù");
			_petSkill.petSkill1 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "½ºÅ³1");
			_petSkill.petSkill2 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "½ºÅ³2");
			_petSkill.petSkill3 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "½ºÅ³3");
			_petSkill.petSkill4 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "½ºÅ³4");
			_petSkill.petSkill5 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "½ºÅ³5");
			_petSkill.petSkill6 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "½ºÅ³6");
		}

		if (_petSkill.petInfoCurrentPage == 5)
		{
			_petSkill.petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "ÀÌ¸§");
			_petSkill.petType = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "Á¾·ù");
			_petSkill.petSkill1 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "½ºÅ³1");
			_petSkill.petSkill2 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "½ºÅ³2");
			_petSkill.petSkill3 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "½ºÅ³3");
			_petSkill.petSkill4 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "½ºÅ³4");
			_petSkill.petSkill5 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "½ºÅ³5");
			_petSkill.petSkill6 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "½ºÅ³6");
		}
	}
}

void petSkillWindow::petInfoRender()
{
	//Æê ÀÌ¸§ ¶ç¿ì´Â°÷
	HFONT font3 = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY¸ñ°¢ÆÄÀÓB"));
	HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), font3);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 50, CAMERAMANAGER->getCameraTOP() + 35,
		_petSkill.petName.c_str(), strlen(_petSkill.petName.c_str()));

	SelectObject(getMemDC(), oldFont3);
	DeleteObject(font3);
	SetBkMode(getMemDC(), OPAQUE);

	//½ºÅ³ Á¤º¸ ¶ç¿ì´Â°÷
	HFONT font2 = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("¸¼Àº°íµñ"));
	HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), font2);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 80, CAMERAMANAGER->getCameraTOP() + 65,
		_petSkill.petSkill1.c_str(), strlen(_petSkill.petSkill1.c_str()));

	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 80, CAMERAMANAGER->getCameraTOP() + 91,
		_petSkill.petSkill2.c_str(), strlen(_petSkill.petSkill2.c_str()));

	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 80, CAMERAMANAGER->getCameraTOP() + 117,
		_petSkill.petSkill3.c_str(), strlen(_petSkill.petSkill3.c_str()));

	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 80, CAMERAMANAGER->getCameraTOP() + 143,
		_petSkill.petSkill4.c_str(), strlen(_petSkill.petSkill4.c_str()));

	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 80, CAMERAMANAGER->getCameraTOP() + 169,
		_petSkill.petSkill5.c_str(), strlen(_petSkill.petSkill5.c_str()));

	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 80, CAMERAMANAGER->getCameraTOP() + 195,
		_petSkill.petSkill6.c_str(), strlen(_petSkill.petSkill6.c_str()));

	SelectObject(getMemDC(), oldFont2);
	DeleteObject(font2);
	SetBkMode(getMemDC(), OPAQUE);
}
