#include "stdafx.h"
#include "playScene.h"

playScene::playScene()
{
}

playScene::~playScene()
{
}

HRESULT playScene::init()
{
	SOUNDMANAGER->addSound("lobbyMusic", "music/lobby.mp3", true, true);
	SOUNDMANAGER->play("lobbyMusic", 0.8f);

	_player.img = IMAGEMANAGER->addFrameImage("player", "img/player.bmp", 384, 192, 4, 2, true, RGB(255, 0, 255));
	_backGround = IMAGEMANAGER->addImage("Lobby", "img/playLobby.bmp", 1920, 2150, false, RGB(255, 0, 255));

	_player.x = 246;
	_player.y = 200;

	_player.rc = RectMake(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());

	_centerX = (_player.rc.right + _player.rc.left) / 2;
	_centerY = (_player.rc.top + _player.rc.bottom) / 2;

	_player.img->setFrameX(0);
	_player.img->setFrameY(0);

	CAMERAMANAGER->setCamera(0, 0);

	_elapsedSec = 0;

	_UIM = new UIManager;
	_UIM->setHeart(3);
	_UIM->setHeartBeat(7);
	_UIM->setMoney();
	_UIM->setDiamond();
	_UIM->setMoneyNumber();
	_UIM->setDiaNumber();
	_UIM->setItemHUD();
	_UIM->init();


	return S_OK;
}

void playScene::release()
{
}

void playScene::update()
{
	_elapsedSec += TIMEMANAGER->getElapsedTime();

	if (_elapsedSec >= 0.125f)
	{
		_elapsedSec -= 0.125f;
		if (_player.img->getFrameX() == _player.img->getMaxFrameX())
		{
			_player.img->setFrameX(0);
		}

		else _player.img->setFrameX(_player.img->getFrameX() + 1);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_player.x -= 96;
		_player.img->setFrameX(0);
		_player.img->setFrameY(1);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_player.y -= 96;
		_player.img->setFrameX(0);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_player.x += 96;
		_player.img->setFrameX(0);
		_player.img->setFrameY(0);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_player.y += 96;
		_player.img->setFrameX(0);
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_UIM->plusItemHUD(BODY);
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_UIM->plusItemHUD(HEAD);
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		_UIM->plusItemHUD(FEET);
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_UIM->plusItemHUD(TORCH);
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_UIM->minusItemHUD(BODY);
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_UIM->minusItemHUD(HEAD);
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_UIM->minusItemHUD(FEET);
	}

	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		_UIM->minusItemHUD(TORCH);
	}


	_player.rc = RectMake(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	_centerX = (_player.rc.right + _player.rc.left) / 2;
	_centerY = (_player.rc.top + _player.rc.bottom) / 2;
	CAMERAMANAGER->updateCamera(_player.x, _player.y);
	_UIM->updateHeart();
	_UIM->updaetHeartBeat(1.5f);
	_UIM->updateMoney();
	_UIM->updateDiamond();
	_UIM->updateMoneyNumber(123, false);
	_UIM->updateDiaNumber(5, false);
	_UIM->updateItemHUD();
}

void playScene::render()
{
	_backGround->render(getMemDC());
	_player.img->frameRender(getMemDC(), _player.x, _player.y);
	_UIM->renderHeart();
	_UIM->renderHeartBeat();
	_UIM->renderMoney();
	_UIM->renderDiamond();
	_UIM->renderMoneyNumber();
	_UIM->renderDiaNumber();
	_UIM->renderItemHUD();
}
