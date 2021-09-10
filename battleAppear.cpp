#include "stdafx.h"
#include "gameNode.h"
#include "battleMap.h"
#include "playerTurn.h"
#include "battleAppear.h"
#include "petTurn.h"
#include "battleTurn.h"
#include "battleClose.h"

battleState * battleAppear::inputHandle(battleMap * battleMap)
{
	if (battleMap->_battleTurn == TURN_PLAYER)
	{
		return new playerTurn();
	}

	return nullptr;
}

void battleAppear::update(battleMap * battleMap)
{
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsMove() == false)
		{
			battleMap->_petIsMoveCount++;
		}
	}

	if (battleMap->_petIsMoveCount != battleMap->_vPet.size())
	{
		battleMap->_petIsMoveCount = 0;
	}

	if (battleMap->_petIsMoveCount == battleMap->_vPet.size() &&
		battleMap->_player->getIsPlayerMove() == false)
	{
		battleMap->_petIsMoveCount = 0;
		battleMap->_battleTurn = TURN_PLAYER;
	}
}

void battleAppear::enter(battleMap * battleMap)
{
	battleMap->_petIsMoveCount = 0;
}

void battleAppear::render(battleMap * battleMap)
{
}

void battleAppear::exit(battleMap * battleMap)
{
}
