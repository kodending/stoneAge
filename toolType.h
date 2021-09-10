#pragma once
#include "gameNode.h"

class mapTool;

class toolType : public gameNode
{
protected:

public:
	virtual toolType* inputHandle(mapTool* mapTool) = 0;
	virtual void update(mapTool* mapTool) = 0;
	virtual void enter(mapTool* mapTool) = 0;
	virtual void render(mapTool* mapTool) = 0;
	virtual void exit(mapTool* mapTool) = 0;
};

