#pragma once
#include "gameNode.h"

enum ITEMTYPE
{
	TYPE_NONE,			//Ÿ�Ծ���
	TYPE_CONSUMBLE,		//�Ҹ�
	TYPE_ARMOR,			//��
	TYPE_HELMET,		//���
	TYPE_HATCHAT,		//����
	TYPE_CLUB,			//������
	TYPE_SPEAR,			//â
	TYPE_RIDE_BOOK		//ž�¹���
};

struct tagItem
{
	RECT imgRc;					//������ ��Ʈ
	RECT selectRc;				//���� ��Ʈ
	image* img;					//������ �̹���
	int currentFrameX;			//������ �����ӵ�����
	int currentFrameY;			//������ Y��������
	float centerX;				//������ ���� ��ǥ x
	float centerY;				//������ ���� ��ǥ y
	string name;				//������ �̸�
	string itemExplain;			//������ ����
	string sellPrice;			//�ǸŰ���
	ITEMNAME ItemName;			//������ ������ ����
	ITEMTYPE itemType;			//�����ۺ� ����
	bool isAvailableWear;		//���밡�ɿ���
	bool isWeared;				//�����ߴ�������
	bool isUsed;				//����ߴ�������
	int attackPower;			//������ ���ݷ�
	int defensePower;			//������ ����
	int speedPower;				//������ ���߷�
	int price;					//����
	int alphaIndex;				//�̹��� ���İ��ֱ�
	int healQuantiy;			//ü�º��淮
	int amount;					//�󸶳����� ������ �ִ���
	int itemPos;				//�������� ���°�� ��ġ���ִ���
	bool isSelect;				//�������� �����ߴ���
	int sellPage;				//�Ǹ��Ҷ� ���������� �ִ��� Ȯ��
};

class item : public gameNode
{
private:
	

public:
	tagItem _item;
	float _imageMoveY;

	item();
	~item();

	HRESULT init(ITEMNAME itemName, POINT position);
	void release();
	void update();
	void render();

	void itemExplainInput(string inputMassage);
	void itemPriceInput(int price);
	void setAbility(ITEMNAME itemName);
	void itemPowerInput(int attack, int defense, int speed);
	void alphaIndexInput(int alphaIndex);
	void itemAmount(int amount);
	void itemPosInput(int itemPos);

	tagItem getItem() { return _item; }
	void setItem(tagItem item) { _item = item; }
};

