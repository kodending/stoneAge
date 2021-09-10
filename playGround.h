#pragma once
#include "gameNode.h"
#include "mapToolScene.h"
#include "villageScene.h"
#include "mainScene.h"
#include "selectScene.h"
#include "createScene.h"
#include "playerSetting.h"
#include "firstDungeonScene.h"
#include "firstBattleScene.h"
#include "itemShopScene.h"

class playGround : public gameNode
{
private:

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void addImage();
	void addSoundEffect();
};

