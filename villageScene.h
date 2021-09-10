#pragma once
#include "gameNode.h"
#include "tileMap.h"
#include "player.h"
#include <string>

struct tagVillageNotice
{
	image* frontImg;		//알림창 전면부
	image* backImg;			//알림창 후면부
	RECT rc;				//알림창 렉트
	string notice;			//알림창 스트링
	bool isEndTime;			//알림창 종료시
};

class villageScene : public gameNode
{
private:
	tileMap* _tm;
	player* _player;

	bool _isWriteInidata;	//이니데이터 읽기용

	float _worldTime;					//월드타임 계산용
	int _timeCount;						//시계
	tagVillageNotice _villageNotice;	//알림창띄우는용도
	bool _isMusic;

public:
	villageScene();
	~villageScene();

	virtual HRESULT init();
	void release();
	void update();
	void render();

	void writeInidata();
	void villageNotice();
};

