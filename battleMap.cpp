#include "stdafx.h"
#include "battleMap.h"
#include "battleAppear.h"

battleMap::battleMap()
{
}

battleMap::~battleMap()
{
}

void battleMap::InputHandle()
{
	battleState* newType = _battleState->inputHandle(this);
	if (newType != nullptr)
	{
		SAFE_DELETE(_battleState);
		_battleState = newType;
		_battleState->enter(this);
	}
}

HRESULT battleMap::init()
{
	_enemyNum = RND->getFromIntTo(1, 10); // 0 ~ 9
	_moveSpeedX = 2.72f;
	_moveSpeedY = 2;
	_isWriteInidata = false;
	_isSetPlayer = false;
	_petIsMoveCount = 0;
	_isStart = false;
	_isOneCycle = false;
	_timeCount = 0;
	_battleStartTime = TIMEMANAGER->getWorldTime();

	setEnemy();
	setSelectTime();

	_battleTurn = TURN_START_BATTLE;
	_battleState = new battleAppear();
	_battleState->enter(this);

	_underBar.img = IMAGEMANAGER->findImage("underBar2");
	_underBar.rc = RectMake(0, WINSIZEY - _underBar.img->getHeight(), _underBar.img->getWidth(), _underBar.img->getHeight());

	CAMERAMANAGER->setCamera(0, 0);

	setNoticeWindow();

	return S_OK;
}

void battleMap::release()
{
	_battleState->exit(this);
	_vPet.clear();
}

void battleMap::update()
{
	startBattle();
	writeInidata();
	setPlayer();

	appearEnemy();
	playerPetMove();
	playerMove();
	updateSelecTime();
	RENDERMANAGER->update();

	InputHandle();
	_battleState->update(this);

	for (_viPet = _vPet.begin(); _viPet != _vPet.end(); ++_viPet)
	{
		(*_viPet)->update();
	}
}

void battleMap::render(string backGroundImageName)
{
	IMAGEMANAGER->render(backGroundImageName, getMemDC(), 0, 0);

	if (_isOneCycle == true) RENDERMANAGER->render(getMemDC());

	for (_viPet = _vPet.begin(); _viPet != _vPet.end(); ++_viPet)
	{
		(*_viPet)->render();
	}

	if (_battleTurn == TURN_PLAYER || _battleTurn == TURN_PET)
	{
		for (int i = 0; i < 2; ++i)
		{
			_battleTime[i].img->frameRender(getMemDC(), _battleTime[i].rc.left, _battleTime[i].rc.top,
				_battleTime[i].currentFrameX, _battleTime[i].currentFrameY);
		}

		_noticeWindow.backImg->alphaRender(getMemDC(), _noticeWindow.backRect.left, _noticeWindow.backRect.top, 200);
		_noticeWindow.frontImg->render(getMemDC(), _noticeWindow.frontRect.left, _noticeWindow.frontRect.top);
		
		HFONT font = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY������B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);

		SetTextColor(getMemDC(), RGB(80, 255, 255));
		TextOut(getMemDC(), _noticeWindow.frontRect.left + 40, _noticeWindow.frontRect.top + 50,
			_noticeWindow.noticeWord.c_str(), strlen(_noticeWindow.noticeWord.c_str()));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}

	_battleState->render(this);

	SelectRender();

	_underBar.img->render(getMemDC(), _underBar.rc.left, _underBar.rc.top);
	infoRender();
	IMAGEMANAGER->render("mouse", getMemDC(), _ptMouse.x, _ptMouse.y);

	if (_isOneCycle == false) _isOneCycle = true;
}

void battleMap::setEnemy()
{
	for (int i = 0; i < _enemyNum; ++i)
	{
		pet* _pet = new pet;
		int petType = RND->getFromIntTo(0, 16); //0, 16 (0~15)

		if (_enemyNum == 1) _pet->init(PointMake(-256, -164), DIR_FIVE, PET_STAND, (PETNAME)petType, false);

		if (_enemyNum == 2) _pet->init(PointMake(-320 + (i * 128), -117 - (i * 94)), DIR_FIVE, PET_STAND, (PETNAME)petType, false);

		if (_enemyNum == 3) _pet->init(PointMake(-320 + (i * 64), -117 - (i * 47)), DIR_FIVE, PET_STAND, (PETNAME)petType, false);

		if (_enemyNum == 4) _pet->init(PointMake(-320 + (i * 64), -117 - (i * 47)), DIR_FIVE, PET_STAND, (PETNAME)petType, false);

		if (_enemyNum == 5) _pet->init(PointMake(-384 + (i * 64), -70 - (i * 47)), DIR_FIVE, PET_STAND, (PETNAME)petType, false);

		if (_enemyNum == 6)
		{
			if (i <= 4) _pet->init(PointMake(-384 + (i * 64), -70 - (i * 47)), DIR_FIVE, PET_STAND, (PETNAME)petType, false);
			if (i == 5) _pet->init(PointMake(-480, -141), DIR_FIVE, PET_STAND, (PETNAME)petType, false);
		}

		if (_enemyNum == 7)
		{
			if (i <= 4) _pet->init(PointMake(-384 + (i * 64), -70 - (i * 47)), DIR_FIVE, PET_STAND, (PETNAME)petType, false);
			if (i == 5) _pet->init(PointMake(-480, -141), DIR_FIVE, PET_STAND, (PETNAME)petType, false);
			if (i == 6) _pet->init(PointMake(-480 + 64, -141 - 47), DIR_FIVE, PET_STAND, (PETNAME)petType, false);
		}

		if (_enemyNum == 8)
		{
			if (i <= 4) _pet->init(PointMake(-384 + (i * 64), -70 - (i * 47)), DIR_FIVE, PET_STAND, (PETNAME)petType, false);
			if (i == 5) _pet->init(PointMake(-480, -141), DIR_FIVE, PET_STAND, (PETNAME)petType, false);
			if (i == 6) _pet->init(PointMake(-480 + 64, -141 - 47), DIR_FIVE, PET_STAND, (PETNAME)petType, false);
			if (i == 7) _pet->init(PointMake(-480 + 192, -141 - 141), DIR_FIVE, PET_STAND, (PETNAME)petType, false);
		}

		if (_enemyNum == 9)
		{
			if (i <= 4) _pet->init(PointMake(-384 + (i * 64), -70 - (i * 47)), DIR_FIVE, PET_STAND, (PETNAME)petType, false);
			if (i == 5) _pet->init(PointMake(-480, -141), DIR_FIVE, PET_STAND, (PETNAME)petType, false);
			if (i == 6) _pet->init(PointMake(-480 + 64, -141 - 47), DIR_FIVE, PET_STAND, (PETNAME)petType, false);
			if (i == 7) _pet->init(PointMake(-480 + 192, -141 - 141), DIR_FIVE, PET_STAND, (PETNAME)petType, false);
			if (i == 8) _pet->init(PointMake(-480 + 256, -141 - 188), DIR_FIVE, PET_STAND, (PETNAME)petType, false);
		}

		_vPet.push_back(_pet);
	}

	for (_viPet = _vPet.begin(); _viPet != _vPet.end(); ++_viPet)
	{
		(*_viPet)->setMoveEndX((*_viPet)->getTileCenterX() + 576);		// 320
		(*_viPet)->setMoveEndY((*_viPet)->getTileCenterY() + 422);		// 258
	}
}

void battleMap::writeInidata()
{
	if (_isWriteInidata == true) return;

	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");
	int playerCharacter1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "����");
	int playerCharacter2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "����");

	//�α��� �÷��̾� Ȯ��
	if (loginPlayer1 == (int)INFO_YES)
	{
		if (playerCharacter1 == (int)INFO_BLUE)
		{
			_player->_player.playerCharacter = BLUE;
			_player->_playerImageName = "blue_stand_basic";
			_player->setPlayerImageMoveY(-30);
		}

		if (playerCharacter1 == (int)INFO_RED)
		{
			_player->_player.playerCharacter = RED;
			_player->_playerImageName = "red_stand_basic";
			_player->setPlayerImageMoveY(-23.5f);
		}

		//�÷��̾� ���� �о����
		_playerInfo.currentStamina = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "����ü��");
		_playerInfo.totalStamina = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "ü��") * 4 + INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�Ϸ�") +
			INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�ǰ�") + INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "���ǵ�");
		_playerInfo.attackPower = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�Ϸ�") + INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "���ݷ�") +
			INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "���ݷ�") + INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "���ݷ�");
		_playerInfo.defensePower = 1 + INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�ǰ�") + INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "����") +
			INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "����") + INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "����");
		_playerInfo.speedPower = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "���ǵ�") + INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "���߷�") +
			INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "���߷�") + INIDATA->loadDataInterger("�÷��̾�1_������", "��������", "���߷�");
		_playerInfo.charming = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�ŷ�");
		_playerInfo.attributeLandCount = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "���Ӽ�");
		_playerInfo.attributeWaterCount = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "���Ӽ�");
		_playerInfo.attributeFireCount = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "ȭ�Ӽ�");
		_playerInfo.attributeWindCount = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "ǳ�Ӽ�");
	}

	//�α��� �÷��̾� Ȯ��
	if (loginPlayer2 == (int)INFO_YES)
	{
		if (playerCharacter2 == (int)INFO_BLUE)
		{
			_player->_player.playerCharacter = BLUE;
			_player->_playerImageName = "blue_stand_basic";
			_player->setPlayerImageMoveY(-30);
		}

		if (playerCharacter2 == (int)INFO_RED)
		{
			_player->_player.playerCharacter = RED;
			_player->_playerImageName = "red_stand_basic";
			_player->setPlayerImageMoveY(-23.5f);
		}

		//�÷��̾� ���� �о����
		_playerInfo.currentStamina = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "����ü��");
		_playerInfo.totalStamina = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "ü��") * 4 + INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�Ϸ�") +
			INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�ǰ�") + INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "���ǵ�");
		_playerInfo.attackPower = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�Ϸ�") + INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "���ݷ�") +
			INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "���ݷ�") + INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "���ݷ�");
		_playerInfo.defensePower = 1 + INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�ǰ�") + INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "����") +
			INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "����") + INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "����");
		_playerInfo.speedPower = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "���ǵ�") + INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "���߷�") +
			INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "���߷�") + INIDATA->loadDataInterger("�÷��̾�2_������", "��������", "���߷�");
		_playerInfo.charming = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�ŷ�");
		_playerInfo.attributeLandCount = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "���Ӽ�");
		_playerInfo.attributeWaterCount = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "���Ӽ�");
		_playerInfo.attributeFireCount = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "ȭ�Ӽ�");
		_playerInfo.attributeWindCount = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "ǳ�Ӽ�");
	}

	//�� ���� �о����
	if (loginPlayer1 == (int)INFO_YES)
	{
		pet* _playerPet = new pet;
		string pet1_mode = INIDATA->loadDataString("�÷��̾�1_��", "��1", "���");
		string pet2_mode = INIDATA->loadDataString("�÷��̾�1_��", "��2", "���");
		string pet3_mode = INIDATA->loadDataString("�÷��̾�1_��", "��3", "���");
		string pet4_mode = INIDATA->loadDataString("�÷��̾�1_��", "��4", "���");
		string pet5_mode = INIDATA->loadDataString("�÷��̾�1_��", "��5", "���");

		if (pet1_mode == "��Ʋ") _playerPet->setPetName((PETNAME)INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "����"));

		if (pet2_mode == "��Ʋ") _playerPet->setPetName((PETNAME)INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "����"));

		if (pet3_mode == "��Ʋ") _playerPet->setPetName((PETNAME)INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "����"));

		if (pet4_mode == "��Ʋ") _playerPet->setPetName((PETNAME)INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "����"));

		if (pet5_mode == "��Ʋ") _playerPet->setPetName((PETNAME)INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "����"));

		_playerPet->init(PointMake(WINSIZEX + 224, WINSIZEY + 176), DIR_ELEVEN, PET_STAND, _playerPet->getPetName(), true);
		_vPet.push_back(_playerPet);
	}

	//�� ���� �о����
	if (loginPlayer2 == (int)INFO_YES)
	{
		pet* _playerPet = new pet;
		string pet1_mode = INIDATA->loadDataString("�÷��̾�2_��", "��1", "���");
		string pet2_mode = INIDATA->loadDataString("�÷��̾�2_��", "��2", "���");
		string pet3_mode = INIDATA->loadDataString("�÷��̾�2_��", "��3", "���");
		string pet4_mode = INIDATA->loadDataString("�÷��̾�2_��", "��4", "���");
		string pet5_mode = INIDATA->loadDataString("�÷��̾�2_��", "��5", "���");

		if (pet1_mode == "��Ʋ") _playerPet->setPetName((PETNAME)INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "����"));

		if (pet2_mode == "��Ʋ") _playerPet->setPetName((PETNAME)INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "����"));

		if (pet3_mode == "��Ʋ") _playerPet->setPetName((PETNAME)INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "����"));

		if (pet4_mode == "��Ʋ") _playerPet->setPetName((PETNAME)INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "����"));

		if (pet5_mode == "��Ʋ") _playerPet->setPetName((PETNAME)INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "����"));

		_playerPet->init(PointMake(WINSIZEX + 256, WINSIZEY + 164), DIR_ELEVEN, PET_STAND, _playerPet->getPetName(), true);
		_vPet.push_back(_playerPet);
	}

	//�� ������ġ ���
	for (int i = 0; i < _vPet.size(); ++i)
	{
		if (_vPet[i]->getIsPlayerPet() == false) continue;

		_vPet[i]->setMoveEndX(512);
		_vPet[i]->setMoveEndY(399);
	}

	_isWriteInidata = true;
}

void battleMap::appearEnemy()
{
	if (_battleTurn != TURN_START_BATTLE) return;

	for (int i = 0; i < _vPet.size(); ++i)
	{
		if (_vPet[i]->getIsPlayerPet() == true) continue;

		if (_vPet[i]->getMoveEndX() > _vPet[i]->getTileCenterX())
		{
			_vPet[i]->setTileCenterX(_vPet[i]->getTileCenterX() + _moveSpeedX);
		}

		if (_vPet[i]->getMoveEndY() > _vPet[i]->getTileCenterY())
		{
			_vPet[i]->setTileCenterY(_vPet[i]->getTileCenterY() + _moveSpeedY);
		}

		if (_vPet[i]->getMoveEndX() <= _vPet[i]->getTileCenterX())
		{
			_vPet[i]->setTileCenterX(_vPet[i]->getMoveEndX());
		}

		if (_vPet[i]->getMoveEndY() <= _vPet[i]->getTileCenterY())
		{
			_vPet[i]->setTileCenterY(_vPet[i]->getMoveEndY());
		}

		_vPet[i]->setImageRect(RectMakeCenter(_vPet[i]->getTileCenterX() + _vPet[i]->getImageMoveX(),
			_vPet[i]->getTileCenterY() + _vPet[i]->getImageMoveY(),
			_vPet[i]->getImage()->getFrameWidth(), _vPet[i]->getImage()->getFrameHeight()));
		_vPet[i]->setImageCenterX(_vPet[i]->getTileCenterX() + _vPet[i]->getImageMoveX());
		_vPet[i]->setImageCenterY(_vPet[i]->getTileCenterY() + _vPet[i]->getImageMoveY());
		_vPet[i]->setSelectRect(RectMakeCenter(_vPet[i]->getTileCenterX() + _vPet[i]->getImageMoveX(),
			_vPet[i]->getTileCenterY() + _vPet[i]->getImageMoveY(),
			_vPet[i]->getImage()->getFrameWidth() / 2, _vPet[i]->getImage()->getFrameHeight() / 2));

		if (_vPet[i]->getMoveEndX() != _vPet[i]->getTileCenterX() ||
			_vPet[i]->getMoveEndY() != _vPet[i]->getTileCenterY())
		{
			_vPet[i]->setIsMove(true);
		}

		else _vPet[i]->setIsMove(false);
	}
}

void battleMap::playerPetMove()
{
	if (_battleTurn != TURN_START_BATTLE) return;

	for (int i = 0; i < _vPet.size(); ++i)
	{
		if (_vPet[i]->getIsPlayerPet() == false) continue;

		if (_vPet[i]->getMoveEndX() < _vPet[i]->getTileCenterX())
		{
			_vPet[i]->setTileCenterX(_vPet[i]->getTileCenterX() - _moveSpeedX);
		}

		if (_vPet[i]->getMoveEndY() < _vPet[i]->getTileCenterY())
		{
			_vPet[i]->setTileCenterY(_vPet[i]->getTileCenterY() - _moveSpeedY);
		}

		if (_vPet[i]->getMoveEndX() >= _vPet[i]->getTileCenterX())
		{
			_vPet[i]->setTileCenterX(_vPet[i]->getMoveEndX());
		}

		if (_vPet[i]->getMoveEndY() >= _vPet[i]->getTileCenterY())
		{
			_vPet[i]->setTileCenterY(_vPet[i]->getMoveEndY());
		}

		_vPet[i]->setImageRect(RectMakeCenter(_vPet[i]->getTileCenterX() + _vPet[i]->getImageMoveX(),
			_vPet[i]->getTileCenterY() + _vPet[i]->getImageMoveY(),
			_vPet[i]->getImage()->getFrameWidth(), _vPet[i]->getImage()->getFrameHeight()));
		_vPet[i]->setImageCenterX(_vPet[i]->getTileCenterX() + _vPet[i]->getImageMoveX());
		_vPet[i]->setImageCenterY(_vPet[i]->getTileCenterY() + _vPet[i]->getImageMoveY());
		_vPet[i]->setSelectRect(RectMakeCenter(_vPet[i]->getTileCenterX() + _vPet[i]->getImageMoveX(),
			_vPet[i]->getTileCenterY() + _vPet[i]->getImageMoveY(),
			_vPet[i]->getImage()->getFrameWidth() / 2, _vPet[i]->getImage()->getFrameHeight() / 2));

		if (_vPet[i]->getMoveEndX() != _vPet[i]->getTileCenterX() ||
			_vPet[i]->getMoveEndY() != _vPet[i]->getTileCenterY())
		{
			_vPet[i]->setIsMove(true);
		}

		else _vPet[i]->setIsMove(false);
	}
}

void battleMap::setPlayer()
{
	if (_isSetPlayer == true) return;

	_player->setPlayerCenterX(WINSIZEX + 288);
	_player->setPlayerCenterY(WINSIZEY + 223);
	_player->setPlayerDirection(DIR_ELEVEN);
	_player->setPlayerRect(RectMakeCenter(_player->getPlayerCenterX() + _player->getPlayerImageMoveX(),
		_player->getPlayerCenterY() + _player->getPlayerImageMoveY(),
		_player->getPlayerImage()->getFrameWidth(), _player->getPlayerImage()->getFrameHeight()));
	_player->setPlayerImageCenterX(_player->getPlayerCenterX() + _player->getPlayerImageMoveX());
	_player->setPlayerImageCenterY(_player->getPlayerCenterY() + _player->getPlayerImageMoveY());
	_player->setPlayerTileRect(RectMakeCenter(_player->getPlayerCenterX(), _player->getPlayerCenterY(),
		64, 47));
	_player->setSelectRect(RectMakeCenter(_player->getPlayerCenterX() + _player->getPlayerImageMoveX(),
		_player->getPlayerCenterY() + _player->getPlayerImageMoveY(),
		_player->getPlayerImage()->getFrameWidth() / 2, _player->getPlayerImage()->getFrameHeight() - 20));

	_player->setPlayerMoveEndX(576);
	_player->setPlayerMoveEndY(446);

	_isSetPlayer = true;
}

void battleMap::playerMove()
{
	if (_battleTurn != TURN_START_BATTLE) return;

	if (_player->getPlayerMoveEndX() < _player->getPlayerCenterX())
	{
		_player->setPlayerCenterX(_player->getPlayerCenterX() - _moveSpeedX);
	}

	if (_player->getPlayerMoveEndY() < _player->getPlayerCenterY())
	{
		_player->setPlayerCenterY(_player->getPlayerCenterY() - _moveSpeedY);
	}

	if (_player->getPlayerMoveEndX() >= _player->getPlayerCenterX())
	{
		_player->setPlayerCenterX(_player->getPlayerMoveEndX());
	}

	if (_player->getPlayerMoveEndY() >= _player->getPlayerCenterY())
	{
		_player->setPlayerCenterY(_player->getPlayerMoveEndY());
	}

	_player->setPlayerRect(RectMakeCenter(_player->getPlayerCenterX() + _player->getPlayerImageMoveX(),
		_player->getPlayerCenterY() + _player->getPlayerImageMoveY(),
		_player->getPlayerImage()->getFrameWidth(), _player->getPlayerImage()->getFrameHeight()));
	_player->setPlayerImageCenterX(_player->getPlayerCenterX() + _player->getPlayerImageMoveX());
	_player->setPlayerImageCenterY(_player->getPlayerCenterY() + _player->getPlayerImageMoveY());
	_player->setPlayerTileRect(RectMakeCenter(_player->getPlayerCenterX(), _player->getPlayerCenterY(),
		64, 47));
	_player->setSelectRect(RectMakeCenter(_player->getPlayerCenterX() + _player->getPlayerImageMoveX(),
		_player->getPlayerCenterY() + _player->getPlayerImageMoveY(),
		_player->getPlayerImage()->getFrameWidth() / 2, _player->getPlayerImage()->getFrameHeight() - 20));

	if (_player->getPlayerMoveEndX() != _player->getPlayerCenterX() ||
		_player->getPlayerMoveEndY() != _player->getPlayerCenterY())
	{
		_player->setIsPlayerMove(true);
	}

	else _player->setIsPlayerMove(false);
}

void battleMap::setSelectTime()
{
	_selectTimeCount = 31;
	_worldTime = TIMEMANAGER->getWorldTime();

	for (int i = 0; i < 2; ++i)
	{
		_battleTime[i].img = IMAGEMANAGER->findImage("battleTime");
		_battleTime[i].rc = RectMakeCenter(WINSIZEX / 2 - 20 + i * 30, WINSIZEY / 2,
			_battleTime[i].img->getFrameWidth(), _battleTime[i].img->getFrameHeight());
		_battleTime[0].currentFrameX = _selectTimeCount / 10;
		_battleTime[1].currentFrameX = _selectTimeCount % 10;
		_battleTime[i].currentFrameY = 0;
	}
}

void battleMap::updateSelecTime()
{
	if (_battleTurn != TURN_PLAYER && _battleTurn != TURN_PET) return;

	if (TIMEMANAGER->getWorldTime() - _worldTime >= 1)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
		_selectTimeCount--;

		if (_selectTimeCount < 0)
		{
			for (int i = 0; i < _vPet.size(); ++i)
			{
				if (_vPet[i]->getIsPlayerPet() == false) continue;

				_vPet[i]->_petSkill = PET_SKILL_NONE;
			}

			_battleTurn = TURN_BATTLE;
		}
	}

	_battleTime[0].currentFrameX = _selectTimeCount / 10;
	_battleTime[1].currentFrameX = _selectTimeCount % 10;
}

void battleMap::SelectRender()
{
	if (_battleTurn == TURN_CLOSE_BATTLE) return;

	HPEN myPen = CreatePen(PS_DASH, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	for (_viPet = _vPet.begin(); _viPet != _vPet.end(); ++_viPet)
	{
		if (PtInRect(&(*_viPet)->getTileRect(), _ptMouse))
		{
			Rectangle(getMemDC(), *&(*_viPet)->getSelectRect());
		}
	}

	if (PtInRect(&_player->getPlayerTileRect(), _ptMouse))
	{
		Rectangle(getMemDC(), *&_player->getSelectRect());
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void battleMap::infoRender()
{
	if (_battleTurn == TURN_CLOSE_BATTLE) return;

	//������ ���� ������(����, �̸���)
	for (int i = 0; i < _vPet.size(); ++i)
	{
		if (PtInRect(&_vPet[i]->getTileRect(), _ptMouse))
		{
			if (_vPet[i]->getIsPlayerPet() == true) continue;

			string petName = _vPet[i]->getPetNameString();
			int petLevel = _vPet[i]->getLevel();
			char level[256];
			char levelInfo[256];

			HFONT font = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
				0, 0, 0, 0, TEXT("�������"));
			HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
			SetBkMode(getMemDC(), TRANSPARENT);

			//������ ����ֱ�
			SetTextColor(getMemDC(), RGB(255, 255, 255));

			TextOut(getMemDC(), 34, 580, petName.c_str(), strlen(petName.c_str()));

			sprintf(levelInfo, "���� : ");
			TextOut(getMemDC(), 110, 580, levelInfo, strlen(levelInfo));

			TextOut(getMemDC(), 160, 580, itoa(petLevel, level, 10), strlen(itoa(petLevel, level, 10)));

			SelectObject(getMemDC(), oldFont);
			DeleteObject(font);
			SetBkMode(getMemDC(), OPAQUE);
		}
	}

	//�츮�� ����(�̸�, ����, ����ü�� / ��ü��)
	for (int i = 0; i < _vPet.size(); ++i)
	{
		if (_vPet[i]->getIsPlayerPet() == false) continue;

		if (PtInRect(&_vPet[i]->getTileRect(), _ptMouse))
		{
			string petName = _vPet[i]->getPetNameString();
			int petLevel = _vPet[i]->getLevel();
			int currentStamina = _vPet[i]->getPetCurrentStamina();
			int totalStamina = _vPet[i]->getPetTotalStamina();
			char level[256];
			char levelInfo[256];
			char stamina[256];
			char cs[256];
			char ts[256];
			char slash[256];

			HFONT font = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
				0, 0, 0, 0, TEXT("�������"));
			HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
			SetBkMode(getMemDC(), TRANSPARENT);

			//������ ����ֱ�
			SetTextColor(getMemDC(), RGB(255, 255, 255));

			TextOut(getMemDC(), 34, 580, petName.c_str(), strlen(petName.c_str()));

			sprintf(levelInfo, "���� : ");
			TextOut(getMemDC(), 110, 580, levelInfo, strlen(levelInfo));

			TextOut(getMemDC(), 160, 580, itoa(petLevel, level, 10), strlen(itoa(petLevel, level, 10)));

			sprintf(stamina, "ü�� : ");
			TextOut(getMemDC(), 200, 580, stamina, strlen(stamina));

			TextOut(getMemDC(), 250, 580, itoa(currentStamina, cs, 10), strlen(itoa(currentStamina, cs, 10)));

			sprintf(slash, " / ");
			TextOut(getMemDC(), 270, 580, slash, strlen(slash));

			TextOut(getMemDC(), 290, 580, itoa(totalStamina, ts, 10), strlen(itoa(totalStamina, ts, 10)));

			SelectObject(getMemDC(), oldFont);
			DeleteObject(font);
			SetBkMode(getMemDC(), OPAQUE);
		}
	}

	if (PtInRect(&_player->getPlayerTileRect(), _ptMouse))
	{
		int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
		int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

		string playerName;
		int playerLevel;

		if (loginPlayer1 == (int)INFO_YES)
		{
			playerName = INIDATA->loadDataString("ĳ����", "�÷��̾�1", "�̸�");
			playerLevel = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "����");
		}
		if (loginPlayer2 == (int)INFO_YES)
		{
			playerName = INIDATA->loadDataString("ĳ����", "�÷��̾�2", "�̸�");
			playerLevel = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "����");
		}

		char level[256];
		char levelInfo[256];
		char stamina[256];
		char cs[256];
		char ts[256];
		char slash[256];

		HFONT font = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("�������"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);

		//������ ����ֱ�
		SetTextColor(getMemDC(), RGB(255, 255, 255));

		TextOut(getMemDC(), 34, 580, playerName.c_str(), strlen(playerName.c_str()));

		sprintf(levelInfo, "���� : ");
		TextOut(getMemDC(), 110, 580, levelInfo, strlen(levelInfo));

		TextOut(getMemDC(), 160, 580, itoa(playerLevel, level, 10), strlen(itoa(playerLevel, level, 10)));

		sprintf(stamina, "ü�� : ");
		TextOut(getMemDC(), 200, 580, stamina, strlen(stamina));

		TextOut(getMemDC(), 250, 580, itoa(_playerInfo.currentStamina, cs, 10), strlen(itoa(_playerInfo.currentStamina, cs, 10)));

		sprintf(slash, " / ");
		TextOut(getMemDC(), 270, 580, slash, strlen(slash));

		TextOut(getMemDC(), 290, 580, itoa(_playerInfo.totalStamina, ts, 10), strlen(itoa(_playerInfo.totalStamina, ts, 10)));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}
}

void battleMap::setNoticeWindow()
{
	_noticeWindow.frontImg = IMAGEMANAGER->findImage("inputWindow2");
	_noticeWindow.backImg = IMAGEMANAGER->findImage("inputWindowBack");
	_noticeWindow.frontRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 200,
		_noticeWindow.frontImg->getWidth(), _noticeWindow.frontImg->getHeight());
	_noticeWindow.backRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 200,
		_noticeWindow.backImg->getWidth(), _noticeWindow.backImg->getHeight());
}

void battleMap::startBattle()
{
	if (_isStart == true) return;

	if (TIMEMANAGER->getWorldTime() - _battleStartTime >= 1)
	{
		_battleStartTime = TIMEMANAGER->getWorldTime();
		_timeCount++;
	}

	if (_timeCount >= 4)
	{
		_timeCount = 0;
		_isStart = true;
		KEYMANAGER->setKeyDown('S', true);
	}
}


