#pragma once
#include "menuType.h"

enum PLAYERWEARTYPE
{
	WEAR_NONE,
	WEAR_WEAPON,
	WEAR_HELMET,
	WEAR_ARMOR,
	WEAR_RIDE_BOOK
};

struct tagPlayerWear
{
	RECT rc;					// 플레이어 착용렉트
	PLAYERWEARTYPE playerWear;	// 플레이어 착용타입
	int centerX;				// 센터x
	int centerY;				// 센터y
	bool isExistItem;			//아이템이 있다확인용
	int itemPos;				//아이템포스
};

struct tagItem2
{
	RECT rc;					//아이템칸 렉트
	int centerX;				//아이템칸 중심좌표 x
	int centerY;				//아이템칸 중심좌표 y
	bool isExistItem;			//아이템이 있다확인용
	int itemPos;
};

struct tagItemWindow2
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	RECT arrangeRect;			//가방정리 렉트
	RECT exitRect;				//닫기 렉트
	tagPlayerWear pw[3][4];		//플레이어 착용부분
	tagItem2 item[5][3];			//아이템 렉트
};

class tileMap;

class itemWindow : public menuType
{
private:
	tagItemWindow2 _itemWindow;

	bool _isLoadSetItem;		//아이템세팅 불값
	int _playerStone;			//플레이어의 소지금
	bool _isClickItem;
	int _clickDelayTime;		//딜레이타임주기
	bool _isAbleSameClick;		//제자리에 다시 둘수있도록하기위함
	bool _isTime;				//타임켜주기

public:
	virtual menuType* inputHandle(tileMap * tileMap);
	virtual void update(tileMap * tileMap);
	virtual void enter(tileMap * tileMap);
	virtual void render(tileMap * tileMap);
	virtual void exit(tileMap * tileMap);

	void updateRect(tileMap* tileMap);
	void PtInRender(tileMap * tileMap);

	void setItem(tileMap* tileMap);
	void selectItem(tileMap* tileMap);
	void switchItem(tileMap* tileMap);
	void updateSelectItem(tileMap* tileMap);

	void updateItem(tileMap* tileMap);

	void itemRender(tileMap* tileMap);

	void textRender(tileMap* tileMap);

	void deleteInidata(tileMap* tileMap, int itemPos);
	void saveInidata(tileMap* tileMap, int itemPos);

	void lineUpItem(tileMap* tileMap);
};

