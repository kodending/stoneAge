#pragma once
#include "menuType.h"

struct tagButton5
{
	image* img;
	RECT rc;
	int currentFrameX;
	int currentFrameY;
	int timeCount;
};

struct tagnoticeWindow6
{
	image* img;
	RECT rc;
	bool isClickItem;
	bool isCheckNumber;
	tagButton5 leftButton;
	tagButton5 rightButton;
	int sellNum;
	string message;
	RECT decideRect;
	RECT returnRect;
	RECT okayRect;
};

struct tagSellWindow
{
	image* frontImg;
	image* backImg;
	RECT backRect;
	RECT frontRect;
	string title;
	RECT returnRect;
	tagButton5 leftButton;
	tagButton5 rightButton;
	int currentPage;
	int maxPage;
	int playerStone;
};

class tileMap;

class sellItemWindow : public menuType
{
private:
	tagSellWindow _sellWindow;
	tagnoticeWindow6 _noticeWindow;

	int		_ableCount;
	bool	_isDisableClick;		//클릭가능하도록하기위한방법

public:
	virtual menuType* inputHandle(tileMap * tileMap);
	virtual void update(tileMap * tileMap);
	virtual void enter(tileMap * tileMap);
	virtual void render(tileMap * tileMap);
	virtual void exit(tileMap * tileMap);

	void setItem(tileMap* tileMap);
	void setSellWindow(tileMap* tileMap);

	void updateRect(tileMap* tileMap);


	void saveInidata(tileMap* tileMap);

	void textRender(tileMap* tileMap);
	void PtInRender(tileMap* tileMap);
	void imageRender(tileMap* tileMap);
	void clickPage(tileMap* tileMap);
	void updateButton(tileMap* tileMap);
	void clickItem(tileMap* tileMap);
	void noticeRender(tileMap* tileMap);
	void updateNotice(tileMap* tileMap);
	void setNotice(tileMap* tileMap);
	void clickNotice(tileMap* tileMap);
};

