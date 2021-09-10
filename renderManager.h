#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class renderManager : public singletonBase<renderManager>
{
private:
	typedef struct tagObj
	{
		const char* objectImageName;
		int *currentFrameX;
		int *currentFrameY;
		float* centerX;
		float* centerY;
		bool* objRendered;
		float* imageCenterX;
		float* imageCenterY;
	}OBJ;

	typedef vector<OBJ>						arrObj;
	typedef vector<OBJ>::iterator			iterObj;
	typedef map<string, arrObj>				mapObjList;
	typedef map<string, arrObj>::iterator	mapObjIter;

private:
	mapObjList _mObjList; //오브젝터 맵

	arrObj _arrObj; //오브젝트 정렬용 벡터
public :
	renderManager();
	~renderManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc, const char* objectImageName, const char* petImageName);
	void render(HDC hdc, const char* objectImageName);
	void render(HDC hdc);

	void addObj(string strKey, const char* objectImageName, bool* objectRenderd, float* centerX, float* centerY, int* currentFrameX, int* currentFrameY);
	void addObj(string strKey, const char* objectImageName, float* centerX, float* centerY, int* currentFrameX, int* currentFrameY);
	void addObj(string strKey, const char* objectImageName, float* centerX, float* centerY, float* imageCenterX, float* imageCenterY, int* currentFrameX, int* currentFrameY);

	bool deleteObj(string strKey, float* centerX, float* centerY);

	void setObjArray();

	void quickSort(int left, int right);

	bool deleteAll();
};

