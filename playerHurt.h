#pragma once
#include "playerState.h"

class player;

class playerHurt : public playerState
{
private:
	int _preCurrentFrameY;		//���� Y�� �����ϱ�

public:
	virtual playerState* inputHandle(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
	virtual void exit(player* player);
};

