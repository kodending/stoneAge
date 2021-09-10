#include "stdafx.h"
#include "tileMap.h"
#include "baseType.h"

tileMap::tileMap()
{
}

tileMap::~tileMap()
{
}

void tileMap::InputHandle()
{
	menuType* newType = _menuType->inputHandle(this);
	if (newType != nullptr)
	{
		SAFE_DELETE(_menuType);
		_menuType = newType;
		_menuType->enter(this);
	}
}

HRESULT tileMap::init()
{
	_tileMap[TILE_COUNT_X][TILE_COUNT_Y] = { 0, };

	_isoX = 0;
	_isoY = 0;
	_corner = 0;
	_closeListCount = 0;
	_isReSearchAStar = false;
	_isDontMoveMent = false;
	_mentCount = 0;

	_playerIsoX = _playerIsoY = 0;
	_palyerCorner = 0;

	_playerIdX = _playerIdY = 0;
	_moveIdX = _moveIdY = 0;

	int size = sizeof(_tileMap);

	memset(_tileMap, 0, size);

	_isMouseOnToolBar = false;

	_count = 0;

	_prePlayerCurrentIsoX = 0;
	_prePlayerCurrentIsoY = 0;
	_currentPlayerX = 0;
	_currentPlayerY = 0;
	_prePlayerCenterX = 0;
	_prePlayerCenterY = 0;
	_currentPlayerCenterX = 0;
	_currentPlayerCenterY = 0;
	frontPosX = 0;
	frontPosY = 0;
	rightPosX = 0;
	rightPosY = 0;
	leftPosX = 0;
	leftPosY = 0;
	_isEndTotalList = false;
	_isStartTotalList = false;

	for (int i = 0; i < TILE_COUNT_X; ++i)
	{
		for (int j = 0; j < TILE_COUNT_Y; ++j)
		{
			_tiles[i][j].isPrePlayer = false;
		}
	}

	setTiles();

	_isWriteInidata = false;

	_delayClickCount = 0;
	_isPosibleClick = false;
	_isMenuBarOn = false;

	_isMouseOnBaseLeft = false;
	_isMouseOnBaseRight = false;
	_isMouseOnAction = false;
	_isPlayerInfo = false;
	_isMouseOnState = false;
	_isMouseOnPet = false;
	_isDungeon = false;
	_isAvailableClickNPC = false;
	_isClickArmorNPC = false;
	_isClickWeaponNPC = false;

	_menuType = new baseType();
	_menuType->enter(this);

	return S_OK;
}

void tileMap::release()
{
	_menuType->exit(this);
}

void tileMap::update()
{
	writeInidata();
	playerMove();
	playerLastMove();
	updateMenuBar();
	mouseSelectTile();
	renderSwitch();
	RENDERMANAGER->update();

	_underBarRc = RectMake(CAMERAMANAGER->getCameraLEFT(), CAMERAMANAGER->getCameraBOTTOM() - 24, 800, 24);

	mouseLButton();
	mouseRButton();
	currentPlayerTile();
	whorfSpotSearch();
	NPCSpotSearch();

	initAStar();
	updateAStar();
	_menuType->update(this);

	if (_isDontMoveMent)
	{
		_mentCount++;
		if (_mentCount % 80 == 0)
		{
			_mentCount = 0;
			_isDontMoveMent = false;
		}
	}

	//�����϶��� NPCŬ�� �Ұ���
	if (_player->getIsPlayerMove() == true &&
		_isAvailableClickNPC == true)
	{
		_isAvailableClickNPC = false;
	}

	dungeonToBattle();
}

void tileMap::render()
{
	//Ÿ�Ϸ������ֱ�
	for (int i = 0; i < TILE_COUNT_X; ++i)
	{
		for (int j = 0; j < TILE_COUNT_Y; ++j)
		{
			//ī�޶� �ȿ����� �����ǰ� �ϱ����� �۾�
			RECT temp;
			RECT cameraRect = RectMake(CAMERAMANAGER->getCameraLEFT(), CAMERAMANAGER->getCameraTOP(), CAMERAX, CAMERAY);
			RECT tileRect = RectMake(_tiles[i][j].left, _tiles[i][j].top, 64, 47);
			if (!IntersectRect(&temp, &cameraRect, &tileRect)) continue;

			IMAGEMANAGER->frameRender("tile", getMemDC(), _tiles[i][j].left, _tiles[i][j].top,
				_tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
		}
	}

	//������Ʈ�������ֱ�(z-order��)
	RENDERMANAGER->render(getMemDC(), _player->getPlayerImageName().c_str());

	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		//����Ÿ�� �������ֱ�
		for (int i = 0; i < TILE_COUNT_X; ++i)
		{
			for (int j = 0; j < TILE_COUNT_Y; ++j)
			{
				//�̵����� Ÿ���̸� �׸����ʰԲ� ����ó��
				if (_tiles[i][j].tileType == TYPE_MOVE) continue;

				//ī�޶� �ȿ����� �����ǰ� �ϱ����� �۾�
				RECT temp;
				RECT cameraRect = RectMake(CAMERAMANAGER->getCameraLEFT(), CAMERAMANAGER->getCameraTOP(), CAMERAX, CAMERAY);
				RECT tileRect = RectMake(_tiles[i][j].left, _tiles[i][j].top, 64, 47);
				if (!IntersectRect(&temp, &cameraRect, &tileRect)) continue;

				IMAGEMANAGER->alphaFrameRender("tileType", getMemDC(), _tiles[i][j].left, _tiles[i][j].top,
					_tiles[i][j].tileTypeFrameX, _tiles[i][j].tileTypeFrameY, 100);
			}
		}
	}

	if (KEYMANAGER->isToggleKey(VK_F6))
	{
		//�÷��̾� ���� �ִ� Ÿ�� �������ֱ�
		for (int i = 0; i < TILE_COUNT_X; ++i)
		{
			for (int j = 0; j < TILE_COUNT_Y; ++j)
			{
				if (_tiles[i][j].isPlayer == false) continue;

				if (_tiles[i][j].isPlayer == true)
				{
					drawRhombus(_tiles[i][j].left, _tiles[i][j].top);
				}
			}
		}

		//�÷��̾� ���� ��ġ�ߴ� Ÿ�� �������ֱ�
		for (int i = 0; i < TILE_COUNT_X; ++i)
		{
			for (int j = 0; j < TILE_COUNT_Y; ++j)
			{
				if (_tiles[i][j].isPrePlayer == false) continue;

				if (_tiles[i][j].isPrePlayer == true)
				{
					drawRhombus(_tiles[i][j].left, _tiles[i][j].top);
				}
			}
		}
	}

	drawTileMap();
	renderAStar();

	IMAGEMANAGER->render("underBar2", getMemDC(), _underBarRc.left, _underBarRc.top);

	_menuType->render(this);
	renderMenuBar();

	IMAGEMANAGER->render("mouse", getMemDC(), _ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY);

	//����׿�
	//SetTextColor(getMemDC(), RGB(255, 0, 0));
	//sprintf(str, "��Ż : %d \n ���� : %d \n Ŭ���� : %d \ n _moveIdX : %d,  _moveIdY : %d",
	//	_vTotalList.size(), _vOpenList.size(), _vCloseList.size(), /*_endTile->getIdX(), _endTile->getIdY()*/ _moveIdX, _moveIdY);
	//TextOut(getMemDC(), CAMERAMANAGER->getCameraCenterX() - 200, CAMERAMANAGER->getCameraCenterY() - 200, str, strlen(str));

	//if (_vOpenList.size() != 0)
	//{
	//	SetTextColor(getMemDC(), RGB(255, 0, 0));
	//	sprintf(str, "%d", sqrtf(RADIUS_WIDTH * RADIUS_WIDTH + RADIUS_HEIGHT * RADIUS_HEIGHT));
	//	TextOut(getMemDC(), CAMERAMANAGER->getCameraCenterX() - 200, CAMERAMANAGER->getCameraCenterY() - 250, str, strlen(str));
	//}


	if (_isDontMoveMent == true)
	{
		HFONT font = CreateFont(20, 0, 0, 0, 600, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY������B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(30, 80, 120));
		sprintf(str, "������� ��Ÿ�� ���� �����ϴٰ� �߾�");
		TextOut(getMemDC(), CAMERAMANAGER->getCameraCenterX() - 180, CAMERAMANAGER->getCameraCenterY() - 100, str, strlen(str));
		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}
}

void tileMap::moveCamera()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() - 5);
		_cameraBufferX -= 5;

		if (CAMERAMANAGER->getCameraLEFT() <= 0)
		{
			CAMERAMANAGER->setCameraX(0);
			_cameraBufferX = 0;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() + 5);
		_cameraBufferX += 5;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() - 5);
		_cameraBufferY -= 5;

		if (CAMERAMANAGER->getCameraTOP() <= 0)
		{
			CAMERAMANAGER->setCameraY(0);
			_cameraBufferY = 0;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() + 5);
		_cameraBufferY += 5;
	}
}

void tileMap::drawTileMap()
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			int left = INIT_X + (i * RADIUS_WIDTH) - (j * RADIUS_WIDTH);
			int top = INIT_Y + (i * RADIUS_HEIGHT) + (j * RADIUS_HEIGHT);

			int centerX = left + RADIUS_WIDTH;
			int centerY = top + RADIUS_HEIGHT;

			if (_tileMap[i][j] == 1)
			{
				IMAGEMANAGER->render("tileSelect", getMemDC(), left, top);
			}

			if (KEYMANAGER->isToggleKey(VK_F1))
			{
				//��ǥ���� �ҷ����� (���߿� �ּ�ó�����ּ���)
				SetTextColor(getMemDC(), RGB(255, 0, 0));
				sprintf(str, "(%d, %d)", i, j);
				TextOut(getMemDC(), centerX, centerY, str, strlen(str));
			}

			//Ÿ�� ����Ʈ, ž ��ǥ ��ƹ�����
			_tiles[i][j].left = left;
			_tiles[i][j].top = top;

			_tiles[i][j].rc = RectMake(_tiles[i][j].left, _tiles[i][j].top, 64, 47);
			_tiles[i][j].centerX = _tiles[i][j].left + RADIUS_WIDTH;
			_tiles[i][j].centerY = _tiles[i][j].top + RADIUS_HEIGHT;
		}
	}
}

void tileMap::drawRhombus(int left, int top)
{
	int centerX = left + RADIUS_WIDTH;
	int centerY = top + RADIUS_HEIGHT;

	POINT p[5];
	p[0].x = centerX;
	p[0].y = centerY - RADIUS_HEIGHT;
	p[1].x = centerX + RADIUS_WIDTH;
	p[1].y = centerY;
	p[2].x = centerX;
	p[2].y = centerY + RADIUS_HEIGHT;
	p[3].x = centerX - RADIUS_WIDTH;
	p[3].y = centerY;
	p[4].x = centerX;
	p[4].y = centerY - RADIUS_HEIGHT;

	MoveToEx(getMemDC(), p[0].x, p[0].y, NULL);
	for (int i = 1; i < 5; i++)
	{
		LineTo(getMemDC(), p[i].x, p[i].y);
	}
}

int tileMap::getCornerIndex(int isoX, int isoY)
{
	int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
	int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

	int right = left + CELL_WIDTH;
	int bottom = top + CELL_HEIGHT;

	//���콺 ��ǥ �ȿ� ���� ������ �������� 4�и� ����
	//left Top : 1, right Top : 2, left Bottom : 3, right Bottom : 4
	float dx = (_ptMouse.x + _cameraBufferX - left) / (float)CELL_WIDTH;
	float dy = (_ptMouse.y + _cameraBufferY - top) / (float)CELL_HEIGHT;

	if (dx < 0.5f && dy < 0.5f) return 1;
	if (dx >= 0.5f && dy < 0.5f) return 2;
	if (dx < 0.5f && dy >= 0.5f) return 3;
	if (dx >= 0.5f && dy >= 0.5f) return 4;

	return 0;
}

bool tileMap::isInRhombus(int corner, int isoX, int isoY)
{
	if (corner == 1)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		float dx = (float)(_ptMouse.x + _cameraBufferX - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(_ptMouse.y + _cameraBufferY - top) / (CELL_HEIGHT / 2.0f);
		if ((1.0f - dy) <= dx) return true;
		else return false;
	}
	else if (corner == 2)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		left += (CELL_WIDTH / 2.0f);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		float dx = (float)(_ptMouse.x + _cameraBufferX - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(_ptMouse.y + _cameraBufferY - top) / (CELL_HEIGHT / 2.0f);
		if (dy >= dx) return true;
		else return false;
	}
	else if (corner == 3)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);

		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);
		top += (CELL_HEIGHT / 2.0f);

		float dx = (float)(_ptMouse.x + _cameraBufferX - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(_ptMouse.y + _cameraBufferY - top) / (CELL_HEIGHT / 2.0f);
		if (dy <= dx) return true;
		else return false;
	}
	else if (corner == 4)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		left += (CELL_WIDTH / 2.0f);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);
		top += (CELL_HEIGHT / 2.0f);

		float dx = (float)(_ptMouse.x + _cameraBufferX - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(_ptMouse.y + _cameraBufferY - top) / (CELL_HEIGHT / 2.0f);
		if ((1.0f - dy) >= dx) return true;
		else return false;
	}

	return false;
}

void tileMap::setMenuBar()
{
	_menuMapRc = RectMake(CAMERAMANAGER->getCameraLEFT(), CAMERAMANAGER->getCameraBOTTOM(), 114, 24);
	_menuStateRc = RectMake(_menuMapRc.right, CAMERAMANAGER->getCameraBOTTOM(), 114, 24);
	_menuPetRc = RectMake(_menuStateRc.right, CAMERAMANAGER->getCameraBOTTOM(), 114, 24);
	_menuItemRc = RectMake(_menuPetRc.right, CAMERAMANAGER->getCameraBOTTOM(), 114, 24);
	_menuMailRc = RectMake(_menuItemRc.right, CAMERAMANAGER->getCameraBOTTOM(), 114, 24);
	_menuAlbumRc = RectMake(_menuMailRc.right, CAMERAMANAGER->getCameraBOTTOM(), 114, 24);
	_menuSystemRc = RectMake(_menuAlbumRc.right, CAMERAMANAGER->getCameraBOTTOM(), 116, 24);

	_toolY = CAMERAMANAGER->getCameraBOTTOM() + _cameraBufferY;
}

void tileMap::updateMenuBar()
{
	if (_isMenuBarOn == true)
	{
		_toolY = CAMERAMANAGER->getCameraBOTTOM() - 24;
	}

	if (PtInRect(&_underBarRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		if (_toolY > CAMERAMANAGER->getCameraBOTTOM() - 24 && _isMenuBarOn == false)
		{
			_toolY -= 5.0f;
		}

		else if (_toolY <= CAMERAMANAGER->getCameraBOTTOM() - 24)
		{
			_toolY = CAMERAMANAGER->getCameraBOTTOM() - 24;
			_isMenuBarOn = true;
		}
	}

	else
	{
		if (_toolY < CAMERAMANAGER->getCameraBOTTOM())
		{
			_toolY += 5.0f;
			_isMenuBarOn = false;
		}

		else
		{
			_toolY = CAMERAMANAGER->getCameraBOTTOM();
		}
	}

	//���ù�ư���� �ȿö����������� false���༭ Ÿ�� ���õǰԲ�
	if (PtInRect(&_underBarRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		_isMouseOnToolBar = true;
	}

	else _isMouseOnToolBar = false;

	_menuMapRc = RectMake(CAMERAMANAGER->getCameraLEFT(), _toolY, 114, 24);
	_menuStateRc = RectMake(_menuMapRc.right, _toolY, 114, 24);
	_menuPetRc = RectMake(_menuStateRc.right, _toolY, 114, 24);
	_menuItemRc = RectMake(_menuPetRc.right, _toolY, 114, 24);
	_menuMailRc = RectMake(_menuItemRc.right, _toolY, 114, 24);
	_menuAlbumRc = RectMake(_menuMailRc.right, _toolY, 114, 24);
	_menuSystemRc = RectMake(_menuAlbumRc.right, _toolY, 116, 24);
}

void tileMap::renderMenuBar()
{
	IMAGEMANAGER->render("menuBar", getMemDC(),
		CAMERAMANAGER->getCameraLEFT(), _menuMapRc.top);

	HPEN myPen = CreatePen(PS_DASH, 3, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	if (PtInRect(&_menuMapRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _menuMapRc);
	}

	if (PtInRect(&_menuStateRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _menuStateRc);
	}

	if (PtInRect(&_menuPetRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _menuPetRc);
	}

	if (PtInRect(&_menuItemRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _menuItemRc);
	}

	if (PtInRect(&_menuMailRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _menuMailRc);
	}

	if (PtInRect(&_menuAlbumRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _menuAlbumRc);
	}

	if (PtInRect(&_menuSystemRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _menuSystemRc);
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void tileMap::mouseSelectTile()
{
	float cellX = (float)(_ptMouse.x - INIT_X + _cameraBufferX);
	if (cellX < 0)
	{
		cellX = (cellX - CELL_WIDTH) / CELL_WIDTH;
	}
	else
	{
		cellX = (cellX) / (float)CELL_WIDTH;
	}

	int cellY = (abs)((_ptMouse.y - INIT_Y + _cameraBufferY)) / CELL_HEIGHT;
	cellY = (_ptMouse.y < INIT_Y) ? cellY * -1 : cellY;

	int isoX = (int)cellX + (int)cellY;
	int isoY = (int)cellY - (int)cellX;

	if (isoX >= 0 && isoX < TILE_COUNT_X &&
		isoY >= 0 && isoY < TILE_COUNT_Y)
	{
		//1�и� -> [x - 1][y]
		//2�и� -> [x][y - 1]
		//3�и� -> [x][y + 1]
		//4�и� -> [x + 1][y]
		int corner = getCornerIndex(isoX, isoY);
		if (isInRhombus(corner, isoX, isoY))
		{
			corner = 0;
		}

		_corner = corner;
		_isoX = isoX;
		_isoY = isoY;

		switch (corner)
		{
		case 1:
			isoX = isoX - 1;
			break;
		case 2:
			isoY = isoY - 1;
			break;
		case 3:
			isoY = isoY + 1;
			break;
		case 4:
			isoX = isoX + 1;
			break;
		}

		//���콺Ŀ�� ��ġ �ø�������
		for (int i = 0; i < TILE_COUNT_X; ++i)
		{
			for (int j = 0; j < TILE_COUNT_Y; ++j)
			{
				if (i == isoX && j == isoY)
				{
					_tileMap[i][j] = 1;
				}

				else
				{
					_tileMap[i][j] = 0;
				}
			}
		}
	}
}

void tileMap::setCamera(int isoX, int isoY)
{
	RECT temp = RectMakeCenter(_tiles[isoX][isoY].left, _tiles[isoX][isoY].top, CAMERAX, CAMERAY);

	_cameraBufferX = temp.left + 32;
	_cameraBufferY = temp.top + 23.5f;

	CAMERAMANAGER->setCamera(_cameraBufferX, _cameraBufferY);

	setMenuBar();
}

TERRAIN tileMap::terrainSelect(int frameX, int frameY)
{
	//1�� ~ 6��
	if (frameX >= 0 && frameX <= 13 &&
		frameY >= 0 && frameY <= 5)
	{
		return TR_DESERT;
	}

	//7��
	if (frameX >= 0 && frameX <= 13 &&
		frameY == 6)
	{
		return TR_WATER;
	}

	//8��
	if (frameX >= 0 && frameX <= 13 &&
		frameY == 7)
	{
		return TR_GRASS;
	}

	//9~11��
	if (frameX >= 0 && frameX <= 13 &&
		frameY >= 8 && frameY <= 10)
	{
		return TR_LAVAREGION;
	}

	//12��
	if (frameX >= 0 && frameX <= 13 &&
		frameY == 11)
	{
		return TR_DIRT;
	}

	//13 ~ 14��
	if (frameX >= 0 && frameX <= 13 &&
		frameY >= 12 && frameY <= 13)
	{
		return TR_GRASS;
	}

	//15��
	if (frameX >= 0 && frameX <= 13 &&
		frameY == 14)
	{
		return TR_LAVAREGION;
	}

	//16~17��
	if (frameX >= 0 && frameX <= 13 &&
		frameY >= 15 && frameY <= 16)
	{
		return TR_LAVA;
	}

	//18��
	if (frameX >= 0 && frameX <= 13 &&
		frameY == 17)
	{
		return TR_GRASS;
	}

	//19��
	if (frameX >= 0 && frameX <= 13 &&
		frameY == 18)
	{
		return TR_LAVAREGION;
	}

	//20 ~ 21��
	if (frameX >= 0 && frameX <= 13 &&
		frameY >= 19 && frameY <= 20)
	{
		return TR_DIRT;
	}

	return TERRAIN();
}

TILETYPE tileMap::tileTypeSelect(int frameX, int frameY)
{
	if (frameX == 0) return TYPE_MOVE;
	if (frameX == 1) return TYPE_UNMOVE;
	if (frameX == 2) return TYPE_WHORF_CHIEF;
	if (frameX == 3) return TYPE_WHORF_ITEMSHOP;
	if (frameX == 4) return TYPE_WHORF_PETSHOP;
	if (frameX == 5) return TYPE_WHORF_HOSPITAL;
	if (frameX == 6) return TYPE_WHORF_DUNGEON1;
	if (frameX == 7) return TYPE_WHORF_DUNGEON2;
	if (frameX == 8) return TYPE_WHORF_DUNGEON3;
	if (frameX == 9) return TYPE_WHORF_DUNGEON4;
	if (frameX == 10) return TYPE_WHORF_VILLAGE;

	return TILETYPE();
}

void tileMap::renderSwitch()
{
	for (int j = 0; j < TILE_COUNT_Y; ++j)
	{
		for (int i = 0; i < TILE_COUNT_X; ++i)
		{
			if (!_tiles[i][j].objRendered) continue;

			if (_tiles[i][j].obj == OBJ_NONE)
			{
				_tiles[i][j].objRendered = false;
			}
		}
	}
	for (int j = 0; j < TILE_COUNT_Y; ++j)
	{
		for (int i = 0; i < TILE_COUNT_X; ++i)
		{
			if (_tiles[i][j].obj == OBJ_NONE) continue;

			if (!_tiles[i][j].objRendered)
			{
				if (_tiles[i][j].obj == OBJ_STRUCTURE)
				{
					_tiles[i][j].objRendered = true;

					RENDERMANAGER->addObj("structure", "structure", &_tiles[i][j].objRendered, &_tiles[i][j].centerX, &_tiles[i][j].centerY,
						&_tiles[i][j].objFrameX, &_tiles[i][j].objFrameY);
				}

				else if (_tiles[i][j].obj == OBJ_OBJECT)
				{
					_tiles[i][j].objRendered = true;

					RENDERMANAGER->addObj("object", "object", &_tiles[i][j].objRendered, &_tiles[i][j].centerX, &_tiles[i][j].centerY,
						&_tiles[i][j].objFrameX, &_tiles[i][j].objFrameY);
				}

				else if (_tiles[i][j].obj == OBJ_FENCE)
				{
					_tiles[i][j].objRendered = true;

					RENDERMANAGER->addObj("fence", "fence", &_tiles[i][j].objRendered, &_tiles[i][j].centerX, &_tiles[i][j].centerY,
						&_tiles[i][j].objFrameX, &_tiles[i][j].objFrameY);
				}

				else if (_tiles[i][j].obj == OBJ_GATE)
				{
					_tiles[i][j].objRendered = true;

					RENDERMANAGER->addObj("gate", "gate", &_tiles[i][j].objRendered, &_tiles[i][j].centerX, &_tiles[i][j].centerY,
						&_tiles[i][j].objFrameX, &_tiles[i][j].objFrameY);
				}

				else if (_tiles[i][j].obj == OBJ_DISPLAY)
				{
					_tiles[i][j].objRendered = true;

					RENDERMANAGER->addObj("display", "display", &_tiles[i][j].objRendered, &_tiles[i][j].centerX, &_tiles[i][j].centerY,
						&_tiles[i][j].objFrameX, &_tiles[i][j].objFrameY);
				}

				else if (_tiles[i][j].obj == OBJ_PLANTS)
				{
					_tiles[i][j].objRendered = true;

					RENDERMANAGER->addObj("plants", "plants", &_tiles[i][j].objRendered, &_tiles[i][j].centerX, &_tiles[i][j].centerY,
						&_tiles[i][j].objFrameX, &_tiles[i][j].objFrameY);
				}

				else if (_tiles[i][j].obj == OBJ_ROCK)
				{
					_tiles[i][j].objRendered = true;

					RENDERMANAGER->addObj("rock", "rock", &_tiles[i][j].objRendered, &_tiles[i][j].centerX, &_tiles[i][j].centerY,
						&_tiles[i][j].objFrameX, &_tiles[i][j].objFrameY);
				}

				else if (_tiles[i][j].obj == OBJ_WALL_BASIC)
				{
					_tiles[i][j].objRendered = true;

					RENDERMANAGER->addObj("wall_basic", "wall_basic", &_tiles[i][j].objRendered, &_tiles[i][j].centerX, &_tiles[i][j].centerY,
						&_tiles[i][j].objFrameX, &_tiles[i][j].objFrameY);
				}

				else if (_tiles[i][j].obj == OBJ_WALL_DUNGEON)
				{
					_tiles[i][j].objRendered = true;

					RENDERMANAGER->addObj("wall_dungeon", "wall_dungeon", &_tiles[i][j].objRendered, &_tiles[i][j].centerX, &_tiles[i][j].centerY,
						&_tiles[i][j].objFrameX, &_tiles[i][j].objFrameY);
				}

				else if (_tiles[i][j].obj == OBJ_NPC)
				{
					_tiles[i][j].objRendered = true;

					RENDERMANAGER->addObj("npc", "npc", &_tiles[i][j].objRendered, &_tiles[i][j].centerX, &_tiles[i][j].centerY,
						&_tiles[i][j].objFrameX, &_tiles[i][j].objFrameY);
				}
			}
		}
	}
}

void tileMap::setTiles()
{
	for (int i = 0; i < TILE_COUNT_X; i++)
	{
		for (int j = 0; j < TILE_COUNT_Y; j++)
		{
			int left = INIT_X  + (i * RADIUS_WIDTH) - (j * RADIUS_WIDTH);
			int top = INIT_Y + (i * RADIUS_HEIGHT) + (j * RADIUS_HEIGHT);

			int centerX = left + RADIUS_WIDTH;
			int centerY = top + RADIUS_HEIGHT;

			//Ÿ�� ����Ʈ, ž ��ǥ ��ƹ�����
			_tiles[i][j].left = left;
			_tiles[i][j].top = top;

			_tiles[i][j].rc = RectMake(_tiles[i][j].left, _tiles[i][j].top, 64, 47);
			_tiles[i][j].centerX = left + RADIUS_WIDTH;
			_tiles[i][j].centerY = top + RADIUS_HEIGHT;
		}
	}
}

void tileMap::playerMovePoint(float x, float y)
{
	_player->setPlayerMoveEndX(x + RADIUS_WIDTH);
	_player->setPlayerMoveEndY(y + RADIUS_HEIGHT);
}

void tileMap::playerMove()
{
	if (_vCloseList.size() == 0) return; //�ϴ� �߰�
	if (_closeListCount == _vCloseList.size()) return;

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeedX = _player->getPlayerSpeedX();
	float moveSpeedY = _player->getPlayerSpeedY();

	//�÷��̾����� �����̰� �ִٰ� �˷��ִ� ��ġ
	_player->setIsPlayerMove(true);

	//�÷��̾� ���� ��ġ�� ���콺����Ʈ ���� x��ǥ�� ������� ���������� ����������
	if (_player->getPlayerCenterX() < _vCloseList[_closeListCount]->getCenter().x)
	{
		//�����񱳴� _player->getPlayerMoveEndX, Y�� ���߾���
		_cameraBufferX += moveSpeedX;
		_prePlayerCenterX = _player->getPlayerCenterX();

		if (CAMERAMANAGER->getCameraCenterX() <= _vCloseList[_closeListCount]->getCenter().x)
		{
			_player->setPlayerCenterX(_player->getPlayerCenterX() + moveSpeedX);
			CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() + moveSpeedX);
		}

		if (_player->getPlayerCenterX() >= _vCloseList[_closeListCount]->getCenter().x)
		{
			_player->setPlayerCenterX(_vCloseList[_closeListCount]->getCenter().x);
			if (CAMERAMANAGER->getCameraLEFT() > 0)
			{
				CAMERAMANAGER->setCameraCenterX(_vCloseList[_closeListCount]->getCenter().x);
				_cameraBufferX = CAMERAMANAGER->getCameraLEFT();
			}
		}
	}

	//�÷��̾� ���� ��ġ�� ���콺����Ʈ ���� x��ǥ�� Ŭ��� �������� ����������
	if (_player->getPlayerCenterX() > _vCloseList[_closeListCount]->getCenter().x)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_player->setPlayerCenterX(_player->getPlayerCenterX() - moveSpeedX);
		CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() - moveSpeedX);
		_cameraBufferX -= moveSpeedX;

		if (_player->getPlayerCenterX() <= _vCloseList[_closeListCount]->getCenter().x)
		{
			_player->setPlayerCenterX(_vCloseList[_closeListCount]->getCenter().x);
			if (CAMERAMANAGER->getCameraLEFT() > 0)
			{
				CAMERAMANAGER->setCameraCenterX(_vCloseList[_closeListCount]->getCenter().x);
				_cameraBufferX = CAMERAMANAGER->getCameraLEFT();
			}
		}

		if (CAMERAMANAGER->getCameraLEFT() <= 0)
		{
			CAMERAMANAGER->setCameraX(0);
			_cameraBufferX = 0;
		}
	}

	//�÷��̾� ���� ��ġ�� ���콺����Ʈ ���� Y��ǥ�� ������� �Ʒ������� ����������
	if (_player->getPlayerCenterY() < _vCloseList[_closeListCount]->getCenter().y)
	{
		_prePlayerCenterY = _player->getPlayerCenterY();
		_player->setPlayerCenterY(_player->getPlayerCenterY() + moveSpeedY);

		if (CAMERAMANAGER->getCameraCenterY() <= _vCloseList[_closeListCount]->getCenter().y)
		{
			CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() + moveSpeedY);
			_cameraBufferY += moveSpeedY;
		}

		if (_player->getPlayerCenterY() >= _vCloseList[_closeListCount]->getCenter().y)
		{
			_player->setPlayerCenterY(_vCloseList[_closeListCount]->getCenter().y);
			if (CAMERAMANAGER->getCameraTOP() > 0)
			{
				CAMERAMANAGER->setCameraCenterY(_vCloseList[_closeListCount]->getCenter().y);
				_cameraBufferY = CAMERAMANAGER->getCameraTOP();
			}
		}
	}

	//�÷��̾� ���� ��ġ�� ���콺����Ʈ ���� Y��ǥ�� Ŭ��� �������� ����������
	if (_player->getPlayerCenterY() > _vCloseList[_closeListCount]->getCenter().y)
	{
		_prePlayerCenterY = _player->getPlayerCenterY();
		_player->setPlayerCenterY(_player->getPlayerCenterY() - moveSpeedY);
		CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() - moveSpeedY);
		_cameraBufferY -= moveSpeedY;

		if (_player->getPlayerCenterY() <= _vCloseList[_closeListCount]->getCenter().y)
		{
			_player->setPlayerCenterY(_vCloseList[_closeListCount]->getCenter().y);
			if (CAMERAMANAGER->getCameraTOP() > 0)
			{
				CAMERAMANAGER->setCameraCenterY(_vCloseList[_closeListCount]->getCenter().y);
				_cameraBufferY = CAMERAMANAGER->getCameraTOP();
			}
		}

		if (CAMERAMANAGER->getCameraTOP() <= 0)
		{
			CAMERAMANAGER->setCameraY(0);
			_cameraBufferY = 0;
		}
	}

	_player->setPlayerRect(RectMakeCenter(_player->getPlayerCenterX() + _player->getPlayerImageMoveX(), _player->getPlayerCenterY() + _player->getPlayerImageMoveY(),
		_player->getPlayerImage()->getFrameWidth(), _player->getPlayerImage()->getFrameHeight()));
	_player->setPlayerImageCenterX(_player->getPlayerCenterX() + _player->getPlayerImageMoveX());
	_player->setPlayerImageCenterY(_player->getPlayerCenterY() + _player->getPlayerImageMoveY());
	_player->setPlayerTileRect(RectMakeCenter(_player->getPlayerCenterX(), _player->getPlayerCenterY(),
		64, 47));

	if (_player->getPlayerCenterX() == _vCloseList[_closeListCount]->getCenter().x &&
		_player->getPlayerCenterY() == _vCloseList[_closeListCount]->getCenter().y)
	{
		_closeListCount++;
		if (_closeListCount == _vCloseList.size())
		{
			_closeListCount = _vCloseList.size();
			_player->setIsMoveClick(true);
		}
	}

	//�÷��̾� ������ ���⿡ ���� �̵����� �����ϱ�

	//6�ù����ΰ��
	if (_player->getPlayerCenterX() == _prePlayerCenterX &&
		_player->getPlayerCenterY() > _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_SIX);
		return;
	}

	//7�ù����ΰ��
	if (_player->getPlayerCenterX() < _prePlayerCenterX &&
		_player->getPlayerCenterY() > _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_SEVEN);
		return;
	}

	//9�ù����ΰ��
	if (_player->getPlayerCenterX() < _prePlayerCenterX &&
		_player->getPlayerCenterY() == _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_NINE);
		return;
	}

	//11�ù����ΰ��
	if (_player->getPlayerCenterX() < _prePlayerCenterX &&
		_player->getPlayerCenterY() < _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_ELEVEN);
		return;
	}

	//12�ù����ΰ��
	if (_player->getPlayerCenterX() == _prePlayerCenterX &&
		_player->getPlayerCenterY() < _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_TWELVE);
		return;
	}

	//1�ù����ΰ��
	if (_player->getPlayerCenterX() > _prePlayerCenterX &&
		_player->getPlayerCenterY() < _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_ONE);
		return;
	}

	//3�ù����ΰ��
	if (_player->getPlayerCenterX() > _prePlayerCenterX &&
		_player->getPlayerCenterY() == _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_THREE);
		return;
	}

	//5�ù����ΰ��
	if (_player->getPlayerCenterX() > _prePlayerCenterX &&
		_player->getPlayerCenterY() > _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_FIVE);
		return;
	}
}

void tileMap::playerLastMove()
{
	if (_player->getIsMoveClick() == false) return;

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeedX = _player->getPlayerSpeedX();
	float moveSpeedY = _player->getPlayerSpeedY();

	//�÷��̾� ���� ��ġ�� ���콺����Ʈ ���� x��ǥ�� ������� ���������� ����������
	if (_player->getPlayerCenterX() < _player->getPlayerMoveEndX())
	{
		//�����񱳴� _player->getPlayerMoveEndX, Y�� ���߾���
		_cameraBufferX += moveSpeedX;
		_prePlayerCenterX = _player->getPlayerCenterX();

		if (CAMERAMANAGER->getCameraCenterX() <= _player->getPlayerMoveEndX())
		{
			_player->setPlayerCenterX(_player->getPlayerCenterX() + moveSpeedX);
			CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() + moveSpeedX);
		}

		if (_player->getPlayerCenterX() >= _player->getPlayerMoveEndX())
		{
			_player->setPlayerCenterX(_player->getPlayerMoveEndX());
			if (CAMERAMANAGER->getCameraLEFT() > 0)
			{
				CAMERAMANAGER->setCameraCenterX(_player->getPlayerMoveEndX());
				_cameraBufferX = CAMERAMANAGER->getCameraLEFT();
			}
		}
	}

	//�÷��̾� ���� ��ġ�� ���콺����Ʈ ���� x��ǥ�� Ŭ��� �������� ����������
	if (_player->getPlayerCenterX() > _player->getPlayerMoveEndX())
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_player->setPlayerCenterX(_player->getPlayerCenterX() - moveSpeedX);
		CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() - moveSpeedX);
		_cameraBufferX -= moveSpeedX;

		if (_player->getPlayerCenterX() <= _player->getPlayerMoveEndX())
		{
			_player->setPlayerCenterX(_player->getPlayerMoveEndX());
			if (CAMERAMANAGER->getCameraLEFT() > 0)
			{
				CAMERAMANAGER->setCameraCenterX(_player->getPlayerMoveEndX());
				_cameraBufferX = CAMERAMANAGER->getCameraLEFT();
			}
		}

		if (CAMERAMANAGER->getCameraLEFT() <= 0)
		{
			CAMERAMANAGER->setCameraX(0);
			_cameraBufferX = 0;
		}
	}

	//�÷��̾� ���� ��ġ�� ���콺����Ʈ ���� Y��ǥ�� ������� �Ʒ������� ����������
	if (_player->getPlayerCenterY() < _player->getPlayerMoveEndY())
	{
		_prePlayerCenterY = _player->getPlayerCenterY();
		_player->setPlayerCenterY(_player->getPlayerCenterY() + moveSpeedY);

		if (CAMERAMANAGER->getCameraCenterY() <= _player->getPlayerMoveEndY())
		{
			CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() + moveSpeedY);
			_cameraBufferY += moveSpeedY;
		}

		if (_player->getPlayerCenterY() >= _player->getPlayerMoveEndY())
		{
			_player->setPlayerCenterY(_player->getPlayerMoveEndY());
			if (CAMERAMANAGER->getCameraTOP() > 0)
			{
				CAMERAMANAGER->setCameraCenterY(_player->getPlayerMoveEndY());
				_cameraBufferY = CAMERAMANAGER->getCameraTOP();
			}
		}
	}

	//�÷��̾� ���� ��ġ�� ���콺����Ʈ ���� Y��ǥ�� Ŭ��� �������� ����������
	if (_player->getPlayerCenterY() > _player->getPlayerMoveEndY())
	{
		_prePlayerCenterY = _player->getPlayerCenterY();
		_player->setPlayerCenterY(_player->getPlayerCenterY() - moveSpeedY);
		CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() - moveSpeedY);
		_cameraBufferY -= moveSpeedY;

		if (_player->getPlayerCenterY() <= _player->getPlayerMoveEndY())
		{
			_player->setPlayerCenterY(_player->getPlayerMoveEndY());
			if (CAMERAMANAGER->getCameraTOP() > 0)
			{
				CAMERAMANAGER->setCameraCenterY(_player->getPlayerMoveEndY());
				_cameraBufferY = CAMERAMANAGER->getCameraTOP();
			}
		}

		if (CAMERAMANAGER->getCameraTOP() <= 0)
		{
			CAMERAMANAGER->setCameraY(0);
			_cameraBufferY = 0;
		}
	}

	_player->setPlayerRect(RectMakeCenter(_player->getPlayerCenterX() + _player->getPlayerImageMoveX(), _player->getPlayerCenterY() + _player->getPlayerImageMoveY(),
		_player->getPlayerImage()->getFrameWidth(), _player->getPlayerImage()->getFrameHeight()));
	_player->setPlayerImageCenterX(_player->getPlayerCenterX() + _player->getPlayerImageMoveX());
	_player->setPlayerImageCenterY(_player->getPlayerCenterY() + _player->getPlayerImageMoveY());
	_player->setPlayerTileRect(RectMakeCenter(_player->getPlayerCenterX(), _player->getPlayerCenterY(),
		64, 47));

	//������������ ����������~
	if (_player->getPlayerCenterX() == _player->getPlayerMoveEndX() &&
		_player->getPlayerCenterY() == _player->getPlayerMoveEndY())
	{
		_player->setIsMoveClick(false);
		_moveIdX = 0;
		_moveIdY = 0;
		_vCloseList.clear();
		_vOpenList.clear();
		_closeListCount = 0;
		_isReSearchAStar = true;
		_vTotalList.clear();
		SAFE_RELEASE(_startTile);
		SAFE_DELETE(_startTile);
		SAFE_RELEASE(_endTile);
		SAFE_DELETE(_endTile);

		_player->setIsPlayerMove(false);
		_player->setPlayerActionRun(false);

		//for (int i = 0; i < _vTotalList.size(); ++i)
		//{
		//	if (_vTotalList[i]->getAttribute() == "typeUnMove") continue;

		//	_vTotalList[i]->setParentNode(NULL);
		//	_vTotalList[i]->setCostFromStart(0);
		//	_vTotalList[i]->setCostToGoal(0);
		//	_vTotalList[i]->setTotalCost(0);
		//	_vTotalList[i]->setColor(RGB(255, 0, 255));
		//	_vTotalList[i]->setIsOpen(true);
		//	_vTotalList[i]->setIdX(0);
		//	_vTotalList[i]->setIdY(0);
		//	_vTotalList[i]->setAttribute("none");
		//}
	}


	//�÷��̾� ������ ���⿡ ���� �̵����� �����ϱ�

	//6�ù����ΰ��
	if (_player->getPlayerCenterX() == _prePlayerCenterX &&
		_player->getPlayerCenterY() > _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_SIX);
		return;
	}

	//7�ù����ΰ��
	if (_player->getPlayerCenterX() < _prePlayerCenterX &&
		_player->getPlayerCenterY() > _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_SEVEN);
		return;
	}

	//9�ù����ΰ��
	if (_player->getPlayerCenterX() < _prePlayerCenterX &&
		_player->getPlayerCenterY() == _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_NINE);
		return;
	}

	//11�ù����ΰ��
	if (_player->getPlayerCenterX() < _prePlayerCenterX &&
		_player->getPlayerCenterY() < _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_ELEVEN);
		return;
	}

	//12�ù����ΰ��
	if (_player->getPlayerCenterX() == _prePlayerCenterX &&
		_player->getPlayerCenterY() < _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_TWELVE);
		return;
	}

	//1�ù����ΰ��
	if (_player->getPlayerCenterX() > _prePlayerCenterX &&
		_player->getPlayerCenterY() < _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_ONE);
		return;
	}

	//3�ù����ΰ��
	if (_player->getPlayerCenterX() > _prePlayerCenterX &&
		_player->getPlayerCenterY() == _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_THREE);
		return;
	}

	//5�ù����ΰ��
	if (_player->getPlayerCenterX() > _prePlayerCenterX &&
		_player->getPlayerCenterY() > _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_FIVE);
		return;
	}
}

void tileMap::mouseLButton()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		InputHandle();
	//	SOUNDMANAGER->play("click", 0.4f);
	}

	if (_isPosibleClick == false)
	{
		_delayClickCount++;
	}

	if (_delayClickCount >= 10 && _isPosibleClick == false)
	{
		_delayClickCount = 10;
		_isPosibleClick = true;
	}

	if (_isPosibleClick == false) return;
	if (_isMouseOnBaseLeft == true) return;
	if (_isMouseOnBaseRight == true) return;
	if (_isMouseOnAction == true) return;
	if (_isMouseOnState == true) return;
	if (_isMouseOnPet == true) return;

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		//ī�޶� ���� �̵��� ��ŭ + ����� �׿� �´� �ε����� ���� �� �ִ�
		float cellX = (float)(_ptMouse.x - INIT_X + _cameraBufferX);
		if (cellX < 0)
		{
			cellX = (cellX - CELL_WIDTH) / CELL_WIDTH;
		}
		else
		{
			cellX = (cellX) / (float)CELL_WIDTH;
		}

		int cellY = (abs)((_ptMouse.y - INIT_Y + _cameraBufferY)) / CELL_HEIGHT;
		cellY = (_ptMouse.y < INIT_Y) ? cellY * -1 : cellY;

		int isoX = (int)cellX + (int)cellY;
		int isoY = (int)cellY - (int)cellX;

		if (isoX >= 0 && isoX < TILE_COUNT_X &&
			isoY >= 0 && isoY < TILE_COUNT_Y)
		{
			//1�и� -> [x - 1][y]
			//2�и� -> [x][y - 1]
			//3�и� -> [x][y + 1]
			//4�и� -> [x + 1][y]
			int corner = getCornerIndex(isoX, isoY);
			if (isInRhombus(corner, isoX, isoY))
			{
				corner = 0;
			}

			_corner = corner;
			_isoX = isoX;
			_isoY = isoY;

			switch (corner)
			{
			case 1:
				isoX = isoX - 1;
				break;
			case 2:
				isoY = isoY - 1;
				break;
			case 3:
				isoY = isoY + 1;
				break;
			case 4:
				isoX = isoX + 1;
				break;
			}

			if (_tiles[isoX][isoY].tileType == TYPE_UNMOVE) return;
			if (PtInRect(&_underBarRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY))) return;
			if (isoX == _playerIdX && isoY == _playerIdY) return;

			playerMovePoint(_tiles[isoX][isoY].left, _tiles[isoX][isoY].top);

			if (_vTotalList.size() != 0)
			{
				_vTotalList.clear();
				_vCloseList.clear();
				_vOpenList.clear();
				SAFE_RELEASE(_startTile);
				SAFE_DELETE(_startTile);
				SAFE_RELEASE(_endTile);
				SAFE_DELETE(_endTile);
				_player->setIsMoveClick(false);
				_moveIdX = 0;
				_moveIdY = 0;
				_closeListCount = 0;
				_isReSearchAStar = true;
			}

			for (int i = 0; i < TILE_COUNT_X; ++i)
			{
				for (int j = 0; j < TILE_COUNT_Y; ++j)
				{
					if (_tiles[i][j].isMovePoint == true)
					{
						_tiles[i][j].isMovePoint = false;
					}

					if (i == isoX && j == isoY)
					{
						_tiles[i][j].isMovePoint = true;
						_moveIdX = i;
						_moveIdY = j;
					}
				}
			}
		}
	}
}

void tileMap::mouseRButton()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		clickNPC();
		SOUNDMANAGER->play("click", 0.4f);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		//ī�޶� ���� �̵��� ��ŭ + ����� �׿� �´� �ε����� ���� �� �ִ�
		float cellX = (float)(_ptMouse.x - INIT_X + _cameraBufferX);
		if (cellX < 0)
		{
			cellX = (cellX - CELL_WIDTH) / CELL_WIDTH;
		}
		else
		{
			cellX = (cellX) / (float)CELL_WIDTH;
		}

		int cellY = (abs)((_ptMouse.y - INIT_Y + _cameraBufferY)) / CELL_HEIGHT;
		cellY = (_ptMouse.y < INIT_Y) ? cellY * -1 : cellY;

		int isoX = (int)cellX + (int)cellY;
		int isoY = (int)cellY - (int)cellX;

		if (isoX >= 0 && isoX < TILE_COUNT_X &&
			isoY >= 0 && isoY < TILE_COUNT_Y)
		{
			//1�и� -> [x - 1][y]
			//2�и� -> [x][y - 1]
			//3�и� -> [x][y + 1]
			//4�и� -> [x + 1][y]
			int corner = getCornerIndex(isoX, isoY);
			if (isInRhombus(corner, isoX, isoY))
			{
				corner = 0;
			}

			_corner = corner;
			_isoX = isoX;
			_isoY = isoY;

			switch (corner)
			{
			case 1:
				isoX = isoX - 1;
				break;
			case 2:
				isoY = isoY - 1;
				break;
			case 3:
				isoY = isoY + 1;
				break;
			case 4:
				isoX = isoX + 1;
				break;
			}
		}

		//���⿡ �Լ� �־��~

		for (int i = 0; i < TILE_COUNT_X; ++i)
		{
			for (int j = 0; j < TILE_COUNT_Y; ++j)
			{
				if (_tiles[i][j].isPlayer == false) continue;
				if (i == isoX && j == isoY) continue;

				if (_tiles[i][j].isPlayer == true)
				{
					//6�ù����϶� �����Ӱ� �ٲٱ�
					if (i < isoX && j < isoY)
					{
						_player->setPlayerDirection(DIR_SIX);
						break;
					}

					//7�� �����϶� �����Ӱ� �ٲٱ�
					else if (i == isoX && j < isoY)
					{
						_player->setPlayerDirection(DIR_SEVEN);
						break;
					}

					//9�� �����϶� �����Ӱ� �ٲٱ�
					else if (i > isoX && j < isoY)
					{
						_player->setPlayerDirection(DIR_NINE);
						break;
					}

					//11�� �����϶� �����Ӱ� �ٲٱ�
					else if (i > isoX && j == isoY)
					{
						_player->setPlayerDirection(DIR_ELEVEN);
						break;
					}

					//12�� �����϶� �����Ӱ� �ٲٱ�
					else if (i > isoX && j > isoY)
					{
						_player->setPlayerDirection(DIR_TWELVE);
						break;
					}

					//1�� �����϶� �����Ӱ� �ٲٱ�
					else if (i == isoX && j > isoY)
					{
						_player->setPlayerDirection(DIR_ONE);
						break;
					}

					//3�� �����϶� �����Ӱ� �ٲٱ�
					else if (i < isoX && j > isoY)
					{
						_player->setPlayerDirection(DIR_THREE);
						break;
					}

					//5�� �����϶� �����Ӱ� �ٲٱ�
					else if (i < isoX && j == isoY)
					{
						_player->setPlayerDirection(DIR_FIVE);
						break;
					}
				}
			}
		}
	}
}

void tileMap::currentPlayerTile()
{
	float cellX = (float)((_player->getPlayerTileRect().left + _player->getPlayerTileRect().right) / 2 - INIT_X);
	if (cellX < 0)
	{
		cellX = (cellX - CELL_WIDTH) / CELL_WIDTH;
	}
	else
	{
		cellX = (cellX) / (float)CELL_WIDTH;
	}

	int cellY = (abs)((_player->getPlayerTileRect().top + _player->getPlayerTileRect().bottom) / 2 - INIT_Y) / CELL_HEIGHT;
	cellY = ((_player->getPlayerTileRect().top + _player->getPlayerTileRect().bottom) / 2 < INIT_Y) ? cellY * -1 : cellY;

	int isoX = (int)cellX + (int)cellY;
	int isoY = (int)cellY - (int)cellX;

	if (isoX >= 0 && isoX < TILE_COUNT_X &&
		isoY >= 0 && isoY < TILE_COUNT_Y)
	{
		//1�и� -> [x - 1][y]
		//2�и� -> [x][y - 1]
		//3�и� -> [x][y + 1]
		//4�и� -> [x + 1][y]
		int corner = getCornerPlayerIndex(isoX, isoY);
		if (isInPlayerRhombus(corner, isoX, isoY))
		{
			corner = 0;
		}

		_palyerCorner = corner;
		_playerIsoX = isoX;
		_playerIsoY = isoY;

		switch (corner)
		{
		case 1:
			isoX = isoX - 1;
			break;
		case 2:
			isoY = isoY - 1;
			break;
		case 3:
			isoY = isoY + 1;
			break;
		case 4:
			isoX = isoX + 1;
			break;
		}

		//���� �÷��̾� ��ġ�� Ȯ���ϱ� ����
		for (int i = 0; i < TILE_COUNT_X; ++i)
		{
			for (int j = 0; j < TILE_COUNT_Y; ++j)
			{
				if (_tiles[i][j].isPlayer == true)
				{
					_tiles[i][j].isPlayer = false;
				}

				if (i == isoX && j == isoY)
				{
					_tiles[i][j].isPlayer = true;
					_playerIdX = i;
					_playerIdY = j;

					//���� ��� inidata�� �����ϱ�
					//�α��εǾ��ִ� �÷��̾�Ȯ��
					if (_player->getIsPlayerMove() == false)
					{
						int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
						int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

						if (loginPlayer1 == (int)INFO_YES)
						{
							int playerX = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "������ǥX");
							int playerY = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "������ǥY");

							if (playerX != _playerIdX || playerY != _playerIdY)
							{
								char currentIsoX[256];
								char currentIsoY[256];
								INIDATA->addData("�÷��̾�1", "������ǥX", _itoa(_playerIdX, currentIsoX, 10));
								INIDATA->addData("�÷��̾�1", "������ǥY", _itoa(_playerIdY, currentIsoY, 10));
								INIDATA->iniSave("ĳ����");
							}
						}

						if (loginPlayer2 == (int)INFO_YES)
						{
							int playerX = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "������ǥX");
							int playerY = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "������ǥY");

							if (playerX != _playerIdX || playerY != _playerIdY)
							{
								char currentIsoX[256];
								char currentIsoY[256];
								INIDATA->addData("�÷��̾�2", "������ǥX", _itoa(_playerIdX, currentIsoX, 10));
								INIDATA->addData("�÷��̾�2", "������ǥY", _itoa(_playerIdY, currentIsoY, 10));
								INIDATA->iniSave("ĳ����");
							}
						}
					}

				}
			}
		}
	}
}

int tileMap::getCornerPlayerIndex(int isoX, int isoY)
{
	int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
	int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

	int right = left + CELL_WIDTH;
	int bottom = top + CELL_HEIGHT;

	//���콺 ��ǥ �ȿ� ���� ������ �������� 4�и� ����
	//left Top : 1, right Top : 2, left Bottom : 3, right Bottom : 4
	float dx = (_player->getPlayerCenterX() - left) / (float)CELL_WIDTH;
	float dy = (_player->getPlayerCenterY() - top) / (float)CELL_HEIGHT;

	if (dx < 0.5f && dy < 0.5f) return 1;
	if (dx >= 0.5f && dy < 0.5f) return 2;
	if (dx < 0.5f && dy >= 0.5f) return 3;
	if (dx >= 0.5f && dy >= 0.5f) return 4;

	return 0;
}

bool tileMap::isInPlayerRhombus(int corner, int isoX, int isoY)
{
	if (corner == 1)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		float dx = (float)(_player->getPlayerCenterX() - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(_player->getPlayerCenterY() - top) / (CELL_HEIGHT / 2.0f);
		if ((1.0f - dy) <= dx) return true;
		else return false;
	}
	else if (corner == 2)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		left += (CELL_WIDTH / 2.0f);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);

		float dx = (float)(_player->getPlayerCenterX() - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(_player->getPlayerCenterY() - top) / (CELL_HEIGHT / 2.0f);
		if (dy >= dx) return true;
		else return false;
	}
	else if (corner == 3)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);

		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);
		top += (CELL_HEIGHT / 2.0f);

		float dx = (float)(_player->getPlayerCenterX() - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(_player->getPlayerCenterY() - top) / (CELL_HEIGHT / 2.0f);
		if (dy <= dx) return true;
		else return false;
	}
	else if (corner == 4)
	{
		int left = INIT_X + (isoX * RADIUS_WIDTH) - (isoY * RADIUS_WIDTH);
		left += (CELL_WIDTH / 2.0f);
		int top = INIT_Y + (isoX * RADIUS_HEIGHT) + (isoY * RADIUS_HEIGHT);
		top += (CELL_HEIGHT / 2.0f);

		float dx = (float)(_player->getPlayerCenterX() - left) / (CELL_WIDTH / 2.0f);
		float dy = (float)(_player->getPlayerCenterY() - top) / (CELL_HEIGHT / 2.0f);
		if ((1.0f - dy) >= dx) return true;
		else return false;
	}

	return false;
}

void tileMap::moveTileSearch()
{
	for (int i = 0; i < TILE_COUNT_X; ++i)
	{
		for (int j = 0; j < TILE_COUNT_Y; ++j)
		{
			if (_tiles[i][j].isPlayer == false) continue;

			if (_tiles[i][j].isPlayer == true)
			{
				if (_player->getPlayerDirection() == DIR_SIX)
				{
					
				}
			}
		}
	}
}

void tileMap::load(string mapName)
{
	//�о����
	HANDLE file;
	DWORD read;

	file = CreateFile(mapName.c_str(), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y, &read, NULL);

	CloseHandle(file);
}

void tileMap::initAStar()
{
	_aStarCount = 0;
	_isAStarStart = false;
	setAStarTiles();
}

void tileMap::setAStarTiles()
{
	if (_vTotalList.size() != 0) return;
	if (_moveIdX == 0 && _moveIdY == 0) return;

	_startTile = new aStarTile;
	_startTile->init(_playerIdX, _playerIdY);
	_startTile->setAttribute("start");

	_endTile = new aStarTile;
	_endTile->init(_moveIdX, _moveIdY);
	_endTile->setAttribute("end");

	_currentTile = _startTile;

	for (int i = 0; i < TILE_COUNT_X; ++i)
	{
		for (int j = 0; j < TILE_COUNT_Y; ++j)
		{
			if (i == _startTile->getIdX() && j == _startTile->getIdY())
			{
				//_startTile->setColor(RGB(0, 255, 255));
				_vTotalList.push_back(_startTile);
				continue;
			}

			if (i == _endTile->getIdX() && j == _endTile->getIdY())
			{
				//_endTile->setColor(RGB(10, 120, 55));
				_vTotalList.push_back(_endTile);
				continue;
			}

			aStarTile* node = new aStarTile;

			if (_tiles[i][j].tileType == TYPE_UNMOVE)
			{
				node->init(i, j);
				node->setAttribute("typeUnMove");
				node->setIsOpen(false);
				//node->setColor(RGB(230, 140, 200));
				_vTotalList.push_back(node);
				continue;
			}

			node->init(i, j);

			_vTotalList.push_back(node);
		}
	}
}

//�� �� �ִ� �� ã�� ��� �Լ�
vector<aStarTile*> tileMap::addOpenList(aStarTile * currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			aStarTile* node = _vTotalList[(startX * TILE_COUNT_X) + startY + i + (j * TILE_COUNT_X)];

			//����ó��
			if (node->getIsOpen() == false) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "typeUnMove") continue;

			//���� Ÿ�� ��� �������ش�
			node->setParentNode(_currentTile);
			
			//�ֺ� Ÿ���� �����ϸ鼭 üũ�ߴ��� ������ �˼��ְ� ������ �Ұ� ����
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				//�̹� �ִ� �ִ�
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			if (node->getAttribute() != "end") //node->setColor(RGB(128, 64, 28));

			//�̹� üũ�� �ִ� �ǳʶڴ�
			if (addObj == false) continue;

			//���� �ִ� Ÿ���� ���¸���Ʈ ���Ϳ� ����ش�
			_vOpenList.push_back(node);
		}
	}

	return _vOpenList;
}

//�� �� �ִ� �Լ� ã���
void tileMap::pathFinder(aStarTile * currentTile)
{
	//���ϱ� ���� ������ ��κ���� �����صд�
	float tempTotalCost = 5000;
	aStarTile* tempTile = nullptr;

	//���¸���Ʈ ���� �ȿ���, ���� ���� ��θ� �̾Ƴ���
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		//H �� ����
		_vOpenList[i]->setCostToGoal(
			(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
				abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		//
		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		//Ÿ�� ���� ���̿� ���̰� ������ �밢�� �������� ����(47)�������� ��� �۳Ŀ� ���� �ڽ�Ʈ �ο�
		if (getDistance(center1.x, center1.y, center2.x, center2.y) < CELL_HEIGHT)
		{
			_vOpenList[i]->setCostFromStart(10);
		}

		else if (getDistance(center1.x, center1.y, center2.x, center2.y) >= CELL_HEIGHT &&
				 getDistance(center1.x, center1.y, center2.x, center2.y) < CELL_WIDTH)
		{
			_vOpenList[i]->setCostFromStart(12);
		}

		else if (getDistance(center1.x, center1.y, center2.x, center2.y) >= CELL_WIDTH)
		{
			_vOpenList[i]->setCostFromStart(16);
		}

		//_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > CELL_HEIGHT) ? 14 : 10);

		//�� ��κ�� == �� �� �ִ� Ÿ�� �� �߿��� �� ��� ����
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
			_vOpenList[i]->getCostFromStart());

		//�׷��� �̾Ƴ� �� ��κ����� ������ ��κ��� �����ؼ�,
		//���� ���� ���� ��� �̾Ƴ���
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		_vOpenList[i]->setIsOpen(false);
		if (addObj == false) continue;

		_vOpenList.push_back(tempTile);
	}

	if (tempTile->getAttribute() == "end")
	{
		while (_currentTile->getParentNode() != NULL)
		{
			//_currentTile->setColor(RGB(22, 14, 128));
			_currentTile = _currentTile->getParentNode();
		}

		//�ٷ� �տ� �̵��ҽ� ��. �ٷξտ�Ŭ���ؼ� Ŭ�����Ʈ�� 0�ϰ�� �ٷ� �������̵��ܰ�� �Ű��ش�
		if (_vCloseList.size() == 0)
		{
			_player->setIsMoveClick(true);
			_player->setIsPlayerMove(true);
			return;
		}

		return;
	}

	//�ִ� ��θ� ����
	_vCloseList.push_back(tempTile);

	//���� �ִܰ�ΰ� ���¸���Ʈ ��κ��� Ŀ������ ���� ��ã�� ���� �����ؾߵ�
	if (_vCloseList.size() > 100)
	{
		_player->setIsMoveClick(true);
		_vCloseList.clear();
		_vOpenList.clear();
		_vTotalList.clear();
		playerMovePoint(_tiles[_playerIdX][_playerIdY].left, _tiles[_playerIdX][_playerIdY].top);
		_isDontMoveMent = true;
		return;
	}

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		//�̾Ƴ� �ִܰ�δ� ���¸���Ʈ���� ����
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;
}

void tileMap::releaseAStar()
{
}

void tileMap::updateAStar()
{
	if (_moveIdX != 0 && _moveIdY != 0)
	{
		pathFinder(_currentTile);

		//_aStarCount++;
		//if (_aStarCount % 5 == 0)
		//{
		//	_aStarCount = 0;
		//}
	}
}

void tileMap::renderAStar()
{
	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		if (_vTotalList.size() == 0) break;

		//if (_vTotalList[i]->getAttribute() == "typeUnMove")
		//{
		//	HPEN myPen2 = CreatePen(PS_SOLID, 2, RGB(255, 50, 150));
		//	HPEN oldPen2 = (HPEN)SelectObject(getMemDC(), myPen2);

		//	_vTotalList[i]->render(_vTotalList[i]->getCenter().x, _vTotalList[i]->getCenter().y);

		//	DeleteObject(SelectObject(getMemDC(), oldPen2));
		//}

		//else if (_vTotalList[i] == _endTile)
		//{
		//	HPEN myPen3 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		//	HPEN oldPen3 = (HPEN)SelectObject(getMemDC(), myPen3);

		//	_vTotalList[i]->render(_vTotalList[i]->getCenter().x, _vTotalList[i]->getCenter().y);

		//	DeleteObject(SelectObject(getMemDC(), oldPen3));
		//}

		//else if (_vTotalList[i] == _startTile)
		//{
		//	HPEN myPen4 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		//	HPEN oldPen4 = (HPEN)SelectObject(getMemDC(), myPen4);

		//	_vTotalList[i]->render(_vTotalList[i]->getCenter().x, _vTotalList[i]->getCenter().y);

		//	DeleteObject(SelectObject(getMemDC(), oldPen4));
		//}
	}

	//for (int i = 0; i < _vCloseList.size(); ++i)
	//{
	//	if (_vCloseList.size() == 0) break;

	//	HPEN myPen = CreatePen(PS_SOLID, 2, RGB(200, 160, 50));
	//	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);

	//	_vCloseList[i]->render(_vCloseList[i]->getCenter().x, _vCloseList[i]->getCenter().y);

	//	DeleteObject(SelectObject(getMemDC(), oldPen));
	//}
}

void tileMap::writeInidata()
{
	if (_isWriteInidata == true) return;

	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");

	//�÷��̾� 1�� �α����������
	if (loginPlayer1 == (int)INFO_YES)
	{
		_playerInfo.name = INIDATA->loadDataString("ĳ����", "�÷��̾�1", "�̸�");
		_playerInfo.type = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "����");
		_playerInfo.level = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "����");
		_playerInfo.totalStamina = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "ü��") * 4 + INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�Ϸ�") +
			INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�ǰ�") + INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "���ǵ�");
		_playerInfo.attackPower = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�Ϸ�") + INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "���ݷ�") +
			INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "���ݷ�") + INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "���ݷ�");
		_playerInfo.defensePower = 1 + INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�ǰ�") + INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "����") +
			INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "����") + INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "����");
		_playerInfo.speedPower = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "���ǵ�") + INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "���߷�") +
			INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "���߷�") + INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "���߷�");
		_playerInfo.charming = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�ŷ�");
		_playerInfo.loginNum = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���Ƚ��");
		_playerInfo.attributeLand = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "���Ӽ�");
		_playerInfo.attributeWater = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "���Ӽ�");
		_playerInfo.attributeFire = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "ȭ�Ӽ�");
		_playerInfo.attributeWind = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "ǳ�Ӽ�");
		_playerInfo.currentStamina = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "����ü��");
		_playerInfo.magicalEnergy = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "���");
		_playerInfo.playerHealth = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�ǰ�");
		_playerInfo.playerStamina = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "ü��");
		_playerInfo.playerStrength = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�Ϸ�");
		_playerInfo.playerSpeed = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "���ǵ�");
		_playerInfo.currentEXP = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�������ġ");
		_playerInfo.nextEXP = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "��������ġ");

		string isDungeon = INIDATA->loadDataString("ĳ����", "�÷��̾�1", "�������");

		if (isDungeon == "����1")
		{
			_isDungeon = true;
		}

		if (_playerInfo.type == (int)INFO_BLUE)
		{
			_player->_player.playerCharacter = BLUE;
			_player->_playerImageName = "blue_stand_basic";
			_player->_player.img = IMAGEMANAGER->findImage("blue_stand_basic");
			_player->setPlayerImageMoveY(-30);
			_player->setPlayerRect(RectMakeCenter(_player->getPlayerCenterX() + _player->getPlayerImageMoveX(), _player->getPlayerCenterY() + _player->getPlayerImageMoveY(),
				_player->getPlayerImage()->getFrameWidth(), _player->getPlayerImage()->getFrameHeight()));
			_player->setPlayerImageCenterX(_player->getPlayerCenterX() + _player->getPlayerImageMoveX());
			_player->setPlayerImageCenterY(_player->getPlayerCenterY() + _player->getPlayerImageMoveY());
			_player->setPlayerDirection(DIR_SIX);
			_player->setPlayerCurrentFrameY((int)DIR_SIX);
		}

		if (_playerInfo.type == (int)INFO_RED)
		{
			_player->_player.playerCharacter = RED;
			_player->_playerImageName = "red_stand_basic";
			_player->_player.img = IMAGEMANAGER->findImage("red_stand_basic");
			_player->setPlayerImageMoveY(-23.5f);
			_player->setPlayerRect(RectMakeCenter(_player->getPlayerCenterX() + _player->getPlayerImageMoveX(), _player->getPlayerCenterY() + _player->getPlayerImageMoveY(),
				_player->getPlayerImage()->getFrameWidth(), _player->getPlayerImage()->getFrameHeight()));
			_player->setPlayerImageCenterX(_player->getPlayerCenterX() + _player->getPlayerImageMoveX());
			_player->setPlayerImageCenterY(_player->getPlayerCenterY() + _player->getPlayerImageMoveY());
			_player->setPlayerDirection(DIR_SIX);
			_player->setPlayerCurrentFrameY((int)DIR_SIX);
		}
	}

	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	//�÷��̾� 2�� �α����������
	if (loginPlayer2 == (int)INFO_YES)
	{
		_playerInfo.name = INIDATA->loadDataString("ĳ����", "�÷��̾�2", "�̸�");
		_playerInfo.type = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "����");
		_playerInfo.level = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "����");
		_playerInfo.totalStamina = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "ü��") * 4 + INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�Ϸ�") +
			INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�ǰ�") + INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "���ǵ�");
		_playerInfo.attackPower = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�Ϸ�") + INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "���ݷ�") +
			INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "���ݷ�") + INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "���ݷ�");
		_playerInfo.defensePower = 1 + INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�ǰ�") + INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "����") +
			INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "����") + INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "����");
		_playerInfo.speedPower = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "���ǵ�") + INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "���߷�") +
			INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "���߷�") + INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "���߷�");
		_playerInfo.charming = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�ŷ�");
		_playerInfo.loginNum = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���Ƚ��");
		_playerInfo.attributeLand = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "���Ӽ�");
		_playerInfo.attributeWater = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "���Ӽ�");
		_playerInfo.attributeFire = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "ȭ�Ӽ�");
		_playerInfo.attributeWind = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "ǳ�Ӽ�");
		_playerInfo.currentStamina = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "����ü��");
		_playerInfo.magicalEnergy = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "���");
		_playerInfo.playerHealth = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�ǰ�");
		_playerInfo.playerStamina = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "ü��");
		_playerInfo.playerStrength = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�Ϸ�");
		_playerInfo.playerSpeed = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "���ǵ�");
		_playerInfo.currentEXP = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�������ġ");
		_playerInfo.nextEXP = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "��������ġ");

		string isDungeon = INIDATA->loadDataString("ĳ����", "�÷��̾�2", "�������");

		if (isDungeon == "����1")
		{
			_isDungeon = true;
		}

		if (_playerInfo.type == (int)INFO_BLUE)
		{
			_player->_player.playerCharacter = BLUE;
			_player->_playerImageName = "blue_stand_basic";
			_player->_player.img = IMAGEMANAGER->findImage("blue_stand_basic");
			_player->setPlayerImageMoveY(-30);
			_player->setPlayerRect(RectMakeCenter(_player->getPlayerCenterX() + _player->getPlayerImageMoveX(), _player->getPlayerCenterY() + _player->getPlayerImageMoveY(),
				_player->getPlayerImage()->getFrameWidth(), _player->getPlayerImage()->getFrameHeight()));
			_player->setPlayerImageCenterX(_player->getPlayerCenterX() + _player->getPlayerImageMoveX());
			_player->setPlayerImageCenterY(_player->getPlayerCenterY() + _player->getPlayerImageMoveY());
			_player->setPlayerDirection(DIR_SIX);
			_player->setPlayerCurrentFrameY((int)DIR_SIX);
		}

		if (_playerInfo.type == (int)INFO_RED)
		{
			_player->_player.playerCharacter = RED;
			_player->_playerImageName = "red_stand_basic";
			_player->_player.img = IMAGEMANAGER->findImage("red_stand_basic");
			_player->setPlayerImageMoveY(-23.5f);
			_player->setPlayerRect(RectMakeCenter(_player->getPlayerCenterX() + _player->getPlayerImageMoveX(), _player->getPlayerCenterY() + _player->getPlayerImageMoveY(),
				_player->getPlayerImage()->getFrameWidth(), _player->getPlayerImage()->getFrameHeight()));
			_player->setPlayerImageCenterX(_player->getPlayerCenterX() + _player->getPlayerImageMoveX());
			_player->setPlayerImageCenterY(_player->getPlayerCenterY() + _player->getPlayerImageMoveY());
			_player->setPlayerDirection(DIR_SIX);
			_player->setPlayerCurrentFrameY((int)DIR_SIX);
		}
	}


	_isWriteInidata = true;
}

void tileMap::whorfSpotSearch()
{
	//�α��εǾ��ִ� �÷��̾�Ȯ��
	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	searchIsoX[0] = _playerIdX - 1;
	searchIsoY[0] = _playerIdY;
	searchIsoX[1] = _playerIdX;
	searchIsoY[1] = _playerIdY - 1;
	searchIsoX[2] = _playerIdX + 1;
	searchIsoY[2] = _playerIdY;
	searchIsoX[3] = _playerIdX - 1;
	searchIsoY[3] = _playerIdY + 1;

	for (int i = 0; i < 4; ++i)
	{
		//�����ΰ��� ������ ��������
		if (_tiles[searchIsoX[i]][searchIsoY[i]].tileType == TYPE_WHORF_VILLAGE)
		{
			if (loginPlayer1 == (int)INFO_YES)
			{
				string currentPlace = INIDATA->loadDataString("ĳ����", "�÷��̾�1", "�������");

				//�̵� �� ��Ұ� ����1�ϰ��
				if (currentPlace == "����1")
				{
					INIDATA->addData("�÷��̾�1", "�������", "����1");
					char convertPlace[256];
					INIDATA->addData("�÷��̾�1", "����̵�", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("ĳ����");
					RENDERMANAGER->deleteAll();
					SOUNDMANAGER->play("village_bg", 0.4f);
					SCENEMANAGER->changeScene("����");
					break;
				}

				if (currentPlace == "�����ۻ���")
				{
					INIDATA->addData("�÷��̾�1", "�������", "�����ۻ���");
					char convertPlace[256];
					INIDATA->addData("�÷��̾�1", "����̵�", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("ĳ����");
					RENDERMANAGER->deleteAll();
					SOUNDMANAGER->play("village_bg", 0.4f);
					SCENEMANAGER->changeScene("����");
					break;
				}
			}

			if (loginPlayer2 == (int)INFO_YES)
			{
				string currentPlace = INIDATA->loadDataString("ĳ����", "�÷��̾�2", "�������");

				//�̵� �� ��Ұ� ����1�ϰ��
				if (currentPlace == "����1")
				{
					INIDATA->addData("�÷��̾�2", "�������", "����1");
					char convertPlace[256];
					INIDATA->addData("�÷��̾�2", "����̵�", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("ĳ����");
					RENDERMANAGER->deleteAll();
					SCENEMANAGER->changeScene("����");
					break;
				}

				if (currentPlace == "�����ۻ���")
				{
					INIDATA->addData("�÷��̾�2", "�������", "�����ۻ���");
					char convertPlace[256];
					INIDATA->addData("�÷��̾�2", "����̵�", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("ĳ����");
					RENDERMANAGER->deleteAll();
					SCENEMANAGER->changeScene("����");
					break;
				}
			}
		}

		//����1�� ���� ������ ��������
		if (_tiles[searchIsoX[i]][searchIsoY[i]].tileType == TYPE_WHORF_DUNGEON1)
		{
			if (loginPlayer1 == (int)INFO_YES)
			{
				string currentPlace = INIDATA->loadDataString("ĳ����", "�÷��̾�1", "�������");

				//�̵� �� ��Ұ� �����ϰ��
				if (currentPlace == "����")
				{
					INIDATA->addData("�÷��̾�1", "�������", "����");
					char convertPlace[256];
					INIDATA->addData("�÷��̾�1", "����̵�", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("ĳ����");
					RENDERMANAGER->deleteAll();
					SOUNDMANAGER->play("dungeon1_bg", 0.4f);
					SCENEMANAGER->changeScene("����1");
					break;
				}
			}

			if (loginPlayer2 == (int)INFO_YES)
			{
				string currentPlace = INIDATA->loadDataString("ĳ����", "�÷��̾�2", "�������");

				//�̵� �� ��Ұ� �����ϰ��
				if (currentPlace == "����")
				{
					INIDATA->addData("�÷��̾�2", "�������", "����");
					char convertPlace[256];
					INIDATA->addData("�÷��̾�2", "����̵�", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("ĳ����");
					RENDERMANAGER->deleteAll();
					SOUNDMANAGER->play("dungeon1_bg", 0.4f);
					SCENEMANAGER->changeScene("����1");
					break;
				}
			}
		}

		//�����ۻ������� ���� ������ ��������
		if (_tiles[searchIsoX[i]][searchIsoY[i]].tileType == TYPE_WHORF_ITEMSHOP)
		{
			if (loginPlayer1 == (int)INFO_YES)
			{
				string currentPlace = INIDATA->loadDataString("ĳ����", "�÷��̾�1", "�������");

				//�̵� �� ��Ұ� �����ϰ��
				if (currentPlace == "����")
				{
					INIDATA->addData("�÷��̾�1", "�������", "����");
					char convertPlace[256];
					INIDATA->addData("�÷��̾�1", "����̵�", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("ĳ����");
					RENDERMANAGER->deleteAll();
					SCENEMANAGER->changeScene("�����ۻ���");
					break;
				}
			}

			if (loginPlayer2 == (int)INFO_YES)
			{
				string currentPlace = INIDATA->loadDataString("ĳ����", "�÷��̾�2", "�������");

				//�̵� �� ��Ұ� �����ϰ��
				if (currentPlace == "����")
				{
					INIDATA->addData("�÷��̾�2", "�������", "����");
					char convertPlace[256];
					INIDATA->addData("�÷��̾�2", "����̵�", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("ĳ����");
					RENDERMANAGER->deleteAll();
					SCENEMANAGER->changeScene("�����ۻ���");
					break;
				}
			}
		}
	}
}

void tileMap::NPCSpotSearch()
{
	if (_isAvailableClickNPC == true) return;

	//��ǥ���� �����ϱ�
	for (int i = 0; i < 16; ++i)
	{
		if (i >= 0 && i <= 3)
		{
			searchNPCIsoX[i] = _playerIdX - 1 - i;
			searchNPCIsoY[i] = _playerIdY;
		}

		if (i >= 4 && i <= 7)
		{
			searchNPCIsoX[i] = _playerIdX;
			searchNPCIsoY[i] = _playerIdY - 1 - (i - 4);
		}

		if (i >= 8 && i <= 11)
		{
			searchNPCIsoX[i] = _playerIdX + 1 + (i - 8);
			searchNPCIsoY[i] = _playerIdY;
		}

		if (i >= 12 && i <= 15)
		{
			searchNPCIsoX[i] = _playerIdX;
			searchNPCIsoY[i] = _playerIdY + 1 + (i - 12);
		}
	}

	for (int i = 0; i < 16; ++i)
	{
		//NPC�� ����������
		if (_tiles[searchNPCIsoX[i]][searchNPCIsoY[i]].obj == OBJ_NPC)
		{
			_isAvailableClickNPC = true;
		}
	}
}

void tileMap::clickNPC()
{
	if (_isAvailableClickNPC == false) return;


	//ī�޶� ���� �̵��� ��ŭ + ����� �׿� �´� �ε����� ���� �� �ִ�
	float cellX = (float)(_ptMouse.x - INIT_X + _cameraBufferX);
	if (cellX < 0)
	{
		cellX = (cellX - CELL_WIDTH) / CELL_WIDTH;
	}
	else
	{
		cellX = (cellX) / (float)CELL_WIDTH;
	}

	int cellY = (abs)((_ptMouse.y - INIT_Y + _cameraBufferY)) / CELL_HEIGHT;
	cellY = (_ptMouse.y < INIT_Y) ? cellY * -1 : cellY;

	int isoX = (int)cellX + (int)cellY;
	int isoY = (int)cellY - (int)cellX;

	if (isoX >= 0 && isoX < TILE_COUNT_X &&
		isoY >= 0 && isoY < TILE_COUNT_Y)
	{
		//1�и� -> [x - 1][y]
		//2�и� -> [x][y - 1]
		//3�и� -> [x][y + 1]
		//4�и� -> [x + 1][y]
		int corner = getCornerIndex(isoX, isoY);
		if (isInRhombus(corner, isoX, isoY))
		{
			corner = 0;
		}

		_corner = corner;
		_isoX = isoX;
		_isoY = isoY;

		switch (corner)
		{
		case 1:
			isoX = isoX - 1;
			break;
		case 2:
			isoY = isoY - 1;
			break;
		case 3:
			isoY = isoY + 1;
			break;
		case 4:
			isoX = isoX + 1;
			break;
		}
		//	if (i == isoX && j == isoY) �߰��ض� ���ǿ�
		for (int i = 0; i < TILE_COUNT_X; ++i)
		{
			for (int j = 0; j < TILE_COUNT_Y; ++j)
			{
				if (i == isoX && j == isoY)
				{
					//Ŭ���� Ÿ�Ͽ� �� ��������� �������
					if (_tiles[i][j].obj == OBJ_NPC &&
						_tiles[i][j].objFrameX == (int)NPC_ARMOR_SALESMAN &&
						_tiles[i][j].objFrameY == 0)
					{
						_isClickArmorNPC = true;
						InputHandle();
						break;
					}

					//Ŭ���� Ÿ�Ͽ� �� ��������� �������
					if (_tiles[i][j].obj == OBJ_NPC &&
						_tiles[i][j].objFrameX == (int)NPC_WEAPON_SALESMAN &&
						_tiles[i][j].objFrameY == 0)
					{
						_isClickWeaponNPC = true;
						InputHandle();
						break;
					}
				}
			}
		}
	}
}

void tileMap::dungeonToBattle()
{
	if (_isDungeon == false) return;

	//�÷��̾ ������ ��� Ȯ���� ������
	if (_player->getIsPlayerMove() == true)
	{
		int isBattle = false;

		while (true)
		{
			isBattle = RND->getFromIntTo(0, 300);
			break;
		}

		if (isBattle != 1) return;

		if (isBattle == 1)
		{
			int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
			int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");
			//��1 ��ǥ����
			if (loginPlayer1 == (int)INFO_YES)
			{
					char currentIsoX[256];
					char currentIsoY[256];
					INIDATA->addData("�÷��̾�1", "������ǥX", _itoa(_playerIdX, currentIsoX, 10));
					INIDATA->addData("�÷��̾�1", "������ǥY", _itoa(_playerIdY, currentIsoY, 10));
					INIDATA->iniSave("ĳ����");
			}
			//��2 ��ǥ����
			if (loginPlayer2 == (int)INFO_YES)
			{
					char currentIsoX[256];
					char currentIsoY[256];
					INIDATA->addData("�÷��̾�2", "������ǥX", _itoa(_playerIdX, currentIsoX, 10));
					INIDATA->addData("�÷��̾�2", "������ǥY", _itoa(_playerIdY, currentIsoY, 10));
					INIDATA->iniSave("ĳ����");
			}
			RENDERMANAGER->deleteAll();
			SOUNDMANAGER->play("battle_convert", 0.4f);
			SCENEMANAGER->changeScene("��Ʋ1");
		}
	}
}
