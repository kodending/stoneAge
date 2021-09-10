#pragma once
#include "gameNode.h"
#include "pet.h"
#include "player.h"
#include "battleState.h"
#include <vector>
#include <string>

enum BATTLESELECT
{
	BATTLE_ATTACK,			// �����ϱ�
	BATTLE_SKILL,			// �������
	BATTLE_CATCH,			// ��ȹ�ϱ�
	BATTLE_HELP,			// �����û
	BATTLE_DEFENSE,			// ����ϱ�
	BATTLE_ITEM,			// ������â����
	BATTLE_PET,				// ��â����
	BATTLE_ESCAPE,			// ��������
	BATTLE_NONE				// �ƹ��͵� ���þ���
};

struct tagPlayerInfo6
{
	int currentStamina;				//����ü��
	int totalStamina;				//�÷��̾� �ѳ�����
	int attackPower;				//�÷��̾� ���ݷ�
	int defensePower;				//�÷��̾� ����
	int speedPower;					//�÷��̾� ���߷�
	int charming;					//�÷��̾� �ŷ�
	int attributeLandCount;			//�÷��̾� ���Ӽ�
	int attributeWaterCount;		//�÷��̾� ���Ӽ�
	int attributeFireCount;			//�÷��̾� ȭ�Ӽ�
	int attributeWindCount;			//�÷��̾� ǳ�Ӽ�
};

struct tagBattleTime
{
	image* img;
	RECT rc;
	int currentFrameX;
	int currentFrameY;
};

struct tagUnderBar3
{
	image* img;
	RECT rc;
};

struct tagNoticeWindow
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	string noticeWord;
};

enum BATTLETURN
{
	TURN_PLAYER,
	TURN_PET,
	TURN_BATTLE,
	TURN_CLOSE_BATTLE,
	TURN_START_BATTLE
};

class battleMap : public gameNode
{
private:
	typedef vector<pet*>			vPet;
	typedef vector<pet*>::iterator  viPet;

private:


public:
	battleState* _battleState;
	int _battleCount;				//���° ��Ʋ����
	bool _isWriteInidata;			//����Ÿ �б�
	bool _isSetPlayer;				//�÷��̾� ���� Ȯ�ο�
	int _selectTimeCount;			//���ýð� ī��Ʈ
	int _enemyNum;
	bool _isStart;
	float _battleStartTime;
	int _timeCount;
	bool _isOneCycle;				//�ѻ���Ŭ���Ҵ��� Ȯ�ο�

	int _petIsMoveCount;				//��ü�� ������ ������� Ȯ�ο�

	player*			_player;				//�÷��̾�
	vPet			_vPet;					//�� ����
	viPet			_viPet;					//�� ����
	tagPlayerInfo6	_playerInfo;			//�÷��̾�����
	tagUnderBar3	_underBar;				//����� Ȱ��ȭ
	tagNoticeWindow _noticeWindow;			//�˸�â
	BATTLESELECT _battleSelect;				//�÷��̾ �����Ѱ�

	tagBattleTime	_battleTime[2];			//��Ʋ �ð�
	BATTLETURN _battleTurn;					//��Ʋ �� ����

	float _moveSpeedX;						//�����ӿ�
	float _moveSpeedY;						//�����ӿ�

	float _worldTime;						//����Ÿ�� �����

	battleMap();
	~battleMap();

	void InputHandle();

	HRESULT init();
	void release();
	void update();
	void render(string backGroundImageName);

	//���ʹ� �ʱ⼳���Լ�
	void setEnemy();
	//������ �б��Լ�
	void writeInidata();
	//ó�� ����κ��Լ�
	void appearEnemy();

	//�÷��̾� �� ����
	void playerPetMove();

	//�÷��̾� ����
	void setPlayer();
	void playerMove();

	//��Ʋ���ýð� ����
	void setSelectTime();
	void updateSelecTime();

	//��Ʋâ �����Ҷ� �������ֱ�
	void SelectRender();

	//�����Ҷ� ������ʿ� �⺻���� ����ֱ�
	void infoRender();

	//�˸�â���� ����
	void setNoticeWindow();

	//�غ���
	void startBattle();
	
	//�÷��̾� ��ũ
	void setPlayerMemoryAddressLink(player* player) { _player = player; }
};

