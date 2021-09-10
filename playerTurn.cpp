#include "stdafx.h"
#include "gameNode.h"
#include "battleMap.h"
#include "playerTurn.h"
#include "battleAppear.h"
#include "petTurn.h"
#include "battleTurn.h"
#include "battleClose.h"

battleState * playerTurn::inputHandle(battleMap * battleMap)
{
	if (battleMap->_battleTurn == TURN_PET)
	{
		return new petTurn();
	}

	if (battleMap->_battleTurn == TURN_BATTLE)
	{
		for (int i = 0; i < battleMap->_vPet.size(); ++i)
		{
			if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

			battleMap->_vPet[i]->_petSkill = PET_SKILL_NONE;
		}

		return new battleTurn();
	}

	return nullptr;
}

void playerTurn::update(battleMap * battleMap)
{
	updateBattleWindow(battleMap);

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SOUNDMANAGER->play("click", 0.4f);
		selectBattleWindow(battleMap);
		selectBattle(battleMap);

		if (PtInRect(&_itemWindow.closeRect, _ptMouse))
		{
			_isItemCloseRect = true;
		}
	}

	if (_isSelected == true)
	{
		_isSkillWindow = false;
		_isHelpWindow = false;
		_isItemWindow = false;
	}

	updateItemWindow(battleMap);
}

void playerTurn::enter(battleMap * battleMap)
{
	setBattleWindow(battleMap);
	_isSelected = false;
	_isSound = false;
	_isSound2 = false;

	battleMap->_selectTimeCount = 31; //플레이어 선택시는 항상 타임카운트 초기화

	setSkillNotice(battleMap);
	setHelpNotice(battleMap);
	setItemWindow(battleMap);
}

void playerTurn::render(battleMap * battleMap)
{
	_battleWindow.frontImg->frameRender(getMemDC(), _battleWindow.frontRect.left, _battleWindow.frontRect.top,
		_battleWindow.currentSelectX, _battleWindow.currentSelectY);

	renderSkillNotice(battleMap);
	renderHelpNotice(battleMap);
	renderItemWindow(battleMap);

	PtInRender(battleMap);
}

void playerTurn::exit(battleMap * battleMap)
{
}

void playerTurn::setBattleWindow(battleMap * battleMap)
{
	_battleWindow.frontImg = IMAGEMANAGER->findImage("battleWindow");
	_battleWindow.frontRect = RectMake(WINSIZEX, 0,
		_battleWindow.frontImg->getFrameWidth(), _battleWindow.frontImg->getFrameHeight());
	_battleWindow.currentSelectX = 0;
	_battleWindow.currentSelectY = 0;
	battleMap->_battleSelect = BATTLE_ATTACK;
	_battleWindow.centerX = (_battleWindow.frontRect.left + _battleWindow.frontRect.right) / 2;
	_battleWindow.centerY = (_battleWindow.frontRect.top + _battleWindow.frontRect.bottom) / 2;

	for (int i = 0; i < 8; ++i)
	{
		if (i <= 3)
		{
			_battleWindow.select[i] = RectMakeCenter(_battleWindow.frontRect.left + 34 + (i * 61),
				_battleWindow.frontRect.top + 52, 57, 57);
		}

		if (i > 3)
		{
			_battleWindow.select[i] = RectMakeCenter(_battleWindow.frontRect.left + 34 + ((i - 4) * 61),
				_battleWindow.frontRect.top + 112, 57, 57);
		}
	}

	//알림창 설정
	battleMap->_noticeWindow.noticeWord = "대상을 선택해주세요";
}

void playerTurn::updateBattleWindow(battleMap * battleMap)
{
	if (_isSelected == false)
	{
		if (_battleWindow.centerX > WINSIZEX - _battleWindow.frontImg->getFrameWidth() / 2)
		{
			_battleWindow.centerX -= 8;
		}

		if (_battleWindow.centerX <= WINSIZEX - _battleWindow.frontImg->getFrameWidth() / 2)
		{
			_battleWindow.centerX = WINSIZEX - _battleWindow.frontImg->getFrameWidth() / 2;
			if (_isSound == false)
			{
				SOUNDMANAGER->play("window_up", 0.4f);
				_isSound = true;
			}
			_isSound2 = false;
		}
	}

	else if (_isSelected == true)
	{
		if (_battleWindow.centerX < WINSIZEX + _battleWindow.frontImg->getFrameWidth() / 2)
		{
			_battleWindow.centerX += 8;
		}

		if (_battleWindow.centerX >= WINSIZEX + _battleWindow.frontImg->getFrameWidth() / 2)
		{
			_battleWindow.centerX = WINSIZEX + _battleWindow.frontImg->getFrameWidth() / 2;

			//이미 내 펫이 죽었을경우는 펫 선택창에서 넘어갈수없음, 도망치는선택을했을경우도포함
			for (int i = 0; i < battleMap->_vPet.size(); ++i)
			{
				if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

				if (battleMap->_vPet[i]->_isDead == true || 
					battleMap->_battleSelect == BATTLE_ESCAPE) battleMap->_battleTurn = TURN_BATTLE;

				else battleMap->_battleTurn = TURN_PET;
			}
			if (_isSound2 == false)
			{
				SOUNDMANAGER->play("window_down", 0.4f);
				_isSound2 = true;
			}

			_isSound = false;
		}
	}

	_battleWindow.frontRect = RectMakeCenter(_battleWindow.centerX, _battleWindow.centerY,
		_battleWindow.frontImg->getFrameWidth(), _battleWindow.frontImg->getFrameHeight());

	for (int i = 0; i < 8; ++i)
	{
		if (i <= 3)
		{
			_battleWindow.select[i] = RectMakeCenter(_battleWindow.frontRect.left + 34 + (i * 60.5f),
				_battleWindow.frontRect.top + 52, 57, 57);
		}

		if (i > 3)
		{
			_battleWindow.select[i] = RectMakeCenter(_battleWindow.frontRect.left + 34 + ((i - 4) * 60.5f),
				_battleWindow.frontRect.top + 112, 57, 57);
		}
	}
}

void playerTurn::selectBattleWindow(battleMap * battleMap)
{
	for (int i = 0; i < 8; ++i)
	{
		if (PtInRect(&_battleWindow.select[i], _ptMouse))
		{
			if (i == (int)BATTLE_ATTACK)
			{
				_battleWindow.currentSelectX = (int)BATTLE_ATTACK;
				battleMap->_battleSelect = BATTLE_ATTACK;
			}

			if (i == (int)BATTLE_SKILL)
			{
				_battleWindow.currentSelectX = (int)BATTLE_SKILL;
				battleMap->_battleSelect = BATTLE_SKILL;
			}

			if (i == (int)BATTLE_CATCH)
			{
				_battleWindow.currentSelectX = (int)BATTLE_CATCH;
				battleMap->_battleSelect = BATTLE_CATCH;
			}

			if (i == (int)BATTLE_HELP)
			{
				_battleWindow.currentSelectX = (int)BATTLE_HELP;
				battleMap->_battleSelect = BATTLE_HELP;
			}

			if (i == (int)BATTLE_DEFENSE)
			{
				_battleWindow.currentSelectX = (int)BATTLE_DEFENSE;
				battleMap->_battleSelect = BATTLE_DEFENSE;
			}

			if (i == (int)BATTLE_ITEM)
			{
				_battleWindow.currentSelectX = (int)BATTLE_ITEM;
				battleMap->_battleSelect = BATTLE_ITEM;
				_isItemCloseRect = false;
			}

			if (i == (int)BATTLE_PET)
			{
				_battleWindow.currentSelectX = (int)BATTLE_PET;
				battleMap->_battleSelect = BATTLE_PET;
			}

			if (i == (int)BATTLE_ESCAPE)
			{
				_battleWindow.currentSelectX = (int)BATTLE_ESCAPE;
				battleMap->_battleSelect = BATTLE_ESCAPE;
			}
		}
	}
}

void playerTurn::selectBattle(battleMap * battleMap)
{
	if (battleMap->_battleSelect == BATTLE_ATTACK ||
		battleMap->_battleSelect == BATTLE_CATCH)
	{
		for (int i = 0; i < battleMap->_vPet.size(); ++i)
		{
			if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;
			if (battleMap->_vPet[i]->getEnumPetState() == PET_DEAD) continue;

			if (PtInRect(&battleMap->_vPet[i]->getTileRect(), _ptMouse))
			{
				battleMap->_player->setAttackPointX(battleMap->_vPet[i]->getTileCenterX() + 32);
				battleMap->_player->setAttackPointY(battleMap->_vPet[i]->getTileCenterY() + 23.5f);
				_isSelected = true;
			}
		}
	}

	if (battleMap->_battleSelect == BATTLE_SKILL)
	{
		battleMap->_player->setAttackPointX(battleMap->_player->getPlayerCenterX());
		battleMap->_player->setAttackPointY(battleMap->_player->getPlayerCenterY());

		_isSkillWindow = true;
	}

	else _isSkillWindow = false;

	if (battleMap->_battleSelect == BATTLE_HELP)
	{
		battleMap->_player->setAttackPointX(battleMap->_player->getPlayerCenterX());
		battleMap->_player->setAttackPointY(battleMap->_player->getPlayerCenterY());

		_isHelpWindow = true;
	}

	else _isHelpWindow = false;

	if (battleMap->_battleSelect == BATTLE_DEFENSE)
	{
		battleMap->_player->setAttackPointX(battleMap->_player->getPlayerCenterX());
		battleMap->_player->setAttackPointY(battleMap->_player->getPlayerCenterY());
		_isSelected = true;
	}

	if (battleMap->_battleSelect == BATTLE_ITEM)
	{
		battleMap->_player->setAttackPointX(battleMap->_player->getPlayerCenterX());
		battleMap->_player->setAttackPointY(battleMap->_player->getPlayerCenterY());
		_isItemWindow = true;
	}

	else if (battleMap->_battleSelect != BATTLE_ITEM || _isItemCloseRect == true)
	{
		_isItemWindow = false;
	}

	if (battleMap->_battleSelect == BATTLE_ESCAPE)
	{
		battleMap->_player->setAttackPointX(WINSIZEX + 224);
		battleMap->_player->setAttackPointY(WINSIZEY + 176);
		_isSelected = true;
	}
}

void playerTurn::setSkillNotice(battleMap * battleMap)
{
	_isSkillWindow = false;
	_skillNotice.frontImg = IMAGEMANAGER->findImage("inputWindow2");
	_skillNotice.backImg = IMAGEMANAGER->findImage("inputWindowBack");
	_skillNotice.frontRect = RectMakeCenter(660, 220,
		_skillNotice.frontImg->getWidth(), _skillNotice.frontImg->getHeight());
	_skillNotice.backRect = RectMakeCenter(660, 220,
		_skillNotice.backImg->getWidth(), _skillNotice.backImg->getHeight());
	_skillNotice.noticeWord = "현재 기술이 없습니다";
}

void playerTurn::renderSkillNotice(battleMap * battleMap)
{
	if (_isSkillWindow == true)
	{
		_skillNotice.backImg->alphaRender(getMemDC(), _skillNotice.backRect.left, _skillNotice.backRect.top, 200);
		_skillNotice.frontImg->render(getMemDC(), _skillNotice.frontRect.left, _skillNotice.frontRect.top);

		HFONT font = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY목각파임B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);

		SetTextColor(getMemDC(), RGB(80, 255, 255));
		TextOut(getMemDC(), _skillNotice.frontRect.left + 40, _skillNotice.frontRect.top + 50,
			_skillNotice.noticeWord.c_str(), strlen(_skillNotice.noticeWord.c_str()));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}
}

void playerTurn::setHelpNotice(battleMap * battleMap)
{
	_isHelpWindow = false;
	_helpNotice.frontImg = IMAGEMANAGER->findImage("inputWindow2");
	_helpNotice.backImg = IMAGEMANAGER->findImage("inputWindowBack");
	_helpNotice.frontRect = RectMakeCenter(660, 220,
		_helpNotice.frontImg->getWidth(), _helpNotice.frontImg->getHeight());
	_helpNotice.backRect = RectMakeCenter(660, 220,
		_helpNotice.backImg->getWidth(), _helpNotice.backImg->getHeight());
	_helpNotice.noticeWord = "도움을 요청중입니다";
}

void playerTurn::renderHelpNotice(battleMap * battleMap)
{
	if (_isHelpWindow == true)
	{
		_helpNotice.backImg->alphaRender(getMemDC(), _helpNotice.backRect.left, _helpNotice.backRect.top, 200);
		_helpNotice.frontImg->render(getMemDC(), _helpNotice.frontRect.left, _helpNotice.frontRect.top);

		HFONT font = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY목각파임B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);

		SetTextColor(getMemDC(), RGB(80, 255, 255));
		TextOut(getMemDC(), _helpNotice.frontRect.left + 40, _helpNotice.frontRect.top + 50,
			_helpNotice.noticeWord.c_str(), strlen(_helpNotice.noticeWord.c_str()));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}
}

void playerTurn::setItemWindow(battleMap * battleMap)
{
	_isItemWindow = false;
	_isItemCloseRect = false;
	_itemWindow.frontImg = IMAGEMANAGER->findImage("battleItemWindow");
	_itemWindow.backImg = IMAGEMANAGER->findImage("battleItemWindowBack");
	_itemWindow.frontRect = RectMakeCenter(WINSIZEX + 200, 0,
		_itemWindow.frontImg->getWidth(), _itemWindow.frontImg->getHeight());
	_itemWindow.backRect = RectMakeCenter(WINSIZEX + 200, 0,
		_itemWindow.backImg->getWidth(), _itemWindow.backImg->getHeight());
	_itemWindow.closeRect = RectMakeCenter(_itemWindow.frontRect.left + 165, _itemWindow.frontRect.top + 295,
		82, 16);
	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			_itemWindow.itemRect[i][j] = RectMakeCenter(_itemWindow.frontRect.left + 67 + i * 64,
				_itemWindow.frontRect.top + 62 + j * 52, 51, 39);
		}
	}
	_itemWindow.noticeWord = "아이템이 없습니다";
}

void playerTurn::updateItemWindow(battleMap * battleMap)
{
	if (_isItemWindow == true && _isItemCloseRect == false)
	{
		_itemWindow.frontImg = IMAGEMANAGER->findImage("battleItemWindow");
		_itemWindow.backImg = IMAGEMANAGER->findImage("battleItemWindowBack");
		_itemWindow.frontRect = RectMakeCenter(WINSIZEX - _itemWindow.frontImg->getWidth() / 2,
			145 + _itemWindow.frontImg->getHeight() / 2,
			_itemWindow.frontImg->getWidth(), _itemWindow.frontImg->getHeight());
		_itemWindow.backRect = RectMakeCenter((_itemWindow.frontRect.left + _itemWindow.frontRect.right) / 2 + 10,
			(_itemWindow.frontRect.top + _itemWindow.frontRect.bottom) / 2 + 10,
			_itemWindow.backImg->getWidth(), _itemWindow.backImg->getHeight());
		_itemWindow.closeRect = RectMakeCenter(_itemWindow.frontRect.left + 162, _itemWindow.frontRect.top + 295,
			83, 17);
		for (int j = 0; j < 3; ++j)
		{
			for (int i = 0; i < 4; ++i)
			{
				_itemWindow.itemRect[i][j] = RectMakeCenter(_itemWindow.frontRect.left + 67 + i * 64,
					_itemWindow.frontRect.top + 62 + j * 52, 55, 45);
			}
		}
	}

	else
	{
		_itemWindow.frontImg = IMAGEMANAGER->findImage("battleItemWindow");
		_itemWindow.backImg = IMAGEMANAGER->findImage("battleItemWindowBack");
		_itemWindow.frontRect = RectMakeCenter(WINSIZEX + 200, 0,
			_itemWindow.frontImg->getWidth(), _itemWindow.frontImg->getHeight());
		_itemWindow.backRect = RectMakeCenter(WINSIZEX + 200, 0,
			_itemWindow.backImg->getWidth(), _itemWindow.backImg->getHeight());
		_itemWindow.closeRect = RectMakeCenter(_itemWindow.frontRect.left + 165, _itemWindow.frontRect.top + 295,
			82, 16);
		for (int j = 0; j < 3; ++j)
		{
			for (int i = 0; i < 4; ++i)
			{
				_itemWindow.itemRect[i][j] = RectMakeCenter(_itemWindow.frontRect.left + 67 + i * 64,
					_itemWindow.frontRect.top + 62 + j * 52, 51, 39);
			}
		}
	}
}

void playerTurn::renderItemWindow(battleMap * battleMap)
{
	if (_isItemWindow == false) return;
	if (_isItemCloseRect == true) return;

	_itemWindow.backImg->alphaRender(getMemDC(), _itemWindow.backRect.left, _itemWindow.backRect.top, 200);
	_itemWindow.frontImg->render(getMemDC(), _itemWindow.frontRect.left, _itemWindow.frontRect.top);

	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (PtInRect(&_itemWindow.itemRect[i][j], _ptMouse))
			{
				HFONT font = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
					0, 0, 0, 0, TEXT("HY목각파임B"));
				HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
				SetBkMode(getMemDC(), TRANSPARENT);
				SetTextColor(getMemDC(), RGB(80, 255, 255));

				TextOut(getMemDC(), _itemWindow.frontRect.left + 60, _itemWindow.frontRect.top + 240,
					_itemWindow.noticeWord.c_str(), strlen(_itemWindow.noticeWord.c_str()));

				SelectObject(getMemDC(), oldFont);
				DeleteObject(font);
				SetBkMode(getMemDC(), OPAQUE);
			}
		}
	}
}

void playerTurn::PtInRender(battleMap * battleMap)
{
	HPEN myPen = CreatePen(PS_DASH, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	for (int i = 0; i < 8; ++i)
	{
		if (PtInRect(&_battleWindow.select[i], _ptMouse))
		{
			Rectangle(getMemDC(), _battleWindow.select[i]);
		}
	}

	if (PtInRect(&_itemWindow.closeRect, _ptMouse))
	{
		Rectangle(getMemDC(), _itemWindow.closeRect);
	}

	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (PtInRect(&_itemWindow.itemRect[i][j], _ptMouse))
			{
				Rectangle(getMemDC(), _itemWindow.itemRect[i][j]);
			}
		}
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}
