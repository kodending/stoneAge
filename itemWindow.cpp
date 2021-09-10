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

menuType * itemWindow::inputHandle(tileMap * tileMap)
{
	if (PtInRect(&_itemWindow.exitRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(false);
		tileMap->setIsPosibleClick(false);
		tileMap->setDelayClickCount(0);
		exit(tileMap);
		SOUNDMANAGER->play("window_down", 0.4f);
		return new baseType();
	}

	if (PtInRect(&tileMap->getMenuStateRect(), PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		exit(tileMap);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new stateWindow();
	}

	if (PtInRect(&tileMap->getMenuPetRect(), PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		exit(tileMap);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new petWindow();
	}

	if (PtInRect(&_itemWindow.arrangeRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		lineUpItem(tileMap);
	}

	selectItem(tileMap);
	switchItem(tileMap);

	return nullptr;
}

void itemWindow::update(tileMap * tileMap)
{
	updateRect(tileMap);
	setItem(tileMap);
	updateItem(tileMap);
	updateSelectItem(tileMap);

	if (PtInRect(&_itemWindow.frontRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnPet(true);
	}

	else tileMap->setIsMouseOnPet(false);

	if (_isTime == true)
	{
		_clickDelayTime++;

		if (_clickDelayTime >= 4)
		{
			_clickDelayTime = 0;
			_isTime = false;
			_isAbleSameClick = true;
		}
	}
}

void itemWindow::enter(tileMap * tileMap)
{
	_itemWindow.frontImg = IMAGEMANAGER->findImage("itemWindow");
	_itemWindow.backImg = IMAGEMANAGER->findImage("itemWindowBack");

	_clickDelayTime = 0;
	_isLoadSetItem = false;
	_isAbleSameClick = false;
	_isTime = false;
}

void itemWindow::render(tileMap * tileMap)
{
	_itemWindow.backImg->alphaRender(getMemDC(), _itemWindow.backRect.left + 11, _itemWindow.backRect.top, 200);
	_itemWindow.frontImg->render(getMemDC(), _itemWindow.frontRect.left, _itemWindow.frontRect.top);



	itemRender(tileMap);
	textRender(tileMap);
	PtInRender(tileMap);
}

void itemWindow::exit(tileMap * tileMap)
{
	if (tileMap->_vItem.size() != 0)
	{
		tileMap->_vItem.clear();
	}
}

void itemWindow::updateRect(tileMap* tileMap)
{
	//��â
	_itemWindow.frontRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - _itemWindow.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _itemWindow.frontImg->getHeight() / 2,
		_itemWindow.frontImg->getWidth(), _itemWindow.frontImg->getHeight());
	//��â
	_itemWindow.backRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - _itemWindow.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _itemWindow.frontImg->getHeight() / 2,
		_itemWindow.backImg->getWidth(), _itemWindow.backImg->getHeight());
	//����������Ʈ
	_itemWindow.arrangeRect = RectMake(CAMERAMANAGER->getCameraRIGHT() - 244, CAMERAMANAGER->getCameraTOP() + 424,
		85, 16);
	//�ݱⷺƮ
	_itemWindow.exitRect = RectMake(CAMERAMANAGER->getCameraRIGHT() - 119, CAMERAMANAGER->getCameraTOP() + 424,
		85, 16);
	//������ ĭ ��Ʈ
	for (int j = 0; j < 3; ++j)
	{
		for(int i = 0; i < 5; ++i)
		{
			_itemWindow.item[i][j].rc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 250 + i * 54,
				CAMERAMANAGER->getCameraTOP() + 225 + j * 45, 51, 39);
			_itemWindow.item[i][j].centerX = (_itemWindow.item[i][j].rc.left + _itemWindow.item[i][j].rc.right) / 2;
			_itemWindow.item[i][j].centerY = (_itemWindow.item[i][j].rc.top + _itemWindow.item[i][j].rc.bottom) / 2;
		}
	}

	//ĳ���� �Է����� ĭ ��Ʈ
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 3; ++i)
		{
			_itemWindow.pw[i][j].rc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 244 + i * 53,
				CAMERAMANAGER->getCameraTOP() + 31 + j * 44, 50, 41);
			_itemWindow.pw[i][j].centerX = (_itemWindow.pw[i][j].rc.left + _itemWindow.pw[i][j].rc.right) / 2;
			_itemWindow.pw[i][j].centerY = (_itemWindow.pw[i][j].rc.top + _itemWindow.pw[i][j].rc.bottom) / 2;
		}
	}
}

void itemWindow::PtInRender(tileMap* tileMap)
{
	HPEN myPen = CreatePen(PS_DASH, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	//������ ĭ ��Ʈ
	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < 5; ++i)
		{
			if (PtInRect(&_itemWindow.item[i][j].rc,
				PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
			{
				Rectangle(getMemDC(), _itemWindow.item[i][j].rc);
			}
		}
	}

	//ĳ���� �Է����� ĭ ��Ʈ
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (PtInRect(&_itemWindow.pw[i][j].rc,
				PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
			{
				Rectangle(getMemDC(), _itemWindow.pw[i][j].rc);
			}
		}
	}

	//���������� ��Ʈ
	if (PtInRect(&_itemWindow.arrangeRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _itemWindow.arrangeRect);
	}

	//�ݱ� ��Ʈ
	if (PtInRect(&_itemWindow.exitRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _itemWindow.exitRect);
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void itemWindow::setItem(tileMap * tileMap)
{
	if (_isLoadSetItem == true) return;

	_isClickItem = false;

	//ĳ���� �Է� ����ĭ Ÿ�Ժο�
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 3; ++i)
		{
			//���Ÿ������
			if (i == 1 && j == 0)
			{
				_itemWindow.pw[i][j].playerWear = WEAR_HELMET;
				_itemWindow.pw[i][j].isExistItem = false;
			}
			//����Ÿ�� ����
			else if (i == 0 && j == 1)
			{
				_itemWindow.pw[i][j].playerWear = WEAR_WEAPON;
				_itemWindow.pw[i][j].isExistItem = false;
			}
			//��Ÿ�� ����
			else if (i == 1 && j == 1)
			{
				_itemWindow.pw[i][j].playerWear = WEAR_ARMOR;
				_itemWindow.pw[i][j].isExistItem = false;
			}
			//ž�¹���Ÿ�� ����
			else if (i == 1 && j == 2)
			{
				_itemWindow.pw[i][j].playerWear = WEAR_RIDE_BOOK;
				_itemWindow.pw[i][j].isExistItem = false;
			}
			else
			{
				_itemWindow.pw[i][j].playerWear = WEAR_NONE;
				_itemWindow.pw[i][j].isExistItem = false;
			}
			
			_itemWindow.pw[i][j].itemPos = (j * 3) + i + 1;
		}
	}

	//�ʱ� false�� �ο�
	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < 5; ++i)
		{
			_itemWindow.item[i][j].isExistItem = false;
			_itemWindow.item[i][j].itemPos = (j * 3) + i + j + j + 1;
		}
	}

	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	//�÷��̾�1�� �α����������
	if (loginPlayer1 == (int)INFO_YES)
	{
		int itemType[19];

		_playerStone = INIDATA->loadDataInterger("�÷��̾�1_������", "������", "�ݾ�");

		itemType[0] = INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "����");
		itemType[1] = INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "����");
		itemType[2] = INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "����");
		itemType[3] = INIDATA->loadDataInterger("�÷��̾�1_������", "ž�¹�������", "����");

		itemType[4] = INIDATA->loadDataInterger("�÷��̾�1_������", "������1", "����");
		itemType[5] = INIDATA->loadDataInterger("�÷��̾�1_������", "������2", "����");
		itemType[6] = INIDATA->loadDataInterger("�÷��̾�1_������", "������3", "����");
		itemType[7] = INIDATA->loadDataInterger("�÷��̾�1_������", "������4", "����");
		itemType[8] = INIDATA->loadDataInterger("�÷��̾�1_������", "������5", "����");
		itemType[9] = INIDATA->loadDataInterger("�÷��̾�1_������", "������6", "����");
		itemType[10] = INIDATA->loadDataInterger("�÷��̾�1_������", "������7", "����");
		itemType[11] = INIDATA->loadDataInterger("�÷��̾�1_������", "������8", "����");
		itemType[12] = INIDATA->loadDataInterger("�÷��̾�1_������", "������9", "����");
		itemType[13] = INIDATA->loadDataInterger("�÷��̾�1_������", "������10", "����");
		itemType[14] = INIDATA->loadDataInterger("�÷��̾�1_������", "������11", "����");
		itemType[15] = INIDATA->loadDataInterger("�÷��̾�1_������", "������12", "����");
		itemType[16] = INIDATA->loadDataInterger("�÷��̾�1_������", "������13", "����");
		itemType[17] = INIDATA->loadDataInterger("�÷��̾�1_������", "������14", "����");
		itemType[18] = INIDATA->loadDataInterger("�÷��̾�1_������", "������15", "����");

		for (int j = 0; j < 17; ++j)
		{
			//������ ���Ⱑ �������
			if (itemType[0] == (ITEMNAME)j &&
				itemType[0] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[0][1].centerX, _itemWindow.pw[0][1].centerY));
				_item->_item.isWeared = true;
				_itemWindow.pw[0][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//������ ������ �������
			if (itemType[1] == (ITEMNAME)j &&
				itemType[1] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[1][1].centerX, _itemWindow.pw[1][1].centerY));
				_item->_item.isWeared = true;
				_itemWindow.pw[1][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//������ ������ �������
			if (itemType[2] == (ITEMNAME)j &&
				itemType[2] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[1][0].centerX, _itemWindow.pw[1][0].centerY));
				_item->_item.isWeared = true;
				_itemWindow.pw[1][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//������ ž�¹����� �������
			if (itemType[3] == (ITEMNAME)j &&
				itemType[3] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[1][2].centerX, _itemWindow.pw[1][2].centerY));
				_item->_item.isWeared = true;
				_itemWindow.pw[1][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//ù��°ĭ �������� �������
			if (itemType[4] == (ITEMNAME)j &&
				itemType[4] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[0][0].centerX, _itemWindow.item[0][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������1", "����"));
				_item->_item.itemPos = 1;
				_itemWindow.item[0][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//�ι�°ĭ �������� �������
			if (itemType[5] == (ITEMNAME)j &&
				itemType[5] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[1][0].centerX, _itemWindow.item[1][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������2", "����"));
				_item->_item.itemPos = 2;
				_itemWindow.item[1][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//����°ĭ �������� �������
			if (itemType[6] == (ITEMNAME)j &&
				itemType[6] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[2][0].centerX, _itemWindow.item[2][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������3", "����"));
				_item->_item.itemPos = 3;
				_itemWindow.item[2][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//�׹�°ĭ�� �������� �������
			if (itemType[7] == (ITEMNAME)j &&
				itemType[7] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[3][0].centerX, _itemWindow.item[3][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������4", "����"));
				_item->_item.itemPos = 4;
				_itemWindow.item[3][0].isExistItem = true;

				tileMap->_vItem.push_back(_item);
			}

			//�ټ���°ĭ�� �������� �������
			if (itemType[8] == (ITEMNAME)j &&
				itemType[8] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[4][0].centerX, _itemWindow.item[4][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������5", "����"));
				_item->_item.itemPos = 5;
				_itemWindow.item[4][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//������°ĭ�� �������� �������
			if (itemType[9] == (ITEMNAME)j &&
				itemType[9] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[0][1].centerX, _itemWindow.item[0][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������6", "����"));
				_item->_item.itemPos = 6;
				_itemWindow.item[0][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//7��°ĭ�� �������� �������
			if (itemType[10] == (ITEMNAME)j &&
				itemType[10] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[1][1].centerX, _itemWindow.item[1][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������7", "����"));
				_item->_item.itemPos = 7;
				_itemWindow.item[1][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//8��°ĭ�� �������� �������
			if (itemType[11] == (ITEMNAME)j &&
				itemType[11] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[2][1].centerX, _itemWindow.item[2][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������8", "����"));
				_item->_item.itemPos = 8;
				_itemWindow.item[2][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//9��°ĭ�� �������� �������
			if (itemType[12] == (ITEMNAME)j &&
				itemType[12] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[3][1].centerX, _itemWindow.item[3][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������9", "����"));
				_item->_item.itemPos = 9;
				_itemWindow.item[3][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//10��°ĭ�� �������� �������
			if (itemType[13] == (ITEMNAME)j &&
				itemType[13] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[4][1].centerX, _itemWindow.item[4][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������10", "����"));
				_item->_item.itemPos = 10;
				_itemWindow.item[4][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//11��°ĭ�� �������� �������
			if (itemType[14] == (ITEMNAME)j &&
				itemType[14] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[0][2].centerX, _itemWindow.item[0][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������11", "����"));
				_item->_item.itemPos = 11;
				_itemWindow.item[0][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//12��°ĭ�� �������� �������
			if (itemType[15] == (ITEMNAME)j &&
				itemType[15] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[1][2].centerX, _itemWindow.item[1][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������12", "����"));
				_item->_item.itemPos = 12;
				_itemWindow.item[1][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//13��°ĭ�� �������� �������
			if (itemType[16] == (ITEMNAME)j &&
				itemType[16] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[2][2].centerX, _itemWindow.item[2][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������13", "����"));
				_item->_item.itemPos = 13;
				_itemWindow.item[2][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//14��°ĭ�� �������� �������
			if (itemType[17] == (ITEMNAME)j &&
				itemType[17] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[3][2].centerX, _itemWindow.item[3][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������14", "����"));
				_item->_item.itemPos = 14;
				_itemWindow.item[3][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//15��°ĭ�� �������� �������
			if (itemType[18] == (ITEMNAME)j &&
				itemType[18] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[4][2].centerX, _itemWindow.item[4][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������15", "����"));
				_item->_item.itemPos = 15;
				_itemWindow.item[4][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}
		}
	}

	//�÷��̾�2�� �α����������
	if (loginPlayer2 == (int)INFO_YES)
	{
		int itemType[19];

		_playerStone = INIDATA->loadDataInterger("�÷��̾�2_������", "������", "�ݾ�");

		itemType[0] = INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "����");
		itemType[1] = INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "����");
		itemType[2] = INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "����");
		itemType[3] = INIDATA->loadDataInterger("�÷��̾�2_������", "ž�¹�������", "����");

		itemType[4] = INIDATA->loadDataInterger("�÷��̾�2_������", "������1", "����");
		itemType[5] = INIDATA->loadDataInterger("�÷��̾�2_������", "������2", "����");
		itemType[6] = INIDATA->loadDataInterger("�÷��̾�2_������", "������3", "����");
		itemType[7] = INIDATA->loadDataInterger("�÷��̾�2_������", "������4", "����");
		itemType[8] = INIDATA->loadDataInterger("�÷��̾�2_������", "������5", "����");
		itemType[9] = INIDATA->loadDataInterger("�÷��̾�2_������", "������6", "����");
		itemType[10] = INIDATA->loadDataInterger("�÷��̾�2_������", "������7", "����");
		itemType[11] = INIDATA->loadDataInterger("�÷��̾�2_������", "������8", "����");
		itemType[12] = INIDATA->loadDataInterger("�÷��̾�2_������", "������9", "����");
		itemType[13] = INIDATA->loadDataInterger("�÷��̾�2_������", "������10", "����");
		itemType[14] = INIDATA->loadDataInterger("�÷��̾�2_������", "������11", "����");
		itemType[15] = INIDATA->loadDataInterger("�÷��̾�2_������", "������12", "����");
		itemType[16] = INIDATA->loadDataInterger("�÷��̾�2_������", "������13", "����");
		itemType[17] = INIDATA->loadDataInterger("�÷��̾�2_������", "������14", "����");
		itemType[18] = INIDATA->loadDataInterger("�÷��̾�2_������", "������15", "����");

		for (int j = 0; j < 16; ++j)
		{
			//������ ���Ⱑ �������
			if (itemType[0] == (ITEMNAME)j &&
				itemType[0] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[0][1].centerX, _itemWindow.pw[0][1].centerY));
				_item->_item.isWeared = true;
				tileMap->_vItem.push_back(_item);
			}

			//������ ������ �������
			if (itemType[1] == (ITEMNAME)j &&
				itemType[1] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[1][1].centerX, _itemWindow.pw[1][1].centerY));
				_item->_item.isWeared = true;
				tileMap->_vItem.push_back(_item);
			}

			//������ ������ �������
			if (itemType[2] == (ITEMNAME)j &&
				itemType[2] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[1][0].centerX, _itemWindow.pw[1][0].centerY));
				_item->_item.isWeared = true;
				tileMap->_vItem.push_back(_item);
			}

			//������ ž�¹����� �������
			if (itemType[3] == (ITEMNAME)j &&
				itemType[3] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[1][2].centerX, _itemWindow.pw[1][2].centerY));
				_item->_item.isWeared = true;
				tileMap->_vItem.push_back(_item);
			}

			//ù��°ĭ �������� �������
			if (itemType[4] == (ITEMNAME)j &&
				itemType[4] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[0][0].centerX, _itemWindow.item[0][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������1", "����"));
				_item->_item.itemPos = 1;
				_itemWindow.item[0][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//�ι�°ĭ �������� �������
			if (itemType[5] == (ITEMNAME)j &&
				itemType[5] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[1][0].centerX, _itemWindow.item[1][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������2", "����"));
				_item->_item.itemPos = 2;
				_itemWindow.item[1][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//����°ĭ �������� �������
			if (itemType[6] == (ITEMNAME)j &&
				itemType[6] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[2][0].centerX, _itemWindow.item[2][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������3", "����"));
				_item->_item.itemPos = 3;
				_itemWindow.item[2][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//�׹�°ĭ�� �������� �������
			if (itemType[7] == (ITEMNAME)j &&
				itemType[7] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[3][0].centerX, _itemWindow.item[3][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������4", "����"));
				_item->_item.itemPos = 4;
				_itemWindow.item[3][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//�ټ���°ĭ�� �������� �������
			if (itemType[8] == (ITEMNAME)j &&
				itemType[8] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[4][0].centerX, _itemWindow.item[4][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������5", "����"));
				_item->_item.itemPos = 5;
				_itemWindow.item[4][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//������°ĭ�� �������� �������
			if (itemType[9] == (ITEMNAME)j &&
				itemType[9] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[0][1].centerX, _itemWindow.item[0][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������6", "����"));
				_item->_item.itemPos = 6;
				_itemWindow.item[0][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//7��°ĭ�� �������� �������
			if (itemType[10] == (ITEMNAME)j &&
				itemType[10] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[1][1].centerX, _itemWindow.item[1][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������7", "����"));
				_item->_item.itemPos = 7;
				_itemWindow.item[1][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//8��°ĭ�� �������� �������
			if (itemType[11] == (ITEMNAME)j &&
				itemType[11] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[2][1].centerX, _itemWindow.item[2][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������8", "����"));
				_item->_item.itemPos = 8;
				_itemWindow.item[2][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//9��°ĭ�� �������� �������
			if (itemType[12] == (ITEMNAME)j &&
				itemType[12] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[3][1].centerX, _itemWindow.item[3][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������9", "����"));
				_item->_item.itemPos = 9;
				_itemWindow.item[3][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//10��°ĭ�� �������� �������
			if (itemType[13] == (ITEMNAME)j &&
				itemType[13] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[4][1].centerX, _itemWindow.item[4][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������10", "����"));
				_item->_item.itemPos = 10;
				_itemWindow.item[4][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//11��°ĭ�� �������� �������
			if (itemType[14] == (ITEMNAME)j &&
				itemType[14] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[0][2].centerX, _itemWindow.item[0][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������11", "����"));
				_item->_item.itemPos = 11;
				_itemWindow.item[0][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//12��°ĭ�� �������� �������
			if (itemType[15] == (ITEMNAME)j &&
				itemType[15] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[1][2].centerX, _itemWindow.item[1][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������12", "����"));
				_item->_item.itemPos = 12;
				_itemWindow.item[1][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//13��°ĭ�� �������� �������
			if (itemType[16] == (ITEMNAME)j &&
				itemType[16] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[2][2].centerX, _itemWindow.item[2][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������13", "����"));
				_item->_item.itemPos = 13;
				_itemWindow.item[2][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//14��°ĭ�� �������� �������
			if (itemType[17] == (ITEMNAME)j &&
				itemType[17] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[3][2].centerX, _itemWindow.item[3][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������14", "����"));
				_item->_item.itemPos = 14;
				_itemWindow.item[3][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//15��°ĭ�� �������� �������
			if (itemType[18] == (ITEMNAME)j &&
				itemType[18] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[4][2].centerX, _itemWindow.item[4][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������15", "����"));
				_item->_item.itemPos = 15;
				_itemWindow.item[4][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}
		}
	}


	_isLoadSetItem = true;
}

void itemWindow::selectItem(tileMap * tileMap)
{
	if (_isClickItem == true) return;


	//������ �ٸ����ϱ�

	//���ǵ� �ٸ����ϱ�

	for (int i = 0; i < tileMap->_vItem.size(); ++i)
	{
		//�ش� �������� �����������
		if (PtInRect(&tileMap->_vItem[i]->_item.selectRc,
			PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
		{
			//�����Ѿ����۰� ��ġ(Ʈ�簪���ش�)
			tileMap->_vItem[i]->_item.isSelect = true;
			_isClickItem = true;

			//�ش�ĭ ������ĭ�� �������� �����Ƿ� false ���ְ�
			for (int k = 0; k < 3; ++k)
			{
				for (int d = 0; d < 5; ++d)
				{
					if (tileMap->_vItem[i]->_item.itemPos == _itemWindow.item[d][k].itemPos)
					{
						_itemWindow.item[d][k].isExistItem = false;
					}
				}
			}

			//�ش�ĭ �÷��̾�����â �������� �����Ƿ� false ���ְ�
			for (int k = 0; k < 4; ++k)
			{
				for (int d = 0; d < 3; ++d)
				{
					if (PtInRect(&_itemWindow.pw[d][k].rc,
						PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
					{
						if (_itemWindow.pw[d][k].playerWear == TYPE_NONE) continue;

						_itemWindow.pw[d][k].isExistItem = false;
					}
				}
			}

			_isTime = true;

			//���İ� �����ֱ�
			tileMap->_vItem[i]->_item.alphaIndex = 150;
		}
	}
}

void itemWindow::switchItem(tileMap * tileMap)
{
	if (_isClickItem == false) return;

	//������ĭ ����
	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < 5; ++i)
		{
			if (PtInRect(&_itemWindow.item[i][j].rc,
				PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
			{

				//���������� �� ������ ������ĭ�� ����������
				if (_itemWindow.item[i][j].isExistItem == false)
				{
					for (int k = 0; k < tileMap->_vItem.size(); ++k)
					{
						if (tileMap->_vItem[k]->_item.isSelect == false) continue;
						if (tileMap->_vItem[k]->_item.itemPos == _itemWindow.item[i][j].itemPos) continue;

						//���� ĭ�� �־��� ������ �������ֽð�
						deleteInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);

						_itemWindow.item[i][j].isExistItem = true;
						tileMap->_vItem[k]->_item.alphaIndex = 255;
						tileMap->_vItem[k]->_item.itemPos = _itemWindow.item[i][j].itemPos;
						tileMap->_vItem[k]->_item.centerX = _itemWindow.item[i][j].centerX;
						tileMap->_vItem[k]->_item.centerY = _itemWindow.item[i][j].centerY;
						tileMap->_vItem[k]->_item.isSelect = false;
						tileMap->_vItem[k]->_item.isWeared = false;
						_isClickItem = false;
						_isAbleSameClick = false;

						//���ο�ĭ�� ���� �÷����� �������� �����Ѵ�
						saveInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);

						////���� ��ġ�Ѵ�
						//tileMap->_vItem.clear();
						//setItem(tileMap);

						return;
					}
				}

				//���������� �� ������ ������ĭ�� ����������
				if (_itemWindow.item[i][j].isExistItem == false && _isAbleSameClick == true)
				{
					for (int k = 0; k < tileMap->_vItem.size(); ++k)
					{
						if (tileMap->_vItem[k]->_item.isSelect == false) continue;

						//���� ĭ�� �־��� ������ �������ֽð�
						deleteInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);

						_itemWindow.item[i][j].isExistItem = true;
						tileMap->_vItem[k]->_item.alphaIndex = 255;
						tileMap->_vItem[k]->_item.itemPos = _itemWindow.item[i][j].itemPos;
						tileMap->_vItem[k]->_item.centerX = _itemWindow.item[i][j].centerX;
						tileMap->_vItem[k]->_item.centerY = _itemWindow.item[i][j].centerY;
						tileMap->_vItem[k]->_item.isSelect = false;
						tileMap->_vItem[k]->_item.isWeared = false;
						_isClickItem = false;
						_isAbleSameClick = false;

						//���ο�ĭ�� ���� �÷����� �������� �����Ѵ�
						saveInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);

						////���ι�ġ�Ѵ�
						//tileMap->_vItem.clear();
						//setItem(tileMap);

						return;
					}
				}

				//���� �������� �������(���� ����Ī����)
				if (_itemWindow.item[i][j].isExistItem == true)
				{
					for (int k = 0; k < tileMap->_vItem.size(); ++k)
					{
						if (tileMap->_vItem[k]->_item.isSelect == true) continue;

						if (_itemWindow.item[i][j].itemPos == tileMap->_vItem[k]->_item.itemPos)
						{
							for (int h = 0; h < tileMap->_vItem.size(); ++h)
							{
								if (tileMap->_vItem[h]->_item.isSelect == false) continue;
								
								//���� ����־��� �������� ������ĭ�� �÷�����
								int tempPos = tileMap->_vItem[h]->_item.itemPos;
								tileMap->_vItem[h]->_item.isSelect = false;
								tileMap->_vItem[k]->_item.isWeared = false;
								tileMap->_vItem[h]->_item.alphaIndex = 255;
								tileMap->_vItem[h]->_item.itemPos = _itemWindow.item[i][j].itemPos;
								tileMap->_vItem[h]->_item.centerX = _itemWindow.item[i][j].centerX;
								tileMap->_vItem[h]->_item.centerY = _itemWindow.item[i][j].centerY;

								//�ٲ� pos�� �����Ѵ�
								saveInidata(tileMap, tileMap->_vItem[h]->_item.itemPos);

								//Ŭ���� ������ĭ�� ���ø���.
								tileMap->_vItem[k]->_item.itemPos = tempPos;
								tileMap->_vItem[k]->_item.alphaIndex = 155;
								tileMap->_vItem[k]->_item.isSelect = true;
								_isTime = true;

								//�ٲ� pos�� �����Ѵ�
								saveInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);

								////���ι�ġ�Ѵ�
								//tileMap->_vItem.clear();
								//setItem(tileMap);

								return;
							}
						}
					}
				}
			}
		}
	}

	//������ ����
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (PtInRect(&_itemWindow.pw[i][j].rc, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
			{
				if (_itemWindow.pw[i][j].playerWear == WEAR_NONE) continue;

				//������ �÷��̾������ĭ�� ����������
				if (_itemWindow.pw[i][j].isExistItem == false && _isAbleSameClick == true)
				{
					for (int k = 0; k < tileMap->_vItem.size(); ++k)
					{
						if (tileMap->_vItem[k]->_item.isSelect == false) continue;
						
						//������ �������� �����̰� Ŭ���Ѻκ��� pw â�� ����ϰ��
						if (tileMap->_vItem[k]->_item.itemType == TYPE_HELMET &&
							_itemWindow.pw[i][j].playerWear == WEAR_HELMET)
						{
							deleteInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);

							tileMap->_vItem[k]->_item.isWeared = true;
							tileMap->_vItem[k]->_item.centerX = _itemWindow.pw[i][j].centerX;
							tileMap->_vItem[k]->_item.centerY = _itemWindow.pw[i][j].centerY + 20;
							tileMap->_vItem[k]->_item.alphaIndex = 255;
							tileMap->_vItem[k]->_item.itemPos = 0;
							_isClickItem = false;
							_isAbleSameClick = false;

							//���ο�ĭ�� ���� �÷����� �������� �����Ѵ�
							saveInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);
							return;
						}

						//������ �������� �����̰� Ŭ���Ѻκ��� pw â�� �����ϰ��
						if ((tileMap->_vItem[k]->_item.itemType == TYPE_SPEAR ||
							tileMap->_vItem[k]->_item.itemType == TYPE_CLUB ||
							tileMap->_vItem[k]->_item.itemType == TYPE_HATCHAT) &&
							_itemWindow.pw[i][j].playerWear == WEAR_WEAPON)
						{
							deleteInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);

							tileMap->_vItem[k]->_item.isWeared = true;
							tileMap->_vItem[k]->_item.centerX = _itemWindow.pw[i][j].centerX;
							tileMap->_vItem[k]->_item.centerY = _itemWindow.pw[i][j].centerY + 20;
							tileMap->_vItem[k]->_item.alphaIndex = 255;
							tileMap->_vItem[k]->_item.itemPos = 0;
							_isClickItem = false;
							_isAbleSameClick = false;

							//���ο�ĭ�� ���� �÷����� �������� �����Ѵ�
							saveInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);
							return;
						}

						//������ �������� �����̰� Ŭ���Ѻκ��� pw â�� �����ϰ��
						if (tileMap->_vItem[k]->_item.itemType == TYPE_ARMOR &&
							_itemWindow.pw[i][j].playerWear == WEAR_ARMOR)
						{
							deleteInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);

							tileMap->_vItem[k]->_item.isWeared = true;
							tileMap->_vItem[k]->_item.centerX = _itemWindow.pw[i][j].centerX;
							tileMap->_vItem[k]->_item.centerY = _itemWindow.pw[i][j].centerY + 20;
							tileMap->_vItem[k]->_item.alphaIndex = 255;
							tileMap->_vItem[k]->_item.itemPos = 0;
							_isClickItem = false;
							_isAbleSameClick = false;

							//���ο�ĭ�� ���� �÷����� �������� �����Ѵ�
							saveInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);
							return;
						}

						//������ �������� �����̰� Ŭ���Ѻκ��� pw â�� �����ϰ��
						if (tileMap->_vItem[k]->_item.itemType == TYPE_RIDE_BOOK &&
							_itemWindow.pw[i][j].playerWear == WEAR_RIDE_BOOK)
						{
							int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
							int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

							//�÷��̾�1�� �α����߰�
							if (loginPlayer1 == (int)INFO_YES)
							{
								int playerType = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "����");

								//����ϰ��
								if (playerType == (int)INFO_BLUE)
								{
									//������ž�¹����� �ƴҰ�� �����Ѵ�
									if (tileMap->_vItem[k]->_item.ItemName != ITEM_VERGA_RIDE_BOOK) return;
								}

								//�����ϰ��
								if (playerType == (int)INFO_RED)
								{
									//����ž�¹����� �ƴҰ�� �����Ѵ�
									if (tileMap->_vItem[k]->_item.ItemName != ITEM_GORGOR_RIDE_BOOK) return;
								}
							}

							//�÷��̾�2�� �α����߰�
							if (loginPlayer2 == (int)INFO_YES)
							{
								int playerType = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "����");

								//����ϰ��
								if (playerType == (int)INFO_BLUE)
								{
									//������ž�¹����� �ƴҰ�� �����Ѵ�
									if (tileMap->_vItem[k]->_item.ItemName != ITEM_VERGA_RIDE_BOOK) return;
								}

								//�����ϰ��
								if (playerType == (int)INFO_RED)
								{
									//����ž�¹����� �ƴҰ�� �����Ѵ�
									if (tileMap->_vItem[k]->_item.ItemName != ITEM_GORGOR_RIDE_BOOK) return;
								}
							}

							deleteInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);

							tileMap->_vItem[k]->_item.isWeared = true;
							tileMap->_vItem[k]->_item.centerX = _itemWindow.pw[i][j].centerX;
							tileMap->_vItem[k]->_item.centerY = _itemWindow.pw[i][j].centerY + 20;
							tileMap->_vItem[k]->_item.alphaIndex = 255;
							tileMap->_vItem[k]->_item.itemPos = 0;
							_isClickItem = false;
							_isAbleSameClick = false;

							//���ο�ĭ�� ���� �÷����� �������� �����Ѵ�
							saveInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);
							return;
						}
					}
				}
			}
		}
	}
}

void itemWindow::updateSelectItem(tileMap * tileMap)
{
	for (int i = 0; i < tileMap->_vItem.size(); ++i)
	{
		//�����Ѿ����۰� ��ġ(Ʈ�簪�� �ִ� ���콺�� ����ٴѴ�)
		if (tileMap->_vItem[i]->_item.isSelect == true)
		{
			tileMap->_vItem[i]->_item.centerX = _ptMouse.x + tileMap->getCameraBufferX();
			tileMap->_vItem[i]->_item.centerY = _ptMouse.y + tileMap->getCameraBufferY();
			tileMap->_vItem[i]->_item.imgRc = RectMakeCenter(tileMap->_vItem[i]->_item.centerX, tileMap->_vItem[i]->_item.centerY,
				tileMap->_vItem[i]->_item.img->getFrameWidth(), tileMap->_vItem[i]->_item.img->getFrameHeight());
			tileMap->_vItem[i]->_item.selectRc = RectMakeCenter(tileMap->_vItem[i]->_item.centerX, tileMap->_vItem[i]->_item.centerY,
				30, 30);
		}
	}
}

void itemWindow::updateItem(tileMap * tileMap)
{
	//������â�� ���߱�
	for (int i = 0; i < tileMap->_vItem.size(); ++i)
	{
		if (tileMap->_vItem[i]->_item.isSelect == true) continue;

		//������ �����������
		if (tileMap->_vItem[i]->_item.isWeared == true &&
			tileMap->_vItem[i]->_item.itemType == TYPE_HELMET)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.pw[1][0].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.pw[1][0].centerY + 10;
		}

		//���⸦ �����������
		if (tileMap->_vItem[i]->_item.isWeared == true &&
			(tileMap->_vItem[i]->_item.itemType == TYPE_SPEAR ||
			tileMap->_vItem[i]->_item.itemType == TYPE_CLUB ||
			tileMap->_vItem[i]->_item.itemType == TYPE_HATCHAT))
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.pw[0][1].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.pw[0][1].centerY + 10;
		}

		//������ �����������
		if (tileMap->_vItem[i]->_item.isWeared == true &&
			tileMap->_vItem[i]->_item.itemType == TYPE_ARMOR)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.pw[1][1].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.pw[1][1].centerY + 10;
		}

		//���̵� å�� �����������
		if (tileMap->_vItem[i]->_item.isWeared == true &&
			tileMap->_vItem[i]->_item.itemType == TYPE_RIDE_BOOK)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.pw[1][2].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.pw[1][2].centerY + 10;
		}

		//������ 1ĭ�� �������
		if (tileMap->_vItem[i]->_item.itemPos == 1)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[0][0].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[0][0].centerY;
		}

		//������ 2ĭ�� �������
		if (tileMap->_vItem[i]->_item.itemPos == 2)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[1][0].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[1][0].centerY;
		}

		//������ 3ĭ�� �������
		if (tileMap->_vItem[i]->_item.itemPos == 3)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[2][0].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[2][0].centerY;
		}

		//������ 4ĭ�� �������
		if (tileMap->_vItem[i]->_item.itemPos == 4)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[3][0].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[3][0].centerY;
		}

		//������ 5ĭ�� �������
		if (tileMap->_vItem[i]->_item.itemPos == 5)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[4][0].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[4][0].centerY;
		}

		//������ 6ĭ�� �������
		if (tileMap->_vItem[i]->_item.itemPos == 6)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[0][1].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[0][1].centerY;
		}

		//������ 7ĭ�� �������
		if (tileMap->_vItem[i]->_item.itemPos == 7)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[1][1].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[1][1].centerY;
		}

		//������ 8ĭ�� �������
		if (tileMap->_vItem[i]->_item.itemPos == 8)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[2][1].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[2][1].centerY;
		}

		//������ 9ĭ�� �������
		if (tileMap->_vItem[i]->_item.itemPos == 9)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[3][1].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[3][1].centerY;
		}

		//������ 10ĭ�� �������
		if (tileMap->_vItem[i]->_item.itemPos == 10)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[4][1].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[4][1].centerY;
		}

		//������ 11ĭ�� �������
		if (tileMap->_vItem[i]->_item.itemPos == 11)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[0][2].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[0][2].centerY;
		}

		//������ 12ĭ�� �������
		if (tileMap->_vItem[i]->_item.itemPos == 12)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[1][2].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[1][2].centerY;
		}

		//������ 13ĭ�� �������
		if (tileMap->_vItem[i]->_item.itemPos == 13)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[2][2].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[2][2].centerY;
		}

		//������ 14ĭ�� �������
		if (tileMap->_vItem[i]->_item.itemPos == 14)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[3][2].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[3][2].centerY;
		}

		//������ 15ĭ�� �������
		if (tileMap->_vItem[i]->_item.itemPos == 15)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[4][2].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[4][2].centerY;
		}

		//��Ʈ �ٷιٷ� �������ֱ�
		tileMap->_vItem[i]->_item.imgRc = RectMakeCenter(tileMap->_vItem[i]->_item.centerX, tileMap->_vItem[i]->_item.centerY,
			tileMap->_vItem[i]->_item.img->getFrameWidth(), tileMap->_vItem[i]->_item.img->getFrameHeight());
		tileMap->_vItem[i]->_item.selectRc = RectMakeCenter(tileMap->_vItem[i]->_item.centerX, tileMap->_vItem[i]->_item.centerY,
			30, 30);
	}
}

void itemWindow::itemRender(tileMap * tileMap)
{
	if (tileMap->_vItem.size() == 0) return;

	for (int i = 0; i < tileMap->_vItem.size(); ++i)
	{
		tileMap->_vItem[i]->render();
	}
}

void itemWindow::textRender(tileMap * tileMap)
{
	//�Ӵ� ����
	HFONT font2 = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY������B"));
	HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), font2);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(230, 230, 230));

	char stone[256];
	RECT TextBox = RectMake(CAMERAMANAGER->getCameraRIGHT() - 97,
		CAMERAMANAGER->getCameraTOP() + 75, 80, 24);

	DrawText(getMemDC(), _itoa(_playerStone, stone, 10), strlen(_itoa(_playerStone, stone, 10)),
		&TextBox, DT_RIGHT | DT_VCENTER | BS_MULTILINE);

	SelectObject(getMemDC(), oldFont2);
	DeleteObject(font2);
	SetBkMode(getMemDC(), OPAQUE);

	//������ ������
	if (_isClickItem == false)
	{
		for (int i = 0; i < tileMap->_vItem.size(); ++i)
		{
			if (PtInRect(&tileMap->_vItem[i]->_item.selectRc,
				PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
			{
				//����, ��������, ����
				HFONT font = CreateFont(17, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
					0, 0, 0, 0, TEXT("HY������B"));
				HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
				SetBkMode(getMemDC(), TRANSPARENT);

				//����
				SetTextColor(getMemDC(), RGB(80, 255, 255));
				TextOut(getMemDC(), CAMERAMANAGER->getCameraRIGHT() - 255, CAMERAMANAGER->getCameraTOP() + 345,
					tileMap->_vItem[i]->_item.name.c_str(), strlen(tileMap->_vItem[i]->_item.name.c_str()));

				//������
				SetTextColor(getMemDC(), RGB(255, 30, 30));
				TextOut(getMemDC(), CAMERAMANAGER->getCameraRIGHT() - 200, CAMERAMANAGER->getCameraTOP() + 395,
					tileMap->_vItem[i]->_item.sellPrice.c_str(), strlen(tileMap->_vItem[i]->_item.sellPrice.c_str()));

				//����
				char price[256];
				SetTextColor(getMemDC(), RGB(255, 30, 30));
				TextOut(getMemDC(), CAMERAMANAGER->getCameraRIGHT() - 120, CAMERAMANAGER->getCameraTOP() + 395,
					_itoa(tileMap->_vItem[i]->_item.price, price, 10), strlen(_itoa(tileMap->_vItem[i]->_item.price, price, 10)));

				SelectObject(getMemDC(), oldFont);
				DeleteObject(font);
				SetBkMode(getMemDC(), OPAQUE);

				//����
				HFONT font1 = CreateFont(12, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
					0, 0, 0, 0, TEXT("HY������B"));
				HFONT oldFont1 = (HFONT)SelectObject(getMemDC(), font1);
				SetBkMode(getMemDC(), TRANSPARENT);

				SetTextColor(getMemDC(), RGB(255, 255, 255));
				TextOut(getMemDC(), CAMERAMANAGER->getCameraRIGHT() - 255, CAMERAMANAGER->getCameraTOP() + 380,
					tileMap->_vItem[i]->_item.itemExplain.c_str(), strlen(tileMap->_vItem[i]->_item.itemExplain.c_str()));

				SelectObject(getMemDC(), oldFont1);
				DeleteObject(font1);
				SetBkMode(getMemDC(), OPAQUE);
			}
		}
	}

}

void itemWindow::deleteInidata(tileMap * tileMap, int itemPos)
{
	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	//�÷��̾� 1�� �α����������
	if (loginPlayer1 == (int)INFO_YES)
	{
		if (itemPos == 0)
		{
			for (int i = 0; i < tileMap->_vItem.size(); ++i)
			{
				if (tileMap->_vItem[i]->_item.isSelect == false) continue;

				if (tileMap->_vItem[i]->_item.itemType == TYPE_HELMET)
				{
					INIDATA->deleteDataAll("�÷��̾�1_������", "��������");
				}

				if (tileMap->_vItem[i]->_item.itemType == TYPE_CLUB || 
					tileMap->_vItem[i]->_item.itemType == TYPE_SPEAR ||
					tileMap->_vItem[i]->_item.itemType == TYPE_HATCHAT)
				{
					INIDATA->deleteDataAll("�÷��̾�1_������", "��������");
				}

				if (tileMap->_vItem[i]->_item.itemType == TYPE_ARMOR)
				{
					INIDATA->deleteDataAll("�÷��̾�1_������", "��������");
				}

				if (tileMap->_vItem[i]->_item.itemType == TYPE_RIDE_BOOK)
				{
					INIDATA->deleteDataAll("�÷��̾�1_������", "ž�¹�������");
				}
			}
		}
		if (itemPos == 1) INIDATA->deleteDataAll("�÷��̾�1_������", "������1");
		if (itemPos == 2) INIDATA->deleteDataAll("�÷��̾�1_������", "������2");
		if (itemPos == 3) INIDATA->deleteDataAll("�÷��̾�1_������", "������3");
		if (itemPos == 4) INIDATA->deleteDataAll("�÷��̾�1_������", "������4");
		if (itemPos == 5) INIDATA->deleteDataAll("�÷��̾�1_������", "������5");
		if (itemPos == 6) INIDATA->deleteDataAll("�÷��̾�1_������", "������6");
		if (itemPos == 7) INIDATA->deleteDataAll("�÷��̾�1_������", "������7");
		if (itemPos == 8) INIDATA->deleteDataAll("�÷��̾�1_������", "������8");
		if (itemPos == 9) INIDATA->deleteDataAll("�÷��̾�1_������", "������9");
		if (itemPos == 10) INIDATA->deleteDataAll("�÷��̾�1_������", "������10");
		if (itemPos == 11) INIDATA->deleteDataAll("�÷��̾�1_������", "������11");
		if (itemPos == 12) INIDATA->deleteDataAll("�÷��̾�1_������", "������12");
		if (itemPos == 13) INIDATA->deleteDataAll("�÷��̾�1_������", "������13");
		if (itemPos == 14) INIDATA->deleteDataAll("�÷��̾�1_������", "������14");
		if (itemPos == 15) INIDATA->deleteDataAll("�÷��̾�1_������", "������15");
	}

	//�÷��̾� 2�� �α����������
	if (loginPlayer2 == (int)INFO_YES)
	{
		if (itemPos == 0)
		{
			for (int i = 0; i < tileMap->_vItem.size(); ++i)
			{
				if (tileMap->_vItem[i]->_item.isSelect == false) continue;

				if (tileMap->_vItem[i]->_item.itemType == TYPE_HELMET)
				{
					INIDATA->deleteDataAll("�÷��̾�2_������", "��������");
				}

				if (tileMap->_vItem[i]->_item.itemType == TYPE_CLUB ||
					tileMap->_vItem[i]->_item.itemType == TYPE_SPEAR ||
					tileMap->_vItem[i]->_item.itemType == TYPE_HATCHAT)
				{
					INIDATA->deleteDataAll("�÷��̾�2_������", "��������");
				}

				if (tileMap->_vItem[i]->_item.itemType == TYPE_ARMOR)
				{
					INIDATA->deleteDataAll("�÷��̾�2_������", "��������");
				}

				if (tileMap->_vItem[i]->_item.itemType == TYPE_RIDE_BOOK)
				{
					INIDATA->deleteDataAll("�÷��̾�2_������", "ž�¹�������");
				}
			}
		}
		if (itemPos == 1) INIDATA->deleteDataAll("�÷��̾�2_������", "������1");
		if (itemPos == 2) INIDATA->deleteDataAll("�÷��̾�2_������", "������2");
		if (itemPos == 3) INIDATA->deleteDataAll("�÷��̾�2_������", "������3");
		if (itemPos == 4) INIDATA->deleteDataAll("�÷��̾�2_������", "������4");
		if (itemPos == 5) INIDATA->deleteDataAll("�÷��̾�2_������", "������5");
		if (itemPos == 6) INIDATA->deleteDataAll("�÷��̾�2_������", "������6");
		if (itemPos == 7) INIDATA->deleteDataAll("�÷��̾�2_������", "������7");
		if (itemPos == 8) INIDATA->deleteDataAll("�÷��̾�2_������", "������8");
		if (itemPos == 9) INIDATA->deleteDataAll("�÷��̾�2_������", "������9");
		if (itemPos == 10) INIDATA->deleteDataAll("�÷��̾�2_������", "������10");
		if (itemPos == 11) INIDATA->deleteDataAll("�÷��̾�2_������", "������11");
		if (itemPos == 12) INIDATA->deleteDataAll("�÷��̾�2_������", "������12");
		if (itemPos == 13) INIDATA->deleteDataAll("�÷��̾�2_������", "������13");
		if (itemPos == 14) INIDATA->deleteDataAll("�÷��̾�2_������", "������14");
		if (itemPos == 15) INIDATA->deleteDataAll("�÷��̾�2_������", "������15");
	}
}

void itemWindow::saveInidata(tileMap * tileMap, int itemPos)
{
	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	for (int i = 0; i < tileMap->_vItem.size(); ++i)
	{
		//�÷��̾� 1�� �α����������
		if (loginPlayer1 == (int)INFO_YES)
		{
			if (tileMap->_vItem[i]->_item.itemPos == itemPos)
			{
				//0��° �����������ΰ��� �����Ѱ����
				if (itemPos == 0)
				{
					if (tileMap->_vItem[i]->_item.isSelect == false) continue;

					if (tileMap->_vItem[i]->_item.itemType == TYPE_HELMET)
					{
						char itemName[256];
						INIDATA->addData("��������", "����",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						char attackPower[256];
						INIDATA->addData("��������", "���ݷ�",
							_itoa((int)tileMap->_vItem[i]->_item.attackPower, attackPower, 10));
						char defensePower[256];
						INIDATA->addData("��������", "����",
							_itoa((int)tileMap->_vItem[i]->_item.defensePower, defensePower, 10));
						char speedPower[256];
						INIDATA->addData("��������", "���߷�",
							_itoa((int)tileMap->_vItem[i]->_item.speedPower, speedPower, 10));
						INIDATA->iniSave("�÷��̾�1_������");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
					if (tileMap->_vItem[i]->_item.itemType == TYPE_CLUB ||
						tileMap->_vItem[i]->_item.itemType == TYPE_SPEAR ||
						tileMap->_vItem[i]->_item.itemType == TYPE_HATCHAT)
					{
						char itemName[256];
						INIDATA->addData("��������", "����",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						char attackPower[256];
						INIDATA->addData("��������", "���ݷ�",
							_itoa((int)tileMap->_vItem[i]->_item.attackPower, attackPower, 10));
						char defensePower[256];
						INIDATA->addData("��������", "����",
							_itoa((int)tileMap->_vItem[i]->_item.defensePower, defensePower, 10));
						char speedPower[256];
						INIDATA->addData("��������", "���߷�",
							_itoa((int)tileMap->_vItem[i]->_item.speedPower, speedPower, 10));
						INIDATA->iniSave("�÷��̾�1_������");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
					if (tileMap->_vItem[i]->_item.itemType == TYPE_ARMOR)
					{
						char itemName[256];
						INIDATA->addData("��������", "����",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						char attackPower[256];
						INIDATA->addData("��������", "���ݷ�",
							_itoa((int)tileMap->_vItem[i]->_item.attackPower, attackPower, 10));
						char defensePower[256];
						INIDATA->addData("��������", "����",
							_itoa((int)tileMap->_vItem[i]->_item.defensePower, defensePower, 10));
						char speedPower[256];
						INIDATA->addData("��������", "���߷�",
							_itoa((int)tileMap->_vItem[i]->_item.speedPower, speedPower, 10));
						INIDATA->iniSave("�÷��̾�1_������");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
					if (tileMap->_vItem[i]->_item.itemType == TYPE_RIDE_BOOK)
					{
						char itemName[256];
						INIDATA->addData("ž�¹�������", "����",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						INIDATA->iniSave("�÷��̾�1_������");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
				}
				//1��° ������ĭ�� ���� �������
				if (itemPos == 1)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������1", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������1", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�1_������");
					return;
				}

				//2��° ������ĭ�� ���� �������
				if (itemPos == 2)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������2", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������2", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�1_������");
					return;
				}

				//3��° ������ĭ�� ���� �������
				if (itemPos == 3)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������3", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������3", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�1_������");
					return;
				}

				//4��° ������ĭ�� ���� �������
				if (itemPos == 4)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������4", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������4", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�1_������");
					return;
				}

				//5��° ������ĭ�� ���� �������
				if (itemPos == 5)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������5", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������5", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�1_������");
					return;
				}

				//6��° ������ĭ�� ���� �������
				if (itemPos == 6)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������6", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������6", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�1_������");
					return;
				}

				//7��° ������ĭ�� ���� �������
				if (itemPos == 7)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������7", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������7", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�1_������");
					return;
				}

				//8��° ������ĭ�� ���� �������
				if (itemPos == 8)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������8", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������8", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�1_������");
					return;
				}

				//9��° ������ĭ�� ���� �������
				if (itemPos == 9)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������9", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������9", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�1_������");
					return;
				}

				//10��° ������ĭ�� ���� �������
				if (itemPos == 10)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������10", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������10", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�1_������");
					return;
				}

				//11��° ������ĭ�� ���� �������
				if (itemPos == 11)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������11", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������11", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�1_������");
					return;
				}

				//12��° ������ĭ�� ���� �������
				if (itemPos == 12)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������12", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������12", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�1_������");
					return;
				}

				//13��° ������ĭ�� ���� �������
				if (itemPos == 13)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������13", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������13", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�1_������");
					return;
				}

				//14��° ������ĭ�� ���� �������
				if (itemPos == 14)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������14", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������14", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�1_������");
					return;
				}

				//12��° ������ĭ�� ���� �������
				if (itemPos == 15)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������15", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������15", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�1_������");
					return;
				}
			}
		}

		//�÷��̾� 2�� �α����������
		if (loginPlayer2 == (int)INFO_YES)
		{
			if (tileMap->_vItem[i]->_item.itemPos == itemPos)
			{
				//0��° �����������ΰ��� �����Ѱ����
				if (itemPos == 0)
				{
					if (tileMap->_vItem[i]->_item.isSelect == false) continue;

					if (tileMap->_vItem[i]->_item.itemType == TYPE_HELMET)
					{
						char itemName[256];
						INIDATA->addData("��������", "����",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						char attackPower[256];
						INIDATA->addData("��������", "���ݷ�",
							_itoa((int)tileMap->_vItem[i]->_item.attackPower, attackPower, 10));
						char defensePower[256];
						INIDATA->addData("��������", "����",
							_itoa((int)tileMap->_vItem[i]->_item.defensePower, defensePower, 10));
						char speedPower[256];
						INIDATA->addData("��������", "���߷�",
							_itoa((int)tileMap->_vItem[i]->_item.speedPower, speedPower, 10));
						INIDATA->iniSave("�÷��̾�2_������");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
					if (tileMap->_vItem[i]->_item.itemType == TYPE_CLUB ||
						tileMap->_vItem[i]->_item.itemType == TYPE_SPEAR ||
						tileMap->_vItem[i]->_item.itemType == TYPE_HATCHAT)
					{
						char itemName[256];
						INIDATA->addData("��������", "����",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						char attackPower[256];
						INIDATA->addData("��������", "���ݷ�",
							_itoa((int)tileMap->_vItem[i]->_item.attackPower, attackPower, 10));
						char defensePower[256];
						INIDATA->addData("��������", "����",
							_itoa((int)tileMap->_vItem[i]->_item.defensePower, defensePower, 10));
						char speedPower[256];
						INIDATA->addData("��������", "���߷�",
							_itoa((int)tileMap->_vItem[i]->_item.speedPower, speedPower, 10));
						INIDATA->iniSave("�÷��̾�2_������");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
					if (tileMap->_vItem[i]->_item.itemType == TYPE_ARMOR)
					{
						char itemName[256];
						INIDATA->addData("��������", "����",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						char attackPower[256];
						INIDATA->addData("��������", "���ݷ�",
							_itoa((int)tileMap->_vItem[i]->_item.attackPower, attackPower, 10));
						char defensePower[256];
						INIDATA->addData("��������", "����",
							_itoa((int)tileMap->_vItem[i]->_item.defensePower, defensePower, 10));
						char speedPower[256];
						INIDATA->addData("��������", "���߷�",
							_itoa((int)tileMap->_vItem[i]->_item.speedPower, speedPower, 10));
						INIDATA->iniSave("�÷��̾�2_������");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
					if (tileMap->_vItem[i]->_item.itemType == TYPE_RIDE_BOOK)
					{
						char itemName[256];
						INIDATA->addData("ž�¹�������", "����",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						INIDATA->iniSave("�÷��̾�2_������");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
				}

				//1��° ������ĭ�� ���� �������
				if (itemPos == 1)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������1", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������1", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�2_������");
					return;
				}

				//2��° ������ĭ�� ���� �������
				if (itemPos == 2)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������2", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������2", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�2_������");
					return;
				}

				//3��° ������ĭ�� ���� �������
				if (itemPos == 3)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������3", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������3", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�2_������");
					return;
				}

				//4��° ������ĭ�� ���� �������
				if (itemPos == 4)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������4", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������4", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�2_������");
					return;
				}

				//5��° ������ĭ�� ���� �������
				if (itemPos == 5)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������5", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������5", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�2_������");
					return;
				}

				//6��° ������ĭ�� ���� �������
				if (itemPos == 6)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������6", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������6", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�2_������");
					return;
				}

				//7��° ������ĭ�� ���� �������
				if (itemPos == 7)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������7", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������7", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�2_������");
					return;
				}

				//8��° ������ĭ�� ���� �������
				if (itemPos == 8)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������8", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������8", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�2_������");
					return;
				}

				//9��° ������ĭ�� ���� �������
				if (itemPos == 9)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������9", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������9", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�2_������");
					return;
				}

				//10��° ������ĭ�� ���� �������
				if (itemPos == 10)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������10", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������10", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�2_������");
					return;
				}

				//11��° ������ĭ�� ���� �������
				if (itemPos == 11)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������11", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������11", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�2_������");
					return;
				}

				//12��° ������ĭ�� ���� �������
				if (itemPos == 12)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������12", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������12", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�2_������");
					return;
				}

				//13��° ������ĭ�� ���� �������
				if (itemPos == 13)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������13", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������13", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�2_������");
					return;
				}

				//14��° ������ĭ�� ���� �������
				if (itemPos == 14)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������14", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������14", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�2_������");
					return;
				}

				//12��° ������ĭ�� ���� �������
				if (itemPos == 15)
				{
					//���� �����ϰ�
					char itemName[256];
					INIDATA->addData("������15", "����",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//������ �����ϰ�
					char itemNum[256];
					INIDATA->addData("������15", "����",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("�÷��̾�2_������");
					return;
				}
			}
		}
	}

}

void itemWindow::lineUpItem(tileMap * tileMap)
{
	//������ ���Ŀ����� �� ����
	if (_isClickItem == true) return;

	for (int k = tileMap->_vItem.size() - 1; k >= 0; --k)
	{
		if (tileMap->_vItem[k]->_item.isWeared == true) continue;

		for (int j = 2; j >= 0; --j)
		{
			for (int i = 4; i >= 0; --i)
			{
				if (_itemWindow.item[i][j].isExistItem == true) continue;

				if (_itemWindow.item[i][j].isExistItem == false)
				{
					int tempPos = tileMap->_vItem[k]->_item.itemPos;

					deleteInidata(tileMap, tempPos);

					for (int f = 0; f < 3; ++f)
					{
						for (int d = 0; d < 5; ++d)
						{
							if (_itemWindow.item[d][f].itemPos == tempPos)
							{
								_itemWindow.item[d][f].isExistItem = false;
								break;
							}
						}
					}

					tileMap->_vItem[k]->_item.itemPos = _itemWindow.item[i][j].itemPos;
					tileMap->_vItem[k]->_item.centerX = _itemWindow.item[i][j].centerX;
					tileMap->_vItem[k]->_item.centerY = _itemWindow.item[i][j].centerY;
					_itemWindow.item[i][j].isExistItem = true;

					saveInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);
				}
			}
		}
	}

}
