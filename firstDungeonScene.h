#pragma once
#include "gameNode.h"
#include "tileMap.h"
#include "player.h"
#include <string>

struct tagFisrtDungeonNotice
{
	image* frontImg;		//�˸�â �����
	image* backImg;			//�˸�â �ĸ��
	RECT rc;				//�˸�â ��Ʈ
	string notice;			//�˸�â ��Ʈ��
	bool isEndTime;			//�˸�â �����
};

class firstDungeonScene : public gameNode
{
private:
	tileMap* _tm;
	player* _player;

	bool _isWriteInidata;	//�̴ϵ����� �б��

	float _worldTime;					//����Ÿ�� ����
	int _timeCount;						//�ð�
	tagFisrtDungeonNotice _FDNotice;	//�˸�â���¿뵵

	bool _isMusic;

public:
	firstDungeonScene();
	~firstDungeonScene();

	virtual HRESULT init();
	void release();
	void update();
	void render();

	void writeInidata();
	void firstDungeonNotice();
};

