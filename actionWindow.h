#pragma once
#include "menuType.h"

class tileMap;

struct tagActionWindow
{
	image* frontImg;
	image* backImg;
	image* exitButtonImg;
	RECT frontRect;
	RECT backRect;
	RECT exitButtonRect;
	RECT actionRect[2][5];
	RECT actionRect2;
};

class actionWindow : public menuType
{
private:
	tagActionWindow _actionWindow;

public:
	virtual menuType* inputHandle(tileMap * tileMap);
	virtual void update(tileMap * tileMap);
	virtual void enter(tileMap * tileMap);
	virtual void render(tileMap * tileMap);
	virtual void exit(tileMap * tileMap);

	void ptInRectRender(tileMap * tileMap);
	void playerState(tileMap * tileMap);
};

