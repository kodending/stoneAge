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

playerState * playerHurt::inputHandle(player * player)
{
	if (player->getIsPlayerMove() == true)
	{
		player->setPlayerState(STATE_RUN);
		return new playerRun();
	}

	//Y값이 바뀌면 다시 enter해라
	if (_preCurrentFrameY != player->getPlayerCurrentFrameY())
	{
		return new playerHurt();
	}

	if (player->getPlayerState() == STATE_STAND) return new playerStand();

	if (player->getPlayerState() == STATE_RUN) return new playerRun();

	if (player->getPlayerState() == STATE_SEAT) return new playerSeat();

	if (player->getPlayerState() == STATE_DEAD) return new playerDead();

	if (player->getPlayerState() == STATE_HELLO) return new playerHello();

	if (player->getPlayerState() == STATE_ANGRY) return new playerAngry();

	if (player->getPlayerState() == STATE_DEFENSE) return new playerDefense();

	if (player->getPlayerState() == STATE_ATTACK) return new playerAttack();

	if (player->getPlayerState() == STATE_CRY) return new playerCry();

	if (player->getPlayerState() == STATE_HAPPY) return new playerHappy();

	return nullptr;
}

void playerHurt::update(player * player)
{
	//플레이어 frame에 맞춘 방향 설정
	player->setPlayerCurrentFrameY((int)(player->_player.direction));
}

void playerHurt::enter(player * player)
{
	if (player->_player.playerCharacter == BLUE)
	{
		player->_player.img = IMAGEMANAGER->findImage("blue_hurt_basic");
		player->_playerImageName = "blue_hurt_basic";
		player->setPlayerImageMoveY(-30);
		player->setPlayerImageMoveX(0);
		player->setPlayerCurrentFrameX(0);
		player->setPlayerCurrentFrameY((int)(player->_player.direction));
	}

	if (player->_player.playerCharacter == RED)
	{
		player->_player.img = IMAGEMANAGER->findImage("red_hurt_basic");
		player->_playerImageName = "red_hurt_basic";
		player->setPlayerImageMoveX(0);
		player->setPlayerImageMoveY(-23.5f);
		player->setPlayerCurrentFrameX(0);
		player->setPlayerCurrentFrameY((int)(player->_player.direction));
	}

	player->setPlayerFrameAdjustTime(0.15f);

	_preCurrentFrameY = player->getPlayerCurrentFrameY();

	player->setPlayerRect(RectMakeCenter(player->getPlayerCenterX() + player->getPlayerImageMoveX(),
		player->getPlayerCenterX() + player->getPlayerImageMoveY(),
		player->getPlayerImage()->getFrameWidth(), player->getPlayerImage()->getFrameHeight()));
	player->setPlayerImageCenterX(player->getPlayerCenterX() + player->getPlayerImageMoveX());
	player->setPlayerImageCenterY(player->getPlayerCenterY() + player->getPlayerImageMoveY());
}

void playerHurt::exit(player * player)
{
}
