#pragma once
#include "gameNode.h"
#include <vector>

class UI : public gameNode
{
protected:
	//UI 렉트(갯수만큼 들어가게)
	typedef vector<RECT>			vRect;
	typedef vector<RECT>::iterator viRect;
protected:
	vRect _vRc;
	viRect _viRc;
	image* _imageName;		//UI 이미지		

	int _currentFrameX;		//프레임 번호 변수
	int _currentFrameY;

	float _elapsedTime;		//프레임 돌릴용

public:
	UI();
	~UI();

	HRESULT init();
	HRESULT init(const char* imageName, int vectorSize);
	void release();
	void update(float frameSpeed);
	void render();

	//렉트 만들기
	void rectMake(float left, float top, float width, float height, int vectorIndex);

	void draw(float startX, float startY);
	void frameDraw(float startX, float startY);

	vector<RECT> getVRc() { return _vRc; }
	vector<RECT>::iterator getVIRc() { return _viRc; }
};

