#pragma once
#include "playerState.h"

class player;

class playerHurt : public playerState
{
private:
	int _preCurrentFrameY;		//전에 Y값 저장하기

public:
	virtual playerState* inputHandle(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
	virtual void exit(player* player);
};

