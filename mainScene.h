#pragma once
#include "gameNode.h"

struct tagMainMenu
{
	image* menuImg;				//메인메뉴 이미지
	image* backImg;				//메뉴바탕화면 이미지
	RECT gameStartRect;			//게임시작 렉트
	RECT mapToolRect;			//맵툴시작 렉트
	RECT exitRect;				//나가기 렉트
	RECT mainRect;				//메인렉트
	RECT backRect;				//메인바탕화면 렉트
};

struct tagInputWindow
{
	image* frontImg;			//앞배경화면
	image* backImg;				//뒷배경화면
	RECT windowRect;			//윈도우렉트
	RECT backRect;				//뒷배경렉트
	RECT permitRect;			//수락렉트
	RECT rejectRect;			//거절렉트
	RECT textRect;				//텍스트렉트
};

class mainScene : public gameNode
{
private:

	tagMainMenu _mainMenu;
	tagInputWindow _exitWindow;

	bool _isExitOn; //나가기버튼을 눌렀을때 활성화
	bool _isWriteInidata; //데이터 읽어오는 용도
	bool _isMusic;

public:
	mainScene();
	~mainScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void exitWindow();

	void textBoxRender();
	void textRender();
	void exitRender();
	void wirteInidata();
};

