#pragma once
#include "singletonBase.h"
#include "image.h"


class cameraManager : public singletonBase<cameraManager>
{
private:
	image* _cameraBuffer;
	float x[2];
	float y[2];
	void cameraRange(); //카메라가 배경 밖으로 나가지 않게 만드는 함수

	bool _isHaveToMove; //카메라 고정이 풀려서 움직여야하는지

	//ㅈㄱ
	//카메라가 비추는 화면 크기(WINSIZEX, WINSIZEY)와 좌표(left, right, top, bottom)
	RECT _screen, _zoom;
	int _backWidth, _backHeight;	//backDC 크기
	int _frontWidth, _frontHeight;	//frontDC 크기
	float _count;

public:
	//ㅈㄱ=================================================
	cameraManager();
	~cameraManager();

	HRESULT init(int width, int height);
	//카메라 위치 갱신
	void updateScreen(float standardX, float standardY,
		float ratioX = 0.5f, float ratioY = 0.5f, float zoom = 1.0f);
	//카메라 진동
	void vibrateScreen(float standardX, float standardY,
		float magnitude = 5.0f);
	//카메라 출력
	void render(HDC frontDC, int destX, int destY, HDC backDC,
		float zoom = 1.0f);

	void setBackScreenSize(float width, float height) { _backWidth = width, _backHeight = height; }
	//void setFrontScreenSize(float width, float height) { _frontWidth = width, _frontHeight = height; }
	float getBackScreenWidth() { return _backWidth; }
	float getBackScreenHeight() { return _backHeight; }
	//=====================================================

	bool _isFixed; //카메라가 고정되었는지
	
	HRESULT init();
	void release();
	void update();
	void render(image* backBuffer, HDC frontDC);

	//카메라를 중점좌표로 설정
	void setCameraCenter(float x, float y)
	{
		_cameraBuffer->setCenter(x, y);
	}

	//카메라를 left, top 좌표로 설정
	void setCamera(float x, float y)
	{
		_cameraBuffer->setX(x);
		_cameraBuffer->setY(y);
	}

	//카메라 센터값으로 움직임(플레이어를 중심으로 움직이고 싶으면 사용)
	void updateCamera(float x, float y);

	/*
	//플레이어가 카메라에 중심이 아닌 다른 위치에 있고 플레이어에 따라 움직이고 싶을 때 사용)
	void updateCamera(float x, float y, float ratioX, float ratioY);
	*/

	//두 개체의 x, y좌표를 기준으로 카메라 센터 지정
	void updateCamera(float x1, float y1, float x2, float y2, float ratioX1, float ratioX);

	//플레이어가 x축 기준으로 어느정도 비율을 넘어가면 카메라가 움직임(0.5f<ratio<1.0f)
	void updateCamera(float centerX, float centerY, float ratioX);

	// RECT가 X축, y축으로 어느정도 비율을 넘어가면 카메라가 움직임( 0 < ratio < 1.0f)
	// 0을 넣으면 그 축 사용 안함
	void updateCamera(RECT& player, float ratioX, float ratioY);

	/*
	RECT가 ratio1 과 ratio2 사이에서 벗어나면 카메라를 움직임(0<ratio1<0.5f, 0.5f<ratio2<1.0f)
	ratio1은 x축->RECT.left, y축->RECT.top 기준, ratio2는 x축->RECT.right, y축 ->RECT.bottom 기준으로 왼쪽, 위, 오른쪽, 아래로 움직임
	만약 빼고싶은 것이 있다면 0을 넣으면 됨 (x축, y축 하나씩이면 float 두개만 넣는 updateCamera 추천)
	*/
	void updateCamera(RECT& player, float ratioX1, float ratioX2, float ratioY1, float ratioY2);


	void setCameraX(float x) { _cameraBuffer->setX(x); }
	void setCameraY(float y) { _cameraBuffer->setY(y); }

	void setCameraCenterX(float x) { _cameraBuffer->setX(x - (_cameraBuffer->getWidth() / 2)); }
	void setCameraCenterY(float y) { _cameraBuffer->setY(y - (_cameraBuffer->getHeight() / 2)); }

	float getCameraLEFT() { return _cameraBuffer->getX(); }
	float getCameraTOP() { return _cameraBuffer->getY(); }
	
	float getCameraRIGHT();
	float getCameraBOTTOM();

	float getCameraCenterX() { return _cameraBuffer->getCenterX(); }
	float getCameraCenterY() { return _cameraBuffer->getCenterY(); }
	
	HDC getCameraBuffer() { return _cameraBuffer->getMemDC(); }
};

