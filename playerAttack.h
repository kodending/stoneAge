#pragma once
#include "playerState.h"

class player;

class playerAttack : public playerState
{
private:
	int _preCurrentFrameY;		//전에 Y값 저장하기
	bool _isSound;

public:
	virtual playerState* inputHandle(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
	virtual void exit(player* player);
};