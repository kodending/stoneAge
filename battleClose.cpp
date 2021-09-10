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
		SCENEMANAGER->changeScene("����1");
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
	_closeNotice.noticeText = "��� ����";

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
		0, 0, 0, 0, TEXT("HY������B"));
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
		if (_elapsedSec % 3 == 1) _closeNotice.noticeText = "������� ������.";
		if (_elapsedSec % 3 == 2) _closeNotice.noticeText = "������� ������..";
		if (_elapsedSec % 3 == 0) _closeNotice.noticeText = "������� ������...";
		_moveText = 110;
	}
}

void battleClose::saveInidata(battleMap * battleMap)
{
	if (_isSave == true) return;

	//�÷��̾���� ����
	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	//�÷��̾�1 �α����������
	if (loginPlayer1 == (int)INFO_YES)
	{
		char currentStamina[256];

		if (battleMap->_player->_isDead == true)
		{
			INIDATA->addData("�÷��̾�1", "����ü��", _itoa(1, currentStamina, 10));
			int charming = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�ŷ�");
			charming -= 4;
			char charm[256];
			INIDATA->addData("�÷��̾�1", "�ŷ�", _itoa(charming, charm, 10));
		}

		else
		{
			INIDATA->addData("�÷��̾�1", "����ü��", _itoa(battleMap->_playerInfo.currentStamina, currentStamina, 10));
		}

		INIDATA->iniSave("ĳ����");
	}

	//�÷��̾�2 �α����������
	if (loginPlayer1 == (int)INFO_YES)
	{
		char currentStamina[256];

		if (battleMap->_player->_isDead == true)
		{
			INIDATA->addData("�÷��̾�2", "����ü��", _itoa(1, currentStamina, 10));
			int charming = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�ŷ�");
			charming -= 4;
			char charm[256];
			INIDATA->addData("�÷��̾�2", "�ŷ�", _itoa(charming, charm, 10));
		}

		else
		{
			INIDATA->addData("�÷��̾�2", "����ü��", _itoa(battleMap->_playerInfo.currentStamina, currentStamina, 10));
		}

		INIDATA->iniSave("ĳ����");
	}

	//�÷��̾� �� ����
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_vPet[i]->getIsPlayerPet() == false) continue;

		//�÷��̾� 1 ���� ���
		if (loginPlayer1 == (int)INFO_YES)
		{
			string pet1_mode = INIDATA->loadDataString("�÷��̾�1_��", "��1", "���");
			string pet2_mode = INIDATA->loadDataString("�÷��̾�1_��", "��2", "���");
			string pet3_mode = INIDATA->loadDataString("�÷��̾�1_��", "��3", "���");
			string pet4_mode = INIDATA->loadDataString("�÷��̾�1_��", "��4", "���");
			string pet5_mode = INIDATA->loadDataString("�÷��̾�1_��", "��5", "���");

			if (pet1_mode == "��Ʋ")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("��1", "���", "�޽�");
					INIDATA->addData("��1", "����ü��", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("�÷��̾�1_��", "��1", "�漺��");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("��1", "�漺��", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("��1", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet2_mode == "��Ʋ")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("��2", "���", "�޽�");
					INIDATA->addData("��2", "����ü��", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("�÷��̾�1_��", "��2", "�漺��");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("��2", "�漺��", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("��2", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet3_mode == "��Ʋ")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("��3", "���", "�޽�");
					INIDATA->addData("��3", "����ü��", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("�÷��̾�1_��", "��3", "�漺��");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("��3", "�漺��", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("��3", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet4_mode == "��Ʋ")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("��4", "���", "�޽�");
					INIDATA->addData("��4", "����ü��", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("�÷��̾�1_��", "��4", "�漺��");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("��4", "�漺��", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("��4", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet5_mode == "��Ʋ")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("��5", "���", "�޽�");
					INIDATA->addData("��5", "����ü��", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("�÷��̾�1_��", "��5", "�漺��");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("��5", "�漺��", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("��5", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			INIDATA->iniSave("�÷��̾�1_��");
		}

		//�÷��̾� 1 ���� ���
		if (loginPlayer2 == (int)INFO_YES)
		{
			string pet1_mode = INIDATA->loadDataString("�÷��̾�2_��", "��1", "���");
			string pet2_mode = INIDATA->loadDataString("�÷��̾�2_��", "��2", "���");
			string pet3_mode = INIDATA->loadDataString("�÷��̾�2_��", "��3", "���");
			string pet4_mode = INIDATA->loadDataString("�÷��̾�2_��", "��4", "���");
			string pet5_mode = INIDATA->loadDataString("�÷��̾�2_��", "��5", "���");

			if (pet1_mode == "��Ʋ")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("��1", "���", "�޽�");
					INIDATA->addData("��1", "����ü��", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("�÷��̾�2_��", "��1", "�漺��");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("��1", "�漺��", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("��1", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet2_mode == "��Ʋ")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("��2", "���", "�޽�");
					INIDATA->addData("��2", "����ü��", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("�÷��̾�2_��", "��2", "�漺��");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("��2", "�漺��", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("��2", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet3_mode == "��Ʋ")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("��3", "���", "�޽�");
					INIDATA->addData("��3", "����ü��", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("�÷��̾�2_��", "��3", "�漺��");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("��3", "�漺��", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("��3", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet4_mode == "��Ʋ")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("��4", "���", "�޽�");
					INIDATA->addData("��4", "����ü��", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("�÷��̾�2_��", "��4", "�漺��");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("��4", "�漺��", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("��4", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}

			if (pet5_mode == "��Ʋ")
			{
				char currentStamina[256];

				if (battleMap->_vPet[i]->_isDead == true)
				{
					INIDATA->addData("��5", "���", "�޽�");
					INIDATA->addData("��5", "����ü��", _itoa(1, currentStamina, 10));
					int loyality = INIDATA->loadDataInterger("�÷��̾�2_��", "��5", "�漺��");
					loyality -= 4;
					char loyal[256];
					INIDATA->addData("��5", "�漺��", _itoa(loyality, loyal, 10));
				}

				else INIDATA->addData("��5", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
			}


			INIDATA->iniSave("�÷��̾�2_��");
		}
	}

	//Ȥ�� ���� ��ȹ������� ������ش�! ����
	for (int i = 0; i < battleMap->_vPet.size(); ++i)
	{
		if (battleMap->_player->_isEscapeSuccess == true) break;
		if (battleMap->_player->_isDead == true) break;
		if (battleMap->_vPet[i]->getIsPlayerPet() == true) continue;
		if (battleMap->_vPet[i]->_isCatched == false) continue;

		//�÷��̾� 1�� ���
		if (loginPlayer1 == (int)INFO_YES)
		{
			string pet1_exist = INIDATA->loadDataString("�÷��̾�1_��", "��1", "�־�?");
			string pet2_exist = INIDATA->loadDataString("�÷��̾�1_��", "��2", "�־�?");
			string pet3_exist = INIDATA->loadDataString("�÷��̾�1_��", "��3", "�־�?");
			string pet4_exist = INIDATA->loadDataString("�÷��̾�1_��", "��4", "�־�?");
			string pet5_exist = INIDATA->loadDataString("�÷��̾�1_��", "��5", "�־�?");

			//ù��° ��â�� ����������
			if (pet1_exist != "�־�" && _isSavePet[0] == false)
			{
				char type[256];
				INIDATA->addData("��1", "����", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("��1", "����", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("��1", "�������ġ", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("��1", "��������ġ", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("��1", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("��1", "���ݷ�", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("��1", "����", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("��1", "���߷�", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("��1", "�漺��", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("��1", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("��1", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("��1", "ȭ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("��1", "ǳ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("��1", "�־�?", "�־�");
				INIDATA->addData("��1", "���", "�޽�");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("��1", "�̸�", name);
				char totalStamina[256];
				INIDATA->addData("��1", "��üü��", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("��1", "��ų1", "����");
				INIDATA->addData("��1", "��ų2", "���");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("��1", "ž�°���", "����");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("��1", "ž�°���", "�Ұ���");
				char skill1[256];
				INIDATA->addData("��1", "���1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("��1", "���2", _itoa(2, skill2, 10));
				INIDATA->iniSave("�÷��̾�1_��");
				_isSavePet[0] = true;
				continue;
			}

			//�ι�° ��â�� ����������
			if (pet2_exist != "�־�" && _isSavePet[1] == false)
			{
				char type[256];
				INIDATA->addData("��2", "����", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("��2", "����", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("��2", "�������ġ", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("��2", "��������ġ", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("��2", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("��2", "���ݷ�", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("��2", "����", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("��2", "���߷�", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("��2", "�漺��", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("��2", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("��2", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("��2", "ȭ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("��2", "ǳ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("��2", "�־�?", "�־�");
				INIDATA->addData("��2", "���", "�޽�");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("��2", "�̸�", name);
				char totalStamina[256];
				INIDATA->addData("��2", "��üü��", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("��2", "��ų1", "����");
				INIDATA->addData("��2", "��ų2", "���");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("��2", "ž�°���", "����");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("��2", "ž�°���", "�Ұ���");
				char skill1[256];
				INIDATA->addData("��2", "���1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("��2", "���2", _itoa(2, skill2, 10));
				INIDATA->iniSave("�÷��̾�1_��");
				_isSavePet[1] = true;
				continue;
			}

			//����° ��â�� ����������
			if (pet3_exist != "�־�" && _isSavePet[2] == false)
			{
				char type[256];
				INIDATA->addData("��3", "����", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("��3", "����", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("��3", "�������ġ", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("��3", "��������ġ", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("��3", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("��3", "���ݷ�", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("��3", "����", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("��3", "���߷�", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("��3", "�漺��", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("��3", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("��3", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("��3", "ȭ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("��3", "ǳ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("��3", "�־�?", "�־�");
				INIDATA->addData("��3", "���", "�޽�");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("��3", "�̸�", name);
				char totalStamina[256];
				INIDATA->addData("��3", "��üü��", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("��3", "��ų1", "����");
				INIDATA->addData("��3", "��ų2", "���");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("��3", "ž�°���", "����");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("��3", "ž�°���", "�Ұ���");
				char skill1[256];
				INIDATA->addData("��3", "���1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("��3", "���2", _itoa(2, skill2, 10));
				INIDATA->iniSave("�÷��̾�1_��");
				_isSavePet[2] = true;
				continue;
			}

			//�׹�° ��â�� ����������
			if (pet4_exist != "�־�" && _isSavePet[3] == false)
			{
				char type[256];
				INIDATA->addData("��4", "����", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("��4", "����", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("��4", "�������ġ", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("��4", "��������ġ", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("��4", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("��4", "���ݷ�", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("��4", "����", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("��4", "���߷�", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("��4", "�漺��", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("��4", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("��4", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("��4", "ȭ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("��4", "ǳ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("��4", "�־�?", "�־�");
				INIDATA->addData("��4", "���", "�޽�");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("��4", "�̸�", name);
				char totalStamina[256];
				INIDATA->addData("��4", "��üü��", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("��4", "��ų1", "����");
				INIDATA->addData("��4", "��ų2", "���");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("��4", "ž�°���", "����");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("��4", "ž�°���", "�Ұ���");
				char skill1[256];
				INIDATA->addData("��4", "���1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("��4", "���2", _itoa(2, skill2, 10));
				INIDATA->iniSave("�÷��̾�1_��");
				_isSavePet[3] = true;
				continue;
			}

			//�ټ���° ��â�� ����������
			if (pet5_exist != "�־�" && _isSavePet[4] == false)
			{
				char type[256];
				INIDATA->addData("��5", "����", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("��5", "����", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("��5", "�������ġ", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("��5", "��������ġ", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("��5", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("��5", "���ݷ�", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("��5", "����", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("��5", "���߷�", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("��5", "�漺��", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("��5", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("��5", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("��5", "ȭ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("��5", "ǳ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("��5", "�־�?", "�־�");
				INIDATA->addData("��5", "���", "�޽�");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("��5", "�̸�", name);
				char totalStamina[256];
				INIDATA->addData("��5", "��üü��", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("��5", "��ų1", "����");
				INIDATA->addData("��5", "��ų2", "���");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("��5", "ž�°���", "����");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("��5", "ž�°���", "�Ұ���");
				char skill1[256];
				INIDATA->addData("��5", "���1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("��5", "���2", _itoa(2, skill2, 10));
				INIDATA->iniSave("�÷��̾�1_��");
				_isSavePet[4] = true;
				continue;
			}
		}

		//�÷��̾� 2�� ���
		if (loginPlayer1 == (int)INFO_YES)
		{
			string pet1_exist = INIDATA->loadDataString("�÷��̾�2_��", "��1", "�־�?");
			string pet3_exist = INIDATA->loadDataString("�÷��̾�2_��", "��3", "�־�?");
			string pet2_exist = INIDATA->loadDataString("�÷��̾�2_��", "��2", "�־�?");
			string pet4_exist = INIDATA->loadDataString("�÷��̾�2_��", "��4", "�־�?");
			string pet5_exist = INIDATA->loadDataString("�÷��̾�2_��", "��5", "�־�?");

			//ù��° ��â�� ����������
			if (pet1_exist != "�־�" && _isSavePet[0] == false)
			{
				char type[256];
				INIDATA->addData("��1", "����", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("��1", "����", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("��1", "�������ġ", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("��1", "��������ġ", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("��1", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("��1", "���ݷ�", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("��1", "����", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("��1", "���߷�", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("��1", "�漺��", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("��1", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("��1", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("��1", "ȭ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("��1", "ǳ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("��1", "�־�?", "�־�");
				INIDATA->addData("��1", "���", "�޽�");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("��1", "�̸�", name);
				char totalStamina[256];
				INIDATA->addData("��1", "��üü��", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("��1", "��ų1", "����");
				INIDATA->addData("��1", "��ų2", "���");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("��1", "ž�°���", "����");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("��1", "ž�°���", "�Ұ���");
				char skill1[256];
				INIDATA->addData("��1", "���1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("��1", "���2", _itoa(2, skill2, 10));
				INIDATA->iniSave("�÷��̾�2_��");
				_isSavePet[0] = true;
				continue;
			}

			//�ι�° ��â�� ����������
			if (pet2_exist != "�־�" && _isSavePet[1] == false)
			{
				char type[256];
				INIDATA->addData("��2", "����", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("��2", "����", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("��2", "�������ġ", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("��2", "��������ġ", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("��2", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("��2", "���ݷ�", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("��2", "����", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("��2", "���߷�", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("��2", "�漺��", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("��2", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("��2", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("��2", "ȭ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("��2", "ǳ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("��2", "�־�?", "�־�");
				INIDATA->addData("��2", "���", "�޽�");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("��2", "�̸�", name);
				char totalStamina[256];
				INIDATA->addData("��2", "��üü��", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("��2", "��ų1", "����");
				INIDATA->addData("��2", "��ų2", "���");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("��2", "ž�°���", "����");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("��2", "ž�°���", "�Ұ���");
				char skill1[256];
				INIDATA->addData("��2", "���1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("��2", "���2", _itoa(2, skill2, 10));
				INIDATA->iniSave("�÷��̾�2_��");
				_isSavePet[1] = true;
				continue;
			}

			//����° ��â�� ����������
			if (pet2_exist != "�־�" && _isSavePet[2] == false)
			{
				char type[256];
				INIDATA->addData("��3", "����", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("��3", "����", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("��3", "�������ġ", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("��3", "��������ġ", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("��3", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("��3", "���ݷ�", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("��3", "����", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("��3", "���߷�", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("��3", "�漺��", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("��3", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("��3", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("��3", "ȭ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("��3", "ǳ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("��3", "�־�?", "�־�");
				INIDATA->addData("��3", "���", "�޽�");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("��3", "�̸�", name);
				char totalStamina[256];
				INIDATA->addData("��3", "��üü��", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("��3", "��ų1", "����");
				INIDATA->addData("��3", "��ų2", "���");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("��3", "ž�°���", "����");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("��3", "ž�°���", "�Ұ���");
				char skill1[256];
				INIDATA->addData("��3", "���1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("��3", "���2", _itoa(2, skill2, 10));
				INIDATA->iniSave("�÷��̾�2_��");
				_isSavePet[2] = true;
				continue;
			}

			//�׹�° ��â�� ����������
			if (pet2_exist != "�־�" && _isSavePet[3] == false)
			{
				char type[256];
				INIDATA->addData("��4", "����", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("��4", "����", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("��4", "�������ġ", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("��4", "��������ġ", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("��4", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("��4", "���ݷ�", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("��4", "����", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("��4", "���߷�", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("��4", "�漺��", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("��4", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("��4", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("��4", "ȭ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("��4", "ǳ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("��4", "�־�?", "�־�");
				INIDATA->addData("��4", "���", "�޽�");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("��4", "�̸�", name);
				char totalStamina[256];
				INIDATA->addData("��4", "��üü��", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("��4", "��ų1", "����");
				INIDATA->addData("��4", "��ų2", "���");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("��4", "ž�°���", "����");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("��4", "ž�°���", "�Ұ���");
				char skill1[256];
				INIDATA->addData("��4", "���1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("��4", "���2", _itoa(2, skill2, 10));
				INIDATA->iniSave("�÷��̾�2_��");
				_isSavePet[3] = true;
				continue;
			}

			//�ټ���° ��â�� ����������
			if (pet2_exist != "�־�" && _isSavePet[4] == false)
			{
				char type[256];
				INIDATA->addData("��5", "����", _itoa((int)battleMap->_vPet[i]->getPetName(), type, 10));
				char level[256];
				INIDATA->addData("��5", "����", _itoa(battleMap->_vPet[i]->getLevel(), level, 10));
				char currentEXP[256];
				INIDATA->addData("��5", "�������ġ", _itoa(0, currentEXP, 10));
				char nextEXP[256];
				INIDATA->addData("��5", "��������ġ", _itoa(2, nextEXP, 10));
				char currentStamina[256];
				INIDATA->addData("��5", "����ü��", _itoa(battleMap->_vPet[i]->getPetCurrentStamina(), currentStamina, 10));
				char attackPower[256];
				INIDATA->addData("��5", "���ݷ�", _itoa(battleMap->_vPet[i]->getPetAttackPower(), attackPower, 10));
				char defensePower[256];
				INIDATA->addData("��5", "����", _itoa(battleMap->_vPet[i]->getPetDefensePower(), defensePower, 10));
				char speedPower[256];
				INIDATA->addData("��5", "���߷�", _itoa(battleMap->_vPet[i]->getPetSpeedPower(), speedPower, 10));
				char loyality[256];
				INIDATA->addData("��5", "�漺��", _itoa(65, loyality, 10));
				char attributeLand[256];
				INIDATA->addData("��5", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeLandCount(), attributeLand, 10));
				char attributeWater[256];
				INIDATA->addData("��5", "���Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWaterCount(), attributeWater, 10));
				char attributeFire[256];
				INIDATA->addData("��5", "ȭ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeFireCount(), attributeFire, 10));
				char attributeWind[256];
				INIDATA->addData("��5", "ǳ�Ӽ�", _itoa(battleMap->_vPet[i]->getAttributeWindCount(), attributeWind, 10));
				INIDATA->addData("��5", "�־�?", "�־�");
				INIDATA->addData("��5", "���", "�޽�");
				char name[256];
				strcpy(name, battleMap->_vPet[i]->getPetNameString().c_str());
				INIDATA->addData("��5", "�̸�", name);
				char totalStamina[256];
				INIDATA->addData("��5", "��üü��", _itoa(battleMap->_vPet[i]->getPetTotalStamina(), totalStamina, 10));
				INIDATA->addData("��5", "��ų1", "����");
				INIDATA->addData("��5", "��ų2", "���");
				if (battleMap->_vPet[i]->getIsAvailableRide() == true) INIDATA->addData("��5", "ž�°���", "����");
				if (battleMap->_vPet[i]->getIsAvailableRide() == false) INIDATA->addData("��5", "ž�°���", "�Ұ���");
				char skill1[256];
				INIDATA->addData("��5", "���1", _itoa(1, skill1, 10));
				char skill2[256];
				INIDATA->addData("��5", "���2", _itoa(2, skill2, 10));
				INIDATA->iniSave("�÷��̾�2_��");
				_isSavePet[4] = true;
				continue;
			}
		}
	}

	_isSave = true;
}
