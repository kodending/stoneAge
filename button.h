#pragma once
#include "gameNode.h"

//함수포인터 형태를 가진 콜백함수 
typedef void(*CALLBACK_FUNCTION_F)(void);

//<Functional> 
//std::Function, std::move, std::bind 등등의 함수가 있는데
//콜백함수는 전역에 선언되어 있어서 매개변수를 사용할수없는데
//위에 것들을 잘 이용하면 일반적인 매개변수도 넣어서 사용할수 있음.

//함정) 의외로 쉬운데, 이게 진짜 정답인가? 물음표 띄우다 헤멜수 있음 주의
//Lambda expression
//Lambda식 과 섞어서 쓰면 속도도 빠르고 좋다! 람다식이랑 섞어서 만들어보면
//더 좋음!


enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;

	const char* _imageName;
	image* _image;
	RECT _rc;
	float _x, _y;

	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	//콜백함수 typedef 건 애를 정의한 것
	CALLBACK_FUNCTION_F _callbackFunction;

public:
	button();
	~button();

	HRESULT init(const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION_F cbFunction);
	void release();
	void update();
	void render();
};

