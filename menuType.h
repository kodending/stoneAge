#pragma once
#include "gameNode.h"

class tileMap;

class menuType : public gameNode
{
protected:

public:
	virtual menuType* inputHandle(tileMap* tileMap) = 0;
	virtual void update(tileMap* tileMap) = 0;
	virtual void enter(tileMap* tileMap) = 0;
	virtual void render(tileMap* tileMap) = 0;
	virtual void exit(tileMap* tileMap) = 0;
};


