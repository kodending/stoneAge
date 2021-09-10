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
	_villageNotice.notice = "태초마을";

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
			0, 0, 0, 0, TEXT("HY목각파임B"));
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

//장소 저장용
void villageScene::writeInidata()
{
	if (_isWriteInidata == true) return;

	//로그인되어있는 플레이어확인
	int loginPlayer1 = INIDATA->loadDataInterger("캐릭터", "플레이어1", "로그인");
	int loginPlayer2 = INIDATA->loadDataInterger("캐릭터", "플레이어2", "로그인");

	//플레이어1일 경우
	if (loginPlayer1 == (int)INFO_YES)
	{
		int convertPlace = INIDATA->loadDataInterger("캐릭터", "플레이어1", "장소이동");
		INIDATA->addData("플레이어1", "현재장소", "마을");
		INIDATA->iniSave("캐릭터");
		string prePlace = INIDATA->loadDataString("캐릭터", "플레이어1", "이전장소");

		//장소이동했을경우(문앞으로 위치시켜야함)
		if (convertPlace == (int)INFO_YES)
		{
			if (prePlace == "던전1")
			{
				//플레이어 위치설정(던전입구앞 좌표 찾기)
				_tm->setCamera(31, 41);
			}

			if (prePlace == "아이템상점")
			{
				//플레이어 위치설정(던전입구앞 좌표 찾기)
				_tm->setCamera(53, 28);
			}
		}

		//장소이동이 아닌 던전에서 로그아웃하고 다시 접속했을경우
		if (convertPlace == (int)INFO_NO)
		{
			int currentIsoX = INIDATA->loadDataInterger("캐릭터", "플레이어1", "현재좌표X");
			int currentIsoY = INIDATA->loadDataInterger("캐릭터", "플레이어1", "현재좌표Y");
			_tm->setCamera(currentIsoX, currentIsoY);
		}

		//장소이동이후 아니오로 바꿔주기
		convertPlace = (int)INFO_NO;
		char cp[256];
		INIDATA->addData("플레이어1", "장소이동", _itoa(convertPlace, cp, 10));
		INIDATA->iniSave("캐릭터");
	}

	//플레이어2일 경우
	if (loginPlayer2 == (int)INFO_YES)
	{
		int convertPlace = INIDATA->loadDataInterger("캐릭터", "플레이어2", "장소이동");
		INIDATA->addData("플레이어2", "현재장소", "마을");
		INIDATA->iniSave("캐릭터");
		string prePlace = INIDATA->loadDataString("캐릭터", "플레이어2", "이전장소");

		//장소이동했을경우(문앞으로 위치시켜야함)
		if (convertPlace == (int)INFO_YES)
		{
			if (prePlace == "던전1")
			{
				//플레이어 위치설정(던전입구앞 좌표 찾기)
				_tm->setCamera(31, 41);
			}

			if (prePlace == "아이템상점")
			{
				//플레이어 위치설정(던전입구앞 좌표 찾기)
				_tm->setCamera(53, 28);
			}
		}

		//장소이동이 아닌 던전에서 로그아웃하고 다시 접속했을경우
		if (convertPlace == (int)INFO_NO)
		{
			int currentIsoX = INIDATA->loadDataInterger("캐릭터", "플레이어2", "현재좌표X");
			int currentIsoY = INIDATA->loadDataInterger("캐릭터", "플레이어2", "현재좌표Y");
			_tm->setCamera(currentIsoX, currentIsoY);
		}

		//장소이동이후 아니오로 바꿔주기
		convertPlace = (int)INFO_NO;
		char cp[256];
		INIDATA->addData("플레이어2", "장소이동", _itoa(convertPlace, cp, 10));
		INIDATA->iniSave("캐릭터");
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
