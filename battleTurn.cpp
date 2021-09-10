#include "stdafx.h"
#include "gameNode.h"
#include "battleMap.h"
#include "playerTurn.h"
#include "battleAppear.h"
#include "petTurn.h"
#include "battleTurn.h"
#include "battleClose.h"

battleState * battleTurn::inputHandle(battleMap * battleMap)
{
	if (battleMap->_battleTurn == TURN_PLAYER)
	{
		_isDamageCalculation = false;
		return new playerTurn();
	}

	if (battleMap->_battleTurn == TURN_CLOSE_BATTLE)
	{
		return new battleClose();
	}

	return nullptr;
}

void battleTurn::update(battleMap * battleMap)
{
	battleSort(battleMap);
	battleStart(battleMap);
	updateBattle(battleMap);
	battleClosed2(battleMap);
	turnEndBattle(battleMap);
	heatBattle(battleMap);
	hurtMove(battleMap);
	moveFrameY(battleMap);
	deadMotion(battleMap);
	catchBattle(battleMap);
	attackSelectConvert(battleMap);
	battleClosed(battleMap);
	happyTime(battleMap);
}

void battleTurn::enter(battleMap * battleMap)
{
	setEnemySelect(battleMap);
	_delayCount = 0;
	_isDamageCalculation = false;
	_pushPowerX = 8;
	_pushPowerY = 5.875f;
	_isShortStop = false;
	_happyTime = 0;
	_enemyDeathCount = 0;
	_deadCount = 0;
	_isCatchSound = false;
	_isDeadSound = false;
	_turnOffCount = 0;
	_isbattleEnd = false;
	_isCatchCatch = false;
}

void battleTurn::render(battleMap * battleMap)
{


}

void battleTurn::exit(battleMap * battleMap)
{


}

void battleTurn::setEnemySelect(battleMap * battleMap)
{
	//공방결정(죽었을경우 걍 끝)
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;
		if (battleMap->_vPet[i]->_isDead == true) continue;
		if (battleMap->_vPet[i]->_isCatched == true) continue;

		//확률조정하기요~
		int randomNum = RND->getFromIntTo(1, 101); // 1 ~ 100까지 100개의 숫자중 하나 나오게한다 

		if (battleMap->_vPet[i]->getPetAttackPower() >
			battleMap->_vPet[i]->getPetDefensePower())
		{
			if (randomNum >= 30) battleMap->_vPet[i]->_petSkill = PET_SKILL_ATTACK;
			else battleMap->_vPet[i]->_petSkill = PET_SKILL_DEFENSE;
			continue;
		}

		if (battleMap->_vPet[i]->getPetAttackPower() <
			battleMap->_vPet[i]->getPetDefensePower())
		{
			if (randomNum >= 30) battleMap->_vPet[i]->_petSkill = PET_SKILL_DEFENSE;
			else battleMap->_vPet[i]->_petSkill = PET_SKILL_ATTACK;
			continue;
		}

		if (battleMap->_vPet[i]->getPetAttackPower() ==
			battleMap->_vPet[i]->getPetDefensePower())
		{
			if (randomNum >= 51) battleMap->_vPet[i]->_petSkill = PET_SKILL_DEFENSE;
			else battleMap->_vPet[i]->_petSkill = PET_SKILL_ATTACK;
			continue;
		}
	}

	//공격결정했을경우 공격목표 설정하기
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;
		if (battleMap->_vPet[i]->_isDead == true) continue;
		if (battleMap->_vPet[i]->_isCatched == true) continue;

		if (battleMap->_vPet[i]->_petSkill == PET_SKILL_ATTACK)
		{
			int attackPoint = RND->getFromIntTo(1, 11);

			// 8, 9, 10 나올경우 플레이어 공격
			if (attackPoint > 7)
			{
				battleMap->_vPet[i]->setAttackPointX(battleMap->_player->getPlayerCenterX() - 32);
				battleMap->_vPet[i]->setAttackPointY(battleMap->_player->getPlayerCenterY() - 23.5f);
				continue;
			}

			// 1 ~ 7 나올경우 펫 공격
			else
			{
				for (int j = 0; j < battleMap->_vPet.size(); ++j)
				{
					if (battleMap->_vPet[j]->getIsPlayerPet() == false) continue;
					if (battleMap->_vPet[j]->_isDead == true)
					{
						battleMap->_vPet[i]->setAttackPointX(battleMap->_player->getPlayerCenterX() - 32);
						battleMap->_vPet[i]->setAttackPointY(battleMap->_player->getPlayerCenterY() - 23.5f);
						continue;
					}

					battleMap->_vPet[i]->setAttackPointX(battleMap->_vPet[j]->getTileCenterX() - 32);
					battleMap->_vPet[i]->setAttackPointY(battleMap->_vPet[j]->getTileCenterY() - 23.5f);
					continue;
				}
			}
		}
	}

	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->_isDead == true)
		{
			battleMap->_vPet[i]->_isAttacked = true;
		}
	}
		

	//공격이 아닐 경우 이미 공격한것으로 취급하기
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;
		if (battleMap->_vPet[i]->_petSkill == PET_SKILL_ATTACK) continue;

		battleMap->_vPet[i]->_isAttacked = true;
	}

	//공격이 아닐 경우 이미 공격한것으로 취급하기
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;
		if (battleMap->_vPet[i]->_petSkill == PET_SKILL_ATTACK) continue;

		battleMap->_vPet[i]->_isAttacked = true;
	}

	//플레이어도 공격도 캐치도 아닌경우 공격한것으로 취급하기
	if (battleMap->_battleSelect != BATTLE_ATTACK &&
		battleMap->_battleSelect != BATTLE_CATCH &&
		battleMap->_battleSelect != BATTLE_ESCAPE)
	{
		battleMap->_player->_isAttacked = true;
	}

	//순서 배열에 넣기
	addObjArray(battleMap);
}

//배틀 순서 돌리기
void battleTurn::battleSort(battleMap * battleMap)
{
	quickSort(0, _arrObj.size() - 1);
}

void battleTurn::addObject(int speedPower)
{
	OBJECT obj;
	obj.speedPower = speedPower;

	_arrObj.push_back(obj);
}

void battleTurn::addObjArray(battleMap * battleMap)
{
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->_petSkill != PET_SKILL_ATTACK) continue;


		addObject(battleMap->_vPet[i]->getPetSpeedPower());
	}

	if (battleMap->_battleSelect == BATTLE_ATTACK ||
		battleMap->_battleSelect == BATTLE_CATCH ||
		battleMap->_battleSelect == BATTLE_ESCAPE)
	{
		addObject(battleMap->_playerInfo.speedPower);
	}
}

void battleTurn::quickSort(int left, int right)
{
	if (left >= right)
	{
		return;                                          
	}

	int pivot = left;
	int i = left + 1;
	int j = right;
	OBJECT temp;

	while (i <= j)
	{
		while (i <= right && _arrObj[i].speedPower <= _arrObj[pivot].speedPower) i++;
		while (j > left && _arrObj[j].speedPower >= _arrObj[pivot].speedPower) j--;

		if (i > j)
		{
			temp = _arrObj[pivot];
			_arrObj[pivot] = _arrObj[j];
			_arrObj[j] = temp;
		}
		else
		{
			temp = _arrObj[j];
			_arrObj[j] = _arrObj[i];
			_arrObj[i] = temp;
		}
	}
	quickSort(left, j - 1);
	quickSort(j + 1, right);
}

void battleTurn::battleStart(battleMap * battleMap)
{
	//공격중인상황일때는 포문 안돌리기
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->_isAttackTime == true) return;
		if (battleMap->_vPet[i]->_isDeadTime == true) return;
	}

	if (battleMap->_player->_isAttackTime == true) return;
	if (battleMap->_player->_isDead == true) return;

	for (int i = _arrObj.size() - 1; i > -1; --i) //꺼꾸로해야 스피드가 제일 높은애부터 움직임
	{
		if (battleMap->_battleSelect == BATTLE_ATTACK ||
			battleMap->_battleSelect == BATTLE_CATCH ||
			battleMap->_battleSelect == BATTLE_ESCAPE)
		{
			if (_arrObj[i].speedPower == battleMap->_playerInfo.speedPower)
			{
				if (battleMap->_player->_isAttacked == true) continue;

				battleMap->_player->_isAttackTime = true;
				return;
			}
		}

		for (int j = 0; j < battleMap->_vPet.size(); ++j)
		{
			if (_arrObj[i].speedPower == battleMap->_vPet[j]->getPetSpeedPower())
			{
				if (battleMap->_vPet[j]->_isAttacked == true) continue;
				if (battleMap->_vPet[j]->_petSkill != PET_SKILL_ATTACK) continue;

				battleMap->_vPet[j]->_isAttackTime = true;
				return;
			}
		}
	}
}

void battleTurn::updateBattle(battleMap * battleMap)
{
	//플레이어 공격일때
	if (battleMap->_player->_isAttackTime == true)
	{
		//도망치는것을 선택한놈이라면..
		if (battleMap->_battleSelect == BATTLE_ESCAPE)
		{
			for (int i = 0; i < battleMap->_vPet.size(); ++i)
			{
				if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

				if (battleMap->_player->getPlayerCenterX() < battleMap->_player->getAttackPointX())
				{
					battleMap->_player->setPlayerCenterX(battleMap->_player->getPlayerCenterX() + battleMap->_moveSpeedX);
					battleMap->_vPet[i]->setTileCenterX(battleMap->_vPet[i]->getTileCenterX() + battleMap->_moveSpeedX);
				}

				if (battleMap->_player->getPlayerCenterY() < battleMap->_player->getAttackPointY())
				{
					battleMap->_player->setPlayerCenterY(battleMap->_player->getPlayerCenterY() + battleMap->_moveSpeedY);
					battleMap->_vPet[i]->setTileCenterY(battleMap->_vPet[i]->getTileCenterY() + battleMap->_moveSpeedY);
				}

				if (battleMap->_player->getPlayerCenterX() >= battleMap->_player->getAttackPointX())
				{
					battleMap->_player->setPlayerCenterX(battleMap->_player->getAttackPointX());
					battleMap->_vPet[i]->setTileCenterX(battleMap->_player->getAttackPointX());
				}

				if (battleMap->_player->getPlayerCenterY() >= battleMap->_player->getAttackPointY())
				{
					battleMap->_player->setPlayerCenterY(battleMap->_player->getAttackPointY());
					battleMap->_vPet[i]->setTileCenterX(battleMap->_player->getAttackPointY());
				}

				if (battleMap->_player->getPlayerCenterX() == battleMap->_player->getAttackPointX() &&
					battleMap->_player->getPlayerCenterY() == battleMap->_player->getAttackPointY())
				{
					battleMap->_player->setPlayerState(STATE_RUN);
					battleMap->_player->_isEscapeSuccess = true;
					battleMap->_player->setIsPlayerMove(false);
					battleMap->_vPet[i]->setIsMove(false);
				}

				else
				{
					battleMap->_player->_isEscape = true;
					battleMap->_player->setIsPlayerMove(true);
					battleMap->_player->setPlayerDirection(DIR_FIVE);
					battleMap->_player->setPlayerCurrentFrameY((int)DIR_FIVE);
					battleMap->_vPet[i]->setIsMove(true);
					battleMap->_vPet[i]->setPetDirection(DIR_FIVE);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_FIVE);
				}
			}
		}

		//공격하러 올라가서 공격을 아직안했으면
		if (battleMap->_player->_isAttackClose == false &&
			battleMap->_battleSelect != BATTLE_ESCAPE)
		{
			if (battleMap->_player->getPlayerCenterX() > battleMap->_player->getAttackPointX())
			{
				battleMap->_player->setPlayerCenterX(battleMap->_player->getPlayerCenterX() - battleMap->_moveSpeedX);
			}

			if (battleMap->_player->getPlayerCenterY() > battleMap->_player->getAttackPointY())
			{
				battleMap->_player->setPlayerCenterY(battleMap->_player->getPlayerCenterY() - battleMap->_moveSpeedY);
			}

			if (battleMap->_player->getPlayerCenterX() <= battleMap->_player->getAttackPointX())
			{
				battleMap->_player->setPlayerCenterX(battleMap->_player->getAttackPointX());
			}

			if (battleMap->_player->getPlayerCenterY() <= battleMap->_player->getAttackPointY())
			{
				battleMap->_player->setPlayerCenterY(battleMap->_player->getAttackPointY());
			}

			if (battleMap->_player->getPlayerCenterX() == battleMap->_player->getAttackPointX() &&
				battleMap->_player->getPlayerCenterY() == battleMap->_player->getAttackPointY())
			{
				battleMap->_player->setPlayerState(STATE_ATTACK);
				battleMap->_player->setIsPlayerMove(false);
				battleMap->_player->setPlayerDirection(DIR_ELEVEN);
				battleMap->_player->setPlayerCurrentFrameY((int)DIR_ELEVEN);
			}

			else battleMap->_player->setIsPlayerMove(true);
		}

		//공격을 마쳤으면 돌아가가고 도착하면 어택타임 꺼주고, 어택했다고 트루해주기
		if (battleMap->_player->_isAttackClose == true)
		{
			if (battleMap->_player->getPlayerCenterX() < battleMap->_player->getPlayerMoveEndX())
			{
				battleMap->_player->setPlayerCenterX(battleMap->_player->getPlayerCenterX() + battleMap->_moveSpeedX);
			}

			if (battleMap->_player->getPlayerCenterY() < battleMap->_player->getPlayerMoveEndY())
			{
				battleMap->_player->setPlayerCenterY(battleMap->_player->getPlayerCenterY() + battleMap->_moveSpeedY);
			}

			if (battleMap->_player->getPlayerCenterX() >= battleMap->_player->getPlayerMoveEndX())
			{
				battleMap->_player->setPlayerCenterX(battleMap->_player->getPlayerMoveEndX());
			}

			if (battleMap->_player->getPlayerCenterY() >= battleMap->_player->getPlayerMoveEndY())
			{
				battleMap->_player->setPlayerCenterY(battleMap->_player->getPlayerMoveEndY());
			}

			if (battleMap->_player->getPlayerCenterX() == battleMap->_player->getPlayerMoveEndX() &&
				battleMap->_player->getPlayerCenterY() == battleMap->_player->getPlayerMoveEndY())
			{
				battleMap->_player->setIsPlayerMove(false);
				battleMap->_player->_isAttacked = true;
				battleMap->_player->setPlayerDirection(DIR_ELEVEN);
				battleMap->_player->setPlayerCurrentFrameY((int)DIR_ELEVEN);

				//공격하고 돌아왔을때는
				if (battleMap->_battleSelect == BATTLE_ATTACK)	battleMap->_player->_isAttackTime = false;
				//캐치했을때는
				if (battleMap->_battleSelect == BATTLE_CATCH)
				{
					battleMap->_player->setPlayerState(STATE_HAPPY);

					if (_isCatchSound == false)
					{
						SOUNDMANAGER->play("catch_success_bg", 0.4f);
						_isCatchSound = true;
					}

					_happyTime++;
					if (_happyTime >= 250)
					{
						_happyTime = 0;
						battleMap->_player->_isAttackTime = false;
						battleMap->_player->setPlayerState(STATE_STAND);

						for (int i = 0; i < battleMap->_vPet.size(); ++i)
						{
							if (battleMap->_vPet[i]->getEnumPetState() != PET_CATCHED) continue;

							battleMap->_vPet[i]->_isAttacked = true;
							battleMap->_vPet[i]->_isCatched = true;
							battleMap->_vPet[i]->_isDead = true;
							battleMap->_vPet[i]->setEnumPetState(PET_DEAD);
							battleMap->_vPet[i]->setTileCenterX(WINSIZEX + 100);
							battleMap->_vPet[i]->setTileCenterY(WINSIZEY + 100);
						}
					}
				}
			}

			else
			{
				battleMap->_player->setIsPlayerMove(true);
			}
		}

		//공격하고 공격을 마쳤을시 트루 값 바꿔주기				
		if (battleMap->_player->getPlayerState() == STATE_ATTACK &&
			battleMap->_player->_isAttackClose == false)
		{
			if (battleMap->_player->getPlayerCurrentFrameX() ==
				battleMap->_player->getPlayerImage()->getMaxFrameX())
			{
				_delayCount++;
				if (_delayCount >= 30)
				{
					_delayCount = 0;
					_isDamageCalculation = false;
					battleMap->_player->setPlayerState(STATE_STAND);
					battleMap->_player->_isAttackClose = true;
					if (battleMap->_battleSelect == BATTLE_ATTACK)	battleMap->_player->_isAttackTime = false;
				}
			}
		}

		battleMap->_player->setPlayerRect(RectMakeCenter(battleMap->_player->getPlayerCenterX() + battleMap->_player->getPlayerImageMoveX(),
			battleMap->_player->getPlayerCenterY() + battleMap->_player->getPlayerImageMoveY(),
			battleMap->_player->getPlayerImage()->getFrameWidth(), battleMap->_player->getPlayerImage()->getFrameHeight()));
		battleMap->_player->setPlayerImageCenterX(battleMap->_player->getPlayerCenterX() + battleMap->_player->getPlayerImageMoveX());
		battleMap->_player->setPlayerImageCenterY(battleMap->_player->getPlayerCenterY() + battleMap->_player->getPlayerImageMoveY());
		battleMap->_player->setPlayerTileRect(RectMakeCenter(battleMap->_player->getPlayerCenterX(), battleMap->_player->getPlayerCenterY(),
			64, 47));
		battleMap->_player->setSelectRect(RectMakeCenter(battleMap->_player->getPlayerCenterX() + battleMap->_player->getPlayerImageMoveX(),
			battleMap->_player->getPlayerCenterY() + battleMap->_player->getPlayerImageMoveY(),
			battleMap->_player->getPlayerImage()->getFrameWidth() / 2, battleMap->_player->getPlayerImage()->getFrameHeight() - 20));
	}

	//펫 공격일때
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

		if (battleMap->_vPet[i]->_isAttackTime == true)
		{
			//공격하러 올라가서 공격을 아직 안했으면
			if (battleMap->_vPet[i]->_isAttackClose == false)
			{
				if (battleMap->_vPet[i]->getTileCenterX() > battleMap->_vPet[i]->getAttackPointX())
				{
					battleMap->_vPet[i]->setTileCenterX(battleMap->_vPet[i]->getTileCenterX() - battleMap->_moveSpeedX);
				}

				if (battleMap->_vPet[i]->getTileCenterY() > battleMap->_vPet[i]->getAttackPointY())
				{
					battleMap->_vPet[i]->setTileCenterY(battleMap->_vPet[i]->getTileCenterY() - battleMap->_moveSpeedY);
				}

				if (battleMap->_vPet[i]->getTileCenterX() <= battleMap->_vPet[i]->getAttackPointX())
				{
					battleMap->_vPet[i]->setTileCenterX(battleMap->_vPet[i]->getAttackPointX());
				}

				if (battleMap->_vPet[i]->getTileCenterY() <= battleMap->_vPet[i]->getAttackPointY())
				{
					battleMap->_vPet[i]->setTileCenterY(battleMap->_vPet[i]->getAttackPointY());
				}

				if (battleMap->_vPet[i]->getTileCenterX() == battleMap->_vPet[i]->getAttackPointX() &&
					battleMap->_vPet[i]->getTileCenterY() == battleMap->_vPet[i]->getAttackPointY())
				{
					battleMap->_vPet[i]->setEnumPetState(PET_ATTACK);
					battleMap->_vPet[i]->setIsMove(false);
					battleMap->_vPet[i]->setPetDirection(DIR_ELEVEN);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_ELEVEN);
				}

				else battleMap->_vPet[i]->setIsMove(true);
			}

			//공격 후에 다시 원위치 어택타임 끄고, 어택했다고 트루해주기
			if (battleMap->_vPet[i]->_isAttackClose == true)
			{
				if (battleMap->_vPet[i]->getTileCenterX() < battleMap->_vPet[i]->getMoveEndX())
				{
					battleMap->_vPet[i]->setTileCenterX(battleMap->_vPet[i]->getTileCenterX() + battleMap->_moveSpeedX);
				}

				if (battleMap->_vPet[i]->getTileCenterY() < battleMap->_vPet[i]->getMoveEndY())
				{
					battleMap->_vPet[i]->setTileCenterY(battleMap->_vPet[i]->getTileCenterY() + battleMap->_moveSpeedY);
				}

				if (battleMap->_vPet[i]->getTileCenterX() >= battleMap->_vPet[i]->getMoveEndX())
				{
					battleMap->_vPet[i]->setTileCenterX(battleMap->_vPet[i]->getMoveEndX());
				}

				if (battleMap->_vPet[i]->getTileCenterY() >= battleMap->_vPet[i]->getMoveEndY())
				{
					battleMap->_vPet[i]->setTileCenterY(battleMap->_vPet[i]->getMoveEndY());
				}

				if (battleMap->_vPet[i]->getTileCenterX() == battleMap->_vPet[i]->getMoveEndX() &&
					battleMap->_vPet[i]->getTileCenterY() == battleMap->_vPet[i]->getMoveEndY())
				{
					battleMap->_vPet[i]->setIsMove(false);
					battleMap->_vPet[i]->_isAttackTime = false;
					battleMap->_vPet[i]->_isAttacked = true;
					battleMap->_vPet[i]->setPetDirection(DIR_ELEVEN);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_ELEVEN);
				}

				else
				{
					battleMap->_vPet[i]->setIsMove(true);
				}
			}

			if (battleMap->_vPet[i]->getEnumPetState() == PET_ATTACK &&
				battleMap->_vPet[i]->_isAttackClose == false)
			{
				if (battleMap->_vPet[i]->getCurrentFrameX() ==
					battleMap->_vPet[i]->getImage()->getMaxFrameX())
				{
					_delayCount++;
					
					if (_delayCount >= 30)
					{
						_delayCount = 0;
						_isDamageCalculation = false;
						battleMap->_vPet[i]->setEnumPetState(PET_STAND);
						battleMap->_vPet[i]->_isAttackClose = true;
					}
				}
			}

			battleMap->_vPet[i]->setImageRect(RectMakeCenter(battleMap->_vPet[i]->getTileCenterX() + battleMap->_vPet[i]->getImageMoveX(),
				battleMap->_vPet[i]->getTileCenterY() + battleMap->_vPet[i]->getImageMoveY(),
				battleMap->_vPet[i]->getImage()->getFrameWidth(), battleMap->_vPet[i]->getImage()->getFrameHeight()));
			battleMap->_vPet[i]->setImageCenterX(battleMap->_vPet[i]->getTileCenterX() + battleMap->_vPet[i]->getImageMoveX());
			battleMap->_vPet[i]->setImageCenterY(battleMap->_vPet[i]->getTileCenterY() + battleMap->_vPet[i]->getImageMoveY());
			battleMap->_vPet[i]->setSelectRect(RectMakeCenter(battleMap->_vPet[i]->getTileCenterX() + battleMap->_vPet[i]->getImageMoveX(),
				battleMap->_vPet[i]->getTileCenterY() + battleMap->_vPet[i]->getImageMoveY(),
				battleMap->_vPet[i]->getImage()->getFrameWidth() / 2, battleMap->_vPet[i]->getImage()->getFrameHeight() / 2));
		}
	}

	//에너미 공격일때
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;

		if (battleMap->_vPet[i]->_isAttackTime == true)
		{
			//공격하러 올라가서 공격을 아직 안했으면
			if (battleMap->_vPet[i]->_isAttackClose == false)
			{
				if (battleMap->_vPet[i]->getTileCenterX() < battleMap->_vPet[i]->getAttackPointX())
				{
					battleMap->_vPet[i]->setTileCenterX(battleMap->_vPet[i]->getTileCenterX() + battleMap->_moveSpeedX);
				}

				if (battleMap->_vPet[i]->getTileCenterY() < battleMap->_vPet[i]->getAttackPointY())
				{
					battleMap->_vPet[i]->setTileCenterY(battleMap->_vPet[i]->getTileCenterY() + battleMap->_moveSpeedY);
				}

				if (battleMap->_vPet[i]->getTileCenterX() >= battleMap->_vPet[i]->getAttackPointX())
				{
					battleMap->_vPet[i]->setTileCenterX(battleMap->_vPet[i]->getAttackPointX());
				}

				if (battleMap->_vPet[i]->getTileCenterY() >= battleMap->_vPet[i]->getAttackPointY())
				{
					battleMap->_vPet[i]->setTileCenterY(battleMap->_vPet[i]->getAttackPointY());
				}

				if (battleMap->_vPet[i]->getTileCenterX() == battleMap->_vPet[i]->getAttackPointX() &&
					battleMap->_vPet[i]->getTileCenterY() == battleMap->_vPet[i]->getAttackPointY())
				{
					battleMap->_vPet[i]->setEnumPetState(PET_ATTACK);
					battleMap->_vPet[i]->setIsMove(false);
					battleMap->_vPet[i]->setPetDirection(DIR_FIVE);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_FIVE);
				}

				else battleMap->_vPet[i]->setIsMove(true);
			}

			//공격 후에 다시 원위치 어택타임 끄고, 어택했다고 트루해주기
			if (battleMap->_vPet[i]->_isAttackClose == true)
			{
				if (battleMap->_vPet[i]->getTileCenterX() > battleMap->_vPet[i]->getMoveEndX())
				{
					battleMap->_vPet[i]->setTileCenterX(battleMap->_vPet[i]->getTileCenterX() - battleMap->_moveSpeedX);
				}

				if (battleMap->_vPet[i]->getTileCenterY() > battleMap->_vPet[i]->getMoveEndY())
				{
					battleMap->_vPet[i]->setTileCenterY(battleMap->_vPet[i]->getTileCenterY() - battleMap->_moveSpeedY);
				}

				if (battleMap->_vPet[i]->getTileCenterX() <= battleMap->_vPet[i]->getMoveEndX())
				{
					battleMap->_vPet[i]->setTileCenterX(battleMap->_vPet[i]->getMoveEndX());
				}

				if (battleMap->_vPet[i]->getTileCenterY() <= battleMap->_vPet[i]->getMoveEndY())
				{
					battleMap->_vPet[i]->setTileCenterY(battleMap->_vPet[i]->getMoveEndY());
				}

				if (battleMap->_vPet[i]->getTileCenterX() == battleMap->_vPet[i]->getMoveEndX() &&
					battleMap->_vPet[i]->getTileCenterY() == battleMap->_vPet[i]->getMoveEndY())
				{
					battleMap->_vPet[i]->setIsMove(false);
					battleMap->_vPet[i]->_isAttackTime = false;
					battleMap->_vPet[i]->_isAttacked = true;
					battleMap->_vPet[i]->setPetDirection(DIR_FIVE);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_FIVE);
				}

				else
				{
					battleMap->_vPet[i]->setIsMove(true);
				}
			}

			if (battleMap->_vPet[i]->getEnumPetState() == PET_ATTACK &&
				battleMap->_vPet[i]->_isAttackClose == false)
			{
				if (battleMap->_vPet[i]->getCurrentFrameX() ==
					battleMap->_vPet[i]->getImage()->getMaxFrameX())
				{
					_delayCount++;
					if (_delayCount >= 30)
					{
						_delayCount = 0;
						_isDamageCalculation = false;
						battleMap->_vPet[i]->setEnumPetState(PET_STAND);
						battleMap->_vPet[i]->_isAttackClose = true;
					}

				}
			}

			battleMap->_vPet[i]->setImageRect(RectMakeCenter(battleMap->_vPet[i]->getTileCenterX() + battleMap->_vPet[i]->getImageMoveX(),
				battleMap->_vPet[i]->getTileCenterY() + battleMap->_vPet[i]->getImageMoveY(),
				battleMap->_vPet[i]->getImage()->getFrameWidth(), battleMap->_vPet[i]->getImage()->getFrameHeight()));
			battleMap->_vPet[i]->setImageCenterX(battleMap->_vPet[i]->getTileCenterX() + battleMap->_vPet[i]->getImageMoveX());
			battleMap->_vPet[i]->setImageCenterY(battleMap->_vPet[i]->getTileCenterY() + battleMap->_vPet[i]->getImageMoveY());
			battleMap->_vPet[i]->setSelectRect(RectMakeCenter(battleMap->_vPet[i]->getTileCenterX() + battleMap->_vPet[i]->getImageMoveX(),
				battleMap->_vPet[i]->getTileCenterY() + battleMap->_vPet[i]->getImageMoveY(),
				battleMap->_vPet[i]->getImage()->getFrameWidth() / 2, battleMap->_vPet[i]->getImage()->getFrameHeight() / 2));
		}
	}
}

void battleTurn::turnEndBattle(battleMap * battleMap)
{
	if (_isbattleEnd == true) return;

	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->_isAttacked == false) return;
	}

	if (battleMap->_player->_isAttacked == false) return;


	//죽지도않고 잡히지도 않았으면 초기화
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->_isDead == true) continue;
		if (battleMap->_vPet[i]->_isCatched == true) continue;

		battleMap->_vPet[i]->_isAttackClose = false;
		battleMap->_vPet[i]->_isAttacked = false;
		battleMap->_vPet[i]->_isAttackTime = false;
		battleMap->_vPet[i]->setAttackPointX(battleMap->_vPet[i]->getTileCenterX());
		battleMap->_vPet[i]->setAttackPointY(battleMap->_vPet[i]->getTileCenterY());
		battleMap->_vPet[i]->_petSkill = PET_SKILL_NONE;
	}
	
	//죽었거나 잡혔으면 공격한상태그대로두기
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->_isDead == false) continue;
		if (battleMap->_vPet[i]->_isCatched == false) continue;

		battleMap->_vPet[i]->_isAttackClose = false;
		battleMap->_vPet[i]->_isAttacked = true;
		battleMap->_vPet[i]->_isAttackTime = false;
		battleMap->_vPet[i]->setAttackPointX(battleMap->_vPet[i]->getTileCenterX());
		battleMap->_vPet[i]->setAttackPointY(battleMap->_vPet[i]->getTileCenterY());
		battleMap->_vPet[i]->_petSkill = PET_SKILL_NONE;
	}

	if (battleMap->_player->_isDead == false)
	{
		battleMap->_player->_isAttackClose = false;
		battleMap->_player->_isAttacked = false;
		battleMap->_player->_isAttackTime = false;
		battleMap->_player->setAttackPointX(battleMap->_player->getPlayerCenterX());
		battleMap->_player->setAttackPointY(battleMap->_player->getPlayerCenterY());

	}

	battleMap->_battleTurn = TURN_PLAYER;
}

void battleTurn::heatBattle(battleMap * battleMap)
{
	//플레이어 공격시
	if (battleMap->_player->getPlayerState() == STATE_ATTACK)
	{
		if (battleMap->_battleSelect == BATTLE_ATTACK)
		{
			for (int i = 0; i < battleMap->_vPet.size(); ++i)
			{
				if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;

				if (battleMap->_player->getAttackPointX() - 32 == battleMap->_vPet[i]->getTileCenterX() &&
					battleMap->_player->getAttackPointY() - 23.5f == battleMap->_vPet[i]->getTileCenterY())
				{
					//무기마다 히트부위가 다름요~
					if (battleMap->_player->getPlayerCurrentFrameX() == 7)
					{
						if (battleMap->_vPet[i]->_petSkill != PET_SKILL_DEFENSE)
						{
							battleMap->_vPet[i]->setEnumPetState(PET_HURT);
							if (_isDamageCalculation == false)
							{
								battleMap->_vPet[i]->_damageCount = battleMap->_playerInfo.attackPower -
									battleMap->_vPet[i]->getPetDefensePower() + 5;
								if (battleMap->_vPet[i]->_damageCount <= 0) battleMap->_vPet[i]->_damageCount = 1;
								battleMap->_vPet[i]->setPetCurrentStamina(battleMap->_vPet[i]->getPetCurrentStamina()
									- battleMap->_vPet[i]->_damageCount);
								battleMap->_vPet[i]->_isDamaged = true;
								_isDamageCalculation = true;
							}

						}

						if (battleMap->_vPet[i]->_petSkill == PET_SKILL_DEFENSE)
						{
							battleMap->_vPet[i]->_isDefenseOn = true;
							battleMap->_vPet[i]->setEnumPetState(PET_DEFENSE);
							if (_isDamageCalculation == false)
							{
								battleMap->_vPet[i]->_damageCount = battleMap->_playerInfo.attackPower -
									(int)(battleMap->_vPet[i]->getPetDefensePower() * 1.5f) + 5;
								if (battleMap->_vPet[i]->_damageCount <= 0) battleMap->_vPet[i]->_damageCount = 1;
								battleMap->_vPet[i]->setPetCurrentStamina(battleMap->_vPet[i]->getPetCurrentStamina()
									- battleMap->_vPet[i]->_damageCount);
								battleMap->_vPet[i]->_isDamaged = true;
								_isDamageCalculation = true;
							}
						}
					}

					if (battleMap->_player->getPlayerCurrentFrameX() == battleMap->_player->getPlayerImage()->getMaxFrameX())
					{
						battleMap->_vPet[i]->_isDefenseOn = false;
						if (battleMap->_vPet[i]->getEnumPetState() == PET_HURT)
						{
							battleMap->_vPet[i]->_isHurt = true;
						}
						else battleMap->_vPet[i]->setEnumPetState(PET_STAND);
					}
				}
			}
		}
	}

	//펫이 공격시
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

		if (battleMap->_vPet[i]->getEnumPetState() == PET_ATTACK)
		{
			for (int j = 0; j < battleMap->_vPet.size(); ++j)
			{
				if (battleMap->_vPet[j]->getIsPlayerPet() == true) continue;

				if (battleMap->_vPet[i]->getAttackPointX() - 32 == battleMap->_vPet[j]->getTileCenterX() &&
					battleMap->_vPet[i]->getAttackPointY() - 23.5f == battleMap->_vPet[j]->getTileCenterY())
				{
					if (battleMap->_vPet[i]->getCurrentFrameX() == petAttackTiming(battleMap->_vPet[i]->getPetName()))
					{
						if (battleMap->_vPet[j]->_petSkill != PET_SKILL_DEFENSE)
						{
							battleMap->_vPet[j]->setEnumPetState(PET_HURT);
							if (_isDamageCalculation == false)
							{
								battleMap->_vPet[j]->_damageCount = battleMap->_vPet[i]->getPetAttackPower() -
									battleMap->_vPet[j]->getPetDefensePower() + 5;
								if (battleMap->_vPet[j]->_damageCount <= 0) battleMap->_vPet[j]->_damageCount = 1;
								battleMap->_vPet[j]->setPetCurrentStamina(battleMap->_vPet[j]->getPetCurrentStamina()
									- battleMap->_vPet[j]->_damageCount);
								battleMap->_vPet[j]->_isDamaged = true;
								_isDamageCalculation = true;
							}

						}

						if (battleMap->_vPet[j]->_petSkill == PET_SKILL_DEFENSE)
						{
							battleMap->_vPet[j]->_isDefenseOn = true;
							battleMap->_vPet[j]->setEnumPetState(PET_DEFENSE);
							if (_isDamageCalculation == false)
							{
								battleMap->_vPet[j]->_damageCount = battleMap->_vPet[i]->getPetAttackPower() -
									(int)(battleMap->_vPet[j]->getPetDefensePower() * 1.5f) + 5;
								if (battleMap->_vPet[j]->_damageCount <= 0) battleMap->_vPet[j]->_damageCount = 1;
								battleMap->_vPet[j]->setPetCurrentStamina(battleMap->_vPet[j]->getPetCurrentStamina()
									- battleMap->_vPet[j]->_damageCount);
								battleMap->_vPet[j]->_isDamaged = true;
								_isDamageCalculation = true;
							}
						}
					}

					if (battleMap->_vPet[i]->getCurrentFrameX() == battleMap->_vPet[i]->getImage()->getMaxFrameX())
					{
						battleMap->_vPet[j]->_isDefenseOn = false;
						if (battleMap->_vPet[j]->getEnumPetState() == PET_HURT)
						{
							battleMap->_vPet[j]->_isHurt = true;
						}
						else battleMap->_vPet[j]->setEnumPetState(PET_STAND);
					}
				}
			}
		}
	}

	//에너미가 공격시
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;

		if (battleMap->_vPet[i]->getEnumPetState() == PET_ATTACK)
		{
			//우리펫을 공격시
			for (int j = 0; j < battleMap->_vPet.size(); ++j)
			{
				if (battleMap->_vPet[j]->getIsPlayerPet() == false) continue;

				if (battleMap->_vPet[i]->getAttackPointX() + 32 == battleMap->_vPet[j]->getTileCenterX() &&
					battleMap->_vPet[i]->getAttackPointY() + 23.5f == battleMap->_vPet[j]->getTileCenterY())
				{
					if (battleMap->_vPet[i]->getCurrentFrameX() == petAttackTiming(battleMap->_vPet[i]->getPetName()))
					{
						if (battleMap->_vPet[j]->_petSkill != PET_SKILL_DEFENSE)
						{
							battleMap->_vPet[j]->setEnumPetState(PET_HURT);
							if (_isDamageCalculation == false)
							{
								battleMap->_vPet[j]->_damageCount = battleMap->_vPet[i]->getPetAttackPower() -
									battleMap->_vPet[j]->getPetDefensePower();
								if (battleMap->_vPet[j]->_damageCount <= 0) battleMap->_vPet[j]->_damageCount = 1;
								battleMap->_vPet[j]->setPetCurrentStamina(battleMap->_vPet[j]->getPetCurrentStamina()
									- battleMap->_vPet[j]->_damageCount);
								battleMap->_vPet[j]->_isDamaged = true;
								_isDamageCalculation = true;
							}
						}

						if (battleMap->_vPet[j]->_petSkill == PET_SKILL_DEFENSE)
						{
							battleMap->_vPet[j]->_isDefenseOn = true;
							battleMap->_vPet[j]->setEnumPetState(PET_DEFENSE);
							if (_isDamageCalculation == false)
							{
								battleMap->_vPet[j]->_damageCount = battleMap->_vPet[i]->getPetAttackPower() -
									(int)(battleMap->_vPet[j]->getPetDefensePower() * 1.5f);
								if (battleMap->_vPet[j]->_damageCount <= 0) battleMap->_vPet[j]->_damageCount = 1;
								battleMap->_vPet[j]->setPetCurrentStamina(battleMap->_vPet[j]->getPetCurrentStamina()
									- battleMap->_vPet[j]->_damageCount);
								battleMap->_vPet[j]->_isDamaged = true;
								_isDamageCalculation = true;
							}
						}
					}

					if (battleMap->_vPet[i]->getCurrentFrameX() == battleMap->_vPet[i]->getImage()->getMaxFrameX())
					{
						battleMap->_vPet[j]->_isDefenseOn = false;
						if (battleMap->_vPet[j]->getEnumPetState() == PET_HURT)
						{
							battleMap->_vPet[j]->_isHurt = true;
						}
						else battleMap->_vPet[j]->setEnumPetState(PET_STAND);
					}
				}
			}

			//플레이어를 공격시
			if (battleMap->_vPet[i]->getAttackPointX() + 32 == battleMap->_player->getPlayerCenterX() &&
				battleMap->_vPet[i]->getAttackPointY() + 23.5f == battleMap->_player->getPlayerCenterY())
			{
				if (battleMap->_vPet[i]->getCurrentFrameX() == petAttackTiming(battleMap->_vPet[i]->getPetName()))
				{
					if (battleMap->_battleSelect != BATTLE_DEFENSE)
					{
						battleMap->_player->setPlayerState(STATE_HURT);
						if (_isDamageCalculation == false)
						{
							battleMap->_player->_damageCount = battleMap->_vPet[i]->getPetAttackPower() -
								battleMap->_playerInfo.defensePower;
							if (battleMap->_player->_damageCount < 0) battleMap->_player->_damageCount = 1;
							battleMap->_playerInfo.currentStamina = battleMap->_playerInfo.currentStamina -
								battleMap->_player->_damageCount;
							battleMap->_player->_isDamaged = true;
							_isDamageCalculation = true;
						}
	
					}

					if (battleMap->_battleSelect == BATTLE_DEFENSE)
					{
						battleMap->_player->_isDefenseOn = true;
						battleMap->_player->setPlayerState(STATE_DEFENSE);
						if (_isDamageCalculation == false)
						{
							battleMap->_player->_damageCount = battleMap->_vPet[i]->getPetAttackPower() -
								(int)(battleMap->_playerInfo.defensePower * 1.5f);
							if (battleMap->_player->_damageCount <= 0) battleMap->_player->_damageCount = 1;
							battleMap->_playerInfo.currentStamina = battleMap->_playerInfo.currentStamina -
								battleMap->_player->_damageCount;
							battleMap->_player->_isDamaged = true;
							_isDamageCalculation = true;
						}
					}
				}

				if (battleMap->_vPet[i]->getCurrentFrameX() == battleMap->_vPet[i]->getImage()->getMaxFrameX())
				{
					battleMap->_player->_isDefenseOn = false;
					if (battleMap->_player->getPlayerState() == STATE_HURT)
					{
						battleMap->_player->_isHurt = true;
					}
					else battleMap->_player->setPlayerState(STATE_STAND);
				}
			}
		}
	}
}

//공격당했을때 살짝 뒤로 움직여주게하는 함수
void battleTurn::hurtMove(battleMap * battleMap)
{
	//에너미가 공격당했을경우
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;

		if (battleMap->_vPet[i]->_isHurt == true &&
			battleMap->_vPet[i]->getEnumPetState() == PET_HURT &&
			_isShortStop == false)
		{
			_pushPowerX -= 0.68f;
			_pushPowerY -= 0.5f;
			battleMap->_vPet[i]->setTileCenterX(battleMap->_vPet[i]->getTileCenterX() - _pushPowerX);
			battleMap->_vPet[i]->setTileCenterY(battleMap->_vPet[i]->getTileCenterY() - _pushPowerY);

			if (_pushPowerX <= 0 && _pushPowerY <= 0)
			{
				_pushPowerX = 8;
				_pushPowerY = 5.875f;
				_isShortStop = true;
			}
		}

		if (battleMap->_vPet[i]->_isHurt == true &&
			battleMap->_vPet[i]->getEnumPetState() == PET_HURT)
		{
			if (_isShortStop == true)
			{
				_delayCount++;
				if (_delayCount >= 40)
				{
					_delayCount = 0;
					battleMap->_vPet[i]->setEnumPetState(PET_STAND);
					_isShortStop = false;
				}
			}
		}


		if (battleMap->_vPet[i]->_isHurt == true && 
			battleMap->_vPet[i]->getEnumPetState() != PET_HURT)
		{
			if (battleMap->_vPet[i]->getTileCenterX() < battleMap->_vPet[i]->getMoveEndX())
			{
				battleMap->_vPet[i]->setTileCenterX(battleMap->_vPet[i]->getTileCenterX() + battleMap->_moveSpeedX);
			}

			if (battleMap->_vPet[i]->getTileCenterY() < battleMap->_vPet[i]->getMoveEndY())
			{
				battleMap->_vPet[i]->setTileCenterY(battleMap->_vPet[i]->getTileCenterY() + battleMap->_moveSpeedY);
			}

			if (battleMap->_vPet[i]->getTileCenterX() >= battleMap->_vPet[i]->getMoveEndX())
			{
				battleMap->_vPet[i]->setTileCenterX(battleMap->_vPet[i]->getMoveEndX());
			}

			if (battleMap->_vPet[i]->getTileCenterY() >= battleMap->_vPet[i]->getMoveEndY())
			{
				battleMap->_vPet[i]->setTileCenterY(battleMap->_vPet[i]->getMoveEndY());
			}

			if (battleMap->_vPet[i]->getTileCenterX() == battleMap->_vPet[i]->getMoveEndX() &&
				battleMap->_vPet[i]->getTileCenterY() == battleMap->_vPet[i]->getMoveEndY())
			{
				battleMap->_vPet[i]->setIsMove(false);
				battleMap->_vPet[i]->_isHurt = false;
				battleMap->_vPet[i]->setEnumPetState(PET_STAND);
			}

			else battleMap->_vPet[i]->setIsMove(true);
		}

		battleMap->_vPet[i]->setImageRect(RectMakeCenter(battleMap->_vPet[i]->getTileCenterX() + battleMap->_vPet[i]->getImageMoveX(),
			battleMap->_vPet[i]->getTileCenterY() + battleMap->_vPet[i]->getImageMoveY(),
			battleMap->_vPet[i]->getImage()->getFrameWidth(), battleMap->_vPet[i]->getImage()->getFrameHeight()));
		battleMap->_vPet[i]->setImageCenterX(battleMap->_vPet[i]->getTileCenterX() + battleMap->_vPet[i]->getImageMoveX());
		battleMap->_vPet[i]->setImageCenterY(battleMap->_vPet[i]->getTileCenterY() + battleMap->_vPet[i]->getImageMoveY());
		battleMap->_vPet[i]->setSelectRect(RectMakeCenter(battleMap->_vPet[i]->getTileCenterX() + battleMap->_vPet[i]->getImageMoveX(),
			battleMap->_vPet[i]->getTileCenterY() + battleMap->_vPet[i]->getImageMoveY(),
			battleMap->_vPet[i]->getImage()->getFrameWidth() / 2, battleMap->_vPet[i]->getImage()->getFrameHeight() / 2));
	}

	//펫이 공격당했을경우
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

		if (battleMap->_vPet[i]->_isHurt == true &&
			battleMap->_vPet[i]->getEnumPetState() == PET_HURT &&
			_isShortStop == false)
		{
			_pushPowerX -= 0.68f;
			_pushPowerY -= 0.5f;
			battleMap->_vPet[i]->setTileCenterX(battleMap->_vPet[i]->getTileCenterX() + _pushPowerX);
			battleMap->_vPet[i]->setTileCenterY(battleMap->_vPet[i]->getTileCenterY() + _pushPowerY);

			if (_pushPowerX <= 0 && _pushPowerY <= 0)
			{
				_pushPowerX = 8;
				_pushPowerY = 5.875f;
				_isShortStop = true;
			}
		}

		if (battleMap->_vPet[i]->_isHurt == true &&
			battleMap->_vPet[i]->getEnumPetState() == PET_HURT)
		{
			if (_isShortStop == true)
			{
				_delayCount++;
				if (_delayCount >= 40)
				{
					_delayCount = 0;
					battleMap->_vPet[i]->setEnumPetState(PET_STAND);
					_isShortStop = false;
				}
			}
		}


		if (battleMap->_vPet[i]->_isHurt == true &&
			battleMap->_vPet[i]->getEnumPetState() != PET_HURT)
		{
			if (battleMap->_vPet[i]->getTileCenterX() > battleMap->_vPet[i]->getMoveEndX())
			{
				battleMap->_vPet[i]->setTileCenterX(battleMap->_vPet[i]->getTileCenterX() - battleMap->_moveSpeedX);
			}

			if (battleMap->_vPet[i]->getTileCenterY() > battleMap->_vPet[i]->getMoveEndY())
			{
				battleMap->_vPet[i]->setTileCenterY(battleMap->_vPet[i]->getTileCenterY() - battleMap->_moveSpeedY);
			}

			if (battleMap->_vPet[i]->getTileCenterX() <= battleMap->_vPet[i]->getMoveEndX())
			{
				battleMap->_vPet[i]->setTileCenterX(battleMap->_vPet[i]->getMoveEndX());
			}

			if (battleMap->_vPet[i]->getTileCenterY() <= battleMap->_vPet[i]->getMoveEndY())
			{
				battleMap->_vPet[i]->setTileCenterY(battleMap->_vPet[i]->getMoveEndY());
			}

			if (battleMap->_vPet[i]->getTileCenterX() == battleMap->_vPet[i]->getMoveEndX() &&
				battleMap->_vPet[i]->getTileCenterY() == battleMap->_vPet[i]->getMoveEndY())
			{
				battleMap->_vPet[i]->setIsMove(false);
				battleMap->_vPet[i]->_isHurt = false;
				battleMap->_vPet[i]->setEnumPetState(PET_STAND);
			}

			else battleMap->_vPet[i]->setIsMove(true);
		}

		battleMap->_vPet[i]->setImageRect(RectMakeCenter(battleMap->_vPet[i]->getTileCenterX() + battleMap->_vPet[i]->getImageMoveX(),
			battleMap->_vPet[i]->getTileCenterY() + battleMap->_vPet[i]->getImageMoveY(),
			battleMap->_vPet[i]->getImage()->getFrameWidth(), battleMap->_vPet[i]->getImage()->getFrameHeight()));
		battleMap->_vPet[i]->setImageCenterX(battleMap->_vPet[i]->getTileCenterX() + battleMap->_vPet[i]->getImageMoveX());
		battleMap->_vPet[i]->setImageCenterY(battleMap->_vPet[i]->getTileCenterY() + battleMap->_vPet[i]->getImageMoveY());
		battleMap->_vPet[i]->setSelectRect(RectMakeCenter(battleMap->_vPet[i]->getTileCenterX() + battleMap->_vPet[i]->getImageMoveX(),
			battleMap->_vPet[i]->getTileCenterY() + battleMap->_vPet[i]->getImageMoveY(),
			battleMap->_vPet[i]->getImage()->getFrameWidth() / 2, battleMap->_vPet[i]->getImage()->getFrameHeight() / 2));
	}

	//플레이어가 공격당했을경우
	if (battleMap->_player->_isHurt == true)
	{
		if (battleMap->_player->getPlayerState() == STATE_HURT &&
			_isShortStop == false)
		{
			_pushPowerX -= 0.68f;
			_pushPowerY -= 0.5f;
			battleMap->_player->setPlayerCenterX(battleMap->_player->getPlayerCenterX() + _pushPowerX);
			battleMap->_player->setPlayerCenterY(battleMap->_player->getPlayerCenterY() + _pushPowerY);

			if (_pushPowerX <= 0 && _pushPowerY <= 0)
			{
				_pushPowerX = 8;
				_pushPowerY = 5.875f;
				_isShortStop = true;
			}
		}

		if (battleMap->_player->getPlayerState() == STATE_HURT)
		{
			if (_isShortStop == true)
			{
				_delayCount++;
				if (_delayCount >= 40)
				{
					_delayCount = 0;
					battleMap->_player->setPlayerState(STATE_STAND);
					_isShortStop = false;
				}
			}
		}


		if (battleMap->_player->getPlayerState() != STATE_HURT)
		{
			if (battleMap->_player->getPlayerCenterX() > battleMap->_player->getPlayerMoveEndX())
			{
				battleMap->_player->setPlayerCenterX(battleMap->_player->getPlayerCenterX() - battleMap->_moveSpeedX);
			}

			if (battleMap->_player->getPlayerCenterY() > battleMap->_player->getPlayerMoveEndY())
			{
				battleMap->_player->setPlayerCenterY(battleMap->_player->getPlayerCenterY() - battleMap->_moveSpeedY);
			}

			if (battleMap->_player->getPlayerCenterX() <= battleMap->_player->getPlayerMoveEndX())
			{
				battleMap->_player->setPlayerCenterX(battleMap->_player->getPlayerMoveEndX());
			}

			if (battleMap->_player->getPlayerCenterY() <= battleMap->_player->getPlayerMoveEndY())
			{
				battleMap->_player->setPlayerCenterY(battleMap->_player->getPlayerMoveEndY());
			}

			if (battleMap->_player->getPlayerCenterX() == battleMap->_player->getPlayerMoveEndX() &&
				battleMap->_player->getPlayerCenterY() == battleMap->_player->getPlayerMoveEndY())
			{
				battleMap->_player->setIsPlayerMove(false);
				battleMap->_player->_isHurt = false;
				battleMap->_player->setPlayerState(STATE_STAND);
			}

			else battleMap->_player->setIsPlayerMove(true);
		}

		battleMap->_player->setPlayerRect(RectMakeCenter(battleMap->_player->getPlayerCenterX() + battleMap->_player->getPlayerImageMoveX(),
			battleMap->_player->getPlayerCenterY() + battleMap->_player->getPlayerImageMoveY(),
			battleMap->_player->getPlayerImage()->getFrameWidth(), battleMap->_player->getPlayerImage()->getFrameHeight()));
		battleMap->_player->setPlayerImageCenterX(battleMap->_player->getPlayerCenterX() + battleMap->_player->getPlayerImageMoveX());
		battleMap->_player->setPlayerImageCenterY(battleMap->_player->getPlayerCenterY() + battleMap->_player->getPlayerImageMoveY());
		battleMap->_player->setPlayerTileRect(RectMakeCenter(battleMap->_player->getPlayerCenterX(), battleMap->_player->getPlayerCenterY(),
			64, 47));
		battleMap->_player->setSelectRect(RectMakeCenter(battleMap->_player->getPlayerCenterX() + battleMap->_player->getPlayerImageMoveX(),
			battleMap->_player->getPlayerCenterY() + battleMap->_player->getPlayerImageMoveY(),
			battleMap->_player->getPlayerImage()->getFrameWidth() / 2, battleMap->_player->getPlayerImage()->getFrameHeight() - 20));
	}
}

void battleTurn::catchBattle(battleMap * battleMap)
{
	if (battleMap->_player->getPlayerState() == STATE_ATTACK)
	{
		if (battleMap->_battleSelect == BATTLE_CATCH)
		{
			if (battleMap->_player->getPlayerCurrentFrameX() == 7)
			{
				for (int i = 0; i < battleMap->_vPet.size(); ++i)
				{
					if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;

					if (battleMap->_player->getAttackPointX() - 32 == battleMap->_vPet[i]->getTileCenterX() &&
						battleMap->_player->getAttackPointY() - 23.5f == battleMap->_vPet[i]->getTileCenterY())
					{
						//원래 있었던 장소 기억하기
						if (battleMap->_vPet[i]->_prePositionSave == false)
						{
							battleMap->_vPet[i]->_prePositionX = battleMap->_vPet[i]->getMoveEndX();
							battleMap->_vPet[i]->_prePositionY = battleMap->_vPet[i]->getMoveEndY();
							battleMap->_vPet[i]->_prePositionSave = true;
						}

						battleMap->_vPet[i]->setEnumPetState(PET_CATCHED);
						_isCatchSound = false;
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getEnumPetState() != PET_CATCHED) continue;

		float tempX = battleMap->_player->getPlayerCenterX() - 32;
		float tempY = battleMap->_player->getPlayerCenterY() - 23.5f;
		battleMap->_vPet[i]->setTileCenterX(tempX);
		battleMap->_vPet[i]->setTileCenterY(tempY);
		battleMap->_vPet[i]->setImageRect(RectMakeCenter(battleMap->_vPet[i]->getTileCenterX() + battleMap->_vPet[i]->getImageMoveX(),
			battleMap->_vPet[i]->getTileCenterY() + battleMap->_vPet[i]->getImageMoveY(),
			battleMap->_vPet[i]->getImage()->getFrameWidth(), battleMap->_vPet[i]->getImage()->getFrameHeight()));
		battleMap->_vPet[i]->setImageCenterX(battleMap->_vPet[i]->getTileCenterX() + battleMap->_vPet[i]->getImageMoveX());
		battleMap->_vPet[i]->setImageCenterY(battleMap->_vPet[i]->getTileCenterY() + battleMap->_vPet[i]->getImageMoveY());
		battleMap->_vPet[i]->setSelectRect(RectMakeCenter(battleMap->_vPet[i]->getTileCenterX() + battleMap->_vPet[i]->getImageMoveX(),
			battleMap->_vPet[i]->getTileCenterY() + battleMap->_vPet[i]->getImageMoveY(),
			battleMap->_vPet[i]->getImage()->getFrameWidth() / 2, battleMap->_vPet[i]->getImage()->getFrameHeight() / 2));
	}
}

void battleTurn::moveFrameY(battleMap * battleMap)
{
	//에너미 펫 무브시 Y값 설정하기
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;

		//공격이동시
		if (battleMap->_vPet[i]->getIsMove() == true)
		{
			//공격하러갈때
			if (battleMap->_vPet[i]->_isAttackTime == true &&
				battleMap->_vPet[i]->_isAttackClose == false)
			{
				//이동하려는 x값과는 같고, y값이 작은경우
				if (battleMap->_vPet[i]->getTileCenterX() == battleMap->_vPet[i]->getAttackPointX() &&
					battleMap->_vPet[i]->getTileCenterY() < battleMap->_vPet[i]->getAttackPointY())
				{
					battleMap->_vPet[i]->setPetDirection(DIR_SIX);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_SIX);
				}

				//이동하려는 y값과는 같고, x값이 작은경우
				else if (battleMap->_vPet[i]->getTileCenterX() < battleMap->_vPet[i]->getAttackPointX() &&
					battleMap->_vPet[i]->getTileCenterY() == battleMap->_vPet[i]->getAttackPointY())
				{
					battleMap->_vPet[i]->setPetDirection(DIR_THREE);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_THREE);
				}

				else if (battleMap->_vPet[i]->getTileCenterX() == battleMap->_vPet[i]->getAttackPointX() &&
					battleMap->_vPet[i]->getTileCenterY() == battleMap->_vPet[i]->getAttackPointY())
				{
					battleMap->_vPet[i]->setPetDirection(DIR_FIVE);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_FIVE);
				}
			}

			//공격이끝나고 돌아올때
			if (battleMap->_vPet[i]->_isAttackTime == true &&
				battleMap->_vPet[i]->_isAttackClose == true)
			{
				//이동하려는 x값과는 같고, y값이 큰경우
				if (battleMap->_vPet[i]->getTileCenterX() == battleMap->_vPet[i]->getMoveEndX() &&
					battleMap->_vPet[i]->getTileCenterY() > battleMap->_vPet[i]->getMoveEndY())
				{
					battleMap->_vPet[i]->setPetDirection(DIR_TWELVE);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_TWELVE);
				}

				//이동하려는 y값과는 같고, x값이 큰경우
				else if (battleMap->_vPet[i]->getTileCenterX() > battleMap->_vPet[i]->getMoveEndX() &&
					battleMap->_vPet[i]->getTileCenterY() == battleMap->_vPet[i]->getMoveEndY())
				{
					battleMap->_vPet[i]->setPetDirection(DIR_NINE);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_NINE);
				}

				else if (battleMap->_vPet[i]->getTileCenterX() == battleMap->_vPet[i]->getMoveEndX() &&
					battleMap->_vPet[i]->getTileCenterY() == battleMap->_vPet[i]->getMoveEndY())
				{
					battleMap->_vPet[i]->setPetDirection(DIR_FIVE);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_FIVE);
				}

				else
				{
					battleMap->_vPet[i]->setPetDirection(DIR_ELEVEN);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_ELEVEN);
				}
			}
		}
	}

	//펫 무브시 Y값 설정하기
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

		//공격이동시
		if (battleMap->_vPet[i]->getIsMove() == true)
		{
			//공격하러갈때
			if (battleMap->_vPet[i]->_isAttackTime == true &&
				battleMap->_vPet[i]->_isAttackClose == false)
			{
				//이동하려는 x값과는 같고, y값이 큰경우
				if (battleMap->_vPet[i]->getTileCenterX() == battleMap->_vPet[i]->getAttackPointX() &&
					battleMap->_vPet[i]->getTileCenterY() > battleMap->_vPet[i]->getAttackPointY())
				{
					battleMap->_vPet[i]->setPetDirection(DIR_TWELVE);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_TWELVE);
				}

				//이동하려는 y값과는 같고, x값이 큰은경우
				else if (battleMap->_vPet[i]->getTileCenterX() > battleMap->_vPet[i]->getAttackPointX() &&
					battleMap->_vPet[i]->getTileCenterY() == battleMap->_vPet[i]->getAttackPointY())
				{
					battleMap->_vPet[i]->setPetDirection(DIR_NINE);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_NINE);
				}

				else if (battleMap->_vPet[i]->getTileCenterX() == battleMap->_vPet[i]->getAttackPointX() &&
					battleMap->_vPet[i]->getTileCenterY() == battleMap->_vPet[i]->getAttackPointY())
				{
					battleMap->_vPet[i]->setPetDirection(DIR_ELEVEN);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_ELEVEN);
				}
			}

			//공격이끝나고 돌아올때
			if (battleMap->_vPet[i]->_isAttackTime == true &&
				battleMap->_vPet[i]->_isAttackClose == true)
			{
				//이동하려는 x값과는 같고, y값이 작은경우
				if (battleMap->_vPet[i]->getTileCenterX() == battleMap->_vPet[i]->getMoveEndX() &&
					battleMap->_vPet[i]->getTileCenterY() < battleMap->_vPet[i]->getMoveEndY())
				{
					battleMap->_vPet[i]->setPetDirection(DIR_SIX);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_SIX);
				}

				//이동하려는 y값과는 같고, x값이 작은경우
				else if (battleMap->_vPet[i]->getTileCenterX() < battleMap->_vPet[i]->getMoveEndX() &&
					battleMap->_vPet[i]->getTileCenterY() == battleMap->_vPet[i]->getMoveEndY())
				{
					battleMap->_vPet[i]->setPetDirection(DIR_THREE);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_THREE);
				}

				else if (battleMap->_vPet[i]->getTileCenterX() == battleMap->_vPet[i]->getMoveEndX() &&
					battleMap->_vPet[i]->getTileCenterY() == battleMap->_vPet[i]->getMoveEndY())
				{
					battleMap->_vPet[i]->setPetDirection(DIR_ELEVEN);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_ELEVEN);
				}

				else
				{
					battleMap->_vPet[i]->setPetDirection(DIR_FIVE);
					battleMap->_vPet[i]->setCurrentFrameY((int)DIR_FIVE);
				}
			}
		}
	}

	//플레이어 무브시 Y값 설정하기
	if (battleMap->_player->getIsPlayerMove() == true)
	{
		//공격하러갈때
		if (battleMap->_player->_isAttackTime == true &&
			battleMap->_player->_isAttackClose == false)
		{
			//이동하려는 x값과는 같고, y값이 큰경우
			if (battleMap->_player->getPlayerCenterX() == battleMap->_player->getAttackPointX() &&
				battleMap->_player->getPlayerCenterY() > battleMap->_player->getAttackPointY())
			{
				battleMap->_player->setPlayerDirection(DIR_TWELVE);
				battleMap->_player->setPlayerCurrentFrameY((int)DIR_TWELVE);
			}

			//이동하려는 y값과는 같고, x값이 큰은경우
			else if (battleMap->_player->getPlayerCenterX() > battleMap->_player->getAttackPointX() &&
				battleMap->_player->getPlayerCenterY() == battleMap->_player->getAttackPointY())
			{
				battleMap->_player->setPlayerDirection(DIR_NINE);
				battleMap->_player->setPlayerCurrentFrameY((int)DIR_NINE);
			}

			else if (battleMap->_player->getPlayerCenterX() == battleMap->_player->getAttackPointX() &&
				battleMap->_player->getPlayerCenterY() == battleMap->_player->getAttackPointY())
			{
				battleMap->_player->setPlayerDirection(DIR_ELEVEN);
				battleMap->_player->setPlayerCurrentFrameY((int)DIR_ELEVEN);
			}
		}

		//공격이끝나고 돌아올때
		if (battleMap->_player->_isAttackTime == true &&
			battleMap->_player->_isAttackClose == true)
		{
			//이동하려는 x값과는 같고, y값이 작은경우
			if (battleMap->_player->getPlayerCenterX() == battleMap->_player->getPlayerMoveEndX() &&
				battleMap->_player->getPlayerCenterY() < battleMap->_player->getPlayerMoveEndY())
			{
				battleMap->_player->setPlayerDirection(DIR_SIX);
				battleMap->_player->setPlayerCurrentFrameY((int)DIR_SIX);
			}

			//이동하려는 y값과는 같고, x값이 작은경우
			else if (battleMap->_player->getPlayerCenterX() < battleMap->_player->getPlayerMoveEndX() &&
				battleMap->_player->getPlayerCenterY() == battleMap->_player->getPlayerMoveEndY())
			{
				battleMap->_player->setPlayerDirection(DIR_THREE);
				battleMap->_player->setPlayerCurrentFrameY((int)DIR_THREE);
			}

			else if (battleMap->_player->getPlayerCenterX() == battleMap->_player->getPlayerMoveEndX() &&
				battleMap->_player->getPlayerCenterY() == battleMap->_player->getPlayerMoveEndY())
			{
				battleMap->_player->setPlayerDirection(DIR_ELEVEN);
				battleMap->_player->setPlayerCurrentFrameY((int)DIR_ELEVEN);
			}

			else
			{
				battleMap->_player->setPlayerDirection(DIR_FIVE);
				battleMap->_player->setPlayerCurrentFrameY((int)DIR_FIVE);
			}
		}
	}
}

//죽이기
void battleTurn::deadMotion(battleMap * battleMap)
{
	// 플레이어 죽었을경우 isDaed 불값 조금 늦게 발동시키기
	if (battleMap->_player->getPlayerState() == STATE_DEAD)
	{
		if (battleMap->_player->getPlayerCurrentFrameX() == battleMap->_player->getPlayerImage()->getMaxFrameX())
		{
			_deadCount++;
			if (_deadCount >= 20)
			{
				_deadCount = 0;
				battleMap->_player->_isDead = true;
			}
		}
	}

	//	플레이어가 죽었을경우
	if (battleMap->_playerInfo.currentStamina <= 0)
	{
		battleMap->_playerInfo.currentStamina = 0;

		if (battleMap->_player->getIsPlayerMove() == false &&
			battleMap->_player->getPlayerState() != STATE_HURT &&
			battleMap->_player->_isDead == false)
		{
			_delayCount++;
			if (_delayCount >= 10)
			{
				_delayCount = 0;
				battleMap->_player->setPlayerState(STATE_DEAD);
				battleMap->_player->_isAttacked = true;
				battleMap->_battleSelect = BATTLE_NONE;
				battleMap->_player->setAttackPointX(battleMap->_player->getPlayerCenterX());
				battleMap->_player->setAttackPointY(battleMap->_player->getPlayerCenterY());
			}
		}
	}

	// 플레이어 펫이 죽었을경우
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

		if (battleMap->_vPet[i]->getPetCurrentStamina() <= 0 &&
			battleMap->_vPet[i]->_isDead == false)
		{
			battleMap->_vPet[i]->setPetCurrentStamina(0);
			battleMap->_vPet[i]->_isDeadTime = true;

			if (battleMap->_vPet[i]->getIsMove() == false &&
				battleMap->_vPet[i]->getEnumPetState() != PET_HURT)
			{
				_delayCount++;
				if (_delayCount >= 10)
				{
					_delayCount = 0;
					battleMap->_vPet[i]->setEnumPetState(PET_DEAD);
					battleMap->_vPet[i]->_isAttacked = true;
					battleMap->_vPet[i]->_petSkill = PET_SKILL_NONE;
					battleMap->_vPet[i]->setAttackPointX(battleMap->_vPet[i]->getTileCenterX());
					battleMap->_vPet[i]->setAttackPointY(battleMap->_vPet[i]->getTileCenterY());
					battleMap->_vPet[i]->_isDead = true;
					battleMap->_vPet[i]->_isDeadTime = false;
				}
			}
		}
	}

	// 에너미가 죽었을경우
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;

		if (battleMap->_vPet[i]->getPetCurrentStamina() <= 0 &&
			battleMap->_vPet[i]->_isDead == false)
		{
			battleMap->_vPet[i]->setPetCurrentStamina(0);
			battleMap->_vPet[i]->_isDeadTime = true;

			if (battleMap->_vPet[i]->getIsMove() == false &&
				battleMap->_vPet[i]->getEnumPetState() != PET_HURT)
			{
				_delayCount++;
				if (_delayCount >= 10)
				{
					_delayCount = 0;
					battleMap->_vPet[i]->setEnumPetState(PET_DEAD);
					battleMap->_vPet[i]->_isAttacked = true;
					battleMap->_vPet[i]->_petSkill = PET_SKILL_NONE;
					battleMap->_vPet[i]->setAttackPointX(battleMap->_vPet[i]->getTileCenterX());
					battleMap->_vPet[i]->setAttackPointY(battleMap->_vPet[i]->getTileCenterY());
					battleMap->_vPet[i]->_isDead = true;
					battleMap->_vPet[i]->_isDeadTime = false;
				}
			}
		}
	}
}

//턴이 종료되지도 않은시점에서 에너미 또는 플레이어, 펫이 죽었거나 포획되었을경우 공격경로 수정
void battleTurn::attackSelectConvert(battleMap * battleMap)
{
	//플레이어가 죽었을경우 경로 수정(펫으로 경로수정)
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;

		if (battleMap->_player->_isDead == true)
		{
			if (battleMap->_vPet[i]->_isAttacked == false)
			{
				if (battleMap->_vPet[i]->getAttackPointX() + 32 == battleMap->_player->getPlayerCenterX() &&
					battleMap->_vPet[i]->getAttackPointY() + 23.5f == battleMap->_player->getPlayerCenterY())
				{
					for (int j = 0; j < battleMap->_vPet.size(); ++j)
					{
						if (battleMap->_vPet[j]->getIsPlayerPet() == false) continue;

						battleMap->_vPet[i]->setAttackPointX(battleMap->_vPet[j]->getTileCenterX() - 32);
						battleMap->_vPet[i]->setAttackPointY(battleMap->_vPet[j]->getTileCenterY() - 23.5f);
					}
				}
			}
		}
	}

	//펫이 죽었을경우 경로수정(플레이어로 경로수정)
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;

		for (int j = 0; j < battleMap->_vPet.size(); ++j)
		{
			if (battleMap->_vPet[j]->getIsPlayerPet() == false) continue;

			if (battleMap->_vPet[j]->_isDead == true)
			{
				if (battleMap->_vPet[i]->_isAttacked == false)
				{
					if (battleMap->_vPet[i]->getAttackPointX() + 32 == battleMap->_vPet[j]->getTileCenterX() &&
						battleMap->_vPet[i]->getAttackPointY() + 23.5f == battleMap->_vPet[j]->getTileCenterY())
					{
						battleMap->_vPet[i]->setAttackPointX(battleMap->_player->getPlayerCenterX() - 32);
						battleMap->_vPet[i]->setAttackPointY(battleMap->_player->getPlayerCenterY() - 23.5f);
						continue;
					}
				}
			}
		}
	}

	//선택한 에너미가 죽었을경우나 포획되었을경우 경로수정
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;

		if (battleMap->_vPet[i]->_isDead == true ||
			battleMap->_vPet[i]->_isCatched == true)
		{
			//먼저 플레이어가 이 펫을 공격로로 삼았을경우
			if (battleMap->_player->_isAttackTime == true)
			{
				if ((battleMap->_player->getAttackPointX() - 32 == battleMap->_vPet[i]->getTileCenterX() &&
					battleMap->_player->getAttackPointY() - 23.5f == battleMap->_vPet[i]->getTileCenterY()) ||
					(battleMap->_player->getAttackPointX() - 32  == battleMap->_vPet[i]->_prePositionX &&
						battleMap->_player->getAttackPointY() - 23.5f == battleMap->_vPet[i]->_prePositionY))
				{
					// 제 3의 공격타겟 랜덤으로 설정하기
					while (true)
					{
						int k = RND->getFromIntTo(0, battleMap->_vPet.size());
						if (battleMap->_vPet[i] == battleMap->_vPet[k]) continue;

						battleMap->_player->setAttackPointX(battleMap->_vPet[k]->getTileCenterX() + 32);
						battleMap->_player->setAttackPointY(battleMap->_vPet[k]->getTileCenterY() + 23.5f);
						break;
					}
				}
			}

			//플레이어 펫이 이 펫을 공격로로 삼았을경우
			for (int j = 0; j < battleMap->_vPet.size(); ++j)
			{
				if (battleMap->_vPet[j]->getIsPlayerPet() == false) continue;

				if (battleMap->_vPet[j]->_isAttackTime == true)
				{
					if ((battleMap->_vPet[j]->getAttackPointX() - 32 == battleMap->_vPet[i]->getTileCenterX() &&
						battleMap->_vPet[j]->getAttackPointY() - 23.5f == battleMap->_vPet[i]->getTileCenterY()) ||
						(battleMap->_vPet[j]->getAttackPointX() - 32 == battleMap->_vPet[i]->_prePositionX &&
							battleMap->_vPet[j]->getAttackPointY() - 23.5f == battleMap->_vPet[i]->_prePositionY))
					{
						// 제 3의 공격타겟 랜덤으로 설정하기
						while (true)
						{
							int k = RND->getFromIntTo(0, battleMap->_vPet.size());
							if (battleMap->_vPet[i] == battleMap->_vPet[k]) continue;

							battleMap->_vPet[j]->setAttackPointX(battleMap->_vPet[k]->getTileCenterX() + 32);
							battleMap->_vPet[j]->setAttackPointY(battleMap->_vPet[k]->getTileCenterY() + 23.5f);
							break;
						}
					}
				}
			}

		}
	}
}

void battleTurn::battleClosed(battleMap * battleMap)
{
	//플레이어가 죽거나, 적 펫을 모두 죽였거나
	if (battleMap->_player->_isDead == true ||
		battleMap->_player->_isEscapeSuccess == true)
	{
		battleMap->_battleTurn = TURN_CLOSE_BATTLE;
	}
}

void battleTurn::battleClosed2(battleMap * battleMap)
{
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;
		if (battleMap->_vPet[i]->_isDead == false) return;
	}

	if (_isbattleEnd == false) 	_isbattleEnd = true;

	_turnOffCount++;
	if (_turnOffCount >= 150)
	{
		battleMap->_battleTurn = TURN_CLOSE_BATTLE;
		_turnOffCount = 0;
	}

}

void battleTurn::happyTime(battleMap* battleMap)
{
	if (_isCatchCatch == false) return;
}
