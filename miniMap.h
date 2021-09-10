#pragma once
#include "singletonBase.h"
#define MINIMAP_TILE_SIZE 6

class miniMap : public singletonBase<miniMap>
{
private:

	image* _miniMapBuffer;

	int _mapSizeX;
	int _mapSizeY;

	//vector<vector<tagMap>> _miniMap;

public :
	HRESULT init();
	void release();
	void render(HDC hdc);

	void setupMiniMap(int sizeX, int sizeY);
	void drawPlayer(int tileX, int tileY);
};