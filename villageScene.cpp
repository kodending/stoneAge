#include "stdafx.h"
#include "villageScene.h"

villageScene::villageScene()
{
}

villageScene::~villageScene()
{
}

HRESULT villageScene::init()
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
	_villageNotice.isEndTime = false;
	_villageNotice.frontImg = IMAGEMANAGER->findImage("inputWindow2");
	_villageNotice.backImg = IMAGEMANAGER->findImage("inputWindowBack");
	_villageNotice.notice = "���ʸ���";

	return S_OK;
}

void villageScene::release()
{
	SOUNDMANAGER->stop("village_bg");
}

void villageScene::update()
{
	if (_isMusic == false)
	{
		SOUNDMANAGER->play("village_bg", 0.4f);
		_isMusic = true;
	}
	_player->update();
	_tm->update();
	villageNotice();
}

void villageScene::render()
{
	_tm->render();
	_player->render();

	if (_villageNotice.isEndTime == false)
	{
		_villageNotice.backImg->alphaRender(getMemDC(), CAMERAMANAGER->getCameraCenterX() - _villageNotice.backImg->getWidth() / 2,
			CAMERAMANAGER->getCameraCenterY() - _villageNotice.backImg->getHeight() / 2, 200);
		_villageNotice.frontImg->render(getMemDC(), _villageNotice.rc.left, _villageNotice.rc.top);

		HFONT font = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY������B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);

		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), _villageNotice.rc.left + 95, _villageNotice.rc.top + 50,
			_villageNotice.notice.c_str(), strlen(_villageNotice.notice.c_str()));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}
}

//��� �����
void villageScene::writeInidata()
{
	if (_isWriteInidata == true) return;

	//�α��εǾ��ִ� �÷��̾�Ȯ��
	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	//�÷��̾�1�� ���
	if (loginPlayer1 == (int)INFO_YES)
	{
		int convertPlace = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "����̵�");
		INIDATA->addData("�÷��̾�1", "�������", "����");
		INIDATA->iniSave("ĳ����");
		string prePlace = INIDATA->loadDataString("ĳ����", "�÷��̾�1", "�������");

		//����̵��������(�������� ��ġ���Ѿ���)
		if (convertPlace == (int)INFO_YES)
		{
			if (prePlace == "����1")
			{
				//�÷��̾� ��ġ����(�����Ա��� ��ǥ ã��)
				_tm->setCamera(31, 41);
			}

			if (prePlace == "�����ۻ���")
			{
				//�÷��̾� ��ġ����(�����Ա��� ��ǥ ã��)
				_tm->setCamera(53, 28);
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
		INIDATA->addData("�÷��̾�2", "�������", "����");
		INIDATA->iniSave("ĳ����");
		string prePlace = INIDATA->loadDataString("ĳ����", "�÷��̾�2", "�������");

		//����̵��������(�������� ��ġ���Ѿ���)
		if (convertPlace == (int)INFO_YES)
		{
			if (prePlace == "����1")
			{
				//�÷��̾� ��ġ����(�����Ա��� ��ǥ ã��)
				_tm->setCamera(31, 41);
			}

			if (prePlace == "�����ۻ���")
			{
				//�÷��̾� ��ġ����(�����Ա��� ��ǥ ã��)
				_tm->setCamera(53, 28);
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

	_tm->load("village.map");
	_isWriteInidata = true;
}

void villageScene::villageNotice()
{
	if (_villageNotice.isEndTime == true) return;

	_villageNotice.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(),
		_villageNotice.frontImg->getWidth(), _villageNotice.frontImg->getHeight());

	if (TIMEMANAGER->getWorldTime() - _worldTime >= 1)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
		_timeCount++;
	}

	if (_timeCount >= 3)
	{
		_timeCount = 0;
		_villageNotice.isEndTime = true;
	}
}
