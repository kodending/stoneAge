#pragma once
#include "gameNode.h"
#include "playerState.h"

enum PLAYERSTATE
{
	STATE_ANGRY,		//ȭ��
	STATE_ATTACK,		//����
	STATE_CRY,			//����
	STATE_DEAD,			//����
	STATE_DEFENSE,		//���
	STATE_HAPPY,		//���
	STATE_HELLO,		//�λ�
	STATE_HURT,			//���ݹ޴�
	STATE_RUN,			//�ٴ�(�ȴ�)
	STATE_SEAT,			//�ɴ�
	STATE_STAND			//���ִ�
};

struct tagPlayer
{
	DIRECTION direction;
	PLAYERSTATE playerState;
	PLAYERWEAPON playerWeapon;
	PLAYERCHARACTER playerCharacter;
	RECT rc;
	RECT currentTileRect;				//�÷��̾� Ŀ��Ʈ Ÿ�Ϸ�Ʈ
	float centerX, centerY;				//Ŀ��Ʈ Ÿ�Ϸ�Ʈ�� ������ǥ 
	int currentFrameX, currentFrameY;	//����������
	image* img;							//�÷��̾� �̹���
	float moveSpeedX;					//�÷��̾� ���꽺�ǵ� X
	float moveSpeedY;					//�÷��̾� ���꽺�ǵ� Y
	float playerCenterX, playerCenterY;	//�÷��̾� �̹��� ������ǥ
	RECT selectRect;					//������Ʈ
};

class player : public gameNode
{
private:
	float _elapsedSec;			//������ ������

	bool _isMoveClick;			//moveClick �ߴ���Ȯ�ο�
	bool _isPlayerMove;			//�̵������� Ȯ�ο�

	float _moveEndX, _moveEndY;				//������ǥ ����

	float _imageMoveX, _imageMoveY;			//ĳ���� �̹��� ������ ���� x,y��ǥ �̵��ϱ�����
	float _frameAdjustTime;					//������ �ӵ� ������
	bool _isActionRun;						//���� �� �׼������� Ȯ�ο�

	float _attackPointX, _attackPointY;		//������ǥ

public:
	playerState* _playerState;
	tagPlayer _player;
	string _playerImageName;
	bool _isAttackTime;						//���ݼ����� ���� ����Ÿ������ ����
	bool _isAttacked;						//�����ߴ����� Ȯ���ϱ� ���� 
	bool _isAttackClose;					//������ ���ƴ��� Ȯ��
	bool _isHurt;							//������ ��������	
	bool _isDefenseOn;						//���������� �������ֱ�����
	int _damageCount;						//������ ���� ī��Ʈ��
	bool _isDamaged;						//���ݸ������� ���������������ֱ�����
	int _damageTimeCount;					//������ �����ð����ȸ� �߰����ֱ�
	bool _isDead;							//�׾����� Ȯ�ο�
	bool _isPetCatch;						//���� ��ȹ������Ȯ�ο�
	bool _isEscape;							//����ġ���ִ��� Ȯ�ο�
	bool _isEscapeSuccess;					//����������

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

	//���긦 �������� Ȯ�ο�
	bool getIsMoveClick() { return _isMoveClick; }
	void setIsMoveClick(bool isMoveClick) { _isMoveClick = isMoveClick; }

	//�����̰� �ִ��� Ȯ�ο�
	bool getIsPlayerMove() { return _isPlayerMove; }
	void setIsPlayerMove(bool isPlayerMove) { _isPlayerMove = isPlayerMove; }

	RECT getSelectRect() { return _player.selectRect; }
	void setSelectRect(RECT selectRect) { _player.selectRect = selectRect; }

	float getAttackPointX() { return _attackPointX; }
	void setAttackPointX(float attackPointX) { _attackPointX = attackPointX; }

	float getAttackPointY() { return _attackPointY; }
	void setAttackPointY(float attackPointY) { _attackPointY = attackPointY; }
};

