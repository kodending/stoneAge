#pragma once
#include "battleState.h"

struct tagCloseNotice
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	string noticeText;
};

class battleMap;

class battleClose : public battleState
{
private:
	tagCloseNotice _closeNotice;			//종료알림창
	float _worldTime;						//시계확인용
	int _elapsedSec;						//시간계산
	int _moveText;
	bool _isSave;							//이니데이타 저장용도
	bool _isSavePet[5];						//캐치한 펫 넣었는지 확인용

public:
	virtual battleState* inputHandle(battleMap* battleMap);
	virtual void update(battleMap* battleMap);
	virtual void enter(battleMap* battleMap);
	virtual void render(battleMap* battleMap);
	virtual void exit(battleMap* battleMap);

	void noticeRender();

	void convertText();

	void saveInidata(battleMap* battleMap);
};
