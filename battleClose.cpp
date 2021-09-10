#include "stdafx.h"
#include "gameNode.h"
#include "battleMap.h"
#include "playerTurn.h"
#include "battleAppear.h"
#include "petTurn.h"
#include "battleTurn.h"
#include "battleClose.h"

battleState * battleClose::inputHandle(battleMap * battleMap)
{
	if (_elapsedSec >= 5)
	{
		_elapsedSec = 0;
		RENDERMANAGER->deleteAll();
		SOUNDMANAGER->play("dungeon1_bg", 0.4f);
		SCENEMANAGER->changeScene("던전1");
	}

	return nullptr;
}

void battleClose::update(battleMap * battleMap)
{
	convertText();
	saveInidata(battleMap);
}

void battleClose::enter(battleMap * battleMap)
{	
	SOUNDMANAGER->play("scene_start", 0.4f);
	SOUNDMANAGER->stop("battle1_bg");
	SOUNDMANAGER->stop("battle2_bg");

	_closeNotice.backImg = IMAGEMANAGER->findImage("inputWindowBack");
	_closeNotice.frontImg = IMAGEMANAGER->findImage("inputWindow2");
	_closeNotice.backRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2,
		_closeNotice.backImg->getWidth(), _closeNotice.backImg->getHeight());
	_closeNotice.frontRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2,
		_closeNotice.frontImg->getWidth(), _closeNotice.frontImg->getHeight());
	_closeNotice.noticeText = "사냥 종료";

	_worldTime = TIMEMANAGER->getWorldTime();
	_elapsedSec = 0;
	_moveText = 60;
	_isSave = false;
	for (int i = 0; i < 5; ++i) _isSavePet[i] = false;
}

void battleClose::render(battleMap * battleMap)
{
	IMAGEMANAGER->render("battleClose", getMemDC(), 0, 0);

	_closeNotice.backImg->alphaRender(getMemDC(), _closeNotice.backRect.left, _closeNotice.backRect.top, 200);
	_closeNotice.frontImg->render(getMemDC(), _closeNotice.frontRect.left, _closeNotice.frontRect.top);
	noticeRender();
}

void battleClose::exit(battleMap * battleMap)
{
}

void battleClose::noticeRender()
{
	HFONT font = CreateFont(25, 0, 0, 0, 600, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY목각파임B"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	TextOut(getMemDC(), (_closeNotice.frontRect.left + _closeNotice.frontRect.right) / 2 - _moveText,
		(_closeNotice.frontRect.top + _closeNotice.frontRect.bottom) / 2 - 12.5f,
		_closeNotice.noticeText.c_str(), strlen(_closeNotice.noticeText.c_str()));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	SetBkMode(getMemDC(), OPAQUE);
}

void battleClose::convertText()
{
	if (TIMEMANAGER->getWorldTime() - _worldTime >= 1)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
		_elapsedSec++;
	}

	if (_elapsedSec >= 2)
	{
		if (_elapsedSec % 3 == 1) _closeNotice.noticeText = "변경사항 저장중.";
		if (_elapsedSec % 3 == 2) _closeNotice.noticeText = "변경사항 저장중..";
		if (_elapsedSec % 3 == 0) _closeNotice.noticeText = "변경사항 저장중...";
		_moveText = 110;
	}
}

void battleClose::saveInidata(battleMap * battleMap)
{
	if (_isSave == true) return;

	//플레이어부터 저장
	int loginPlayer1 = INIDATA->loadDataInterger("캐릭터", "플레이어1", "로그인");
	int loginPlayer2 = INIDATA->loadDataInterger("캐릭터", "플레이어2", "로그인");

	//플레이어1 로그인했을경우
	if (loginPlayer1 == (int)INFO_YES)
	{
		char currentStamina[256];

		if (battleMap->_player->_isDead == true)
		{
			INIDATA->addData("플레이어1", "현재체력", _itoa(1, currentStamina, 10));
			int charming = INIDATA->loadDataInterger("캐릭터", "플레이어1", "매력");
			charming -= 4;
			char charm[256];
			INIDATA->addData("플레이어1", "매력", _itoa(charming, charm, 10));
		}

		else
		{
			INIDATA->addData("플레이어1", "현재체력", _itoa(battleMap->_playerInfo.currentStamina, currentStamina, 10));
		}

		INIDATA->iniSave("캐릭터");
	}

	//플레이어2 로그인했을경우
	if (loginPlayer1 == (int)INFO_YES)
	{
		char currentStamina[256];

		if (battleMap->_player->_isDead == true)
		{
			INIDATA->addData("플레이어2", "현재체력", _itoa(1, currentStamina, 10));
			int charming = INIDATA->loadDataInterger("캐릭터", "플레이어2", "매력");
			charming -= 4;
			char charm[256];
			INIDATA->addData("플레이어2", "매력", _itoa(charming, charm, 10));
		}

		else
		{
			INIDATA->addData("플레이어2", "현재체력", _itoa(battleMap->_playerInfo.currentStamina, currentStamina, 10));
		}

		INIDATA->iniSave("캐릭터");
	}

	//플레이어 펫 저장
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

		//플레이어 1 펫일 경우
		if (loginPlayer1 == (int)INFO_YES)
		{
			string pet1_mode = INIDATA->loadDataString("플레이어1_펫", "펫1", "모드");
			string pet2_mode = INIDATA->loadDataString("플레이어1_펫", "펫2", "모드");
			string pet3_mode = INIDATA->loadDataString("플레이어1_펫", "펫3", "모드");
			string pet4_mode = INIDATA->loadDataString("플레이어1_펫", "펫4", "모드");
			string pet5_mode = INIDATA->loadDataString("플레이어1_펫", "펫5", "모드");

			if (pet1_mode == "배틀")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("펫1", "모드", "휴식");
					INIDATA->addData("펫1", "현재체력", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("플레이어1_펫", "펫1", "충성도");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("펫1", "충성도", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("펫1", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet2_mode == "배틀")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("펫2", "모드", "휴식");
					INIDATA->addData("펫2", "현재체력", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("플레이어1_펫", "펫2", "충성도");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("펫2", "충성도", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("펫2", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet3_mode == "배틀")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("펫3", "모드", "휴식");
					INIDATA->addData("펫3", "현재체력", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("플레이어1_펫", "펫3", "충성도");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("펫3", "충성도", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("펫3", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet4_mode == "배틀")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("펫4", "모드", "휴식");
					INIDATA->addData("펫4", "현재체력", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("플레이어1_펫", "펫4", "충성도");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("펫4", "충성도", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("펫4", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet5_mode == "배틀")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("펫5", "모드", "휴식");
					INIDATA->addData("펫5", "현재체력", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("플레이어1_펫", "펫5", "충성도");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("펫5", "충성도", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("펫5", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			INIDATA->iniSave("플레이어1_펫");
		}

		//플레이어 1 펫일 경우
		if (loginPlayer2 == (int)INFO_YES)
		{
			string pet1_mode = INIDATA->loadDataString("플레이어2_펫", "펫1", "모드");
			string pet2_mode = INIDATA->loadDataString("플레이어2_펫", "펫2", "모드");
			string pet3_mode = INIDATA->loadDataString("플레이어2_펫", "펫3", "모드");
			string pet4_mode = INIDATA->loadDataString("플레이어2_펫", "펫4", "모드");
			string pet5_mode = INIDATA->loadDataString("플레이어2_펫", "펫5", "모드");

			if (pet1_mode == "배틀")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("펫1", "모드", "휴식");
					INIDATA->addData("펫1", "현재체력", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("플레이어2_펫", "펫1", "충성도");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("펫1", "충성도", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("펫1", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet2_mode == "배틀")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("펫2", "모드", "휴식");
					INIDATA->addData("펫2", "현재체력", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("플레이어2_펫", "펫2", "충성도");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("펫2", "충성도", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("펫2", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet3_mode == "배틀")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("펫3", "모드", "휴식");
					INIDATA->addData("펫3", "현재체력", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("플레이어2_펫", "펫3", "충성도");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("펫3", "충성도", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("펫3", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet4_mode == "배틀")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("펫4", "모드", "휴식");
					INIDATA->addData("펫4", "현재체력", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("플레이어2_펫", "펫4", "충성도");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("펫4", "충성도", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("펫4", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet5_mode == "배틀")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("펫5", "모드", "휴식");
					INIDATA->addData("펫5", "현재체력", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("플레이어2_펫", "펫5", "충성도");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("펫5", "충성도", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("펫5", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}


			INIDATA->iniSave("플레이어2_펫");
		}
	}

	//혹시 펫을 포획했을경우 등록해준다! ㅎㅎ
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_player->_isEscapeSuccess == true) break;
		if (battleMap->_player->_isDead == true) break;
		if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;
		if (battleMap->_vPet[i]->_isCatched == false) continue;

		//플레이어 1일 경우
		if (loginPlayer1 == (int)INFO_YES)
		{
			string pet1_exist = INIDATA->loadDataString("플레이어1_펫", "펫1", "있어?");
			string pet2_exist = INIDATA->loadDataString("플레이어1_펫", "펫2", "있어?");
			string pet3_exist = INIDATA->loadDataString("플레이어1_펫", "펫3", "있어?");
			string pet4_exist = INIDATA->loadDataString("플레이어1_펫", "펫4", "있어?");
			string pet5_exist = INIDATA->loadDataString("플레이어1_펫", "펫5", "있어?");

			//첫번째 펫창이 비어있을경우
			if (pet1_exist != "있어" && _isSavePet[0] == false)
			{
				char type[256];
				INIDATA->addData("펫1", "종류", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("펫1", "레벨", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("펫1", "현재경험치", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("펫1", "다음경험치", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("펫1", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("펫1", "공격력", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("펫1", "방어력", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("펫1", "순발력", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("펫1", "충성도", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("펫1", "지속성", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("펫1", "수속성", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("펫1", "화속성", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("펫1", "풍속성", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("펫1", "있어?", "있어");
				INIDATA->addData("펫1", "모드", "휴식");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("펫1", "이름", name);
				char totalStamina[256];
				INIDATA->addData("펫1", "전체체력", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("펫1", "스킬1", "공격");
				INIDATA->addData("펫1", "스킬2", "방어");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("펫1", "탑승가능", "가능");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("펫1", "탑승가능", "불가능");
				char skill1[256];
				INIDATA->addData("펫1", "기술1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("펫1", "기술2", _itoa(2, skill2, 10));
				INIDATA->iniSave("플레이어1_펫");
				_isSavePet[0] = true;
				continue;
			}

			//두번째 펫창이 비어있을경우
			if (pet2_exist != "있어" && _isSavePet[1] == false)
			{
				char type[256];
				INIDATA->addData("펫2", "종류", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("펫2", "레벨", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("펫2", "현재경험치", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("펫2", "다음경험치", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("펫2", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("펫2", "공격력", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("펫2", "방어력", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("펫2", "순발력", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("펫2", "충성도", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("펫2", "지속성", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("펫2", "수속성", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("펫2", "화속성", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("펫2", "풍속성", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("펫2", "있어?", "있어");
				INIDATA->addData("펫2", "모드", "휴식");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("펫2", "이름", name);
				char totalStamina[256];
				INIDATA->addData("펫2", "전체체력", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("펫2", "스킬1", "공격");
				INIDATA->addData("펫2", "스킬2", "방어");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("펫2", "탑승가능", "가능");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("펫2", "탑승가능", "불가능");
				char skill1[256];
				INIDATA->addData("펫2", "기술1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("펫2", "기술2", _itoa(2, skill2, 10));
				INIDATA->iniSave("플레이어1_펫");
				_isSavePet[1] = true;
				continue;
			}

			//세번째 펫창이 비어있을경우
			if (pet3_exist != "있어" && _isSavePet[2] == false)
			{
				char type[256];
				INIDATA->addData("펫3", "종류", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("펫3", "레벨", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("펫3", "현재경험치", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("펫3", "다음경험치", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("펫3", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("펫3", "공격력", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("펫3", "방어력", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("펫3", "순발력", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("펫3", "충성도", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("펫3", "지속성", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("펫3", "수속성", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("펫3", "화속성", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("펫3", "풍속성", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("펫3", "있어?", "있어");
				INIDATA->addData("펫3", "모드", "휴식");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("펫3", "이름", name);
				char totalStamina[256];
				INIDATA->addData("펫3", "전체체력", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("펫3", "스킬1", "공격");
				INIDATA->addData("펫3", "스킬2", "방어");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("펫3", "탑승가능", "가능");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("펫3", "탑승가능", "불가능");
				char skill1[256];
				INIDATA->addData("펫3", "기술1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("펫3", "기술2", _itoa(2, skill2, 10));
				INIDATA->iniSave("플레이어1_펫");
				_isSavePet[2] = true;
				continue;
			}

			//네번째 펫창이 비어있을경우
			if (pet4_exist != "있어" && _isSavePet[3] == false)
			{
				char type[256];
				INIDATA->addData("펫4", "종류", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("펫4", "레벨", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("펫4", "현재경험치", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("펫4", "다음경험치", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("펫4", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("펫4", "공격력", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("펫4", "방어력", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("펫4", "순발력", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("펫4", "충성도", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("펫4", "지속성", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("펫4", "수속성", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("펫4", "화속성", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("펫4", "풍속성", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("펫4", "있어?", "있어");
				INIDATA->addData("펫4", "모드", "휴식");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("펫4", "이름", name);
				char totalStamina[256];
				INIDATA->addData("펫4", "전체체력", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("펫4", "스킬1", "공격");
				INIDATA->addData("펫4", "스킬2", "방어");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("펫4", "탑승가능", "가능");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("펫4", "탑승가능", "불가능");
				char skill1[256];
				INIDATA->addData("펫4", "기술1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("펫4", "기술2", _itoa(2, skill2, 10));
				INIDATA->iniSave("플레이어1_펫");
				_isSavePet[3] = true;
				continue;
			}

			//다섯번째 펫창이 비어있을경우
			if (pet5_exist != "있어" && _isSavePet[4] == false)
			{
				char type[256];
				INIDATA->addData("펫5", "종류", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("펫5", "레벨", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("펫5", "현재경험치", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("펫5", "다음경험치", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("펫5", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("펫5", "공격력", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("펫5", "방어력", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("펫5", "순발력", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("펫5", "충성도", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("펫5", "지속성", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("펫5", "수속성", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("펫5", "화속성", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("펫5", "풍속성", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("펫5", "있어?", "있어");
				INIDATA->addData("펫5", "모드", "휴식");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("펫5", "이름", name);
				char totalStamina[256];
				INIDATA->addData("펫5", "전체체력", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("펫5", "스킬1", "공격");
				INIDATA->addData("펫5", "스킬2", "방어");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("펫5", "탑승가능", "가능");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("펫5", "탑승가능", "불가능");
				char skill1[256];
				INIDATA->addData("펫5", "기술1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("펫5", "기술2", _itoa(2, skill2, 10));
				INIDATA->iniSave("플레이어1_펫");
				_isSavePet[4] = true;
				continue;
			}
		}

		//플레이어 2일 경우
		if (loginPlayer1 == (int)INFO_YES)
		{
			string pet1_exist = INIDATA->loadDataString("플레이어2_펫", "펫1", "있어?");
			string pet3_exist = INIDATA->loadDataString("플레이어2_펫", "펫3", "있어?");
			string pet2_exist = INIDATA->loadDataString("플레이어2_펫", "펫2", "있어?");
			string pet4_exist = INIDATA->loadDataString("플레이어2_펫", "펫4", "있어?");
			string pet5_exist = INIDATA->loadDataString("플레이어2_펫", "펫5", "있어?");

			//첫번째 펫창이 비어있을경우
			if (pet1_exist != "있어" && _isSavePet[0] == false)
			{
				char type[256];
				INIDATA->addData("펫1", "종류", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("펫1", "레벨", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("펫1", "현재경험치", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("펫1", "다음경험치", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("펫1", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("펫1", "공격력", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("펫1", "방어력", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("펫1", "순발력", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("펫1", "충성도", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("펫1", "지속성", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("펫1", "수속성", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("펫1", "화속성", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("펫1", "풍속성", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("펫1", "있어?", "있어");
				INIDATA->addData("펫1", "모드", "휴식");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("펫1", "이름", name);
				char totalStamina[256];
				INIDATA->addData("펫1", "전체체력", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("펫1", "스킬1", "공격");
				INIDATA->addData("펫1", "스킬2", "방어");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("펫1", "탑승가능", "가능");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("펫1", "탑승가능", "불가능");
				char skill1[256];
				INIDATA->addData("펫1", "기술1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("펫1", "기술2", _itoa(2, skill2, 10));
				INIDATA->iniSave("플레이어2_펫");
				_isSavePet[0] = true;
				continue;
			}

			//두번째 펫창이 비어있을경우
			if (pet2_exist != "있어" && _isSavePet[1] == false)
			{
				char type[256];
				INIDATA->addData("펫2", "종류", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("펫2", "레벨", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("펫2", "현재경험치", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("펫2", "다음경험치", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("펫2", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("펫2", "공격력", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("펫2", "방어력", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("펫2", "순발력", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("펫2", "충성도", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("펫2", "지속성", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("펫2", "수속성", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("펫2", "화속성", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("펫2", "풍속성", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("펫2", "있어?", "있어");
				INIDATA->addData("펫2", "모드", "휴식");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("펫2", "이름", name);
				char totalStamina[256];
				INIDATA->addData("펫2", "전체체력", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("펫2", "스킬1", "공격");
				INIDATA->addData("펫2", "스킬2", "방어");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("펫2", "탑승가능", "가능");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("펫2", "탑승가능", "불가능");
				char skill1[256];
				INIDATA->addData("펫2", "기술1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("펫2", "기술2", _itoa(2, skill2, 10));
				INIDATA->iniSave("플레이어2_펫");
				_isSavePet[1] = true;
				continue;
			}

			//세번째 펫창이 비어있을경우
			if (pet2_exist != "있어" && _isSavePet[2] == false)
			{
				char type[256];
				INIDATA->addData("펫3", "종류", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("펫3", "레벨", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("펫3", "현재경험치", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("펫3", "다음경험치", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("펫3", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("펫3", "공격력", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("펫3", "방어력", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("펫3", "순발력", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("펫3", "충성도", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("펫3", "지속성", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("펫3", "수속성", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("펫3", "화속성", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("펫3", "풍속성", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("펫3", "있어?", "있어");
				INIDATA->addData("펫3", "모드", "휴식");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("펫3", "이름", name);
				char totalStamina[256];
				INIDATA->addData("펫3", "전체체력", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("펫3", "스킬1", "공격");
				INIDATA->addData("펫3", "스킬2", "방어");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("펫3", "탑승가능", "가능");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("펫3", "탑승가능", "불가능");
				char skill1[256];
				INIDATA->addData("펫3", "기술1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("펫3", "기술2", _itoa(2, skill2, 10));
				INIDATA->iniSave("플레이어2_펫");
				_isSavePet[2] = true;
				continue;
			}

			//네번째 펫창이 비어있을경우
			if (pet2_exist != "있어" && _isSavePet[3] == false)
			{
				char type[256];
				INIDATA->addData("펫4", "종류", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("펫4", "레벨", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("펫4", "현재경험치", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("펫4", "다음경험치", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("펫4", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("펫4", "공격력", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("펫4", "방어력", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("펫4", "순발력", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("펫4", "충성도", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("펫4", "지속성", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("펫4", "수속성", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("펫4", "화속성", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("펫4", "풍속성", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("펫4", "있어?", "있어");
				INIDATA->addData("펫4", "모드", "휴식");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("펫4", "이름", name);
				char totalStamina[256];
				INIDATA->addData("펫4", "전체체력", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("펫4", "스킬1", "공격");
				INIDATA->addData("펫4", "스킬2", "방어");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("펫4", "탑승가능", "가능");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("펫4", "탑승가능", "불가능");
				char skill1[256];
				INIDATA->addData("펫4", "기술1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("펫4", "기술2", _itoa(2, skill2, 10));
				INIDATA->iniSave("플레이어2_펫");
				_isSavePet[3] = true;
				continue;
			}

			//다섯번째 펫창이 비어있을경우
			if (pet2_exist != "있어" && _isSavePet[4] == false)
			{
				char type[256];
				INIDATA->addData("펫5", "종류", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("펫5", "레벨", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("펫5", "현재경험치", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("펫5", "다음경험치", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("펫5", "현재체력", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("펫5", "공격력", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("펫5", "방어력", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("펫5", "순발력", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("펫5", "충성도", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("펫5", "지속성", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("펫5", "수속성", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("펫5", "화속성", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("펫5", "풍속성", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("펫5", "있어?", "있어");
				INIDATA->addData("펫5", "모드", "휴식");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("펫5", "이름", name);
				char totalStamina[256];
				INIDATA->addData("펫5", "전체체력", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("펫5", "스킬1", "공격");
				INIDATA->addData("펫5", "스킬2", "방어");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("펫5", "탑승가능", "가능");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("펫5", "탑승가능", "불가능");
				char skill1[256];
				INIDATA->addData("펫5", "기술1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("펫5", "기술2", _itoa(2, skill2, 10));
				INIDATA->iniSave("플레이어2_펫");
				_isSavePet[4] = true;
				continue;
			}
		}
	}

	_isSave = true;
}
