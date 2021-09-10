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

menuType * sellItemWindow::inputHandle(tileMap * tileMap)
{
	clickPage(tileMap);
	clickItem(tileMap);
	clickNotice(tileMap);

	if (tileMap->_isClickArmorNPC == false && tileMap->_isClickWeaponNPC == false)
	{
		exit(tileMap);
		SOUNDMANAGER->play("window_down", 0.4f);
		return new baseType();
	}

	if (PtInRect(&_sellWindow.returnRect,
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

void sellItemWindow::update(tileMap * tileMap)
{
	updateRect(tileMap);
	updateButton(tileMap);
	updateNotice(tileMap);

	if (PtInRect(&_sellWindow.frontRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
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
	if (_noticeWindow.isCheckNumber == false && _noticeWindow.isClickItem == false &&
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

void sellItemWindow::enter(tileMap * tileMap)
{
	setItem(tileMap);
	setSellWindow(tileMap);
	setNotice(tileMap);
}

void sellItemWindow::render(tileMap * tileMap)
{
	imageRender(tileMap);
	textRender(tileMap);
	noticeRender(tileMap);
	PtInRender(tileMap);
}

void sellItemWindow::exit(tileMap * tileMap)
{
	if (tileMap->_vItem.size() != 0)
	{
		tileMap->_vItem.clear();
	}
}

void sellItemWindow::setItem(tileMap * tileMap)
{
	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	//�÷��̾�1�� �α����������
	if (loginPlayer1 == (int)INFO_YES)
	{
		_sellWindow.playerStone = INIDATA->loadDataInterger("�÷��̾�1_������", "������", "�ݾ�");

		int playerItem[15];

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

		for (int i = 0; i < 17; ++i)
		{
			//ù��°ĭ ������Ȯ��
			if (playerItem[0] == (ITEMNAME)i &&
				playerItem[0] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������1", "����"));
				_item->_item.itemPos = 1;
				tileMap->_vItem.push_back(_item);
			}

			//�ι�°ĭ ������Ȯ��
			if (playerItem[1] == (ITEMNAME)i &&
				playerItem[1] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������2", "����"));
				_item->_item.itemPos = 2;
				tileMap->_vItem.push_back(_item);
			}

			//����°ĭ ������Ȯ��
			if (playerItem[2] == (ITEMNAME)i &&
				playerItem[2] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������3", "����"));
				_item->_item.itemPos = 3;
				tileMap->_vItem.push_back(_item);
			}

			//�׹�°ĭ ������Ȯ��
			if (playerItem[3] == (ITEMNAME)i &&
				playerItem[3] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������4", "����"));
				_item->_item.itemPos = 4;
				tileMap->_vItem.push_back(_item);
			}

			//�ټ���°ĭ ������Ȯ��
			if (playerItem[4] == (ITEMNAME)i &&
				playerItem[4] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������5", "����"));
				_item->_item.itemPos = 5;
				tileMap->_vItem.push_back(_item);
			}

			//������°ĭ ������Ȯ��
			if (playerItem[5] == (ITEMNAME)i &&
				playerItem[5] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������6", "����"));
				_item->_item.itemPos = 6;
				tileMap->_vItem.push_back(_item);
			}

			//�ϰ���°ĭ ������Ȯ��
			if (playerItem[6] == (ITEMNAME)i &&
				playerItem[6] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������7", "����"));
				_item->_item.itemPos = 7;
				tileMap->_vItem.push_back(_item);
			}

			//8��°ĭ ������Ȯ��
			if (playerItem[7] == (ITEMNAME)i &&
				playerItem[7] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������8", "����"));
				_item->_item.itemPos = 8;
				tileMap->_vItem.push_back(_item);
			}

			//9��°ĭ ������Ȯ��
			if (playerItem[8] == (ITEMNAME)i &&
				playerItem[8] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������9", "����"));
				_item->_item.itemPos = 9;
				tileMap->_vItem.push_back(_item);
			}

			//10��°ĭ ������Ȯ��
			if (playerItem[9] == (ITEMNAME)i &&
				playerItem[9] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������10", "����"));
				_item->_item.itemPos = 10;
				tileMap->_vItem.push_back(_item);
			}

			//11��°ĭ ������Ȯ��
			if (playerItem[10] == (ITEMNAME)i &&
				playerItem[10] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������11", "����"));
				_item->_item.itemPos = 11;
				tileMap->_vItem.push_back(_item);
			}

			//12��°ĭ ������Ȯ��
			if (playerItem[11] == (ITEMNAME)i &&
				playerItem[11] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������12", "����"));
				_item->_item.itemPos = 12;
				tileMap->_vItem.push_back(_item);
			}

			//13��°ĭ ������Ȯ��
			if (playerItem[12] == (ITEMNAME)i &&
				playerItem[12] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������13", "����"));
				_item->_item.itemPos = 13;
				tileMap->_vItem.push_back(_item);
			}

			//14��°ĭ ������Ȯ��
			if (playerItem[13] == (ITEMNAME)i &&
				playerItem[13] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������14", "����"));
				_item->_item.itemPos = 14;
				tileMap->_vItem.push_back(_item);
			}

			//15��°ĭ ������Ȯ��
			if (playerItem[14] == (ITEMNAME)i &&
				playerItem[14] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�1_������", "������15", "����"));
				_item->_item.itemPos = 15;
				tileMap->_vItem.push_back(_item);
			}
		}
	}

	//�÷��̾�2�� �α����������
	if (loginPlayer2 == (int)INFO_YES)
	{
		_sellWindow.playerStone = INIDATA->loadDataInterger("�÷��̾�2_������", "������", "�ݾ�");

		int playerItem[15];

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

		for (int i = 0; i < 17; ++i)
		{
			//ù��°ĭ ������Ȯ��
			if (playerItem[0] == (ITEMNAME)i &&
				playerItem[0] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�2_������", "������1", "����"));
				_item->_item.itemPos = 1;
				tileMap->_vItem.push_back(_item);
			}

			//�ι�°ĭ ������Ȯ��
			if (playerItem[1] == (ITEMNAME)i &&
				playerItem[1] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�2_������", "������2", "����"));
				_item->_item.itemPos = 2;
				tileMap->_vItem.push_back(_item);
			}

			//����°ĭ ������Ȯ��
			if (playerItem[2] == (ITEMNAME)i &&
				playerItem[2] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�2_������", "������3", "����"));
				_item->_item.itemPos = 3;
				tileMap->_vItem.push_back(_item);
			}

			//�׹�°ĭ ������Ȯ��
			if (playerItem[3] == (ITEMNAME)i &&
				playerItem[3] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�2_������", "������4", "����"));
				_item->_item.itemPos = 4;
				tileMap->_vItem.push_back(_item);
			}

			//�ټ���°ĭ ������Ȯ��
			if (playerItem[4] == (ITEMNAME)i &&
				playerItem[4] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�2_������", "������5", "����"));
				_item->_item.itemPos = 5;
				tileMap->_vItem.push_back(_item);
			}

			//������°ĭ ������Ȯ��
			if (playerItem[5] == (ITEMNAME)i &&
				playerItem[5] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�2_������", "������6", "����"));
				_item->_item.itemPos = 6;
				tileMap->_vItem.push_back(_item);
			}

			//�ϰ���°ĭ ������Ȯ��
			if (playerItem[6] == (ITEMNAME)i &&
				playerItem[6] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�2_������", "������7", "����"));
				_item->_item.itemPos = 7;
				tileMap->_vItem.push_back(_item);
			}

			//8��°ĭ ������Ȯ��
			if (playerItem[7] == (ITEMNAME)i &&
				playerItem[7] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�2_������", "������8", "����"));
				_item->_item.itemPos = 8;
				tileMap->_vItem.push_back(_item);
			}

			//9��°ĭ ������Ȯ��
			if (playerItem[8] == (ITEMNAME)i &&
				playerItem[8] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�2_������", "������9", "����"));
				_item->_item.itemPos = 9;
				tileMap->_vItem.push_back(_item);
			}

			//10��°ĭ ������Ȯ��
			if (playerItem[9] == (ITEMNAME)i &&
				playerItem[9] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�2_������", "������10", "����"));
				_item->_item.itemPos = 10;
				tileMap->_vItem.push_back(_item);
			}

			//11��°ĭ ������Ȯ��
			if (playerItem[10] == (ITEMNAME)i &&
				playerItem[10] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�2_������", "������11", "����"));
				_item->_item.itemPos = 11;
				tileMap->_vItem.push_back(_item);
			}

			//12��°ĭ ������Ȯ��
			if (playerItem[11] == (ITEMNAME)i &&
				playerItem[11] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�2_������", "������12", "����"));
				_item->_item.itemPos = 12;
				tileMap->_vItem.push_back(_item);
			}

			//13��°ĭ ������Ȯ��
			if (playerItem[12] == (ITEMNAME)i &&
				playerItem[12] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�2_������", "������13", "����"));
				_item->_item.itemPos = 13;
				tileMap->_vItem.push_back(_item);
			}

			//14��°ĭ ������Ȯ��
			if (playerItem[13] == (ITEMNAME)i &&
				playerItem[13] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�2_������", "������14", "����"));
				_item->_item.itemPos = 14;
				tileMap->_vItem.push_back(_item);
			}

			//15��°ĭ ������Ȯ��
			if (playerItem[14] == (ITEMNAME)i &&
				playerItem[14] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)i, PointMake(0, 0));
				_item->itemAmount(INIDATA->loadDataInterger("�÷��̾�2_������", "������15", "����"));
				_item->_item.itemPos = 15;
				tileMap->_vItem.push_back(_item);
			}
		}
	}


	//���Ϳ� ����� page �����ϱ�
	_sellWindow.maxPage = (int)((tileMap->_vItem.size() - 1) / 3) + 1;
	_sellWindow.currentPage = 1;

	for (int i = 0; i < tileMap->_vItem.size(); ++i)
	{
		if (i >= 0 && i <= 2)	tileMap->_vItem[i]->_item.sellPage = 1;
		if (i >= 3 && i <= 5)	tileMap->_vItem[i]->_item.sellPage = 2;
		if (i >= 6 && i <= 8)	tileMap->_vItem[i]->_item.sellPage = 3;
		if (i >= 9 && i <= 11)	tileMap->_vItem[i]->_item.sellPage = 4;
		if (i >= 12 && i <= 14)	tileMap->_vItem[i]->_item.sellPage = 5;
	}
}

void sellItemWindow::setSellWindow(tileMap * tileMap)
{
	_sellWindow.backImg = IMAGEMANAGER->findImage("shopWindowBack");
	_sellWindow.frontImg = IMAGEMANAGER->findImage("shopWindow");
	_sellWindow.leftButton.img = IMAGEMANAGER->findImage("leftButton");
	_sellWindow.rightButton.img = IMAGEMANAGER->findImage("rightButton");

	_sellWindow.leftButton.currentFrameX = 0;
	_sellWindow.leftButton.currentFrameY = 0;
	_sellWindow.rightButton.currentFrameX = 0;
	_sellWindow.rightButton.currentFrameY = 0;
	_sellWindow.leftButton.timeCount = 0;
	_sellWindow.rightButton.timeCount = 0;

	_ableCount = 0;
	_isDisableClick = false;
	_sellWindow.title = "�� ������ �ȱ�";
}

void sellItemWindow::updateRect(tileMap * tileMap)
{
	_sellWindow.backRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(),
		_sellWindow.backImg->getWidth(), _sellWindow.backImg->getHeight());
	_sellWindow.frontRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(),
		_sellWindow.frontImg->getWidth(), _sellWindow.frontImg->getHeight());
	_sellWindow.returnRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() + 1, CAMERAMANAGER->getCameraCenterY() + 186, 80, 16);
	_sellWindow.leftButton.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 170, CAMERAMANAGER->getCameraCenterY() - 127,
		_sellWindow.leftButton.img->getFrameWidth(), _sellWindow.leftButton.img->getFrameHeight());
	_sellWindow.rightButton.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 31, CAMERAMANAGER->getCameraCenterY() - 127,
		_sellWindow.rightButton.img->getFrameWidth(), _sellWindow.rightButton.img->getFrameHeight());

	//�����۷�Ʈ �׸���
	for (int i = 0; i < tileMap->_vItem.size(); ++i)
	{
		tileMap->_vItem[i]->_item.imgRc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 138, CAMERAMANAGER->getCameraCenterY() + 122,
			tileMap->_vItem[i]->_item.img->getFrameWidth(), tileMap->_vItem[i]->_item.img->getFrameHeight());

		if (_sellWindow.currentPage == tileMap->_vItem[i]->_item.sellPage)
		{
			tileMap->_vItem[i]->_item.selectRc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(),
				CAMERAMANAGER->getCameraCenterY() - 76 + (i % 3) * 55, 410, 43);
		}

		if (_sellWindow.currentPage != tileMap->_vItem[i]->_item.sellPage)
		{
			tileMap->_vItem[i]->_item.selectRc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 500,
				CAMERAMANAGER->getCameraTOP() - 500, 410, 43);
		}
	}
}

void sellItemWindow::saveInidata(tileMap * tileMap)
{
	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	//�÷��̾�1�� �α����������
	if (loginPlayer1 == (int)INFO_YES)
	{
		for (int i = 0; i < tileMap->_vItem.size(); ++i)
		{
			if (tileMap->_vItem[i]->_item.isSelect == false) continue;

			if (tileMap->_vItem[i]->_item.itemPos == 1)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�1_������", "������1");

				else INIDATA->addData("������1", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�1_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 2)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�1_������", "������2");

				else INIDATA->addData("������2", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�1_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 3)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�1_������", "������3");

				else INIDATA->addData("������3", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�1_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 4)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�1_������", "������4");

				else INIDATA->addData("������4", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�1_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 5)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�1_������", "������5");

				else INIDATA->addData("������5", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�1_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 6)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�1_������", "������6");

				else INIDATA->addData("������6", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�1_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 7)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�1_������", "������7");

				else INIDATA->addData("������7", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�1_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 8)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�1_������", "������8");

				else INIDATA->addData("������8", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�1_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 9)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�1_������", "������9");

				else INIDATA->addData("������9", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�1_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 10)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�1_������", "������10");

				else INIDATA->addData("������10", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�1_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 11)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�1_������", "������11");

				else INIDATA->addData("������11", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�1_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 12)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�1_������", "������12");

				else INIDATA->addData("������12", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�1_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 13)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�1_������", "������13");

				else INIDATA->addData("������13", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�1_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 14)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�1_������", "������14");

				else INIDATA->addData("������14", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�1_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 15)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�1_������", "������15");

				else INIDATA->addData("������15", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�1_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}
		}

	}

	//�÷��̾�1�� �α����������
	if (loginPlayer2 == (int)INFO_YES)
	{
		for (int i = 0; i < tileMap->_vItem.size(); ++i)
		{
			if (tileMap->_vItem[i]->_item.isSelect == false) continue;

			if (tileMap->_vItem[i]->_item.itemPos == 1)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�2_������", "������1");

				else INIDATA->addData("������1", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�2_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 2)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�2_������", "������2");

				else INIDATA->addData("������2", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�2_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 3)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�2_������", "������3");

				else INIDATA->addData("������3", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�2_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 4)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�2_������", "������4");

				else INIDATA->addData("������4", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�2_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 5)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�2_������", "������5");

				else INIDATA->addData("������5", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�2_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 6)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�2_������", "������6");

				else INIDATA->addData("������6", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�2_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 7)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�2_������", "������7");

				else INIDATA->addData("������7", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�2_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 8)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�2_������", "������8");

				else INIDATA->addData("������8", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�2_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 9)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�2_������", "������9");

				else INIDATA->addData("������9", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�2_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 10)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�2_������", "������10");

				else INIDATA->addData("������10", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�2_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 11)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�2_������", "������11");

				else INIDATA->addData("������11", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�2_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 12)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�2_������", "������12");

				else INIDATA->addData("������12", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�2_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 13)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�2_������", "������13");

				else INIDATA->addData("������13", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�2_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 14)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�2_������", "������14");

				else INIDATA->addData("������14", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�2_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}

			if (tileMap->_vItem[i]->_item.itemPos == 15)
			{
				char num[256];
				char money[256];

				tileMap->_vItem[i]->_item.amount -= _noticeWindow.sellNum;

				if (tileMap->_vItem[i]->_item.amount <= 0) INIDATA->deleteDataAll("�÷��̾�2_������", "������15");

				else INIDATA->addData("������15", "����", _itoa(tileMap->_vItem[i]->_item.amount, num, 10));

				_sellWindow.playerStone += _noticeWindow.sellNum * (tileMap->_vItem[i]->_item.price / 2);
				INIDATA->addData("������", "�ݾ�", _itoa(_sellWindow.playerStone, money, 10));
				INIDATA->iniSave("�÷��̾�2_������");
				_noticeWindow.sellNum = 0;
				_noticeWindow.isClickItem = false;
				tileMap->_vItem.clear();
				setItem(tileMap);
				return;
			}
		}

	}
}

void sellItemWindow::textRender(tileMap * tileMap)
{
	//��Ʈ�ֱ�
	HFONT font4 = CreateFont(16, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY������B"));
	HFONT oldFont4 = (HFONT)SelectObject(getMemDC(), font4);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(230, 230, 230));

	RECT textBox = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 110,
		CAMERAMANAGER->getCameraCenterY() - 155, 150, 24);
	DrawText(getMemDC(), TEXT("������ �Ľðڽ��ϱ�?"), strlen(TEXT("������ �Ľðڽ��ϱ�?")),
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
	DrawText(getMemDC(), _sellWindow.title.c_str(), strlen(_sellWindow.title.c_str()),
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
	DrawText(getMemDC(), _itoa(_sellWindow.currentPage, currentPage, 10), strlen(_itoa(_sellWindow.currentPage, currentPage, 10)),
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
	DrawText(getMemDC(), _itoa(_sellWindow.maxPage, maxPage, 10), strlen(_itoa(_sellWindow.maxPage, maxPage, 10)),
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
	DrawText(getMemDC(), _itoa(_sellWindow.playerStone, playerStone, 10), strlen(_itoa(_sellWindow.playerStone, playerStone, 10)),
		&playerStoneBox, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

	//�÷��̾� ������ �ֱ�
	RECT stoneBox = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() + 170,
		CAMERAMANAGER->getCameraCenterY() - 127, 60, 24);
	DrawText(getMemDC(), TEXT("stone"), strlen(TEXT("stone")),
		&stoneBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SelectObject(getMemDC(), oldFont2);
	DeleteObject(font2);
	SetBkMode(getMemDC(), OPAQUE);

	RECT nameBox[3];
	RECT priceBox[3];
	RECT moneyAmountBox[3];
	RECT numBox[3];
	RECT amountBox[3];
	char amount[256][3];
	char price[256][3];

	//������ �̸�, �ǸŰ���, ���� �ֱ�
	for (int i = 0; i < tileMap->_vItem.size(); ++i)
	{
		if (tileMap->_vItem[i]->_item.sellPage != _sellWindow.currentPage) continue;

		HFONT font3 = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY������B"));
		HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), font3);
		SetBkMode(getMemDC(), TRANSPARENT);

		//�������̸�
		for (int j = 0; j < 3; ++j)
		{
			nameBox[j] = RectMake(tileMap->_vItem[i]->_item.selectRc.left + 10,
				tileMap->_vItem[i]->_item.selectRc.top, 200, 43);
			SetTextColor(getMemDC(), RGB(80, 230, 230));
			DrawText(getMemDC(), tileMap->_vItem[i]->_item.name.c_str(), strlen(tileMap->_vItem[i]->_item.name.c_str()),
				&nameBox[j], DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		}

		//����
		for (int j = 0; j < 3; ++j)
		{
			amountBox[j] = RectMake(tileMap->_vItem[i]->_item.selectRc.left + 170,
				tileMap->_vItem[i]->_item.selectRc.top, 40, 43);
			SetTextColor(getMemDC(), RGB(80, 230, 230));
			DrawText(getMemDC(), _itoa(tileMap->_vItem[i]->_item.amount, amount[j], 10), strlen(_itoa(tileMap->_vItem[i]->_item.amount, amount[j], 10)),
				&amountBox[j], DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
		}

		//~��
		for (int j = 0; j < 3; ++j)
		{
			numBox[j] = RectMake(tileMap->_vItem[i]->_item.selectRc.left + 210,
				tileMap->_vItem[i]->_item.selectRc.top, 20, 43);
			SetTextColor(getMemDC(), RGB(80, 230, 230));
			DrawText(getMemDC(), TEXT("��"), strlen(TEXT("��")),
				&numBox[j], DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
		}

		//����
		for (int j = 0; j < 3; ++j)
		{
			priceBox[j] = RectMake(tileMap->_vItem[i]->_item.selectRc.right - 205, tileMap->_vItem[i]->_item.selectRc.top,
				100, 43);
			SetTextColor(getMemDC(), RGB(230, 230, 230));
			DrawText(getMemDC(), _itoa(tileMap->_vItem[i]->_item.price / 2, price[j], 10), strlen(_itoa(tileMap->_vItem[i]->_item.price / 2, price[j], 10)),
				&priceBox[j], DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
		}

		//����
		for (int j = 0; j < 3; ++j)
		{
			moneyAmountBox[j] = RectMake(tileMap->_vItem[i]->_item.selectRc.right - 205, tileMap->_vItem[i]->_item.selectRc.top,
				180, 43);
			DrawText(getMemDC(), TEXT("stone"), strlen(TEXT("stone")),
				&moneyAmountBox[j], DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
		}


		SelectObject(getMemDC(), oldFont3);
		DeleteObject(font3);
		SetBkMode(getMemDC(), OPAQUE);
	}

	if (_isDisableClick == false)
	{
		for (int i = 0; i < tileMap->_vItem.size(); ++i)
	{
		if (tileMap->_vItem[i]->_item.sellPage != _sellWindow.currentPage) continue;

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

		if (PtInRect(&tileMap->_vItem[i]->_item.selectRc,
			PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
		{
			//��������Ű�
			DrawText(getMemDC(), tileMap->_vItem[i]->_item.itemExplain.c_str(), strlen(tileMap->_vItem[i]->_item.itemExplain.c_str()),
				&textBox, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			//������ֱ�
			DrawText(getMemDC(), TEXT("���ݷ� : "), strlen(TEXT("���ݷ� : ")), &attackBox, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			DrawText(getMemDC(), _itoa(tileMap->_vItem[i]->_item.attackPower, powerNum[0], 10), strlen(_itoa(tileMap->_vItem[i]->_item.attackPower, powerNum[0], 10)),
				&attackBox, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

			DrawText(getMemDC(), TEXT("���� : "), strlen(TEXT("���� : ")), &defenseBox, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			DrawText(getMemDC(), _itoa(tileMap->_vItem[i]->_item.defensePower, powerNum[1], 10), strlen(_itoa(tileMap->_vItem[i]->_item.defensePower, powerNum[1], 10)),
				&defenseBox, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

			DrawText(getMemDC(), TEXT("���߷� : "), strlen(TEXT("���߷� : ")), &speedBox, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			DrawText(getMemDC(), _itoa(tileMap->_vItem[i]->_item.speedPower, powerNum[2], 10), strlen(_itoa(tileMap->_vItem[i]->_item.speedPower, powerNum[2], 10)),
				&speedBox, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
		}

		SelectObject(getMemDC(), oldFont2);
		DeleteObject(font2);
		SetBkMode(getMemDC(), OPAQUE);
	}
	}
}

void sellItemWindow::PtInRender(tileMap * tileMap)
{
	HPEN myPen = CreatePen(PS_DASH, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	if (_isDisableClick == false)
	{
		for (int i = 0; i < tileMap->_vItem.size(); ++i)
	{
		if (tileMap->_vItem[i]->_item.sellPage != _sellWindow.currentPage) continue;

		if (PtInRect(&tileMap->_vItem[i]->_item.selectRc,
			PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
		{
			Rectangle(getMemDC(), tileMap->_vItem[i]->_item.selectRc);
			tileMap->_vItem[i]->render();
		}
	}
	}


	if (PtInRect(&_sellWindow.returnRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _sellWindow.returnRect);
	}

	if (PtInRect(&_sellWindow.leftButton.rc,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _sellWindow.leftButton.rc);
	}

	if (PtInRect(&_sellWindow.rightButton.rc,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _sellWindow.rightButton.rc);
	}

	if (PtInRect(&_noticeWindow.returnRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _noticeWindow.returnRect);
	}

	if (PtInRect(&_noticeWindow.leftButton.rc,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _noticeWindow.leftButton.rc);
	}

	if (PtInRect(&_noticeWindow.rightButton.rc,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _noticeWindow.rightButton.rc);
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

void sellItemWindow::imageRender(tileMap * tileMap)
{
	_sellWindow.backImg->alphaRender(getMemDC(), CAMERAMANAGER->getCameraCenterX() - _sellWindow.backImg->getWidth() / 2,
		CAMERAMANAGER->getCameraCenterY() - _sellWindow.backImg->getHeight() / 2, 200);
	_sellWindow.frontImg->render(getMemDC(), _sellWindow.frontRect.left, _sellWindow.frontRect.top);
	_sellWindow.leftButton.img->frameRender(getMemDC(), _sellWindow.leftButton.rc.left, _sellWindow.leftButton.rc.top,
		_sellWindow.leftButton.currentFrameX, _sellWindow.leftButton.currentFrameY);
	_sellWindow.rightButton.img->frameRender(getMemDC(), _sellWindow.rightButton.rc.left, _sellWindow.rightButton.rc.top,
		_sellWindow.rightButton.currentFrameX, _sellWindow.rightButton.currentFrameY);
}

void sellItemWindow::clickPage(tileMap * tileMap)
{
	if (PtInRect(&_sellWindow.leftButton.rc,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		_sellWindow.currentPage--;
		_sellWindow.leftButton.currentFrameX = 1;

		if (_sellWindow.currentPage < 1)
		{
			_sellWindow.currentPage = _sellWindow.maxPage;
		}
	}

	if (PtInRect(&_sellWindow.rightButton.rc,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		_sellWindow.currentPage++;
		_sellWindow.rightButton.currentFrameX = 1;

		if (_sellWindow.currentPage > _sellWindow.maxPage)
		{
			_sellWindow.currentPage = 1;
		}
	}

}

void sellItemWindow::updateButton(tileMap * tileMap)
{
	if (_sellWindow.leftButton.currentFrameX == 1)
	{
		_sellWindow.leftButton.timeCount++;

		if (_sellWindow.leftButton.timeCount >= 4)
		{
			_sellWindow.leftButton.timeCount = 0;
			_sellWindow.leftButton.currentFrameX = 0;
		}
	}

	if (_sellWindow.rightButton.currentFrameX == 1)
	{
		_sellWindow.rightButton.timeCount++;

		if (_sellWindow.rightButton.timeCount >= 4)
		{
			_sellWindow.rightButton.timeCount = 0;
			_sellWindow.rightButton.currentFrameX = 0;
		}
	}

	if (_noticeWindow.leftButton.currentFrameX == 1)
	{
		_noticeWindow.leftButton.timeCount++;

		if (_noticeWindow.leftButton.timeCount >= 4)
		{
			_noticeWindow.leftButton.timeCount = 0;
			_noticeWindow.leftButton.currentFrameX = 0;
		}
	}

	if (_noticeWindow.rightButton.currentFrameX == 1)
	{
		_noticeWindow.rightButton.timeCount++;

		if (_noticeWindow.rightButton.timeCount >= 4)
		{
			_noticeWindow.rightButton.timeCount = 0;
			_noticeWindow.rightButton.currentFrameX = 0;
		}
	}
}

void sellItemWindow::clickItem(tileMap * tileMap)
{
	if (_isDisableClick == true) return;

	for (int i = 0; i < tileMap->_vItem.size(); ++i)
	{
		if (tileMap->_vItem[i]->_item.sellPage != _sellWindow.currentPage) continue;

		if (PtInRect(&tileMap->_vItem[i]->_item.selectRc,
			PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
		{
			tileMap->_vItem[i]->_item.isSelect = true;
			_noticeWindow.isClickItem = true;
			_noticeWindow.isCheckNumber = true;
			_isDisableClick = true;
			_noticeWindow.message = "�Ǹ��� ������ �����ϼ���";
		}
	}
}

void sellItemWindow::noticeRender(tileMap * tileMap)
{
	if (_noticeWindow.isClickItem == true && _noticeWindow.isCheckNumber == false)
	{
		IMAGEMANAGER->alphaRender("inputWindowBack", getMemDC(), CAMERAMANAGER->getCameraCenterX() - IMAGEMANAGER->findImage("inputWindowBack")->getWidth() / 2,
			CAMERAMANAGER->getCameraCenterY() - IMAGEMANAGER->findImage("inputWindowBack")->getHeight() / 2, 220);
		_noticeWindow.img->render(getMemDC(), _noticeWindow.rc.left, _noticeWindow.rc.top);
		IMAGEMANAGER->render("button", getMemDC(), _noticeWindow.decideRect.left, _noticeWindow.decideRect.top);
		IMAGEMANAGER->render("button", getMemDC(), _noticeWindow.returnRect.left, _noticeWindow.returnRect.top);
	}

	if (_noticeWindow.isClickItem == true && _noticeWindow.isCheckNumber == true)
	{
		IMAGEMANAGER->alphaRender("inputWindowBack", getMemDC(), CAMERAMANAGER->getCameraCenterX() - IMAGEMANAGER->findImage("inputWindowBack")->getWidth() / 2,
			CAMERAMANAGER->getCameraCenterY() - IMAGEMANAGER->findImage("inputWindowBack")->getHeight() / 2, 220);
		_noticeWindow.img->render(getMemDC(), _noticeWindow.rc.left, _noticeWindow.rc.top);
		_noticeWindow.leftButton.img->frameRender(getMemDC(), _noticeWindow.leftButton.rc.left, _noticeWindow.leftButton.rc.top,
			_noticeWindow.leftButton.currentFrameX, _noticeWindow.leftButton.currentFrameY);
		_noticeWindow.rightButton.img->frameRender(getMemDC(), _noticeWindow.rightButton.rc.left, _noticeWindow.rightButton.rc.top,
			_noticeWindow.rightButton.currentFrameX, _noticeWindow.rightButton.currentFrameY);
		IMAGEMANAGER->render("button", getMemDC(), _noticeWindow.okayRect.left, _noticeWindow.okayRect.top);
	}

	//�˸�â �޼���, ����, ���, �����̹�ư
	if (_noticeWindow.isClickItem == true && _noticeWindow.isCheckNumber == false)
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

	if (_noticeWindow.isCheckNumber == true)
	{
		HFONT font5 = CreateFont(17, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY������B"));
		HFONT oldFont5 = (HFONT)SelectObject(getMemDC(), font5);
		SetBkMode(getMemDC(), TRANSPARENT);

		//�˸�â �޼���
		RECT noticeBox = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY() - 15,
			216, 43);
		SetTextColor(getMemDC(), RGB(230, 230, 230));
		DrawText(getMemDC(), _noticeWindow.message.c_str(), strlen(_noticeWindow.message.c_str()),
			&noticeBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		//���� �޼���
		SetTextColor(getMemDC(), RGB(20, 20, 230));
		DrawText(getMemDC(), TEXT("Ȯ��"), strlen(TEXT("Ȯ��")),
			&_noticeWindow.okayRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


		RECT numberBox = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() + 60, CAMERAMANAGER->getCameraCenterY() + 24,
			31, 31);
		char number[256];
		SetTextColor(getMemDC(), RGB(230, 230, 230));
		DrawText(getMemDC(), _itoa(_noticeWindow.sellNum, number, 10), strlen(TEXT(_itoa(_noticeWindow.sellNum, number, 10))),
			&numberBox, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

		SelectObject(getMemDC(), oldFont5);
		DeleteObject(font5);
		SetBkMode(getMemDC(), OPAQUE);
	}
}

void sellItemWindow::updateNotice(tileMap * tileMap)
{
	if (_noticeWindow.isClickItem == true && _noticeWindow.isCheckNumber == false)
	{
		_noticeWindow.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(),
			_noticeWindow.img->getWidth(), _noticeWindow.img->getHeight());
		_noticeWindow.decideRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 61, CAMERAMANAGER->getCameraCenterY() + 24,
			96, 30);
		_noticeWindow.returnRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() + 61, CAMERAMANAGER->getCameraCenterY() + 24,
			96, 30);
		_noticeWindow.leftButton.rc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 100, CAMERAMANAGER->getCameraTOP() - 100,
			_noticeWindow.leftButton.img->getFrameWidth(), _noticeWindow.leftButton.img->getFrameHeight());
		_noticeWindow.rightButton.rc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 100, CAMERAMANAGER->getCameraTOP() - 100,
			_noticeWindow.rightButton.img->getFrameWidth(), _noticeWindow.rightButton.img->getFrameHeight());
		_noticeWindow.okayRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 100, CAMERAMANAGER->getCameraTOP() - 100,
			96, 30);
	}

	if (_noticeWindow.isClickItem == false)
	{
		_noticeWindow.decideRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 100, CAMERAMANAGER->getCameraTOP() - 100,
			96, 30);
		_noticeWindow.returnRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 100, CAMERAMANAGER->getCameraTOP() - 100,
			96, 30);
		_noticeWindow.leftButton.rc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 100, CAMERAMANAGER->getCameraTOP() - 100,
			_noticeWindow.leftButton.img->getFrameWidth(), _noticeWindow.leftButton.img->getFrameHeight());
		_noticeWindow.rightButton.rc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 100, CAMERAMANAGER->getCameraTOP() - 100,
			_noticeWindow.rightButton.img->getFrameWidth(), _noticeWindow.rightButton.img->getFrameHeight());
		_noticeWindow.okayRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 100, CAMERAMANAGER->getCameraTOP() - 100,
			96, 30);
	}

	if (_noticeWindow.isCheckNumber == true)
	{
		_noticeWindow.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(),
			_noticeWindow.img->getWidth(), _noticeWindow.img->getHeight());
		_noticeWindow.leftButton.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() + 22, CAMERAMANAGER->getCameraCenterY() + 24,
			_noticeWindow.leftButton.img->getFrameWidth(), _noticeWindow.leftButton.img->getFrameHeight());
		_noticeWindow.rightButton.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() + 95, CAMERAMANAGER->getCameraCenterY() + 24,
			_noticeWindow.rightButton.img->getFrameWidth(), _noticeWindow.rightButton.img->getFrameHeight());
		_noticeWindow.okayRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX() - 61, CAMERAMANAGER->getCameraCenterY() + 24,
			96, 30);
	}
}

void sellItemWindow::setNotice(tileMap * tileMap)
{
	_noticeWindow.img = IMAGEMANAGER->findImage("inputWindow2");
	_noticeWindow.isClickItem = false;
	_noticeWindow.isCheckNumber = false;
	_noticeWindow.message = "���� �Ǹ��Ͻðڽ��ϱ�?";
	_noticeWindow.sellNum = 1;
	_noticeWindow.leftButton.img = IMAGEMANAGER->findImage("leftButton");
	_noticeWindow.rightButton.img = IMAGEMANAGER->findImage("rightButton");

	_noticeWindow.leftButton.timeCount = 0;
	_noticeWindow.rightButton.timeCount = 0;
	_noticeWindow.leftButton.currentFrameX = 0;
	_noticeWindow.leftButton.currentFrameY = 0;
	_noticeWindow.rightButton.currentFrameX = 0;
	_noticeWindow.rightButton.currentFrameY = 0;
}

void sellItemWindow::clickNotice(tileMap * tileMap)
{
	for (int i = 0; i < tileMap->_vItem.size(); ++i)
	{
		if (tileMap->_vItem[i]->_item.isSelect == false) continue;

		if (PtInRect(&_noticeWindow.leftButton.rc,
			PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
		{
			_noticeWindow.sellNum--;
			_noticeWindow.leftButton.currentFrameX = 1;

			if (_noticeWindow.sellNum < 1)
			{
				_noticeWindow.sellNum = tileMap->_vItem[i]->_item.amount;
			}
			break;
		}

		if (PtInRect(&_noticeWindow.rightButton.rc,
			PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
		{
			_noticeWindow.sellNum++;
			_noticeWindow.rightButton.currentFrameX = 1;

			if (_noticeWindow.sellNum > tileMap->_vItem[i]->_item.amount)
			{
				_noticeWindow.sellNum = 1;
			}
			break;
		}
	}

	if (PtInRect(&_noticeWindow.okayRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		_noticeWindow.isCheckNumber = false;
		_noticeWindow.message = "���� �Ľðڽ��ϱ�?";
	}

	if (PtInRect(&_noticeWindow.decideRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		_noticeWindow.isClickItem = false;
		saveInidata(tileMap);
	}

	if (PtInRect(&_noticeWindow.returnRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		for (int i = 0; i < tileMap->_vItem.size(); ++i)
		{
			if (tileMap->_vItem[i]->_item.isSelect == false) continue;

			tileMap->_vItem[i]->_item.isSelect = false;
		}
		_noticeWindow.sellNum = 1;
		_noticeWindow.isClickItem = false;
	}
}
