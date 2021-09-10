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

	//��Ʈ ��� ���� ��Ʈ�� ��������
	for (int i = 0; i < 5; ++i)
	{
		if (PtInRect(&_petWindow.petButtonRect[i], PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
		{
			int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
			int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");
			if (loginPlayer1 == (int)INFO_YES)
			{
				_petWindow.petAvailableRide[0] = INIDATA->loadDataString("�÷��̾�1_��", "��1", "ž�°���");
				_petWindow.petAvailableRide[1] = INIDATA->loadDataString("�÷��̾�1_��", "��2", "ž�°���");
				_petWindow.petAvailableRide[2] = INIDATA->loadDataString("�÷��̾�1_��", "��3", "ž�°���");
				_petWindow.petAvailableRide[3] = INIDATA->loadDataString("�÷��̾�1_��", "��4", "ž�°���");
				_petWindow.petAvailableRide[4] = INIDATA->loadDataString("�÷��̾�1_��", "��5", "ž�°���");
			}
			if (loginPlayer2 == (int)INFO_YES)
			{
				_petWindow.petAvailableRide[0] = INIDATA->loadDataString("�÷��̾�1_��", "��1", "ž�°���");
				_petWindow.petAvailableRide[1] = INIDATA->loadDataString("�÷��̾�1_��", "��2", "ž�°���");
				_petWindow.petAvailableRide[2] = INIDATA->loadDataString("�÷��̾�1_��", "��3", "ž�°���");
				_petWindow.petAvailableRide[3] = INIDATA->loadDataString("�÷��̾�1_��", "��4", "ž�°���");
				_petWindow.petAvailableRide[4] = INIDATA->loadDataString("�÷��̾�1_��", "��5", "ž�°���");
			}
		

			if (_petWindow.petModeName[i] == "��Ʋ")
			{
				_petWindow.petModeName[i] = "���";

				if (i == 0) INIDATA->addData("��1", "���", _petWindow.petModeName[i].c_str());
				if (i == 1) INIDATA->addData("��2", "���", _petWindow.petModeName[i].c_str());
				if (i == 2) INIDATA->addData("��3", "���", _petWindow.petModeName[i].c_str());
				if (i == 3) INIDATA->addData("��4", "���", _petWindow.petModeName[i].c_str());
				if (i == 4) INIDATA->addData("��5", "���", _petWindow.petModeName[i].c_str());

				if (loginPlayer1 == (int)INFO_YES) INIDATA->iniSave("�÷��̾�1_��");
				if (loginPlayer2 == (int)INFO_YES) INIDATA->iniSave("�÷��̾�2_��");

				break;
			}
			
			if (_petWindow.petModeName[i] == "���")
			{
				_petWindow.petModeName[i] = "�޽�";

				if (i == 0) INIDATA->addData("��1", "���", _petWindow.petModeName[i].c_str());
				if (i == 1) INIDATA->addData("��2", "���", _petWindow.petModeName[i].c_str());
				if (i == 2) INIDATA->addData("��3", "���", _petWindow.petModeName[i].c_str());
				if (i == 3) INIDATA->addData("��4", "���", _petWindow.petModeName[i].c_str());
				if (i == 4) INIDATA->addData("��5", "���", _petWindow.petModeName[i].c_str());

				if (loginPlayer1 == (int)INFO_YES) INIDATA->iniSave("�÷��̾�1_��");
				if (loginPlayer2 == (int)INFO_YES) INIDATA->iniSave("�÷��̾�2_��");

				break;
			}

			if (_petWindow.petModeName[i] == "�޽�")
			{
				if (_petWindow.petAvailableRide[i] == "����")
				{
					_petWindow.petModeName[i] = "ž��";
				}

				if (_petWindow.petAvailableRide[i] == "�Ұ���")
				{
					_petWindow.petModeName[i] = "��Ʋ";
				}

				if (i == 0) INIDATA->addData("��1", "���", _petWindow.petModeName[i].c_str());
				if (i == 1) INIDATA->addData("��2", "���", _petWindow.petModeName[i].c_str());
				if (i == 2) INIDATA->addData("��3", "���", _petWindow.petModeName[i].c_str());
				if (i == 3) INIDATA->addData("��4", "���", _petWindow.petModeName[i].c_str());
				if (i == 4) INIDATA->addData("��5", "���", _petWindow.petModeName[i].c_str());

				if (loginPlayer1 == (int)INFO_YES) INIDATA->iniSave("�÷��̾�1_��");
				if (loginPlayer2 == (int)INFO_YES) INIDATA->iniSave("�÷��̾�2_��");

				break;
			}

			if (_petWindow.petModeName[i] == "ž��")
			{
				_petWindow.petModeName[i] = "��Ʋ";

				if (i == 0) INIDATA->addData("��1", "���", _petWindow.petModeName[i].c_str());
				if (i == 1) INIDATA->addData("��2", "���", _petWindow.petModeName[i].c_str());
				if (i == 2) INIDATA->addData("��3", "���", _petWindow.petModeName[i].c_str());
				if (i == 3) INIDATA->addData("��4", "���", _petWindow.petModeName[i].c_str());
				if (i == 4) INIDATA->addData("��5", "���", _petWindow.petModeName[i].c_str());

				if (loginPlayer1 == (int)INFO_YES) INIDATA->iniSave("�÷��̾�1_��");
				if (loginPlayer2 == (int)INFO_YES) INIDATA->iniSave("�÷��̾�2_��");

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
	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	//�÷��̾�1�� �α����������
	if (loginPlayer1 == (int)INFO_YES)
	{
		string pet1 = INIDATA->loadDataString("�÷��̾�1_��", "��1", "�־�?");
		string pet2 = INIDATA->loadDataString("�÷��̾�1_��", "��2", "�־�?");
		string pet3 = INIDATA->loadDataString("�÷��̾�1_��", "��3", "�־�?");
		string pet4 = INIDATA->loadDataString("�÷��̾�1_��", "��4", "�־�?");
		string pet5 = INIDATA->loadDataString("�÷��̾�1_��", "��5", "�־�?");

		if (pet1 == "�־�")
		{
			_petWindow.isPetNum[0] = true;
			_petWindow.petButtonImg[0] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[0] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 54,
				_petWindow.petButtonImg[0]->getWidth(), _petWindow.petButtonImg[0]->getHeight());
			_petWindow.petNameRect[0] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 35,
				80, 18);
			string petModeName = INIDATA->loadDataString("�÷��̾�1_��", "��1", "���");
			_petWindow.petModeName[0] = petModeName;
		}

		if (pet2 == "�־�")
		{
			_petWindow.isPetNum[1] = true;
			_petWindow.petButtonImg[1] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[1] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 111,
				_petWindow.petButtonImg[1]->getWidth(), _petWindow.petButtonImg[1]->getHeight());
			_petWindow.petNameRect[1] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 92,
				80, 18);
			string petModeName = INIDATA->loadDataString("�÷��̾�1_��", "��2", "���");
			_petWindow.petModeName[1] = petModeName;
		}

		if (pet3 == "�־�")
		{
			_petWindow.isPetNum[2] = true;
			_petWindow.petButtonImg[2] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[2] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 168,
				_petWindow.petButtonImg[2]->getWidth(), _petWindow.petButtonImg[2]->getHeight());
			_petWindow.petNameRect[2] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 149,
				80, 18);
			string petModeName = INIDATA->loadDataString("�÷��̾�1_��", "��3", "���");
			_petWindow.petModeName[2] = petModeName;
		}

		if (pet4 == "�־�")
		{
			_petWindow.isPetNum[3] = true;
			_petWindow.petButtonImg[3] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[3] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 225,
				_petWindow.petButtonImg[3]->getWidth(), _petWindow.petButtonImg[3]->getHeight());
			_petWindow.petNameRect[3] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 206,
				80, 18);
			string petModeName = INIDATA->loadDataString("�÷��̾�1_��", "��4", "���");
			_petWindow.petModeName[3] = petModeName;
		}

		if (pet5 == "�־�")
		{
			_petWindow.isPetNum[4] = true;
			_petWindow.petButtonImg[4] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[4] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 282,
				_petWindow.petButtonImg[4]->getWidth(), _petWindow.petButtonImg[4]->getHeight());
			_petWindow.petNameRect[4] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 263,
				80, 18);
			string petModeName = INIDATA->loadDataString("�÷��̾�1_��", "��5", "���");
			_petWindow.petModeName[4] = petModeName;
		}
	}

	//�÷��̾�2�� �α����������
	if (loginPlayer2 == (int)INFO_YES)
	{
		string pet1 = INIDATA->loadDataString("�÷��̾�2_��", "��1", "�־�?");
		string pet2 = INIDATA->loadDataString("�÷��̾�2_��", "��2", "�־�?");
		string pet3 = INIDATA->loadDataString("�÷��̾�2_��", "��3", "�־�?");
		string pet4 = INIDATA->loadDataString("�÷��̾�2_��", "��4", "�־�?");
		string pet5 = INIDATA->loadDataString("�÷��̾�2_��", "��5", "�־�?");

		if (pet1 == "�־�")
		{
			_petWindow.isPetNum[0] = true;
			_petWindow.petButtonImg[0] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[0] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 54,
				_petWindow.petButtonImg[0]->getWidth(), _petWindow.petButtonImg[0]->getHeight());
			_petWindow.petNameRect[0] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 35,
				80, 18);
			string petModeName = INIDATA->loadDataString("�÷��̾�2_��", "��1", "���");
			_petWindow.petModeName[0] = petModeName;
		}

		if (pet2 == "�־�")
		{
			_petWindow.isPetNum[1] = true;
			_petWindow.petButtonImg[1] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[1] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 111,
				_petWindow.petButtonImg[1]->getWidth(), _petWindow.petButtonImg[1]->getHeight());
			_petWindow.petNameRect[1] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 92,
				80, 18);
			string petModeName = INIDATA->loadDataString("�÷��̾�2_��", "��2", "���");
			_petWindow.petModeName[1] = petModeName;
		}

		if (pet3 == "�־�")
		{
			_petWindow.isPetNum[2] = true;
			_petWindow.petButtonImg[2] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[2] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 168,
				_petWindow.petButtonImg[2]->getWidth(), _petWindow.petButtonImg[2]->getHeight());
			_petWindow.petNameRect[2] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 149,
				80, 18);
			string petModeName = INIDATA->loadDataString("�÷��̾�2_��", "��3", "���");
			_petWindow.petModeName[2] = petModeName;
		}

		if (pet4 == "�־�")
		{
			_petWindow.isPetNum[3] = true;
			_petWindow.petButtonImg[3] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[3] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 225,
				_petWindow.petButtonImg[3]->getWidth(), _petWindow.petButtonImg[3]->getHeight());
			_petWindow.petNameRect[3] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 206,
				80, 18);
			string petModeName = INIDATA->loadDataString("�÷��̾�2_��", "��4", "���");
			_petWindow.petModeName[3] = petModeName;
		}

		if (pet5 == "�־�")
		{
			_petWindow.isPetNum[4] = true;
			_petWindow.petButtonImg[4] = IMAGEMANAGER->findImage("petButton");
			_petWindow.petButtonRect[4] = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 43, CAMERAMANAGER->getCameraTOP() + 282,
				_petWindow.petButtonImg[4]->getWidth(), _petWindow.petButtonImg[4]->getHeight());
			_petWindow.petNameRect[4] = RectMake(CAMERAMANAGER->getCameraLEFT() + 100, CAMERAMANAGER->getCameraTOP() + 263,
				80, 18);
			string petModeName = INIDATA->loadDataString("�÷��̾�2_��", "��5", "���");
			_petWindow.petModeName[4] = petModeName;
		}
	}
}

void petWindow::petInfoRender()
{
	//�켱 RGB  ����
	for (int i = 0; i < 5; ++i)
	{
		if (_petWindow.petModeName[i] == "��Ʋ")
		{
			_petModeColorR[i] = 255;
			_petModeColorG[i] = 255;
			_petModeColorB[i] = 0;
		}

		if (_petWindow.petModeName[i] == "���")
		{
			_petModeColorR[i] = 0;
			_petModeColorG[i] = 255;
			_petModeColorB[i] = 255;
		}

		if (_petWindow.petModeName[i] == "�޽�")
		{
			_petModeColorR[i] = 255;
			_petModeColorG[i] = 255;
			_petModeColorB[i] = 255;
		}

		if (_petWindow.petModeName[i] == "ž��")
		{
			_petModeColorR[i] = 0;
			_petModeColorG[i] = 255;
			_petModeColorB[i] = 0;
		}
	}

	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	//�� �̸� ���°�
	HFONT font3 = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY������B"));
	HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), font3);
	SetBkMode(getMemDC(), TRANSPARENT);

	if (loginPlayer1 == (int)INFO_YES)
	{
		if (_petWindow.isPetNum[0] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[0], _petModeColorG[0], _petModeColorB[0]));
			string petName = INIDATA->loadDataString("�÷��̾�1_��", "��1", "�̸�");
			TextOut(getMemDC(), _petWindow.petNameRect[0].left, _petWindow.petNameRect[0].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[1] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[1], _petModeColorG[1], _petModeColorB[1]));
			string petName = INIDATA->loadDataString("�÷��̾�1_��", "��2", "�̸�");
			TextOut(getMemDC(), _petWindow.petNameRect[1].left, _petWindow.petNameRect[1].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[2] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[2], _petModeColorG[2], _petModeColorB[2]));
			string petName = INIDATA->loadDataString("�÷��̾�1_��", "��3", "�̸�");
			TextOut(getMemDC(), _petWindow.petNameRect[2].left, _petWindow.petNameRect[2].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[3] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[3], _petModeColorG[3], _petModeColorB[3]));
			string petName = INIDATA->loadDataString("�÷��̾�1_��", "��4", "�̸�");
			TextOut(getMemDC(), _petWindow.petNameRect[3].left, _petWindow.petNameRect[3].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[4] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[4], _petModeColorG[4], _petModeColorB[4]));
			string petName = INIDATA->loadDataString("�÷��̾�1_��", "��5", "�̸�");
			TextOut(getMemDC(), _petWindow.petNameRect[4].left, _petWindow.petNameRect[4].top, petName.c_str(), strlen(petName.c_str()));
		}
	}

	if (loginPlayer2 == (int)INFO_YES)
	{
		if (_petWindow.isPetNum[0] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[0], _petModeColorG[0], _petModeColorB[0]));
			string petName = INIDATA->loadDataString("�÷��̾�2_��", "��1", "�̸�");
			TextOut(getMemDC(), _petWindow.petNameRect[0].left, _petWindow.petNameRect[0].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[1] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[1], _petModeColorG[1], _petModeColorB[1]));
			string petName = INIDATA->loadDataString("�÷��̾�2_��", "��2", "�̸�");
			TextOut(getMemDC(), _petWindow.petNameRect[1].left, _petWindow.petNameRect[1].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[2] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[2], _petModeColorG[2], _petModeColorB[2]));
			string petName = INIDATA->loadDataString("�÷��̾�2_��", "��3", "�̸�");
			TextOut(getMemDC(), _petWindow.petNameRect[2].left, _petWindow.petNameRect[2].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[3] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[3], _petModeColorG[3], _petModeColorB[3]));
			string petName = INIDATA->loadDataString("�÷��̾�2_��", "��4", "�̸�");
			TextOut(getMemDC(), _petWindow.petNameRect[3].left, _petWindow.petNameRect[3].top, petName.c_str(), strlen(petName.c_str()));
		}

		if (_petWindow.isPetNum[4] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[4], _petModeColorG[4], _petModeColorB[4]));
			string petName = INIDATA->loadDataString("�÷��̾�2_��", "��5", "�̸�");
			TextOut(getMemDC(), _petWindow.petNameRect[4].left, _petWindow.petNameRect[4].top, petName.c_str(), strlen(petName.c_str()));
		}
	}

	SelectObject(getMemDC(), oldFont3);
	DeleteObject(font3);
	SetBkMode(getMemDC(), OPAQUE);

	//�� ���� ���°�
	HFONT font2 = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("�������"));
	HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), font2);
	SetBkMode(getMemDC(), TRANSPARENT);

	if (loginPlayer1 == (int)INFO_YES)
	{
		if (_petWindow.isPetNum[0] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[0], _petModeColorG[0], _petModeColorB[0]));

			int petLevel = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "����");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 60,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "����ü��");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 60,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "��üü��");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 60,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[1] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[1], _petModeColorG[1], _petModeColorB[1]));

			int petLevel = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "����");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 116,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "����ü��");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 116,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "��üü��");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 116,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[2] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[2], _petModeColorG[2], _petModeColorB[2]));

			int petLevel = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "����");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 172,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "����ü��");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 172,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "��üü��");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 172,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[3] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[3], _petModeColorG[3], _petModeColorB[3]));

			int petLevel = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "����");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 228,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "����ü��");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 228,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "��üü��");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 228,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[4] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[4], _petModeColorG[4], _petModeColorB[4]));

			int petLevel = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "����");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 284,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "����ü��");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 284,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "��üü��");
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

			int petLevel = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "����");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 60,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "����ü��");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 60,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "��üü��");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 60,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[1] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[1], _petModeColorG[1], _petModeColorB[1]));

			int petLevel = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "����");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 116,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "����ü��");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 116,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "��üü��");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 116,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[2] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[2], _petModeColorG[2], _petModeColorB[2]));

			int petLevel = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "����");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 172,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "����ü��");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 172,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "��üü��");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 172,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[3] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[3], _petModeColorG[3], _petModeColorB[3]));

			int petLevel = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "����");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 228,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "����ü��");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 228,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "��üü��");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 228,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}

		if (_petWindow.isPetNum[4] == true)
		{
			SetTextColor(getMemDC(), RGB(_petModeColorR[4], _petModeColorG[4], _petModeColorB[4]));

			int petLevel = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "����");
			char level[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 128, CAMERAMANAGER->getCameraTOP() + 284,
				_itoa(petLevel, level, 10), strlen(_itoa(petLevel, level, 10)));

			int petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "����ü��");
			char currentStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 195, CAMERAMANAGER->getCameraTOP() + 284,
				_itoa(petCurrentStamina, currentStamina, 10), strlen(_itoa(petCurrentStamina, currentStamina, 10)));

			int petTotalStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "��üü��");
			char totalStamina[256];
			TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 255, CAMERAMANAGER->getCameraTOP() + 284,
				_itoa(petTotalStamina, totalStamina, 10), strlen(_itoa(petTotalStamina, totalStamina, 10)));
		}
	}

	SelectObject(getMemDC(), oldFont2);
	DeleteObject(font2);
	SetBkMode(getMemDC(), OPAQUE);

	//�� ��� ��ư ����â �̸� ���°�

	HFONT font = CreateFont(20, 0, 0, 0, 550, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY������B"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);

	if (loginPlayer1 == (int)INFO_YES)
	{
		if (_petWindow.isPetNum[0] == true)
		{
			_petWindow.petButtonImg[0]->render(getMemDC(), _petWindow.petButtonRect[0].left, _petWindow.petButtonRect[0].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[0], _petModeColorG[0], _petModeColorB[0]));
			string petMode = INIDATA->loadDataString("�÷��̾�1_��", "��1", "���");
			TextOut(getMemDC(), _petWindow.petButtonRect[0].left + 10, _petWindow.petButtonRect[0].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[1] == true)
		{
			_petWindow.petButtonImg[1]->render(getMemDC(), _petWindow.petButtonRect[1].left, _petWindow.petButtonRect[1].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[1], _petModeColorG[1], _petModeColorB[1]));
			string petMode = INIDATA->loadDataString("�÷��̾�1_��", "��2", "���");
			TextOut(getMemDC(), _petWindow.petButtonRect[1].left + 10, _petWindow.petButtonRect[1].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[2] == true)
		{
			_petWindow.petButtonImg[2]->render(getMemDC(), _petWindow.petButtonRect[2].left, _petWindow.petButtonRect[2].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[2], _petModeColorG[2], _petModeColorB[2]));
			string petMode = INIDATA->loadDataString("�÷��̾�1_��", "��3", "���");
			TextOut(getMemDC(), _petWindow.petButtonRect[2].left + 10, _petWindow.petButtonRect[2].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[3] == true)
		{
			_petWindow.petButtonImg[3]->render(getMemDC(), _petWindow.petButtonRect[3].left, _petWindow.petButtonRect[3].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[3], _petModeColorG[3], _petModeColorB[3]));
			string petMode = INIDATA->loadDataString("�÷��̾�1_��", "��4", "���");
			TextOut(getMemDC(), _petWindow.petButtonRect[3].left + 10, _petWindow.petButtonRect[3].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[4] == true)
		{
			_petWindow.petButtonImg[4]->render(getMemDC(), _petWindow.petButtonRect[4].left, _petWindow.petButtonRect[4].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[4], _petModeColorG[4], _petModeColorB[4]));
			string petMode = INIDATA->loadDataString("�÷��̾�1_��", "��5", "���");
			TextOut(getMemDC(), _petWindow.petButtonRect[4].left + 10, _petWindow.petButtonRect[4].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

	}

	if (loginPlayer2 == (int)INFO_YES)
	{
		if (_petWindow.isPetNum[0] == true)
		{
			_petWindow.petButtonImg[0]->render(getMemDC(), _petWindow.petButtonRect[0].left, _petWindow.petButtonRect[0].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[0], _petModeColorG[0], _petModeColorB[0]));
			string petMode = INIDATA->loadDataString("�÷��̾�2_��", "��1", "���");
			TextOut(getMemDC(), _petWindow.petButtonRect[0].left + 10, _petWindow.petButtonRect[0].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[1] == true)
		{
			_petWindow.petButtonImg[1]->render(getMemDC(), _petWindow.petButtonRect[1].left, _petWindow.petButtonRect[1].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[1], _petModeColorG[1], _petModeColorB[1]));
			string petMode = INIDATA->loadDataString("�÷��̾�2_��", "��2", "���");
			TextOut(getMemDC(), _petWindow.petButtonRect[1].left + 10, _petWindow.petButtonRect[1].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[2] == true)
		{
			_petWindow.petButtonImg[2]->render(getMemDC(), _petWindow.petButtonRect[2].left, _petWindow.petButtonRect[2].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[2], _petModeColorG[2], _petModeColorB[2]));
			string petMode = INIDATA->loadDataString("�÷��̾�2_��", "��3", "���");
			TextOut(getMemDC(), _petWindow.petButtonRect[2].left + 10, _petWindow.petButtonRect[2].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[3] == true)
		{
			_petWindow.petButtonImg[3]->render(getMemDC(), _petWindow.petButtonRect[3].left, _petWindow.petButtonRect[3].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[3], _petModeColorG[3], _petModeColorB[3]));
			string petMode = INIDATA->loadDataString("�÷��̾�2_��", "��4", "���");
			TextOut(getMemDC(), _petWindow.petButtonRect[3].left + 10, _petWindow.petButtonRect[3].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

		if (_petWindow.isPetNum[4] == true)
		{
			_petWindow.petButtonImg[4]->render(getMemDC(), _petWindow.petButtonRect[4].left, _petWindow.petButtonRect[4].top);

			SetTextColor(getMemDC(), RGB(_petModeColorR[4], _petModeColorG[4], _petModeColorB[4]));
			string petMode = INIDATA->loadDataString("�÷��̾�2_��", "��5", "���");
			TextOut(getMemDC(), _petWindow.petButtonRect[4].left + 10, _petWindow.petButtonRect[4].top + 2, petMode.c_str(), strlen(petMode.c_str()));
		}

	}

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	SetBkMode(getMemDC(), OPAQUE);
}
