#include "stdafx.h"
#include "firstDungeonScene.h"

firstDungeonScene::firstDungeonScene()
{
}

firstDungeonScene::~firstDungeonScene()
{
}

HRESULT firstDungeonScene::init()
{
	SOUNDMANAGER->play("scene_start", 0.4f);
	_isMusic = false;
	_isWriteInidata = false;

	_tm = new tileMap;
	_tm->init();
	writeInidata();

	_player = new player;
	_player->init();

	_tm->setPlayerMemoryAddressLink(_player);

	_worldTime = TIMEMANAGER->getWorldTime();
	_timeCount = 0;
	_FDNotice.isEndTime = false;
	_FDNotice.frontImg = IMAGEMANAGER->findImage("inputWindow2");
	_FDNotice.backImg = IMAGEMANAGER->findImage("inputWindowBack");
	_FDNotice.notice = "���� 1��";

	return S_OK;
}

void firstDungeonScene::release()
{
	SOUNDMANAGER->stop("dungeon1_bg");
}

void firstDungeonScene::update()
{
	if (_isMusic == false)
	{
		SOUNDMANAGER->play("dungeon1_bg", 0.4f);
		_isMusic = true;
	}
	_player->update();
	_tm->update();
	firstDungeonNotice();
}

void firstDungeonScene::render()
{
	_tm->render();
	_player->render();

	if (_FDNotice.isEndTime == false)
	{
		_FDNotice.backImg->alphaRender(getMemDC(), CAMERAMANAGER->getCameraCenterX() - _FDNotice.backImg->getWidth() / 2,
			CAMERAMANAGER->getCameraCenterY() - _FDNotice.backImg->getHeight() / 2, 200);
		_FDNotice.frontImg->render(getMemDC(), _FDNotice.rc.left, _FDNotice.rc.top);

		HFONT font = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY������B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);

		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), _FDNotice.rc.left + 90, _FDNotice.rc.top + 50,
			_FDNotice.notice.c_str(), strlen(_FDNotice.notice.c_str()));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}
}

void firstDungeonScene::writeInidata()
{
	if (_isWriteInidata == true) return;

	//�α��εǾ��ִ� �÷��̾�Ȯ��
	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	if (loginPlayer1 == (int)INFO_YES)
	{
		int convertPlace = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "����̵�");
		INIDATA->addData("�÷��̾�1", "�������", "����1");
		INIDATA->iniSave("ĳ����");
		string prePlace = INIDATA->loadDataString("ĳ����", "�÷��̾�1", "�������");

		//����̵��������(�������� ��ġ���Ѿ���)
		if (convertPlace == (int)INFO_YES)
		{
			if (prePlace == "����")
			{
				//�÷��̾� ��ġ����(������ġ�� ��ǥ ã��)
				_tm->setCamera(48, 60);
			}
		}

		//����̵��� �ƴ� �������� �α׾ƿ��ϰ� �ٽ� �����������
		if (convertPlace == (int)INFO_NO)
		{
			int currentIsoX = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "������ǥX");
			int currentIsoY = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "������ǥY");
			_tm->setCamera(currentIsoX, currentIsoY);
		}

		//����̵����� �ƴϿ��� �ٲ��ֱ�
		convertPlace = (int)INFO_NO;
		char cp[256];
		INIDATA->addData("�÷��̾�1", "����̵�", _itoa(convertPlace, cp, 10));
		INIDATA->iniSave("ĳ����");
	}

	//�÷��̾�2�� ���
	if (loginPlayer2 == (int)INFO_YES)
	{
		int convertPlace = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "����̵�");
		INIDATA->addData("�÷��̾�2", "�������", "����1");
		INIDATA->iniSave("ĳ����");
		string prePlace = INIDATA->loadDataString("ĳ����", "�÷��̾�2", "�������");

		//����̵��������(�������� ��ġ���Ѿ���)
		if (convertPlace == (int)INFO_YES)
		{
			if (prePlace == "����")
			{
				//�÷��̾� ��ġ����(������ġ�� ��ǥ ã��)
				_tm->setCamera(48, 60);
			}
		}

		//����̵��� �ƴ� �������� �α׾ƿ��ϰ� �ٽ� �����������
		if (convertPlace == (int)INFO_NO)
		{
			int currentIsoX = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "������ǥX");
			int currentIsoY = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "������ǥY");
			_tm->setCamera(currentIsoX, currentIsoY);
		}

		//����̵����� �ƴϿ��� �ٲ��ֱ�
		convertPlace = (int)INFO_NO;
		char cp[256];
		INIDATA->addData("�÷��̾�2", "����̵�", _itoa(convertPlace, cp, 10));
		INIDATA->iniSave("ĳ����");
	}


	_tm->load("firstDungeon.map");
	_isWriteInidata = true;
}

void firstDungeonScene::firstDungeonNotice()
{
	if (_FDNotice.isEndTime == true) return;

	_FDNotice.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(),
		_FDNotice.frontImg->getWidth(), _FDNotice.frontImg->getHeight());

	if (TIMEMANAGER->getWorldTime() - _worldTime >= 1)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
		_timeCount++;
	}

	if (_timeCount >= 3)
	{
		_timeCount = 0;
		_FDNotice.isEndTime = true;
	}
}

