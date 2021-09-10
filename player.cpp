#include "stdafx.h"
#include "player.h"
#include "playerStand.h"

player::player()
{
}

player::~player()
{
}

void player::InputHandle()
{
	playerState* newType = _playerState->inputHandle(this);
	if (newType != nullptr)
	{
		SAFE_DELETE(_playerState);
		_playerState = newType;
		_playerState->enter(this);
	}
}

HRESULT player::init()
{
	_isMoveClick = false;

	_moveEndX = _moveEndY = 0;

	_imageMoveX = _imageMoveY = 0;

	_isPlayerMove = false;

	_isActionRun = false;

	_isAttackTime = false;
	_isAttacked = false;
	_isAttackClose = false;
	_isHurt = false;
	_isDefenseOn = false;
	_isDamaged = false;
	_damageCount = 0;
	_damageTimeCount = 0;
	_isDead = false;
	_isPetCatch = false;
	_isEscape = false;
	_isEscapeSuccess = false;

	setScene();

	return S_OK;
}

void player::release()
{
	_playerState->exit(this);
}

void player::update()
{
	InputHandle();
	_playerState->update(this);

	if (_isDamaged == true)
	{
		_damageTimeCount++;

		if (_damageTimeCount >= 40)
		{
			_damageTimeCount = 0;
			_isDamaged = false;
		}
	}

	frameImage();
}

void player::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _player.rc);
		Rectangle(getMemDC(), _player.currentTileRect);
	}

	if (_isDefenseOn == true && _isDead == false)
	{
		IMAGEMANAGER->render("guard", getMemDC(), _player.selectRect.left, _player.selectRect.top - 20);
	}

	if (_isDamaged == true)
	{
		HFONT font = CreateFont(25, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("¸¼Àº°íµñ"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 20, 20));

		char damage[256];
		TextOut(getMemDC(), _player.selectRect.left + 25, _player.selectRect.top - 40 - _damageTimeCount,
			_itoa(_damageCount, damage, 10), strlen(_itoa(_damageCount, damage, 10)));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}

	if (_isEscape == true)
	{
		IMAGEMANAGER->render("escape", getMemDC(), _player.selectRect.left - 20, _player.selectRect.top - 25);
	}
}

void player::frameImage()
{
	_elapsedSec += TIMEMANAGER->getElapsedTime();

	if (_elapsedSec >= _frameAdjustTime)
	{
		_elapsedSec -= _frameAdjustTime;

		_player.currentFrameX++;

		if (_player.playerState == STATE_ANGRY || _player.playerState == STATE_HAPPY ||
			_player.playerState == STATE_CRY || _player.playerState == STATE_HELLO ||
			_player.playerState == STATE_RUN || _player.playerState == STATE_STAND)
		{
			if (_player.currentFrameX > _player.img->getMaxFrameX())
			{
				_player.currentFrameX = 0;
			}
		}

		if (_player.playerState == STATE_ATTACK || _player.playerState == STATE_DEAD ||
			_player.playerState == STATE_DEFENSE || _player.playerState == STATE_HURT ||
			_player.playerState == STATE_SEAT)
		{
			if (_player.currentFrameX > _player.img->getMaxFrameX())
			{
				_player.currentFrameX = _player.img->getMaxFrameX();
			}
		}
	}
}

void player::setScene()
{
	_player.currentFrameX = _player.currentFrameY = 0;
	_player.direction = DIR_SIX;
	_player.moveSpeedX = 2.72f; 
	_player.moveSpeedY = 2; 
 	_player.playerCharacter = RED;
	_player.playerWeapon = WEAPON_NONE;
	_player.playerState = STATE_STAND;
	_player.img = IMAGEMANAGER->findImage("blue_stand_basic");
	_playerImageName = "blue_stand_basic";
	_player.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(), _player.img->getFrameWidth(), _player.img->getFrameHeight());
	_player.currentTileRect = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(), 64, 47);
	_player.centerX = (_player.rc.left + _player.rc.right) / 2;
	_player.centerY = (_player.rc.top + _player.rc.bottom) / 2;
	_player.playerCenterX = _player.centerX;
	_player.playerCenterY = _player.centerY - 23.5f;
	_elapsedSec = 0;
	_frameAdjustTime = 0.15f;

	RENDERMANAGER->addObj("player", _playerImageName.c_str(), &_player.centerX, &_player.centerY, &_player.playerCenterX, &_player.playerCenterY, &_player.currentFrameX, &_player.currentFrameY);
	
	_playerState = new playerStand();
	_playerState->enter(this);
}
