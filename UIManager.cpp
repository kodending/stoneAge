#include "stdafx.h"
#include "UIManager.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

HRESULT UIManager::init()
{
	return S_OK;
}

void UIManager::release()
{
}

void UIManager::update()
{
}

void UIManager::render()
{
}

/////////////////////////////
//// ## �޴� �� ���� ##
////////////////////////////
void UIManager::setMenuBar()
{
	_menuBar = new menuBar;
}

void UIManager::updateMenuBar()
{
}

void UIManager::renderMenuBar()
{
}

