#include "stdafx.h"
#include "mapTool.h"
#include "toolEmpty.h"

mapTool::mapTool()
{
}

mapTool::~mapTool()
{
}

void mapTool::InputHandle()
{
	toolType* newType = _toolType->inputHandle(this);
	if (newType != nullptr)
	{
		SAFE_DELETE(_toolType);
		_toolType = newType;
		_toolType->enter(this);
	}
}

HRESULT mapTool::init()
{
	_instantCnt = 0;

	_toolType = new toolEmpty();
	_toolType->enter(this);

	_tileMap[TILE_COUNT_X][TILE_COUNT_Y] = { 0, };

	_isoX = 0;
	_isoY = 0;
	_corner = 0;

	dialogSet();

	int size = sizeof(_tileMap);

	memset(_tileMap, 0, size);

	_cameraBufferX = 500;
	_cameraBufferY = 500;

	_moveX = 0;
	_moveY = 0;

	_isMouseOnToolBar = false;
	_isClickTile = false;
	_isExitButton = false;
	_isToolTile = false;
	_isToolStructure = false;
	_isToolObject = false;
	_isToolFence = false;
	_isToolDisplay = false;
	_isToolPlants = false;
	_isToolRock = false;
	_isToolWallBasic = false;
	_isToolWallDungeon = false;
	_isToolNpc = false;
	_isToolEraser = false;
	_isToolSaveInput = false;

	setToolBar();

	//타일 프레임 초기설정
	for (int i = 0; i < TILE_COUNT_X; ++i)
	{
		for (int j = 0; j < TILE_COUNT_Y; ++j)
		{
			_tiles[i][j].terrainFrameX = 0;
			_tiles[i][j].terrainFrameY = 0;
			_tiles[i][j].objFrameX = 0;
			_tiles[i][j].objFrameY = 0;
			_tiles[i][j].tileTypeFrameX = 0;
			_tiles[i][j].tileTypeFrameY = 0;
			_tiles[i][j].obj = OBJ_NONE;
			_tiles[i][j].terrain = TR_DESERT;
			_tiles[i][j].tileType = TYPE_MOVE;
			_tiles[i][j].objRendered = false;
			_tiles[i][j].isPlayer = false;
			_tiles[i][j].isMovePoint = false;
			_tiles[i][j].isPrePlayer = false;
		}
	}

	_ctrSelect = CTRL_END;

	CAMERAMANAGER->setCamera(_cameraBufferX, _cameraBufferY);

	_leftButton.currentFrameX = 0;
	_leftButton.currentFrameY = 0;
	_rightButton.currentFrameX = 0;
	_rightButton.currentFrameY = 0;

	_count = 0;

	return S_OK;
}

void mapTool::release()
{
	_toolType->exit(this);
}

void mapTool::update()
{
	buttonFrame();
	updateCtrSelect();
	moveCamera();
	updateToolBar();
	mouseSelectTile();
	//이건 렌더매니저 활용하기위한 방법(z-order 용)
	//renderSwitch();
	//RENDERMANAGER->update();


	_underBarRc = RectMake(CAMERAMANAGER->getCameraLEFT(), CAMERAMANAGER->getCameraBOTTOM() - 24, 1024, 24);

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		selectCurrentTile();

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
			isoY >= 0 && isoY < TILE_COUNT_Y && !_isMouseOnToolBar && _isExitButton)
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

			//타일 정보 담기위한 방법
			//_tileMap[isoX][isoY] = 1;


			// 또 그 타일정보를 맵타일에 붙이기위함임
			// 타일이나 오브젝트냐, 이레이저냐 구분해서 하기

			devideCTRL(isoX, isoY);
		}
	}

	//left, up, right, down 버튼을 누르면 프레임 번호바뀌게(생성해야됨)
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		InputHandle();
		SOUNDMANAGER->play("click", 0.4f);
		//불러오기하는 함수
		if (PtInRect(&_loadRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
		{
			loadMap();
		}

		//왼쪽 버튼
		if (PtInRect(&_popUp.leftButtonRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
		{
			if (_sampleTile.terrainFrameX <= 0)
			{
				_sampleTile.terrainFrameX = _sampleTile.img->getMaxFrameX();
			}

			else _sampleTile.terrainFrameX--;
		}

		//위쪽 버튼
		if (PtInRect(&_popUp.upButtonRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
		{
			if (_sampleTile.terrainFrameY <= 0)
			{
				_sampleTile.terrainFrameY = _sampleTile.img->getMaxFrameY();
			}

			else _sampleTile.terrainFrameY--;
		}

		//오른쪽 버튼
		if (PtInRect(&_popUp.rightButtonRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
		{
			if (_sampleTile.terrainFrameX >= _sampleTile.img->getMaxFrameX())
			{
				_sampleTile.terrainFrameX = 0;
			}

			else _sampleTile.terrainFrameX++;
		}

		//아래 버튼
		if (PtInRect(&_popUp.downButtonRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
		{
			if (_sampleTile.terrainFrameY >= _sampleTile.img->getMaxFrameY())
			{
				_sampleTile.terrainFrameY = 0;
			}

			else _sampleTile.terrainFrameY++;
		}

		//팝업창 좌측버튼 눌렀을때
		if (PtInRect(&_leftButton.rc,
			PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
		{
			_leftButton.currentFrameX = 1;
		}

		//팝업창 우측버튼 눌렀을때
		if (PtInRect(&_rightButton.rc,
			PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
		{
			_rightButton.currentFrameX = 1;
		}

		//클릭했을때 타일에 마우스에 그림이 올라오도록하기위함
		if (PtInRect(&_sampleTile.rcTile, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
		{
			_isClickTile = true;
		}

		else _isClickTile = false;
	}

	_toolType->update(this);
}

void mapTool::render()
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
	//RENDERMANAGER->render(getMemDC(), "");

	//오브젝트렌더해주기(맵툴용)
	objectRender();

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

	drawTileMap();

	//sprintf(str, "isoX : %d, isoY : %d, corner: %d", _isoX, _isoY, _corner);
	//TextOut(getMemDC(), CAMERAMANAGER->getCameraLEFT() + 500, CAMERAMANAGER->getCameraTOP() + 20, str, strlen(str));

	IMAGEMANAGER->render("underBar", getMemDC(), _underBarRc.left, _underBarRc.top);

	_toolType->render(this);

	renderToolBar();
	
	if (_isClickTile)
	{
		if (_ctrSelect == CTRL_TERRAINDRAW)
		{
			_currentTile.img->alphaFrameRender(getMemDC(), _ptMouse.x + _cameraBufferX - RADIUS_WIDTH,
				_ptMouse.y + _cameraBufferY - RADIUS_HEIGHT, _currentTile.x, _currentTile.y, 190);
		}

		else if (_ctrSelect == CTRL_STRUCTUREDRAW)
		{
			_currentTile.img->alphaFrameRender(getMemDC(), _ptMouse.x + _cameraBufferX - (_currentTile.img->getFrameWidth() / 2) - 32 + 32,
				_ptMouse.y + _cameraBufferY - (_currentTile.img->getFrameHeight() / 2) - 23.5f - 235 + 141 + 94,
				_currentTile.x, _currentTile.y, 190);
		}

		else if (_ctrSelect == CTRL_OBJECTDRAW)
		{
			_currentTile.img->alphaFrameRender(getMemDC(), _ptMouse.x + _cameraBufferX - (_currentTile.img->getFrameWidth() / 2) - 10,
				_ptMouse.y + _cameraBufferY  - (_currentTile.img->getFrameHeight() / 2),
				_currentTile.x, _currentTile.y, 190);
		}

		else if (_ctrSelect == CTRL_FENCEDRAW)
		{
			_currentTile.img->alphaFrameRender(getMemDC(), _ptMouse.x + _cameraBufferX - (_currentTile.img->getFrameWidth() / 2),
				_ptMouse.y + _cameraBufferY - (_currentTile.img->getFrameHeight() / 2),
				_currentTile.x, _currentTile.y, 190);
		}

		else if (_ctrSelect == CTRL_GATEDRAW)
		{
			_currentTile.img->alphaFrameRender(getMemDC(), _ptMouse.x + _cameraBufferX - (_currentTile.img->getFrameWidth() / 2) + 18,
				_ptMouse.y + _cameraBufferY - (_currentTile.img->getFrameHeight() / 2) - 125 + 10,
				_currentTile.x, _currentTile.y, 190);
		}

		else if (_ctrSelect == CTRL_DISPLAYDRAW)
		{
			_currentTile.img->alphaFrameRender(getMemDC(), _ptMouse.x + _cameraBufferX - (_currentTile.img->getFrameWidth() / 2),
				_ptMouse.y + _cameraBufferY - (_currentTile.img->getFrameHeight() / 2) - 94 + 23.5f + 70.5f,
				_currentTile.x, _currentTile.y, 190);
		}

		else if (_ctrSelect == CTRL_PLANTSDRAW)
		{
			_currentTile.img->alphaFrameRender(getMemDC(), _ptMouse.x + _cameraBufferX - (_currentTile.img->getFrameWidth() / 2) + 3,
				_ptMouse.y + _cameraBufferY - (_currentTile.img->getFrameHeight() / 2) - 94 - 14,
				_currentTile.x, _currentTile.y, 190);
		}

		else if (_ctrSelect == CTRL_ROCKDRAW)
		{
			_currentTile.img->alphaFrameRender(getMemDC(), _ptMouse.x + _cameraBufferX - (_currentTile.img->getFrameWidth() / 2),
				_ptMouse.y + _cameraBufferY - (_currentTile.img->getFrameHeight() / 2) - 23.5f,
				_currentTile.x, _currentTile.y, 190);
		}

		else if (_ctrSelect == CTRL_WALLBASICDRAW)
		{
			_currentTile.img->alphaFrameRender(getMemDC(), _ptMouse.x + _cameraBufferX - (_currentTile.img->getFrameWidth() / 2) + 16,
				_ptMouse.y + _cameraBufferY - (_currentTile.img->getFrameHeight() / 2) - 96 + 11.75f,
				_currentTile.x, _currentTile.y, 190);
		}

		else if (_ctrSelect == CTRL_WALLDUNGEONDRAW)
		{
			_currentTile.img->alphaFrameRender(getMemDC(), _ptMouse.x + _cameraBufferX - (_currentTile.img->getFrameWidth() / 2) + 2,
				_ptMouse.y + _cameraBufferY - (_currentTile.img->getFrameHeight() / 2) - 141 + 47,
				_currentTile.x, _currentTile.y, 190);
		}

		else if (_ctrSelect == CTRL_NPCDRAW)
		{
			_currentTile.img->alphaFrameRender(getMemDC(), _ptMouse.x + _cameraBufferX - (_currentTile.img->getFrameWidth() / 2),
				_ptMouse.y + _cameraBufferY - (_currentTile.img->getFrameHeight() / 2) - 40,
				_currentTile.x, _currentTile.y, 190);
		}

		else if (_ctrSelect == CTRL_TILETYPEDRAW)
		{
			_currentTile.img->alphaFrameRender(getMemDC(), _ptMouse.x + _cameraBufferX - RADIUS_WIDTH,
				_ptMouse.y + _cameraBufferY - RADIUS_HEIGHT, _currentTile.x, _currentTile.y, 190);
		}
	}

	if (!_isToolEraser)
	{
		IMAGEMANAGER->render("mouse", getMemDC(), _ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY);
	}
}

//카메라 움직임
void mapTool::moveCamera()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() - 5);
		_cameraBufferX -= 5;
		_moveX -= 5;

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
		_moveX += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() - 5);
		_cameraBufferY -= 5;
		_moveY -= 5;

		if (CAMERAMANAGER->getCameraTOP() <= 0)
		{
			CAMERAMANAGER->setCameraY(0);
			_cameraBufferY = 0;
			_moveY = 0;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() + 5);
		_cameraBufferY += 5;
		_moveY += 5;
	}
}

//타일맵 그리는 함수
void mapTool::drawTileMap()
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
				drawRhombus(left, top);

				IMAGEMANAGER->render("tileSelect", getMemDC(), left, top);
			}
			else
			{
				drawRhombus(left, top);
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
			_tiles[i][j].centerX = centerX;
			_tiles[i][j].centerY = centerY;
		}
	}
}

void mapTool::drawRhombus(int left, int top)
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

	//마름모 라인 그리기
	//MoveToEx(getMemDC(), p[0].x, p[0].y, NULL);
	//for (int i = 1; i < 5; i++)
	//{
	//	LineTo(getMemDC(), p[i].x, p[i].y);
	//}


}

int mapTool::getCornerIndex(int isoX, int isoY)
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

bool mapTool::isInRhombus(int corner, int isoX, int isoY)
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

void mapTool::setToolBar()
{
	_tileRc = RectMake(CAMERAMANAGER->getCameraLEFT(), CAMERAMANAGER->getCameraBOTTOM(), 128, 24);
	_structureRc = RectMake(_tileRc.right, CAMERAMANAGER->getCameraBOTTOM(), 128, 24);
	_objectRc = RectMake(_structureRc.right, CAMERAMANAGER->getCameraBOTTOM(), 128, 24);
	_NPCRc = RectMake(_objectRc.right, CAMERAMANAGER->getCameraBOTTOM(), 128, 24);
	_eraserRc = RectMake(_NPCRc.right, CAMERAMANAGER->getCameraBOTTOM(), 128, 24);
	_saveRc = RectMake(_eraserRc.right, CAMERAMANAGER->getCameraBOTTOM(), 128, 24);
	_loadRc = RectMake(_saveRc.right, CAMERAMANAGER->getCameraBOTTOM(), 128, 24);
	_exitRc = RectMake(_loadRc.right, CAMERAMANAGER->getCameraBOTTOM(), 128, 24); 

	_toolY = CAMERAMANAGER->getCameraBOTTOM() + _cameraBufferY;
}

void mapTool::updateToolBar()
{
	if (PtInRect(&_underBarRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		if (_toolY > CAMERAMANAGER->getCameraBOTTOM() - 24)
		{
			_toolY -= 5.0f;
		}

		else if (_toolY <= CAMERAMANAGER->getCameraBOTTOM() - 24)
		{
			_toolY = CAMERAMANAGER->getCameraBOTTOM() - 24;
		}
	}

	else
	{
		if (_toolY < CAMERAMANAGER->getCameraBOTTOM())
		{
			_toolY += 5.0f;
		}

		else
		{
			_toolY = CAMERAMANAGER->getCameraBOTTOM();
		}
	}

	//선택버튼위에 안올라가져있을때만 false해줘서 타일 선택되게끔
	if (PtInRect(&_popUp.downButtonRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)) ||
		PtInRect(&_popUp.rightButtonRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)) ||
		PtInRect(&_popUp.upButtonRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)) ||
		PtInRect(&_popUp.leftButtonRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)) ||
		PtInRect(&_underBarRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)) ||
		PtInRect(&_sampleTile.rcTile, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)) ||
		PtInRect(&_popUp.exitButtonRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)) ||
		PtInRect(&_leftButton.rc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)) ||
		PtInRect(&_rightButton.rc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)) ||
		PtInRect(&_saveInput.saveRect, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		_isMouseOnToolBar = true;
	}

	else _isMouseOnToolBar = false;

	_tileRc = RectMake(CAMERAMANAGER->getCameraLEFT(), _toolY, 128, 24);
	_structureRc = RectMake(_tileRc.right, _toolY, 128, 24);
	_objectRc = RectMake(_structureRc.right, _toolY, 128, 24);
	_NPCRc = RectMake(_objectRc.right, _toolY, 128, 24);
	_eraserRc = RectMake(_NPCRc.right, _toolY, 128, 24);
	_saveRc = RectMake(_eraserRc.right, _toolY, 128, 24);
	_loadRc = RectMake(_saveRc.right, _toolY, 128, 24);
	_exitRc = RectMake(_loadRc.right, _toolY, 128, 24);
}

void mapTool::renderToolBar()
{
	IMAGEMANAGER->render("toolBar", getMemDC(),
		CAMERAMANAGER->getCameraLEFT(), _tileRc.top);

	HPEN myPen = CreatePen(PS_DASH, 3, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	if (PtInRect(&_tileRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _tileRc);
	}

	if (PtInRect(&_structureRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _structureRc);
	}

	if (PtInRect(&_objectRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _objectRc);
	}

	if (PtInRect(&_NPCRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _NPCRc);
	}

	if (PtInRect(&_eraserRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _eraserRc);
	}

	if (PtInRect(&_saveRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _saveRc);
	}

	if (PtInRect(&_loadRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _loadRc);
	}

	if (PtInRect(&_exitRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _exitRc);
	}

	if (PtInRect(&_popUp.exitButtonRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _popUp.exitButtonRc);
	}

	if (PtInRect(&_popUp.leftButtonRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _popUp.leftButtonRc);
	}

	if (PtInRect(&_popUp.upButtonRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _popUp.upButtonRc);
	}

	if (PtInRect(&_popUp.rightButtonRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _popUp.rightButtonRc);
	}

	if (PtInRect(&_popUp.downButtonRc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _popUp.downButtonRc);
	}

	if (PtInRect(&_sampleTile.rcTile, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _sampleTile.rcTile);
	}

	if (PtInRect(&_leftButton.rc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _leftButton.rc);
	}

	if (PtInRect(&_rightButton.rc, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _rightButton.rc);
	}

	if (PtInRect(&_saveInput.saveButtonRect, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _saveInput.saveButtonRect);
	}

	if (PtInRect(&_saveInput.cancelButtonRect, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		Rectangle(getMemDC(), _saveInput.cancelButtonRect);
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

//샘플타일을 클릭했을때 그 타일정보를 가져오기위한 함수
void mapTool::selectCurrentTile()
{
	//현재 타일 정보 가져오기
	if (PtInRect(&_sampleTile.rcTile, PointMake(_ptMouse.x + _cameraBufferX, _ptMouse.y + _cameraBufferY)))
	{
		_currentTile.x = _sampleTile.terrainFrameX;
		_currentTile.y = _sampleTile.terrainFrameY;
	}

	//타일돌리기
	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		_instantCnt++;

		if (_instantCnt >= 1)
		{
			_instantCnt = 0;

			if (_currentTile.x == _sampleTile.img->getMaxFrameX())
			{
				_currentTile.x = 0;
			}

			else _currentTile.x++;
		}
	}
}

//마우스를 타일위에 올렸을때 선택 그림 나오게하기
void mapTool::mouseSelectTile()
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

TERRAIN mapTool::terrainSelect(int frameX, int frameY)
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

TILETYPE mapTool::tileTypeSelect(int frameX, int frameY)
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

void mapTool::devideCTRL(int isoX, int isoY)
{
	if (_ctrSelect == CTRL_TERRAINDRAW)
	{
		_tiles[isoX][isoY].terrainFrameX = _currentTile.x;
		_tiles[isoX][isoY].terrainFrameY = _currentTile.y;

		//터레인 정보주기
		_tiles[isoX][isoY].terrain = terrainSelect(_currentTile.x, _currentTile.y);
	}

	else if (_ctrSelect == CTRL_STRUCTUREDRAW)
	{
		_tiles[isoX][isoY].objFrameX = _currentTile.x;
		_tiles[isoX][isoY].objFrameY = _currentTile.y;

		//오브젝트 정보주기
		_tiles[isoX][isoY].obj = OBJ_STRUCTURE;
	}

	else if (_ctrSelect == CTRL_OBJECTDRAW)
	{
		_tiles[isoX][isoY].objFrameX = _currentTile.x;
		_tiles[isoX][isoY].objFrameY = _currentTile.y;

		//오브젝트 정보주기
		_tiles[isoX][isoY].obj = OBJ_OBJECT;
	}

	else if (_ctrSelect == CTRL_FENCEDRAW)
	{
		_tiles[isoX][isoY].objFrameX = _currentTile.x;
		_tiles[isoX][isoY].objFrameY = _currentTile.y;

		//오브젝트 정보주기
		_tiles[isoX][isoY].obj = OBJ_FENCE;
	}

	else if (_ctrSelect == CTRL_GATEDRAW)
	{
		_tiles[isoX][isoY].objFrameX = _currentTile.x;
		_tiles[isoX][isoY].objFrameY = _currentTile.y;

		//오브젝트 정보주기
		_tiles[isoX][isoY].obj = OBJ_GATE;
	}

	else if (_ctrSelect == CTRL_DISPLAYDRAW)
	{
		_tiles[isoX][isoY].objFrameX = _currentTile.x;
		_tiles[isoX][isoY].objFrameY = _currentTile.y;

		//오브젝트 정보주기
		_tiles[isoX][isoY].obj = OBJ_DISPLAY;
	}

	else if (_ctrSelect == CTRL_PLANTSDRAW)
	{
		_tiles[isoX][isoY].objFrameX = _currentTile.x;
		_tiles[isoX][isoY].objFrameY = _currentTile.y;

		//오브젝트 정보주기
		_tiles[isoX][isoY].obj = OBJ_PLANTS;
	}

	else if (_ctrSelect == CTRL_ROCKDRAW)
	{
		_tiles[isoX][isoY].objFrameX = _currentTile.x;
		_tiles[isoX][isoY].objFrameY = _currentTile.y;

		//오브젝트 정보주기
		_tiles[isoX][isoY].obj = OBJ_ROCK;
	}

	else if (_ctrSelect == CTRL_WALLBASICDRAW)
	{
		_tiles[isoX][isoY].objFrameX = _currentTile.x;
		_tiles[isoX][isoY].objFrameY = _currentTile.y;

		//오브젝트 정보주기
		_tiles[isoX][isoY].obj = OBJ_WALL_BASIC;
	}

	else if (_ctrSelect == CTRL_WALLDUNGEONDRAW)
	{
		_tiles[isoX][isoY].objFrameX = _currentTile.x;
		_tiles[isoX][isoY].objFrameY = _currentTile.y;

		//오브젝트 정보주기
		_tiles[isoX][isoY].obj = OBJ_WALL_DUNGEON;
	}

	else if (_ctrSelect == CTRL_NPCDRAW)
	{
		_tiles[isoX][isoY].objFrameX = _currentTile.x;
		_tiles[isoX][isoY].objFrameY = _currentTile.y;

		//오브젝트 정보주기
		_tiles[isoX][isoY].obj = OBJ_NPC;
	}

	else if (_ctrSelect == CTRL_TILETYPEDRAW)
	{
		_tiles[isoX][isoY].tileTypeFrameX = _currentTile.x;
		_tiles[isoX][isoY].tileTypeFrameY = _currentTile.y;

		//타일 타입 정보주기
		_tiles[isoX][isoY].tileType = tileTypeSelect(_currentTile.x, _currentTile.y);
	}

	else if (_ctrSelect == CTRL_ERASER)
	{
		if (_tiles[isoX][isoY].obj == OBJ_NONE) return;

		if (_tiles[isoX][isoY].obj == OBJ_STRUCTURE)
		{
			RENDERMANAGER->deleteObj("structure", &_tiles[isoX][isoY].centerX, &_tiles[isoX][isoY].centerY);
		}

		else if (_tiles[isoX][isoY].obj == OBJ_OBJECT)
		{
			RENDERMANAGER->deleteObj("object", &_tiles[isoX][isoY].centerX, &_tiles[isoX][isoY].centerY);
		}

		else if (_tiles[isoX][isoY].obj == OBJ_FENCE)
		{
			RENDERMANAGER->deleteObj("fence", &_tiles[isoX][isoY].centerX, &_tiles[isoX][isoY].centerY);
		}

		else if (_tiles[isoX][isoY].obj == OBJ_GATE)
		{
			RENDERMANAGER->deleteObj("gate", &_tiles[isoX][isoY].centerX, &_tiles[isoX][isoY].centerY);
		}

		else if (_tiles[isoX][isoY].obj == OBJ_DISPLAY)
		{
			RENDERMANAGER->deleteObj("display", &_tiles[isoX][isoY].centerX, &_tiles[isoX][isoY].centerY);
		}

		else if (_tiles[isoX][isoY].obj == OBJ_PLANTS)
		{
			RENDERMANAGER->deleteObj("plants", &_tiles[isoX][isoY].centerX, &_tiles[isoX][isoY].centerY);
		}

		else if (_tiles[isoX][isoY].obj == OBJ_ROCK)
		{
			RENDERMANAGER->deleteObj("rock", &_tiles[isoX][isoY].centerX, &_tiles[isoX][isoY].centerY);
		}

		else if (_tiles[isoX][isoY].obj == OBJ_WALL_BASIC)
		{
			RENDERMANAGER->deleteObj("wall_basic", &_tiles[isoX][isoY].centerX, &_tiles[isoX][isoY].centerY);
		}

		else if (_tiles[isoX][isoY].obj == OBJ_WALL_DUNGEON)
		{
			RENDERMANAGER->deleteObj("wall_dungeon", &_tiles[isoX][isoY].centerX, &_tiles[isoX][isoY].centerY);
		}

		else if (_tiles[isoX][isoY].obj == OBJ_NPC)
		{
			RENDERMANAGER->deleteObj("npc", &_tiles[isoX][isoY].centerX, &_tiles[isoX][isoY].centerY);
		}

		_tiles[isoX][isoY].objFrameX = NULL;
		_tiles[isoX][isoY].objFrameY = NULL;
		_tiles[isoX][isoY].obj = OBJ_NONE;
	}

	InvalidateRect(_hWnd, NULL, false);
}

void mapTool::updateCtrSelect()
{
	if (_isToolTile)
	{
		_ctrSelect = CTRL_TERRAINDRAW;
	}

	else if (_isToolStructure)
	{
		_ctrSelect = CTRL_STRUCTUREDRAW;
	}

	else if (_isToolObject)
	{
		_ctrSelect = CTRL_OBJECTDRAW;
	}

	else if (_isToolFence)
	{
		_ctrSelect = CTRL_FENCEDRAW;
	}

	else if (_isToolGate)
	{
		_ctrSelect = CTRL_GATEDRAW;
	}

	else if (_isToolDisplay)
	{
		_ctrSelect = CTRL_DISPLAYDRAW;
	}

	else if (_isToolPlants)
	{
		_ctrSelect = CTRL_PLANTSDRAW;
	}

	else if (_isToolRock)
	{
		_ctrSelect = CTRL_ROCKDRAW;
	}

	else if (_isToolWallBasic)
	{
		_ctrSelect = CTRL_WALLBASICDRAW;
	}

	else if (_isToolWallDungeon)
	{
		_ctrSelect = CTRL_WALLDUNGEONDRAW;
	}

	else if (_isToolNpc)
	{
		_ctrSelect = CTRL_NPCDRAW;
	}

	else if (_isToolEraser)
	{
		_ctrSelect = CTRL_ERASER;
	}

	else if (_isToolTileType)
	{
		_ctrSelect = CTRL_TILETYPEDRAW;
	}
}

void mapTool::buttonFrame()
{
	if (_leftButton.currentFrameX == 1)
	{
		_count++;

		if (_count >= 3)
		{
			_count = 0;
			_leftButton.currentFrameX = 0;
		}
	}

	if (_rightButton.currentFrameX == 1)
	{
		_count++;

		if (_count >= 3)
		{
			_count = 0;
			_rightButton.currentFrameX = 0;
		}
	}
}

void mapTool::saveMap()
{
	if (name.size() == 0) return;

	//저장
	HANDLE file;
	DWORD write;	
	name.append(".map");

	file = CreateFile(name.c_str(), GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y, &write, NULL);

	CloseHandle(file);
}

void mapTool::loadMap()
{
	//읽어오기
	HANDLE file;
	DWORD read;

	file = CreateFile("shop.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y, &read, NULL);

	CloseHandle(file);
}

void mapTool::renderSwitch()
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

void mapTool::objectRender()
{
	for (int j = 0; j < TILE_COUNT_Y; ++j)
	{
		for (int i = 0; i < TILE_COUNT_X; ++i)
		{
			//속성이 부여안되어있으면 그리지않게끔 예외처리
			if (_tiles[i][j].obj == OBJ_NONE) continue;

			//카메라 안에서만 렌더되게 하기위한 작업
			RECT temp;
			RECT cameraRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + (CAMERAX / 2), CAMERAMANAGER->getCameraTOP() + (CAMERAY / 2), CAMERAX + 200, CAMERAY + 200);
			RECT tileRect = RectMake(_tiles[i][j].left, _tiles[i][j].top, 64, 47);
			if (!IntersectRect(&temp, &cameraRect, &tileRect)) continue;

			if (_tiles[i][j].obj == OBJ_STRUCTURE)
			{
				IMAGEMANAGER->frameRender("structure", getMemDC(), _tiles[i][j].left - 350 + 32,
					_tiles[i][j].top - 350 - 47,
					_tiles[i][j].objFrameX, _tiles[i][j].objFrameY);
			}

			else if (_tiles[i][j].obj == OBJ_OBJECT)
			{
				IMAGEMANAGER->frameRender("object", getMemDC(), _tiles[i][j].left - 168, _tiles[i][j].top - 203.5f,
					_tiles[i][j].objFrameX, _tiles[i][j].objFrameY);
			}

			else if (_tiles[i][j].obj == OBJ_FENCE)
			{
				IMAGEMANAGER->frameRender("fence", getMemDC(), _tiles[i][j].left - 38, _tiles[i][j].top - 68.5f + 23.5f,
					_tiles[i][j].objFrameX, _tiles[i][j].objFrameY);
			}

			else if (_tiles[i][j].obj == OBJ_GATE)
			{
				IMAGEMANAGER->frameRender("gate", getMemDC(), _tiles[i][j].left - 118 + 18, _tiles[i][j].top - 203.5f - 125 + 10,
					_tiles[i][j].objFrameX, _tiles[i][j].objFrameY);
			}

			else if (_tiles[i][j].obj == OBJ_DISPLAY)
			{
				IMAGEMANAGER->frameRender("display", getMemDC(), _tiles[i][j].left - 125 + 32, _tiles[i][j].top - 125 + 47 - 94 + 23.5f,
					_tiles[i][j].objFrameX, _tiles[i][j].objFrameY);
			}

			else if (_tiles[i][j].obj == OBJ_PLANTS)
			{
				IMAGEMANAGER->frameRender("plants", getMemDC(), _tiles[i][j].left - 150 + 35, _tiles[i][j].top - 150 + 47 - 94 - 14,
					_tiles[i][j].objFrameX, _tiles[i][j].objFrameY);
			}

			else if (_tiles[i][j].obj == OBJ_ROCK)
			{
				IMAGEMANAGER->frameRender("rock", getMemDC(), _tiles[i][j].left - 50 + 32, _tiles[i][j].top - 50,
					_tiles[i][j].objFrameX, _tiles[i][j].objFrameY);
			}

			else if (_tiles[i][j].obj == OBJ_WALL_BASIC)
			{
				IMAGEMANAGER->frameRender("wall_basic", getMemDC(), _tiles[i][j].left - 200 + 32 + 16, _tiles[i][j].top - 200 + 23.5f - 96 + 11.75f,
					_tiles[i][j].objFrameX, _tiles[i][j].objFrameY);
			}

			else if (_tiles[i][j].obj == OBJ_WALL_DUNGEON)
			{
				IMAGEMANAGER->frameRender("wall_dungeon", getMemDC(), _tiles[i][j].left - 200 + 34, _tiles[i][j].top - 250 + 23.5f - 141,
					_tiles[i][j].objFrameX, _tiles[i][j].objFrameY);
			}

			else if (_tiles[i][j].obj == OBJ_NPC)
			{
				IMAGEMANAGER->frameRender("npc", getMemDC(), _tiles[i][j].left - 50 + 32, _tiles[i][j].top - 50 + 23.5f - 40,
					_tiles[i][j].objFrameX, _tiles[i][j].objFrameY);
			}
		}
	}
}

void mapTool::dialogSet()
{
	_dialog = "";
}

void mapTool::dialogInput()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "Q";
			name.append(_dialog);
		}
		else
		{
			_dialog = "q";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "W";
			name.append(_dialog);
		}
		else
		{
			_dialog = "w";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "E";
			name.append(_dialog);
		}
		else
		{
			_dialog = "e";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "R";
			name.append(_dialog);
		}
		else
		{
			_dialog = "r";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "T";
			name.append(_dialog);
		}
		else
		{
			_dialog = "t";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "Y";
			name.append(_dialog);
		}
		else
		{
			_dialog = "y";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('U'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "U";
			name.append(_dialog);
		}
		else
		{
			_dialog = "u";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "I";
			name.append(_dialog);
		}
		else
		{
			_dialog = "i";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "O";
			name.append(_dialog);
		}
		else
		{
			_dialog = "o";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "P";
			name.append(_dialog);
		}
		else
		{
			_dialog = "p";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "A";
			name.append(_dialog);
		}
		else
		{
			_dialog = "a";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "S";
			name.append(_dialog);
		}
		else
		{
			_dialog = "s";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "D";
			name.append(_dialog);
		}
		else
		{
			_dialog = "d";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "F";
			name.append(_dialog);
		}
		else
		{
			_dialog = "f";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "G";
			name.append(_dialog);
		}
		else
		{
			_dialog = "g";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "H";
			name.append(_dialog);
		}
		else
		{
			_dialog = "h";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "J";
			name.append(_dialog);
		}
		else
		{
			_dialog = "j";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "K";
			name.append(_dialog);
		}
		else
		{
			_dialog = "k";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "L";
			name.append(_dialog);
		}
		else
		{
			_dialog = "l";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "Z";
			name.append(_dialog);
		}
		else
		{
			_dialog = "z";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "X";
			name.append(_dialog);
		}
		else
		{
			_dialog = "x";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "C";
			name.append(_dialog);
		}
		else
		{
			_dialog = "c";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "V";
			name.append(_dialog);
		}
		else
		{
			_dialog = "v";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "B";
			name.append(_dialog);
		}
		else
		{
			_dialog = "b";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "N";
			name.append(_dialog);
		}
		else
		{
			_dialog = "n";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "M";
			name.append(_dialog);
		}
		else
		{
			_dialog = "m";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		if (name.size() > 0)
		{
			name.erase(name.end() - 1);
		}
	}
}

void mapTool::renderDialog()
{
	HFONT font = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("Consolas"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);

	TextOut(getMemDC(), _saveInput.textInputRect.left + 10, _saveInput.textInputRect.top, name.c_str(), name.size());

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
}

