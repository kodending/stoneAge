#pragma once
#include "gameNode.h"

class pet;

class petState : public gameNode
{
protected:

public:
	virtual petState* inputHandle(pet* pet) = 0;
	virtual void update(pet* pet) = 0;
	virtual void enter(pet* pet) = 0;
	virtual void exit(pet* pet) = 0;
};

