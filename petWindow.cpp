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

menuType * petWindow::inputHandle(tileMap * tileMap)
{
	if (PtInRect(&_petWindow.exitRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(false);
		tileMap->setIsPosibleClick(false);
		tileMap->setDelayClickCount(0);
		SOUNDMANAGER->play("window_down", 0.4f);
		return new baseType();
	}

	if (PtInRect(&_petWindow.infoRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(false);
		tileMap->setIsPosibleClick(false);
		tileMap->setDelayClickCount(0);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new petInfoWindow();
	}

	if (PtInRect(&tileMap->getMenuStateRect(), PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		SOUNDMANAGER->play("window_up", 0.4f);
		return new stateWindow();
	}

	if (PtInRect(&tileMap->getMenuItemRect(), PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		SOUNDMANAGER->play("window_up", 0.4f);
		return new itemWindow();
	}

	//ÆäÆ® ¸ðµå º¯°æ ·ºÆ®¸¦ ´­·¶À»¶§
	for (int i = 0; i < 5; ++i)
	{
		if (PtInRect(&_petWindow.petButtonRect[i], PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
		{
			int loginPlayer1 = INIDATA->loadDataInterger("Ä³¸¯ÅÍ", "ÇÃ·¹ÀÌ¾î1", "·Î±×ÀÎ");
			int loginPlayer2 = INIDATA->loadDataInterger("Ä³¸¯ÅÍ", "ÇÃ·¹ÀÌ¾î2", "·Î±×ÀÎ");
			if (loginPlayer1 == (int)INFO_YES)
			{
				_petWindow.petAvailableRide[0] = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "Å¾½Â°¡´É");
				_petWindow.petAvailableRide[1] = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "Å¾½Â°¡´É");
				_petWindow.petAvailableRide[2] = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "Å¾½Â°¡´É");
				_petWindow.petAvailableRide[3] = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "Å¾½Â°¡´É");
				_petWindow.petAvailableRide[4] = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "Å¾½Â°¡´É");
			}
			if (loginPlayer2 == (int)INFO_YES)
			{
				_petWindow.petAvailableRide[0] = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "Å¾½Â°¡´É");
				_petWindow.petAvailableRide[1] = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "Å¾½Â°¡´É");
				_petWindow.petAvailableRide[2] = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "Å¾½Â°¡´É");
				_petWindow.petAvailableRide[3] = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "Å¾½Â°¡´É");
				_petWindow.petAvailableRide[4] = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "Å¾½Â°¡´É");
			}
		

			if (_petWindow.petModeName[i] == "¹èÆ²")
			{
				_petWindow.petModeName[i] = "´ë±â";

				if (i == 0) INIDATA->addData("Æê1", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 1) INIDATA->addData("Æê2", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 2) INIDATA->addData("Æê3", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 3) INIDATA->addData("Æê4", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 4) INIDATA->addData("Æê5", "¸ðµå", _petWindow.petModeName[i].c_str());

				if (loginPlayer1 == (int)INFO_YES) INIDATA->iniSave("ÇÃ·¹ÀÌ¾î1_Æê");
				if (loginPlayer2 == (int)INFO_YES) INIDATA->iniSave("ÇÃ·¹ÀÌ¾î2_Æê");

				break;
			}
			
			if (_petWindow.petModeName[i] == "´ë±â")
			{
				_petWindow.petModeName[i] = "ÈÞ½Ä";

				if (i == 0) INIDATA->addData("Æê1", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 1) INIDATA->addData("Æê2", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 2) INIDATA->addData("Æê3", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 3) INIDATA->addData("Æê4", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 4) INIDATA->addData("Æê5", "¸ðµå", _petWindow.petModeName[i].c_str());

				if (loginPlayer1 == (int)INFO_YES) INIDATA->iniSave("ÇÃ·¹ÀÌ¾î1_Æê");
				if (loginPlayer2 == (int)INFO_YES) INIDATA->iniSave("ÇÃ·¹ÀÌ¾î2_Æê");

				break;
			}

			if (_petWindow.petModeName[i] == "ÈÞ½Ä")
			{
				if (_petWindow.petAvailableRide[i] == "°¡´É")
				{
					_petWindow.petModeName[i] = "Å¾½Â";
				}

				if (_petWindow.petAvailableRide[i] == "ºÒ°¡´É")
				{
					_petWindow.petModeName[i] = "¹èÆ²";
				}

				if (i == 0) INIDATA->addData("Æê1", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 1) INIDATA->addData("Æê2", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 2) INIDATA->addData("Æê3", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 3) INIDATA->addData("Æê4", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 4) INIDATA->addData("Æê5", "¸ðµå", _petWindow.petModeName[i].c_str());

				if (loginPlayer1 == (int)INFO_YES) INIDATA->iniSave("ÇÃ·¹ÀÌ¾î1_Æê");
				if (loginPlayer2 == (int)INFO_YES) INIDATA->iniSave("ÇÃ·¹ÀÌ¾î2_Æê");

				break;
			}

			if (_petWindow.petModeName[i] == "Å¾½Â")
			{
				_petWindow.petModeName[i] = "¹èÆ²";

				if (i == 0) INIDATA->addData("Æê1", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 1) INIDATA->addData("Æê2", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 2) INIDATA->addData("Æê3", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 3) INIDATA->addData("Æê4", "¸ðµå", _petWindow.petModeName[i].c_str());
				if (i == 4) INIDATA->addData("Æê5", "¸ðµå", _petWindow.petModeName[i].c_str());

				if (loginPlayer1 == (int)INFO_YES) INIDATA->iniSave("ÇÃ·¹ÀÌ¾î1_Æê");
				if (loginPlayer2 == (int)INFO_YES) INIDATA->iniSave("ÇÃ·¹ÀÌ¾î2_Æê");

				break;
			}
		}
	}


	return nullptr;
}

void petWindow::update(tileMap * tileMap)
{
	writeIniData();

	_petWindow.frontRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + _petWindow.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _petWindow.frontImg->getHeight() / 2,
		_petWindow.frontImg->getWidth(), _petWindow.frontImg->getHeight());
	_petWindow.backRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + _petWindow.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _petWindow.frontImg->getHeight() / 2,
		_petWindow.backImg->getWidth(), _petWindow.backImg->getHeight());
	_petWindow.infoRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 87, CAMERAMANAGER->getCameraTOP() + 330,
		90, 18);
	_petWindow.exitRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 213, CAMERAMANAGER->getCameraTOP() + 330,
		90, 18);


	if (PtInRect(&_petWindow.frontRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(true);
	}

	else tileMap->setIsMouseOnPet(false);
}

void petWindow::enter(tileMap * tileMap)
{
	_petWindow.backImg = IMAGEMANAGER->findImage("petWindowBack");
	_petWindow.frontImg = IMAGEMANAGER->findImage("petWindow");
	_petWindow.frontRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + _petWindow.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _petWindow.frontImg->getHeight() / 2,
		_petWindow.frontImg->getWidth(), _petWindow.frontImg->getHeight());
	_petWindow.backRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + _petWindow.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _petWindow.frontImg->getHeight() / 2,
		_petWindow.backImg->getWidth(), _petWindow.backImg->getHeight());

	for (int i = 0; i < 5; ++i)
	{
		_petWindow.isPetNum[i] = false;
		_petModeColorR[i] = 0;
		_petModeColorG[i] = 0;
		_petModeColorB[i] = 0;
	}
}

void petWindow::render(tileMap * tileMap)
{
	_petWindow.backImg->alphaRender(getMemDC(), _petWindow.backRect.left, _petWindow.backRect.top, 200);
	_petWindow.frontImg->render(getMemDC(), _petWindow.frontRect.left, _petWindow.frontRect.top);

	petInfoRender();

	HPEN myPen = CreatePen(PS_DASH, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	if (PtInRect(&_petWindow.infoRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _petWindow.infoRect);
	}

	if (PtInRect(&_petWindow.exitRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _petWindow.exitRect);
	}

	for (int i = 0; i < 5; ++i)
	{
		if (PtInRect(&_petWindow.petButtonRect[i], PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
		{
			Rectangle(getMemDC(), _petWindow.petButtonRect[i]);
		}

		if (PtInRect(&_petWindow.petNameRect[i], PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
		{
			Rectangle(getMemDC(), _petWindow.petNameRect[i]);
		}
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void petWindow::exit(tileMap * tileMap)
{
}

void petWindow::writeIniData()
{
	int loginPlayer1 = INIDATA->loadDataInterger("Ä³¸¯ÅÍ", "ÇÃ·¹ÀÌ¾î1", "·Î±×ÀÎ");
	int loginPlayer2 = INIDATA->loadDataInterger("Ä³¸¯ÅÍ", "ÇÃ·¹ÀÌ¾î2", "·Î±×ÀÎ");

	//ÇÃ·¹ÀÌ¾î1¿¡ ·Î±×ÀÎÇßÀ»°æ¿ì
	if (loginPlayer1 == (int)INFO_YES)
	{
		string pet1 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "ÀÖ¾î?");
		string pet2 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "ÀÖ¾î?");
		string pet3 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "ÀÖ¾î?");
		string pet4 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "ÀÖ¾î?");
		string pet5 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "ÀÖ¾î?");

		if (pet1 == "ÀÖ¾î")
		{
			_petWindow.isPetNum[0] = true;
			_petWindow.petButtonImg[0] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[0] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 54,
				_petWindow.petButtonImg[0]->getWidth(), _petWindow.petButtonImg[0]->getHeight());
			_petWindow.petNameRect[0] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 35,
				80, 18);
			string petModeName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "¸ðµå");
			_petWindow.petModeName[0] = petModeName;
		}

		if (pet2 == "ÀÖ¾î")
		{
			_petWindow.isPetNum[1] = true;
			_petWindow.petButtonImg[1] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[1] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 111,
				_petWindow.petButtonImg[1]->getWidth(), _petWindow.petButtonImg[1]->getHeight());
			_petWindow.petNameRect[1] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 92,
				80, 18);
			string petModeName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "¸ðµå");
			_petWindow.petModeName[1] = petModeName;
		}

		if (pet3 == "ÀÖ¾î")
		{
			_petWindow.isPetNum[2] = true;
			_petWindow.petButtonImg[2] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[2] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 168,
				_petWindow.petButtonImg[2]->getWidth(), _petWindow.petButtonImg[2]->getHeight());
			_petWindow.petNameRect[2] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 149,
				80, 18);
			string petModeName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "¸ðµå");
			_petWindow.petModeName[2] = petModeName;
		}

		if (pet4 == "ÀÖ¾î")
		{
			_petWindow.isPetNum[3] = true;
			_petWindow.petButtonImg[3] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[3] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 225,
				_petWindow.petButtonImg[3]->getWidth(), _petWindow.petButtonImg[3]->getHeight());
			_petWindow.petNameRect[3] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 206,
				80, 18);
			string petModeName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "¸ðµå");
			_petWindow.petModeName[3] = petModeName;
		}

		if (pet5 == "ÀÖ¾î")
		{
			_petWindow.isPetNum[4] = true;
			_petWindow.petButtonImg[4] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[4] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 282,
				_petWindow.petButtonImg[4]->getWidth(), _petWindow.petButtonImg[4]->getHeight());
			_petWindow.petNameRect[4] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 263,
				80, 18);
			string petModeName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "¸ðµå");
			_petWindow.petModeName[4] = petModeName;
		}
	}

	//ÇÃ·¹ÀÌ¾î2¿¡ ·Î±×ÀÎÇßÀ»°æ¿ì
	if (loginPlayer2 == (int)INFO_YES)
	{
		string pet1 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "ÀÖ¾î?");
		string pet2 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "ÀÖ¾î?");
		string pet3 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "ÀÖ¾î?");
		string pet4 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "ÀÖ¾î?");
		string pet5 = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "ÀÖ¾î?");

		if (pet1 == "ÀÖ¾î")
		{
			_petWindow.isPetNum[0] = true;
			_petWindow.petButtonImg[0] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[0] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 54,
				_petWindow.petButtonImg[0]->getWidth(), _petWindow.petButtonImg[0]->getHeight());
			_petWindow.petNameRect[0] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 35,
				80, 18);
			string petModeName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "¸ðµå");
			_petWindow.petModeName[0] = petModeName;
		}

		if (pet2 == "ÀÖ¾î")
		{
			_petWindow.isPetNum[1] = true;
			_petWindow.petButtonImg[1] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[1] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 111,
				_petWindow.petButtonImg[1]->getWidth(), _petWindow.petButtonImg[1]->getHeight());
			_petWindow.petNameRect[1] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 92,
				80, 18);
			string petModeName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "¸ðµå");
			_petWindow.petModeName[1] = petModeName;
		}

		if (pet3 == "ÀÖ¾î")
		{
			_petWindow.isPetNum[2] = true;
			_petWindow.petButtonImg[2] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[2] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 168,
				_petWindow.petButtonImg[2]->getWidth(), _petWindow.petButtonImg[2]->getHeight());
			_petWindow.petNameRect[2] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 149,
				80, 18);
			string petModeName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "¸ðµå");
			_petWindow.petModeName[2] = petModeName;
		}

		if (pet4 == "ÀÖ¾î")
		{
			_petWindow.isPetNum[3] = true;
			_petWindow.petButtonImg[3] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[3] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 225,
				_petWindow.petButtonImg[3]->getWidth(), _petWindow.petButtonImg[3]->getHeight());
			_petWindow.petNameRect[3] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 206,
				80, 18);
			string petModeName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "¸ðµå");
			_petWindow.petModeName[3] = petModeName;
		}

		if (pet5 == "ÀÖ¾î")
		{
			_petWindow.isPetNum[4] = true;
			_petWindow.petButtonImg[4] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[4] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 282,
				_petWindow.petButtonImg[4]->getWidth(), _petWindow.petButtonImg[4]->getHeight());
			_petWindow.petNameRect[4] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 263,
				80, 18);
			string petModeName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "¸ðµå");
			_petWindow.petModeName[4] = petModeName;
		}
	}
}

void petWindow::petInfoRender()
{
	//¿ì¼± RGB  ¼³Á¤
	for (int i = 0; i < 5; ++i)
	{
		if (_petWindow.petModeName[i] == "¹èÆ²")
		{
			_petModeColorR[i] = 255;
			_petModeColorG[i] = 255;
			_petModeColorB[i] = 0;
		}

		if (_petWindow.petModeName[i] == "´ë±â")
		{
			_petModeColorR[i] = 0;
			_petModeColorG[i] = 255;
			_petModeColorB[i] = 255;
		}

		if (_petWindow.petModeName[i] == "ÈÞ½Ä")
		{
			_petModeColorR[i] = 255;
			_petModeColorG[i] = 255;
			_petModeColorB[i] = 255;
		}

		if (_petWindow.petModeName[i] == "Å¾½Â")
		{
			_petModeColorR[i] = 0;
			_petModeColorG[i] = 255;
			_petModeColorB[i] = 0;
		}
	}

	int loginPlayer1 = INIDATA->loadDataInterger("Ä³¸¯ÅÍ", "ÇÃ·¹ÀÌ¾î1", "·Î±×ÀÎ");
	int loginPlayer2 = INIDATA->loadDataInterger("Ä³¸¯ÅÍ", "ÇÃ·¹ÀÌ¾î2", "·Î±×ÀÎ");

	//Æê ÀÌ¸§ ¶ç¿ì´Â°÷
	HFONT font3 = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY¸ñ°¢ÆÄÀÓB"));
	HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), font3);
	SetBkMode(getMemDC(), TRANSPARENT);

	if (loginPlayer1 == (int)INFO_YES)
	{
		if (_petWindow.isPetNum[0] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[0], _petModeColorG[0], _petModeColorB[0]));
			string petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "ÀÌ¸§");
			TextOut(getMemDC(), _petWindow.petNameRect[0].left, _petWindow.petNameRect[0].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[1] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[1], _petModeColorG[1], _petModeColorB[1]));
			string petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "ÀÌ¸§");
			TextOut(getMemDC(), _petWindow.petNameRect[1].left, _petWindow.petNameRect[1].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[2] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[2], _petModeColorG[2], _petModeColorB[2]));
			string petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "ÀÌ¸§");
			TextOut(getMemDC(), _petWindow.petNameRect[2].left, _petWindow.petNameRect[2].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[3] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[3], _petModeColorG[3], _petModeColorB[3]));
			string petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "ÀÌ¸§");
			TextOut(getMemDC(), _petWindow.petNameRect[3].left, _petWindow.petNameRect[3].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[4] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[4], _petModeColorG[4], _petModeColorB[4]));
			string petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "ÀÌ¸§");
			TextOut(getMemDC(), _petWindow.petNameRect[4].left, _petWindow.petNameRect[4].top, petName.c_str(), strlen(petName.c_str()));
		}
	}

	if (loginPlayer2 == (int)INFO_YES)
	{
		if (_petWindow.isPetNum[0] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[0], _petModeColorG[0], _petModeColorB[0]));
			string petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "ÀÌ¸§");
			TextOut(getMemDC(), _petWindow.petNameRect[0].left, _petWindow.petNameRect[0].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[1] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[1], _petModeColorG[1], _petModeColorB[1]));
			string petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "ÀÌ¸§");
			TextOut(getMemDC(), _petWindow.petNameRect[1].left, _petWindow.petNameRect[1].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[2] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[2], _petModeColorG[2], _petModeColorB[2]));
			string petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "ÀÌ¸§");
			TextOut(getMemDC(), _petWindow.petNameRect[2].left, _petWindow.petNameRect[2].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[3] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[3], _petModeColorG[3], _petModeColorB[3]));
			string petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "ÀÌ¸§");
			TextOut(getMemDC(), _petWindow.petNameRect[3].left, _petWindow.petNameRect[3].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[4] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[4], _petModeColorG[4], _petModeColorB[4]));
			string petName = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "ÀÌ¸§");
			TextOut(getMemDC(), _petWindow.petNameRect[4].left, _petWindow.petNameRect[4].top, petName.c_str(), strlen(petName.c_str()));
		}
	}

	SelectObject(getMemDC(), oldFont3);
	DeleteObject(font3);
	SetBkMode(getMemDC(), OPAQUE);

	//Æê Á¤º¸ ¶ç¿ì´Â°÷
	HFONT font2 = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("¸¼Àº°íµñ"));
	HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), font2);
	SetBkMode(getMemDC(), TRANSPARENT);

	if (loginPlayer1 == (int)INFO_YES)
	{
		if (_petWindow.isPetNum[0] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[0], _petModeColorG[0], _petModeColorB[0]));

			int petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "·¹º§");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 60,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "ÇöÀçÃ¼·Â");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 60,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "ÀüÃ¼Ã¼·Â");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 60,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[1] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[1], _petModeColorG[1], _petModeColorB[1]));

			int petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "·¹º§");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 116,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "ÇöÀçÃ¼·Â");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 116,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "ÀüÃ¼Ã¼·Â");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 116,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[2] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[2], _petModeColorG[2], _petModeColorB[2]));

			int petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "·¹º§");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 172,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "ÇöÀçÃ¼·Â");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 172,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "ÀüÃ¼Ã¼·Â");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 172,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[3] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[3], _petModeColorG[3], _petModeColorB[3]));

			int petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "·¹º§");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 228,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "ÇöÀçÃ¼·Â");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 228,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "ÀüÃ¼Ã¼·Â");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 228,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[4] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[4], _petModeColorG[4], _petModeColorB[4]));

			int petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "·¹º§");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 284,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "ÇöÀçÃ¼·Â");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 284,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "ÀüÃ¼Ã¼·Â");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 284,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}
	}

	if (loginPlayer2 == (int)INFO_YES)
	{
		if (_petWindow.isPetNum[0] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[0], _petModeColorG[0], _petModeColorB[0]));

			int petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "·¹º§");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 60,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "ÇöÀçÃ¼·Â");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 60,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "ÀüÃ¼Ã¼·Â");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 60,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[1] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[1], _petModeColorG[1], _petModeColorB[1]));

			int petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "·¹º§");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 116,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "ÇöÀçÃ¼·Â");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 116,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "ÀüÃ¼Ã¼·Â");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 116,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[2] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[2], _petModeColorG[2], _petModeColorB[2]));

			int petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "·¹º§");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 172,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "ÇöÀçÃ¼·Â");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 172,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "ÀüÃ¼Ã¼·Â");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 172,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[3] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[3], _petModeColorG[3], _petModeColorB[3]));

			int petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "·¹º§");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 228,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "ÇöÀçÃ¼·Â");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 228,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "ÀüÃ¼Ã¼·Â");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 228,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[4] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[4], _petModeColorG[4], _petModeColorB[4]));

			int petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "·¹º§");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 284,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "ÇöÀçÃ¼·Â");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 284,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "ÀüÃ¼Ã¼·Â");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 284,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}
	}

	SelectObject(getMemDC(), oldFont2);
	DeleteObject(font2);
	SetBkMode(getMemDC(), OPAQUE);

	//Æê ¸ðµå ¹öÆ° »óÅÂÃ¢ ÀÌ¸§ ¶ç¿ì´Â°÷

	HFONT font = CreateFont(20, 0, 0, 0, 550, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY¸ñ°¢ÆÄÀÓB"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);

	if (loginPlayer1 == (int)INFO_YES)
	{
		if (_petWindow.isPetNum[0] == true)
		{
			_petWindow.petButtonImg[0]->render(getMemDC(), _petWindow.petButtonRect[0].left, _petWindow.petButtonRect[0].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[0], _petModeColorG[0], _petModeColorB[0]));
			string petMode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "¸ðµå");
			TextOut(getMemDC(), _petWindow.petButtonRect[0].left + 10, _petWindow.petButtonRect[0].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[1] == true)
		{
			_petWindow.petButtonImg[1]->render(getMemDC(), _petWindow.petButtonRect[1].left, _petWindow.petButtonRect[1].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[1], _petModeColorG[1], _petModeColorB[1]));
			string petMode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "¸ðµå");
			TextOut(getMemDC(), _petWindow.petButtonRect[1].left + 10, _petWindow.petButtonRect[1].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[2] == true)
		{
			_petWindow.petButtonImg[2]->render(getMemDC(), _petWindow.petButtonRect[2].left, _petWindow.petButtonRect[2].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[2], _petModeColorG[2], _petModeColorB[2]));
			string petMode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "¸ðµå");
			TextOut(getMemDC(), _petWindow.petButtonRect[2].left + 10, _petWindow.petButtonRect[2].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[3] == true)
		{
			_petWindow.petButtonImg[3]->render(getMemDC(), _petWindow.petButtonRect[3].left, _petWindow.petButtonRect[3].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[3], _petModeColorG[3], _petModeColorB[3]));
			string petMode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "¸ðµå");
			TextOut(getMemDC(), _petWindow.petButtonRect[3].left + 10, _petWindow.petButtonRect[3].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[4] == true)
		{
			_petWindow.petButtonImg[4]->render(getMemDC(), _petWindow.petButtonRect[4].left, _petWindow.petButtonRect[4].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[4], _petModeColorG[4], _petModeColorB[4]));
			string petMode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "¸ðµå");
			TextOut(getMemDC(), _petWindow.petButtonRect[4].left + 10, _petWindow.petButtonRect[4].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

	}

	if (loginPlayer2 == (int)INFO_YES)
	{
		if (_petWindow.isPetNum[0] == true)
		{
			_petWindow.petButtonImg[0]->render(getMemDC(), _petWindow.petButtonRect[0].left, _petWindow.petButtonRect[0].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[0], _petModeColorG[0], _petModeColorB[0]));
			string petMode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "¸ðµå");
			TextOut(getMemDC(), _petWindow.petButtonRect[0].left + 10, _petWindow.petButtonRect[0].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[1] == true)
		{
			_petWindow.petButtonImg[1]->render(getMemDC(), _petWindow.petButtonRect[1].left, _petWindow.petButtonRect[1].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[1], _petModeColorG[1], _petModeColorB[1]));
			string petMode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "¸ðµå");
			TextOut(getMemDC(), _petWindow.petButtonRect[1].left + 10, _petWindow.petButtonRect[1].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[2] == true)
		{
			_petWindow.petButtonImg[2]->render(getMemDC(), _petWindow.petButtonRect[2].left, _petWindow.petButtonRect[2].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[2], _petModeColorG[2], _petModeColorB[2]));
			string petMode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "¸ðµå");
			TextOut(getMemDC(), _petWindow.petButtonRect[2].left + 10, _petWindow.petButtonRect[2].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[3] == true)
		{
			_petWindow.petButtonImg[3]->render(getMemDC(), _petWindow.petButtonRect[3].left, _petWindow.petButtonRect[3].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[3], _petModeColorG[3], _petModeColorB[3]));
			string petMode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "¸ðµå");
			TextOut(getMemDC(), _petWindow.petButtonRect[3].left + 10, _petWindow.petButtonRect[3].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[4] == true)
		{
			_petWindow.petButtonImg[4]->render(getMemDC(), _petWindow.petButtonRect[4].left, _petWindow.petButtonRect[4].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[4], _petModeColorG[4], _petModeColorB[4]));
			string petMode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "¸ðµå");
			TextOut(getMemDC(), _petWindow.petButtonRect[4].left + 10, _petWindow.petButtonRect[4].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

	}

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	SetBkMode(getMemDC(), OPAQUE);
}
