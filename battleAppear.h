#pragma once
#include "battleState.h"

class battleMap;

class battleAppear : public battleState
{
private:

public:
	virtual battleState* inputHandle(battleMap* battleMap);
	virtual void update(battleMap* battleMap);
	virtual void enter(battleMap* battleMap);
	virtual void render(battleMap* battleMap);
	virtual void exit(battleMap* battleMap);
};
