#include "stdafx.h"
#include "player.h"
#include "playerStand.h"
#include "playerRun.h"
#include "playerSeat.h"
#include "playerDead.h"
#include "playerHurt.h"
#include "playerHello.h"
#include "playerAngry.h"
#include "playerDefense.h"
#include "playerAttack.h"
#include "playerCry.h"
#include "playerHappy.h"

playerState * playerAttack::inputHandle(player * player)
{
	if (player->getIsPlayerMove() == true)
	{
		player->setPlayerState(STATE_RUN);
		return new playerRun();
	}

	//Y값이 바뀌면 다시 enter해라
	if (_preCurrentFrameY != player->getPlayerCurrentFrameY())
	{
		return new playerAttack();
	}

	if (player->getPlayerState() == STATE_STAND) return new playerStand();

	if (player->getPlayerState() == STATE_RUN) return new playerRun();

	if (player->getPlayerState() == STATE_SEAT) return new playerSeat();

	if (player->getPlayerState() == STATE_DEAD) return new playerDead();

	if (player->getPlayerState() == STATE_HURT) return new playerHurt();

	if (player->getPlayerState() == STATE_HELLO) return new playerHello();

	if (player->getPlayerState() == STATE_ANGRY) return new playerAngry();

	if (player->getPlayerState() == STATE_DEFENSE) return new playerDefense();

	if (player->getPlayerState() == STATE_CRY) return new playerCry();

	if (player->getPlayerState() == STATE_HAPPY) return new playerHappy();

	return nullptr;
}

void playerAttack::update(player * player)
{
	//플레이어 frame에 맞춘 방향 설정
	player->setPlayerCurrentFrameY((int)(player->_player.direction));

	if (player->getPlayerCurrentFrameX() == 6)
	{
		if (_isSound == false)
		{
			SOUNDMANAGER->play("one_heat", 0.4f);
			_isSound = true;
		}
	}
}

void playerAttack::enter(player * player)
{
	_isSound = false;

	if (player->_player.playerCharacter == BLUE)
	{
		player->_player.img = IMAGEMANAGER->findImage("blue_attack_basic");
		player->_playerImageName = "blue_attack_basic";
		player->setPlayerCurrentFrameX(0);
		player->setPlayerCurrentFrameY((int)(player->_player.direction));

		if (player->getPlayerCurrentFrameY() == (int)DIR_SIX)
		{
			player->setPlayerImageMoveY(-23);
			player->setPlayerImageMoveX(-3);
		}

		if (player->getPlayerCurrentFrameY() == (int)DIR_SEVEN)
		{
			player->setPlayerImageMoveY(-27);
			player->setPlayerImageMoveX(-14);
		}

		if (player->getPlayerCurrentFrameY() == (int)DIR_NINE)
		{
			player->setPlayerImageMoveY(-34);
			player->setPlayerImageMoveX(-14);
		}

		if (player->getPlayerCurrentFrameY() == (int)DIR_ELEVEN)
		{
			player->setPlayerImageMoveY(-40);
			player->setPlayerImageMoveX(-14);
		}

		if (player->getPlayerCurrentFrameY() == (int)DIR_TWELVE)
		{
			player->setPlayerImageMoveY(-40);
			player->setPlayerImageMoveX(3);
		}

		if (player->getPlayerCurrentFrameY() == (int)DIR_ONE)
		{
			player->setPlayerImageMoveY(-40);
			player->setPlayerImageMoveX(10);
		}

		if (player->getPlayerCurrentFrameY() == (int)DIR_THREE)
		{
			player->setPlayerImageMoveY(-35);
			player->setPlayerImageMoveX(10);
		}

		if (player->getPlayerCurrentFrameY() == (int)DIR_FIVE)
		{
			player->setPlayerImageMoveY(-25);
			player->setPlayerImageMoveX(10);
		}
	}

	if (player->_player.playerCharacter == RED)
	{
		player->_player.img = IMAGEMANAGER->findImage("red_attack_basic");
		player->_playerImageName = "red_attack_basic";
		player->setPlayerImageMoveX(0);
		player->setPlayerImageMoveY(-23.5f);
		player->setPlayerCurrentFrameX(0);
		player->setPlayerCurrentFrameY((int)(player->_player.direction));
	}

	player->setPlayerFrameAdjustTime(0.10f);

	_preCurrentFrameY = player->getPlayerCurrentFrameY();

	player->setPlayerRect(RectMakeCenter(player->getPlayerCenterX() + player->getPlayerImageMoveX(),
		player->getPlayerCenterX() + player->getPlayerImageMoveY(),
		player->getPlayerImage()->getFrameWidth(), player->getPlayerImage()->getFrameHeight()));
	player->setPlayerImageCenterX(player->getPlayerCenterX() + player->getPlayerImageMoveX());
	player->setPlayerImageCenterY(player->getPlayerCenterY() + player->getPlayerImageMoveY());
}

void playerAttack::exit(player * player)
{
}
