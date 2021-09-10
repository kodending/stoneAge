#pragma once
#include "menuType.h"

class tileMap;

struct tagBaseWindow
{
	image* img;
	RECT frontRect;
	RECT menuRect;
	RECT mailTradeRect;
	RECT partyRect;
	RECT dealRect;
	RECT tribeRect;
	RECT marketRect;
	RECT fightRect;
	RECT matchRect;
	RECT questRect;
	RECT actionRect;
};

class baseType : public menuType
{
private:
	tagBaseWindow _baseLeft;
	tagBaseWindow _baseRight;

public:
	virtual menuType* inputHandle(tileMap * tileMap);
	virtual void update(tileMap * tileMap);
	virtual void enter(tileMap * tileMap);
	virtual void render(tileMap * tileMap);
	virtual void exit(tileMap * tileMap);
};


