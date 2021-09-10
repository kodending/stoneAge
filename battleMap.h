#pragma once
#include "gameNode.h"
#include "pet.h"
#include "player.h"
#include "battleState.h"
#include <vector>
#include <string>

enum BATTLESELECT
{
	BATTLE_ATTACK,			// 공격하기
	BATTLE_SKILL,			// 기술쓰기
	BATTLE_CATCH,			// 포획하기
	BATTLE_HELP,			// 도움요청
	BATTLE_DEFENSE,			// 방어하기
	BATTLE_ITEM,			// 아이템창열기
	BATTLE_PET,				// 펫창열기
	BATTLE_ESCAPE,			// 도망가기
	BATTLE_NONE				// 아무것도 선택안함
};

struct tagPlayerInfo6
{
	int currentStamina;				//현재체력
	int totalStamina;				//플레이어 총내구력
	int attackPower;				//플레이어 공격력
	int defensePower;				//플레이어 방어력
	int speedPower;					//플레이어 순발력
	int charming;					//플레이어 매력
	int attributeLandCount;			//플레이어 지속성
	int attributeWaterCount;		//플레이어 수속성
	int attributeFireCount;			//플레이어 화속성
	int attributeWindCount;			//플레이어 풍속성
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
	int _battleCount;				//몇번째 배틀인지
	bool _isWriteInidata;			//데이타 읽기
	bool _isSetPlayer;				//플레이어 세팅 확인용
	int _selectTimeCount;			//선택시간 카운트
	int _enemyNum;
	bool _isStart;
	float _battleStartTime;
	int _timeCount;
	bool _isOneCycle;				//한사이클돌았는지 확인용

	int _petIsMoveCount;				//전체가 무빙을 멈췄는지 확인용

	player*			_player;				//플레이어
	vPet			_vPet;					//펫 벡터
	viPet			_viPet;					//펫 이터
	tagPlayerInfo6	_playerInfo;			//플레이어정보
	tagUnderBar3	_underBar;				//언더바 활성화
	tagNoticeWindow _noticeWindow;			//알림창
	BATTLESELECT _battleSelect;				//플레이어가 선택한것

	tagBattleTime	_battleTime[2];			//배틀 시간
	BATTLETURN _battleTurn;					//배틀 턴 적용

	float _moveSpeedX;						//움직임용
	float _moveSpeedY;						//움직임용

	float _worldTime;						//월드타임 저장용

	battleMap();
	~battleMap();

	void InputHandle();

	HRESULT init();
	void release();
	void update();
	void render(string backGroundImageName);

	//에너미 초기설정함수
	void setEnemy();
	//데이터 읽기함수
	void writeInidata();
	//처음 등장부분함수
	void appearEnemy();

	//플레이어 펫 등장
	void playerPetMove();

	//플레이어 등장
	void setPlayer();
	void playerMove();

	//배틀선택시간 띄우기
	void setSelectTime();
	void updateSelecTime();

	//배틀창 선택할때 렌더해주기
	void SelectRender();

	//선택할때 언더바쪽에 기본정보 띄어주기
	void infoRender();

	//알림창띄우기 세팅
	void setNoticeWindow();

	//해보자
	void startBattle();
	
	//플레이어 링크
	void setPlayerMemoryAddressLink(player* player) { _player = player; }
};

