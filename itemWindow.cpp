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
	//앞창
	_itemWindow.frontRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - _itemWindow.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _itemWindow.frontImg->getHeight() / 2,
		_itemWindow.frontImg->getWidth(), _itemWindow.frontImg->getHeight());
	//뒷창
	_itemWindow.backRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - _itemWindow.frontImg->getWidth() / 2,
		CAMERAMANAGER->getCameraTOP() + _itemWindow.frontImg->getHeight() / 2,
		_itemWindow.backImg->getWidth(), _itemWindow.backImg->getHeight());
	//가방정리렉트
	_itemWindow.arrangeRect = RectMake(CAMERAMANAGER->getCameraRIGHT() - 244, CAMERAMANAGER->getCameraTOP() + 424,
		85, 16);
	//닫기렉트
	_itemWindow.exitRect = RectMake(CAMERAMANAGER->getCameraRIGHT() - 119, CAMERAMANAGER->getCameraTOP() + 424,
		85, 16);
	//아이템 칸 렉트
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

	//캐릭터 입력정보 칸 렉트
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

	//아이템 칸 렉트
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

	//캐릭터 입력정보 칸 렉트
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

	//아이템정렬 렉트
	if (PtInRect(&_itemWindow.arrangeRect,
		PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _itemWindow.arrangeRect);
	}

	//닫기 렉트
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

	//캐릭터 입력 정보칸 타입부여
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 3; ++i)
		{
			//헬멧타입적용
			if (i == 1 && j == 0)
			{
				_itemWindow.pw[i][j].playerWear = WEAR_HELMET;
				_itemWindow.pw[i][j].isExistItem = false;
			}
			//무기타입 적용
			else if (i == 0 && j == 1)
			{
				_itemWindow.pw[i][j].playerWear = WEAR_WEAPON;
				_itemWindow.pw[i][j].isExistItem = false;
			}
			//방어구타입 적용
			else if (i == 1 && j == 1)
			{
				_itemWindow.pw[i][j].playerWear = WEAR_ARMOR;
				_itemWindow.pw[i][j].isExistItem = false;
			}
			//탑승문서타입 적용
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

	//초기 false값 부여
	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < 5; ++i)
		{
			_itemWindow.item[i][j].isExistItem = false;
			_itemWindow.item[i][j].itemPos = (j * 3) + i + j + j + 1;
		}
	}

	int loginPlayer1 = INIDATA->loadDataInterger("캐릭터", "플레이어1", "로그인");
	int loginPlayer2 = INIDATA->loadDataInterger("캐릭터", "플레이어2", "로그인");

	//플레이어1이 로그인했을경우
	if (loginPlayer1 == (int)INFO_YES)
	{
		int itemType[19];

		_playerStone = INIDATA->loadDataInterger("플레이어1_아이템", "소지금", "금액");

		itemType[0] = INIDATA->loadDataInterger("플레이어1_아이템", "무기착용", "종류");
		itemType[1] = INIDATA->loadDataInterger("플레이어1_아이템", "갑옷착용", "종류");
		itemType[2] = INIDATA->loadDataInterger("플레이어1_아이템", "투구착용", "종류");
		itemType[3] = INIDATA->loadDataInterger("플레이어1_아이템", "탑승문서착용", "종류");

		itemType[4] = INIDATA->loadDataInterger("플레이어1_아이템", "아이템1", "종류");
		itemType[5] = INIDATA->loadDataInterger("플레이어1_아이템", "아이템2", "종류");
		itemType[6] = INIDATA->loadDataInterger("플레이어1_아이템", "아이템3", "종류");
		itemType[7] = INIDATA->loadDataInterger("플레이어1_아이템", "아이템4", "종류");
		itemType[8] = INIDATA->loadDataInterger("플레이어1_아이템", "아이템5", "종류");
		itemType[9] = INIDATA->loadDataInterger("플레이어1_아이템", "아이템6", "종류");
		itemType[10] = INIDATA->loadDataInterger("플레이어1_아이템", "아이템7", "종류");
		itemType[11] = INIDATA->loadDataInterger("플레이어1_아이템", "아이템8", "종류");
		itemType[12] = INIDATA->loadDataInterger("플레이어1_아이템", "아이템9", "종류");
		itemType[13] = INIDATA->loadDataInterger("플레이어1_아이템", "아이템10", "종류");
		itemType[14] = INIDATA->loadDataInterger("플레이어1_아이템", "아이템11", "종류");
		itemType[15] = INIDATA->loadDataInterger("플레이어1_아이템", "아이템12", "종류");
		itemType[16] = INIDATA->loadDataInterger("플레이어1_아이템", "아이템13", "종류");
		itemType[17] = INIDATA->loadDataInterger("플레이어1_아이템", "아이템14", "종류");
		itemType[18] = INIDATA->loadDataInterger("플레이어1_아이템", "아이템15", "종류");

		for (int j = 0; j < 17; ++j)
		{
			//착용한 무기가 있을경우
			if (itemType[0] == (ITEMNAME)j &&
				itemType[0] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[0][1].centerX, _itemWindow.pw[0][1].centerY));
				_item->_item.isWeared = true;
				_itemWindow.pw[0][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//착용한 갑옷이 있을경우
			if (itemType[1] == (ITEMNAME)j &&
				itemType[1] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[1][1].centerX, _itemWindow.pw[1][1].centerY));
				_item->_item.isWeared = true;
				_itemWindow.pw[1][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//착용한 투구가 있을경우
			if (itemType[2] == (ITEMNAME)j &&
				itemType[2] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[1][0].centerX, _itemWindow.pw[1][0].centerY));
				_item->_item.isWeared = true;
				_itemWindow.pw[1][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//착용한 탑승문서가 있을경우
			if (itemType[3] == (ITEMNAME)j &&
				itemType[3] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[1][2].centerX, _itemWindow.pw[1][2].centerY));
				_item->_item.isWeared = true;
				_itemWindow.pw[1][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//첫번째칸 아이템이 있을경우
			if (itemType[4] == (ITEMNAME)j &&
				itemType[4] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[0][0].centerX, _itemWindow.item[0][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템1", "갯수"));
				_item->_item.itemPos = 1;
				_itemWindow.item[0][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//두번째칸 아이템이 있을경우
			if (itemType[5] == (ITEMNAME)j &&
				itemType[5] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[1][0].centerX, _itemWindow.item[1][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템2", "갯수"));
				_item->_item.itemPos = 2;
				_itemWindow.item[1][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//세번째칸 아이템이 있을경우
			if (itemType[6] == (ITEMNAME)j &&
				itemType[6] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[2][0].centerX, _itemWindow.item[2][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템3", "갯수"));
				_item->_item.itemPos = 3;
				_itemWindow.item[2][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//네번째칸에 아이템이 있을경우
			if (itemType[7] == (ITEMNAME)j &&
				itemType[7] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[3][0].centerX, _itemWindow.item[3][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템4", "갯수"));
				_item->_item.itemPos = 4;
				_itemWindow.item[3][0].isExistItem = true;

				tileMap->_vItem.push_back(_item);
			}

			//다섯번째칸에 아이템이 있을경우
			if (itemType[8] == (ITEMNAME)j &&
				itemType[8] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[4][0].centerX, _itemWindow.item[4][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템5", "갯수"));
				_item->_item.itemPos = 5;
				_itemWindow.item[4][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//여섯번째칸에 아이템이 있을경우
			if (itemType[9] == (ITEMNAME)j &&
				itemType[9] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[0][1].centerX, _itemWindow.item[0][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템6", "갯수"));
				_item->_item.itemPos = 6;
				_itemWindow.item[0][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//7번째칸에 아이템이 있을경우
			if (itemType[10] == (ITEMNAME)j &&
				itemType[10] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[1][1].centerX, _itemWindow.item[1][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템7", "갯수"));
				_item->_item.itemPos = 7;
				_itemWindow.item[1][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//8번째칸에 아이템이 있을경우
			if (itemType[11] == (ITEMNAME)j &&
				itemType[11] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[2][1].centerX, _itemWindow.item[2][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템8", "갯수"));
				_item->_item.itemPos = 8;
				_itemWindow.item[2][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//9번째칸에 아이템이 있을경우
			if (itemType[12] == (ITEMNAME)j &&
				itemType[12] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[3][1].centerX, _itemWindow.item[3][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템9", "갯수"));
				_item->_item.itemPos = 9;
				_itemWindow.item[3][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//10번째칸에 아이템이 있을경우
			if (itemType[13] == (ITEMNAME)j &&
				itemType[13] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[4][1].centerX, _itemWindow.item[4][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템10", "갯수"));
				_item->_item.itemPos = 10;
				_itemWindow.item[4][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//11번째칸에 아이템이 있을경우
			if (itemType[14] == (ITEMNAME)j &&
				itemType[14] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[0][2].centerX, _itemWindow.item[0][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템11", "갯수"));
				_item->_item.itemPos = 11;
				_itemWindow.item[0][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//12번째칸에 아이템이 있을경우
			if (itemType[15] == (ITEMNAME)j &&
				itemType[15] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[1][2].centerX, _itemWindow.item[1][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템12", "갯수"));
				_item->_item.itemPos = 12;
				_itemWindow.item[1][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//13번째칸에 아이템이 있을경우
			if (itemType[16] == (ITEMNAME)j &&
				itemType[16] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[2][2].centerX, _itemWindow.item[2][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템13", "갯수"));
				_item->_item.itemPos = 13;
				_itemWindow.item[2][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//14번째칸에 아이템이 있을경우
			if (itemType[17] == (ITEMNAME)j &&
				itemType[17] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[3][2].centerX, _itemWindow.item[3][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템14", "갯수"));
				_item->_item.itemPos = 14;
				_itemWindow.item[3][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//15번째칸에 아이템이 있을경우
			if (itemType[18] == (ITEMNAME)j &&
				itemType[18] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[4][2].centerX, _itemWindow.item[4][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템15", "갯수"));
				_item->_item.itemPos = 15;
				_itemWindow.item[4][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}
		}
	}

	//플레이어2이 로그인했을경우
	if (loginPlayer2 == (int)INFO_YES)
	{
		int itemType[19];

		_playerStone = INIDATA->loadDataInterger("플레이어2_아이템", "소지금", "금액");

		itemType[0] = INIDATA->loadDataInterger("플레이어2_아이템", "무기착용", "종류");
		itemType[1] = INIDATA->loadDataInterger("플레이어2_아이템", "갑옷착용", "종류");
		itemType[2] = INIDATA->loadDataInterger("플레이어2_아이템", "투구착용", "종류");
		itemType[3] = INIDATA->loadDataInterger("플레이어2_아이템", "탑승문서착용", "종류");

		itemType[4] = INIDATA->loadDataInterger("플레이어2_아이템", "아이템1", "종류");
		itemType[5] = INIDATA->loadDataInterger("플레이어2_아이템", "아이템2", "종류");
		itemType[6] = INIDATA->loadDataInterger("플레이어2_아이템", "아이템3", "종류");
		itemType[7] = INIDATA->loadDataInterger("플레이어2_아이템", "아이템4", "종류");
		itemType[8] = INIDATA->loadDataInterger("플레이어2_아이템", "아이템5", "종류");
		itemType[9] = INIDATA->loadDataInterger("플레이어2_아이템", "아이템6", "종류");
		itemType[10] = INIDATA->loadDataInterger("플레이어2_아이템", "아이템7", "종류");
		itemType[11] = INIDATA->loadDataInterger("플레이어2_아이템", "아이템8", "종류");
		itemType[12] = INIDATA->loadDataInterger("플레이어2_아이템", "아이템9", "종류");
		itemType[13] = INIDATA->loadDataInterger("플레이어2_아이템", "아이템10", "종류");
		itemType[14] = INIDATA->loadDataInterger("플레이어2_아이템", "아이템11", "종류");
		itemType[15] = INIDATA->loadDataInterger("플레이어2_아이템", "아이템12", "종류");
		itemType[16] = INIDATA->loadDataInterger("플레이어2_아이템", "아이템13", "종류");
		itemType[17] = INIDATA->loadDataInterger("플레이어2_아이템", "아이템14", "종류");
		itemType[18] = INIDATA->loadDataInterger("플레이어2_아이템", "아이템15", "종류");

		for (int j = 0; j < 16; ++j)
		{
			//착용한 무기가 있을경우
			if (itemType[0] == (ITEMNAME)j &&
				itemType[0] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[0][1].centerX, _itemWindow.pw[0][1].centerY));
				_item->_item.isWeared = true;
				tileMap->_vItem.push_back(_item);
			}

			//착용한 갑옷이 있을경우
			if (itemType[1] == (ITEMNAME)j &&
				itemType[1] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[1][1].centerX, _itemWindow.pw[1][1].centerY));
				_item->_item.isWeared = true;
				tileMap->_vItem.push_back(_item);
			}

			//착용한 투구가 있을경우
			if (itemType[2] == (ITEMNAME)j &&
				itemType[2] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[1][0].centerX, _itemWindow.pw[1][0].centerY));
				_item->_item.isWeared = true;
				tileMap->_vItem.push_back(_item);
			}

			//착용한 탑승문서가 있을경우
			if (itemType[3] == (ITEMNAME)j &&
				itemType[3] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.pw[1][2].centerX, _itemWindow.pw[1][2].centerY));
				_item->_item.isWeared = true;
				tileMap->_vItem.push_back(_item);
			}

			//첫번째칸 아이템이 있을경우
			if (itemType[4] == (ITEMNAME)j &&
				itemType[4] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[0][0].centerX, _itemWindow.item[0][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템1", "갯수"));
				_item->_item.itemPos = 1;
				_itemWindow.item[0][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//두번째칸 아이템이 있을경우
			if (itemType[5] == (ITEMNAME)j &&
				itemType[5] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[1][0].centerX, _itemWindow.item[1][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템2", "갯수"));
				_item->_item.itemPos = 2;
				_itemWindow.item[1][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//세번째칸 아이템이 있을경우
			if (itemType[6] == (ITEMNAME)j &&
				itemType[6] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[2][0].centerX, _itemWindow.item[2][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템3", "갯수"));
				_item->_item.itemPos = 3;
				_itemWindow.item[2][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//네번째칸에 아이템이 있을경우
			if (itemType[7] == (ITEMNAME)j &&
				itemType[7] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[3][0].centerX, _itemWindow.item[3][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템4", "갯수"));
				_item->_item.itemPos = 4;
				_itemWindow.item[3][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//다섯번째칸에 아이템이 있을경우
			if (itemType[8] == (ITEMNAME)j &&
				itemType[8] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[4][0].centerX, _itemWindow.item[4][0].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템5", "갯수"));
				_item->_item.itemPos = 5;
				_itemWindow.item[4][0].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//여섯번째칸에 아이템이 있을경우
			if (itemType[9] == (ITEMNAME)j &&
				itemType[9] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[0][1].centerX, _itemWindow.item[0][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템6", "갯수"));
				_item->_item.itemPos = 6;
				_itemWindow.item[0][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//7번째칸에 아이템이 있을경우
			if (itemType[10] == (ITEMNAME)j &&
				itemType[10] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[1][1].centerX, _itemWindow.item[1][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템7", "갯수"));
				_item->_item.itemPos = 7;
				_itemWindow.item[1][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//8번째칸에 아이템이 있을경우
			if (itemType[11] == (ITEMNAME)j &&
				itemType[11] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[2][1].centerX, _itemWindow.item[2][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템8", "갯수"));
				_item->_item.itemPos = 8;
				_itemWindow.item[2][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//9번째칸에 아이템이 있을경우
			if (itemType[12] == (ITEMNAME)j &&
				itemType[12] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[3][1].centerX, _itemWindow.item[3][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템9", "갯수"));
				_item->_item.itemPos = 9;
				_itemWindow.item[3][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//10번째칸에 아이템이 있을경우
			if (itemType[13] == (ITEMNAME)j &&
				itemType[13] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[4][1].centerX, _itemWindow.item[4][1].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템10", "갯수"));
				_item->_item.itemPos = 10;
				_itemWindow.item[4][1].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//11번째칸에 아이템이 있을경우
			if (itemType[14] == (ITEMNAME)j &&
				itemType[14] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[0][2].centerX, _itemWindow.item[0][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템11", "갯수"));
				_item->_item.itemPos = 11;
				_itemWindow.item[0][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//12번째칸에 아이템이 있을경우
			if (itemType[15] == (ITEMNAME)j &&
				itemType[15] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[1][2].centerX, _itemWindow.item[1][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템12", "갯수"));
				_item->_item.itemPos = 12;
				_itemWindow.item[1][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//13번째칸에 아이템이 있을경우
			if (itemType[16] == (ITEMNAME)j &&
				itemType[16] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[2][2].centerX, _itemWindow.item[2][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템13", "갯수"));
				_item->_item.itemPos = 13;
				_itemWindow.item[2][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//14번째칸에 아이템이 있을경우
			if (itemType[17] == (ITEMNAME)j &&
				itemType[17] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[3][2].centerX, _itemWindow.item[3][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템14", "갯수"));
				_item->_item.itemPos = 14;
				_itemWindow.item[3][2].isExistItem = true;
				tileMap->_vItem.push_back(_item);
			}

			//15번째칸에 아이템이 있을경우
			if (itemType[18] == (ITEMNAME)j &&
				itemType[18] != (ITEMNAME)0)
			{
				item* _item = new item;
				_item->init((ITEMNAME)j, PointMake(_itemWindow.item[4][2].centerX, _itemWindow.item[4][2].centerY));
				_item->itemAmount(INIDATA->loadDataInterger("플레이어1_아이템", "아이템15", "갯수"));
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


	//물약은 다르게하기

	//복권도 다르게하기

	for (int i = 0; i < tileMap->_vItem.size(); ++i)
	{
		//해당 아이템을 선택했을경우
		if (PtInRect(&tileMap->_vItem[i]->_item.selectRc,
			PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
		{
			//선택한아이템과 일치(트루값을준다)
			tileMap->_vItem[i]->_item.isSelect = true;
			_isClickItem = true;

			//해당칸 아이템칸은 아이템이 없으므로 false 해주고
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

			//해당칸 플레이어정보창 아이템이 없으므로 false 해주고
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

			//알파값 정해주기
			tileMap->_vItem[i]->_item.alphaIndex = 150;
		}
	}
}

void itemWindow::switchItem(tileMap * tileMap)
{
	if (_isClickItem == false) return;

	//아이템칸 조절
	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < 5; ++i)
		{
			if (PtInRect(&_itemWindow.item[i][j].rc,
				PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
			{

				//선택했을때 그 선택한 아이템칸이 비어있을경우
				if (_itemWindow.item[i][j].isExistItem == false)
				{
					for (int k = 0; k < tileMap->_vItem.size(); ++k)
					{
						if (tileMap->_vItem[k]->_item.isSelect == false) continue;
						if (tileMap->_vItem[k]->_item.itemPos == _itemWindow.item[i][j].itemPos) continue;

						//원래 칸에 있었던 아이템 삭제해주시고
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

						//새로운칸에 현재 올려놓은 아이템을 저장한다
						saveInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);

						////새로 배치한다
						//tileMap->_vItem.clear();
						//setItem(tileMap);

						return;
					}
				}

				//선택했을때 그 선택한 아이템칸이 비어있을경우
				if (_itemWindow.item[i][j].isExistItem == false && _isAbleSameClick == true)
				{
					for (int k = 0; k < tileMap->_vItem.size(); ++k)
					{
						if (tileMap->_vItem[k]->_item.isSelect == false) continue;

						//원래 칸에 있었던 아이템 삭제해주시고
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

						//새로운칸에 현재 올려놓은 아이템을 저장한다
						saveInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);

						////새로배치한다
						//tileMap->_vItem.clear();
						//setItem(tileMap);

						return;
					}
				}

				//만약 아이템이 있을경우(서로 스위칭해줌)
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
								
								//원래 들고있었던 아이템은 아이템칸에 올려놓고
								int tempPos = tileMap->_vItem[h]->_item.itemPos;
								tileMap->_vItem[h]->_item.isSelect = false;
								tileMap->_vItem[k]->_item.isWeared = false;
								tileMap->_vItem[h]->_item.alphaIndex = 255;
								tileMap->_vItem[h]->_item.itemPos = _itemWindow.item[i][j].itemPos;
								tileMap->_vItem[h]->_item.centerX = _itemWindow.item[i][j].centerX;
								tileMap->_vItem[h]->_item.centerY = _itemWindow.item[i][j].centerY;

								//바뀐 pos에 저장한다
								saveInidata(tileMap, tileMap->_vItem[h]->_item.itemPos);

								//클릭한 아이템칸을 들어올린다.
								tileMap->_vItem[k]->_item.itemPos = tempPos;
								tileMap->_vItem[k]->_item.alphaIndex = 155;
								tileMap->_vItem[k]->_item.isSelect = true;
								_isTime = true;

								//바뀐 pos에 저장한다
								saveInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);

								////새로배치한다
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

	//아이템 착용
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (PtInRect(&_itemWindow.pw[i][j].rc, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
			{
				if (_itemWindow.pw[i][j].playerWear == WEAR_NONE) continue;

				//선택한 플레이어아이템칸이 비어있을경우
				if (_itemWindow.pw[i][j].isExistItem == false && _isAbleSameClick == true)
				{
					for (int k = 0; k < tileMap->_vItem.size(); ++k)
					{
						if (tileMap->_vItem[k]->_item.isSelect == false) continue;
						
						//내가든 아이템이 투구이고 클릭한부분의 pw 창이 헬멧일경우
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

							//새로운칸에 현재 올려놓은 아이템을 저장한다
							saveInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);
							return;
						}

						//내가든 아이템이 무기이고 클릭한부분의 pw 창이 무기일경우
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

							//새로운칸에 현재 올려놓은 아이템을 저장한다
							saveInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);
							return;
						}

						//내가든 아이템이 갑옷이고 클릭한부분의 pw 창이 갑옷일경우
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

							//새로운칸에 현재 올려놓은 아이템을 저장한다
							saveInidata(tileMap, tileMap->_vItem[k]->_item.itemPos);
							return;
						}

						//내가든 아이템이 갑옷이고 클릭한부분의 pw 창이 갑옷일경우
						if (tileMap->_vItem[k]->_item.itemType == TYPE_RIDE_BOOK &&
							_itemWindow.pw[i][j].playerWear == WEAR_RIDE_BOOK)
						{
							int loginPlayer1 = INIDATA->loadDataInterger("캐릭터", "플레이어1", "로그인");
							int loginPlayer2 = INIDATA->loadDataInterger("캐릭터", "플레이어2", "로그인");

							//플레이어1이 로그인했고
							if (loginPlayer1 == (int)INFO_YES)
							{
								int playerType = INIDATA->loadDataInterger("캐릭터", "플레이어1", "종류");

								//블루일경우
								if (playerType == (int)INFO_BLUE)
								{
									//베르가탑승문서가 아닐경우 리턴한다
									if (tileMap->_vItem[k]->_item.ItemName != ITEM_VERGA_RIDE_BOOK) return;
								}

								//레드일경우
								if (playerType == (int)INFO_RED)
								{
									//고르고르탑승문서가 아닐경우 리턴한다
									if (tileMap->_vItem[k]->_item.ItemName != ITEM_GORGOR_RIDE_BOOK) return;
								}
							}

							//플레이어2이 로그인했고
							if (loginPlayer2 == (int)INFO_YES)
							{
								int playerType = INIDATA->loadDataInterger("캐릭터", "플레이어2", "종류");

								//블루일경우
								if (playerType == (int)INFO_BLUE)
								{
									//베르가탑승문서가 아닐경우 리턴한다
									if (tileMap->_vItem[k]->_item.ItemName != ITEM_VERGA_RIDE_BOOK) return;
								}

								//레드일경우
								if (playerType == (int)INFO_RED)
								{
									//고르고르탑승문서가 아닐경우 리턴한다
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

							//새로운칸에 현재 올려놓은 아이템을 저장한다
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
		//선택한아이템과 일치(트루값인 애는 마우스를 따라다닌다)
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
	//아이템창에 맞추기
	for (int i = 0; i < tileMap->_vItem.size(); ++i)
	{
		if (tileMap->_vItem[i]->_item.isSelect == true) continue;

		//투구를 착용했을경우
		if (tileMap->_vItem[i]->_item.isWeared == true &&
			tileMap->_vItem[i]->_item.itemType == TYPE_HELMET)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.pw[1][0].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.pw[1][0].centerY + 10;
		}

		//무기를 착용했을경우
		if (tileMap->_vItem[i]->_item.isWeared == true &&
			(tileMap->_vItem[i]->_item.itemType == TYPE_SPEAR ||
			tileMap->_vItem[i]->_item.itemType == TYPE_CLUB ||
			tileMap->_vItem[i]->_item.itemType == TYPE_HATCHAT))
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.pw[0][1].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.pw[0][1].centerY + 10;
		}

		//갑옷을 착용했을경우
		if (tileMap->_vItem[i]->_item.isWeared == true &&
			tileMap->_vItem[i]->_item.itemType == TYPE_ARMOR)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.pw[1][1].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.pw[1][1].centerY + 10;
		}

		//라이딩 책을 착용했을경우
		if (tileMap->_vItem[i]->_item.isWeared == true &&
			tileMap->_vItem[i]->_item.itemType == TYPE_RIDE_BOOK)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.pw[1][2].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.pw[1][2].centerY + 10;
		}

		//아이템 1칸에 있을경우
		if (tileMap->_vItem[i]->_item.itemPos == 1)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[0][0].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[0][0].centerY;
		}

		//아이템 2칸에 있을경우
		if (tileMap->_vItem[i]->_item.itemPos == 2)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[1][0].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[1][0].centerY;
		}

		//아이템 3칸에 있을경우
		if (tileMap->_vItem[i]->_item.itemPos == 3)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[2][0].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[2][0].centerY;
		}

		//아이템 4칸에 있을경우
		if (tileMap->_vItem[i]->_item.itemPos == 4)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[3][0].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[3][0].centerY;
		}

		//아이템 5칸에 있을경우
		if (tileMap->_vItem[i]->_item.itemPos == 5)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[4][0].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[4][0].centerY;
		}

		//아이템 6칸에 있을경우
		if (tileMap->_vItem[i]->_item.itemPos == 6)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[0][1].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[0][1].centerY;
		}

		//아이템 7칸에 있을경우
		if (tileMap->_vItem[i]->_item.itemPos == 7)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[1][1].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[1][1].centerY;
		}

		//아이템 8칸에 있을경우
		if (tileMap->_vItem[i]->_item.itemPos == 8)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[2][1].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[2][1].centerY;
		}

		//아이템 9칸에 있을경우
		if (tileMap->_vItem[i]->_item.itemPos == 9)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[3][1].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[3][1].centerY;
		}

		//아이템 10칸에 있을경우
		if (tileMap->_vItem[i]->_item.itemPos == 10)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[4][1].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[4][1].centerY;
		}

		//아이템 11칸에 있을경우
		if (tileMap->_vItem[i]->_item.itemPos == 11)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[0][2].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[0][2].centerY;
		}

		//아이템 12칸에 있을경우
		if (tileMap->_vItem[i]->_item.itemPos == 12)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[1][2].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[1][2].centerY;
		}

		//아이템 13칸에 있을경우
		if (tileMap->_vItem[i]->_item.itemPos == 13)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[2][2].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[2][2].centerY;
		}

		//아이템 14칸에 있을경우
		if (tileMap->_vItem[i]->_item.itemPos == 14)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[3][2].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[3][2].centerY;
		}

		//아이템 15칸에 있을경우
		if (tileMap->_vItem[i]->_item.itemPos == 15)
		{
			tileMap->_vItem[i]->_item.centerX = _itemWindow.item[4][2].centerX;
			tileMap->_vItem[i]->_item.centerY = _itemWindow.item[4][2].centerY;
		}

		//렉트 바로바로 수정해주기
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
	//머니 띄우기
	HFONT font2 = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY목각파임B"));
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

	//아이템 설명충
	if (_isClickItem == false)
	{
		for (int i = 0; i < tileMap->_vItem.size(); ++i)
		{
			if (PtInRect(&tileMap->_vItem[i]->_item.selectRc,
				PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
			{
				//제목, 가격형성, 가격
				HFONT font = CreateFont(17, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
					0, 0, 0, 0, TEXT("HY목각파임B"));
				HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
				SetBkMode(getMemDC(), TRANSPARENT);

				//제목
				SetTextColor(getMemDC(), RGB(80, 255, 255));
				TextOut(getMemDC(), CAMERAMANAGER->getCameraRIGHT() - 255, CAMERAMANAGER->getCameraTOP() + 345,
					tileMap->_vItem[i]->_item.name.c_str(), strlen(tileMap->_vItem[i]->_item.name.c_str()));

				//상점가
				SetTextColor(getMemDC(), RGB(255, 30, 30));
				TextOut(getMemDC(), CAMERAMANAGER->getCameraRIGHT() - 200, CAMERAMANAGER->getCameraTOP() + 395,
					tileMap->_vItem[i]->_item.sellPrice.c_str(), strlen(tileMap->_vItem[i]->_item.sellPrice.c_str()));

				//가격
				char price[256];
				SetTextColor(getMemDC(), RGB(255, 30, 30));
				TextOut(getMemDC(), CAMERAMANAGER->getCameraRIGHT() - 120, CAMERAMANAGER->getCameraTOP() + 395,
					_itoa(tileMap->_vItem[i]->_item.price, price, 10), strlen(_itoa(tileMap->_vItem[i]->_item.price, price, 10)));

				SelectObject(getMemDC(), oldFont);
				DeleteObject(font);
				SetBkMode(getMemDC(), OPAQUE);

				//설명
				HFONT font1 = CreateFont(12, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
					0, 0, 0, 0, TEXT("HY목각파임B"));
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
	int loginPlayer1 = INIDATA->loadDataInterger("캐릭터", "플레이어1", "로그인");
	int loginPlayer2 = INIDATA->loadDataInterger("캐릭터", "플레이어2", "로그인");

	//플레이어 1이 로그인했을경우
	if (loginPlayer1 == (int)INFO_YES)
	{
		if (itemPos == 0)
		{
			for (int i = 0; i < tileMap->_vItem.size(); ++i)
			{
				if (tileMap->_vItem[i]->_item.isSelect == false) continue;

				if (tileMap->_vItem[i]->_item.itemType == TYPE_HELMET)
				{
					INIDATA->deleteDataAll("플레이어1_아이템", "투구착용");
				}

				if (tileMap->_vItem[i]->_item.itemType == TYPE_CLUB || 
					tileMap->_vItem[i]->_item.itemType == TYPE_SPEAR ||
					tileMap->_vItem[i]->_item.itemType == TYPE_HATCHAT)
				{
					INIDATA->deleteDataAll("플레이어1_아이템", "무기착용");
				}

				if (tileMap->_vItem[i]->_item.itemType == TYPE_ARMOR)
				{
					INIDATA->deleteDataAll("플레이어1_아이템", "갑옷착용");
				}

				if (tileMap->_vItem[i]->_item.itemType == TYPE_RIDE_BOOK)
				{
					INIDATA->deleteDataAll("플레이어1_아이템", "탑승문서착용");
				}
			}
		}
		if (itemPos == 1) INIDATA->deleteDataAll("플레이어1_아이템", "아이템1");
		if (itemPos == 2) INIDATA->deleteDataAll("플레이어1_아이템", "아이템2");
		if (itemPos == 3) INIDATA->deleteDataAll("플레이어1_아이템", "아이템3");
		if (itemPos == 4) INIDATA->deleteDataAll("플레이어1_아이템", "아이템4");
		if (itemPos == 5) INIDATA->deleteDataAll("플레이어1_아이템", "아이템5");
		if (itemPos == 6) INIDATA->deleteDataAll("플레이어1_아이템", "아이템6");
		if (itemPos == 7) INIDATA->deleteDataAll("플레이어1_아이템", "아이템7");
		if (itemPos == 8) INIDATA->deleteDataAll("플레이어1_아이템", "아이템8");
		if (itemPos == 9) INIDATA->deleteDataAll("플레이어1_아이템", "아이템9");
		if (itemPos == 10) INIDATA->deleteDataAll("플레이어1_아이템", "아이템10");
		if (itemPos == 11) INIDATA->deleteDataAll("플레이어1_아이템", "아이템11");
		if (itemPos == 12) INIDATA->deleteDataAll("플레이어1_아이템", "아이템12");
		if (itemPos == 13) INIDATA->deleteDataAll("플레이어1_아이템", "아이템13");
		if (itemPos == 14) INIDATA->deleteDataAll("플레이어1_아이템", "아이템14");
		if (itemPos == 15) INIDATA->deleteDataAll("플레이어1_아이템", "아이템15");
	}

	//플레이어 2이 로그인했을경우
	if (loginPlayer2 == (int)INFO_YES)
	{
		if (itemPos == 0)
		{
			for (int i = 0; i < tileMap->_vItem.size(); ++i)
			{
				if (tileMap->_vItem[i]->_item.isSelect == false) continue;

				if (tileMap->_vItem[i]->_item.itemType == TYPE_HELMET)
				{
					INIDATA->deleteDataAll("플레이어2_아이템", "투구착용");
				}

				if (tileMap->_vItem[i]->_item.itemType == TYPE_CLUB ||
					tileMap->_vItem[i]->_item.itemType == TYPE_SPEAR ||
					tileMap->_vItem[i]->_item.itemType == TYPE_HATCHAT)
				{
					INIDATA->deleteDataAll("플레이어2_아이템", "무기착용");
				}

				if (tileMap->_vItem[i]->_item.itemType == TYPE_ARMOR)
				{
					INIDATA->deleteDataAll("플레이어2_아이템", "갑옷착용");
				}

				if (tileMap->_vItem[i]->_item.itemType == TYPE_RIDE_BOOK)
				{
					INIDATA->deleteDataAll("플레이어2_아이템", "탑승문서착용");
				}
			}
		}
		if (itemPos == 1) INIDATA->deleteDataAll("플레이어2_아이템", "아이템1");
		if (itemPos == 2) INIDATA->deleteDataAll("플레이어2_아이템", "아이템2");
		if (itemPos == 3) INIDATA->deleteDataAll("플레이어2_아이템", "아이템3");
		if (itemPos == 4) INIDATA->deleteDataAll("플레이어2_아이템", "아이템4");
		if (itemPos == 5) INIDATA->deleteDataAll("플레이어2_아이템", "아이템5");
		if (itemPos == 6) INIDATA->deleteDataAll("플레이어2_아이템", "아이템6");
		if (itemPos == 7) INIDATA->deleteDataAll("플레이어2_아이템", "아이템7");
		if (itemPos == 8) INIDATA->deleteDataAll("플레이어2_아이템", "아이템8");
		if (itemPos == 9) INIDATA->deleteDataAll("플레이어2_아이템", "아이템9");
		if (itemPos == 10) INIDATA->deleteDataAll("플레이어2_아이템", "아이템10");
		if (itemPos == 11) INIDATA->deleteDataAll("플레이어2_아이템", "아이템11");
		if (itemPos == 12) INIDATA->deleteDataAll("플레이어2_아이템", "아이템12");
		if (itemPos == 13) INIDATA->deleteDataAll("플레이어2_아이템", "아이템13");
		if (itemPos == 14) INIDATA->deleteDataAll("플레이어2_아이템", "아이템14");
		if (itemPos == 15) INIDATA->deleteDataAll("플레이어2_아이템", "아이템15");
	}
}

void itemWindow::saveInidata(tileMap * tileMap, int itemPos)
{
	int loginPlayer1 = INIDATA->loadDataInterger("캐릭터", "플레이어1", "로그인");
	int loginPlayer2 = INIDATA->loadDataInterger("캐릭터", "플레이어2", "로그인");

	for (int i = 0; i < tileMap->_vItem.size(); ++i)
	{
		//플레이어 1이 로그인했을경우
		if (loginPlayer1 == (int)INFO_YES)
		{
			if (tileMap->_vItem[i]->_item.itemPos == itemPos)
			{
				//0번째 아이템포스인경우는 착용한경우임
				if (itemPos == 0)
				{
					if (tileMap->_vItem[i]->_item.isSelect == false) continue;

					if (tileMap->_vItem[i]->_item.itemType == TYPE_HELMET)
					{
						char itemName[256];
						INIDATA->addData("투구착용", "종류",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						char attackPower[256];
						INIDATA->addData("투구착용", "공격력",
							_itoa((int)tileMap->_vItem[i]->_item.attackPower, attackPower, 10));
						char defensePower[256];
						INIDATA->addData("투구착용", "방어력",
							_itoa((int)tileMap->_vItem[i]->_item.defensePower, defensePower, 10));
						char speedPower[256];
						INIDATA->addData("투구착용", "순발력",
							_itoa((int)tileMap->_vItem[i]->_item.speedPower, speedPower, 10));
						INIDATA->iniSave("플레이어1_아이템");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
					if (tileMap->_vItem[i]->_item.itemType == TYPE_CLUB ||
						tileMap->_vItem[i]->_item.itemType == TYPE_SPEAR ||
						tileMap->_vItem[i]->_item.itemType == TYPE_HATCHAT)
					{
						char itemName[256];
						INIDATA->addData("무기착용", "종류",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						char attackPower[256];
						INIDATA->addData("무기착용", "공격력",
							_itoa((int)tileMap->_vItem[i]->_item.attackPower, attackPower, 10));
						char defensePower[256];
						INIDATA->addData("무기착용", "방어력",
							_itoa((int)tileMap->_vItem[i]->_item.defensePower, defensePower, 10));
						char speedPower[256];
						INIDATA->addData("무기착용", "순발력",
							_itoa((int)tileMap->_vItem[i]->_item.speedPower, speedPower, 10));
						INIDATA->iniSave("플레이어1_아이템");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
					if (tileMap->_vItem[i]->_item.itemType == TYPE_ARMOR)
					{
						char itemName[256];
						INIDATA->addData("갑옷착용", "종류",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						char attackPower[256];
						INIDATA->addData("갑옷착용", "공격력",
							_itoa((int)tileMap->_vItem[i]->_item.attackPower, attackPower, 10));
						char defensePower[256];
						INIDATA->addData("갑옷착용", "방어력",
							_itoa((int)tileMap->_vItem[i]->_item.defensePower, defensePower, 10));
						char speedPower[256];
						INIDATA->addData("갑옷착용", "순발력",
							_itoa((int)tileMap->_vItem[i]->_item.speedPower, speedPower, 10));
						INIDATA->iniSave("플레이어1_아이템");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
					if (tileMap->_vItem[i]->_item.itemType == TYPE_RIDE_BOOK)
					{
						char itemName[256];
						INIDATA->addData("탑승문서착용", "종류",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						INIDATA->iniSave("플레이어1_아이템");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
				}
				//1번째 아이템칸에 템이 있을경우
				if (itemPos == 1)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템1", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템1", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어1_아이템");
					return;
				}

				//2번째 아이템칸에 템이 있을경우
				if (itemPos == 2)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템2", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템2", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어1_아이템");
					return;
				}

				//3번째 아이템칸에 템이 있을경우
				if (itemPos == 3)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템3", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템3", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어1_아이템");
					return;
				}

				//4번째 아이템칸에 템이 있을경우
				if (itemPos == 4)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템4", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템4", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어1_아이템");
					return;
				}

				//5번째 아이템칸에 템이 있을경우
				if (itemPos == 5)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템5", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템5", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어1_아이템");
					return;
				}

				//6번째 아이템칸에 템이 있을경우
				if (itemPos == 6)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템6", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템6", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어1_아이템");
					return;
				}

				//7번째 아이템칸에 템이 있을경우
				if (itemPos == 7)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템7", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템7", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어1_아이템");
					return;
				}

				//8번째 아이템칸에 템이 있을경우
				if (itemPos == 8)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템8", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템8", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어1_아이템");
					return;
				}

				//9번째 아이템칸에 템이 있을경우
				if (itemPos == 9)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템9", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템9", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어1_아이템");
					return;
				}

				//10번째 아이템칸에 템이 있을경우
				if (itemPos == 10)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템10", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템10", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어1_아이템");
					return;
				}

				//11번째 아이템칸에 템이 있을경우
				if (itemPos == 11)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템11", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템11", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어1_아이템");
					return;
				}

				//12번째 아이템칸에 템이 있을경우
				if (itemPos == 12)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템12", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템12", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어1_아이템");
					return;
				}

				//13번째 아이템칸에 템이 있을경우
				if (itemPos == 13)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템13", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템13", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어1_아이템");
					return;
				}

				//14번째 아이템칸에 템이 있을경우
				if (itemPos == 14)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템14", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템14", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어1_아이템");
					return;
				}

				//12번째 아이템칸에 템이 있을경우
				if (itemPos == 15)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템15", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템15", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어1_아이템");
					return;
				}
			}
		}

		//플레이어 2이 로그인했을경우
		if (loginPlayer2 == (int)INFO_YES)
		{
			if (tileMap->_vItem[i]->_item.itemPos == itemPos)
			{
				//0번째 아이템포스인경우는 착용한경우임
				if (itemPos == 0)
				{
					if (tileMap->_vItem[i]->_item.isSelect == false) continue;

					if (tileMap->_vItem[i]->_item.itemType == TYPE_HELMET)
					{
						char itemName[256];
						INIDATA->addData("투구착용", "종류",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						char attackPower[256];
						INIDATA->addData("투구착용", "공격력",
							_itoa((int)tileMap->_vItem[i]->_item.attackPower, attackPower, 10));
						char defensePower[256];
						INIDATA->addData("투구착용", "방어력",
							_itoa((int)tileMap->_vItem[i]->_item.defensePower, defensePower, 10));
						char speedPower[256];
						INIDATA->addData("투구착용", "순발력",
							_itoa((int)tileMap->_vItem[i]->_item.speedPower, speedPower, 10));
						INIDATA->iniSave("플레이어2_아이템");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
					if (tileMap->_vItem[i]->_item.itemType == TYPE_CLUB ||
						tileMap->_vItem[i]->_item.itemType == TYPE_SPEAR ||
						tileMap->_vItem[i]->_item.itemType == TYPE_HATCHAT)
					{
						char itemName[256];
						INIDATA->addData("무기착용", "종류",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						char attackPower[256];
						INIDATA->addData("무기착용", "공격력",
							_itoa((int)tileMap->_vItem[i]->_item.attackPower, attackPower, 10));
						char defensePower[256];
						INIDATA->addData("무기착용", "방어력",
							_itoa((int)tileMap->_vItem[i]->_item.defensePower, defensePower, 10));
						char speedPower[256];
						INIDATA->addData("무기착용", "순발력",
							_itoa((int)tileMap->_vItem[i]->_item.speedPower, speedPower, 10));
						INIDATA->iniSave("플레이어2_아이템");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
					if (tileMap->_vItem[i]->_item.itemType == TYPE_ARMOR)
					{
						char itemName[256];
						INIDATA->addData("갑옷착용", "종류",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						char attackPower[256];
						INIDATA->addData("갑옷착용", "공격력",
							_itoa((int)tileMap->_vItem[i]->_item.attackPower, attackPower, 10));
						char defensePower[256];
						INIDATA->addData("갑옷착용", "방어력",
							_itoa((int)tileMap->_vItem[i]->_item.defensePower, defensePower, 10));
						char speedPower[256];
						INIDATA->addData("갑옷착용", "순발력",
							_itoa((int)tileMap->_vItem[i]->_item.speedPower, speedPower, 10));
						INIDATA->iniSave("플레이어2_아이템");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
					if (tileMap->_vItem[i]->_item.itemType == TYPE_RIDE_BOOK)
					{
						char itemName[256];
						INIDATA->addData("탑승문서착용", "종류",
							_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));
						INIDATA->iniSave("플레이어2_아이템");
						tileMap->_vItem[i]->_item.isSelect = false;
						return;
					}
				}

				//1번째 아이템칸에 템이 있을경우
				if (itemPos == 1)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템1", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템1", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어2_아이템");
					return;
				}

				//2번째 아이템칸에 템이 있을경우
				if (itemPos == 2)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템2", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템2", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어2_아이템");
					return;
				}

				//3번째 아이템칸에 템이 있을경우
				if (itemPos == 3)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템3", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템3", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어2_아이템");
					return;
				}

				//4번째 아이템칸에 템이 있을경우
				if (itemPos == 4)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템4", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템4", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어2_아이템");
					return;
				}

				//5번째 아이템칸에 템이 있을경우
				if (itemPos == 5)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템5", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템5", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어2_아이템");
					return;
				}

				//6번째 아이템칸에 템이 있을경우
				if (itemPos == 6)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템6", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템6", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어2_아이템");
					return;
				}

				//7번째 아이템칸에 템이 있을경우
				if (itemPos == 7)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템7", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템7", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어2_아이템");
					return;
				}

				//8번째 아이템칸에 템이 있을경우
				if (itemPos == 8)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템8", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템8", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어2_아이템");
					return;
				}

				//9번째 아이템칸에 템이 있을경우
				if (itemPos == 9)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템9", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템9", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어2_아이템");
					return;
				}

				//10번째 아이템칸에 템이 있을경우
				if (itemPos == 10)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템10", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템10", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어2_아이템");
					return;
				}

				//11번째 아이템칸에 템이 있을경우
				if (itemPos == 11)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템11", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템11", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어2_아이템");
					return;
				}

				//12번째 아이템칸에 템이 있을경우
				if (itemPos == 12)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템12", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템12", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어2_아이템");
					return;
				}

				//13번째 아이템칸에 템이 있을경우
				if (itemPos == 13)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템13", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템13", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어2_아이템");
					return;
				}

				//14번째 아이템칸에 템이 있을경우
				if (itemPos == 14)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템14", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템14", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어2_아이템");
					return;
				}

				//12번째 아이템칸에 템이 있을경우
				if (itemPos == 15)
				{
					//종류 저장하고
					char itemName[256];
					INIDATA->addData("아이템15", "종류",
						_itoa((int)tileMap->_vItem[i]->_item.ItemName, itemName, 10));

					//갯수를 저장하고
					char itemNum[256];
					INIDATA->addData("아이템15", "갯수",
						_itoa(tileMap->_vItem[i]->_item.amount, itemNum, 10));

					INIDATA->iniSave("플레이어2_아이템");
					return;
				}
			}
		}
	}

}

void itemWindow::lineUpItem(tileMap * tileMap)
{
	//아이템 정렬용으로 쓸 생각
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
