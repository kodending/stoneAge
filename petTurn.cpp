#include "stdafx.h"
#include "gameNode.h"
#include "battleMap.h"
#include "playerTurn.h"
#include "battleAppear.h"
#include "petTurn.h"
#include "battleTurn.h"
#include "battleClose.h"

battleState * petTurn::inputHandle(battleMap * battleMap)
{
	if (battleMap->_battleTurn == TURN_BATTLE)
	{
		//0초까지 선택을 못했을경우는
		if (battleMap->_selectTimeCount < 0)
		{
			for (int j = 0; j < battleMap->_vPet.size(); ++j)
			{
				if (battleMap->_vPet[j]->getIsPlayerPet() == false) continue;

				battleMap->_vPet[j]->setAttackPointX(battleMap->_vPet[j]->getTileCenterX());
				battleMap->_vPet[j]->setAttackPointY(battleMap->_vPet[j]->getTileCenterY());
			}
		}

		return new battleTurn();
	}

	return nullptr;
}

void petTurn::update(battleMap * battleMap)
{
	updatePetControl(battleMap);

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SOUNDMANAGER->play("click", 0.4f);
		selectPetControl(battleMap);
		selectEnemy(battleMap);
	}
}

void petTurn::enter(battleMap * battleMap)
{
	_isPetSkillSelected = false;
	setPetControlWindow(battleMap);
}

void petTurn::render(battleMap * battleMap)
{
	_petControlWindow.selectSkillImg->render(getMemDC(), _petControlWindow.selectSkillRc.left, _petControlWindow.selectSkillRc.top);

	if (_isPetSkillSelected == false)
	{
		_petControlWindow.backImg->alphaRender(getMemDC(), _petControlWindow.backRect.left, _petControlWindow.backRect.top, 200);
		_petControlWindow.frontImg->render(getMemDC(), _petControlWindow.frontRect.left, _petControlWindow.frontRect.top);
	}

	renderPetControl(battleMap);
	PtInRender(battleMap);
}

void petTurn::exit(battleMap * battleMap)
{

}

void petTurn::setPetControlWindow(battleMap * battleMap)
{
	_petControlWindow.backImg = IMAGEMANAGER->findImage("petSkillWindowBack");
	_petControlWindow.frontImg = IMAGEMANAGER->findImage("petSkillWindow2");
	_petControlWindow.selectSkillImg = IMAGEMANAGER->findImage("selectSkillWindow");
	_petControlWindow.selectSkillRc = RectMake(WINSIZEX - _petControlWindow.selectSkillImg->getWidth(), 0,
		_petControlWindow.selectSkillImg->getWidth(), _petControlWindow.selectSkillImg->getHeight());
	_petControlWindow.frontRect = RectMake(WINSIZEX - _petControlWindow.frontImg->getWidth(),
		_petControlWindow.selectSkillRc.bottom,
		_petControlWindow.frontImg->getWidth(), _petControlWindow.frontImg->getHeight());
	_petControlWindow.backRect = RectMake(WINSIZEX - _petControlWindow.frontImg->getWidth(),
		_petControlWindow.selectSkillRc.bottom,
		_petControlWindow.backImg->getWidth(), _petControlWindow.backImg->getHeight());
	_petControlWindow.closeRect = RectMake(_petControlWindow.frontRect.left + 106,
		_petControlWindow.frontRect.top + 354, 88, 18);
	_petControlWindow.skillWindowText = "펫 기술 선택";

	for (int i = 0; i < 6; ++i)
	{
		_petControlWindow.skillRc[i] = RectMakeCenter(_petControlWindow.frontRect.left + 80,
			_petControlWindow.frontRect.top + 65 + i * 26, 60, 20);
	}

	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

		for (int j = 0; j < 6; ++j)
		{
			if (battleMap->_vPet[i]->_petSkillNum[j] == (int)PET_SKILL_ATTACK)
			{
				_petControlWindow.skillName[j] = "공격";
				_petControlWindow.skillInfo[j] = "통상적인 공격이다";
			}

			else if (battleMap->_vPet[i]->_petSkillNum[j] == (int)PET_SKILL_DEFENSE)
			{
				_petControlWindow.skillName[j] = "방어";
				_petControlWindow.skillInfo[j] = "최소한의 피해로 방어를 한다";
			}

			else _petControlWindow.skillName[j] = "없음";
		}
	}
}

void petTurn::selectPetControl(battleMap * battleMap)
{
	for (int i = 0; i < 6; ++i)
	{
		if (_petControlWindow.skillName[i] == "없음") continue;

		if (PtInRect(&_petControlWindow.skillRc[i], _ptMouse))
		{
			if (_petControlWindow.skillName[i] == "공격")
			{
				for (int i = 0; i < battleMap->_vPet.size(); ++i)
				{
					if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

					battleMap->_vPet[i]->_petSkill = PET_SKILL_ATTACK;
					break;
				}
			}

			if (_petControlWindow.skillName[i] == "방어")
			{
				for (int i = 0; i < battleMap->_vPet.size(); ++i)
				{
					if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

					battleMap->_vPet[i]->_petSkill = PET_SKILL_DEFENSE;
					battleMap->_vPet[i]->setAttackPointX(battleMap->_vPet[i]->getTileCenterX());
					battleMap->_vPet[i]->setAttackPointY(battleMap->_vPet[i]->getTileCenterY());

					battleMap->_battleTurn = TURN_BATTLE;
					break;
				}
			}
	
			_isPetSkillSelected = true;
		}
	}

	if (PtInRect(&_petControlWindow.closeRect, _ptMouse))
	{
		for (int i = 0; i < battleMap->_vPet.size(); ++i)
		{
			if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

			battleMap->_vPet[i]->_petSkill = PET_SKILL_NONE;
		}
		_isPetSkillSelected = true;
	}

	if (PtInRect(&_petControlWindow.skillselectButton, _ptMouse))
	{
		for (int i = 0; i < battleMap->_vPet.size(); ++i)
		{
			if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

			battleMap->_vPet[i]->_petSkill = PET_SKILL_NONE;
		}
		_isPetSkillSelected = false;
	}
}

void petTurn::updatePetControl(battleMap * battleMap)
{
	if (_isPetSkillSelected == true)
	{
		_petControlWindow.frontRect = RectMake(WINSIZEX + _petControlWindow.frontImg->getWidth(),
			_petControlWindow.selectSkillRc.bottom,
			_petControlWindow.frontImg->getWidth(), _petControlWindow.frontImg->getHeight());
		_petControlWindow.backRect = RectMake(WINSIZEX + _petControlWindow.frontImg->getWidth(),
			_petControlWindow.selectSkillRc.bottom,
			_petControlWindow.backImg->getWidth(), _petControlWindow.backImg->getHeight());
		_petControlWindow.closeRect = RectMake(_petControlWindow.frontRect.left + 106,
			_petControlWindow.frontRect.top + 354, 88, 18);
		_petControlWindow.skillselectButton = RectMake(_petControlWindow.selectSkillRc.left + 72,
			_petControlWindow.selectSkillRc.top + 63, 91, 20);

		for (int i = 0; i < 6; ++i)
		{
			_petControlWindow.skillRc[i] = RectMakeCenter(_petControlWindow.frontRect.left + 80,
				_petControlWindow.frontRect.top + 75 + i * 26, 60, 20);
		}
	}

	else
	{
		_petControlWindow.frontRect = RectMake(WINSIZEX - _petControlWindow.frontImg->getWidth(),
			_petControlWindow.selectSkillRc.bottom,
			_petControlWindow.frontImg->getWidth(), _petControlWindow.frontImg->getHeight());
		_petControlWindow.backRect = RectMake(WINSIZEX - _petControlWindow.frontImg->getWidth(),
			_petControlWindow.selectSkillRc.bottom,
			_petControlWindow.backImg->getWidth(), _petControlWindow.backImg->getHeight());
		_petControlWindow.closeRect = RectMake(_petControlWindow.frontRect.left + 106,
			_petControlWindow.frontRect.top + 354, 88, 18);
		_petControlWindow.skillselectButton = RectMake(_petControlWindow.selectSkillRc.left + 72,
			_petControlWindow.selectSkillRc.top + 63, 91, 20);

		for (int i = 0; i < 6; ++i)
		{
			_petControlWindow.skillRc[i] = RectMakeCenter(_petControlWindow.frontRect.left + 100,
				_petControlWindow.frontRect.top + 75 + i * 26, 60, 20);
		}
	}
}

void petTurn::renderPetControl(battleMap * battleMap)
{
	//기술창이름 띄우는곳
	HFONT font = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY목각파임B"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(80, 255, 255));

	TextOut(getMemDC(), _petControlWindow.frontRect.left + 106, _petControlWindow.frontRect.top + 6,
		_petControlWindow.skillWindowText.c_str(), strlen(_petControlWindow.skillWindowText.c_str()));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	SetBkMode(getMemDC(), OPAQUE);

	//펫이름 띄우는곳
	
	HFONT font3 = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("HY목각파임B"));
	HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), font3);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

		TextOut(getMemDC(), _petControlWindow.frontRect.left + 50, _petControlWindow.frontRect.top + 35,
			battleMap->_vPet[i]->getPetNameString().c_str(), strlen(battleMap->_vPet[i]->getPetNameString().c_str()));
	}

	SelectObject(getMemDC(), oldFont3);
	DeleteObject(font3);
	SetBkMode(getMemDC(), OPAQUE);

	//기술이름 띄운느곳 
	HFONT font2 = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("맑은고딕"));
	HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), font2);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	for (int i = 0; i < 6; ++i)
	{
		if (_petControlWindow.skillName[i] == "없음") continue;

		TextOut(getMemDC(), _petControlWindow.skillRc[i].left + 5, _petControlWindow.skillRc[i].top + 2,
			_petControlWindow.skillName[i].c_str(), strlen(_petControlWindow.skillName[i].c_str()));
	}

	SelectObject(getMemDC(), oldFont2);
	DeleteObject(font2);
	SetBkMode(getMemDC(), OPAQUE);

	//핕인하면 설명창나오는곳
	
	for (int i = 0; i < 6; ++i)
	{
		if (_petControlWindow.skillName[i] == "없음") continue;

		if (PtInRect(&_petControlWindow.skillRc[i], _ptMouse))
		{
			HFONT font = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
				0, 0, 0, 0, TEXT("HY목각파임B"));
			HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
			SetBkMode(getMemDC(), TRANSPARENT);
			SetTextColor(getMemDC(), RGB(80, 255, 255));

			TextOut(getMemDC(), _petControlWindow.frontRect.left + 30, _petControlWindow.frontRect.top + 295,
				_petControlWindow.skillInfo[i].c_str(), strlen(_petControlWindow.skillInfo[i].c_str()));

			SelectObject(getMemDC(), oldFont);
			DeleteObject(font);
			SetBkMode(getMemDC(), OPAQUE);
		}
	}

	HFONT font4 = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("맑은고딕"));
	HFONT oldFont4 = (HFONT)SelectObject(getMemDC(), font4);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 80));

	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

		if (battleMap->_vPet[i]->_petSkill == PET_SKILL_ATTACK)
		{
			for (int i = 0; i < 6; ++i)
			{
				if (_petControlWindow.skillName[i] != "공격") continue;

				TextOut(getMemDC(), _petControlWindow.selectSkillRc.left + 45, _petControlWindow.selectSkillRc.top + 38,
					_petControlWindow.skillName[i].c_str(), strlen(_petControlWindow.skillName[i].c_str()));
			}
		}

		if (battleMap->_vPet[i]->_petSkill == PET_SKILL_DEFENSE)
		{
			for (int i = 0; i < 6; ++i)
			{
				if (_petControlWindow.skillName[i] != "방어") continue;

				TextOut(getMemDC(), _petControlWindow.selectSkillRc.left + 45, _petControlWindow.selectSkillRc.top + 38,
					_petControlWindow.skillName[i].c_str(), strlen(_petControlWindow.skillName[i].c_str()));
			}
		}
	}


	SelectObject(getMemDC(), oldFont4);
	DeleteObject(font4);
	SetBkMode(getMemDC(), OPAQUE);
}

void petTurn::PtInRender(battleMap * battleMap)
{
	HPEN myPen = CreatePen(PS_DASH, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	for (int i = 0; i < 6; ++i)
	{
		if (_petControlWindow.skillName[i] == "없음") continue;

		if (PtInRect(&_petControlWindow.skillRc[i], _ptMouse))
		{
			Rectangle(getMemDC(), _petControlWindow.skillRc[i]);
		}
	}

	if (PtInRect(&_petControlWindow.closeRect, _ptMouse))
	{
		Rectangle(getMemDC(), _petControlWindow.closeRect);
	}

	if (PtInRect(&_petControlWindow.skillselectButton, _ptMouse))
	{
		Rectangle(getMemDC(), _petControlWindow.skillselectButton);
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void petTurn::selectEnemy(battleMap * battleMap)
{
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getEnumPetState() == PET_DEAD) continue;

		if (PtInRect(&battleMap->_vPet[i]->getTileRect(), _ptMouse))
		{
			for (int j = 0; j < battleMap->_vPet.size(); ++j)
			{
				if (battleMap->_vPet[j]->getIsPlayerPet() == false) continue;


				if (battleMap->_vPet[j]->_petSkill == PET_SKILL_ATTACK)
				{
					battleMap->_vPet[j]->setAttackPointX(battleMap->_vPet[i]->getTileCenterX() + 32);
					battleMap->_vPet[j]->setAttackPointY(battleMap->_vPet[i]->getTileCenterY() + 23.5f);

					battleMap->_battleTurn = TURN_BATTLE;
				}
			}
		}
	}
}

