#pragma once
#include "battleState.h"

struct tagPetControlWindow
{
	image* selectSkillImg;
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	RECT selectSkillRc;
	RECT skillRc[6];
	RECT closeRect;
	string skillName[6];
	string skillWindowText;
	string skillInfo[6];
	RECT skillselectButton;
};

class battleMap;

class petTurn : public battleState
{
private:
	tagPetControlWindow _petControlWindow;	//펫 컨트롤창

	bool _isPetSkillSelected;		//펫기술 선택했는지 확인용

public:
	virtual battleState* inputHandle(battleMap* battleMap);
	virtual void update(battleMap* battleMap);
	virtual void enter(battleMap* battleMap);
	virtual void render(battleMap* battleMap);
	virtual void exit(battleMap* battleMap);

	void setPetControlWindow(battleMap* battleMap);
	void selectPetControl(battleMap* battleMap);
	void updatePetControl(battleMap* battleMap);
	void renderPetControl(battleMap* battleMap);

	void PtInRender(battleMap* battleMap);

	void selectEnemy(battleMap* battleMap);
};

