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

	//��ų������ ��������
	if (PtInRect(&_petInfo.skiilRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
		int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");
		char petPage[256];

		if (loginPlayer1 == (int)INFO_YES)
		{
			INIDATA->addData("��������", "����������", _itoa(_petInfo.petInfoCurrentPage, petPage, 10));
			INIDATA->iniSave("�÷��̾�1_��");
		}

		if (loginPlayer2 == (int)INFO_YES)
		{
			INIDATA->addData("��������", "����������", _itoa(_petInfo.petInfoCurrentPage, petPage, 10));
			INIDATA->iniSave("�÷��̾�2_��");
		}
		SOUNDMANAGER->play("window_up", 0.4f);
		return new petSkillWindow();
	}

	//�����ʹ�ư�� ��������
	if (PtInRect(&_petInfo.rightButtonRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		_petInfo.petInfoCurrentPage++;

		if (_petInfo.petInfoCurrentPage > _petInfo.petInfoMaxPage)
		{
			_petInfo.petInfoCurrentPage = 1;
		}
	}

	//���ʹ�ư�� ��������
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

	//��Ʈ ���콺 �÷����� �ʷϻ��׸���
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
	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	//��ü����������
	if (loginPlayer1 == (int)INFO_YES)
	{
		string pet1 = INIDATA->loadDataString("�÷��̾�1_��", "��1", "�־�?");
		string pet2 = INIDATA->loadDataString("�÷��̾�1_��", "��2", "�־�?");
		string pet3 = INIDATA->loadDataString("�÷��̾�1_��", "��3", "�־�?");
		string pet4 = INIDATA->loadDataString("�÷��̾�1_��", "��4", "�־�?");
		string pet5 = INIDATA->loadDataString("�÷��̾�1_��", "��5", "�־�?");

		if (pet1 == "�־�") 	_petInfo.petInfoMaxPage = 1;
		if (pet2 == "�־�") 	_petInfo.petInfoMaxPage = 2;
		if (pet3 == "�־�") 	_petInfo.petInfoMaxPage = 3;
		if (pet4 == "�־�") 	_petInfo.petInfoMaxPage = 4;
		if (pet5 == "�־�") 	_petInfo.petInfoMaxPage = 5;
	}

	if (loginPlayer2 == (int)INFO_YES)
	{
		string pet1 = INIDATA->loadDataString("�÷��̾�2_��", "��1", "�־�?");
		string pet2 = INIDATA->loadDataString("�÷��̾�2_��", "��2", "�־�?");
		string pet3 = INIDATA->loadDataString("�÷��̾�2_��", "��3", "�־�?");
		string pet4 = INIDATA->loadDataString("�÷��̾�2_��", "��4", "�־�?");
		string pet5 = INIDATA->loadDataString("�÷��̾�2_��", "��5", "�־�?");

		if (pet1 == "�־�") 	_petInfo.petInfoMaxPage = 1;
		if (pet2 == "�־�") 	_petInfo.petInfoMaxPage = 2;
		if (pet3 == "�־�") 	_petInfo.petInfoMaxPage = 3;
		if (pet4 == "�־�") 	_petInfo.petInfoMaxPage = 4;
		if (pet5 == "�־�") 	_petInfo.petInfoMaxPage = 5;
	}

	//������â �ҷ�����
	if (loginPlayer1 == (int)INFO_YES)
	{
		if (_petInfo.petInfoCurrentPage == 1)
		{
			_petInfo.petName = INIDATA->loadDataString("�÷��̾�1_��", "��1", "�̸�");
			_petInfo.petType = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "����");
			_petInfo.petLevel = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "����");
			_petInfo.currentEXP = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "�������ġ");
			_petInfo.nextEXP = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "��������ġ");
			_petInfo.currentStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "����ü��");
			_petInfo.totalStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "��üü��");
			_petInfo.attackPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "���ݷ�");
			_petInfo.defensePower = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "����");
			_petInfo.speedPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "���߷�");
			_petInfo.loyality = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "�漺��");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "���Ӽ�");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "���Ӽ�");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "ȭ�Ӽ�");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "ǳ�Ӽ�");
		}

		if (_petInfo.petInfoCurrentPage == 2)
		{
			_petInfo.petName = INIDATA->loadDataString("�÷��̾�1_��", "��2", "�̸�");
			_petInfo.petType = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "����");
			_petInfo.petLevel = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "����");
			_petInfo.currentEXP = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "�������ġ");
			_petInfo.nextEXP = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "��������ġ");
			_petInfo.currentStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "����ü��");
			_petInfo.totalStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "��üü��");
			_petInfo.attackPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "���ݷ�");
			_petInfo.defensePower = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "����");
			_petInfo.speedPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "���߷�");
			_petInfo.loyality = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "�漺��");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "���Ӽ�");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "���Ӽ�");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "ȭ�Ӽ�");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "ǳ�Ӽ�");
		}

		if (_petInfo.petInfoCurrentPage == 3)
		{
			_petInfo.petName = INIDATA->loadDataString("�÷��̾�1_��", "��3", "�̸�");
			_petInfo.petType = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "����");
			_petInfo.petLevel = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "����");
			_petInfo.currentEXP = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "�������ġ");
			_petInfo.nextEXP = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "��������ġ");
			_petInfo.currentStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "����ü��");
			_petInfo.totalStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "��üü��");
			_petInfo.attackPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "���ݷ�");
			_petInfo.defensePower = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "����");
			_petInfo.speedPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "���߷�");
			_petInfo.loyality = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "�漺��");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "���Ӽ�");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "���Ӽ�");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "ȭ�Ӽ�");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "ǳ�Ӽ�");
		}

		if (_petInfo.petInfoCurrentPage == 4)
		{
			_petInfo.petName = INIDATA->loadDataString("�÷��̾�1_��", "��4", "�̸�");
			_petInfo.petType = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "����");
			_petInfo.petLevel = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "����");
			_petInfo.currentEXP = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "�������ġ");
			_petInfo.nextEXP = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "��������ġ");
			_petInfo.currentStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "����ü��");
			_petInfo.totalStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "��üü��");
			_petInfo.attackPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "���ݷ�");
			_petInfo.defensePower = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "����");
			_petInfo.speedPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "���߷�");
			_petInfo.loyality = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "�漺��");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "���Ӽ�");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "���Ӽ�");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "ȭ�Ӽ�");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "ǳ�Ӽ�");
		}

		if (_petInfo.petInfoCurrentPage == 5)
		{
			_petInfo.petName = INIDATA->loadDataString("�÷��̾�1_��", "��5", "�̸�");
			_petInfo.petType = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "����");
			_petInfo.petLevel = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "����");
			_petInfo.currentEXP = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "�������ġ");
			_petInfo.nextEXP = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "��������ġ");
			_petInfo.currentStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "����ü��");
			_petInfo.totalStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "��üü��");
			_petInfo.attackPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "���ݷ�");
			_petInfo.defensePower = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "����");
			_petInfo.speedPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "���߷�");
			_petInfo.loyality = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "�漺��");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "���Ӽ�");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "���Ӽ�");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "ȭ�Ӽ�");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "ǳ�Ӽ�");
		}
	}

	if (loginPlayer2 == (int)INFO_YES)
	{
		if (_petInfo.petInfoCurrentPage == 1)
		{
			_petInfo.petName = INIDATA->loadDataString("�÷��̾�2_��", "��1", "�̸�");
			_petInfo.petType = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "����");
			_petInfo.petLevel = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "����");
			_petInfo.currentEXP = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "�������ġ");
			_petInfo.nextEXP = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "��������ġ");
			_petInfo.currentStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "����ü��");
			_petInfo.totalStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "��üü��");
			_petInfo.attackPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "���ݷ�");
			_petInfo.defensePower = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "����");
			_petInfo.speedPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "���߷�");
			_petInfo.loyality = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "�漺��");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "���Ӽ�");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "���Ӽ�");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "ȭ�Ӽ�");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "ǳ�Ӽ�");
		}

		if (_petInfo.petInfoCurrentPage == 2)
		{
			_petInfo.petName = INIDATA->loadDataString("�÷��̾�2_��", "��2", "�̸�");
			_petInfo.petType = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "����");
			_petInfo.petLevel = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "����");
			_petInfo.currentEXP = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "�������ġ");
			_petInfo.nextEXP = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "��������ġ");
			_petInfo.currentStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "����ü��");
			_petInfo.totalStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "��üü��");
			_petInfo.attackPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "���ݷ�");
			_petInfo.defensePower = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "����");
			_petInfo.speedPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "���߷�");
			_petInfo.loyality = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "�漺��");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "���Ӽ�");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "���Ӽ�");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "ȭ�Ӽ�");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "ǳ�Ӽ�");
		}

		if (_petInfo.petInfoCurrentPage == 3)
		{
			_petInfo.petName = INIDATA->loadDataString("�÷��̾�2_��", "��3", "�̸�");
			_petInfo.petType = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "����");
			_petInfo.petLevel = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "����");
			_petInfo.currentEXP = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "�������ġ");
			_petInfo.nextEXP = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "��������ġ");
			_petInfo.currentStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "����ü��");
			_petInfo.totalStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "��üü��");
			_petInfo.attackPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "���ݷ�");
			_petInfo.defensePower = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "����");
			_petInfo.speedPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "���߷�");
			_petInfo.loyality = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "�漺��");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "���Ӽ�");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "���Ӽ�");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "ȭ�Ӽ�");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "ǳ�Ӽ�");
		}

		if (_petInfo.petInfoCurrentPage == 4)
		{
			_petInfo.petName = INIDATA->loadDataString("�÷��̾�2_��", "��4", "�̸�");
			_petInfo.petType = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "����");
			_petInfo.petLevel = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "����");
			_petInfo.currentEXP = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "�������ġ");
			_petInfo.nextEXP = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "��������ġ");
			_petInfo.currentStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "����ü��");
			_petInfo.totalStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "��üü��");
			_petInfo.attackPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "���ݷ�");
			_petInfo.defensePower = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "����");
			_petInfo.speedPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "���߷�");
			_petInfo.loyality = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "�漺��");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "���Ӽ�");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "���Ӽ�");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "ȭ�Ӽ�");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "ǳ�Ӽ�");
		}

		if (_petInfo.petInfoCurrentPage == 5)
		{
			_petInfo.petName = INIDATA->loadDataString("�÷��̾�2_��", "��5", "�̸�");
			_petInfo.petType = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "����");
			_petInfo.petLevel = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "����");
			_petInfo.currentEXP = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "�������ġ");
			_petInfo.nextEXP = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "��������ġ");
			_petInfo.currentStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "����ü��");
			_petInfo.totalStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "��üü��");
			_petInfo.attackPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "���ݷ�");
			_petInfo.defensePower = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "����");
			_petInfo.speedPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "���߷�");
			_petInfo.loyality = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "�漺��");

			_petInfo.attributeLandCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "���Ӽ�");
			_petInfo.attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "���Ӽ�");
			_petInfo.attributeFireCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "ȭ�Ӽ�");
			_petInfo.attributeWindCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "ǳ�Ӽ�");
		}
	}

	//���̹����ҷ�����
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

	//���Ӽ�
	for (int i = 0; i < _petInfo.attributeLandCount; ++i)
	{
		_arrayAttributeLand[i].img = IMAGEMANAGER->findImage("playerAttribute");
		_arrayAttributeLand[i].rc = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 363 + i * 8, CAMERAMANAGER->getCameraTOP() + 217,
			8, 12);
		_arrayAttributeLand[i].currentFrameX = 2;
		_arrayAttributeLand[i].currentFrameY = 0;
	}

	//���Ӽ�
	for (int i = 0; i < _petInfo.attributeWaterCount; ++i)
	{
		_arrayAttributeWater[i].img = IMAGEMANAGER->findImage("playerAttribute");
		_arrayAttributeWater[i].rc = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 363 + i * 8, CAMERAMANAGER->getCameraTOP() + 245,
			8, 12);
		_arrayAttributeWater[i].currentFrameX = 0;
		_arrayAttributeWater[i].currentFrameY = 0;
	}

	//ȭ�Ӽ�
	for (int i = 0; i < _petInfo.attributeFireCount; ++i)
	{
		_arrayAttributeFire[i].img = IMAGEMANAGER->findImage("playerAttribute");
		_arrayAttributeFire[i].rc = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + 363 + i * 8, CAMERAMANAGER->getCameraTOP() + 273,
			8, 12);
		_arrayAttributeFire[i].currentFrameX = 1;
		_arrayAttributeFire[i].currentFrameY = 0;
	}

	//ǳ�Ӽ�
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
	//�� �̸� ���°�
	HFONT font3 = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY������B"));
	HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), font3);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 60, CAMERAMANAGER->getCameraTOP() + 40,
		_petInfo.petName.c_str(), strlen(_petInfo.petName.c_str()));
	
	SelectObject(getMemDC(), oldFont3);
	DeleteObject(font3);
	SetBkMode(getMemDC(), OPAQUE);

	//�� ���� ���°�
	HFONT font2 = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("�������"));
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

	//���Ӽ�
	for (int i = 0; i < _petInfo.attributeLandCount; ++i)
	{
		_arrayAttributeLand[i].img->frameRender(getMemDC(), _arrayAttributeLand[i].rc.left, _arrayAttributeLand[i].rc.top,
			_arrayAttributeLand[i].currentFrameX, _arrayAttributeLand[i].currentFrameY);
	}

	//���Ӽ�
	for (int i = 0; i < _petInfo.attributeWaterCount; ++i)
	{
		_arrayAttributeWater[i].img->frameRender(getMemDC(), _arrayAttributeWater[i].rc.left, _arrayAttributeWater[i].rc.top,
			_arrayAttributeWater[i].currentFrameX, _arrayAttributeWater[i].currentFrameY);
	}

	//ȭ�Ӽ�
	for (int i = 0; i < _petInfo.attributeFireCount; ++i)
	{
		_arrayAttributeFire[i].img->frameRender(getMemDC(), _arrayAttributeFire[i].rc.left, _arrayAttributeFire[i].rc.top,
			_arrayAttributeFire[i].currentFrameX, _arrayAttributeFire[i].currentFrameY);
	}

	//ǳ�Ӽ�
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
