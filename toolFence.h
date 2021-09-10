#pragma once
#include "toolType.h"

class mapTool;

class toolFence : public toolType
{
private:

public:
	virtual toolType* inputHandle(mapTool* mapTool);
	virtual void update(mapTool* mapTool);
	virtual void enter(mapTool* mapTool);
	virtual void render(mapTool* mapTool);
	virtual void exit(mapTool* mapTool);
};

