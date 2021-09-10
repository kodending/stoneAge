#pragma once
#include "gameNode.h"
#include "UI.h"
#include "menuBar.h"
#include <vector>

class UIManager : public gameNode
{
private:
	typedef vector<UI*>  vUI;
	typedef vector<UI*>  viUI;
private:
	menuBar* _menuBar;

public:
	UIManager();
	~UIManager();

	HRESULT init();
	void release();
	void update();
	void render();

	/////////////////////////////
	//// ## 메뉴 바 설정 ##
	////////////////////////////
	void setMenuBar();
	void updateMenuBar();
	void renderMenuBar();
};

