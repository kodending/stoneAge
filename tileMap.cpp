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

	//움직일때는 NPC클릭 불가능
	if (_player->getIsPlayerMove() == true &&
		_isAvailableClickNPC == true)
	{
		_isAvailableClickNPC = false;
	}

	dungeonToBattle();
}

void tileMap::render()
{
	//타일렌더해주기
	for (int i = 0; i < TILE_COUNT_X; ++i)
	{
		for (int j = 0; j < TILE_COUNT_Y; ++j)
		{
			//카메라 안에서만 렌더되게 하기위한 작업
			RECT temp;
			RECT cameraRect = RectMake(CAMERAMANAGER->getCameraLEFT(), CAMERAMANAGER->getCameraTOP(), CAMERAX, CAMERAY);
			RECT tileRect = RectMake(_tiles[i][j].left, _tiles[i][j].top, 64, 47);
			if (!IntersectRect(&temp, &cameraRect, &tileRect)) continue;

			IMAGEMANAGER->frameRender("tile", getMemDC(), _tiles[i][j].left, _tiles[i][j].top,
				_tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
		}
	}

	//오브젝트렌더해주기(z-order용)
	RENDERMANAGER->render(getMemDC(), _player->getPlayerImageName().c_str());

	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		//워프타일 렌더해주기
		for (int i = 0; i < TILE_COUNT_X; ++i)
		{
			for (int j = 0; j < TILE_COUNT_Y; ++j)
			{
				//이동가능 타일이면 그리지않게끔 예외처리
				if (_tiles[i][j].tileType == TYPE_MOVE) continue;

				//카메라 안에서만 렌더되게 하기위한 작업
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
		//플레이어 현재 있는 타일 렌더해주기
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

		//플레이어 전에 위치했던 타일 렌더해주기
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

	//디버그용
	//SetTextColor(getMemDC(), RGB(255, 0, 0));
	//sprintf(str, "토탈 : %d \n 오픈 : %d \n 클로즈 : %d \ n _moveIdX : %d,  _moveIdY : %d",
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
			0, 0, 0, 0, TEXT("HY목각파임B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(30, 80, 120));
		sprintf(str, "촌장님이 울타리 밖은 위험하다고 했어");
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
				//좌표정보 불러오기 (나중에 주석처리해주세용)
				SetTextColor(getMemDC(), RGB(255, 0, 0));
				sprintf(str, "(%d, %d)", i, j);
				TextOut(getMemDC(), centerX, centerY, str, strlen(str));
			}

			//타일 레프트, 탑 좌표 담아버리기
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

	//마우스 좌표 안에 있을 비율을 기준으로 4분면 구분
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

	//선택버튼위에 안올라가져있을때만 false해줘서 타일 선택되게끔
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
		//1분면 -> [x - 1][y]
		//2분면 -> [x][y - 1]
		//3분면 -> [x][y + 1]
		//4분면 -> [x + 1][y]
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

		//마우스커서 위치 올리기위한
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
	//1줄 ~ 6줄
	if (frameX >= 0 && frameX <= 13 &&
		frameY >= 0 && frameY <= 5)
	{
		return TR_DESERT;
	}

	//7줄
	if (frameX >= 0 && frameX <= 13 &&
		frameY == 6)
	{
		return TR_WATER;
	}

	//8줄
	if (frameX >= 0 && frameX <= 13 &&
		frameY == 7)
	{
		return TR_GRASS;
	}

	//9~11줄
	if (frameX >= 0 && frameX <= 13 &&
		frameY >= 8 && frameY <= 10)
	{
		return TR_LAVAREGION;
	}

	//12줄
	if (frameX >= 0 && frameX <= 13 &&
		frameY == 11)
	{
		return TR_DIRT;
	}

	//13 ~ 14줄
	if (frameX >= 0 && frameX <= 13 &&
		frameY >= 12 && frameY <= 13)
	{
		return TR_GRASS;
	}

	//15줄
	if (frameX >= 0 && frameX <= 13 &&
		frameY == 14)
	{
		return TR_LAVAREGION;
	}

	//16~17줄
	if (frameX >= 0 && frameX <= 13 &&
		frameY >= 15 && frameY <= 16)
	{
		return TR_LAVA;
	}

	//18줄
	if (frameX >= 0 && frameX <= 13 &&
		frameY == 17)
	{
		return TR_GRASS;
	}

	//19줄
	if (frameX >= 0 && frameX <= 13 &&
		frameY == 18)
	{
		return TR_LAVAREGION;
	}

	//20 ~ 21줄
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

			//타일 레프트, 탑 좌표 담아버리기
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
	if (_vCloseList.size() == 0) return; //일단 추가
	if (_closeListCount == _vCloseList.size()) return;

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeedX = _player->getPlayerSpeedX();
	float moveSpeedY = _player->getPlayerSpeedY();

	//플레이어한테 움직이고 있다고 알려주는 장치
	_player->setIsPlayerMove(true);

	//플레이어 센터 위치가 마우스포인트 찍은 x좌표가 작을경우 오른쪽으로 움직여야함
	if (_player->getPlayerCenterX() < _vCloseList[_closeListCount]->getCenter().x)
	{
		//원래비교는 _player->getPlayerMoveEndX, Y랑 비교했었음
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

	//플레이어 센터 위치가 마우스포인트 찍은 x좌표가 클경우 왼쪽으로 움직여야함
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

	//플레이어 센터 위치가 마우스포인트 찍은 Y좌표가 작을경우 아래쪽으로 움직여야함
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

	//플레이어 센터 위치가 마우스포인트 찍은 Y좌표가 클경우 위쪽으로 움직여야함
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

	//플레이어 움직임 방향에 따라 이동방향 설정하기

	//6시방향인경우
	if (_player->getPlayerCenterX() == _prePlayerCenterX &&
		_player->getPlayerCenterY() > _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_SIX);
		return;
	}

	//7시방향인경우
	if (_player->getPlayerCenterX() < _prePlayerCenterX &&
		_player->getPlayerCenterY() > _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_SEVEN);
		return;
	}

	//9시방향인경우
	if (_player->getPlayerCenterX() < _prePlayerCenterX &&
		_player->getPlayerCenterY() == _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_NINE);
		return;
	}

	//11시방향인경우
	if (_player->getPlayerCenterX() < _prePlayerCenterX &&
		_player->getPlayerCenterY() < _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_ELEVEN);
		return;
	}

	//12시방향인경우
	if (_player->getPlayerCenterX() == _prePlayerCenterX &&
		_player->getPlayerCenterY() < _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_TWELVE);
		return;
	}

	//1시방향인경우
	if (_player->getPlayerCenterX() > _prePlayerCenterX &&
		_player->getPlayerCenterY() < _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_ONE);
		return;
	}

	//3시방향인경우
	if (_player->getPlayerCenterX() > _prePlayerCenterX &&
		_player->getPlayerCenterY() == _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_THREE);
		return;
	}

	//5시방향인경우
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

	//플레이어 센터 위치가 마우스포인트 찍은 x좌표가 작을경우 오른쪽으로 움직여야함
	if (_player->getPlayerCenterX() < _player->getPlayerMoveEndX())
	{
		//원래비교는 _player->getPlayerMoveEndX, Y랑 비교했었음
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

	//플레이어 센터 위치가 마우스포인트 찍은 x좌표가 클경우 왼쪽으로 움직여야함
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

	//플레이어 센터 위치가 마우스포인트 찍은 Y좌표가 작을경우 아래쪽으로 움직여야함
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

	//플레이어 센터 위치가 마우스포인트 찍은 Y좌표가 클경우 위쪽으로 움직여야함
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

	//최종목적지에 도착했으면~
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


	//플레이어 움직임 방향에 따라 이동방향 설정하기

	//6시방향인경우
	if (_player->getPlayerCenterX() == _prePlayerCenterX &&
		_player->getPlayerCenterY() > _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_SIX);
		return;
	}

	//7시방향인경우
	if (_player->getPlayerCenterX() < _prePlayerCenterX &&
		_player->getPlayerCenterY() > _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_SEVEN);
		return;
	}

	//9시방향인경우
	if (_player->getPlayerCenterX() < _prePlayerCenterX &&
		_player->getPlayerCenterY() == _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_NINE);
		return;
	}

	//11시방향인경우
	if (_player->getPlayerCenterX() < _prePlayerCenterX &&
		_player->getPlayerCenterY() < _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_ELEVEN);
		return;
	}

	//12시방향인경우
	if (_player->getPlayerCenterX() == _prePlayerCenterX &&
		_player->getPlayerCenterY() < _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_TWELVE);
		return;
	}

	//1시방향인경우
	if (_player->getPlayerCenterX() > _prePlayerCenterX &&
		_player->getPlayerCenterY() < _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_ONE);
		return;
	}

	//3시방향인경우
	if (_player->getPlayerCenterX() > _prePlayerCenterX &&
		_player->getPlayerCenterY() == _prePlayerCenterY)
	{
		_prePlayerCenterX = _player->getPlayerCenterX();
		_prePlayerCenterY = _player->getPlayerCenterY();

		_player->setPlayerDirection(DIR_THREE);
		return;
	}

	//5시방향인경우
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
		//카메라에 맞춰 이동한 만큼 + 해줘야 그에 맞는 인덱스로 찍을 수 있다
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
			//1분면 -> [x - 1][y]
			//2분면 -> [x][y - 1]
			//3분면 -> [x][y + 1]
			//4분면 -> [x + 1][y]
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
		//카메라에 맞춰 이동한 만큼 + 해줘야 그에 맞는 인덱스로 찍을 수 있다
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
			//1분면 -> [x - 1][y]
			//2분면 -> [x][y - 1]
			//3분면 -> [x][y + 1]
			//4분면 -> [x + 1][y]
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

		//여기에 함수 넣어라~

		for (int i = 0; i < TILE_COUNT_X; ++i)
		{
			for (int j = 0; j < TILE_COUNT_Y; ++j)
			{
				if (_tiles[i][j].isPlayer == false) continue;
				if (i == isoX && j == isoY) continue;

				if (_tiles[i][j].isPlayer == true)
				{
					//6시방향일때 프레임값 바꾸기
					if (i < isoX && j < isoY)
					{
						_player->setPlayerDirection(DIR_SIX);
						break;
					}

					//7시 방향일때 프레임값 바꾸기
					else if (i == isoX && j < isoY)
					{
						_player->setPlayerDirection(DIR_SEVEN);
						break;
					}

					//9시 방향일때 프레임값 바꾸기
					else if (i > isoX && j < isoY)
					{
						_player->setPlayerDirection(DIR_NINE);
						break;
					}

					//11시 방향일때 프레임값 바꾸기
					else if (i > isoX && j == isoY)
					{
						_player->setPlayerDirection(DIR_ELEVEN);
						break;
					}

					//12시 방향일때 프레임값 바꾸기
					else if (i > isoX && j > isoY)
					{
						_player->setPlayerDirection(DIR_TWELVE);
						break;
					}

					//1시 방향일때 프레임값 바꾸기
					else if (i == isoX && j > isoY)
					{
						_player->setPlayerDirection(DIR_ONE);
						break;
					}

					//3시 방향일때 프레임값 바꾸기
					else if (i < isoX && j > isoY)
					{
						_player->setPlayerDirection(DIR_THREE);
						break;
					}

					//5시 방향일때 프레임값 바꾸기
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
		//1분면 -> [x - 1][y]
		//2분면 -> [x][y - 1]
		//3분면 -> [x][y + 1]
		//4분면 -> [x + 1][y]
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

		//현재 플레이어 위치를 확인하기 위한
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

					//현재 장소 inidata에 저장하기
					//로그인되어있는 플레이어확인
					if (_player->getIsPlayerMove() == false)
					{
						int loginPlayer1 = INIDATA->loadDataInterger("캐릭터", "플레이어1", "로그인");
						int loginPlayer2 = INIDATA->loadDataInterger("캐릭터", "플레이어2", "로그인");

						if (loginPlayer1 == (int)INFO_YES)
						{
							int playerX = INIDATA->loadDataInterger("캐릭터", "플레이어1", "현재좌표X");
							int playerY = INIDATA->loadDataInterger("캐릭터", "플레이어1", "현재좌표Y");

							if (playerX != _playerIdX || playerY != _playerIdY)
							{
								char currentIsoX[256];
								char currentIsoY[256];
								INIDATA->addData("플레이어1", "현재좌표X", _itoa(_playerIdX, currentIsoX, 10));
								INIDATA->addData("플레이어1", "현재좌표Y", _itoa(_playerIdY, currentIsoY, 10));
								INIDATA->iniSave("캐릭터");
							}
						}

						if (loginPlayer2 == (int)INFO_YES)
						{
							int playerX = INIDATA->loadDataInterger("캐릭터", "플레이어2", "현재좌표X");
							int playerY = INIDATA->loadDataInterger("캐릭터", "플레이어2", "현재좌표Y");

							if (playerX != _playerIdX || playerY != _playerIdY)
							{
								char currentIsoX[256];
								char currentIsoY[256];
								INIDATA->addData("플레이어2", "현재좌표X", _itoa(_playerIdX, currentIsoX, 10));
								INIDATA->addData("플레이어2", "현재좌표Y", _itoa(_playerIdY, currentIsoY, 10));
								INIDATA->iniSave("캐릭터");
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

	//마우스 좌표 안에 있을 비율을 기준으로 4분면 구분
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
	//읽어오기
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

//갈 수 있는 길 찾아 담는 함수
vector<aStarTile*> tileMap::addOpenList(aStarTile * currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			aStarTile* node = _vTotalList[(startX * TILE_COUNT_X) + startY + i + (j * TILE_COUNT_X)];

			//예외처리
			if (node->getIsOpen() == false) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "typeUnMove") continue;

			//현재 타일 계속 갱신해준다
			node->setParentNode(_currentTile);
			
			//주변 타일을 검출하면서 체크했는지 유무를 알수있게 임의의 불값 선언
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				//이미 있는 애다
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			if (node->getAttribute() != "end") //node->setColor(RGB(128, 64, 28));

			//이미 체크된 애는 건너뛴다
			if (addObj == false) continue;

			//갈수 있는 타일은 오픈리스트 벡터에 담아준다
			_vOpenList.push_back(node);
		}
	}

	return _vOpenList;
}

//갈 수 있는 함수 찾기용
void tileMap::pathFinder(aStarTile * currentTile)
{
	//비교하기 쉽게 임의의 경로비용을 설정해둔다
	float tempTotalCost = 5000;
	aStarTile* tempTile = nullptr;

	//오픈리스트 벡터 안에서, 가장 빠른 경로를 뽑아낸다
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		//H 값 연산
		_vOpenList[i]->setCostToGoal(
			(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
				abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		//
		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		//타일 중점 사이에 길이가 마름모 대각선 길이포함 세로(47)기준으로 기냐 작냐에 따른 코스트 부여
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

		//총 경로비용 == 갈 수 있는 타일 들 중에서 총 경로 비용들
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
			_vOpenList[i]->getCostFromStart());

		//그렇게 뽑아낸 총 경로비용들을 임의의 경로비용과 연산해서,
		//가장 작은 값을 계속 뽑아낸다
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

		//바로 앞에 이동할시 즉. 바로앞에클릭해서 클로즈리스트가 0일경우 바로 마지막이동단계로 옮겨준다
		if (_vCloseList.size() == 0)
		{
			_player->setIsMoveClick(true);
			_player->setIsPlayerMove(true);
			return;
		}

		return;
	}

	//최단 경로를 뽑자
	_vCloseList.push_back(tempTile);

	//만약 최단경로가 오픈리스트 경로보다 커질경우는 길을 못찾는 경우라 종료해야됨
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
		//뽑아낸 최단경로는 오픈리스트에서 삭제
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

	int loginPlayer1 = INIDATA->loadDataInterger("캐릭터", "플레이어1", "로그인");

	//플레이어 1이 로그인했을경우
	if (loginPlayer1 == (int)INFO_YES)
	{
		_playerInfo.name = INIDATA->loadDataString("캐릭터", "플레이어1", "이름");
		_playerInfo.type = INIDATA->loadDataInterger("캐릭터", "플레이어1", "종류");
		_playerInfo.level = INIDATA->loadDataInterger("캐릭터", "플레이어1", "레벨");
		_playerInfo.totalStamina = INIDATA->loadDataInterger("캐릭터", "플레이어1", "체력") * 4 + INIDATA->loadDataInterger("캐릭터", "플레이어1", "완력") +
			INIDATA->loadDataInterger("캐릭터", "플레이어1", "건강") + INIDATA->loadDataInterger("캐릭터", "플레이어1", "스피드");
		_playerInfo.attackPower = INIDATA->loadDataInterger("캐릭터", "플레이어1", "완력") + INIDATA->loadDataInterger("플레이어1_아이템", "무기착용", "공격력") +
			INIDATA->loadDataInterger("플레이어1_아이템", "갑옷착용", "공격력") + INIDATA->loadDataInterger("플레이어1_아이템", "투구착용", "공격력");
		_playerInfo.defensePower = 1 + INIDATA->loadDataInterger("캐릭터", "플레이어1", "건강") + INIDATA->loadDataInterger("플레이어1_아이템", "무기착용", "방어력") +
			INIDATA->loadDataInterger("플레이어1_아이템", "갑옷착용", "방어력") + INIDATA->loadDataInterger("플레이어1_아이템", "투구착용", "방어력");
		_playerInfo.speedPower = INIDATA->loadDataInterger("캐릭터", "플레이어1", "스피드") + INIDATA->loadDataInterger("플레이어1_아이템", "무기착용", "순발력") +
			INIDATA->loadDataInterger("플레이어1_아이템", "갑옷착용", "순발력") + INIDATA->loadDataInterger("플레이어1_아이템", "투구착용", "순발력");
		_playerInfo.charming = INIDATA->loadDataInterger("캐릭터", "플레이어1", "매력");
		_playerInfo.loginNum = INIDATA->loadDataInterger("캐릭터", "플레이어1", "로그인횟수");
		_playerInfo.attributeLand = INIDATA->loadDataInterger("캐릭터", "플레이어1", "지속성");
		_playerInfo.attributeWater = INIDATA->loadDataInterger("캐릭터", "플레이어1", "수속성");
		_playerInfo.attributeFire = INIDATA->loadDataInterger("캐릭터", "플레이어1", "화속성");
		_playerInfo.attributeWind = INIDATA->loadDataInterger("캐릭터", "플레이어1", "풍속성");
		_playerInfo.currentStamina = INIDATA->loadDataInterger("캐릭터", "플레이어1", "현재체력");
		_playerInfo.magicalEnergy = INIDATA->loadDataInterger("캐릭터", "플레이어1", "기력");
		_playerInfo.playerHealth = INIDATA->loadDataInterger("캐릭터", "플레이어1", "건강");
		_playerInfo.playerStamina = INIDATA->loadDataInterger("캐릭터", "플레이어1", "체력");
		_playerInfo.playerStrength = INIDATA->loadDataInterger("캐릭터", "플레이어1", "완력");
		_playerInfo.playerSpeed = INIDATA->loadDataInterger("캐릭터", "플레이어1", "스피드");
		_playerInfo.currentEXP = INIDATA->loadDataInterger("캐릭터", "플레이어1", "현재경험치");
		_playerInfo.nextEXP = INIDATA->loadDataInterger("캐릭터", "플레이어1", "다음경험치");

		string isDungeon = INIDATA->loadDataString("캐릭터", "플레이어1", "현재장소");

		if (isDungeon == "던전1")
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

	int loginPlayer2 = INIDATA->loadDataInterger("캐릭터", "플레이어2", "로그인");

	//플레이어 2이 로그인했을경우
	if (loginPlayer2 == (int)INFO_YES)
	{
		_playerInfo.name = INIDATA->loadDataString("캐릭터", "플레이어2", "이름");
		_playerInfo.type = INIDATA->loadDataInterger("캐릭터", "플레이어2", "종류");
		_playerInfo.level = INIDATA->loadDataInterger("캐릭터", "플레이어2", "레벨");
		_playerInfo.totalStamina = INIDATA->loadDataInterger("캐릭터", "플레이어2", "체력") * 4 + INIDATA->loadDataInterger("캐릭터", "플레이어2", "완력") +
			INIDATA->loadDataInterger("캐릭터", "플레이어2", "건강") + INIDATA->loadDataInterger("캐릭터", "플레이어2", "스피드");
		_playerInfo.attackPower = INIDATA->loadDataInterger("캐릭터", "플레이어2", "완력") + INIDATA->loadDataInterger("플레이어2_아이템", "무기착용", "공격력") +
			INIDATA->loadDataInterger("플레이어2_아이템", "갑옷착용", "공격력") + INIDATA->loadDataInterger("플레이어2_아이템", "투구착용", "공격력");
		_playerInfo.defensePower = 1 + INIDATA->loadDataInterger("캐릭터", "플레이어2", "건강") + INIDATA->loadDataInterger("플레이어2_아이템", "무기착용", "방어력") +
			INIDATA->loadDataInterger("플레이어2_아이템", "갑옷착용", "방어력") + INIDATA->loadDataInterger("플레이어2_아이템", "투구착용", "방어력");
		_playerInfo.speedPower = INIDATA->loadDataInterger("캐릭터", "플레이어2", "스피드") + INIDATA->loadDataInterger("플레이어2_아이템", "무기착용", "순발력") +
			INIDATA->loadDataInterger("플레이어2_아이템", "갑옷착용", "순발력") + INIDATA->loadDataInterger("플레이어2_아이템", "투구착용", "순발력");
		_playerInfo.charming = INIDATA->loadDataInterger("캐릭터", "플레이어2", "매력");
		_playerInfo.loginNum = INIDATA->loadDataInterger("캐릭터", "플레이어2", "로그인횟수");
		_playerInfo.attributeLand = INIDATA->loadDataInterger("캐릭터", "플레이어2", "지속성");
		_playerInfo.attributeWater = INIDATA->loadDataInterger("캐릭터", "플레이어2", "수속성");
		_playerInfo.attributeFire = INIDATA->loadDataInterger("캐릭터", "플레이어2", "화속성");
		_playerInfo.attributeWind = INIDATA->loadDataInterger("캐릭터", "플레이어2", "풍속성");
		_playerInfo.currentStamina = INIDATA->loadDataInterger("캐릭터", "플레이어2", "현재체력");
		_playerInfo.magicalEnergy = INIDATA->loadDataInterger("캐릭터", "플레이어2", "기력");
		_playerInfo.playerHealth = INIDATA->loadDataInterger("캐릭터", "플레이어2", "건강");
		_playerInfo.playerStamina = INIDATA->loadDataInterger("캐릭터", "플레이어2", "체력");
		_playerInfo.playerStrength = INIDATA->loadDataInterger("캐릭터", "플레이어2", "완력");
		_playerInfo.playerSpeed = INIDATA->loadDataInterger("캐릭터", "플레이어2", "스피드");
		_playerInfo.currentEXP = INIDATA->loadDataInterger("캐릭터", "플레이어2", "현재경험치");
		_playerInfo.nextEXP = INIDATA->loadDataInterger("캐릭터", "플레이어2", "다음경험치");

		string isDungeon = INIDATA->loadDataString("캐릭터", "플레이어2", "현재장소");

		if (isDungeon == "던전1")
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
	//로그인되어있는 플레이어확인
	int loginPlayer1 = INIDATA->loadDataInterger("캐릭터", "플레이어1", "로그인");
	int loginPlayer2 = INIDATA->loadDataInterger("캐릭터", "플레이어2", "로그인");

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
		//마을로가는 워프를 만났을때
		if (_tiles[searchIsoX[i]][searchIsoY[i]].tileType == TYPE_WHORF_VILLAGE)
		{
			if (loginPlayer1 == (int)INFO_YES)
			{
				string currentPlace = INIDATA->loadDataString("캐릭터", "플레이어1", "현재장소");

				//이동 전 장소가 던전1일경우
				if (currentPlace == "던전1")
				{
					INIDATA->addData("플레이어1", "이전장소", "던전1");
					char convertPlace[256];
					INIDATA->addData("플레이어1", "장소이동", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("캐릭터");
					RENDERMANAGER->deleteAll();
					SOUNDMANAGER->play("village_bg", 0.4f);
					SCENEMANAGER->changeScene("마을");
					break;
				}

				if (currentPlace == "아이템상점")
				{
					INIDATA->addData("플레이어1", "이전장소", "아이템상점");
					char convertPlace[256];
					INIDATA->addData("플레이어1", "장소이동", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("캐릭터");
					RENDERMANAGER->deleteAll();
					SOUNDMANAGER->play("village_bg", 0.4f);
					SCENEMANAGER->changeScene("마을");
					break;
				}
			}

			if (loginPlayer2 == (int)INFO_YES)
			{
				string currentPlace = INIDATA->loadDataString("캐릭터", "플레이어2", "현재장소");

				//이동 전 장소가 던전1일경우
				if (currentPlace == "던전1")
				{
					INIDATA->addData("플레이어2", "이전장소", "던전1");
					char convertPlace[256];
					INIDATA->addData("플레이어2", "장소이동", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("캐릭터");
					RENDERMANAGER->deleteAll();
					SCENEMANAGER->changeScene("마을");
					break;
				}

				if (currentPlace == "아이템상점")
				{
					INIDATA->addData("플레이어2", "이전장소", "아이템상점");
					char convertPlace[256];
					INIDATA->addData("플레이어2", "장소이동", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("캐릭터");
					RENDERMANAGER->deleteAll();
					SCENEMANAGER->changeScene("마을");
					break;
				}
			}
		}

		//던전1로 가는 워프를 만났을때
		if (_tiles[searchIsoX[i]][searchIsoY[i]].tileType == TYPE_WHORF_DUNGEON1)
		{
			if (loginPlayer1 == (int)INFO_YES)
			{
				string currentPlace = INIDATA->loadDataString("캐릭터", "플레이어1", "현재장소");

				//이동 전 장소가 마을일경우
				if (currentPlace == "마을")
				{
					INIDATA->addData("플레이어1", "이전장소", "마을");
					char convertPlace[256];
					INIDATA->addData("플레이어1", "장소이동", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("캐릭터");
					RENDERMANAGER->deleteAll();
					SOUNDMANAGER->play("dungeon1_bg", 0.4f);
					SCENEMANAGER->changeScene("던전1");
					break;
				}
			}

			if (loginPlayer2 == (int)INFO_YES)
			{
				string currentPlace = INIDATA->loadDataString("캐릭터", "플레이어2", "현재장소");

				//이동 전 장소가 마을일경우
				if (currentPlace == "마을")
				{
					INIDATA->addData("플레이어2", "이전장소", "마을");
					char convertPlace[256];
					INIDATA->addData("플레이어2", "장소이동", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("캐릭터");
					RENDERMANAGER->deleteAll();
					SOUNDMANAGER->play("dungeon1_bg", 0.4f);
					SCENEMANAGER->changeScene("던전1");
					break;
				}
			}
		}

		//아이템상점으로 가는 워프를 만났을때
		if (_tiles[searchIsoX[i]][searchIsoY[i]].tileType == TYPE_WHORF_ITEMSHOP)
		{
			if (loginPlayer1 == (int)INFO_YES)
			{
				string currentPlace = INIDATA->loadDataString("캐릭터", "플레이어1", "현재장소");

				//이동 전 장소가 마을일경우
				if (currentPlace == "마을")
				{
					INIDATA->addData("플레이어1", "이전장소", "마을");
					char convertPlace[256];
					INIDATA->addData("플레이어1", "장소이동", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("캐릭터");
					RENDERMANAGER->deleteAll();
					SCENEMANAGER->changeScene("아이템상점");
					break;
				}
			}

			if (loginPlayer2 == (int)INFO_YES)
			{
				string currentPlace = INIDATA->loadDataString("캐릭터", "플레이어2", "현재장소");

				//이동 전 장소가 마을일경우
				if (currentPlace == "마을")
				{
					INIDATA->addData("플레이어2", "이전장소", "마을");
					char convertPlace[256];
					INIDATA->addData("플레이어2", "장소이동", _itoa((int)INFO_YES, convertPlace, 10));
					INIDATA->iniSave("캐릭터");
					RENDERMANAGER->deleteAll();
					SCENEMANAGER->changeScene("아이템상점");
					break;
				}
			}
		}
	}
}

void tileMap::NPCSpotSearch()
{
	if (_isAvailableClickNPC == true) return;

	//좌표부터 설정하기
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
		//NPC와 컨택했을때
		if (_tiles[searchNPCIsoX[i]][searchNPCIsoY[i]].obj == OBJ_NPC)
		{
			_isAvailableClickNPC = true;
		}
	}
}

void tileMap::clickNPC()
{
	if (_isAvailableClickNPC == false) return;


	//카메라에 맞춰 이동한 만큼 + 해줘야 그에 맞는 인덱스로 찍을 수 있다
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
		//1분면 -> [x - 1][y]
		//2분면 -> [x][y - 1]
		//3분면 -> [x][y + 1]
		//4분면 -> [x + 1][y]
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
		//	if (i == isoX && j == isoY) 추가해라 조건에
		for (int i = 0; i < TILE_COUNT_X; ++i)
		{
			for (int j = 0; j < TILE_COUNT_Y; ++j)
			{
				if (i == isoX && j == isoY)
				{
					//클릭한 타일에 방어구 세일즈맨이 있을경우
					if (_tiles[i][j].obj == OBJ_NPC &&
						_tiles[i][j].objFrameX == (int)NPC_ARMOR_SALESMAN &&
						_tiles[i][j].objFrameY == 0)
					{
						_isClickArmorNPC = true;
						InputHandle();
						break;
					}

					//클릭한 타일에 방어구 세일즈맨이 있을경우
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

	//플레이어가 움직일 경우 확률을 돌린다
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
			int loginPlayer1 = INIDATA->loadDataInterger("캐릭터", "플레이어1", "로그인");
			int loginPlayer2 = INIDATA->loadDataInterger("캐릭터", "플레이어2", "로그인");
			//플1 좌표저장
			if (loginPlayer1 == (int)INFO_YES)
			{
					char currentIsoX[256];
					char currentIsoY[256];
					INIDATA->addData("플레이어1", "현재좌표X", _itoa(_playerIdX, currentIsoX, 10));
					INIDATA->addData("플레이어1", "현재좌표Y", _itoa(_playerIdY, currentIsoY, 10));
					INIDATA->iniSave("캐릭터");
			}
			//플2 좌표저장
			if (loginPlayer2 == (int)INFO_YES)
			{
					char currentIsoX[256];
					char currentIsoY[256];
					INIDATA->addData("플레이어2", "현재좌표X", _itoa(_playerIdX, currentIsoX, 10));
					INIDATA->addData("플레이어2", "현재좌표Y", _itoa(_playerIdY, currentIsoY, 10));
					INIDATA->iniSave("캐릭터");
			}
			RENDERMANAGER->deleteAll();
			SOUNDMANAGER->play("battle_convert", 0.4f);
			SCENEMANAGER->changeScene("배틀1");
		}
	}
}
