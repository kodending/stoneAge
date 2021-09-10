#pragma once
#include "gameNode.h"

struct tagMenu
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	RECT decideRect;
	RECT directionRect;
	RECT cancelRect;
};

struct tagReturn
{
	image* img;
	RECT rc;
};

struct tagCharacter
{
	image* img;
	RECT rc;
	RECT ptInRc;
	int currentFrameX;
	int currentFrameY;
};

class createScene : public gameNode
{
private:
	bool _isSelected;	//ĳ���͸� �����ߴ��� Ȯ�ο�
	bool _isRed;
	bool _isBlue;

	tagMenu			_menu;				//�޴�â
	tagReturn		_return;			//����â
	tagCharacter	_red;				//����ĳ����
	tagCharacter	_blue;				//���ĳ����

	float _elapsedTime;

public:
	createScene();
	~createScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void menuRender();
	void playerRender();
	void textBoxRender();
	void subMenuRender();
};

