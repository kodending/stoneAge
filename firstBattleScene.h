#pragma once
#include "gameNode.h"
#include "battleMap.h"
#include "player.h"

class firstBattleScene : public gameNode
{
private:
	battleMap* _bm;
	player* _player;

	bool _isWriteInidata;	//�̴ϵ����� �б��

	bool _isMusic;

public:
	firstBattleScene();
    ~firstBattleScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void writeInidata();
	void firstBattleNotice();
};

