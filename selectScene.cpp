#include "stdafx.h"
#include "selectScene.h"

selectScene::selectScene()
{
}

selectScene::~selectScene()
{
}

HRESULT selectScene::init()
{
	SOUNDMANAGER->play("scene_start", 0.4f);
	_isMusic = false;

	for (int i = 0; i < 2; ++i)
	{
		_createButton[i].img = IMAGEMANAGER->findImage("button");
		_loginButton[i].img = IMAGEMANAGER->findImage("button");
		_deleteButton[i].img = IMAGEMANAGER->findImage("button");
		_deleteButton[i].isDeleteWindow = false;
	}

	for (int i = 0; i < 10; ++i)
	{
		_playerInfo1._arrayAttributeFire[i].currentFrameX = 0;
		_playerInfo1._arrayAttributeFire[i].currentFrameY = 0;
		_playerInfo1._arrayAttributeLand[i].currentFrameX = 0;
		_playerInfo1._arrayAttributeLand[i].currentFrameY = 0;
		_playerInfo1._arrayAttributeWater[i].currentFrameX = 0;
		_playerInfo1._arrayAttributeWater[i].currentFrameY = 0;
		_playerInfo1._arrayAttributeWind[i].currentFrameX = 0;
		_playerInfo1._arrayAttributeWind[i].currentFrameY = 0;
		_playerInfo2._arrayAttributeFire[i].currentFrameX = 0;
		_playerInfo2._arrayAttributeFire[i].currentFrameY = 0;
		_playerInfo2._arrayAttributeLand[i].currentFrameX = 0;
		_playerInfo2._arrayAttributeLand[i].currentFrameY = 0;
		_playerInfo2._arrayAttributeWater[i].currentFrameX = 0;
		_playerInfo2._arrayAttributeWater[i].currentFrameY = 0;
		_playerInfo2._arrayAttributeWind[i].currentFrameX = 0;
		_playerInfo2._arrayAttributeWind[i].currentFrameY = 0;
	}

	_playerInfo1.faceCurrentFrameX = 0;
	_playerInfo1.faceCurrentFrameY = 0;
	_playerInfo2.faceCurrentFrameX = 0;
	_playerInfo2.faceCurrentFrameY = 0;

	_isWriteInidata = false;

	_deleteWindow.backImg = IMAGEMANAGER->findImage("inputWindowBack");
	_deleteWindow.frontImg = IMAGEMANAGER->findImage("inputWindow");

	CAMERAMANAGER->setCamera(0, 0);

	return S_OK;
}

void selectScene::release()
{
	SOUNDMANAGER->stop("select_bg");
}

void selectScene::update()
{
	if (_isMusic == false)
	{
		SOUNDMANAGER->play("select_bg", 0.4f);
		_isMusic = true;
	}
	writeInidata();
	nonePlayer();
	existPlayer();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SOUNDMANAGER->play("click", 0.4f);
		//첫번쨰 생성버튼을 누른경우
		if (PtInRect(&_createButton[0].rc, _ptMouse))
		{
			char temp[128];
			char temp2[128];
			INIDATA->addData("플레이어1", "선택", itoa((int)INFO_YES, temp, 10));
			INIDATA->addData("플레이어2", "선택", itoa((int)INFO_NO, temp2, 10));
			INIDATA->iniSave("캐릭터");
			SCENEMANAGER->changeScene("생성화면");
		}

		//두번째 생성버튼을 눌렀을 경우
		if (PtInRect(&_createButton[1].rc, _ptMouse))
		{
			char temp[128];
			char temp2[128];
			INIDATA->addData("플레이어1", "선택", itoa((int)INFO_NO, temp, 10));
			INIDATA->addData("플레이어2", "선택", itoa((int)INFO_YES, temp2, 10));
			INIDATA->iniSave("캐릭터");
			SCENEMANAGER->changeScene("생성화면");
		}

		for (int i = 0; i < 2; ++i)
		{
			if (PtInRect(&_deleteButton[i].rc, _ptMouse))
			{
				if (i == 0)
				{
					_deleteButton[0].isDeleteWindow = true;
					_deleteButton[1].isDeleteWindow = false;
				}
				if (i == 1)
				{
					_deleteButton[1].isDeleteWindow = true;
					_deleteButton[0].isDeleteWindow = false;
				}
			}
		}

		if (PtInRect(&_deleteWindow.rejectRect, _ptMouse))
		{
			if (_deleteButton[0].isDeleteWindow == true)
			{
				_deleteButton[0].isDeleteWindow = false;
				_deleteButton[1].isDeleteWindow = false;
			}

			if (_deleteButton[1].isDeleteWindow == true)
			{
				_deleteButton[0].isDeleteWindow = false;
				_deleteButton[1].isDeleteWindow = false;
			}
		}

		if (PtInRect(&_deleteWindow.decideRect, _ptMouse))
		{
			if (_deleteButton[0].isDeleteWindow == true)
			{
				_isPlayer[0] = false;
				char temp[256];
				INIDATA->addData("플레이어1", "있어?", _itoa((int)INFO_NO, temp, 10));
				INIDATA->deleteDataAll("플레이어1_아이템", "무기착용");
				INIDATA->deleteDataAll("플레이어1_아이템", "투구착용");
				INIDATA->deleteDataAll("플레이어1_아이템", "갑옷착용");
				INIDATA->deleteDataAll("플레이어1_아이템", "탑승문서착용");
				INIDATA->deleteDataAll("플레이어1_아이템", "아이템1");
				INIDATA->deleteDataAll("플레이어1_아이템", "아이템2");
				INIDATA->deleteDataAll("플레이어1_아이템", "아이템3");
				INIDATA->deleteDataAll("플레이어1_아이템", "아이템4");
				INIDATA->deleteDataAll("플레이어1_아이템", "아이템5");
				INIDATA->deleteDataAll("플레이어1_아이템", "아이템6");
				INIDATA->deleteDataAll("플레이어1_아이템", "아이템7");
				INIDATA->deleteDataAll("플레이어1_아이템", "아이템8");
				INIDATA->deleteDataAll("플레이어1_아이템", "아이템9");
				INIDATA->deleteDataAll("플레이어1_아이템", "아이템10");
				INIDATA->deleteDataAll("플레이어1_아이템", "아이템11");
				INIDATA->deleteDataAll("플레이어1_아이템", "아이템12");
				INIDATA->deleteDataAll("플레이어1_아이템", "아이템13");
				INIDATA->deleteDataAll("플레이어1_아이템", "아이템14");
				INIDATA->deleteDataAll("플레이어1_아이템", "아이템15");
				INIDATA->deleteDataAll("플레이어1_펫", "펫1");
				INIDATA->deleteDataAll("플레이어1_펫", "펫2");
				INIDATA->deleteDataAll("플레이어1_펫", "펫3");
				INIDATA->deleteDataAll("플레이어1_펫", "펫4");
				INIDATA->deleteDataAll("플레이어1_펫", "펫5");
				INIDATA->iniSave("캐릭터");
				_isWriteInidata = false;
				_deleteButton[0].isDeleteWindow = false;
			}

			if (_deleteButton[1].isDeleteWindow == true)
			{
				_isPlayer[1] = false;
				char temp[256];
				INIDATA->addData("플레이어2", "있어?", _itoa((int)INFO_NO, temp, 10));
				INIDATA->deleteDataAll("플레이어2_아이템", "무기착용");
				INIDATA->deleteDataAll("플레이어2_아이템", "투구착용");
				INIDATA->deleteDataAll("플레이어2_아이템", "갑옷착용");
				INIDATA->deleteDataAll("플레이어2_아이템", "탑승문서착용");
				INIDATA->deleteDataAll("플레이어2_아이템", "아이템1");
				INIDATA->deleteDataAll("플레이어2_아이템", "아이템2");
				INIDATA->deleteDataAll("플레이어2_아이템", "아이템3");
				INIDATA->deleteDataAll("플레이어2_아이템", "아이템4");
				INIDATA->deleteDataAll("플레이어2_아이템", "아이템5");
				INIDATA->deleteDataAll("플레이어2_아이템", "아이템6");
				INIDATA->deleteDataAll("플레이어2_아이템", "아이템7");
				INIDATA->deleteDataAll("플레이어2_아이템", "아이템8");
				INIDATA->deleteDataAll("플레이어2_아이템", "아이템9");
				INIDATA->deleteDataAll("플레이어2_아이템", "아이템10");
				INIDATA->deleteDataAll("플레이어2_아이템", "아이템11");
				INIDATA->deleteDataAll("플레이어2_아이템", "아이템12");
				INIDATA->deleteDataAll("플레이어2_아이템", "아이템13");
				INIDATA->deleteDataAll("플레이어2_아이템", "아이템14");
				INIDATA->deleteDataAll("플레이어2_아이템", "아이템15");
				INIDATA->deleteDataAll("플레이어2_펫", "펫1");
				INIDATA->deleteDataAll("플레이어2_펫", "펫2");
				INIDATA->deleteDataAll("플레이어2_펫", "펫3");
				INIDATA->deleteDataAll("플레이어2_펫", "펫4");
				INIDATA->deleteDataAll("플레이어2_펫", "펫5");
				INIDATA->iniSave("캐릭터");
				_isWriteInidata = false;
				_deleteButton[1].isDeleteWindow = false;
			}
		}

		if (_deleteButton[0].isDeleteWindow == false && _deleteButton[1].isDeleteWindow == false)
		{
			//플레이어1에 로그인버튼을 눌렀을경우 //로그인횟수 늘리는거 해야함
			if (PtInRect(&_loginButton[0].rc, _ptMouse))
			{
				char temp[256];
				INIDATA->addData("플레이어1", "로그인", _itoa((int)INFO_YES, temp, 10));
				char temp2[256];
				INIDATA->addData("플레이어2", "로그인", _itoa((int)INFO_NO, temp2, 10));
				_playerInfo1.loginNum += 1;
				char loginNum[256];
				INIDATA->addData("플레이어1", "로그인횟수", _itoa(_playerInfo1.loginNum, loginNum, 10));
				INIDATA->iniSave("캐릭터");
				string currentPlace = INIDATA->loadDataString("캐릭터", "플레이어1", "현재장소");
				SCENEMANAGER->changeScene(currentPlace);
			}

			//플레이어2에 로그인버튼을 눌렀을경우
			if (PtInRect(&_loginButton[1].rc, _ptMouse))
			{
				char temp[256];
				INIDATA->addData("플레이어2", "로그인", _itoa((int)INFO_YES, temp, 10));
				char temp2[256];
				INIDATA->addData("플레이어1", "로그인", _itoa((int)INFO_NO, temp2, 10));
				_playerInfo2.loginNum += 1;
				char loginNum[256];
				INIDATA->addData("플레이어2", "로그인횟수", _itoa(_playerInfo2.loginNum, loginNum, 10));
				INIDATA->iniSave("캐릭터");
				string currentPlace = INIDATA->loadDataString("캐릭터", "플레이어2", "현재장소");
				SCENEMANAGER->changeScene(currentPlace);
			}
		}
	}

	deleteWindowUpdate();
}

void selectScene::render()
{
	IMAGEMANAGER->render("characterSelect", getMemDC(), 0, 0);

	nonePlayerRender();
	existPlayerRender();
	deleteWindowRender();
	ptInRectRender();

	IMAGEMANAGER->render("mouse", getMemDC(), _ptMouse.x, _ptMouse.y);
}

void selectScene::nonePlayer()
{
	if (_isPlayer[0] == false)
	{
		_createButton[0].rc = RectMakeCenter(WINSIZEX / 2 - 200, WINSIZEY / 2 + 230, _createButton[0].img->getWidth(), _createButton[0].img->getHeight());
		_loginButton[0].rc = RectMakeCenter(WINSIZEX + 285, WINSIZEY + 230, _loginButton[0].img->getWidth(), _loginButton[0].img->getHeight());
		_deleteButton[0].rc = RectMakeCenter(WINSIZEX + 115, WINSIZEY + 230, _deleteButton[0].img->getWidth(), _deleteButton[0].img->getHeight());
	}

	if (_isPlayer[1] == false)
	{
		_createButton[1].rc = RectMakeCenter(WINSIZEX / 2 + 200, WINSIZEY / 2 + 230, _createButton[1].img->getWidth(), _createButton[1].img->getHeight());
		_loginButton[1].rc = RectMakeCenter(WINSIZEX + 285, WINSIZEY + 230, _loginButton[1].img->getWidth(), _loginButton[1].img->getHeight());
		_deleteButton[1].rc = RectMakeCenter(WINSIZEX + 115, WINSIZEY + 230, _deleteButton[1].img->getWidth(), _deleteButton[1].img->getHeight());
	}
}

void selectScene::nonePlayerRender()
{
	if (_isPlayer[0] == false)
	{
		_createButton[0].img->render(getMemDC(), _createButton[0].rc.left, _createButton[0].rc.top);
		char str[128];
		HFONT font = CreateFont(20, 0, 0, 0, 600, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY목각파임B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(80, 255, 255));

		sprintf(str, "신규");
		TextOut(getMemDC(), _createButton[0].rc.left + 25, _createButton[0].rc.top + 5, str, strlen(str));
		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}

	if (_isPlayer[1] == false)
	{
		_createButton[1].img->render(getMemDC(), _createButton[1].rc.left, _createButton[1].rc.top);
		char str2[128];
		HFONT font = CreateFont(20, 0, 0, 0, 600, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY목각파임B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(80, 255, 255));

		sprintf(str2, "신규");
		TextOut(getMemDC(), _createButton[1].rc.left + 25, _createButton[1].rc.top + 5, str2, strlen(str2));
		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}
}

void selectScene::existPlayer()
{
	if (_isPlayer[0] == true)
	{
		_createButton[0].rc = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200, _createButton[0].img->getWidth(), _createButton[0].img->getHeight());
		_loginButton[0].rc = RectMakeCenter(WINSIZEX / 2 - 285, WINSIZEY / 2 + 230, _loginButton[0].img->getWidth(), _loginButton[0].img->getHeight());
		_deleteButton[0].rc = RectMakeCenter(WINSIZEX / 2 - 115, WINSIZEY / 2 + 230, _deleteButton[0].img->getWidth(), _deleteButton[0].img->getHeight());
	}

	if (_isPlayer[1] == true)
	{
		_createButton[1].rc = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200, _createButton[1].img->getWidth(), _createButton[1].img->getHeight());
		_loginButton[1].rc = RectMakeCenter(WINSIZEX / 2 + 100, WINSIZEY / 2 + 230, _loginButton[1].img->getWidth(), _loginButton[1].img->getHeight());
		_deleteButton[1].rc = RectMakeCenter(WINSIZEX / 2 + 280, WINSIZEY / 2 + 230, _deleteButton[1].img->getWidth(), _deleteButton[1].img->getHeight());
	}
}

void selectScene::existPlayerRender()
{
	if (_isPlayer[0] == true)
	{
		_loginButton[0].img->render(getMemDC(), _loginButton[0].rc.left, _loginButton[0].rc.top);
		_deleteButton[0].img->render(getMemDC(), _deleteButton[0].rc.left, _deleteButton[0].rc.top);

		char str3[128];
		char str4[128];
		HFONT font = CreateFont(20, 0, 0, 0, 600, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY목각파임B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);

		SetTextColor(getMemDC(), RGB(80, 255, 255));
		sprintf(str3, "로그인");
		TextOut(getMemDC(), _loginButton[0].rc.left + 18, _loginButton[0].rc.top + 5, str3, strlen(str3));

		SetTextColor(getMemDC(), RGB(255, 50, 50));
		sprintf(str4, "삭제");
		TextOut(getMemDC(), _deleteButton[0].rc.left + 28, _deleteButton[0].rc.top + 5, str4, strlen(str4));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);

		HFONT font3 = CreateFont(25, 0, 0, 0, 550, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY목각파임B"));
		HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), font3);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 80));

		TextOut(getMemDC(), 120, 178, _playerInfo1.name.c_str(), strlen(_playerInfo1.name.c_str()));

		SelectObject(getMemDC(), oldFont3);
		DeleteObject(font3);
		SetBkMode(getMemDC(), OPAQUE);

		HFONT font2 = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("맑은고딕"));
		HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), font2);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 80));

		char level[256];
		TextOut(getMemDC(), 130, 220, _itoa(_playerInfo1.level, level, 10), strlen(_itoa(_playerInfo1.level, level, 10)));

		char totalStamina[256];
		TextOut(getMemDC(), 130, 257, _itoa(_playerInfo1.totalStamina, totalStamina, 10), strlen(_itoa(_playerInfo1.totalStamina, totalStamina, 10)));

		char attackPower[256];
		TextOut(getMemDC(), 130, 294, _itoa(_playerInfo1.attackPower, attackPower, 10), strlen(_itoa(_playerInfo1.attackPower, attackPower, 10)));

		char defensePower[256];
		TextOut(getMemDC(), 130, 333, _itoa(_playerInfo1.defensePower, defensePower, 10), strlen(_itoa(_playerInfo1.defensePower, defensePower, 10)));

		char speedPower[256];
		TextOut(getMemDC(), 130, 369, _itoa(_playerInfo1.speedPower, speedPower, 10), strlen(_itoa(_playerInfo1.speedPower, speedPower, 10)));

		char charming[256];
		TextOut(getMemDC(), 130, 408, _itoa(_playerInfo1.charming, charming, 10), strlen(_itoa(_playerInfo1.charming, charming, 10)));

		char loginNum[256];
		TextOut(getMemDC(), 195, 445, _itoa(_playerInfo1.loginNum, loginNum, 10), strlen(_itoa(_playerInfo1.loginNum, loginNum, 10)));

		SelectObject(getMemDC(), oldFont2);
		DeleteObject(font2);
		SetBkMode(getMemDC(), OPAQUE);

		_playerInfo1.playerFace->frameRender(getMemDC(), 168, 42, _playerInfo1.faceCurrentFrameX, _playerInfo1.faceCurrentFrameY);

		for (int i = 0; i < _playerInfo1.attributeLand; ++i)
		{
			_playerInfo1._arrayAttributeLand[i].img->frameRender(getMemDC(), _playerInfo1._arrayAttributeLand[i].rc.left - 3, _playerInfo1._arrayAttributeLand[i].rc.top - 1,
				_playerInfo1._arrayAttributeLand[i].currentFrameX, _playerInfo1._arrayAttributeLand[i].currentFrameY);
		}

		for (int i = 0; i < _playerInfo1.attributeWater; ++i)
		{
			_playerInfo1._arrayAttributeWater[i].img->frameRender(getMemDC(), _playerInfo1._arrayAttributeWater[i].rc.left - 3, _playerInfo1._arrayAttributeWater[i].rc.top - 2,
				_playerInfo1._arrayAttributeWater[i].currentFrameX, _playerInfo1._arrayAttributeWater[i].currentFrameY);
		}

		for (int i = 0; i < _playerInfo1.attributeFire; ++i)
		{
			_playerInfo1._arrayAttributeFire[i].img->frameRender(getMemDC(), _playerInfo1._arrayAttributeFire[i].rc.left - 3, _playerInfo1._arrayAttributeFire[i].rc.top - 1,
				_playerInfo1._arrayAttributeFire[i].currentFrameX, _playerInfo1._arrayAttributeFire[i].currentFrameY);
		}

		for (int i = 0; i < _playerInfo1.attributeWind; ++i)
		{
			_playerInfo1._arrayAttributeWind[i].img->frameRender(getMemDC(), _playerInfo1._arrayAttributeWind[i].rc.left - 3, _playerInfo1._arrayAttributeWind[i].rc.top,
				_playerInfo1._arrayAttributeWind[i].currentFrameX, _playerInfo1._arrayAttributeWind[i].currentFrameY);
		}
	}

	if (_isPlayer[1] == true)
	{
		_loginButton[1].img->render(getMemDC(), _loginButton[1].rc.left, _loginButton[1].rc.top);
		_deleteButton[1].img->render(getMemDC(), _deleteButton[1].rc.left, _deleteButton[1].rc.top);

		char str5[128];
		char str6[128];
		HFONT font = CreateFont(20, 0, 0, 0, 600, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY목각파임B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);

		SetTextColor(getMemDC(), RGB(80, 255, 255));
		sprintf(str5, "로그인");
		TextOut(getMemDC(), _loginButton[1].rc.left + 18, _loginButton[1].rc.top + 5, str5, strlen(str5));

		SetTextColor(getMemDC(), RGB(255, 50, 50));
		sprintf(str6, "삭제");
		TextOut(getMemDC(), _deleteButton[1].rc.left + 28, _deleteButton[1].rc.top + 5, str6, strlen(str6));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);

		HFONT font3 = CreateFont(25, 0, 0, 0, 550, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY목각파임B"));
		HFONT oldFont3 = (HFONT)SelectObject(getMemDC(), font3);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 80));

		TextOut(getMemDC(), 515, 178, _playerInfo2.name.c_str(), strlen(_playerInfo2.name.c_str()));

		SelectObject(getMemDC(), oldFont3);
		DeleteObject(font3);
		SetBkMode(getMemDC(), OPAQUE);

		HFONT font2 = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("맑은고딕"));
		HFONT oldFont2 = (HFONT)SelectObject(getMemDC(), font2);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 80));

		char level[256];
		TextOut(getMemDC(), 515, 220, _itoa(_playerInfo2.level, level, 10), strlen(_itoa(_playerInfo2.level, level, 10)));

		char totalStamina[256];
		TextOut(getMemDC(), 515, 257, _itoa(_playerInfo2.totalStamina, totalStamina, 10), strlen(_itoa(_playerInfo2.totalStamina, totalStamina, 10)));

		char attackPower[256];
		TextOut(getMemDC(), 515, 294, _itoa(_playerInfo2.attackPower, attackPower, 10), strlen(_itoa(_playerInfo2.attackPower, attackPower, 10)));

		char defensePower[256];
		TextOut(getMemDC(), 515, 333, _itoa(_playerInfo2.defensePower, defensePower, 10), strlen(_itoa(_playerInfo2.defensePower, defensePower, 10)));

		char speedPower[256];
		TextOut(getMemDC(), 515, 369, _itoa(_playerInfo2.speedPower, speedPower, 10), strlen(_itoa(_playerInfo2.speedPower, speedPower, 10)));

		char charming[256];
		TextOut(getMemDC(), 515, 408, _itoa(_playerInfo2.charming, charming, 10), strlen(_itoa(_playerInfo2.charming, charming, 10)));

		char loginNum[256];
		TextOut(getMemDC(), 578, 445, _itoa(_playerInfo2.loginNum, loginNum, 10), strlen(_itoa(_playerInfo2.loginNum, loginNum, 10)));

		SelectObject(getMemDC(), oldFont2);
		DeleteObject(font2);
		SetBkMode(getMemDC(), OPAQUE);

		_playerInfo2.playerFace->frameRender(getMemDC(), 553, 42, _playerInfo2.faceCurrentFrameX, _playerInfo2.faceCurrentFrameY);

		for (int i = 0; i < _playerInfo2.attributeLand; ++i)
		{
			_playerInfo2._arrayAttributeLand[i].img->frameRender(getMemDC(), _playerInfo2._arrayAttributeLand[i].rc.left - 3, _playerInfo2._arrayAttributeLand[i].rc.top - 1,
				_playerInfo2._arrayAttributeLand[i].currentFrameX, _playerInfo2._arrayAttributeLand[i].currentFrameY);
		}

		for (int i = 0; i < _playerInfo2.attributeWater; ++i)
		{
			_playerInfo2._arrayAttributeWater[i].img->frameRender(getMemDC(), _playerInfo2._arrayAttributeWater[i].rc.left - 3, _playerInfo2._arrayAttributeWater[i].rc.top - 2,
				_playerInfo2._arrayAttributeWater[i].currentFrameX, _playerInfo2._arrayAttributeWater[i].currentFrameY);
		}

		for (int i = 0; i < _playerInfo2.attributeFire; ++i)
		{
			_playerInfo2._arrayAttributeFire[i].img->frameRender(getMemDC(), _playerInfo2._arrayAttributeFire[i].rc.left - 3, _playerInfo2._arrayAttributeFire[i].rc.top,
				_playerInfo2._arrayAttributeFire[i].currentFrameX, _playerInfo2._arrayAttributeFire[i].currentFrameY);
		}

		for (int i = 0; i < _playerInfo2.attributeWind; ++i)
		{
			_playerInfo2._arrayAttributeWind[i].img->frameRender(getMemDC(), _playerInfo2._arrayAttributeWind[i].rc.left - 3, _playerInfo2._arrayAttributeWind[i].rc.top + 1,
				_playerInfo2._arrayAttributeWind[i].currentFrameX, _playerInfo2._arrayAttributeWind[i].currentFrameY);
		}
	}
}

void selectScene::ptInRectRender()
{
	HPEN myPen = CreatePen(PS_DASH, 3, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	for (int i = 0; i < 2; ++i)
	{
		if (PtInRect(&_loginButton[i].rc, _ptMouse))
		{
			Rectangle(getMemDC(), _loginButton[i].rc);
		}

		if (PtInRect(&_deleteButton[i].rc, _ptMouse))
		{
			Rectangle(getMemDC(), _deleteButton[i].rc);
		}

		if (PtInRect(&_createButton[i].rc, _ptMouse))
		{
			Rectangle(getMemDC(), _createButton[i].rc);
		}
	}

	if (PtInRect(&_deleteWindow.decideRect, _ptMouse))
	{
		Rectangle(getMemDC(), _deleteWindow.decideRect);
	}

	if (PtInRect(&_deleteWindow.rejectRect, _ptMouse))
	{
		Rectangle(getMemDC(), _deleteWindow.rejectRect);
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void selectScene::writeInidata()
{
	if (_isWriteInidata == true) return;

	string _select1 = INIDATA->loadDataString("캐릭터", "플레이어1", "있어?");
	string _select2 = INIDATA->loadDataString("캐릭터", "플레이어2", "있어?");

	if (atoi(_select1.c_str()) == (int)INFO_NO)
	{
		_isPlayer[0] = false;
	}

	else if (atoi(_select1.c_str()) == (int)INFO_YES)
	{
		_isPlayer[0] = true;
		_playerInfo1.name = INIDATA->loadDataString("캐릭터", "플레이어1", "이름");
		_playerInfo1.type = INIDATA->loadDataInterger("캐릭터", "플레이어1", "종류");
		_playerInfo1.level = INIDATA->loadDataInterger("캐릭터", "플레이어1", "레벨");
		_playerInfo1.totalStamina = INIDATA->loadDataInterger("캐릭터", "플레이어1", "체력") * 4 + INIDATA->loadDataInterger("캐릭터", "플레이어1", "완력") +
			INIDATA->loadDataInterger("캐릭터", "플레이어1", "건강") + INIDATA->loadDataInterger("캐릭터", "플레이어1", "스피드");
		_playerInfo1.attackPower = INIDATA->loadDataInterger("캐릭터", "플레이어1", "완력");
		_playerInfo1.defensePower = 1 + INIDATA->loadDataInterger("캐릭터", "플레이어1", "건강");
		_playerInfo1.speedPower = INIDATA->loadDataInterger("캐릭터", "플레이어1", "스피드");
		_playerInfo1.charming = INIDATA->loadDataInterger("캐릭터", "플레이어1", "매력");
		_playerInfo1.loginNum = INIDATA->loadDataInterger("캐릭터", "플레이어1", "로그인횟수");
		_playerInfo1.attributeLand = INIDATA->loadDataInterger("캐릭터", "플레이어1", "지속성");
		_playerInfo1.attributeWater = INIDATA->loadDataInterger("캐릭터", "플레이어1", "수속성");
		_playerInfo1.attributeFire = INIDATA->loadDataInterger("캐릭터", "플레이어1", "화속성");
		_playerInfo1.attributeWind = INIDATA->loadDataInterger("캐릭터", "플레이어1", "풍속성");

		if (_playerInfo1.type == (int)INFO_BLUE)
		{
			_playerInfo1.playerFace = IMAGEMANAGER->findImage("playerFace");
			_playerInfo1.faceCurrentFrameX = 1;
			_playerInfo1.faceCurrentFrameY = 0;
		}	

		if (_playerInfo1.type == (int)INFO_RED)
		{
			_playerInfo1.playerFace = IMAGEMANAGER->findImage("playerFace");
			_playerInfo1.faceCurrentFrameX = 0;
			_playerInfo1.faceCurrentFrameY = 0;
		}

		for (int i = 0; i < _playerInfo1.attributeLand; ++i)
		{
			_playerInfo1._arrayAttributeLand[i].img = IMAGEMANAGER->findImage("playerAttribute");
			_playerInfo1._arrayAttributeLand[i].currentFrameX = 2;
			_playerInfo1._arrayAttributeLand[i].currentFrameY = 0;
			_playerInfo1._arrayAttributeLand[i].rc = RectMakeCenter(265 + i * 8, 267, 8, 12);
		}

		for (int i = 0; i < _playerInfo1.attributeWater; ++i)
		{
			_playerInfo1._arrayAttributeWater[i].img = IMAGEMANAGER->findImage("playerAttribute");
			_playerInfo1._arrayAttributeWater[i].currentFrameX = 0;
			_playerInfo1._arrayAttributeWater[i].currentFrameY = 0;
			_playerInfo1._arrayAttributeWater[i].rc = RectMakeCenter(265 + i * 8, 305, 8, 12);
		}

		for (int i = 0; i < _playerInfo1.attributeFire; ++i)
		{
			_playerInfo1._arrayAttributeFire[i].img = IMAGEMANAGER->findImage("playerAttribute");
			_playerInfo1._arrayAttributeFire[i].currentFrameX = 1;
			_playerInfo1._arrayAttributeFire[i].currentFrameY = 0;
			_playerInfo1._arrayAttributeFire[i].rc = RectMakeCenter(265 + i * 8, 340, 8, 12);
		}

		for (int i = 0; i < _playerInfo1.attributeWind; ++i)
		{
			_playerInfo1._arrayAttributeWind[i].img = IMAGEMANAGER->findImage("playerAttribute");
			_playerInfo1._arrayAttributeWind[i].currentFrameX = 3;
			_playerInfo1._arrayAttributeWind[i].currentFrameY = 0;
			_playerInfo1._arrayAttributeWind[i].rc = RectMakeCenter(265 + i * 8, 376, 8, 12);
		}
	}

	if (atoi(_select2.c_str()) == (int)INFO_NO)
	{
		_isPlayer[1] = false;
	}

	else if (atoi(_select2.c_str()) == (int)INFO_YES)
	{
		_isPlayer[1] = true;
		_playerInfo2.name = INIDATA->loadDataString("캐릭터", "플레이어2", "이름");
		_playerInfo2.type = INIDATA->loadDataInterger("캐릭터", "플레이어2", "종류");
		_playerInfo2.level = INIDATA->loadDataInterger("캐릭터", "플레이어2", "레벨");
		_playerInfo2.totalStamina = INIDATA->loadDataInterger("캐릭터", "플레이어2", "체력") * 4 + INIDATA->loadDataInterger("캐릭터", "플레이어2", "완력") +
			INIDATA->loadDataInterger("캐릭터", "플레이어2", "건강") + INIDATA->loadDataInterger("캐릭터", "플레이어2", "스피드");
		_playerInfo2.attackPower = INIDATA->loadDataInterger("캐릭터", "플레이어2", "완력");
		_playerInfo2.defensePower = 1 + INIDATA->loadDataInterger("캐릭터", "플레이어2", "건강");
		_playerInfo2.speedPower = INIDATA->loadDataInterger("캐릭터", "플레이어2", "스피드");
		_playerInfo2.charming = INIDATA->loadDataInterger("캐릭터", "플레이어2", "매력");
		_playerInfo2.loginNum = INIDATA->loadDataInterger("캐릭터", "플레이어2", "로그인횟수");
		_playerInfo2.attributeLand = INIDATA->loadDataInterger("캐릭터", "플레이어2", "지속성");
		_playerInfo2.attributeWater = INIDATA->loadDataInterger("캐릭터", "플레이어2", "수속성");
		_playerInfo2.attributeFire = INIDATA->loadDataInterger("캐릭터", "플레이어2", "화속성");
		_playerInfo2.attributeWind = INIDATA->loadDataInterger("캐릭터", "플레이어2", "풍속성");

		if (_playerInfo2.type == (int)INFO_BLUE)
		{
			_playerInfo2.playerFace = IMAGEMANAGER->findImage("playerFace");
			_playerInfo2.faceCurrentFrameX = 1;
			_playerInfo2.faceCurrentFrameY = 0;
		}

		if (_playerInfo2.type == (int)INFO_RED)
		{
			_playerInfo2.playerFace = IMAGEMANAGER->findImage("playerFace");
			_playerInfo2.faceCurrentFrameX = 0;
			_playerInfo2.faceCurrentFrameY = 0;
		}

		for (int i = 0; i < _playerInfo2.attributeLand; ++i)
		{
			_playerInfo2._arrayAttributeLand[i].img = IMAGEMANAGER->findImage("playerAttribute");
			_playerInfo2._arrayAttributeLand[i].currentFrameX = 2;
			_playerInfo2._arrayAttributeLand[i].currentFrameY = 0;
			_playerInfo2._arrayAttributeLand[i].rc = RectMakeCenter(648 + i * 8, 267, 8, 12);
		}

		for (int i = 0; i < _playerInfo2.attributeWater; ++i)
		{
			_playerInfo2._arrayAttributeWater[i].img = IMAGEMANAGER->findImage("playerAttribute");
			_playerInfo2._arrayAttributeWater[i].currentFrameX = 0;
			_playerInfo2._arrayAttributeWater[i].currentFrameY = 0;
			_playerInfo2._arrayAttributeWater[i].rc = RectMakeCenter(648 + i * 8, 305, 8, 12);
		}

		for (int i = 0; i < _playerInfo2.attributeFire; ++i)
		{
			_playerInfo2._arrayAttributeFire[i].img = IMAGEMANAGER->findImage("playerAttribute");
			_playerInfo2._arrayAttributeFire[i].currentFrameX = 1;
			_playerInfo2._arrayAttributeFire[i].currentFrameY = 0;
			_playerInfo2._arrayAttributeFire[i].rc = RectMakeCenter(648 + i * 8, 340, 8, 12);
		}

		for (int i = 0; i < _playerInfo2.attributeWind; ++i)
		{
			_playerInfo2._arrayAttributeWind[i].img = IMAGEMANAGER->findImage("playerAttribute");
			_playerInfo2._arrayAttributeWind[i].currentFrameX = 3;
			_playerInfo2._arrayAttributeWind[i].currentFrameY = 0;
			_playerInfo2._arrayAttributeWind[i].rc = RectMakeCenter(648 + i * 8, 376, 8, 12);
		}
	}

	_isWriteInidata = true;
}

void selectScene::deleteWindowUpdate()
{
	if (_deleteButton[0].isDeleteWindow == true || _deleteButton[1].isDeleteWindow == true)
	{
		_deleteWindow.backRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2,
			_deleteWindow.backImg->getWidth(), _deleteWindow.backImg->getHeight());
		_deleteWindow.frontRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2,
			_deleteWindow.frontImg->getWidth(), _deleteWindow.frontImg->getHeight());
		_deleteWindow.decideRect = RectMakeCenter(WINSIZEX / 2 - 58, WINSIZEY / 2 + 17,
			97, 31);
		_deleteWindow.rejectRect = RectMakeCenter(WINSIZEX / 2 + 62, WINSIZEY / 2 + 17,
			97, 31);
		_deleteWindow.textRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 20,
			230, 20);
	}

	else if (_deleteButton[0].isDeleteWindow == false && _deleteButton[1].isDeleteWindow == false)
	{
		_deleteWindow.backRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			_deleteWindow.backImg->getWidth(), _deleteWindow.backImg->getHeight());
		_deleteWindow.frontRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			_deleteWindow.frontImg->getWidth(), _deleteWindow.frontImg->getHeight());
		_deleteWindow.decideRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			97, 31);
		_deleteWindow.rejectRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			97, 31);
		_deleteWindow.textRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			230, 20);
	}
}

void selectScene::deleteWindowRender()
{
	_deleteWindow.backImg->alphaRender(getMemDC(), _deleteWindow.backRect.left, _deleteWindow.backRect.top, 200);
	_deleteWindow.frontImg->render(getMemDC(), _deleteWindow.frontRect.left, _deleteWindow.frontRect.top);

	if (_deleteButton[0].isDeleteWindow == true || _deleteButton[1].isDeleteWindow == true)
	{
		HFONT font = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY목각파임B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);

		char str[256];
		SetTextColor(getMemDC(), RGB(80, 255, 255));
		sprintf(str, "정말 삭제하시겠습니까?");
		TextOut(getMemDC(), _deleteWindow.textRect.left, _deleteWindow.textRect.top, str, strlen(str));

		SetTextColor(getMemDC(), RGB(50, 50, 255));
		sprintf(str, "결정");
		TextOut(getMemDC(), _deleteWindow.decideRect.left + 28, _deleteWindow.decideRect.top + 5, str, strlen(str));

		SetTextColor(getMemDC(), RGB(255, 50, 50));
		sprintf(str, "취소");
		TextOut(getMemDC(), _deleteWindow.rejectRect.left + 28, _deleteWindow.rejectRect.top + 5, str, strlen(str));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}
}

void selectScene::writeInit()
{
	if (_isInit == true) return;

	_isInit = true;
}


