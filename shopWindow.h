#pragma once
#include "menuType.h"

class tileMap;

struct tagShopWindow
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT exitRect;			//�ݱ� ��Ʈ
	RECT buyRect;			//��� ��Ʈ
	RECT sellRect;			//�ȴ� ��Ʈ
};

class shopWindow : public menuType
{
private:
	tagShopWindow _shopWindow;

public:
	virtual menuType* inputHandle(tileMap * tileMap);
	virtual void update(tileMap * tileMap);
	virtual void enter(tileMap * tileMap);
	virtual void render(tileMap * tileMap);
	virtual void exit(tileMap * tileMap);

	void updateRect(tileMap* tileMap);

	void textRender(tileMap* tileMap);

	void PtInRender(tileMap* tileMap);
};

