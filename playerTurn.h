#pragma once
#include "battleState.h"

struct tagBattleWindow
{
	image* frontImg;
	RECT frontRect;
	int currentSelectX;		//�����ӿ� ���� ��Ʋ ����Ʈ
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
	tagBattleWindow _battleWindow;			//��Ʋ â

	bool _isSkillWindow;			//��ųâȰ��ȭ	
	bool _isHelpWindow;				//����âȰ��ȭ	
	bool _isItemWindow;				//������â Ȱ��ȭ
	bool _isItemCloseRect;			//������Ŭ���Ʈ�� �������� Ȯ��
	tagNoticeSkill _skillNotice;	//��ų�˸�â
	tagNoticeHelp _helpNotice;		//�����˸�â
	tagItemWindow _itemWindow;		//������â
	bool _isSelected;				//�������Ϸ������� â �������� �̵���Ű��������
	bool _isSound;					//�����ġ
	bool _isSound2;					//�����ġ

public:
	virtual battleState* inputHandle(battleMap* battleMap);
	virtual void update(battleMap* battleMap);
	virtual void enter(battleMap* battleMap);
	virtual void render(battleMap* battleMap);
	virtual void exit(battleMap* battleMap);

	void setBattleWindow(battleMap* battleMap);
	void updateBattleWindow(battleMap* battleMap);

	//��Ʋâ Ŭ���� �̳ѹ� �ٲ��ֱ�
	void selectBattleWindow(battleMap* battleMap);

	//����� üũ �Ǵ� �ٸ��� Ŭ�������� �������ֱ�
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

