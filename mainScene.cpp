#include "stdafx.h"
#include "mainScene.h"

mainScene::mainScene()
{
}

mainScene::~mainScene()
{
}

HRESULT mainScene::init()
{
	_isMusic = false;
	_mainMenu.backImg = new image;
	_mainMenu.menuImg = new image;
	_exitWindow.frontImg = new image;
	_exitWindow.backImg = new image;
	_mainMenu.backImg = IMAGEMANAGER->findImage("mainMenuBack");
	_mainMenu.menuImg = IMAGEMANAGER->findImage("mainMenu");
	_exitWindow.frontImg = IMAGEMANAGER->findImage("inputWindow");
	_exitWindow.backImg = IMAGEMANAGER->findImage("inputWindowBack");

	_mainMenu.mainRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 100, _mainMenu.menuImg->getWidth(), _mainMenu.menuImg->getHeight());

	_mainMenu.backRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 100, _mainMenu.backImg->getWidth(), _mainMenu.backImg->getHeight());

	_mainMenu.gameStartRect = RectMakeCenter(WINSIZEX / 2, _mainMenu.mainRect.top + 60, _mainMenu.menuImg->getWidth() - 65, 30);
	_mainMenu.mapToolRect = RectMakeCenter(WINSIZEX / 2, _mainMenu.gameStartRect.bottom + 35, _mainMenu.menuImg->getWidth() - 65, 30);
	_mainMenu.exitRect = RectMakeCenter(WINSIZEX / 2, _mainMenu.mapToolRect.bottom + 35, _mainMenu.menuImg->getWidth() - 95, 30);

	_isExitOn = false;

	_isWriteInidata = false;

	return S_OK;
}

void mainScene::release()
{
}

void mainScene::update()
{
	if (_isMusic == false)
	{
		SOUNDMANAGER->play("scene_start", 0.4f);

		_isMusic = true;
	}
	wirteInidata();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SOUNDMANAGER->play("click", 0.4f);
		if (!_isExitOn)
		{
			//나가기 버튼을 누르면
			if (PtInRect(&_mainMenu.exitRect, _ptMouse))
			{
				_isExitOn = true;
			}

			if (PtInRect(&_mainMenu.gameStartRect, _ptMouse))
			{
				SCENEMANAGER->changeScene("캐릭터선택");
			}
		}

		else
		{
			if (PtInRect(&_exitWindow.rejectRect, _ptMouse))
			{
				_isExitOn = false;
			}

			if (PtInRect(&_exitWindow.permitRect, _ptMouse))
			{
				PostQuitMessage(0);
			}
		}
	}

	exitWindow();
}

void mainScene::render()
{
	IMAGEMANAGER->render("main", getMemDC(), 0, 0);
	_mainMenu.backImg->alphaRender(getMemDC(), _mainMenu.backRect.left, _mainMenu.backRect.top, 200);
	_mainMenu.menuImg->render(getMemDC(), _mainMenu.mainRect.left, _mainMenu.mainRect.top);

	textRender();
	exitRender();
	textBoxRender();

	IMAGEMANAGER->render("mouse", getMemDC(), _ptMouse.x, _ptMouse.y);
}

void mainScene::exitWindow()
{
	if (_isExitOn)
	{
		_exitWindow.windowRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, _exitWindow.frontImg->getWidth(), _exitWindow.frontImg->getHeight());
		_exitWindow.backRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, _exitWindow.backImg->getWidth(), _exitWindow.backImg->getHeight());
		_exitWindow.permitRect = RectMake(WINSIZEX / 2 - 107, WINSIZEY / 2 + 2, 97, 31);
		_exitWindow.rejectRect = RectMake(WINSIZEX / 2 + 14, WINSIZEY / 2 + 2, 97, 31);
		_exitWindow.textRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 13, 200, 31);
	}

	else
	{
		_exitWindow.windowRect = RectMakeCenter(WINSIZEX + 100, WINSIZEY+ 100, _exitWindow.frontImg->getWidth(), _exitWindow.frontImg->getHeight());
		_exitWindow.backRect = RectMakeCenter(WINSIZEX + 100, WINSIZEY + 100, _exitWindow.backImg->getWidth(), _exitWindow.backImg->getHeight());
		_exitWindow.permitRect = RectMake(WINSIZEX + 100, WINSIZEY + 100, 97, 31);
		_exitWindow.rejectRect = RectMake(WINSIZEX + 100, WINSIZEY + 100, 97, 31);
		_exitWindow.textRect = RectMakeCenter(WINSIZEX + 100, WINSIZEY + 100, 200, 31);
	}
}

void mainScene::textBoxRender()
{
	HPEN myPen = CreatePen(PS_DASH, 3, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	if (PtInRect(&_mainMenu.gameStartRect, _ptMouse))
	{
		Rectangle(getMemDC(), _mainMenu.gameStartRect);
	}

	if (PtInRect(&_mainMenu.mapToolRect, _ptMouse))
	{
		Rectangle(getMemDC(), _mainMenu.mapToolRect);
	}

	if (PtInRect(&_mainMenu.exitRect, _ptMouse))
	{
		Rectangle(getMemDC(), _mainMenu.exitRect);
	}

	if (PtInRect(&_exitWindow.permitRect, _ptMouse))
	{
		Rectangle(getMemDC(), _exitWindow.permitRect);
	}

	if (PtInRect(&_exitWindow.rejectRect, _ptMouse))
	{
		Rectangle(getMemDC(), _exitWindow.rejectRect);
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void mainScene::textRender()
{
	char str[128];
	char str2[128];
	char str3[128];
	HFONT font = CreateFont(30, 0, 0, 0, 600, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY목각파임B"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(80, 200, 230));
	sprintf(str, "게임시작");
	TextOut(getMemDC(), _mainMenu.gameStartRect.left, _mainMenu.gameStartRect.top, str, strlen(str));
	sprintf(str2, "맵툴제작");
	TextOut(getMemDC(), _mainMenu.mapToolRect.left, _mainMenu.mapToolRect.top, str2, strlen(str2));
	sprintf(str3, "끝내기");
	TextOut(getMemDC(), _mainMenu.exitRect.left, _mainMenu.exitRect.top, str3, strlen(str3));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	SetBkMode(getMemDC(), OPAQUE);
}

void mainScene::exitRender()
{
	if (_isExitOn)
	{
		_exitWindow.backImg->alphaRender(getMemDC(), _exitWindow.backRect.left, _exitWindow.backRect.top, 200);
		_exitWindow.frontImg->render(getMemDC(), _exitWindow.windowRect.left, _exitWindow.windowRect.top);
		char str[128];
		char str2[128];
		char str3[128];
		HFONT font = CreateFont(20, 0, 0, 0, 600, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY목각파임B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		sprintf(str, "정말 나가시겠습니까?");
		TextOut(getMemDC(), _exitWindow.textRect.left, _exitWindow.textRect.top, str, strlen(str));
		SetTextColor(getMemDC(), RGB(0, 0, 255));
		sprintf(str2, "네");
		TextOut(getMemDC(), (_exitWindow.permitRect.left + _exitWindow.permitRect.right) / 2 - 10, _exitWindow.permitRect.top + 5, str2, strlen(str2));
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		sprintf(str3, "아니오");
		TextOut(getMemDC(), (_exitWindow.rejectRect.left + _exitWindow.rejectRect.right) / 2 - 30, _exitWindow.rejectRect.top + 5, str3, strlen(str3));
		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}
}

void mainScene::wirteInidata()
{
	if (_isWriteInidata) return;

	string existPlayer1 = INIDATA->loadDataString("캐릭터", "플레이어1", "있어?");
	string existPlayer2 = INIDATA->loadDataString("캐릭터", "플레이어2", "있어?");

	if (atoi(existPlayer1.c_str()) != (int)INFO_YES)
	{
		char temp[128];
		INIDATA->addData("플레이어1", "있어?", itoa((int)INFO_NO, temp, 10));
		INIDATA->iniSave("캐릭터");
	}

	if (atoi(existPlayer2.c_str()) != (int)INFO_YES)
	{
		char temp[128];
		INIDATA->addData("플레이어2", "있어?", itoa((int)INFO_NO, temp, 10));
		INIDATA->iniSave("캐릭터");
	}

	_isWriteInidata = true;
}

