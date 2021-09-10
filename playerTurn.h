#pragma once
#include "battleState.h"

struct tagBattleWindow
{
	image* frontImg;
	RECT frontRect;
	int currentSelectX;		//프레임에 맞춘 배틀 셀렉트
	int currentSelectY;
	float centerX;
	float centerY;
	RECT select[8];
};

struct tagNoticeSkill
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	string noticeWord;
};

struct tagNoticeHelp
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	string noticeWord;
};

struct tagItemWindow
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	string noticeWord;
	RECT closeRect;
	RECT itemRect[4][3];
};

class battleMap;

class playerTurn : public battleState
{
private:
	tagBattleWindow _battleWindow;			//배틀 창

	bool _isSkillWindow;			//스킬창활성화	
	bool _isHelpWindow;				//핼프창활성화	
	bool _isItemWindow;				//아이템창 활성화
	bool _isItemCloseRect;			//아이템클로즈렉트를 눌렀는지 확인
	tagNoticeSkill _skillNotice;	//스킬알림창
	tagNoticeHelp _helpNotice;		//핼프알림창
	tagItemWindow _itemWindow;		//아이템창
	bool _isSelected;				//선택을완료했으면 창 왼쪽으로 이동시키기위함임
	bool _isSound;					//사운드배치
	bool _isSound2;					//사운드배치

public:
	virtual battleState* inputHandle(battleMap* battleMap);
	virtual void update(battleMap* battleMap);
	virtual void enter(battleMap* battleMap);
	virtual void render(battleMap* battleMap);
	virtual void exit(battleMap* battleMap);

	void setBattleWindow(battleMap* battleMap);
	void updateBattleWindow(battleMap* battleMap);

	//배틀창 클릭시 이넘문 바꿔주기
	void selectBattleWindow(battleMap* battleMap);

	//상대편 체크 또는 다른걸 클릭했을때 반응해주기
	void selectBattle(battleMap* battleMap);

	void setSkillNotice(battleMap* battleMap);
	void renderSkillNotice(battleMap* battleMap);
	void setHelpNotice(battleMap* battleMap);
	void renderHelpNotice(battleMap* battleMap);
	void setItemWindow(battleMap* battleMap);
	void updateItemWindow(battleMap* battleMap);
	void renderItemWindow(battleMap* battleMap);


	void PtInRender(battleMap* battleMap);
};

