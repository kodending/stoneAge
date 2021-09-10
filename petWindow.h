#pragma once
#include "menuType.h"

class tileMap;

struct tagPetWindow
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	RECT infoRect;
	RECT exitRect;
	RECT petNameRect[5];			//펫이름 활성화
	RECT petButtonRect[5];			//펫버튼 렉트 활성화
	image* petButtonImg[5];			//펫창에 펫이 있을때 버튼 이미지 활성화
	bool isPetNum[5];				//펫창에 펫이 있는지
	string petModeName[5];			//펫 모드 이름
	string petAvailableRide[5];		//펫 탑승가능여부 확인
};


class petWindow : public menuType
{
private:
	tagPetWindow _petWindow;

	int _petModeColorR[5];				//펫모드 RGB 설정
	int _petModeColorG[5];				//펫모드 RGB 설정
	int _petModeColorB[5];				//펫모드 RGB 설정

public:
	virtual menuType* inputHandle(tileMap * tileMap);
	virtual void update(tileMap * tileMap);
	virtual void enter(tileMap * tileMap);
	virtual void render(tileMap * tileMap);
	virtual void exit(tileMap * tileMap);

	void writeIniData();

	void petInfoRender();
};
