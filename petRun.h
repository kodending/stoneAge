#pragma once
#include "petState.h"

class pet;

class petRun : public petState
{
private:
	int _preCurrentFrameY;		//���� Y�� �����ϱ�

public:
	virtual petState* inputHandle(pet* pet);
	virtual void update(pet* pet);
	virtual void enter(pet* pet);
	virtual void exit(pet* pet);


	void setPetImage(pet* pet);

	//�ǽð� �� ���⿡ ���� ��ġ ����
	void updatePetImage(pet* pet);
};

