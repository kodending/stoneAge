#pragma once
#include "gameNode.h"
#include "tileMap.h"
#include "player.h"
#include <string>

struct tagItemShopNotice
{
	image* frontImg;		//�˸�â �����
	image* backImg;			//�˸�â �ĸ��
	RECT rc;				//�˸�â ��Ʈ
	string notice;			//�˸�â ��Ʈ��
	bool isEndTime;			//�˸�â �����
};

class itemShopScene : public gameNode
{
private:
	tileMap* _tm;
	player* _player;

	bool _isWriteInidata;				//�̴ϵ����� �б��

	float _worldTime;					//����Ÿ�� ����
	int _timeCount;						//�ð�
	tagItemShopNotice _itemShopNotice;	//�˸�â���¿뵵

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

