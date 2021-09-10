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

menuType * actionWindow::inputHandle(tileMap * tileMap)
{
	if (PtInRect(&_actionWindow.exitButtonRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsPosibleClick(false);
		tileMap->setDelayClickCount(0);
		tileMap->setIsMouseOnAction(false);
		SOUNDMANAGER->play("window_down", 0.4f);
		return new baseType();
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

	playerState(tileMap);

	return nullptr;
}

void actionWindow::update(tileMap * tileMap)
{
	_actionWindow.backRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 125, CAMERAMANAGER->getCameraTOP() + 140,
		_actionWindow.backImg->getWidth(), _actionWindow.backImg->getHeight());
	_actionWindow.frontRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 125, CAMERAMANAGER->getCameraTOP() + 140,
		_actionWindow.frontImg->getWidth(), _actionWindow.frontImg->getHeight());
	_actionWindow.exitButtonRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 125, CAMERAMANAGER->getCameraTOP() + 240,
		_actionWindow.exitButtonImg->getWidth(), _actionWindow.exitButtonImg->getHeight());

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			_actionWindow.actionRect[j][i] = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 170 + j * 100, CAMERAMANAGER->getCameraTOP() + 50 + i * 30,
				70, 20);
		}
	}

	_actionWindow.actionRect2 = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 125, CAMERAMANAGER->getCameraTOP() + 200,
		70, 20);

	if (PtInRect(&_actionWindow.frontRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setIsMouseOnAction(true);
	}

	else tileMap->setIsMouseOnAction(false);
}

void actionWindow::enter(tileMap * tileMap)
{
	_actionWindow.backImg = IMAGEMANAGER->findImage("actionWindowBack");
	_actionWindow.frontImg = IMAGEMANAGER->findImage("actionWindow");
	_actionWindow.exitButtonImg = IMAGEMANAGER->findImage("button");
	_actionWindow.backRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 125, CAMERAMANAGER->getCameraTOP() + 140,
		_actionWindow.backImg->getWidth(), _actionWindow.backImg->getHeight());
	_actionWindow.frontRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 125, CAMERAMANAGER->getCameraTOP() + 140,
		_actionWindow.frontImg->getWidth(), _actionWindow.frontImg->getHeight());
	_actionWindow.exitButtonRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 125, CAMERAMANAGER->getCameraTOP() + 240,
		_actionWindow.exitButtonImg->getWidth(), _actionWindow.exitButtonImg->getHeight());
	
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			_actionWindow.actionRect[j][i] = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 170 + j * 100, CAMERAMANAGER->getCameraTOP() + 50 + i * 30,
				70, 20);
		}
	}

	_actionWindow.actionRect2 = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 125, CAMERAMANAGER->getCameraTOP() + 200,
		70, 20);
}

void actionWindow::render(tileMap * tileMap)
{
	_actionWindow.backImg->alphaRender(getMemDC(), _actionWindow.backRect.left, _actionWindow.backRect.top, 200);
	_actionWindow.frontImg->render(getMemDC(), _actionWindow.frontRect.left, _actionWindow.frontRect.top);
	_actionWindow.exitButtonImg->render(getMemDC(), _actionWindow.exitButtonRect.left, _actionWindow.exitButtonRect.top);

	HFONT font2 = CreateFont(15, 0, 0, 0, 400, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("¸¼Àº°íµñ"));
	HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), font2);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	char seat[256];
	char stand[256];
	char hello[256];
	char run[256];
	char hurt[256];
	char dead[256];
	char happy[256];
	char cry[256];
	char attack[256];
	char defence[256];
	char angry[256];

	sprintf(seat, "¾É ´Ù");
	TextOut(getMemDC(), _actionWindow.actionRect[0][0].left + 5, _actionWindow.actionRect[0][0].top + 2,
		seat, strlen(seat));

	sprintf(stand, "ÀÏ¾î³ª´Ù");
	TextOut(getMemDC(), _actionWindow.actionRect[1][0].left + 5, _actionWindow.actionRect[1][0].top + 2,
		stand, strlen(stand));

	sprintf(hello, "¼ÕÈçµé´Ù");
	TextOut(getMemDC(), _actionWindow.actionRect[0][1].left + 5, _actionWindow.actionRect[0][1].top + 2,
		hello, strlen(hello));

	sprintf(run, "°È ´Ù");
	TextOut(getMemDC(), _actionWindow.actionRect[1][1].left + 5, _actionWindow.actionRect[1][1].top + 2,
		run, strlen(run));

	sprintf(hurt, "¾ò¾î¸Â´Ù");
	TextOut(getMemDC(), _actionWindow.actionRect[0][2].left + 5, _actionWindow.actionRect[0][2].top + 2,
		hurt, strlen(hurt));

	sprintf(dead, "¾²·¯Áö´Ù");
	TextOut(getMemDC(), _actionWindow.actionRect[1][2].left + 5, _actionWindow.actionRect[1][2].top + 2,
		dead, strlen(dead));

	sprintf(happy, "Áñ°Å¿ò");
	TextOut(getMemDC(), _actionWindow.actionRect[0][3].left + 5, _actionWindow.actionRect[0][3].top + 2,
		happy, strlen(happy));

	sprintf(cry, "½½ÆÛÇÏ´Ù");
	TextOut(getMemDC(), _actionWindow.actionRect[1][3].left + 5, _actionWindow.actionRect[1][3].top + 2,
		cry, strlen(cry));

	sprintf(attack, "°ø°ÝÇÏ´Ù");
	TextOut(getMemDC(), _actionWindow.actionRect[0][4].left + 5, _actionWindow.actionRect[0][4].top + 2,
		attack, strlen(attack));

	sprintf(defence, "¹æ¾îÇÏ´Ù");
	TextOut(getMemDC(), _actionWindow.actionRect[1][4].left + 5, _actionWindow.actionRect[1][4].top + 2,
		defence, strlen(defence));

	sprintf(angry, "È­¸¦³»´Ù");
	TextOut(getMemDC(), _actionWindow.actionRect2.left + 5, _actionWindow.actionRect2.top + 2,
		angry, strlen(angry));

	SelectObject(getMemDC(), oldFont2);
	DeleteObject(font2);
	SetBkMode(getMemDC(), OPAQUE);

	HFONT font = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY¸ñ°¢ÆÄÀÓB"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(222, 0, 0));

	char exit[256];
	sprintf(exit, "´Ý ±â");
	TextOut(getMemDC(), _actionWindow.exitButtonRect.left + 25, _actionWindow.exitButtonRect.top + 5,
		exit, strlen(exit));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	SetBkMode(getMemDC(), OPAQUE);

	ptInRectRender(tileMap);
}

void actionWindow::exit(tileMap * tileMap)
{
}

void actionWindow::ptInRectRender(tileMap * tileMap)
{
	HPEN myPen = CreatePen(PS_DASH, 3, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	if (PtInRect(&_actionWindow.exitButtonRect, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _actionWindow.exitButtonRect);
	}

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (PtInRect(&_actionWindow.actionRect[j][i], PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
			{
				Rectangle(getMemDC(), _actionWindow.actionRect[j][i]);
			}
		}
	}

	if (PtInRect(&_actionWindow.actionRect2, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		Rectangle(getMemDC(), _actionWindow.actionRect2);
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void actionWindow::playerState(tileMap * tileMap)
{
	//¾É±â¸¦ ´­·¶À»¶§
	if (PtInRect(&_actionWindow.actionRect[0][0], PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setPlayerState(STATE_SEAT);
	}

	//¼­ÀÖ±â¸¦ ´­·¶À»¶§
	if (PtInRect(&_actionWindow.actionRect[1][0], PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setPlayerState(STATE_STAND);
	}

	//¼ÕÈçµé´Ù¸¦ ´­·¶À»¶§
	if (PtInRect(&_actionWindow.actionRect[0][1], PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setPlayerState(STATE_HELLO);
	}

	//°È±â¸¦ ´­·¶À»¶§
	if (PtInRect(&_actionWindow.actionRect[1][1], PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setPlayerActionRun(true);
		tileMap->setPlayerState(STATE_RUN);
	}

	//¾ò¾î¸Â´Ù¸¦ ´­·¶À»¶§
	if (PtInRect(&_actionWindow.actionRect[0][2], PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setPlayerState(STATE_HURT);
	}

	//¾²·¯Áö´Ù¸¦ ´­·¶À»¶§
	if (PtInRect(&_actionWindow.actionRect[1][2], PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setPlayerState(STATE_DEAD);
	}

	//Áñ°Å¿òÀ» ´­·¶À»¶§
	if (PtInRect(&_actionWindow.actionRect[0][3], PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setPlayerState(STATE_HAPPY);
	}

	//½½ÇÄÀ» ´­·¶À»¶§
	if (PtInRect(&_actionWindow.actionRect[1][3], PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setPlayerState(STATE_CRY);
	}

	//°ø°ÝÇÏ´Ù¸¦ ´­·¶À»¶§
	if (PtInRect(&_actionWindow.actionRect[0][4], PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setPlayerState(STATE_ATTACK);
	}

	//¹æ¾îÇÏ´Ù¸¦ ´­·¶À»¶§
	if (PtInRect(&_actionWindow.actionRect[1][4], PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setPlayerState(STATE_DEFENSE);
	}

	//È­¸¦³»´Ù¸¦ ´­·¶À»¶§
	if (PtInRect(&_actionWindow.actionRect2, PointMake(_ptMouse.x + tileMap->getCameraBufferX(), _ptMouse.y + tileMap->getCameraBufferY())))
	{
		tileMap->setPlayerState(STATE_ANGRY);
	}
}
