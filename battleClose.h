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
	tagCloseNotice _closeNotice;			//����˸�â
	float _worldTime;						//�ð�Ȯ�ο�
	int _elapsedSec;						//�ð����
	int _moveText;
	bool _isSave;							//�̴ϵ���Ÿ ����뵵
	bool _isSavePet[5];						//ĳġ�� �� �־����� Ȯ�ο�

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
