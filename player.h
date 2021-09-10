#pragma once
#include "gameNode.h"
#include "playerState.h"

enum PLAYERSTATE
{
	STATE_ANGRY,		//화남
	STATE_ATTACK,		//공격
	STATE_CRY,			//슬픔
	STATE_DEAD,			//죽음
	STATE_DEFENSE,		//방어
	STATE_HAPPY,		//기쁨
	STATE_HELLO,		//인사
	STATE_HURT,			//공격받다
	STATE_RUN,			//뛰다(걷다)
	STATE_SEAT,			//앉다
	STATE_STAND			//서있다
};

struct tagPlayer
{
	DIRECTION direction;
	PLAYERSTATE playerState;
	PLAYERWEAPON playerWeapon;
	PLAYERCHARACTER playerCharacter;
	RECT rc;
	RECT currentTileRect;				//플레이어 커런트 타일렉트
	float centerX, centerY;				//커런트 타일렉트의 중점좌표 
	int currentFrameX, currentFrameY;	//현재프레임
	image* img;							//플레이어 이미지
	float moveSpeedX;					//플레이어 무브스피드 X
	float moveSpeedY;					//플레이어 무브스피드 Y
	float playerCenterX, playerCenterY;	//플레이어 이미지 중점좌표
	RECT selectRect;					//셀렉렉트
};

class player : public gameNode
{
private:
	float _elapsedSec;			//프레임 돌릴용

	bool _isMoveClick;			//moveClick 했는지확인용
	bool _isPlayerMove;			//이동중인지 확인용

	float _moveEndX, _moveEndY;				//도착좌표 계산용

	float _imageMoveX, _imageMoveY;			//캐릭터 이미지 변동에 따른 x,y좌표 이동하기위한
	float _frameAdjustTime;					//프레임 속도 조절용
	bool _isActionRun;						//지금 런 액션중인지 확인용

	float _attackPointX, _attackPointY;		//어택좌표

public:
	playerState* _playerState;
	tagPlayer _player;
	string _playerImageName;
	bool _isAttackTime;						//공격순서를 위한 공격타임인지 결정
	bool _isAttacked;						//공격했는지를 확인하기 위한 
	bool _isAttackClose;					//공격을 마쳤는지 확인
	bool _isHurt;							//공격을 당했을때	
	bool _isDefenseOn;						//방어성공했을때 렌더해주기위함
	int _damageCount;						//데미지 먹힌 카운트값
	bool _isDamaged;						//공격먹혔을때 데미지값렌더해주기위함
	int _damageTimeCount;					//데미지 일정시간동안만 뜨게해주기
	bool _isDead;							//죽었는지 확인용
	bool _isPetCatch;						//펫을 포획중인지확인용
	bool _isEscape;							//도망치고있는지 확인용
	bool _isEscapeSuccess;					//도망성공시

	player();
	~player();

	void InputHandle();

	HRESULT init();
	void release();
	void update();
	void render();

	void frameImage();

	void setScene();

	void setPlayerRect(RECT playerRect) { _player.rc = playerRect; }
	void setPlayerTileRect(RECT playerTileRect) { _player.currentTileRect = playerTileRect; }
	void setPlayerCenterX(float playerCenterX) { _player.centerX = playerCenterX; }
	void setPlayerCenterY(float playerCenterY) { _player.centerY = playerCenterY; }
	void setPlayerMoveEndX(float moveEndX) { _moveEndX = moveEndX; }
	void setPlayerMoveEndY(float moveEndY) { _moveEndY = moveEndY; }
	void setPlayerImageMoveX(float imageMoveX) { _imageMoveX = imageMoveX; }
	void setPlayerImageMoveY(float imageMoveY) { _imageMoveY = imageMoveY; }
	void setPlayerImageCenterX(float imageCenterX) { _player.playerCenterX = imageCenterX; }
	void setPlayerImageCenterY(float imageCenterY) { _player.playerCenterY = imageCenterY; }
	void setPlayerCurrentFrameX(float currentFrameX) { _player.currentFrameX = currentFrameX; }
	void setPlayerCurrentFrameY(float currentFrameY) { _player.currentFrameY = currentFrameY; }
	void setPlayerDirection(DIRECTION direction) { _player.direction = direction; }
	void setPlayerImage(string playerImage) { _playerImageName = playerImage; }
	void setPlayerFrameAdjustTime(float frameAdjustTime) { _frameAdjustTime = frameAdjustTime; }
	void setPlayerState(PLAYERSTATE playerState) { _player.playerState = playerState; }
	void setPlayerActionRun(bool actionRun) { _isActionRun = actionRun; }

	float getPlayerSpeedX() { return _player.moveSpeedX; }
	float getPlayerSpeedY() { return _player.moveSpeedY; }
	float getPlayerMoveEndX() { return _moveEndX; }
	float getPlayerMoveEndY() { return _moveEndY; }
	RECT getPlayerRect() { return _player.rc; }
	RECT getPlayerTileRect() { return _player.currentTileRect; }
	float getPlayerCenterX() { return _player.centerX; }
	float getPlayerCenterY() { return _player.centerY; }
	image* getPlayerImage() { return _player.img; }
	string getPlayerImageName() { return _playerImageName; }
	float getPlayerImageMoveX() { return _imageMoveX; }
	float getPlayerImageMoveY() { return _imageMoveY; }
	float getPlayerImageCenterX() { return _player.playerCenterX; }
	float getPlayerImageCenterY() { return _player.playerCenterY; }
	int getPlayerCurrentFrameX() { return _player.currentFrameX; }
	int getPlayerCurrentFrameY() { return _player.currentFrameY; }
	DIRECTION getPlayerDirection() { return _player.direction; }
	float getPlayerFrameAdjustTime() { return _frameAdjustTime; }
	PLAYERSTATE getPlayerState() { return _player.playerState; }
	bool getPlayerActionRun() { return _isActionRun; }

	//무브를 눌렀는지 확인용
	bool getIsMoveClick() { return _isMoveClick; }
	void setIsMoveClick(bool isMoveClick) { _isMoveClick = isMoveClick; }

	//움직이고 있는지 확인용
	bool getIsPlayerMove() { return _isPlayerMove; }
	void setIsPlayerMove(bool isPlayerMove) { _isPlayerMove = isPlayerMove; }

	RECT getSelectRect() { return _player.selectRect; }
	void setSelectRect(RECT selectRect) { _player.selectRect = selectRect; }

	float getAttackPointX() { return _attackPointX; }
	void setAttackPointX(float attackPointX) { _attackPointX = attackPointX; }

	float getAttackPointY() { return _attackPointY; }
	void setAttackPointY(float attackPointY) { _attackPointY = attackPointY; }
};

