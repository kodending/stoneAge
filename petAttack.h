#pragma once
#include "petState.h"

class pet;

class petAttack : public petState
{
private:
	int _preCurrentFrameY;		//���� Y�� �����ϱ�
	bool _isSound1;
	bool _isSound2;
	bool _isSound3;

public:
	virtual petState* inputHandle(pet* pet);
	virtual void update(pet* pet);
	virtual void enter(pet* pet);
	virtual void exit(pet* pet);

	void setPetImage(pet* pet);

	//�ǽð� �� ���⿡ ���� ��ġ ����
	void updatePetImage(pet* pet);
};

