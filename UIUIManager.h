#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class UIUIManager : public singletonBase<UIUIManager>
{
private:
	typedef struct tagUI
	{
		const char* UIImageName;
		int* currentFrameX;
		int* currentFrameY;
		float* x;
		float* y;
		bool isFrame;
		bool isAlpha;
		int* alpha;
		RECT* rc;
	}UI;

	typedef vector<UI>						 arrUI;
	typedef vector<UI>::iterator			 iterUI;
	typedef map<string, arrUI>				 mapUIList;
	typedef map<string, arrUI>::iterator	 mapUIIter;

private:
	int _elapsedTime;

	mapUIList _mUIList;
	arrUI _arrUI;
	iterUI _iterUI;

public:
	UIUIManager();
	~UIUIManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc, float UIX, float UIY);

	void renderByRect(string strKey, HDC hdc);

	void render(string strKey, HDC hdc, float UIX, float UIY);

	void render(string strKey, HDC hdc, float UIX, float UIY, float currentFrameX, float currentFrameY);

	void addUI(string strKey, const char* UIImageName, float *UIX, float *UIY, int *currentFrameX, int *currentFrameY, int *alpha);
	void addUI(string strKey, const char* UIImageName, float *UIX, float *UIY, int *currentFrameX, int *currentFrameY);
	void addUI(string strKey, const char* UIImageName, float *UIX, float *UIY, int *alpha);
	void addUI(string strKey, const char* UIImageName, float *UIX, float* UIY);
	void addUI(string strKey, const char* UIImageName, RECT* rc, int* currentFrameX, int* currentFrameY);


	bool deleteUI(string strKey);

	bool deleteAll();
};

