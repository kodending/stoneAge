#include "stdafx.h"
#include "createScene.h"

createScene::createScene()
{
}

createScene::~createScene()
{
}

HRESULT createScene::init()
{
	SOUNDMANAGER->play("scene_start", 0.4f);
	_menu.frontImg = new image;
	_menu.backImg = new image;
	_return.img = new image;
	_red.img = new image;
	_blue.img = new image;

	_menu.frontImg = IMAGEMANAGER->findImage("mainMenu");
	_menu.backImg = IMAGEMANAGER->findImage("mainMenuBack");
	_return.img = IMAGEMANAGER->findImage("return");
	_red.img = IMAGEMANAGER->findImage("red_stand_basic");
	_blue.img = IMAGEMANAGER->findImage("blue_stand_basic");

	_isSelected = false;
	_isRed = false;
	_isBlue = false;

	_red.currentFrameX = _red.currentFrameY = 0;
	_blue.currentFrameX = _blue.currentFrameY = 0;

	_red.rc = RectMakeCenter(200, WINSIZEY / 2, _red.img->getFrameWidth(), _red.img->getFrameHeight()); 
	_red.ptInRc = RectMakeCenter(200, WINSIZEY / 2, 50, 75);
	_blue.rc = RectMakeCenter(365, WINSIZEY - 150, _blue.img->getFrameWidth(), _blue.img->getFrameHeight());
	_blue.ptInRc = RectMakeCenter(365, WINSIZEY - 150, 50, 85);

	_elapsedTime = 0;

	return S_OK;
}

void createScene::release()
{
}

void createScene::update()
{
	_elapsedTime += TIMEMANAGER->getElapsedTime();

	if (_elapsedTime >= 0.18f)
	{
		_elapsedTime -= 0.18f;

		if (_red.currentFrameX == _red.img->getMaxFrameX())
		{
			_red.currentFrameX = 0;
		}

		else _red.currentFrameX++;

		if (_blue.currentFrameX == _blue.img->getMaxFrameX())
		{
			_blue.currentFrameX = 0;
		}

		else _blue.currentFrameX++;
	}

	if (_isSelected)
	{
		_menu.frontRect = RectMakeCenter(WINSIZEX - 160, 190, _menu.frontImg->getWidth(), _menu.frontImg->getHeight());
		_menu.backRect = RectMakeCenter(WINSIZEX - 160, 190, _menu.backImg->getWidth(), _menu.backImg->getHeight());
		_return.rc = RectMakeCenter(-64, WINSIZEY + 64, _return.img->getWidth(), _return.img->getHeight());
		_menu.decideRect = RectMakeCenter(WINSIZEX - 160, 140, 45, 25);
		_menu.directionRect = RectMakeCenter(WINSIZEX - 160, 190, 45, 25);
		_menu.cancelRect = RectMakeCenter(WINSIZEX - 160, 240, 45, 25);
	}

	else
	{
		_menu.frontRect = RectMakeCenter(WINSIZEX + 160, WINSIZEY + 190, _menu.frontImg->getWidth(), _menu.frontImg->getHeight());
		_menu.backRect = RectMakeCenter(WINSIZEX + 160, WINSIZEY + 190, _menu.backImg->getWidth(), _menu.backImg->getHeight());
		_return.rc = RectMakeCenter(64, WINSIZEY - 64, _return.img->getWidth(), _return.img->getHeight());
		_menu.decideRect = RectMakeCenter(WINSIZEX + 160, WINSIZEY + 190, 50, 50);
		_menu.directionRect = RectMakeCenter(WINSIZEX + 160, WINSIZEY + 190, 50, 50);
		_menu.cancelRect = RectMakeCenter(WINSIZEX + 160, WINSIZEY + 190, 50, 50);
	}

	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SOUNDMANAGER->play("click", 0.4f);
		if (PtInRect(&_red.ptInRc, _ptMouse))
		{
			_isRed = true;
			_isBlue = false;
			_isSelected = true;
			_red.img = IMAGEMANAGER->findImage("red_run_basic");
			_blue.img = IMAGEMANAGER->findImage("blue_stand_basic");
			_blue.currentFrameY = 0;
			_blue.currentFrameX = 0;
		}

		if (PtInRect(&_blue.ptInRc, _ptMouse))
		{
			_isBlue = true;
			_isRed = false;
			_isSelected = true;
			_blue.img = IMAGEMANAGER->findImage("blue_run_basic");
			_red.img = IMAGEMANAGER->findImage("red_stand_basic");
			_red.currentFrameY = 0;
			_red.currentFrameX = 0;
		}

		if (_isSelected)
		{
			if (PtInRect(&_menu.decideRect, _ptMouse))
			{
				string selectNumber1 = INIDATA->loadDataString("캐릭터", "플레이어1", "선택");

				if (atoi(selectNumber1.c_str()) == (int)INFO_YES)
				{
					if (_isBlue)
					{
						char temp[256];
						INIDATA->addData("플레이어1", "종류", _itoa((int)INFO_BLUE, temp, 10));
					}

					if (_isRed)
					{
						char temp[256];
						INIDATA->addData("플레이어1", "종류", _itoa((int)INFO_RED, temp, 10));
					}

					INIDATA->iniSave("캐릭터");
				}

				else
				{

				}


				SCENEMANAGER->changeScene("플레이어초기설정");
			}

			if (PtInRect(&_menu.decideRect, _ptMouse))
			{
				string selectNumber2 = INIDATA->loadDataString("캐릭터", "플레이어2", "선택");

				if (atoi(selectNumber2.c_str()) == (int)INFO_YES)
				{
					if (_isBlue)
					{
						char temp[256];
						INIDATA->addData("플레이어2", "종류", _itoa((int)INFO_BLUE, temp, 10));
					}

					if (_isRed)
					{
						char temp[256];
						INIDATA->addData("플레이어2", "종류", _itoa((int)INFO_RED, temp, 10));
					}

					INIDATA->iniSave("캐릭터");
				}

				else
				{

				}

				SCENEMANAGER->changeScene("플레이어초기설정");
			}

			if (PtInRect(&_menu.directionRect, _ptMouse))
			{
				if (_isRed)
				{
					_red.currentFrameY++;

					if (_red.currentFrameY > _red.img->getMaxFrameY())
					{
						_red.currentFrameY = 0;
					}
				}

				if (_isBlue)
				{
					_blue.currentFrameY++;

					if (_blue.currentFrameY > _blue.img->getMaxFrameY())
					{
						_blue.currentFrameY = 0;
					}
				}
			}

			if (PtInRect(&_menu.cancelRect, _ptMouse))
			{
				_isBlue = false;
				_isRed = false;
				_isSelected = false;
				_blue.img = IMAGEMANAGER->findImage("blue_stand_basic");
				_red.img = IMAGEMANAGER->findImage("red_stand_basic");
				_red.currentFrameX = 0;
				_red.currentFrameY = 0;
				_blue.currentFrameX = 0;
				_blue.currentFrameY = 0;
			}
		}

		if (!_isSelected)
		{
			if (PtInRect(&_return.rc, _ptMouse))
			{
				SCENEMANAGER->changeScene("메인");
			}
		}
	}
}

void createScene::render()
{
	IMAGEMANAGER->render("characterCreate", getMemDC(), 0, 0);

	menuRender();
	playerRender();
	textBoxRender();
	subMenuRender();

	IMAGEMANAGER->render("mouse", getMemDC(), _ptMouse.x, _ptMouse.y);
}

void createScene::menuRender()
{
	if (_isSelected)
	{
		_menu.backImg->alphaRender(getMemDC(), _menu.backRect.left, _menu.backRect.top, 200);
		_menu.frontImg->render(getMemDC(), _menu.frontRect.left, _menu.frontRect.top);
	}

	else
	{
		_return.img->render(getMemDC(), _return.rc.left, _return.rc.top);
	}
}

void createScene::playerRender()
{
	_red.img->frameRender(getMemDC(), _red.rc.left, _red.rc.top, _red.currentFrameX, _red.currentFrameY);
	_blue.img->frameRender(getMemDC(), _blue.rc.left, _blue.rc.top, _blue.currentFrameX, _blue.currentFrameY);
}

void createScene::textBoxRender()
{
	HPEN myPen = CreatePen(PS_DASH, 3, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	if (PtInRect(&_red.ptInRc, _ptMouse) || _isRed)
	{
		Rectangle(getMemDC(), _red.ptInRc);
	}

	if (PtInRect(&_blue.ptInRc, _ptMouse) || _isBlue)
	{
		Rectangle(getMemDC(), _blue.ptInRc);
	}

	if (PtInRect(&_return.rc, _ptMouse))
	{
		Rectangle(getMemDC(),_return.rc);
	}

	if (PtInRect(&_menu.decideRect, _ptMouse))
	{
		Rectangle(getMemDC(), _menu.decideRect);
	}

	if (PtInRect(&_menu.directionRect, _ptMouse))
	{
		Rectangle(getMemDC(), _menu.directionRect);
	}

	if (PtInRect(&_menu.cancelRect, _ptMouse))
	{
		Rectangle(getMemDC(), _menu.cancelRect);
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void createScene::subMenuRender()
{
	if (_isSelected)
	{
		char str[128];
		char str2[128];
		char str3[128];
		HFONT font = CreateFont(20, 0, 0, 0, 600, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY목각파임B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);

		SetTextColor(getMemDC(), RGB(255, 240, 21));
		sprintf(str, "결정");
		TextOut(getMemDC(), _menu.decideRect.left, _menu.decideRect.top + 2, str, strlen(str));

		SetTextColor(getMemDC(), RGB(255, 240, 21));
		sprintf(str2, "방향");
		TextOut(getMemDC(), _menu.directionRect.left, _menu.directionRect.top + 2, str2, strlen(str2));

		SetTextColor(getMemDC(), RGB(255, 240, 21));
		sprintf(str3, "취소");
		TextOut(getMemDC(), _menu.cancelRect.left, _menu.cancelRect.top + 2, str3, strlen(str3));


		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}
}
