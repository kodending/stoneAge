#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include <string>

class aStarTile : public gameNode
{
private:
	int _idX;
	int _idY;

	POINT _center;
	RECT _rc;

	//F = G + H 
	//F == �� �Ÿ� ��� (TotalCost)
	//G == ���������κ��� ���� ������ ��κ��(CostFromStart)
	//H == ������κ��� ���������� ��κ��(CostToGoal)

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;//�����ִ� Ÿ������ ����

	aStarTile* _parentNode; //���� ���� Ÿ�� (��� ���ŵǴ� Ÿ��)

	//COLORREF	_color;
	//HBRUSH		_brush;

	string _attribute;

public:
	aStarTile();
	~aStarTile();

	HRESULT init(int idX, int idY);
	void release();
	void update();
	void render(float centerX, float centerY);
	void render();

	int getIdX() { return _idX; }
	int getIdY() { return _idY; }
	void setIdX(int idX) { _idX = idX; }
	void setIdY(int idY) { _idY = idY; }

	//void setColor(COLORREF color)
	//{
	//	DeleteObject(_brush);
	//	_color = color;
	//	_brush = CreateSolidBrush(_color);
	//}

	//COLORREF getColor() { return _color; }

	void setCenter(POINT center) { _center = center; }
	POINT getCenter() { return _center; }

	void setAttribute(string str) { _attribute = str; }
	string getAttribute() { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	void setRect(RECT rc) { _rc = rc; }
	RECT getRect() { return _rc; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setParentNode(aStarTile* t) { _parentNode = t; }
	aStarTile* getParentNode() { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen() { return _isOpen; }
};

