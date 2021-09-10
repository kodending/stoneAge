#pragma once
#include "gameNode.h"
#include "tileMap.h"
#include "player.h"
#include <string>

struct tagVillageNotice
{
	image* frontImg;		//�˸�â �����
	image* backImg;			//�˸�â �ĸ��
	RECT rc;				//�˸�â ��Ʈ
	string notice;			//�˸�â ��Ʈ��
	bool isEndTime;			//�˸�â �����
};

class villageScene : public gameNode
{
private:
	tileMap* _tm;
	player* _player;

	bool _isWriteInidata;	//�̴ϵ����� �б��

	float _worldTime;					//����Ÿ�� ����
	int _timeCount;						//�ð�
	tagVillageNotice _villageNotice;	//�˸�â���¿뵵
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
