#include "stdafx.h"
#include "aStarTile.h"

aStarTile::aStarTile()
	: _totalCost(0), _costFromStart(0),
	_costToGoal(0), _parentNode(NULL),
	_idX(0), _idY(0), _isOpen(true)
{
}

aStarTile::~aStarTile()
{
}

HRESULT aStarTile::init(int idX, int idY)
{
	//_color = RGB(255, 0, 255);
	//_brush = CreateSolidBrush(_color);
	//_pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	_center = PointMake(INIT_X + (idX * RADIUS_WIDTH) - (idY * RADIUS_WIDTH) + RADIUS_WIDTH,
		INIT_Y + (idX * RADIUS_HEIGHT) + (idY * RADIUS_HEIGHT) + RADIUS_HEIGHT);

	_idX = idX;
	_idY = idY;

	_rc = RectMakeCenter(_center.x, _center.y, CELL_WIDTH, CELL_HEIGHT);

	return S_OK;
}

void aStarTile::release()
{
}

void aStarTile::update()
{
}

void aStarTile::render(float centerX, float centerY)
{
	POINT p[5];
	p[0].x = centerX;
	p[0].y = centerY - RADIUS_HEIGHT;
	p[1].x = centerX + RADIUS_WIDTH;
	p[1].y = centerY;
	p[2].x = centerX;
	p[2].y = centerY + RADIUS_HEIGHT;
	p[3].x = centerX - RADIUS_WIDTH;
	p[3].y = centerY;
	p[4].x = centerX;
	p[4].y = centerY - RADIUS_HEIGHT;

	MoveToEx(getMemDC(), p[0].x, p[0].y, NULL);
	for (int i = 1; i < 5; i++)
	{
		LineTo(getMemDC(), p[i].x, p[i].y);
	}
}

void aStarTile::render()
{
}
