#pragma once
#include "menuType.h"

class tileMap;

struct tagPlayerAttribute4
{
	image* img;
	RECT rc;
	int currentFrameX;
	int currentFrameY;
};

struct tagPetInfo
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	RECT skiilRect;
	RECT returnRect;
	RECT leftButtonRect;
	RECT rightButtonRect;
	RECT petNameChangeButtonRect;
	int petInfoCurrentPage;			//펫 인포 페이지 확인
	int petInfoMaxPage;				//펫 전체페이지 확인
	string petName;					//펫이름 활성화
	int petLevel;
	int currentEXP;
	int nextEXP;
	int currentStamina;
	int totalStamina;
	int attackPower;
	int defensePower;
	int speedPower;
	int loyality;
	int petType;
	image* petImg;					//펫이미지 활성화
	RECT petImgRect;
	int petCurrentFrameX;
	int petCurrentFrameY;
	int attributeFireCount;
	int attributeWaterCount;
	int attributeLandCount;
	int attributeWindCount;
};


class petInfoWindow : public menuType
{
private:
	tagPetInfo _petInfo;

	tagPlayerAttribute4	_arrayAttributeFire[10];		//화속성 배열
	tagPlayerAttribute4	_arrayAttributeWater[10];		//수속성 배열
	tagPlayerAttribute4	_arrayAttributeLand[10];		//지속성 배열
	tagPlayerAttribute4	_arrayAttributeWind[10];		//풍속성 배열

	float _elapsedTime;

public:
	virtual menuType* inputHandle(tileMap * tileMap);
	virtual void update(tileMap * tileMap);
	virtual void enter(tileMap * tileMap);
	virtual void render(tileMap * tileMap);
	virtual void exit(tileMap * tileMap);

	void writeIniData();

	void petInfoRender();

	void petFrameUpdate();
};
