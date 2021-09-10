#include "stdafx.h"
#include "playerSetting.h"

playerSetting::playerSetting()
{
}

playerSetting::~playerSetting()
{
}

HRESULT playerSetting::init()
{
	SOUNDMANAGER->play("scene_start", 0.4f);
	_playerType.img = IMAGEMANAGER->findImage("playerFaceSetting");
	_inCompleteWindow.backImg = IMAGEMANAGER->findImage("inputWindowBack");
	_inCompleteWindow.frontImg = IMAGEMANAGER->findImage("inputWindow2");
	_inCompleteWindow.checkImg = IMAGEMANAGER->findImage("button");
	_decideWindow.backImg = IMAGEMANAGER->findImage("inputWindowBack");
	_decideWindow.frontImg = IMAGEMANAGER->findImage("inputWindow");
	_returnWindow.backImg = IMAGEMANAGER->findImage("inputWindowBack");
	_returnWindow.frontImg = IMAGEMANAGER->findImage("inputWindow");

	_playerType.rc = RectMakeCenter(91, 173, _playerType.img->getFrameWidth(), _playerType.img->getFrameHeight());

	_isWriteInidata = false;
	_isDecideRect = false;
	_isReturnRect = false;
	_isIncompleteWindow = false;

	_nameRect = RectMakeCenter(180, 110, 140, 20);

	dialogSetNickName();

	_baseStatusCount = 20; //초기 기본 부여스텟 20개
	_statusStamina = 0;
	_statusSpeed = 0;
	_statusHealth = 0;
	_statusStrength = 0;
	_attributeFire = 0;
	_attributeWater = 0;
	_attributeLand = 0;
	_attributeWind = 0;

	_baseAttributeCount = 10;

	//스탯렉트
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			_statusRect[j][i] = RectMakeCenter(160 + j * 37, 258 + i * 28, 33, 17);
		}
	}

	//속성렉트
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			_attributeRect[j][i] = RectMakeCenter(397 + j * 37, 259 + i * 24, 33, 18);
		}
	}

	//결정버튼
	_decideRect = RectMakeCenter(319, 410, 65, 65);

	//돌아가기버튼
	_returnRect = RectMakeCenter(420, 410, 65, 65);

	//이름 초기화
	name = "";

	return S_OK;
}

void playerSetting::release()
{
}

void playerSetting::update()
{
	if (!_isWriteInidata)
	{
		selectRed();
		selectBlue();
		_isWriteInidata = true;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SOUNDMANAGER->play("click", 0.4f);
		if (!_isDecideRect && !_isIncompleteWindow && !_isReturnRect)
		{
			statusSelect();
			attributeSelect();
		}

		decideButton();
		returnButton();
	}

	dialogInput();
	attributeRect();
	buttonActive();
}

void playerSetting::render()
{
	IMAGEMANAGER->render("playerSetting", getMemDC(), 0, 0);

	_playerType.img->frameRender(getMemDC(), _playerType.rc.left - 1, _playerType.rc.top - 2, _playerType.currentFrameX, _playerType.currentFrameY);
	dialogRender();
	attributeRender();
	buttonRender();
	ptInRectRender();
	textOutRender();

	IMAGEMANAGER->render("mouse", getMemDC(), _ptMouse.x, _ptMouse.y);
}

void playerSetting::selectRed()
{
	string selectNum1 = INIDATA->loadDataString("캐릭터", "플레이어1", "선택");
	string player1 = INIDATA->loadDataString("캐릭터", "플레이어1", "종류");

	if (atoi(selectNum1.c_str()) == (int)INFO_YES)
	{
		if (atoi(player1.c_str()) == (int)INFO_RED)
		{
			_playerType.currentFrameX = 0;
			_playerType.currentFrameY = 0;
		}

		if (atoi(player1.c_str()) == (int)INFO_BLUE)
		{
			_playerType.currentFrameX = 1;
			_playerType.currentFrameY = 0;
		}
	}
}

void playerSetting::selectBlue()
{
	string selectNum2 = INIDATA->loadDataString("캐릭터", "플레이어2", "선택");
	string player1 = INIDATA->loadDataString("캐릭터", "플레이어2", "종류");

	if (atoi(selectNum2.c_str()) == (int)INFO_YES)
	{
		if (atoi(player1.c_str()) == (int)INFO_RED)
		{
			_playerType.currentFrameX = 0;
			_playerType.currentFrameY = 0;
		}

		if (atoi(player1.c_str()) == (int)INFO_BLUE)
		{
			_playerType.currentFrameX = 1;
			_playerType.currentFrameY = 0;
		}
	}
}

void playerSetting::dialogSetNickName()
{
	_dialog = "";
}

void playerSetting::dialogInput()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "Q";
			name.append(_dialog);
		}
		else
		{
			_dialog = "q";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "W";
			name.append(_dialog);
		}
		else
		{
			_dialog = "w";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "E";
			name.append(_dialog);
		}
		else
		{
			_dialog = "e";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "R";
			name.append(_dialog);
		}
		else
		{
			_dialog = "r";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "T";
			name.append(_dialog);
		}
		else
		{
			_dialog = "t";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "Y";
			name.append(_dialog);
		}
		else
		{
			_dialog = "y";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('U'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "U";
			name.append(_dialog);
		}
		else
		{
			_dialog = "u";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "I";
			name.append(_dialog);
		}
		else
		{
			_dialog = "i";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "O";
			name.append(_dialog);
		}
		else
		{
			_dialog = "o";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "P";
			name.append(_dialog);
		}
		else
		{
			_dialog = "p";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "A";
			name.append(_dialog);
		}
		else
		{
			_dialog = "a";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "S";
			name.append(_dialog);
		}
		else
		{
			_dialog = "s";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "D";
			name.append(_dialog);
		}
		else
		{
			_dialog = "d";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "F";
			name.append(_dialog);
		}
		else
		{
			_dialog = "f";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "G";
			name.append(_dialog);
		}
		else
		{
			_dialog = "g";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "H";
			name.append(_dialog);
		}
		else
		{
			_dialog = "h";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "J";
			name.append(_dialog);
		}
		else
		{
			_dialog = "j";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "K";
			name.append(_dialog);
		}
		else
		{
			_dialog = "k";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "L";
			name.append(_dialog);
		}
		else
		{
			_dialog = "l";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "Z";
			name.append(_dialog);
		}
		else
		{
			_dialog = "z";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "X";
			name.append(_dialog);
		}
		else
		{
			_dialog = "x";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "C";
			name.append(_dialog);
		}
		else
		{
			_dialog = "c";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "V";
			name.append(_dialog);
		}
		else
		{
			_dialog = "v";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "B";
			name.append(_dialog);
		}
		else
		{
			_dialog = "b";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "N";
			name.append(_dialog);
		}
		else
		{
			_dialog = "n";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) ||
			KEYMANAGER->isToggleKey(VK_CAPITAL))
		{
			_dialog = "M";
			name.append(_dialog);
		}
		else
		{
			_dialog = "m";
			name.append(_dialog);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		if (name.size() > 0)
		{
			name.erase(name.end() - 1);
		}
	}
}

void playerSetting::dialogRender()
{
	HFONT font = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("Consolas"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 240, 21));

	TextOut(getMemDC(), _nameRect.left, _nameRect.top, name.c_str(), name.size());

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	SetBkMode(getMemDC(), OPAQUE);
}

void playerSetting::statusSelect()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (PtInRect(&_statusRect[j][i], _ptMouse))
			{
				//체력 스탯 (빼기)
				if (j == 0 && i == 0)
				{
					if (_statusStamina == 0) break;

					_statusStamina--;

					if (_statusStamina <= 0)
					{
						_statusStamina = 0;
					}

				}

				//체력 스탯 (더하기)
				if (j == 1 && i == 0)
				{
					if (_baseStatusCount <= 0) break;

					_statusStamina++;
					_baseStatusCount--;
				}

				//완력 스탯 (빼기)
				if (j == 0 && i == 1)
				{
					if (_statusStrength == 0) break;

					_statusStrength--;

					if (_statusStrength <= 0)
					{
						_statusStrength = 0;
					}
				}

				//완력 스탯 (더하기)
				if (j == 1 && i == 1)
				{
					if (_baseStatusCount <= 0) break;

					_statusStrength++;
					_baseStatusCount--;
				}

				//건강 스탯 (빼기)
				if (j == 0 && i == 2)
				{
					if (_statusHealth == 0) break;

					_statusHealth--;

					if (_statusHealth <= 0)
					{
						_statusHealth = 0;
					}
				}

				//건강 스탯 (더하기)
				if (j == 1 && i == 2)
				{
					if (_baseStatusCount <= 0) break;

					_statusHealth++;
					_baseStatusCount--;
				}

				//스피드 스탯 (빼기)
				if (j == 0 && i == 3)
				{
					if (_statusSpeed == 0) break;

					_statusSpeed--;

					if (_statusSpeed <= 0)
					{
						_statusSpeed = 0;
					}
				}

				//스피드 스탯 (더하기)
				if (j == 1 && i == 3)
				{
					if (_baseStatusCount <= 0) break;

					_statusSpeed++;
					_baseStatusCount--;
				}

				if (j == 0)
				{
					if (_statusHealth + _statusSpeed +
						_statusStamina + _statusStrength < 20 && 
						_baseStatusCount < 20)
					{
						_baseStatusCount++;
					}

					if (_baseStatusCount <= 0)
					{
						_baseStatusCount = 0;
					}
				}
			}
		}
	}
}

void playerSetting::attributeSelect()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (PtInRect(&_attributeRect[j][i], _ptMouse))
			{
				//지속성 빼기
				if (j == 0 && i == 0)
				{
					if (_attributeLand == 0) break;

					_attributeLand--;

					if (_attributeLand <= 0)
					{
						_attributeLand = 0;
					}
				}

				//지속성 더하기
				if (j == 1 && i == 0)
				{
					if (_baseAttributeCount <= 0) break;

					_attributeLand++;
					_baseAttributeCount--;
				}

				//수속성 빼기
				if (j == 0 && i == 1)
				{
					if (_attributeWater == 0) break;

					_attributeWater--;

					if (_attributeWater <= 0)
					{
						_attributeWater = 0;
					}
				}

				//수속성 더하기
				if (j == 1 && i == 1)
				{
					if (_baseAttributeCount <= 0) break;

					_attributeWater++;
					_baseAttributeCount--;
				}

				//화속성 빼기
				if (j == 0 && i == 2)
				{
					if (_attributeFire == 0) break;

					_attributeFire--;

					if (_attributeFire <= 0)
					{
						_attributeFire = 0;
					}
				}

				//화속성 더하기
				if (j == 1 && i == 2)
				{
					if (_baseAttributeCount <= 0) break;

					_attributeFire++;
					_baseAttributeCount--;
				}

				//풍속성 빼기
				if (j == 0 && i == 3)
				{
					if (_attributeWind == 0) break;

					_attributeWind--;

					if (_attributeWind <= 0)
					{
						_attributeWind = 0;
					}
				}

				//풍속성 더하기
				if (j == 1 && i == 3)
				{
					if (_baseAttributeCount <= 0) break;

					_attributeWind++;
					_baseAttributeCount--;
				}

				if (j == 0)
				{
					if (_attributeFire + _attributeLand +
						_attributeWater + _attributeWind < 10 &&
						_baseAttributeCount < 10)
					{
						_baseAttributeCount++;
					}

					if (_baseAttributeCount <= 0)
					{
						_baseAttributeCount = 0;
					}
				}
			}
		}
	}
}

void playerSetting::attributeRect()
{
	//지속성 배열에 넣기
	for (int i = 0; i < _attributeLand; ++i)
	{
		_arrayAttributeLand[i].currentFrameX = 2;
		_arrayAttributeLand[i].currentFrameY = 0;
		_arrayAttributeLand[i].img = IMAGEMANAGER->findImage("playerAttribute");
		_arrayAttributeLand[i].rc = RectMakeCenter(300 + i * 8, 258,
			_arrayAttributeLand[i].img->getFrameWidth(), _arrayAttributeLand[i].img->getFrameHeight());
	}

	//수속성 배열에 넣기
	for (int i = 0; i < _attributeWater; ++i)
	{
		_arrayAttributeWater[i].currentFrameX = 0;
		_arrayAttributeWater[i].currentFrameY = 0;
		_arrayAttributeWater[i].img = IMAGEMANAGER->findImage("playerAttribute");
		_arrayAttributeWater[i].rc = RectMakeCenter(300 + i * 8, 282,
			_arrayAttributeWater[i].img->getFrameWidth(), _arrayAttributeWater[i].img->getFrameHeight());
	}

	//화속성 배열에 넣기
	for (int i = 0; i < _attributeFire; ++i)
	{
		_arrayAttributeFire[i].currentFrameX = 1;
		_arrayAttributeFire[i].currentFrameY = 0;
		_arrayAttributeFire[i].img = IMAGEMANAGER->findImage("playerAttribute");
		_arrayAttributeFire[i].rc = RectMakeCenter(300 + i * 8, 306,
			_arrayAttributeFire[i].img->getFrameWidth(), _arrayAttributeFire[i].img->getFrameHeight());
	}

	//풍속성 배열에 넣기
	for (int i = 0; i < _attributeWind; ++i)
	{
		_arrayAttributeWind[i].currentFrameX = 3;
		_arrayAttributeWind[i].currentFrameY = 0;
		_arrayAttributeWind[i].img = IMAGEMANAGER->findImage("playerAttribute");
		_arrayAttributeWind[i].rc = RectMakeCenter(300 + i * 8, 330,
			_arrayAttributeWind[i].img->getFrameWidth(), _arrayAttributeWind[i].img->getFrameHeight());
	}
}

void playerSetting::attributeRender()
{
	//지속성 렌더
	for (int i = 0; i < _attributeLand; ++i)
	{
		_arrayAttributeLand[i].img->frameRender(getMemDC(), _arrayAttributeLand[i].rc.left, _arrayAttributeLand[i].rc.top,
			_arrayAttributeLand[i].currentFrameX, _arrayAttributeLand[i].currentFrameY);
	}

	//수속성 렌더
	for (int i = 0; i < _attributeWater; ++i)
	{
		_arrayAttributeWater[i].img->frameRender(getMemDC(), _arrayAttributeWater[i].rc.left, _arrayAttributeWater[i].rc.top,
			_arrayAttributeWater[i].currentFrameX, _arrayAttributeWater[i].currentFrameY);
	}

	//화속성 렌더
	for (int i = 0; i < _attributeFire; ++i)
	{
		_arrayAttributeFire[i].img->frameRender(getMemDC(), _arrayAttributeFire[i].rc.left, _arrayAttributeFire[i].rc.top,
			_arrayAttributeFire[i].currentFrameX, _arrayAttributeFire[i].currentFrameY);
	}

	//풍속성 렌더
	for (int i = 0; i < _attributeWind; ++i)
	{
		_arrayAttributeWind[i].img->frameRender(getMemDC(), _arrayAttributeWind[i].rc.left, _arrayAttributeWind[i].rc.top,
			_arrayAttributeWind[i].currentFrameX, _arrayAttributeWind[i].currentFrameY);
	}
}

void playerSetting::ptInRectRender()
{
	HPEN myPen = CreatePen(PS_DASH, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	if (!_isIncompleteWindow && !_isDecideRect && !_isReturnRect)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				if (PtInRect(&_statusRect[j][i], _ptMouse))
				{
					Rectangle(getMemDC(), _statusRect[j][i]);
				}

				if (PtInRect(&_attributeRect[j][i], _ptMouse))
				{
					Rectangle(getMemDC(), _attributeRect[j][i]);
				}
			}
		}

		if (PtInRect(&_decideRect, _ptMouse))
		{
			Rectangle(getMemDC(), _decideRect);
		}

		if (PtInRect(&_returnRect, _ptMouse))
		{
			Rectangle(getMemDC(), _returnRect);
		}
	}

	if (PtInRect(&_inCompleteWindow.checkRect, _ptMouse))
	{
		Rectangle(getMemDC(), _inCompleteWindow.checkRect);
	}

	if (PtInRect(&_decideWindow.decideRect, _ptMouse))
	{
		Rectangle(getMemDC(), _decideWindow.decideRect);
	}

	if (PtInRect(&_decideWindow.rejectRect, _ptMouse))
	{
		Rectangle(getMemDC(), _decideWindow.rejectRect);
	}

	if (PtInRect(&_returnWindow.decideRect, _ptMouse))
	{
		Rectangle(getMemDC(), _returnWindow.decideRect);
	}

	if (PtInRect(&_returnWindow.rejectRect, _ptMouse))
	{
		Rectangle(getMemDC(), _returnWindow.rejectRect);
	}

	DeleteObject(SelectObject(getMemDC(), oldPen));
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
}

void playerSetting::textOutRender()
{
	char temp[128];
	HFONT font = CreateFont(15, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
		0, 0, 0, 0, TEXT("맑은고딕"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);

	//스텟들 띄워주기
	SetTextColor(getMemDC(), RGB(255, 240, 21));
	sprintf(temp, itoa(_baseStatusCount, temp, 10));
	TextOut(getMemDC(), 165, 224, itoa(_baseStatusCount, temp, 10), strlen(itoa(_baseStatusCount, temp, 10)));

	sprintf(temp, itoa(_statusStamina, temp, 10));
	TextOut(getMemDC(), 115, 250, itoa(_statusStamina, temp, 10), strlen(itoa(_statusStamina, temp, 10)));

	sprintf(temp, itoa(_statusStrength, temp, 10));
	TextOut(getMemDC(), 115, 278, itoa(_statusStrength, temp, 10), strlen(itoa(_statusStrength, temp, 10)));

	sprintf(temp, itoa(_statusHealth, temp, 10));
	TextOut(getMemDC(), 115, 307, itoa(_statusHealth, temp, 10), strlen(itoa(_statusHealth, temp, 10)));

	sprintf(temp, itoa(_statusSpeed, temp, 10));
	TextOut(getMemDC(), 115, 335, itoa(_statusSpeed, temp, 10), strlen(itoa(_statusSpeed, temp, 10)));

	//속성 띄워주기
	sprintf(temp, itoa(_baseAttributeCount, temp, 10));
	TextOut(getMemDC(), 357, 224, itoa(_baseAttributeCount, temp, 10), strlen(itoa(_baseAttributeCount, temp, 10)));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	SetBkMode(getMemDC(), OPAQUE);

	if (_isIncompleteWindow)
	{
		HFONT font = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY목각파임B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);

		char str[256];
		SetTextColor(getMemDC(), RGB(80, 255, 255));
		sprintf(str, "아직 입력못한게 있어요");
		TextOut(getMemDC(), _inCompleteWindow.textRect.left + 10, _inCompleteWindow.textRect.top, str, strlen(str));

		SetTextColor(getMemDC(), RGB(0, 0, 255));
		sprintf(str, "확인");
		TextOut(getMemDC(), _inCompleteWindow.checkRect.left + 28, _inCompleteWindow.checkRect.top + 5, str, strlen(str));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}

	if (_isDecideRect)
	{
		HFONT font = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY목각파임B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);

		char str[256];
		SetTextColor(getMemDC(), RGB(80, 255, 255));
		sprintf(str, "정말 결정하시겠습니까?");
		TextOut(getMemDC(), _decideWindow.textRect.left, _decideWindow.textRect.top, str, strlen(str));

		SetTextColor(getMemDC(), RGB(50, 50, 255));
		sprintf(str, "결정");
		TextOut(getMemDC(), _decideWindow.decideRect.left + 28, _decideWindow.decideRect.top + 5, str, strlen(str));

		SetTextColor(getMemDC(), RGB(255, 50, 50));
		sprintf(str, "취소");
		TextOut(getMemDC(), _decideWindow.rejectRect.left + 28, _decideWindow.rejectRect.top + 5, str, strlen(str));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}

	if (_isReturnRect)
	{
		HFONT font = CreateFont(20, 0, 0, 0, 500, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("HY목각파임B"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);

		char str[256];
		SetTextColor(getMemDC(), RGB(80, 255, 255));
		sprintf(str, "정말 돌아가시겠습니까?");
		TextOut(getMemDC(), _returnWindow.textRect.left + 7, _returnWindow.textRect.top, str, strlen(str));

		SetTextColor(getMemDC(), RGB(50, 50, 255));
		sprintf(str, "결정");
		TextOut(getMemDC(), _returnWindow.decideRect.left + 28, _returnWindow.decideRect.top + 5, str, strlen(str));

		SetTextColor(getMemDC(), RGB(255, 50, 50));
		sprintf(str, "취소");
		TextOut(getMemDC(), _returnWindow.rejectRect.left + 28, _returnWindow.rejectRect.top + 5, str, strlen(str));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}
}

void playerSetting::decideButton()
{
	if (PtInRect(&_decideRect, _ptMouse))
	{
		if (name.size() == 0 || _baseAttributeCount != 0 || _baseStatusCount != 0)
		{
			_isIncompleteWindow = true;
		}

		else if (name.size() != 0 && _baseAttributeCount == 0 && _baseStatusCount == 0)
		{
			_isDecideRect = true;
		}
	}

	if (_isIncompleteWindow)
	{
		if (PtInRect(&_inCompleteWindow.checkRect, _ptMouse))
		{
			_isIncompleteWindow = false;
		}
	}

	if (_isDecideRect)
	{
		//생성확정버튼을 눌렀다면
		if (PtInRect(&_decideWindow.decideRect, _ptMouse))
		{
			saveInidata();
			SCENEMANAGER->changeScene("캐릭터선택");
		}

		//취소버튼을 눌렀다면
		if (PtInRect(&_decideWindow.rejectRect, _ptMouse))
		{
			_isDecideRect = false;
		}
	}
}

void playerSetting::returnButton()
{
	if (PtInRect(&_returnRect, _ptMouse))
	{
		_isReturnRect = true;
	}

	if (_isReturnRect)
	{
		//돌아가기 확정버튼을 눌렀다면
		if (PtInRect(&_returnWindow.decideRect, _ptMouse))
		{
			SCENEMANAGER->changeScene("캐릭터선택");
		}

		//돌아가기 취소버튼을 눌렀다면
		if (PtInRect(&_returnWindow.rejectRect, _ptMouse))
		{
			_isReturnRect = false;
		}
	}
}

void playerSetting::buttonActive()
{
	//아직미완성되었다고 창 띄어주는것
	if (_isIncompleteWindow)
	{
		_inCompleteWindow.backRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2,
			_inCompleteWindow.backImg->getWidth(), _inCompleteWindow.backImg->getHeight());
		_inCompleteWindow.frontRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2,
			_inCompleteWindow.frontImg->getWidth(), _inCompleteWindow.frontImg->getHeight());
		_inCompleteWindow.checkRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 25,
			_inCompleteWindow.checkImg->getWidth(), _inCompleteWindow.checkImg->getHeight());
		_inCompleteWindow.textRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 20,
			230, 20);
	}

	//미완성버튼 활성화 안되어있을때
	else
	{
		_inCompleteWindow.backRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			_inCompleteWindow.backImg->getWidth(), _inCompleteWindow.backImg->getHeight());
		_inCompleteWindow.frontRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			_inCompleteWindow.frontImg->getWidth(), _inCompleteWindow.frontImg->getHeight());
		_inCompleteWindow.checkRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			_inCompleteWindow.checkImg->getWidth(), _inCompleteWindow.checkImg->getHeight());
		_inCompleteWindow.textRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			230, 20);
	}

	//정말 결정하겠냐고 띄우기
	if (_isDecideRect)
	{
		_decideWindow.backRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2,
			_decideWindow.backImg->getWidth(), _decideWindow.backImg->getHeight());
		_decideWindow.frontRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2,
			_decideWindow.frontImg->getWidth(), _decideWindow.frontImg->getHeight());
		_decideWindow.decideRect = RectMakeCenter(WINSIZEX / 2 - 58, WINSIZEY / 2 + 17,
			97, 31);
		_decideWindow.rejectRect = RectMakeCenter(WINSIZEX / 2 + 62, WINSIZEY / 2 + 17,
			97, 31);
		_decideWindow.textRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 20,
			230, 20);
	}

	//안눌렀을경우 렉트 조정
	else
	{
		_decideWindow.backRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			_decideWindow.backImg->getWidth(), _decideWindow.backImg->getHeight());
		_decideWindow.frontRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			_decideWindow.frontImg->getWidth(), _decideWindow.frontImg->getHeight());
		_decideWindow.decideRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			97, 31);
		_decideWindow.rejectRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			97, 31);
		_decideWindow.textRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			230, 20);
	}

	if (_isReturnRect)
	{
		_returnWindow.backRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2,
			_returnWindow.backImg->getWidth(), _returnWindow.backImg->getHeight());
		_returnWindow.frontRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2,
			_returnWindow.frontImg->getWidth(), _returnWindow.frontImg->getHeight());
		_returnWindow.decideRect = RectMakeCenter(WINSIZEX / 2 - 58, WINSIZEY / 2 + 17,
			97, 31);
		_returnWindow.rejectRect = RectMakeCenter(WINSIZEX / 2 + 62, WINSIZEY / 2 + 17,
			97, 31);
		_returnWindow.textRect = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 - 20,
			230, 20);
	}

	else
	{
		_returnWindow.backRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			_returnWindow.backImg->getWidth(), _returnWindow.backImg->getHeight());
		_returnWindow.frontRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			_returnWindow.frontImg->getWidth(), _returnWindow.frontImg->getHeight());
		_returnWindow.decideRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			97, 31);
		_returnWindow.rejectRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			97, 31);
		_returnWindow.textRect = RectMakeCenter(WINSIZEX + 200, WINSIZEY + 200,
			230, 20);
	}
}

void playerSetting::buttonRender()
{
	if (_isIncompleteWindow)
	{
		_inCompleteWindow.backImg->alphaRender(getMemDC(), _inCompleteWindow.backRect.left, _inCompleteWindow.backRect.top, 200);
		_inCompleteWindow.frontImg->render(getMemDC(), _inCompleteWindow.frontRect.left, _inCompleteWindow.frontRect.top);
		_inCompleteWindow.checkImg->render(getMemDC(), _inCompleteWindow.checkRect.left, _inCompleteWindow.checkRect.top);
	}

	if (_isDecideRect)
	{
		_decideWindow.backImg->alphaRender(getMemDC(), _decideWindow.backRect.left, _decideWindow.backRect.top, 200);
		_decideWindow.frontImg->render(getMemDC(), _decideWindow.frontRect.left, _decideWindow.frontRect.top);
	}

	if (_isReturnRect)
	{
		_returnWindow.backImg->alphaRender(getMemDC(), _returnWindow.backRect.left, _returnWindow.backRect.top, 200);
		_returnWindow.frontImg->render(getMemDC(), _returnWindow.frontRect.left, _returnWindow.frontRect.top);
	}
}

void playerSetting::saveInidata()
{
	string selectNum1 = INIDATA->loadDataString("캐릭터", "플레이어1", "선택");

	//플레이어1에서 선택했을경우 플레이어 1에 저장하기
	if (atoi(selectNum1.c_str()) == (int)INFO_YES)
	{
		//플레이어생성
		char temp[256];
		INIDATA->addData("플레이어1", "있어?", _itoa((int)INFO_YES, temp, 10));

		INIDATA->addData("플레이어1", "이름", name.c_str());

		char level[256];
		INIDATA->addData("플레이어1", "레벨", _itoa(1, level, 10));

		char stamina[256];
		INIDATA->addData("플레이어1", "체력", _itoa(_statusStamina, stamina, 10));

		char strength[256];
		INIDATA->addData("플레이어1", "완력", _itoa(_statusStrength, strength, 10));

		char health[256];
		INIDATA->addData("플레이어1", "건강", _itoa(_statusHealth, health, 10));

		char speed[256];
		INIDATA->addData("플레이어1", "스피드", _itoa(_statusSpeed, speed, 10));

		char land[256];
		INIDATA->addData("플레이어1", "지속성", _itoa(_attributeLand, land, 10));

		char water[256];
		INIDATA->addData("플레이어1", "수속성", _itoa(_attributeWater, water, 10));

		char fire[256];
		INIDATA->addData("플레이어1", "화속성", _itoa(_attributeFire, fire, 10));

		char wind[256];
		INIDATA->addData("플레이어1", "풍속성", _itoa(_attributeWind, wind, 10));

		char charming[256];
		INIDATA->addData("플레이어1", "매력", _itoa(60, charming, 10));
		
		char loginNum[256];
		INIDATA->addData("플레이어1", "로그인횟수", _itoa(0, loginNum, 10));

		char currentEXP[256];
		INIDATA->addData("플레이어1", "현재경험치", _itoa(0, currentEXP, 10));

		char nextEXP[256];
		INIDATA->addData("플레이어1", "다음경험치", _itoa(2, nextEXP, 10));

		char magicalEnergy[256];
		INIDATA->addData("플레이어1", "기력", _itoa(100, magicalEnergy, 10));

		char currentStamina[256];
		INIDATA->addData("플레이어1", "현재체력", _itoa(_statusStamina * 4 + _statusStrength +
			_statusHealth + _statusSpeed, currentStamina, 10));

		INIDATA->addData("플레이어1", "현재장소", "마을");

		INIDATA->addData("플레이어1", "이전장소", "마을");
		
		char currentX[256];
		INIDATA->addData("플레이어1", "현재좌표X", _itoa(41, currentX, 10));

		char currentY[256];
		INIDATA->addData("플레이어1", "현재좌표Y", _itoa(43, currentY, 10));

		char convertPlace[256];
		INIDATA->addData("플레이어1", "장소이동", _itoa((int)INFO_NO, convertPlace, 10));

		INIDATA->iniSave("캐릭터");


		//플레이어 초기 펫 생성
		PETNAME pet = DURI;
		char petName[256];
		INIDATA->addData("펫1", "종류", _itoa((int)pet, petName, 10));

		INIDATA->addData("펫1", "이름", "두리");
		
		char petLevel[256];
		INIDATA->addData("펫1", "레벨", _itoa(1, petLevel, 10));

		char petCurrentEXP[256];
		INIDATA->addData("펫1", "현재경험치", _itoa(0, petCurrentEXP, 10));

		char petNextEXP[256];
		INIDATA->addData("펫1", "다음경험치", _itoa(2, petNextEXP, 10));

		//자 공방순을 어떻게 뽑아낼건지 변수로 정해야함.
		int petTotalStaminaNum = RND->getFromIntTo(25, 38);
		int petAttackPowerNum = RND->getFromIntTo(4, 7);
		int petDefensePowerNum = RND->getFromIntTo(2, 5);
		int petSpeedPowerNum = RND->getFromIntTo(3, 6);

		char petCurrentStamina[256];
		INIDATA->addData("펫1", "현재체력", _itoa(petTotalStaminaNum, petCurrentStamina, 10));

		char petTotalStamina[256];
		INIDATA->addData("펫1", "전체체력", _itoa(petTotalStaminaNum, petTotalStamina, 10));

		char petAttackPower[256];
		INIDATA->addData("펫1", "공격력", _itoa(petAttackPowerNum, petAttackPower, 10));

		char petDefensePower[256];
		INIDATA->addData("펫1", "방어력", _itoa(petDefensePowerNum, petDefensePower, 10));

		char petSpeedPower[256];
		INIDATA->addData("펫1", "순발력", _itoa(petSpeedPowerNum, petSpeedPower, 10));

		char loyality[256];
		INIDATA->addData("펫1", "충성도", _itoa(100, loyality, 10));

		char petAttributeLand[256];
		INIDATA->addData("펫1", "지속성", _itoa(0, petAttributeLand, 10));

		char petAttributeWater[256];
		INIDATA->addData("펫1", "수속성", _itoa(4, petAttributeWater, 10));

		char petAttributeFire[256];
		INIDATA->addData("펫1", "화속성", _itoa(6, petAttributeFire, 10));

		char petAttributeWind[256];
		INIDATA->addData("펫1", "풍속성", _itoa(0, petAttributeWind, 10));

		INIDATA->addData("펫1", "모드", "배틀");

		INIDATA->addData("펫1", "스킬1", "공격");

		INIDATA->addData("펫1", "스킬2", "방어");

		char petSkillNum1[256];
		INIDATA->addData("펫1", "기술1", _itoa((int)PET_SKILL_ATTACK, petSkillNum1, 10));

		char petSkillNum2[256];
		INIDATA->addData("펫1", "기술2", _itoa((int)PET_SKILL_DEFENSE, petSkillNum2, 10));

		INIDATA->addData("펫1", "탑승가능", "불가능");

		INIDATA->addData("펫1", "있어?", "있어");
		INIDATA->iniSave("플레이어1_펫");


		//초기 아이템과 돈 입력
		char stone[256];
		INIDATA->addData("소지금", "금액", _itoa(5000, stone, 10));

		//초기 포션지급
		char itemName[256];
		INIDATA->addData("아이템1", "종류", _itoa((int)ITEM_POTION, itemName, 10));

		char itemNum[256];
		INIDATA->addData("아이템1", "갯수", _itoa(10, itemNum, 10));

		//초기 탑승권지급(고르고르)
		char gorgor[256];
		INIDATA->addData("아이템2", "종류", _itoa((int)ITEM_GORGOR_RIDE_BOOK, gorgor, 10));

		char gorgorNum[256];
		INIDATA->addData("아이템2", "갯수", _itoa(1, gorgorNum, 10));

		//초기 탑승권지급(베르가)
		char verga[256];
		INIDATA->addData("아이템3", "종류", _itoa((int)ITEM_VERGA_RIDE_BOOK, verga, 10));

		char vergaNum[256];
		INIDATA->addData("아이템3", "갯수", _itoa(1, vergaNum, 10));

		INIDATA->iniSave("플레이어1_아이템");
	}

	string selectNum2 = INIDATA->loadDataString("캐릭터", "플레이어2", "선택");

	//플레이어1에서 선택했을경우 플레이어 2에 저장하기
	if (atoi(selectNum2.c_str()) == (int)INFO_YES)
	{
		char temp[256];
		INIDATA->addData("플레이어2", "있어?", _itoa((int)INFO_YES, temp, 10));
		
		INIDATA->addData("플레이어2", "이름", name.c_str());

		char level[256];
		INIDATA->addData("플레이어2", "레벨", _itoa(1, level, 10));

		char stamina[256];
		INIDATA->addData("플레이어2", "체력", _itoa(_statusStamina, stamina, 10));

		char strength[256];
		INIDATA->addData("플레이어2", "완력", _itoa(_statusStrength, strength, 10));

		char health[256];
		INIDATA->addData("플레이어2", "건강", _itoa(_statusHealth, health, 10));

		char speed[256];
		INIDATA->addData("플레이어2", "스피드", _itoa(_statusSpeed, speed, 10));

		char land[256];
		INIDATA->addData("플레이어2", "지속성", _itoa(_attributeLand, land, 10));

		char water[256];
		INIDATA->addData("플레이어2", "수속성", _itoa(_attributeWater, water, 10));

		char fire[256];
		INIDATA->addData("플레이어2", "화속성", _itoa(_attributeFire, fire, 10));

		char wind[256];
		INIDATA->addData("플레이어2", "풍속성", _itoa(_attributeWind, wind, 10));

		char charming[256];
		INIDATA->addData("플레이어2", "매력", _itoa(60, charming, 10));

		char loginNum[256];
		INIDATA->addData("플레이어2", "로그인횟수", _itoa(0, loginNum, 10));

		char currentEXP[256];
		INIDATA->addData("플레이어2", "현재경험치", _itoa(0, currentEXP, 10));

		char nextEXP[256];
		INIDATA->addData("플레이어2", "다음경험치", _itoa(2, nextEXP, 10));

		char magicalEnergy[256];
		INIDATA->addData("플레이어2", "기력", _itoa(100, magicalEnergy, 10));

		char currentStamina[256];
		INIDATA->addData("플레이어2", "현재체력", _itoa(_statusStamina * 4 + _statusStrength +
			_statusHealth + _statusSpeed, currentStamina, 10));

		INIDATA->addData("플레이어2", "현재장소", "마을");

		INIDATA->addData("플레이어2", "이전장소", "마을");

		char currentX[256];
		INIDATA->addData("플레이어2", "현재좌표X", _itoa(41, currentX, 10));

		char currentY[256];
		INIDATA->addData("플레이어2", "현재좌표Y", _itoa(43, currentY, 10));

		char convertPlace[256];
		INIDATA->addData("플레이어2", "장소이동", _itoa((int)INFO_NO, convertPlace, 10));

		INIDATA->iniSave("캐릭터");


		//플레이어 초기 펫 생성
		PETNAME pet = DURI;
		char petName[256];
		INIDATA->addData("펫1", "종류", _itoa((int)pet, petName, 10));

		INIDATA->addData("펫1", "이름", "두리");

		char petLevel[256];
		INIDATA->addData("펫1", "레벨", _itoa(1, petLevel, 10));

		char petCurrentEXP[256];
		INIDATA->addData("펫1", "현재경험치", _itoa(0, petCurrentEXP, 10));

		char petNextEXP[256];
		INIDATA->addData("펫1", "다음경험치", _itoa(2, petNextEXP, 10));

		//자 공방순을 어떻게 뽑아낼건지 변수로 정해야함.
		int petTotalStaminaNum = RND->getFromIntTo(25, 38);
		int petAttackPowerNum = RND->getFromIntTo(4, 7);
		int petDefensePowerNum = RND->getFromIntTo(2, 5);
		int petSpeedPowerNum = RND->getFromIntTo(3, 6);

		char petCurrentStamina[256];
		INIDATA->addData("펫1", "현재체력", _itoa(petTotalStaminaNum, petCurrentStamina, 10));

		char petTotalStamina[256];
		INIDATA->addData("펫1", "전체체력", _itoa(petTotalStaminaNum, petTotalStamina, 10));

		char petAttackPower[256];
		INIDATA->addData("펫1", "공격력", _itoa(petAttackPowerNum, petAttackPower, 10));

		char petDefensePower[256];
		INIDATA->addData("펫1", "방어력", _itoa(petDefensePowerNum, petDefensePower, 10));

		char petSpeedPower[256];
		INIDATA->addData("펫1", "순발력", _itoa(petSpeedPowerNum, petSpeedPower, 10));

		char loyality[256];
		INIDATA->addData("펫1", "충성도", _itoa(100, loyality, 10));

		char petAttributeLand[256];
		INIDATA->addData("펫1", "지속성", _itoa(0, petAttributeLand, 10));

		char petAttributeWater[256];
		INIDATA->addData("펫1", "수속성", _itoa(4, petAttributeWater, 10));

		char petAttributeFire[256];
		INIDATA->addData("펫1", "화속성", _itoa(6, petAttributeFire, 10));

		char petAttributeWind[256];
		INIDATA->addData("펫1", "풍속성", _itoa(0, petAttributeWind, 10));

		INIDATA->addData("펫1", "모드", "배틀");

		INIDATA->addData("펫1", "스킬1", "공격");

		INIDATA->addData("펫1", "스킬2", "방어");

		char petSkillNum1[256];
		INIDATA->addData("펫1", "기술1", _itoa((int)PET_SKILL_ATTACK, petSkillNum1, 10));

		char petSkillNum2[256];
		INIDATA->addData("펫1", "기술2", _itoa((int)PET_SKILL_DEFENSE, petSkillNum2, 10));

		INIDATA->addData("펫1", "탑승가능", "불가능");

		INIDATA->addData("펫1", "있어?", "있어");
		INIDATA->iniSave("플레이어2_펫");

		//초기 아이템과 돈 입력
		char stone[256];
		INIDATA->addData("소지금", "금액", _itoa(5000, stone, 10));

		//초기 포션지급
		char itemName[256];
		INIDATA->addData("아이템1", "종류", _itoa((int)ITEM_POTION, itemName, 10));

		char itemNum[256];
		INIDATA->addData("아이템1", "갯수", _itoa(10, itemNum, 10));

		//초기 탑승권지급(고르고르)
		char gorgor[256];
		INIDATA->addData("아이템2", "종류", _itoa((int)ITEM_GORGOR_RIDE_BOOK, gorgor, 10));

		char gorgorNum[256];
		INIDATA->addData("아이템2", "갯수", _itoa(1, gorgorNum, 10));

		//초기 탑승권지급(베르가)
		char verga[256];
		INIDATA->addData("아이템3", "종류", _itoa((int)ITEM_VERGA_RIDE_BOOK, verga, 10));

		char vergaNum[256];
		INIDATA->addData("아이템3", "갯수", _itoa(1, vergaNum, 10));


		INIDATA->iniSave("플레이어2_아이템");
	}
}
