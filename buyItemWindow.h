#pragma once
#include "menuType.h"

struct tagnoticeWindow5
{
	image* img;
	RECT rc;
	bool isClickItem;
	bool isShortageMoney;
	string message;
	RECT decideRect;
	RECT okayRect;
	RECT returnRect;
};

struct tagButton4
{
	image* img;
	RECT rc;
	int currentFrameX;
	int currentFrameY;
	int timeCount;
};

struct tagBuyWindow
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	string title;
	RECT returnRect;
	tagButton4 leftButton;
	tagButton4 rightButton;
	int currentPage;
	int maxPage;
	int playerStone;
};

class tileMap;

class buyItemWindow : public menuType
{
private:
	tagBuyWindow _buyWindow;
	tagnoticeWindow5 _noticeWindow;
	item* _pageTwoItem[3];
	item* _pageOneItem[3];

	int _ableCount;
	bool _isDisableClick;		//클릭가능하도록하기위한방법

public:
	virtual menuType* inputHandle(tileMap * tileMap);
	virtual void update(tileMap * tileMap);
	virtual void enter(tileMap * tileMap);
	virtual void render(tileMap * tileMap);
	virtual void exit(tileMap * tileMap);

	void writeInidata(tileMap* tileMap);
	void saveInidata(tileMap* tileMap);

	void textRender(tileMap* tileMap);
	void PtInRender(tileMap* tileMap);
	void imageRender(tileMap* tileMap);

	void setItem(tileMap* tileMap);
	void updateItem(tileMap* tileMap);
	void clickPage(tileMap* tileMap);
	void updateButton(tileMap* tileMap);
	void clickItem(tileMap* tileMap);
	void noticeRender(tileMap* tileMap);

};
