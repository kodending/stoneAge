#include "stdafx.h"
#include "item.h"

item::item()
{
}

item::~item()
{
}

HRESULT item::init(ITEMNAME itemName, POINT position)
{
	_item.img = IMAGEMANAGER->findImage("item");
	_item.centerX = position.x;
	_item.centerY = position.y;
	_item.imgRc = RectMakeCenter(_item.centerX, _item.centerY,
		_item.img->getFrameWidth(), _item.img->getFrameHeight());
	_item.selectRc = RectMakeCenter(_item.centerX, _item.centerY,
		30, 30);
	_item.isUsed = false;
	_item.isWeared = false;
	_item.alphaIndex = 255;
	_item.sellPrice = "(상점가 :          스톤)";
	_item.healQuantiy = 0;
	_item.amount = 1;
	_item.itemPos = 0;
	_item.isSelect = false;
	_item.ItemName = itemName;
	setAbility(itemName);

	return S_OK;
}

void item::release()
{
}

void item::update()
{
	_item.imgRc = RectMakeCenter(_item.centerX, _item.centerY,
		_item.img->getFrameWidth(), _item.img->getFrameHeight());
	_item.selectRc = RectMakeCenter(_item.centerX, _item.centerY,
		30, 30);
}

void item::render()
{
	_item.img->alphaFrameRender(getMemDC(), _item.imgRc.left, _item.imgRc.top + _imageMoveY,
		_item.currentFrameX, _item.currentFrameY, _item.alphaIndex);

	//아이템 양이 1보다 클때만 표시한다
	if (_item.amount > 1)
	{
		//아이템 양 표시하기
		HFONT font = CreateFont(15, 0, 0, 0, 400, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("궁서체"));
		HFONT oldFont = (HFONT)SelectObject(getMemDC(), font);
		SetBkMode(getMemDC(), TRANSPARENT);

		char amount[256];
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), _item.centerX + 5, _item.centerY + 5,
			_itoa(_item.amount, amount, 10), strlen(_itoa(_item.amount, amount, 10)));

		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
		SetBkMode(getMemDC(), OPAQUE);
	}
}

void item::itemExplainInput(string inputMassage)
{
	_item.itemExplain = inputMassage;
}

void item::itemPriceInput(int price)
{
	_item.price = price;
}

void item::itemPowerInput(int attack, int defense, int speed)
{
	_item.attackPower = attack;
	_item.defensePower = defense;
	_item.speedPower = speed;
}

void item::alphaIndexInput(int alphaIndex)
{
	_item.alphaIndex = alphaIndex;
}

void item::itemAmount(int amount)
{
	_item.amount = amount;
}

void item::itemPosInput(int itemPos)
{
	_item.itemPos = itemPos;
}

void item::setAbility(ITEMNAME itemName)
{
	//포션아이템일때
	if (itemName == ITEM_POTION)
	{
		_item.isAvailableWear = false;
		_item.currentFrameX = 0;
		_item.currentFrameY = 0;
		_item.name = "포션";
		_item.itemType = TYPE_CONSUMBLE;
		_item.healQuantiy = 20;
		itemPowerInput(0, 0, 0);
		itemPriceInput(100);
		itemExplainInput("체력을 20만큼 보충해주는 아이템이다"); 
		_imageMoveY = -10;
	}

	//로또일때
	if (itemName == ITEM_LOTTO)
	{
		_item.isAvailableWear = false;
		_item.currentFrameX = 1;
		_item.currentFrameY = 0;
		_item.name = "로또복권";
		_item.itemType = TYPE_CONSUMBLE;
		itemPowerInput(0, 0, 0);
		itemPriceInput(300);
		itemExplainInput("당첨되면 1등펫 노르노르 증정");
		_imageMoveY = -10;
	}

	//고르고르탑승문서
	if (itemName == ITEM_GORGOR_RIDE_BOOK)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 2;
		_item.currentFrameY = 0;
		_item.name = "고르고르 탑승문서";
		_item.itemType = TYPE_RIDE_BOOK;
		itemPowerInput(0, 0, 0);
		itemPriceInput(1500);
		itemExplainInput("고르고르 탑승문서(레드만 탈 수 있음)");
		_imageMoveY = -10;
	}

	//베르가탑승문서
	if (itemName == ITEM_VERGA_RIDE_BOOK)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 2;
		_item.currentFrameY = 0;
		_item.name = "베르가 탑승문서";
		_item.itemType = TYPE_RIDE_BOOK;
		itemPowerInput(0, 0, 0);
		itemPriceInput(1500);
		itemExplainInput("베르가 탑승문서(블루만 탈 수 있음)");
		_imageMoveY = -10;
	}

	//바다의 창
	if (itemName == ITEM_SEA_SPEAR)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 3;
		_item.currentFrameY = 0;
		_item.name = "바다의 창";
		_item.itemType = TYPE_SPEAR;
		itemPowerInput(13, -3, 0);
		itemPriceInput(2500);
		itemExplainInput("바다의 기운을 모은 창");
		_imageMoveY = -10;
	}

	//나무 창
	if (itemName == ITEM_TREE_SPEAR)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 4;
		_item.currentFrameY = 0;
		_item.name = "나무 창";
		_item.itemType = TYPE_SPEAR;
		itemPowerInput(5, -1, 0);
		itemPriceInput(1500);
		itemExplainInput("딱총나무로 가공된 창(지팡이 아님)");
		_imageMoveY = -10;
	}

	//금 도끼
	if (itemName == ITEM_GOLD_HATCHAT)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 5;
		_item.currentFrameY = 0;
		_item.name = "금도끼";
		_item.itemType = TYPE_HATCHAT;
		itemPowerInput(15, 0, -5);
		itemPriceInput(2500);
		itemExplainInput("나무꾼이 흘리고간 금도끼");
		_imageMoveY = -10;
	}

	//마부리 도끼
	if (itemName == ITEM_MABURI_HATCHAT)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 6;
		_item.currentFrameY = 0;
		_item.name = "마부리 도끼";
		_item.itemType = TYPE_HATCHAT;
		itemPowerInput(8, 0, -2);
		itemPriceInput(1500);
		itemExplainInput("마동석이 썼던 도끼");
		_imageMoveY = -10;
	}

	//산타 몽둥이
	if (itemName == ITEM_SANTA_CLUB)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 7;
		_item.currentFrameY = 0;
		_item.name = "산타 몽둥이";
		_item.itemType = TYPE_CLUB;
		itemPowerInput(4, 0, 0);
		itemPriceInput(1000);
		itemExplainInput("12월 25일 산타가 선물해준 몽둥이");
		_imageMoveY = -10;
	}

	//냉동참다랑어 몽둥이
	if (itemName == ITEM_FISH_CLUB)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 8;
		_item.currentFrameY = 0;
		_item.name = "냉동참다랑어 몽둥이";
		_item.itemType = TYPE_CLUB;
		itemPowerInput(10, 0, 0);
		itemPriceInput(2500);
		itemExplainInput("참다랑어를 얼려만든 몽둥이");
		_imageMoveY = -10;
	}

	//바다의 갑옷
	if (itemName == ITEM_SEA_ARMOR)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 9;
		_item.currentFrameY = 0;
		_item.name = "바다의 갑옷";
		_item.itemType = TYPE_ARMOR;
		itemPowerInput(0, 8, -2);
		itemPriceInput(2500);
		itemExplainInput("소금기운으로 만든 방어구");
		_imageMoveY = -10;
	}

	//고대의 갑옷
	if (itemName == ITEM_ANCIENT_ARMOR)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 10;
		_item.currentFrameY = 0;
		_item.name = "고대의 갑옷";
		_item.itemType = TYPE_ARMOR;
		itemPowerInput(0, 3, 0);
		itemPriceInput(1500);
		itemExplainInput("상점주인의 할아버지의 \n\n 할아버지가 입던 갑옷");
		_imageMoveY = -10;
	}

	//도르도르의 갑옷
	if (itemName == ITEM_DORDOR_ARMOR)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 11;
		_item.currentFrameY = 0;
		_item.name = "도르도르의 갑옷";
		_item.itemType = TYPE_ARMOR;
		itemPowerInput(2, 3, -1);
		itemPriceInput(1500);
		itemExplainInput("도르도르 가죽으로 만든 갑옷");
		_imageMoveY = -10;
	}

	//헤스티아의 투구
	if (itemName == ITEM_HESTIA_HELMET)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 12;
		_item.currentFrameY = 0;
		_item.name = "헤스티아 투구";
		_item.itemType = TYPE_HELMET;
		itemPowerInput(0, 3, 3);
		itemPriceInput(1500);
		itemExplainInput("헤스티아인이 만든 투구");
		_imageMoveY = -10;
	}

	//마부리의 투구
	if (itemName == ITEM_MABURI_HELMET)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 13;
		_item.currentFrameY = 0;
		_item.name = "마부리 투구";
		_item.itemType = TYPE_HELMET;
		itemPowerInput(0, 1, 1);
		itemPriceInput(500);
		itemExplainInput("마동석이 쓰던 투구");
		_imageMoveY = -10;
	}

	//바다의 투구
	if (itemName == ITEM_SEA_HELMET)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 14;
		_item.currentFrameY = 0;
		_item.name = "바다의 투구";
		_item.itemType = TYPE_HELMET;
		itemPowerInput(0, 5, 5);
		itemPriceInput(2500);
		itemExplainInput("심해 15,000m에서 만든 투구");
		_imageMoveY = -10;
	}
}


