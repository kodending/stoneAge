#pragma once
#include "gameNode.h"

enum ITEMTYPE
{
	TYPE_NONE,			//타입없음
	TYPE_CONSUMBLE,		//소모성
	TYPE_ARMOR,			//방어구
	TYPE_HELMET,		//헬멧
	TYPE_HATCHAT,		//도끼
	TYPE_CLUB,			//몽둥이
	TYPE_SPEAR,			//창
	TYPE_RIDE_BOOK		//탑승문서
};

struct tagItem
{
	RECT imgRc;					//아이템 렉트
	RECT selectRc;				//선택 렉트
	image* img;					//아이템 이미지
	int currentFrameX;			//아이템 프레임돌리기
	int currentFrameY;			//아이템 Y값돌리기
	float centerX;				//아이템 센터 좌표 x
	float centerY;				//아이템 센터 좌표 y
	string name;				//아이템 이름
	string itemExplain;			//아이템 설명
	string sellPrice;			//판매가격
	ITEMNAME ItemName;			//아이템 종류별 설정
	ITEMTYPE itemType;			//아이템별 종류
	bool isAvailableWear;		//착용가능여부
	bool isWeared;				//착용했는지여부
	bool isUsed;				//사용했는지여부
	int attackPower;			//아이템 공격력
	int defensePower;			//아이템 방어력
	int speedPower;				//아이템 순발력
	int price;					//가격
	int alphaIndex;				//이미지 알파값넣기
	int healQuantiy;			//체력보충량
	int amount;					//얼마나양을 가지고 있는지
	int itemPos;				//아이템이 몇번째에 위치해있는지
	bool isSelect;				//아이템을 선택했는지
	int sellPage;				//판매할때 몇페이지에 있는지 확인
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

