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

	//�����ʹ�ư�� ��������
	if (PtInRect(&_petSkill.rightButtonRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		_petSkill.petInfoCurrentPage++;

		if (_petSkill.petInfoCurrentPage > _petSkill.petInfoMaxPage)
		{
			_petSkill.petInfoCurrentPage = 1;
		}
	}

	//���ʹ�ư�� ��������
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

	//��Ʈ ���콺 �÷����� �ʷϻ��׸���
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
	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	//�� �ƽ�������, ���������� �ҷ�����
	if (loginPlayer1 == (int)INFO_YES)
	{
		string pet1 = INIDATA->loadDataString("�÷��̾�1_��", "��1", "�־�?");
		string pet2 = INIDATA->loadDataString("�÷��̾�1_��", "��2", "�־�?");
		string pet3 = INIDATA->loadDataString("�÷��̾�1_��", "��3", "�־�?");
		string pet4 = INIDATA->loadDataString("�÷��̾�1_��", "��4", "�־�?");
		string pet5 = INIDATA->loadDataString("�÷��̾�1_��", "��5", "�־�?");

		if (pet1 == "�־�") 	_petSkill.petInfoMaxPage = 1;
		if (pet2 == "�־�") 	_petSkill.petInfoMaxPage = 2;
		if (pet3 == "�־�") 	_petSkill.petInfoMaxPage = 3;
		if (pet4 == "�־�") 	_petSkill.petInfoMaxPage = 4;
		if (pet5 == "�־�") 	_petSkill.petInfoMaxPage = 5;

		int petCurrentpage = INIDATA->loadDataInterger("�÷��̾�1_��", "��������", "����������");
		_petSkill.petInfoCurrentPage = petCurrentpage;
	}

	if (loginPlayer2 == (int)INFO_YES)
	{

	}
	

	//�� ���������� Ȯ���ϰ� ������������ �� �̸��� �����������
	if (loginPlayer1 == (int)INFO_YES)
	{
		if (_petSkill.petInfoCurrentPage == 1)
		{
			_petSkill.petName = INIDATA->loadDataString("�÷��̾�1_��", "��1", "�̸�");
			_petSkill.petType = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "����");
			_petSkill.petSkill1 = INIDATA->loadDataString("�÷��̾�1_��", "��1", "��ų1");
			_petSkill.petSkill2 = INIDATA->loadDataString("�÷��̾�1_��", "��1", "��ų2");
			_petSkill.petSkill3 = INIDATA->loadDataString("�÷��̾�1_��", "��1", "��ų3");
			_petSkill.petSkill4 = INIDATA->loadDataString("�÷��̾�1_��", "��1", "��ų4");
			_petSkill.petSkill5 = INIDATA->loadDataString("�÷��̾�1_��", "��1", "��ų5");
			_petSkill.petSkill6 = INIDATA->loadDataString("�÷��̾�1_��", "��1", "��ų6");
		}

		if (_petSkill.petInfoCurrentPage == 2)
		{
			_petSkill.petName = INIDATA->loadDataString("�÷��̾�1_��", "��2", "�̸�");
			_petSkill.petType = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "����");
			_petSkill.petSkill1 = INIDATA->loadDataString("�÷��̾�1_��", "��2", "��ų1");
			_petSkill.petSkill2 = INIDATA->loadDataString("�÷��̾�1_��", "��2", "��ų2");
			_petSkill.petSkill3 = INIDATA->loadDataString("�÷��̾�1_��", "��2", "��ų3");
			_petSkill.petSkill4 = INIDATA->loadDataString("�÷��̾�1_��", "��2", "��ų4");
			_petSkill.petSkill5 = INIDATA->loadDataString("�÷��̾�1_��", "��2", "��ų5");
			_petSkill.petSkill6 = INIDATA->loadDataString("�÷��̾�1_��", "��2", "��ų6");
		}

		if (_petSkill.petInfoCurrentPage == 3)
		{
			_petSkill.petName = INIDATA->loadDataString("�÷��̾�1_��", "��3", "�̸�");
			_petSkill.petType = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "����");
			_petSkill.petSkill1 = INIDATA->loadDataString("�÷��̾�1_��", "��3", "��ų1");
			_petSkill.petSkill2 = INIDATA->loadDataString("�÷��̾�1_��", "��3", "��ų2");
			_petSkill.petSkill3 = INIDATA->loadDataString("�÷��̾�1_��", "��3", "��ų3");
			_petSkill.petSkill4 = INIDATA->loadDataString("�÷��̾�1_��", "��3", "��ų4");
			_petSkill.petSkill5 = INIDATA->loadDataString("�÷��̾�1_��", "��3", "��ų5");
			_petSkill.petSkill6 = INIDATA->loadDataString("�÷��̾�1_��", "��3", "��ų6");
		}

		if (_petSkill.petInfoCurrentPage == 4)
		{
			_petSkill.petName = INIDATA->loadDataString("�÷��̾�1_��", "��4", "�̸�");
			_petSkill.petType = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "����");
			_petSkill.petSkill1 = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "��ų1");
			_petSkill.petSkill2 = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "��ų2");
			_petSkill.petSkill3 = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "��ų3");
			_petSkill.petSkill4 = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "��ų4");
			_petSkill.petSkill5 = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "��ų5");
			_petSkill.petSkill6 = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "��ų6");
		}

		if (_petSkill.petInfoCurrentPage == 5)
		{
			_petSkill.petName = INIDATA->loadDataString("�÷��̾�1_��", "��5", "�̸�");
			_petSkill.petType = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "����");
			_petSkill.petSkill1 = INIDATA->loadDataString("�÷��̾�1_��", "��5", "��ų1");
			_petSkill.petSkill2 = INIDATA->loadDataString("�÷��̾�1_��", "��5", "��ų2");
			_petSkill.petSkill3 = INIDATA->loadDataString("�÷��̾�1_��", "��5", "��ų3");
			_petSkill.petSkill4 = INIDATA->loadDataString("�÷��̾�1_��", "��5", "��ų4");
			_petSkill.petSkill5 = INIDATA->loadDataString("�÷��̾�1_��", "��5", "��ų5");
			_petSkill.petSkill6 = INIDATA->loadDataString("�÷��̾�1_��", "��5", "��ų6");
		}
	}

	if (loginPlayer2 == (int)INFO_YES)
	{
		if (_petSkill.petInfoCurrentPage == 1)
		{
			_petSkill.petName = INIDATA->loadDataString("�÷��̾�2_��", "��1", "�̸�");
			_petSkill.petType = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "����");
			_petSkill.petSkill1 = INIDATA->loadDataString("�÷��̾�2_��", "��1", "��ų1");
			_petSkill.petSkill2 = INIDATA->loadDataString("�÷��̾�2_��", "��1", "��ų2");
			_petSkill.petSkill3 = INIDATA->loadDataString("�÷��̾�2_��", "��1", "��ų3");
			_petSkill.petSkill4 = INIDATA->loadDataString("�÷��̾�2_��", "��1", "��ų4");
			_petSkill.petSkill5 = INIDATA->loadDataString("�÷��̾�2_��", "��1", "��ų5");
			_petSkill.petSkill6 = INIDATA->loadDataString("�÷��̾�2_��", "��1", "��ų6");
		}

		if (_petSkill.petInfoCurrentPage == 2)
		{
			_petSkill.petName = INIDATA->loadDataString("�÷��̾�2_��", "��2", "�̸�");
			_petSkill.petType = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "����");
			_petSkill.petSkill1 = INIDATA->loadDataString("�÷��̾�2_��", "��2", "��ų1");
			_petSkill.petSkill2 = INIDATA->loadDataString("�÷��̾�2_��", "��2", "��ų2");
			_petSkill.petSkill3 = INIDATA->loadDataString("�÷��̾�2_��", "��2", "��ų3");
			_petSkill.petSkill4 = INIDATA->loadDataString("�÷��̾�2_��", "��2", "��ų4");
			_petSkill.petSkill5 = INIDATA->loadDataString("�÷��̾�2_��", "��2", "��ų5");
			_petSkill.petSkill6 = INIDATA->loadDataString("�÷��̾�2_��", "��2", "��ų6");
		}

		if (_petSkill.petInfoCurrentPage == 3)
		{
			_petSkill.petName = INIDATA->loadDataString("�÷��̾�2_��", "��3", "�̸�");
			_petSkill.petType = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "����");
			_petSkill.petSkill1 = INIDATA->loadDataString("�÷��̾�2_��", "��3", "��ų1");
			_petSkill.petSkill2 = INIDATA->loadDataString("�÷��̾�2_��", "��3", "��ų2");
			_petSkill.petSkill3 = INIDATA->loadDataString("�÷��̾�2_��", "��3", "��ų3");
			_petSkill.petSkill4 = INIDATA->loadDataString("�÷��̾�2_��", "��3", "��ų4");
			_petSkill.petSkill5 = INIDATA->loadDataString("�÷��̾�2_��", "��3", "��ų5");
			_petSkill.petSkill6 = INIDATA->loadDataString("�÷��̾�2_��", "��3", "��ų6");
		}

		if (_petSkill.petInfoCurrentPage == 4)
		{
			_petSkill.petName = INIDATA->loadDataString("�÷��̾�2_��", "��4", "�̸�");
			_petSkill.petType = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "����");
			_petSkill.petSkill1 = INIDATA->loadDataString("�÷��̾�2_��", "��4", "��ų1");
			_petSkill.petSkill2 = INIDATA->loadDataString("�÷��̾�2_��", "��4", "��ų2");
			_petSkill.petSkill3 = INIDATA->loadDataString("�÷��̾�2_��", "��4", "��ų3");
			_petSkill.petSkill4 = INIDATA->loadDataString("�÷��̾�2_��", "��4", "��ų4");
			_petSkill.petSkill5 = INIDATA->loadDataString("�÷��̾�2_��", "��4", "��ų5");
			_petSkill.petSkill6 = INIDATA->loadDataString("�÷��̾�2_��", "��4", "��ų6");
		}

		if (_petSkill.petInfoCurrentPage == 5)
		{
			_petSkill.petName = INIDATA->loadDataString("�÷��̾�2_��", "��5", "�̸�");
			_petSkill.petType = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "����");
			_petSkill.petSkill1 = INIDATA->loadDataString("�÷��̾�2_��", "��5", "��ų1");
			_petSkill.petSkill2 = INIDATA->loadDataString("�÷��̾�2_��", "��5", "��ų2");
			_petSkill.petSkill3 = INIDATA->loadDataString("�÷��̾�2_��", "��5", "��ų3");
			_petSkill.petSkill4 = INIDATA->loadDataString("�÷��̾�2_��", "��5", "��ų4");
			_petSkill.petSkill5 = INIDATA->loadDataString("�÷��̾�2_��", "��5", "��ų5");
			_petSkill.petSkill6 = INIDATA->loadDataString("�÷��̾�2_��", "��5", "��ų6");
		}
	}
}

void petSkillWindow::petInfoRender()
{
	//�� �̸� ���°�
	HFONT font3 = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY������B"));
	HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), font3);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 50, CAMERAMANAGER->getCameraTOP() + 35,
		_petSkill.petName.c_str(), strlen(_petSkill.petName.c_str()));

	SelectObject(getMemDC(), oldFont3);
	DeleteObject(font3);
	SetBkMode(getMemDC(), OPAQUE);

	//��ų ���� ���°�
	HFONT font2 = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("�������"));
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
