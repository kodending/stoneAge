#pragma once
#include "gameNode.h"
#include "petState.h"

enum PETSTATE
{
	PET_RUN,
	PET_DEAD,
	PET_DEFENSE,
	PET_HURT,
	PET_ATTACK,
	PET_STAND,
	PET_CATCHED
};

class pet : public gameNode
{
protected:
	image* _imageName;			//�� �̹���
	string _renderName;			//�����Ŵ��� ����� ����
	string _petNameString;		//���̸�
	RECT _imageRect;			//�̹��� ��Ʈ
	RECT _tileRect;				//���� Ÿ��
	RECT _selectRect;			//�����Ҷ� �ߴ� ��Ʈ
	float _tileCenterX;			//���� Ÿ�� ������ǥ X
	float _tileCenterY;			//���� Ÿ�� ������ǥ Y
	float _imageCenterX;		//�̹��� ������ǥ
	float _imageCenterY;		//�̹��� ������ǥ
	float _imageMoveX;			//�̹��� ������ �뵵
	float _imageMoveY;			//�̹��� ������ �뵵
	float _attackPointX;		//������ ����Ʈ ���
	float _attackPointY;		//������ ����Ʈ ���

	float _moveEndX;			//����� �̵���������ǥ;
	float _moveEndY;			//����� �̵���������ǥ;

	int _currentFrameX;
	int _currentFrameY;

	float _elapsedSec;			//������ �ӵ� �����ޱ�
	float _elapsedTime;			//�̹��� �����ӿ�

	DIRECTION _petDirection;	//����
	PETSTATE _enumPetState;		//�꽺����Ʈ �̳ѹ�
	PETNAME _petName;			//����

	bool _isPlayerPet;			//�÷��̾� ������ ���� Ȯ��
	bool _isBattleMode;			//��Ʋ�� ������ ������ ����
	bool _isRideMode;			//ž�� �ߴ��� ����
	bool _isAvailableRide;		//ž�� ������ ������ Ȯ��
	bool _isMove;				//�����̰��ִ��� Ȯ��

	int _petCurrentStamina;
	int _petTotalStamina;
	int _petAttackPower;
	int _petDefensePower;
	int _petSpeedPower;
	int _attributeLandCount;
	int _attributeWindCount;
	int _attributeWaterCount;
	int _attributeFireCount;
	int _petLevel;

public:
	petState* _petState;
	int _petSkillNum[6];
	PETSKILL _petSkill;						//��Ʈ�� ������ ���
	bool _isAttackTime;						//���ݼ����� ���� ����Ÿ������ ����
	bool _isAttacked;						//�����ߴ����� Ȯ���ϱ� ���� 
	bool _isAttackClose;					//������ ���ƴ��� Ȯ��
	bool _isHurt;							//������ ��������
	bool _isDefenseOn;						//���������� (�������ֱ�������)
	int _damageCount;						//������ ���� ī��Ʈ��
	bool _isDamaged;						//���ݸ������� ���������������ֱ�����
	int _damageTimeCount;					//������ �����ð����ȸ� �߰����ֱ�
	bool _isCatched;						//��ȹ�Ǿ����� Ȯ��
	bool _isDead;							//�׾����� Ȯ�ο�
	bool _isDeadTime;						//�ױ��� �ൿ�Ҷ� ���� ������ �̷������ʵ����ϱ�����
	float _prePositionX;					//ĳġ�Ǳ��� Ÿ��x
	float _prePositionY;					//ĳġ�Ǳ��� Ÿ��y
	bool _prePositionSave;					//������x,y����Ǿ�����Ȯ�ο�

	pet() {};
	~pet() {};

	void InputHandle();

	virtual HRESULT init();
	virtual HRESULT init(POINT position, DIRECTION petDirection, PETSTATE petState, PETNAME petName, bool isPlayerPet);
	virtual void release();
	virtual void update();
	virtual void render();

	void deletePet();

	void setPetName();
	void setPlayerPetName();

	//���ͼ��� ����

	image* getImage() { return _imageName; }
	void setImage(image* image) { _imageName = image; }

	RECT getTileRect() { return _tileRect; }
	void setTileRect(RECT tileRect) { _tileRect = tileRect; }

	RECT getImageRect() { return _imageRect; }
	void setImageRect(RECT imageRect) { _imageRect = imageRect; }

	RECT getSelectRect() { return _selectRect; }
	void setSelectRect(RECT selectRect) { _selectRect = selectRect; }

	int getCurrentFrameX() { return _currentFrameX; }
	void setCurrentFrameX(int frameX) { _currentFrameX = frameX; }

	int getCurrentFrameY() { return _currentFrameY; }
	void setCurrentFrameY(int frameY) { _currentFrameY = frameY; }

	DIRECTION getPetDirection() { return _petDirection; }
	void setPetDirection(DIRECTION petDirection) { _petDirection = petDirection; }

	PETSTATE getEnumPetState() { return _enumPetState; }
	void setEnumPetState(PETSTATE enumPetState) { _enumPetState = enumPetState; }

	float getTileCenterX() { return _tileCenterX; }
	void setTileCenterX(float tileCenterX) { _tileCenterX = tileCenterX; }

	float getTileCenterY() { return _tileCenterY; }
	void setTileCenterY(float tileCenterY) { _tileCenterY = tileCenterY; }

	float getImageCenterX() { return _imageCenterX; }
	void setImageCenterX(float imageCenterX) { _imageCenterX = imageCenterX; }

	float getImageCenterY() { return _imageCenterY; }
	void setImageCenterY(float imageCenterY) { _imageCenterY = imageCenterY; }

	float getImageMoveX() { return _imageMoveX; }
	void setImageMoveX(float imageMoveX) { _imageMoveX = imageMoveX; }

	float getImageMoveY() { return _imageMoveY; }
	void setImageMoveY(float imageMoveY) { _imageMoveY = imageMoveY; }

	PETNAME getPetName() { return _petName; }
	void setPetName(PETNAME petName) { _petName = petName; }

	string getPetRenderName() { return _renderName; }
	void setPetRenderName(string renderName) { _renderName = renderName; }

	bool getIsPlayerPet() { return _isPlayerPet; }
	void setIsPlayerPet(bool isPlayerPet) { _isPlayerPet = isPlayerPet; }

	int getPetTotalStamina() { return _petTotalStamina; }
	void setPetTotalStamina(int TotalStamina) { _petTotalStamina = TotalStamina; }

	int getPetCurrentStamina() { return _petCurrentStamina; }
	void setPetCurrentStamina(int CurrentStamina) { _petCurrentStamina = CurrentStamina; }

	int getPetAttackPower() { return _petAttackPower; }
	void setPetAttackPower(int petAttackPower) { _petAttackPower = petAttackPower; }

	int getPetDefensePower() { return _petDefensePower; }
	void setPetDefensePower(int petDefensePower) { _petDefensePower = petDefensePower; }

	int getPetSpeedPower() { return _petSpeedPower; }
	void setPetSpeedPower(int petSpeedPower) { _petSpeedPower = petSpeedPower; }

	int getAttributeLandCount() { return _attributeLandCount; }
	void setAttributeLandCount(int attributeLandCount) { _attributeLandCount = attributeLandCount; }

	int getAttributeWaterCount() { return _attributeWaterCount; }
	void setAttributeWaterCount(int attributeWaterCount) { _attributeWaterCount = attributeWaterCount; }

	int getAttributeFireCount() { return _attributeFireCount; }
	void setAttributeFireCount(int attributeFireCount) { _attributeFireCount = attributeFireCount; }

	int getAttributeWindCount() { return _attributeWindCount; }
	void setAttributeWindCount(int attributeWindCount) { _attributeWindCount = attributeWindCount; }

	float getMoveEndX() { return _moveEndX; }
	void setMoveEndX(float moveEndX) { _moveEndX = moveEndX; }

	float getMoveEndY() { return _moveEndY; }
	void setMoveEndY(float moveEndY) { _moveEndY = moveEndY; }

	bool getIsMove() { return _isMove; }
	void setIsMove(bool isMove) { _isMove = isMove; }

	float getAttackPointX() { return _attackPointX; }
	void setAttackPointX(float attackPointX) { _attackPointX = attackPointX; }

	float getAttackPointY() { return _attackPointY; }
	void setAttackPointY(float attackPointY) { _attackPointY = attackPointY; }

	int getLevel() { return _petLevel; }
	void setLevel(int level) { _petLevel = level; }

	string getPetNameString() { return _petNameString; }
	void setPetNameString(string petNameString) { _petNameString = petNameString; }

	bool getIsAvailableRide() { return _isAvailableRide; }
	void setIsAvailableRide(bool isAvailableRide) { _isAvailableRide = isAvailableRide; }
};

