#include "stdafx.h"
#include "itemShopScene.h"

itemShopScene::itemShopScene()
{
}

itemShopScene::~itemShopScene()
{
}

HRESULT itemShopScene::init()
{
	SOUNDMANAGER->play("scene_start", 0.4f);

	_isWriteInidata = false;

	_tm = new tileMap;
	_tm->init();
	writeInidata();

	_player = new player;
	_player->init();

	_tm->setPlayerMemoryAddressLink(_player);

	_worldTime = TIMEMANAGER->getWorldTime();
	_timeCount = 0;
	_itemShopNotice.isEndTime = false;
	_itemShopNotice.frontImg = IMAGEMANAGER->findImage("inputWindow2");
	_itemShopNotice.backImg = IMAGEMANAGER->findImage("inputWindowBack");
	_itemShopNotice.notice = "������ ����";

	return S_OK;
}

void itemShopScene::release()
{
}

void itemShopScene::update()
{
	_player->update();
	_tm->update();
	itemShopNotice();
}

void itemShopScene::render()
{
	_tm->render();
	_player->render();

	if (_itemShopNotice.isEndTime == false)
	{
		_itemShopNotice.backImg->alphaRender(getMemDC(), CAMERAMANAGER->getCameraCenterX() - _itemShopNotice.backImg->getWidth() / 2,
			CAMERAMANAGER->getCameraCenterY() - _itemShopNotice.backImg->getHeight() / 2, 200);
		_itemShopNotice.frontImg->render(getMemDC(), _itemShopNotice.rc.left, _itemShopNotice.rc.top);

		HFONT font = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY������B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);

		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), _itemShopNotice.rc.left + 80, _itemShopNotice.rc.top + 50,
			_itemShopNotice.notice.c_str(), strlen(_itemShopNotice.notice.c_str()));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}
}

void itemShopScene::writeInidata()
{
	if (_isWriteInidata == true) return;

	//�α��εǾ��ִ� �÷��̾�Ȯ��
	int loginPlayer1 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "�α���");
	int loginPlayer2 = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "�α���");

	//�÷��̾�1�� ���
	if (loginPlayer1 == (int)INFO_YES)
	{
		int convertPlace = INIDATA->loadDataInterger("ĳ����", "�÷��̾�1", "����̵�");
		INIDATA->addData("�÷��̾�1", "�������", "�����ۻ���");
		INIDATA->iniSave("ĳ����");
		string prePlace = INIDATA->loadDataString("ĳ����", "�÷��̾�1", "�������");

		//����̵��������(�������� ��ġ���Ѿ���)
		if (convertPlace == (int)INFO_YES)
		{
			if (prePlace == "����")
			{
				//�÷��̾� ��ġ����(�����ۼ��Ա��� ��ǥ ã��)
				_tm->setCamera(51, 64);
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
		//convertPlace = ;
		char cp[256];
		INIDATA->addData("�÷��̾�1", "����̵�", _itoa((int)INFO_NO, cp, 10));
		INIDATA->iniSave("ĳ����");
	}

	//�÷��̾�2�� ���
	if (loginPlayer2 == (int)INFO_YES)
	{
		int convertPlace = INIDATA->loadDataInterger("ĳ����", "�÷��̾�2", "����̵�");
		INIDATA->addData("�÷��̾�2", "�������", "�����ۻ���");
		INIDATA->iniSave("ĳ����");
		string prePlace = INIDATA->loadDataString("ĳ����", "�÷��̾�2", "�������");

		//����̵��������(�������� ��ġ���Ѿ���)
		if (convertPlace == (int)INFO_YES)
		{
			if (prePlace == "����")
			{
				//�÷��̾� ��ġ����(�����ۼ��Ա��� ��ǥ ã��)
				_tm->setCamera(51, 64);
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

	_tm->load("shop.map");
	_isWriteInidata = true;
}

void itemShopScene::itemShopNotice()
{
	if (_itemShopNotice.isEndTime == true) return;

	_itemShopNotice.rc = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraCenterY(),
		_itemShopNotice.frontImg->getWidth(), _itemShopNotice.frontImg->getHeight());

	if (TIMEMANAGER->getWorldTime() - _worldTime >= 1)
	{
		_worldTime = TIMEMANAGER->getWorldTime();
		_timeCount++;
	}

	if (_timeCount >= 3)
	{
		_timeCount = 0;
		_itemShopNotice.isEndTime = true;
	}
}
