#pragma once
#include "gameNode.h"
#include <vector>

class UI : public gameNode
{
protected:
	//UI ��Ʈ(������ŭ ����)
	typedef vector<RECT>			vRect;
	typedef vector<RECT>::iterator viRect;
protected:
	vRect _vRc;
	viRect _viRc;
	image* _imageName;		//UI �̹���		

	int _currentFrameX;		//������ ��ȣ ����
	int _currentFrameY;

	float _elapsedTime;		//������ ������

public:
	UI();
	~UI();

	HRESULT init();
	HRESULT init(const char* imageName, int vectorSize);
	void release();
	void update(float frameSpeed);
	void render();

	//��Ʈ �����
	void rectMake(float left, float top, float width, float height, int vectorIndex);

	void draw(float startX, float startY);
	void frameDraw(float startX, float startY);

	vector<RECT> getVRc() { return _vRc; }
	vector<RECT>::iterator getVIRc() { return _viRc; }
};

