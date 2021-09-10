#pragma once
#include "gameNode.h"

class player;

class playerState : public gameNode
{
protected:

public:
	virtual playerState* inputHandle(player* player) = 0;
	virtual void update(player* player) = 0;
	virtual void enter(player* player) = 0;
	virtual void exit(player* player) = 0;
};

