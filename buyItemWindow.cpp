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

menuType * buyItemWindow::inputHandle(tileMap * tileMap)
{
	clickPage(tileMap);
	clickItem(tileMap);

	if (tileMap->_isClickArmorNPC == false && tileMap->_isClickWeaponNPC == false)
	{
		exit(tileMap);
		SOUNDMANAGER->play("window_down", 0.4f);
		return new baseType();
	}

	if (PtInRect(&_buyWindow.returnRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(false);
		tileMap->setIsPosibleClick(false);
		tileMap->setDelayClickCount(0);
		exit(tileMap);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new shopWindow();
	}


	return nullptr;
}

void buyItemWindow::update(tileMap * tileMap)
{
	updateButton(tileMap);
	updateItem(tileMap);

	if (PtInRect(&_buyWindow.frontRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(true);
	}

	else tileMap->setIsMouseOnPet(false);

	//�����ӻ��°��Ǹ� ��ǲ�ڵ�ٽ��ѹ��� ���Բ�
	if (tileMap->getIsPlayerMove() == true)
	{
		tileMap->_isClickArmorNPC = false;
		tileMap->_isClickWeaponNPC = false;
		tileMap->InputHandle();
	}

	//�����ð� ������ �ٽ� ��ư�������ְ��ϱ�
	if (_noticeWindow.isShortageMoney == false && _noticeWindow.isClickItem == false &&
		_isDisableClick == true)
	{
		_ableCount++;

		if (_ableCount >= 4)
		{
			_ableCount = 0;
			_isDisableClick = false;
		}
	}
}

void buyItemWindow::enter(tileMap * tileMap)
{
	writeInidata(tileMap);
	_buyWindow.frontImg = IMAGEMANAGER->findImage("shopWindow");
	_buyWindow.backImg = IMAGEMANAGER->findImage("shopWindowBack");
	_buyWindow.leftButton.img = IMAGEMANAGER->findImage("leftButton");
	_buyWindow.rightButton.img = IMAGEMANAGER->findImage("rightButton");
	_buyWindow.leftButton.currentFrameX = 0;
	_buyWindow.leftButton.currentFrameY = 0;
	_buyWindow.leftButton.timeCount = 0;
	_buyWindow.rightButton.currentFrameX = 0;
	_buyWindow.rightButton.currentFrameY = 0;
	_buyWindow.rightButton.timeCount = 0;
	_buyWindow.currentPage = 1;
	_buyWindow.maxPage = 2;
	_ableCount = 0;
	_isDisableClick = false;

	_noticeWindow.isShortageMoney = false;
	_noticeWindow.isClickItem = false;

	setItem(tileMap);

}

void buyItemWindow::render(tileMap * tileMap)
{
	imageRender(tileMap);
	textRender(tileMap);
	noticeRender(tileMap);
	PtInRender(tileMap);
}

void buyItemWindow::exit(tileMap * tileMap)
{
	for (int i = 0; i < 3; ++i)
	{
		SAFE_RELEASE(_pageOneItem[i]);
		SAFE_DELETE(_pageOneItem[i]);
		SAFE_RELEASE(_pageTwoItem[i]);
		SAFE_DELETE(_pageTwoItem[i]);
	}
}

void buyItemWindow::writeInidata(tileMap * tileMap)
{
	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	if (loginPlayer1 == (int)INFO_YES)
	{
		_buyWindow.playerStone = INIDATA->loadDataInterger("�÷��̾�1_������", "������", "�ݾ�");
	}

	if (loginPlayer2 == (int)INFO_YES)
	{
		_buyWindow.playerStone = INIDATA->loadDataInterger("�÷��̾�2_������", "������", "�ݾ�");
	}
}

void buyItemWindow::saveInidata(tileMap * tileMap)
{
	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	//�÷��̾�1�� �α����������
	if (loginPlayer1 == (int)INFO_YES)
	{
		int playerItem[15];
		char itemName[256];
		char itemNum[256];

		playerItem[0] = INIDATA->loadDataInterger("�÷��̾�1_������", "������1", "����");
		playerItem[1] = INIDATA->loadDataInterger("�÷��̾�1_������", "������2", "����");
		playerItem[2] = INIDATA->loadDataInterger("�÷��̾�1_������", "������3", "����");
		playerItem[3] = INIDATA->loadDataInterger("�÷��̾�1_������", "������4", "����");
		playerItem[4] = INIDATA->loadDataInterger("�÷��̾�1_������", "������5", "����");
		playerItem[5] = INIDATA->loadDataInterger("�÷��̾�1_������", "������6", "����");
		playerItem[6] = INIDATA->loadDataInterger("�÷��̾�1_������", "������7", "����");
		playerItem[7] = INIDATA->loadDataInterger("�÷��̾�1_������", "������8", "����");
		playerItem[8] = INIDATA->loadDataInterger("�÷��̾�1_������", "������9", "����");
		playerItem[9] = INIDATA->loadDataInterger("�÷��̾�1_������", "������10", "����");
		playerItem[10] = INIDATA->loadDataInterger("�÷��̾�1_������", "������11", "����");
		playerItem[11] = INIDATA->loadDataInterger("�÷��̾�1_������", "������12", "����");
		playerItem[12] = INIDATA->loadDataInterger("�÷��̾�1_������", "������13", "����");
		playerItem[13] = INIDATA->loadDataInterger("�÷��̾�1_������", "������14", "����");
		playerItem[14] = INIDATA->loadDataInterger("�÷��̾�1_������", "������15", "����");

		for (int i = 0; i < 3; ++i)
		{
			if (playerItem[0] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������1", "����",	_itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������1", "����", _itoa(1, itemNum, 10));
					_pageOneItem[i]->_item.isSelect = false;
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������1", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������1", "����", _itoa(1, itemNum, 10));
					_pageTwoItem[i]->_item.isSelect = false;
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					break;
				}
			}

			if (playerItem[1] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������2", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������2", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageOneItem[i]->_item.isSelect = false;
					return;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������2", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������2", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageTwoItem[i]->_item.isSelect = false;
					return;
				}
			}

			if (playerItem[2] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������3", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������3", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������3", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������3", "����", _itoa(1, itemNum, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[3] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������4", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������4", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������4", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������4", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[4] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������5", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������5", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������5", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������5", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[5] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������6", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������6", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������6", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������6", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[6] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������7", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������7", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������7", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������7", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[7] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������8", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������8", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������8", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������8", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[8] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������9", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������9", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������9", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������9", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[9] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������10", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������10", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������10", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������10", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[10] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������11", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������11", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������11", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������11", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[11] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������12", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������12", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������12", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������12", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[12] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������13", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������13", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������13", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������13", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[13] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������14", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������14", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������14", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������14", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[14] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������15", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������15", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������15", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������15", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}
		} 
	}

	//�÷��̾�2�� �α����������
	if (loginPlayer2 == (int)INFO_YES)
	{
		int playerItem[15];
		char itemName[256];
		char itemNum[256];

		playerItem[0] = INIDATA->loadDataInterger("�÷��̾�2_������", "������1", "����");
		playerItem[1] = INIDATA->loadDataInterger("�÷��̾�2_������", "������2", "����");
		playerItem[2] = INIDATA->loadDataInterger("�÷��̾�2_������", "������3", "����");
		playerItem[3] = INIDATA->loadDataInterger("�÷��̾�2_������", "������4", "����");
		playerItem[4] = INIDATA->loadDataInterger("�÷��̾�2_������", "������5", "����");
		playerItem[5] = INIDATA->loadDataInterger("�÷��̾�2_������", "������6", "����");
		playerItem[6] = INIDATA->loadDataInterger("�÷��̾�2_������", "������7", "����");
		playerItem[7] = INIDATA->loadDataInterger("�÷��̾�2_������", "������8", "����");
		playerItem[8] = INIDATA->loadDataInterger("�÷��̾�2_������", "������9", "����");
		playerItem[9] = INIDATA->loadDataInterger("�÷��̾�2_������", "������10", "����");
		playerItem[10] = INIDATA->loadDataInterger("�÷��̾�2_������", "������11", "����");
		playerItem[11] = INIDATA->loadDataInterger("�÷��̾�2_������", "������12", "����");
		playerItem[12] = INIDATA->loadDataInterger("�÷��̾�2_������", "������13", "����");
		playerItem[13] = INIDATA->loadDataInterger("�÷��̾�2_������", "������14", "����");
		playerItem[14] = INIDATA->loadDataInterger("�÷��̾�2_������", "������15", "����");

		for (int i = 0; i < 3; ++i)
		{
			if (playerItem[0] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������1", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������1", "����", _itoa(1, itemNum, 10));
					_pageOneItem[i]->_item.isSelect = false;
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������1", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������1", "����", _itoa(1, itemNum, 10));
					_pageTwoItem[i]->_item.isSelect = false;
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					break;
				}
			}

			if (playerItem[1] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������2", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������2", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageOneItem[i]->_item.isSelect = false;
					return;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������2", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������2", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageTwoItem[i]->_item.isSelect = false;
					return;
				}
			}

			if (playerItem[2] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������3", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������3", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������3", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������3", "����", _itoa(1, itemNum, 10));
					INIDATA->iniSave("�÷��̾�1_������");
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[3] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������4", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������4", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������4", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������4", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[4] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������5", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������5", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������5", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������5", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[5] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������6", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������6", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������6", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������6", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[6] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������7", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������7", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������7", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������7", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[7] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������8", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������8", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������8", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������8", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[8] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������9", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������9", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������9", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������9", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[9] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������10", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������10", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������10", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������10", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[10] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������11", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������11", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������11", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������11", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[11] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������12", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������12", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������12", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������12", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[12] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������13", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������13", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������13", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������13", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[13] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������14", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������14", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������14", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������14", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}

			if (playerItem[14] == (int)ITEM_NONE)
			{
				if (_pageOneItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������15", "����", _itoa((int)_pageOneItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������15", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageOneItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageOneItem[i]->_item.isSelect = false;
					break;
				}

				if (_pageTwoItem[i]->_item.isSelect == true)
				{
					INIDATA->addData("������15", "����", _itoa((int)_pageTwoItem[i]->_item.ItemName, itemName, 10));
					INIDATA->addData("������15", "����", _itoa(1, itemNum, 10));
					_buyWindow.playerStone -= _pageTwoItem[i]->_item.price;
					char money[256];
					INIDATA->addData("������", "�ݾ�", _itoa(_buyWindow.playerStone, money, 10));
					INIDATA->iniSave("�÷��̾�2_������");
					_pageTwoItem[i]->_item.isSelect = false;
					break;
				}
			}
		}
	}
}

void buyItemWindow::textRender(tileMap * tileMap)
{
	//��Ʈ�ֱ�
	HFONT font4 = CreateFont(16, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY������B"));
	HFONT oldFont4 = (HFONT)SelectObject(getMemDC(), font4);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(230, 230, 230));

	RECT textBox = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 110,
		CAMERAMANAGER->getCameraCenterY() - 155, 150, 24);
	DrawText(getMemDC(), TEXT("������ ��ðڽ��ϱ�?"), strlen(TEXT("������ ��ðڽ��ϱ�?")),
		&textBox, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	SelectObject(getMemDC(), oldFont4);
	DeleteObject(font4);
	SetBkMode(getMemDC(), OPAQUE);

	//Ÿ��Ʋ �ֱ�
	HFONT font = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY������B"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(230, 230, 230));

	RECT TitleBox = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(),
		CAMERAMANAGER->getCameraCenterY() - 185, 130, 24);
	DrawText(getMemDC(), _buyWindow.title.c_str(), strlen(_buyWindow.title.c_str()),
		&TitleBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	SetBkMode(getMemDC(), OPAQUE);

	//����������, ����������, ������
	HFONT font2 = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("�ü�ü"));
	HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), font2);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(230, 230, 230));

	//����������
	char currentPage[256];
	RECT crrentBox = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 135,
		CAMERAMANAGER->getCameraCenterY() - 127, 20, 24);
	DrawText(getMemDC(), _itoa(_buyWindow.currentPage, currentPage, 10), strlen(_itoa(_buyWindow.currentPage, currentPage, 10)),
		&crrentBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//�߰��� ������ �ֱ�
	RECT slashBox = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 120,
		CAMERAMANAGER->getCameraCenterY() - 127, 20, 24);
	DrawText(getMemDC(), TEXT("/"), strlen(TEXT("/")),
		&slashBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//�ִ������� �ֱ�
	char maxPage[256];
	RECT maxBox = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 105,
		CAMERAMANAGER->getCameraCenterY() - 127, 20, 24);
	DrawText(getMemDC(), _itoa(_buyWindow.maxPage, maxPage, 10), strlen(_itoa(_buyWindow.maxPage, maxPage, 10)),
		&maxBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//page���� �ֱ�
	RECT pageBox = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 70,
		CAMERAMANAGER->getCameraCenterY() - 127, 40, 24);
	DrawText(getMemDC(), TEXT("page"), strlen(TEXT("page")),
		&pageBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//�÷��̾� ������ �ֱ�
	RECT moneyBox = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() + 60,
		CAMERAMANAGER->getCameraCenterY() - 127, 90, 24);
	DrawText(getMemDC(), TEXT("�������� : "), strlen(TEXT("�������� :  ")),
		&moneyBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//�����������
	char playerStone[256];
	RECT playerStoneBox = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() + 120,
		CAMERAMANAGER->getCameraCenterY() - 127, 50, 24);
	DrawText(getMemDC(), _itoa(_buyWindow.playerStone, playerStone, 10), strlen(_itoa(_buyWindow.playerStone, playerStone, 10)),
		&playerStoneBox, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

	//�÷��̾� ������ �ֱ�
	RECT stoneBox = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() + 170,
		CAMERAMANAGER->getCameraCenterY() - 127, 60, 24);
	DrawText(getMemDC(), TEXT("stone"), strlen(TEXT("stone")),
		&stoneBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SelectObject(getMemDC(), oldFont2);
	DeleteObject(font2);
	SetBkMode(getMemDC(), OPAQUE);

	//�������̸� �� ���� �ֱ�
	for (int i = 0; i < 3; ++i)
	{
		HFONT font3 = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY������B"));
		HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), font3);
		SetBkMode(getMemDC(), TRANSPARENT);
		RECT nameBox[3];
		RECT priceBox[3];
		char price[256][3];
		RECT stoneBox[3];

		if (_buyWindow.currentPage == 1)
		{
			//�������̸�
			nameBox[i] = RectMake(_pageOneItem[i]->_item.selectRc.left + 10, _pageOneItem[i]->_item.selectRc.top,
				200, 43);
			SetTextColor(getMemDC(), RGB(80, 230, 230));
			DrawText(getMemDC(), _pageOneItem[i]->_item.name.c_str(), strlen(_pageOneItem[i]->_item.name.c_str()),
				&nameBox[i], DT_LEFT | DT_VCENTER | DT_SINGLELINE);

			//����
			priceBox[i] = RectMake(_pageOneItem[i]->_item.selectRc.right - 205, _pageOneItem[i]->_item.selectRc.top,
				100, 43);
			SetTextColor(getMemDC(), RGB(230, 230, 230));
			DrawText(getMemDC(), _itoa(_pageOneItem[i]->_item.price, price[i], 10), strlen(_itoa(_pageOneItem[i]->_item.price, price[i], 10)),
				&priceBox[i], DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

			//����
			stoneBox[i] = RectMake(_pageOneItem[i]->_item.selectRc.right - 205, _pageOneItem[i]->_item.selectRc.top,
				180, 43);
			DrawText(getMemDC(), TEXT("stone"), strlen(TEXT("stone")),
				&stoneBox[i], DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
		}

		if (_buyWindow.currentPage == 2)
		{
			nameBox[i] = RectMake(_pageTwoItem[i]->_item.selectRc.left + 10, _pageTwoItem[i]->_item.selectRc.top,
				200, 43);
			SetTextColor(getMemDC(), RGB(80, 230, 230));
			DrawText(getMemDC(), _pageTwoItem[i]->_item.name.c_str(), strlen(_pageTwoItem[i]->_item.name.c_str()),
				&nameBox[i], DT_LEFT | DT_VCENTER | DT_SINGLELINE);

			//����
			priceBox[i] = RectMake(_pageTwoItem[i]->_item.selectRc.right - 205, _pageTwoItem[i]->_item.selectRc.top,
				100, 43);
			SetTextColor(getMemDC(), RGB(230, 230, 230));
			DrawText(getMemDC(), _itoa(_pageTwoItem[i]->_item.price, price[i], 10), strlen(_itoa(_pageTwoItem[i]->_item.price, price[i], 10)),
				&priceBox[i], DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

			//����
			stoneBox[i] = RectMake(_pageTwoItem[i]->_item.selectRc.right - 205, _pageTwoItem[i]->_item.selectRc.top,
				180, 43);
			DrawText(getMemDC(), TEXT("stone"), strlen(TEXT("stone")),
				&stoneBox[i], DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
		}

		SelectObject(getMemDC(), oldFont3);
		DeleteObject(font3);
		SetBkMode(getMemDC(), OPAQUE);
	}

	//�����ۼ���ֱ�
	if (_noticeWindow.isClickItem == false && _noticeWindow.isShortageMoney == false)
	{
		for (int i = 0; i < 3; ++i)
		{
			HFONT font3 = CreateFont(12, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
				0, 0, 0, 0, TEXT("HY������B"));
			HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), font3);
			SetBkMode(getMemDC(), TRANSPARENT);
			SetTextColor(getMemDC(), RGB(230, 230, 230));
			RECT textBox = RectMake(CAMERAMANAGER->getCameraCenterX() - 80, CAMERAMANAGER->getCameraCenterY() + 80,
				270, 30);
			RECT attackBox = RectMake(CAMERAMANAGER->getCameraCenterX() - 80, CAMERAMANAGER->getCameraCenterY() + 110,
				67, 30);
			RECT defenseBox = RectMake(CAMERAMANAGER->getCameraCenterX() + 10, CAMERAMANAGER->getCameraCenterY() + 110,
				67, 30);
			RECT speedBox = RectMake(CAMERAMANAGER->getCameraCenterX() + 100, CAMERAMANAGER->getCameraCenterY() + 110,
				67, 30);
			char powerNum[256][3];

			if (PtInRect(&_pageOneItem[i]->_item.selectRc,
				PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
			{
				if (_buyWindow.currentPage == 1)
				{
					//��������Ű�
					DrawText(getMemDC(), _pageOneItem[i]->_item.itemExplain.c_str(), strlen(_pageOneItem[i]->_item.itemExplain.c_str()),
						&textBox, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
					//������ֱ�
					DrawText(getMemDC(), TEXT("���ݷ� : "), strlen(TEXT("���ݷ� : ")), &attackBox, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
					DrawText(getMemDC(), _itoa(_pageOneItem[i]->_item.attackPower, powerNum[0], 10), strlen(_itoa(_pageOneItem[i]->_item.attackPower, powerNum[0], 10)),
						&attackBox, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

					DrawText(getMemDC(), TEXT("���� : "), strlen(TEXT("���� : ")), &defenseBox, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
					DrawText(getMemDC(), _itoa(_pageOneItem[i]->_item.defensePower, powerNum[1], 10), strlen(_itoa(_pageOneItem[i]->_item.defensePower, powerNum[1], 10)),
						&defenseBox, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

					DrawText(getMemDC(), TEXT("���߷� : "), strlen(TEXT("���߷� : ")), &speedBox, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
					DrawText(getMemDC(), _itoa(_pageOneItem[i]->_item.speedPower, powerNum[2], 10), strlen(_itoa(_pageOneItem[i]->_item.speedPower, powerNum[2], 10)),
						&speedBox, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
				}
			}

			if (PtInRect(&_pageTwoItem[i]->_item.selectRc,
				PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
			{
				if (_buyWindow.currentPage == 2)
				{
					DrawText(getMemDC(), _pageTwoItem[i]->_item.itemExplain.c_str(), strlen(_pageTwoItem[i]->_item.itemExplain.c_str()),
						&textBox, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
					//������ֱ�
					DrawText(getMemDC(), TEXT("���ݷ� : "), strlen(TEXT("���ݷ� : ")), &attackBox, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
					DrawText(getMemDC(), _itoa(_pageTwoItem[i]->_item.attackPower, powerNum[0], 10), strlen(_itoa(_pageTwoItem[i]->_item.attackPower, powerNum[0], 10)),
						&attackBox, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

					DrawText(getMemDC(), TEXT("���� : "), strlen(TEXT("���� : ")), &defenseBox, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
					DrawText(getMemDC(), _itoa(_pageTwoItem[i]->_item.defensePower, powerNum[1], 10), strlen(_itoa(_pageTwoItem[i]->_item.defensePower, powerNum[1], 10)),
						&defenseBox, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

					DrawText(getMemDC(), TEXT("���߷� : "), strlen(TEXT("���߷� : ")), &speedBox, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
					DrawText(getMemDC(), _itoa(_pageTwoItem[i]->_item.speedPower, powerNum[2], 10), strlen(_itoa(_pageTwoItem[i]->_item.speedPower, powerNum[2], 10)),
						&speedBox, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
				}
			}

			SelectObject(getMemDC(), oldFont2);
			DeleteObject(font2);
			SetBkMode(getMemDC(), OPAQUE);
		}
	}
}

void buyItemWindow::PtInRender(tileMap * tileMap)
{
	HPEN myPen = CreatePen(PS_DASH, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	if (_noticeWindow.isClickItem == false && _noticeWindow.isShortageMoney == false)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (PtInRect(&_pageOneItem[i]->_item.selectRc,
				PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
			{
				if (_buyWindow.currentPage == 1)
				{
					Rectangle(getMemDC(), _pageOneItem[i]->_item.selectRc);
					_pageOneItem[i]->render();
				}
			}

			if (PtInRect(&_pageTwoItem[i]->_item.selectRc,
				PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
			{
				if (_buyWindow.currentPage == 2)
				{
					Rectangle(getMemDC(), _pageTwoItem[i]->_item.selectRc);
					_pageTwoItem[i]->render();
				}
			}
		}
	}

	if (PtInRect(&_buyWindow.returnRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _buyWindow.returnRect);
	}

	if (PtInRect(&_buyWindow.leftButton.rc,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _buyWindow.leftButton.rc);
	}

	if (PtInRect(&_buyWindow.rightButton.rc,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _buyWindow.rightButton.rc);
	}

	if (PtInRect(&_noticeWindow.returnRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _noticeWindow.returnRect);
	}

	if (PtInRect(&_noticeWindow.decideRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _noticeWindow.decideRect);
	}

	if (PtInRect(&_noticeWindow.okayRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _noticeWindow.okayRect);
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void buyItemWindow::imageRender(tileMap * tileMap)
{
	_buyWindow.backImg->alphaRender(getMemDC(), CAMERAMANAGER->getCameraCenterX() - _buyWindow.backImg->getWidth() / 2,
		CAMERAMANAGER->getCameraCenterY() - _buyWindow.backImg->getHeight() / 2, 200);
	_buyWindow.frontImg->render(getMemDC(), _buyWindow.frontRect.left, _buyWindow.frontRect.top);
	_buyWindow.leftButton.img->frameRender(getMemDC(), _buyWindow.leftButton.rc.left, _buyWindow.leftButton.rc.top,
		_buyWindow.leftButton.currentFrameX, _buyWindow.leftButton.currentFrameY);
	_buyWindow.rightButton.img->frameRender(getMemDC(), _buyWindow.rightButton.rc.left, _buyWindow.rightButton.rc.top,
		_buyWindow.rightButton.currentFrameX, _buyWindow.rightButton.currentFrameY);
}

void buyItemWindow::setItem(tileMap * tileMap)
{
	_buyWindow.frontRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(),
		_buyWindow.frontImg->getWidth(), _buyWindow.frontImg->getHeight());
	_noticeWindow.img = IMAGEMANAGER->findImage("inputWindow2");
	_noticeWindow.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(),
		_noticeWindow.img->getWidth(), _noticeWindow.img->getHeight());

	//�� �����ϰ��
	if (tileMap->_isClickArmorNPC == true)
	{
		_buyWindow.title = "�� ����";
		
		for (int i = 0; i < 3; ++i)
		{
			//1������ ����

			_pageOneItem[i] = new item;
			_pageOneItem[i]->init((ITEMNAME)(i + 11), PointMake(0, 0));
			_pageOneItem[i]->_item.imgRc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraTOP() + 329,
				_pageOneItem[i]->_item.img->getFrameWidth(), _pageOneItem[i]->_item.img->getFrameHeight());
			_pageOneItem[i]->_item.selectRc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(),
				CAMERAMANAGER->getCameraTOP() + 131 + i * 55, 410, 43);



			//2������ ����
			_pageTwoItem[i] = new item;
			_pageTwoItem[i]->init((ITEMNAME)(i + 14), PointMake(0, 0));
			_pageTwoItem[i]->_item.imgRc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraTOP() + 329,
				_pageTwoItem[i]->_item.img->getFrameWidth(), _pageTwoItem[i]->_item.img->getFrameHeight());
			_pageTwoItem[i]->_item.selectRc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(),
				CAMERAMANAGER->getCameraTOP() + 131 + i * 55, 410, 43);
		}
	}

	//���� �����ϰ��
	if (tileMap->_isClickWeaponNPC == true)
	{
		_buyWindow.title = "���� ����";

		for (int i = 0; i < 3; ++i)
		{
			//1������ ����

			_pageOneItem[i] = new item;
			_pageOneItem[i]->init((ITEMNAME)(i + 5), PointMake(0, 0));
			_pageOneItem[i]->_item.imgRc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraTOP() + 329,
				_pageOneItem[i]->_item.img->getFrameWidth(), _pageOneItem[i]->_item.img->getFrameHeight());
			_pageOneItem[i]->_item.selectRc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(),
				CAMERAMANAGER->getCameraTOP() + 131 + i * 55, 410, 43);



			//2������ ����
			_pageTwoItem[i] = new item;
			_pageTwoItem[i]->init((ITEMNAME)(i + 8), PointMake(0, 0));
			_pageTwoItem[i]->_item.imgRc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraTOP() + 329,
				_pageTwoItem[i]->_item.img->getFrameWidth(), _pageTwoItem[i]->_item.img->getFrameHeight());
			_pageTwoItem[i]->_item.selectRc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(),
				CAMERAMANAGER->getCameraTOP() + 131 + i * 55, 410, 43);
		}
	}
}

void buyItemWindow::updateItem(tileMap * tileMap)
{
	_buyWindow.frontRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(),
		_buyWindow.frontImg->getWidth(), _buyWindow.frontImg->getHeight());
	_buyWindow.leftButton.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 170, CAMERAMANAGER->getCameraCenterY() - 127,
		_buyWindow.leftButton.img->getFrameWidth(), _buyWindow.leftButton.img->getFrameHeight());
	_buyWindow.rightButton.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 31, CAMERAMANAGER->getCameraCenterY() - 127,
		_buyWindow.rightButton.img->getFrameWidth(), _buyWindow.rightButton.img->getFrameHeight());
	_buyWindow.returnRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() + 1, CAMERAMANAGER->getCameraCenterY() + 186, 80, 16);

	if (_noticeWindow.isClickItem == true)
	{
		_noticeWindow.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(),
			_noticeWindow.img->getWidth(), _noticeWindow.img->getHeight());
		_noticeWindow.decideRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 61, CAMERAMANAGER->getCameraCenterY() + 24,
			96, 30);
		_noticeWindow.returnRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() + 61, CAMERAMANAGER->getCameraCenterY() + 24,
			96, 30);
	}

	if (_noticeWindow.isClickItem == false)
	{
		_noticeWindow.decideRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 100, CAMERAMANAGER->getCameraTOP() - 100,
			96, 30);
		_noticeWindow.returnRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 100, CAMERAMANAGER->getCameraTOP() - 100,
			96, 30);
	}

	if (_noticeWindow.isShortageMoney == true)
	{
		_noticeWindow.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(),
			_noticeWindow.img->getWidth(), _noticeWindow.img->getHeight());
		_noticeWindow.okayRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY() + 24,
			96, 30);
	}

	if (_noticeWindow.isShortageMoney == false)
	{
		_noticeWindow.okayRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 100, CAMERAMANAGER->getCameraTOP() - 100,
			96, 30);
	}

	if (_noticeWindow.isClickItem == false && _noticeWindow.isShortageMoney == false)
	{
		_noticeWindow.rc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 200, CAMERAMANAGER->getCameraTOP() - 329,
			_noticeWindow.img->getWidth(), _noticeWindow.img->getHeight());
	}

	for (int i = 0; i < 3; ++i)
	{
		if (_buyWindow.currentPage == 1)
		{
			_pageOneItem[i]->_item.imgRc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 138, CAMERAMANAGER->getCameraCenterY() + 122,
				_pageOneItem[i]->_item.img->getFrameWidth(), _pageOneItem[i]->_item.img->getFrameHeight());
			_pageOneItem[i]->_item.selectRc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(),
				CAMERAMANAGER->getCameraCenterY() - 76 + i * 55, 410, 43);

			_pageTwoItem[i]->_item.imgRc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 200, CAMERAMANAGER->getCameraTOP() - 329,
				_pageTwoItem[i]->_item.img->getFrameWidth(), _pageTwoItem[i]->_item.img->getFrameHeight());
			_pageTwoItem[i]->_item.selectRc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 200,
				CAMERAMANAGER->getCameraTOP() - 329, 410, 43);
		}

		if (_buyWindow.currentPage == 2)
		{
			_pageTwoItem[i]->_item.imgRc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 138, CAMERAMANAGER->getCameraCenterY() + 122,
				_pageTwoItem[i]->_item.img->getFrameWidth(), _pageTwoItem[i]->_item.img->getFrameHeight());
			_pageTwoItem[i]->_item.selectRc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(),
				CAMERAMANAGER->getCameraCenterY() - 76 + i * 55, 410, 43);

			_pageOneItem[i]->_item.imgRc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 200, CAMERAMANAGER->getCameraTOP() - 329,
				_pageOneItem[i]->_item.img->getFrameWidth(), _pageOneItem[i]->_item.img->getFrameHeight());
			_pageOneItem[i]->_item.selectRc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 200,
				CAMERAMANAGER->getCameraTOP() - 329, 410, 43);
		}
	}
}

void buyItemWindow::clickPage(tileMap * tileMap)
{
	if (PtInRect(&_buyWindow.leftButton.rc,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		_buyWindow.currentPage--;
		_buyWindow.leftButton.currentFrameX = 1;

		if (_buyWindow.currentPage < 1)
		{
			_buyWindow.currentPage = _buyWindow.maxPage;
		}
	}

	if (PtInRect(&_buyWindow.rightButton.rc,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		_buyWindow.currentPage++;
		_buyWindow.rightButton.currentFrameX = 1;

		if (_buyWindow.currentPage > _buyWindow.maxPage)
		{
			_buyWindow.currentPage = 1;
		}
	}


	if (PtInRect(&_noticeWindow.returnRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		for (int i = 0; i < 3; ++i)
		{
			_pageOneItem[i]->_item.isSelect = false;
			_pageTwoItem[i]->_item.isSelect = false;
		}

		_noticeWindow.isClickItem = false;
	}

	if (PtInRect(&_noticeWindow.decideRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		_noticeWindow.isClickItem = false;
		saveInidata(tileMap);
	}

	if (PtInRect(&_noticeWindow.okayRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		_noticeWindow.isShortageMoney = false;
	}
}

void buyItemWindow::updateButton(tileMap * tileMap)
{
	if (_buyWindow.leftButton.currentFrameX == 1)
	{
		_buyWindow.leftButton.timeCount++;

		if (_buyWindow.leftButton.timeCount >= 4)
		{
			_buyWindow.leftButton.timeCount = 0;
			_buyWindow.leftButton.currentFrameX = 0;
		}
	}

	if (_buyWindow.rightButton.currentFrameX == 1)
	{
		_buyWindow.rightButton.timeCount++;

		if (_buyWindow.rightButton.timeCount >= 4)
		{
			_buyWindow.rightButton.timeCount = 0;
			_buyWindow.rightButton.currentFrameX = 0;
		}
	}
}

void buyItemWindow::clickItem(tileMap * tileMap)
{
	if (_noticeWindow.isClickItem == true) return;
	if (_noticeWindow.isShortageMoney == true) return;
	if (_isDisableClick == true) return;
	//�ش�������� Ŭ��������� 
	for (int i = 0; i < 3; ++i)
	{
		if (PtInRect(&_pageOneItem[i]->_item.selectRc,
			PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
		{
			if (_buyWindow.currentPage == 1)
			{
				if (_buyWindow.playerStone < _pageOneItem[i]->_item.price)
				{
					_noticeWindow.isShortageMoney = true;
					_isDisableClick = true;
					_noticeWindow.message = "������ �����մϴ�";
				}

				if (_buyWindow.playerStone >= _pageOneItem[i]->_item.price)
				{
					_noticeWindow.isClickItem = true;
					_pageOneItem[i]->_item.isSelect = true;
					_isDisableClick = true;
					_noticeWindow.message = "������ �����Ͻðڽ��ϱ�?";
				}
			}
		}

		if (PtInRect(&_pageTwoItem[i]->_item.selectRc,
			PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
		{
			if (_buyWindow.currentPage == 2)
			{
				if (_buyWindow.playerStone < _pageTwoItem[i]->_item.price)
				{
					_noticeWindow.isShortageMoney = true;
					_isDisableClick = true;
					_noticeWindow.message = "������ �����մϴ�";
				}

				if (_buyWindow.playerStone >= _pageTwoItem[i]->_item.price)
				{
					_noticeWindow.isClickItem = true;
					_pageTwoItem[i]->_item.isSelect = true;
					_isDisableClick = true;
					_noticeWindow.message = "������ �����Ͻðڽ��ϱ�?";
				}
			}
		}
	}
}

void buyItemWindow::noticeRender(tileMap * tileMap)
{
	if (_noticeWindow.isClickItem == true)
	{
		IMAGEMANAGER->alphaRender("inputWindowBack", getMemDC(), CAMERAMANAGER->getCameraCenterX() - IMAGEMANAGER->findImage("inputWindowBack")->getWidth() / 2,
			CAMERAMANAGER->getCameraCenterY() - IMAGEMANAGER->findImage("inputWindowBack")->getHeight() / 2, 220);
		_noticeWindow.img->render(getMemDC(), _noticeWindow.rc.left, _noticeWindow.rc.top);
		IMAGEMANAGER->render("button", getMemDC(), _noticeWindow.decideRect.left, _noticeWindow.decideRect.top);
		IMAGEMANAGER->render("button", getMemDC(), _noticeWindow.returnRect.left, _noticeWindow.returnRect.top);
	}

	if (_noticeWindow.isShortageMoney == true)
	{
		IMAGEMANAGER->alphaRender("inputWindowBack", getMemDC(), CAMERAMANAGER->getCameraCenterX() - IMAGEMANAGER->findImage("inputWindowBack")->getWidth() / 2,
			CAMERAMANAGER->getCameraCenterY() - IMAGEMANAGER->findImage("inputWindowBack")->getHeight() / 2, 220);
		_noticeWindow.img->render(getMemDC(), _noticeWindow.rc.left, _noticeWindow.rc.top);
		IMAGEMANAGER->render("button", getMemDC(), _noticeWindow.okayRect.left, _noticeWindow.okayRect.top);
	}


	//�˸�â �޼���, ����, ���, �����̹�ư
	if (_noticeWindow.isClickItem == true)
	{
		HFONT font3 = CreateFont(17, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY������B"));
		HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), font3);
		SetBkMode(getMemDC(), TRANSPARENT);

		//�˸�â �޼���
		RECT noticeBox = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY() - 15,
			216, 43);
		SetTextColor(getMemDC(), RGB(230, 230, 230));
		DrawText(getMemDC(), _noticeWindow.message.c_str(), strlen(_noticeWindow.message.c_str()),
			&noticeBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		//���� �޼���
		SetTextColor(getMemDC(), RGB(20, 20, 230));
		DrawText(getMemDC(), TEXT("����"), strlen(TEXT("����")),
			&_noticeWindow.decideRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		//��� �޼���
		SetTextColor(getMemDC(), RGB(230, 20, 20));
		DrawText(getMemDC(), TEXT("���"), strlen(TEXT("���")),
			&_noticeWindow.returnRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


		SelectObject(getMemDC(), oldFont3);
		DeleteObject(font3);
		SetBkMode(getMemDC(), OPAQUE);
	}

	if (_noticeWindow.isShortageMoney == true)
	{
		HFONT font3 = CreateFont(17, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY������B"));
		HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), font3);
		SetBkMode(getMemDC(), TRANSPARENT);

		//�˸�â �޼���
		RECT noticeBox = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY() - 15,
			216, 43);
		SetTextColor(getMemDC(), RGB(230, 230, 230));
		DrawText(getMemDC(), _noticeWindow.message.c_str(), strlen(_noticeWindow.message.c_str()),
			&noticeBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		//������ �޼���
		SetTextColor(getMemDC(), RGB(230, 30, 30));
		DrawText(getMemDC(), TEXT("OKAY"), strlen(TEXT("OKAY")),
			&_noticeWindow.okayRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		SelectObject(getMemDC(), oldFont3);
		DeleteObject(font3);
		SetBkMode(getMemDC(), OPAQUE);
	}
}
