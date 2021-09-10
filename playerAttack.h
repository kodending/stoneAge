#pragma once
#include "playerState.h"

class player;

class playerAttack : public playerState
{
private:
	int _preCurrentFrameY;		//���� Y�� �����ϱ�
	bool _isSound;

public:
	virtual playerState* inputHandle(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
	virtual void exit(player* player);
};