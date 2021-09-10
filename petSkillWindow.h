#pragma once
#include "menuType.h"

class tileMap;

struct tagPetSkill
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	RECT returnRect;
	RECT leftButtonRect;
	RECT rightButtonRect;
	RECT petNameChangeButtonRect;
	int petInfoCurrentPage;			//펫 인포 페이지 확인
	int petInfoMaxPage;				//펫 전체페이지 확인
	string petName;					//펫이름 활성화
	int petType;
	string petSkill1;
	string petSkill2;
	string petSkill3;
	string petSkill4;
	string petSkill5;
	string petSkill6;
};


class petSkillWindow : public menuType
{
private:
	tagPetSkill _petSkill;

public:
	virtual menuType* inputHandle(tileMap * tileMap);
	virtual void update(tileMap * tileMap);
	virtual void enter(tileMap * tileMap);
	virtual void render(tileMap * tileMap);
	virtual void exit(tileMap * tileMap);

	void writeIniData();
	void petInfoRender();
};


