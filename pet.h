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
	image* _imageName;			//펫 이미지
	string _renderName;			//렌더매니저 등록할 변수
	string _petNameString;		//펫이름
	RECT _imageRect;			//이미지 렉트
	RECT _tileRect;				//현재 타일
	RECT _selectRect;			//선택할때 뜨는 렉트
	float _tileCenterX;			//현재 타일 센터좌표 X
	float _tileCenterY;			//현재 타일 센터좌표 Y
	float _imageCenterX;		//이미지 중점좌표
	float _imageCenterY;		//이미지 중점좌표
	float _imageMoveX;			//이미지 조정할 용도
	float _imageMoveY;			//이미지 조정할 용도
	float _attackPointX;		//공격할 포인트 찍기
	float _attackPointY;		//공격할 포인트 찍기

	float _moveEndX;			//등장씬 이동마지막좌표;
	float _moveEndY;			//등장씬 이동마지막좌표;

	int _currentFrameX;
	int _currentFrameY;

	float _elapsedSec;			//프레임 속도 변수받기
	float _elapsedTime;			//이미지 프레임용

	DIRECTION _petDirection;	//방향
	PETSTATE _enumPetState;		//펫스테이트 이넘문
	PETNAME _petName;			//펫종

	bool _isPlayerPet;			//플레이어 펫인지 여부 확인
	bool _isBattleMode;			//배틀에 나오는 펫인지 여부
	bool _isRideMode;			//탑승 했는지 여부
	bool _isAvailableRide;		//탑승 가능한 펫인지 확인
	bool _isMove;				//움직이고있는지 확인

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
	PETSKILL _petSkill;						//페트가 선택한 기술
	bool _isAttackTime;						//공격순서를 위한 공격타임인지 결정
	bool _isAttacked;						//공격했는지를 확인하기 위한 
	bool _isAttackClose;					//공격을 마쳤는지 확인
	bool _isHurt;							//공격이 들어왔을때
	bool _isDefenseOn;						//방어성공했을때 (방어렌더해주기위함임)
	int _damageCount;						//데미지 먹힌 카운트값
	bool _isDamaged;						//공격먹혔을때 데미지값렌더해주기위함
	int _damageTimeCount;					//데미지 일정시간동안만 뜨게해주기
	bool _isCatched;						//포획되었는지 확인
	bool _isDead;							//죽었는지 확인용
	bool _isDeadTime;						//죽기전 행동할때 다음 공격이 이뤄지지않도록하기위함
	float _prePositionX;					//캐치되기전 타일x
	float _prePositionY;					//캐치되기전 타일y
	bool _prePositionSave;					//포지션x,y저장되었는지확인용

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

	//게터세터 설정

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

