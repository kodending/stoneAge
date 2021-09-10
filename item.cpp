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
	_item.sellPrice = "(������ :          ����)";
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

	//������ ���� 1���� Ŭ���� ǥ���Ѵ�
	if (_item.amount > 1)
	{
		//������ �� ǥ���ϱ�
		HFONT font = CreateFont(15, 0, 0, 0, 400, false, false, false, DEFAULT_CHARSET,
			0, 0, 0, 0, TEXT("�ü�ü"));
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
	//���Ǿ������϶�
	if (itemName == ITEM_POTION)
	{
		_item.isAvailableWear = false;
		_item.currentFrameX = 0;
		_item.currentFrameY = 0;
		_item.name = "����";
		_item.itemType = TYPE_CONSUMBLE;
		_item.healQuantiy = 20;
		itemPowerInput(0, 0, 0);
		itemPriceInput(100);
		itemExplainInput("ü���� 20��ŭ �������ִ� �������̴�"); 
		_imageMoveY = -10;
	}

	//�ζ��϶�
	if (itemName == ITEM_LOTTO)
	{
		_item.isAvailableWear = false;
		_item.currentFrameX = 1;
		_item.currentFrameY = 0;
		_item.name = "�ζǺ���";
		_item.itemType = TYPE_CONSUMBLE;
		itemPowerInput(0, 0, 0);
		itemPriceInput(300);
		itemExplainInput("��÷�Ǹ� 1���� �븣�븣 ����");
		_imageMoveY = -10;
	}

	//����ž�¹���
	if (itemName == ITEM_GORGOR_RIDE_BOOK)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 2;
		_item.currentFrameY = 0;
		_item.name = "���� ž�¹���";
		_item.itemType = TYPE_RIDE_BOOK;
		itemPowerInput(0, 0, 0);
		itemPriceInput(1500);
		itemExplainInput("���� ž�¹���(���常 Ż �� ����)");
		_imageMoveY = -10;
	}

	//������ž�¹���
	if (itemName == ITEM_VERGA_RIDE_BOOK)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 2;
		_item.currentFrameY = 0;
		_item.name = "������ ž�¹���";
		_item.itemType = TYPE_RIDE_BOOK;
		itemPowerInput(0, 0, 0);
		itemPriceInput(1500);
		itemExplainInput("������ ž�¹���(��縸 Ż �� ����)");
		_imageMoveY = -10;
	}

	//�ٴ��� â
	if (itemName == ITEM_SEA_SPEAR)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 3;
		_item.currentFrameY = 0;
		_item.name = "�ٴ��� â";
		_item.itemType = TYPE_SPEAR;
		itemPowerInput(13, -3, 0);
		itemPriceInput(2500);
		itemExplainInput("�ٴ��� ����� ���� â");
		_imageMoveY = -10;
	}

	//���� â
	if (itemName == ITEM_TREE_SPEAR)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 4;
		_item.currentFrameY = 0;
		_item.name = "���� â";
		_item.itemType = TYPE_SPEAR;
		itemPowerInput(5, -1, 0);
		itemPriceInput(1500);
		itemExplainInput("���ѳ����� ������ â(������ �ƴ�)");
		_imageMoveY = -10;
	}

	//�� ����
	if (itemName == ITEM_GOLD_HATCHAT)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 5;
		_item.currentFrameY = 0;
		_item.name = "�ݵ���";
		_item.itemType = TYPE_HATCHAT;
		itemPowerInput(15, 0, -5);
		itemPriceInput(2500);
		itemExplainInput("�������� �긮�� �ݵ���");
		_imageMoveY = -10;
	}

	//���θ� ����
	if (itemName == ITEM_MABURI_HATCHAT)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 6;
		_item.currentFrameY = 0;
		_item.name = "���θ� ����";
		_item.itemType = TYPE_HATCHAT;
		itemPowerInput(8, 0, -2);
		itemPriceInput(1500);
		itemExplainInput("�������� ��� ����");
		_imageMoveY = -10;
	}

	//��Ÿ ������
	if (itemName == ITEM_SANTA_CLUB)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 7;
		_item.currentFrameY = 0;
		_item.name = "��Ÿ ������";
		_item.itemType = TYPE_CLUB;
		itemPowerInput(4, 0, 0);
		itemPriceInput(1000);
		itemExplainInput("12�� 25�� ��Ÿ�� �������� ������");
		_imageMoveY = -10;
	}

	//�õ����ٶ��� ������
	if (itemName == ITEM_FISH_CLUB)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 8;
		_item.currentFrameY = 0;
		_item.name = "�õ����ٶ��� ������";
		_item.itemType = TYPE_CLUB;
		itemPowerInput(10, 0, 0);
		itemPriceInput(2500);
		itemExplainInput("���ٶ�� ������� ������");
		_imageMoveY = -10;
	}

	//�ٴ��� ����
	if (itemName == ITEM_SEA_ARMOR)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 9;
		_item.currentFrameY = 0;
		_item.name = "�ٴ��� ����";
		_item.itemType = TYPE_ARMOR;
		itemPowerInput(0, 8, -2);
		itemPriceInput(2500);
		itemExplainInput("�ұݱ������ ���� ��");
		_imageMoveY = -10;
	}

	//����� ����
	if (itemName == ITEM_ANCIENT_ARMOR)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 10;
		_item.currentFrameY = 0;
		_item.name = "����� ����";
		_item.itemType = TYPE_ARMOR;
		itemPowerInput(0, 3, 0);
		itemPriceInput(1500);
		itemExplainInput("���������� �Ҿƹ����� \n\n �Ҿƹ����� �Դ� ����");
		_imageMoveY = -10;
	}

	//���������� ����
	if (itemName == ITEM_DORDOR_ARMOR)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 11;
		_item.currentFrameY = 0;
		_item.name = "���������� ����";
		_item.itemType = TYPE_ARMOR;
		itemPowerInput(2, 3, -1);
		itemPriceInput(1500);
		itemExplainInput("�������� �������� ���� ����");
		_imageMoveY = -10;
	}

	//�콺Ƽ���� ����
	if (itemName == ITEM_HESTIA_HELMET)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 12;
		_item.currentFrameY = 0;
		_item.name = "�콺Ƽ�� ����";
		_item.itemType = TYPE_HELMET;
		itemPowerInput(0, 3, 3);
		itemPriceInput(1500);
		itemExplainInput("�콺Ƽ������ ���� ����");
		_imageMoveY = -10;
	}

	//���θ��� ����
	if (itemName == ITEM_MABURI_HELMET)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 13;
		_item.currentFrameY = 0;
		_item.name = "���θ� ����";
		_item.itemType = TYPE_HELMET;
		itemPowerInput(0, 1, 1);
		itemPriceInput(500);
		itemExplainInput("�������� ���� ����");
		_imageMoveY = -10;
	}

	//�ٴ��� ����
	if (itemName == ITEM_SEA_HELMET)
	{
		_item.isAvailableWear = true;
		_item.currentFrameX = 14;
		_item.currentFrameY = 0;
		_item.name = "�ٴ��� ����";
		_item.itemType = TYPE_HELMET;
		itemPowerInput(0, 5, 5);
		itemPriceInput(2500);
		itemExplainInput("���� 15,000m���� ���� ����");
		_imageMoveY = -10;
	}
}


