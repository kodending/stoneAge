#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "UIManager.h"

class mapToolScene : public gameNode
{
private:
	mapTool* _mt;
	UIManager* _UIM;

public:
	mapToolScene();
	~mapToolScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

