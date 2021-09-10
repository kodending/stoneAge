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
	_FDNotice.notice = "던전 1층";

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
			0, 0, 0, 0, TEXT("HY목각파임B"));
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

	//로그인되어있는 플레이어확인
	int loginPlayer1 = INIDATA->loadDataInterger("캐릭터", "플레이어1", "로그인");
	int loginPlayer2 = INIDATA->loadDataInterger("캐릭터", "플레이어2", "로그인");

	if (loginPlayer1 == (int)INFO_YES)
	{
		int convertPlace = INIDATA->loadDataInterger("캐릭터", "플레이어1", "장소이동");
		INIDATA->addData("플레이어1", "현재장소", "던전1");
		INIDATA->iniSave("캐릭터");
		string prePlace = INIDATA->loadDataString("캐릭터", "플레이어1", "이전장소");

		//장소이동했을경우(문앞으로 위치시켜야함)
		if (convertPlace == (int)INFO_YES)
		{
			if (prePlace == "마을")
			{
				//플레이어 위치설정(던전위치앞 좌표 찾기)
				_tm->setCamera(48, 60);
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
		INIDATA->addData("플레이어2", "현재장소", "던전1");
		INIDATA->iniSave("캐릭터");
		string prePlace = INIDATA->loadDataString("캐릭터", "플레이어2", "이전장소");

		//장소이동했을경우(문앞으로 위치시켜야함)
		if (convertPlace == (int)INFO_YES)
		{
			if (prePlace == "마을")
			{
				//플레이어 위치설정(던전위치앞 좌표 찾기)
				_tm->setCamera(48, 60);
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

