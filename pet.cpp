#include "stdafx.h"
#include "pet.h"
#include "petStand.h"

void pet::InputHandle()
{
	petState* newType = _petState->inputHandle(this);
	if (newType != nullptr)
	{
		SAFE_DELETE(_petState);
		_petState = newType;
		_petState->enter(this);
	}
}

HRESULT pet::init()
{
	return S_OK;
}

HRESULT pet::init(POINT position, DIRECTION petDirection, PETSTATE petState, PETNAME petName, bool isPlayerPet)
{
	_currentFrameX = 0;
	_elapsedTime = 0;
	_elapsedSec = 0.15f;
	_petName = petName;
	_imageMoveX = 0;
	_imageMoveY = 0;
	_petDirection = petDirection;
	_currentFrameY = (int)petDirection;
	_isPlayerPet = isPlayerPet;
	_enumPetState = petState;
	_isMove = false;
	_prePositionX = 0;
	_prePositionY = 0;
	_prePositionSave = false;

	//ÆêÁ¾·ù¸¶´Ù ¼³Á¤ÇÏ±â
	setPetName();
	setPlayerPetName();
	_imageName = IMAGEMANAGER->findImage(_renderName);

	_tileCenterX = position.x;
	_tileCenterY = position.y;
	_imageCenterX = 0;
	_imageCenterY = 0;

	_moveEndX = 0;
	_moveEndY = 0;

	_imageRect = RectMakeCenter(_tileCenterX, _tileCenterY, _imageName->getFrameWidth(), _imageName->getFrameHeight());

	_selectRect = RectMakeCenter(_tileCenterX, _tileCenterY, _imageName->getFrameWidth() / 2, _imageName->getFrameHeight() / 2);

	_tileRect = RectMakeCenter(_tileCenterX, _tileCenterY, 64, 47);

	RENDERMANAGER->addObj("pet", _renderName.c_str(), &_tileCenterX, &_tileCenterY, &_imageCenterX, &_imageCenterY, &_currentFrameX, &_currentFrameY);

	_isBattleMode = false;
	_isRideMode = false;
	_elapsedSec = 0.11f;
	_isAttackTime = false;
	_isAttacked = false;
	_isAttackClose = false;
	_isHurt = false;
	_isDefenseOn = false;
	_damageCount = 0;
	_isDamaged = false;
	_damageTimeCount = 0;
	_isCatched = false;
	_isDead = false;
	_isDeadTime = false;

	_petState = new petStand();
	_petState->enter(this);

	return S_OK;
}

void pet::release()
{
	_petState->exit(this);
}

void pet::update()
{
	InputHandle();
	_petState->update(this);

	_elapsedTime += TIMEMANAGER->getElapsedTime();

	if (_elapsedTime >= _elapsedSec)
	{
		_elapsedTime -= _elapsedSec;

		if (_enumPetState != PET_CATCHED) 	_currentFrameX++;

		if (_enumPetState == PET_RUN || _enumPetState == PET_STAND)
		{
			if (_currentFrameX > _imageName->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
		}

		if (_enumPetState == PET_ATTACK || _enumPetState == PET_DEAD ||
			_enumPetState == PET_DEFENSE || _enumPetState == PET_HURT)
		{
			if (_currentFrameX > _imageName->getMaxFrameX())
			{
				_currentFrameX = _imageName->getMaxFrameX();
			}
		}
	}

	if (_isDamaged == true)
	{
		_damageTimeCount++;

		if (_damageTimeCount >= 40)
		{
			_damageTimeCount = 0;
			_isDamaged = false;
		}
	}

	_tileRect = RectMakeCenter(_tileCenterX, _tileCenterY, 64, 47);
	_imageRect = RectMakeCenter(_tileCenterX + _imageMoveX, _tileCenterY + _imageMoveY,
		_imageName->getFrameWidth(), _imageName->getFrameHeight());
	_imageCenterX = _tileCenterX + _imageMoveX;
	_imageCenterY = _tileCenterY + _imageMoveY;
	_selectRect = RectMakeCenter(_tileCenterX + _imageMoveX, _tileCenterY + _imageMoveY,
		_imageName->getFrameWidth() / 2, _imageName->getFrameHeight() / 2);
}

void pet::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _imageRect);
		Rectangle(getMemDC(), _selectRect);
		Rectangle(getMemDC(), _tileRect);
	}

	if (_isDefenseOn == true && _isDead == false)
	{
		IMAGEMANAGER->render("guard", getMemDC(), _selectRect.left, _selectRect.top - 20);
	}

	if (_isDamaged == true)
	{
		HFONT font = CreateFont(25, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("¸¼Àº°íµñ"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 20, 20));

		char damage[256];
		TextOut(getMemDC(), _selectRect.left + 25, _selectRect.top - 40 - _damageTimeCount,
			_itoa(_damageCount, damage, 10), strlen(_itoa(_damageCount, damage, 10)));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}
}

void pet::deletePet()
{
	RENDERMANAGER->deleteObj("pet", &_tileCenterX, &_tileCenterY);
}

void pet::setPetName()
{
	if (_isPlayerPet == true) return;

	_petLevel = 1;
	for (int i = 0; i < 6; ++i)
	{
		if (i == 0) _petSkillNum[0] = (int)PET_SKILL_ATTACK;
		if (i == 1) _petSkillNum[1] = (int)PET_SKILL_DEFENSE;
		if (i > 1)  _petSkillNum[i] = (int)PET_SKILL_NONE;
	}


	if (_petName == DURI)
	{
		_renderName = "duri_stand";
		_petNameString = "µÎ¸®";
		_attributeLandCount = 0;
		_attributeWaterCount = 4;
		_attributeFireCount = 6;
		_attributeWindCount = 0;
		_petAttackPower = RND->getFromIntTo(3, 8);
		_petDefensePower = RND->getFromIntTo(2, 6);
		_petSpeedPower = RND->getFromIntTo(3, 7);
		_petTotalStamina = RND->getFromIntTo(28, 38);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 5;
			_imageMoveY = -10.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 0;
			_imageMoveY = -10.5f;
		}
	}

	if (_petName == SPOTTEDURI)
	{
		_renderName = "spottedUri_stand";
		_petNameString = "¾ó·è¿ì¸®";
		_attributeLandCount = 10;
		_attributeWaterCount = 0;
		_attributeFireCount = 0;
		_attributeWindCount = 0;
		_petAttackPower = RND->getFromIntTo(2, 6);
		_petDefensePower = RND->getFromIntTo(2, 6);
		_petSpeedPower = RND->getFromIntTo(1, 5);
		_petTotalStamina = RND->getFromIntTo(19, 29);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 5;
			_imageMoveY = -10.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 0;
			_imageMoveY = -10.5f;
		}
	}

	if (_petName == URI)
	{
		_renderName = "uri_stand";
		_petNameString = "¿ì¸®";
		_attributeLandCount = 8;
		_attributeWaterCount = 2;
		_attributeFireCount = 0;
		_attributeWindCount = 0;
		_petAttackPower = RND->getFromIntTo(1, 3);
		_petDefensePower = RND->getFromIntTo(1, 3);
		_petSpeedPower = RND->getFromIntTo(1, 3);
		_petTotalStamina = RND->getFromIntTo(14, 20);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 5;
			_imageMoveY = -10.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 0;
			_imageMoveY = -10.5f;
		}
	}

	if (_petName == MAMONAS)
	{
		_renderName = "mamonas_stand";
		_petNameString = "¸¶¸ð³ª½º";
		_attributeLandCount = 7;
		_attributeWaterCount = 3;
		_attributeFireCount = 0;
		_attributeWindCount = 0;
		_petAttackPower = RND->getFromIntTo(6, 11);
		_petDefensePower = RND->getFromIntTo(4, 8);
		_petSpeedPower = RND->getFromIntTo(1, 5);
		_petTotalStamina = RND->getFromIntTo(60, 80);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 16;
			_imageMoveY = -10.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = -10;
			_imageMoveY = -35.5f;
		}
	}

	if (_petName == MANMO)
	{
		_renderName = "manmo_stand";
		_petNameString = "¸¸¸ð";
		_attributeLandCount = 9;
		_attributeWaterCount = 1;
		_attributeFireCount = 0;
		_attributeWindCount = 0;
		_petAttackPower = RND->getFromIntTo(7, 12);
		_petDefensePower = RND->getFromIntTo(5, 9);
		_petSpeedPower = RND->getFromIntTo(1, 5);
		_petTotalStamina = RND->getFromIntTo(60, 80);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 16;
			_imageMoveY = -10.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = -10;
			_imageMoveY = -35.5f;
		}
	}

	if (_petName == MANMOR)
	{
		_renderName = "manmor_stand";
		_petNameString = "¸¸¸ð¸£";
		_attributeLandCount = 0;
		_attributeWaterCount = 2;
		_attributeFireCount = 8;
		_attributeWindCount = 0;
		_petAttackPower = RND->getFromIntTo(6, 11);
		_petDefensePower = RND->getFromIntTo(4, 8);
		_petSpeedPower = RND->getFromIntTo(1, 5);
		_petTotalStamina = RND->getFromIntTo(55, 70);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 16;
			_imageMoveY = -10.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = -10;
			_imageMoveY = -35.5f;
		}
	}

	if (_petName == MOGAROS)
	{
		_renderName = "mogaros_stand";
		_petNameString = "¸ð°¡·Î½º";
		_attributeLandCount = 0;
		_attributeWaterCount = 2;
		_attributeFireCount = 8;
		_attributeWindCount = 0;
		_petAttackPower = RND->getFromIntTo(10, 15);
		_petDefensePower = RND->getFromIntTo(6, 10);
		_petSpeedPower = RND->getFromIntTo(5, 9);
		_petTotalStamina = RND->getFromIntTo(45, 60);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 8;
			_imageMoveY = -23.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}
	}

	if (_petName == OGAROS)
	{
		_renderName = "ogaros_stand";
		_petNameString = "¿À°¡·Î½º";
		_attributeLandCount = 6;
		_attributeWaterCount = 4;
		_attributeFireCount = 0;
		_attributeWindCount = 0;
		_petAttackPower = RND->getFromIntTo(7, 12);
		_petDefensePower = RND->getFromIntTo(7, 12);
		_petSpeedPower = RND->getFromIntTo(4, 8);
		_petTotalStamina = RND->getFromIntTo(43, 58);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 8;
			_imageMoveY = -23.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}
	}

	if (_petName == GORGOR)
	{
		_renderName = "gorgor_stand";
		_petNameString = "°í¸£°í¸£";
		_attributeLandCount = 0;
		_attributeWaterCount = 0;
		_attributeFireCount = 8;
		_attributeWindCount = 2;
		_petAttackPower = RND->getFromIntTo(5, 10);
		_petDefensePower = RND->getFromIntTo(3, 7);
		_petSpeedPower = RND->getFromIntTo(4, 8);
		_petTotalStamina = RND->getFromIntTo(30, 41);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = true;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = -8;
			_imageMoveY = -15.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 8;
			_imageMoveY = -15.5f;
		}
	}

	if (_petName == VERGA)
	{
		_renderName = "verga_stand";
		_petNameString = "º£¸£°¡";
		_attributeLandCount = 6;
		_attributeWaterCount = 4;
		_attributeFireCount = 0;
		_attributeWindCount = 0;
		_petAttackPower = RND->getFromIntTo(7, 12);
		_petDefensePower = RND->getFromIntTo(4, 8);
		_petSpeedPower = RND->getFromIntTo(5, 9);
		_petTotalStamina = RND->getFromIntTo(38, 50);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = true;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = -8;
			_imageMoveY = -15.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 8;
			_imageMoveY = -15.5f;
		}
	}

	if (_petName == VERURU)
	{
		_renderName = "veruru_stand";
		_petNameString = "º£·ç·ç";
		_attributeLandCount = 0;
		_attributeWaterCount = 7;
		_attributeFireCount = 3;
		_attributeWindCount = 0;
		_petAttackPower = RND->getFromIntTo(7, 12);
		_petDefensePower = RND->getFromIntTo(3, 7);
		_petSpeedPower = RND->getFromIntTo(5, 9);
		_petTotalStamina = RND->getFromIntTo(32, 48);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = -8;
			_imageMoveY = -15.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 8;
			_imageMoveY = -15.5f;
		}
	}

	if (_petName == BANBORO)
	{
		_renderName = "banboro_stand";
		_petNameString = "¹Ýº¸·Î";
		_attributeLandCount = 0;
		_attributeWaterCount = 0;
		_attributeFireCount = 5;
		_attributeWindCount = 5;
		_petAttackPower = RND->getFromIntTo(10, 14);
		_petDefensePower = RND->getFromIntTo(5, 9);
		_petSpeedPower = RND->getFromIntTo(4, 8);
		_petTotalStamina = RND->getFromIntTo(45, 60);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 16;
			_imageMoveY = -30.5f;
		}
	}

	if (_petName == BANGINO)
	{
		_renderName = "bangino_stand";
		_petNameString = "¹Ý±â³ë";
		_attributeLandCount = 0;
		_attributeWaterCount = 0;
		_attributeFireCount = 10;
		_attributeWindCount = 0;
		_petAttackPower = RND->getFromIntTo(10, 14);
		_petDefensePower = RND->getFromIntTo(5, 9);
		_petSpeedPower = RND->getFromIntTo(4, 8);
		_petTotalStamina = RND->getFromIntTo(42, 57);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 16;
			_imageMoveY = -30.5f;
		}
	}

	if (_petName == BURDON)
	{
		_renderName = "burdon_stand";
		_petNameString = "ºÎ¸£µ·";
		_attributeLandCount = 0;
		_attributeWaterCount = 0;
		_attributeFireCount = 2;
		_attributeWindCount = 8;
		_petAttackPower = RND->getFromIntTo(9, 13);
		_petDefensePower = RND->getFromIntTo(4, 8);
		_petSpeedPower = RND->getFromIntTo(5, 9);
		_petTotalStamina = RND->getFromIntTo(41, 56);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 16;
			_imageMoveY = -30.5f;
		}
	}

	if (_petName == RIBINO)
	{
		_renderName = "ribino_stand";
		_petNameString = "¸®ºñ³ë";
		_attributeLandCount = 10;
		_attributeWaterCount = 0;
		_attributeFireCount = 0;
		_attributeWindCount = 0;
		_petAttackPower = RND->getFromIntTo(8, 12);
		_petDefensePower = RND->getFromIntTo(5, 9);
		_petSpeedPower = RND->getFromIntTo(2, 6);
		_petTotalStamina = RND->getFromIntTo(38, 50);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 16;
			_imageMoveY = -30.5f;
		}
	}

	if (_petName == YANGIRO)
	{
		_renderName = "yangiro_stand";
		_petNameString = "¾á±â·Î";
		_attributeLandCount = 0;
		_attributeWaterCount = 3;
		_attributeFireCount = 7;
		_attributeWindCount = 0;
		_petAttackPower = RND->getFromIntTo(11, 15);
		_petDefensePower = RND->getFromIntTo(6, 10);
		_petSpeedPower = RND->getFromIntTo(5, 9);
		_petTotalStamina = RND->getFromIntTo(51, 65);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 16;
			_imageMoveY = -30.5f;
		}
	}

	if (_petName == NORNOR)
	{
		_renderName = "nornor_stand";
		_petNameString = "³ë¸£³ë¸£";
		_attributeLandCount = 3;
		_attributeWaterCount = 0;
		_attributeFireCount = 0;
		_attributeWindCount = 7;
		_petAttackPower = RND->getFromIntTo(7, 11);
		_petDefensePower = RND->getFromIntTo(5, 9);
		_petSpeedPower = RND->getFromIntTo(6, 10);
		_petTotalStamina = RND->getFromIntTo(38, 50);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = -8;
			_imageMoveY = -15.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 8;
			_imageMoveY = -15.5f;
		}
	}

	if (_petName == GOLROS)
	{
		_renderName = "golros_stand";
		_petNameString = "°ñ·Î½º";
		_attributeLandCount = 0;
		_attributeWaterCount = 0;
		_attributeFireCount = 5;
		_attributeWindCount = 5;
		_petAttackPower = RND->getFromIntTo(10, 15);
		_petDefensePower = RND->getFromIntTo(8, 12);
		_petSpeedPower = RND->getFromIntTo(5, 9);
		_petTotalStamina = RND->getFromIntTo(50, 63);
		_petCurrentStamina = _petTotalStamina;
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 8;
			_imageMoveY = -23.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}
	}
}

void pet::setPlayerPetName()
{
	if (_isPlayerPet == false) return;

	int loginPlayer1 = INIDATA->loadDataInterger("Ä³¸¯ÅÍ", "ÇÃ·¹ÀÌ¾î1", "·Î±×ÀÎ");
	int loginPlayer2 = INIDATA->loadDataInterger("Ä³¸¯ÅÍ", "ÇÃ·¹ÀÌ¾î2", "·Î±×ÀÎ");

	if (loginPlayer1 == (int)INFO_YES)
	{
		string pet1_mode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "¸ðµå");
		string pet2_mode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "¸ðµå");
		string pet3_mode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "¸ðµå");
		string pet4_mode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "¸ðµå");
		string pet5_mode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "¸ðµå");

		if (pet1_mode == "¹èÆ²")
		{
			_petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "·¹º§");
			_petNameString = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "ÀÌ¸§");
			_attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "Áö¼Ó¼º");
			_attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "¼ö¼Ó¼º");
			_attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "È­¼Ó¼º");
			_attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "Ç³¼Ó¼º");
			_petAttackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "°ø°Ý·Â");
			_petDefensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "¹æ¾î·Â");
			_petSpeedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "¼ø¹ß·Â");
			_petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "ÀüÃ¼Ã¼·Â");
			_petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "ÇöÀçÃ¼·Â");
			_petSkillNum[0] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "±â¼ú1");
			_petSkillNum[1] = INIDATA-> loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "±â¼ú2");
			_petSkillNum[2] = INIDATA-> loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "±â¼ú3");
			_petSkillNum[3] = INIDATA-> loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "±â¼ú4");
			_petSkillNum[4] = INIDATA-> loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "±â¼ú5");
			_petSkillNum[5] = INIDATA-> loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê1", "±â¼ú6");
		}

		if (pet2_mode == "¹èÆ²")
		{
			_petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "·¹º§");
			_petNameString = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "ÀÌ¸§");
			_attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "Áö¼Ó¼º");
			_attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "¼ö¼Ó¼º");
			_attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "È­¼Ó¼º");
			_attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "Ç³¼Ó¼º");
			_petAttackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "°ø°Ý·Â");
			_petDefensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "¹æ¾î·Â");
			_petSpeedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "¼ø¹ß·Â");
			_petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "ÀüÃ¼Ã¼·Â");
			_petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "ÇöÀçÃ¼·Â");
			_petSkillNum[0] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "±â¼ú1");
			_petSkillNum[1] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "±â¼ú2");
			_petSkillNum[2] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "±â¼ú3");
			_petSkillNum[3] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "±â¼ú4");
			_petSkillNum[4] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "±â¼ú5");
			_petSkillNum[5] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê2", "±â¼ú6");
		}

		if (pet3_mode == "¹èÆ²")
		{
			_petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "·¹º§");
			_petNameString = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "ÀÌ¸§");
			_attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "Áö¼Ó¼º");
			_attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "¼ö¼Ó¼º");
			_attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "È­¼Ó¼º");
			_attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "Ç³¼Ó¼º");
			_petAttackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "°ø°Ý·Â");
			_petDefensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "¹æ¾î·Â");
			_petSpeedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "¼ø¹ß·Â");
			_petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "ÀüÃ¼Ã¼·Â");
			_petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "ÇöÀçÃ¼·Â");
			_petSkillNum[0] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "±â¼ú1");
			_petSkillNum[1] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "±â¼ú2");
			_petSkillNum[2] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "±â¼ú3");
			_petSkillNum[3] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "±â¼ú4");
			_petSkillNum[4] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "±â¼ú5");
			_petSkillNum[5] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê3", "±â¼ú6");
		}

		if (pet4_mode == "¹èÆ²")
		{
			_petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "·¹º§");
			_petNameString = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "ÀÌ¸§");
			_attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "Áö¼Ó¼º");
			_attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "¼ö¼Ó¼º");
			_attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "È­¼Ó¼º");
			_attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "Ç³¼Ó¼º");
			_petAttackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "°ø°Ý·Â");
			_petDefensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "¹æ¾î·Â");
			_petSpeedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "¼ø¹ß·Â");
			_petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "ÀüÃ¼Ã¼·Â");
			_petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "ÇöÀçÃ¼·Â");
			_petSkillNum[0] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "±â¼ú1");
			_petSkillNum[1] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "±â¼ú2");
			_petSkillNum[2] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "±â¼ú3");
			_petSkillNum[3] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "±â¼ú4");
			_petSkillNum[4] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "±â¼ú5");
			_petSkillNum[5] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê4", "±â¼ú6");
		}

		if (pet5_mode == "¹èÆ²")
		{
			_petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "·¹º§");
			_petNameString = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "ÀÌ¸§");
			_attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "Áö¼Ó¼º");
			_attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "¼ö¼Ó¼º");
			_attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "È­¼Ó¼º");
			_attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "Ç³¼Ó¼º");
			_petAttackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "°ø°Ý·Â");
			_petDefensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "¹æ¾î·Â");
			_petSpeedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "¼ø¹ß·Â");
			_petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "ÀüÃ¼Ã¼·Â");
			_petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "ÇöÀçÃ¼·Â");
			_petSkillNum[0] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "±â¼ú1");
			_petSkillNum[1] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "±â¼ú2");
			_petSkillNum[2] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "±â¼ú3");
			_petSkillNum[3] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "±â¼ú4");
			_petSkillNum[4] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "±â¼ú5");
			_petSkillNum[5] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î1_Æê", "Æê5", "±â¼ú6");
		}
	}

	if (loginPlayer2 == (int)INFO_YES)
	{
		string pet1_mode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "¸ðµå");
		string pet2_mode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "¸ðµå");
		string pet3_mode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "¸ðµå");
		string pet4_mode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "¸ðµå");
		string pet5_mode = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "¸ðµå");


		if (pet1_mode == "¹èÆ²")
		{
			_petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "·¹º§");
			_petNameString = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "ÀÌ¸§");
			_attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "Áö¼Ó¼º");
			_attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "¼ö¼Ó¼º");
			_attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "È­¼Ó¼º");
			_attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "Ç³¼Ó¼º");
			_petAttackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "°ø°Ý·Â");
			_petDefensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "¹æ¾î·Â");
			_petSpeedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "¼ø¹ß·Â");
			_petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "ÀüÃ¼Ã¼·Â");
			_petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "ÇöÀçÃ¼·Â");
			_petSkillNum[0] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "±â¼ú1");
			_petSkillNum[1] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "±â¼ú2");
			_petSkillNum[2] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "±â¼ú3");
			_petSkillNum[3] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "±â¼ú4");
			_petSkillNum[4] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "±â¼ú5");
			_petSkillNum[5] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê1", "±â¼ú6");
		}

		if (pet2_mode == "¹èÆ²")
		{
			_petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "·¹º§");
			_petNameString = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "ÀÌ¸§");
			_attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "Áö¼Ó¼º");
			_attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "¼ö¼Ó¼º");
			_attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "È­¼Ó¼º");
			_attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "Ç³¼Ó¼º");
			_petAttackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "°ø°Ý·Â");
			_petDefensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "¹æ¾î·Â");
			_petSpeedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "¼ø¹ß·Â");
			_petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "ÀüÃ¼Ã¼·Â");
			_petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "ÇöÀçÃ¼·Â");
			_petSkillNum[0] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "±â¼ú1");
			_petSkillNum[1] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "±â¼ú2");
			_petSkillNum[2] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "±â¼ú3");
			_petSkillNum[3] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "±â¼ú4");
			_petSkillNum[4] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "±â¼ú5");
			_petSkillNum[5] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê2", "±â¼ú6");
		}

		if (pet3_mode == "¹èÆ²")
		{
			_petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "·¹º§");
			_petNameString = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "ÀÌ¸§");
			_attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "Áö¼Ó¼º");
			_attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "¼ö¼Ó¼º");
			_attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "È­¼Ó¼º");
			_attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "Ç³¼Ó¼º");
			_petAttackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "°ø°Ý·Â");
			_petDefensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "¹æ¾î·Â");
			_petSpeedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "¼ø¹ß·Â");
			_petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "ÀüÃ¼Ã¼·Â");
			_petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "ÇöÀçÃ¼·Â");
			_petSkillNum[0] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "±â¼ú1");
			_petSkillNum[1] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "±â¼ú2");
			_petSkillNum[2] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "±â¼ú3");
			_petSkillNum[3] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "±â¼ú4");
			_petSkillNum[4] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "±â¼ú5");
			_petSkillNum[5] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê3", "±â¼ú6");
		}

		if (pet4_mode == "¹èÆ²")
		{
			_petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "·¹º§");
			_petNameString = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "ÀÌ¸§");
			_attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "Áö¼Ó¼º");
			_attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "¼ö¼Ó¼º");
			_attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "È­¼Ó¼º");
			_attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "Ç³¼Ó¼º");
			_petAttackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "°ø°Ý·Â");
			_petDefensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "¹æ¾î·Â");
			_petSpeedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "¼ø¹ß·Â");
			_petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_ÀÌ¾î1_Æê", "Æê4", "ÀüÃ¼Ã¼·Â");
			_petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "ÇöÀçÃ¼·Â");
			_petSkillNum[0] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "±â¼ú1");
			_petSkillNum[1] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "±â¼ú2");
			_petSkillNum[2] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "±â¼ú3");
			_petSkillNum[3] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "±â¼ú4");
			_petSkillNum[4] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "±â¼ú5");
			_petSkillNum[5] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê4", "±â¼ú6");
		}

		if (pet5_mode == "¹èÆ²")
		{
			_petLevel = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "·¹º§");
			_petNameString = INIDATA->loadDataString("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "ÀÌ¸§");
			_attributeLandCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "Áö¼Ó¼º");
			_attributeWaterCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "¼ö¼Ó¼º");
			_attributeFireCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "È­¼Ó¼º");
			_attributeWindCount = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "Ç³¼Ó¼º");
			_petAttackPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "°ø°Ý·Â");
			_petDefensePower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "¹æ¾î·Â");
			_petSpeedPower = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "¼ø¹ß·Â");
			_petTotalStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "ÀüÃ¼Ã¼·Â");
			_petCurrentStamina = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "ÇöÀçÃ¼·Â");
			_petSkillNum[0] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "±â¼ú1");
			_petSkillNum[1] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "±â¼ú2");
			_petSkillNum[2] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "±â¼ú3");
			_petSkillNum[3] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "±â¼ú4");
			_petSkillNum[4] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "±â¼ú5");
			_petSkillNum[5] = INIDATA->loadDataInterger("ÇÃ·¹ÀÌ¾î2_Æê", "Æê5", "±â¼ú6");
		}
	}

	if (_petName == DURI)
	{
		_renderName = "duri_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 5;
			_imageMoveY = -10.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 0;
			_imageMoveY = -10.5f;
		}
	}

	if (_petName == SPOTTEDURI)
	{
		_renderName = "spottedUri_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 5;
			_imageMoveY = -10.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 0;
			_imageMoveY = -10.5f;
		}
	}

	if (_petName == URI)
	{
		_renderName = "uri_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 5;
			_imageMoveY = -10.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 0;
			_imageMoveY = -10.5f;
		}
	}

	if (_petName == MAMONAS)
	{
		_renderName = "mamonas_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 16;
			_imageMoveY = -10.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = -10;
			_imageMoveY = -35.5f;
		}
	}

	if (_petName == MANMO)
	{
		_renderName = "manmo_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 16;
			_imageMoveY = -10.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = -10;
			_imageMoveY = -35.5f;
		}
	}

	if (_petName == MANMOR)
	{
		_renderName = "manmor_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 16;
			_imageMoveY = -10.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = -10;
			_imageMoveY = -35.5f;
		}
	}

	if (_petName == MOGAROS)
	{
		_renderName = "mogaros_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 8;
			_imageMoveY = -23.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}
	}

	if (_petName == OGAROS)
	{
		_renderName = "ogaros_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 8;
			_imageMoveY = -23.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}
	}

	if (_petName == GORGOR)
	{
		_renderName = "gorgor_stand";
		_isAvailableRide = true;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = -8;
			_imageMoveY = -15.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 8;
			_imageMoveY = -15.5f;
		}
	}

	if (_petName == VERGA)
	{
		_renderName = "verga_stand";
		_isAvailableRide = true;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = -8;
			_imageMoveY = -15.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 8;
			_imageMoveY = -15.5f;
		}
	}

	if (_petName == VERURU)
	{
		_renderName = "veruru_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = -8;
			_imageMoveY = -15.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 8;
			_imageMoveY = -15.5f;
		}
	}

	if (_petName == BANBORO)
	{
		_renderName = "banboro_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 16;
			_imageMoveY = -30.5f;
		}
	}

	if (_petName == BANGINO)
	{
		_renderName = "bangino_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 16;
			_imageMoveY = -30.5f;
		}
	}

	if (_petName == BURDON)
	{
		_renderName = "burdon_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 16;
			_imageMoveY = -30.5f;
		}
	}

	if (_petName == RIBINO)
	{
		_renderName = "ribino_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 16;
			_imageMoveY = -30.5f;
		}
	}

	if (_petName == YANGIRO)
	{
		_renderName = "yangiro_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 16;
			_imageMoveY = -30.5f;
		}
	}

	if (_petName == NORNOR)
	{
		_renderName = "nornor_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = -8;
			_imageMoveY = -15.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 8;
			_imageMoveY = -15.5f;
		}
	}

	if (_petName == GOLROS)
	{
		_renderName = "golros_stand";
		_isAvailableRide = false;

		if (_petDirection == DIR_FIVE)
		{
			_imageMoveX = 8;
			_imageMoveY = -23.5f;
		}

		if (_petDirection == DIR_ELEVEN)
		{
			_imageMoveX = 0;
			_imageMoveY = -30.5f;
		}
	}
}
