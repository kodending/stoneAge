#pragma once
#include "gameNode.h"
#include "UIManager.h"

struct PLAYER
{
	image* img;
	RECT rc;
	float x, y;
};

class playScene : public gameNode
{
private:
	PLAYER _player;
	float _centerX, _centerY;
	image* _backGround;

	float _elapsedSec;

	UIManager* _UIM;

public:
	playScene();
	~playScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

