#pragma once
#include "gameNode.h"

class battleMap;

class battleState : public gameNode
{
protected:

public:
	virtual battleState* inputHandle(battleMap* battleMap) = 0;
	virtual void update(battleMap* battleMap) = 0;
	virtual void enter(battleMap* battleMap) = 0;
	virtual void render(battleMap* battleMap) = 0;
	virtual void exit(battleMap* battleMap) = 0;
};
