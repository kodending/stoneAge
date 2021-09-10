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
	bool _isSelected;	//캐릭터를 셀렉했는지 확인용
	bool _isRed;
	bool _isBlue;

	tagMenu			_menu;				//메뉴창
	tagReturn		_return;			//리턴창
	tagCharacter	_red;				//레드캐릭터
	tagCharacter	_blue;				//블루캐릭터

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

