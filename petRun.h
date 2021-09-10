#pragma once
#include "petState.h"

class pet;

class petRun : public petState
{
private:
	int _preCurrentFrameY;		//전에 Y값 저장하기

public:
	virtual petState* inputHandle(pet* pet);
	virtual void update(pet* pet);
	virtual void enter(pet* pet);
	virtual void exit(pet* pet);


	void setPetImage(pet* pet);

	//실시간 펫 방향에 따른 위치 조정
	void updatePetImage(pet* pet);
};

