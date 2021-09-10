#pragma once
#include "menuType.h"

class tileMap;

struct tagStateWindow
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	RECT groupRect;
	RECT exitRect;
};


class stateWindow : public menuType
{
private:
	tagStateWindow _stateWindow;

public:
	virtual menuType* inputHandle(tileMap * tileMap);
	virtual void update(tileMap * tileMap);
	virtual void enter(tileMap * tileMap);
	virtual void render(tileMap * tileMap);
	virtual void exit(tileMap * tileMap);
};

