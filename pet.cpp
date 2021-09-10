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

	//���������� �����ϱ�
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
			0, 0, 0, 0, TEXT("�������"));
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
		_petNameString = "�θ�";
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
		_petNameString = "���츮";
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
		_petNameString = "�츮";
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
		_petNameString = "���𳪽�";
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
		_petNameString = "����";
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
		_petNameString = "����";
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
		_petNameString = "�𰡷ν�";
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
		_petNameString = "�����ν�";
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
		_petNameString = "����";
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
		_petNameString = "������";
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
		_petNameString = "�����";
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
		_petNameString = "�ݺ���";
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
		_petNameString = "�ݱ��";
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
		_petNameString = "�θ���";
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
		_petNameString = "�����";
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
		_petNameString = "����";
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
		_petNameString = "�븣�븣";
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
		_petNameString = "��ν�";
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

	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	if (loginPlayer1 == (int)INFO_YES)
	{
		string pet1_mode = INIDATA->loadDataString("�÷��̾�1_��", "��1", "���");
		string pet2_mode = INIDATA->loadDataString("�÷��̾�1_��", "��2", "���");
		string pet3_mode = INIDATA->loadDataString("�÷��̾�1_��", "��3", "���");
		string pet4_mode = INIDATA->loadDataString("�÷��̾�1_��", "��4", "���");
		string pet5_mode = INIDATA->loadDataString("�÷��̾�1_��", "��5", "���");

		if (pet1_mode == "��Ʋ")
		{
			_petLevel = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "����");
			_petNameString = INIDATA->loadDataString("�÷��̾�1_��", "��1", "�̸�");
			_attributeLandCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "���Ӽ�");
			_attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "���Ӽ�");
			_attributeFireCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "ȭ�Ӽ�");
			_attributeWindCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "ǳ�Ӽ�");
			_petAttackPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "���ݷ�");
			_petDefensePower = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "����");
			_petSpeedPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "���߷�");
			_petTotalStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "��üü��");
			_petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "����ü��");
			_petSkillNum[0] = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "���1");
			_petSkillNum[1] = INIDATA-> loadDataInterger("�÷��̾�1_��", "��1", "���2");
			_petSkillNum[2] = INIDATA-> loadDataInterger("�÷��̾�1_��", "��1", "���3");
			_petSkillNum[3] = INIDATA-> loadDataInterger("�÷��̾�1_��", "��1", "���4");
			_petSkillNum[4] = INIDATA-> loadDataInterger("�÷��̾�1_��", "��1", "���5");
			_petSkillNum[5] = INIDATA-> loadDataInterger("�÷��̾�1_��", "��1", "���6");
		}

		if (pet2_mode == "��Ʋ")
		{
			_petLevel = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "����");
			_petNameString = INIDATA->loadDataString("�÷��̾�1_��", "��2", "�̸�");
			_attributeLandCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "���Ӽ�");
			_attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "���Ӽ�");
			_attributeFireCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "ȭ�Ӽ�");
			_attributeWindCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "ǳ�Ӽ�");
			_petAttackPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "���ݷ�");
			_petDefensePower = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "����");
			_petSpeedPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "���߷�");
			_petTotalStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "��üü��");
			_petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "����ü��");
			_petSkillNum[0] = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "���1");
			_petSkillNum[1] = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "���2");
			_petSkillNum[2] = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "���3");
			_petSkillNum[3] = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "���4");
			_petSkillNum[4] = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "���5");
			_petSkillNum[5] = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "���6");
		}

		if (pet3_mode == "��Ʋ")
		{
			_petLevel = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "����");
			_petNameString = INIDATA->loadDataString("�÷��̾�1_��", "��3", "�̸�");
			_attributeLandCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "���Ӽ�");
			_attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "���Ӽ�");
			_attributeFireCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "ȭ�Ӽ�");
			_attributeWindCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "ǳ�Ӽ�");
			_petAttackPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "���ݷ�");
			_petDefensePower = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "����");
			_petSpeedPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "���߷�");
			_petTotalStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "��üü��");
			_petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "����ü��");
			_petSkillNum[0] = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "���1");
			_petSkillNum[1] = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "���2");
			_petSkillNum[2] = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "���3");
			_petSkillNum[3] = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "���4");
			_petSkillNum[4] = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "���5");
			_petSkillNum[5] = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "���6");
		}

		if (pet4_mode == "��Ʋ")
		{
			_petLevel = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "����");
			_petNameString = INIDATA->loadDataString("�÷��̾�1_��", "��4", "�̸�");
			_attributeLandCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "���Ӽ�");
			_attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "���Ӽ�");
			_attributeFireCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "ȭ�Ӽ�");
			_attributeWindCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "ǳ�Ӽ�");
			_petAttackPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "���ݷ�");
			_petDefensePower = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "����");
			_petSpeedPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "���߷�");
			_petTotalStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "��üü��");
			_petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "����ü��");
			_petSkillNum[0] = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "���1");
			_petSkillNum[1] = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "���2");
			_petSkillNum[2] = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "���3");
			_petSkillNum[3] = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "���4");
			_petSkillNum[4] = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "���5");
			_petSkillNum[5] = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "���6");
		}

		if (pet5_mode == "��Ʋ")
		{
			_petLevel = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "����");
			_petNameString = INIDATA->loadDataString("�÷��̾�1_��", "��5", "�̸�");
			_attributeLandCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "���Ӽ�");
			_attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "���Ӽ�");
			_attributeFireCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "ȭ�Ӽ�");
			_attributeWindCount = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "ǳ�Ӽ�");
			_petAttackPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "���ݷ�");
			_petDefensePower = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "����");
			_petSpeedPower = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "���߷�");
			_petTotalStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "��üü��");
			_petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "����ü��");
			_petSkillNum[0] = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "���1");
			_petSkillNum[1] = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "���2");
			_petSkillNum[2] = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "���3");
			_petSkillNum[3] = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "���4");
			_petSkillNum[4] = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "���5");
			_petSkillNum[5] = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "���6");
		}
	}

	if (loginPlayer2 == (int)INFO_YES)
	{
		string pet1_mode = INIDATA->loadDataString("�÷��̾�2_��", "��1", "���");
		string pet2_mode = INIDATA->loadDataString("�÷��̾�2_��", "��2", "���");
		string pet3_mode = INIDATA->loadDataString("�÷��̾�2_��", "��3", "���");
		string pet4_mode = INIDATA->loadDataString("�÷��̾�2_��", "��4", "���");
		string pet5_mode = INIDATA->loadDataString("�÷��̾�2_��", "��5", "���");


		if (pet1_mode == "��Ʋ")
		{
			_petLevel = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "����");
			_petNameString = INIDATA->loadDataString("�÷��̾�2_��", "��1", "�̸�");
			_attributeLandCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "���Ӽ�");
			_attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "���Ӽ�");
			_attributeFireCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "ȭ�Ӽ�");
			_attributeWindCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "ǳ�Ӽ�");
			_petAttackPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "���ݷ�");
			_petDefensePower = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "����");
			_petSpeedPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "���߷�");
			_petTotalStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "��üü��");
			_petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "����ü��");
			_petSkillNum[0] = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "���1");
			_petSkillNum[1] = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "���2");
			_petSkillNum[2] = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "���3");
			_petSkillNum[3] = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "���4");
			_petSkillNum[4] = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "���5");
			_petSkillNum[5] = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "���6");
		}

		if (pet2_mode == "��Ʋ")
		{
			_petLevel = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "����");
			_petNameString = INIDATA->loadDataString("�÷��̾�2_��", "��2", "�̸�");
			_attributeLandCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "���Ӽ�");
			_attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "���Ӽ�");
			_attributeFireCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "ȭ�Ӽ�");
			_attributeWindCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "ǳ�Ӽ�");
			_petAttackPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "���ݷ�");
			_petDefensePower = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "����");
			_petSpeedPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "���߷�");
			_petTotalStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "��üü��");
			_petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "����ü��");
			_petSkillNum[0] = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "���1");
			_petSkillNum[1] = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "���2");
			_petSkillNum[2] = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "���3");
			_petSkillNum[3] = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "���4");
			_petSkillNum[4] = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "���5");
			_petSkillNum[5] = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "���6");
		}

		if (pet3_mode == "��Ʋ")
		{
			_petLevel = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "����");
			_petNameString = INIDATA->loadDataString("�÷��̾�2_��", "��3", "�̸�");
			_attributeLandCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "���Ӽ�");
			_attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "���Ӽ�");
			_attributeFireCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "ȭ�Ӽ�");
			_attributeWindCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "ǳ�Ӽ�");
			_petAttackPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "���ݷ�");
			_petDefensePower = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "����");
			_petSpeedPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "���߷�");
			_petTotalStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "��üü��");
			_petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "����ü��");
			_petSkillNum[0] = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "���1");
			_petSkillNum[1] = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "���2");
			_petSkillNum[2] = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "���3");
			_petSkillNum[3] = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "���4");
			_petSkillNum[4] = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "���5");
			_petSkillNum[5] = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "���6");
		}

		if (pet4_mode == "��Ʋ")
		{
			_petLevel = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "����");
			_petNameString = INIDATA->loadDataString("�÷��̾�2_��", "��4", "�̸�");
			_attributeLandCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "���Ӽ�");
			_attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "���Ӽ�");
			_attributeFireCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "ȭ�Ӽ�");
			_attributeWindCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "ǳ�Ӽ�");
			_petAttackPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "���ݷ�");
			_petDefensePower = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "����");
			_petSpeedPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "���߷�");
			_petTotalStamina = INIDATA->loadDataInterger("�÷��̾�2_�̾�1_��", "��4", "��üü��");
			_petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "����ü��");
			_petSkillNum[0] = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "���1");
			_petSkillNum[1] = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "���2");
			_petSkillNum[2] = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "���3");
			_petSkillNum[3] = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "���4");
			_petSkillNum[4] = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "���5");
			_petSkillNum[5] = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "���6");
		}

		if (pet5_mode == "��Ʋ")
		{
			_petLevel = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "����");
			_petNameString = INIDATA->loadDataString("�÷��̾�2_��", "��5", "�̸�");
			_attributeLandCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "���Ӽ�");
			_attributeWaterCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "���Ӽ�");
			_attributeFireCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "ȭ�Ӽ�");
			_attributeWindCount = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "ǳ�Ӽ�");
			_petAttackPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "���ݷ�");
			_petDefensePower = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "����");
			_petSpeedPower = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "���߷�");
			_petTotalStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "��üü��");
			_petCurrentStamina = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "����ü��");
			_petSkillNum[0] = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "���1");
			_petSkillNum[1] = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "���2");
			_petSkillNum[2] = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "���3");
			_petSkillNum[3] = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "���4");
			_petSkillNum[4] = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "���5");
			_petSkillNum[5] = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "���6");
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
