#pragma once
#include "gameNode.h"
#include "tileMap.h"
#include "player.h"
#include <string>

struct tagItemShopNotice
{
	image* frontImg;		//알림창 전면부
	image* backImg;			//알림창 후면부
	RECT rc;				//알림창 렉트
	string notice;			//알림창 스트링
	bool isEndTime;			//알림창 종료시
};

class itemShopScene : public gameNode
{
private:
	tileMap* _tm;
	player* _player;

	bool _isWriteInidata;				//이니데이터 읽기용

	float _worldTime;					//월드타임 계산용
	int _timeCount;						//시계
	tagItemShopNotice _itemShopNotice;	//알림창띄우는용도

public:
	itemShopScene();
	~itemShopScene();

	virtual HRESULT init();
	void release();
	void update();
	void render();

	void writeInidata();
	void itemShopNotice();
};

