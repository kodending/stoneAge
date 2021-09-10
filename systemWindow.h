#pragma once
#include "menuType.h"

struct tagsystemWindow
{
	image* img;
	RECT rc;
	RECT stringRc;
	bool isLogOutButton;
};

struct tagLogOutWindow
{
	image* img;
	RECT rc;
	RECT decideRect;
	RECT returnRect;
};

class tileMap;

class systemWindow : public menuType
{
private:
	tagsystemWindow _sw;
	tagLogOutWindow _lw;

	bool _isWindowOff;

public:
	virtual menuType* inputHandle(tileMap * tileMap);
	virtual void update(tileMap * tileMap);
	virtual void enter(tileMap * tileMap);
	virtual void render(tileMap * tileMap);
	virtual void exit(tileMap * tileMap);
};


