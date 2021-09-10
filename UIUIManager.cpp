#include "stdafx.h"
#include "UIUIManager.h"

UIUIManager::UIUIManager()
{
}

UIUIManager::~UIUIManager()
{
}

HRESULT UIUIManager::init()
{


	return S_OK;
}

void UIUIManager::release()
{
}

void UIUIManager::update()
{
}

void UIUIManager::render(HDC hdc, float UIX, float UIY)
{
	for (int i = 0; _arrUI.size(); ++i)
	{
		if (_arrUI[i].isFrame)
		{
			if (_arrUI[i].isAlpha)
			{
				IMAGEMANAGER->findImage(_arrUI[i].UIImageName)->alphaFrameRender(hdc, UIX, UIY, *_arrUI[i].currentFrameX, *_arrUI[i].currentFrameY, *_arrUI[i].alpha);
			}

			else
			{
				IMAGEMANAGER->findImage(_arrUI[i].UIImageName)->frameRender(hdc, UIX, UIY, *_arrUI[i].currentFrameX, *_arrUI[i].currentFrameY);
			}
		}

		else
		{
			if (_arrUI[i].isAlpha)
			{
				IMAGEMANAGER->findImage(_arrUI[i].UIImageName)->alphaRender(hdc, UIX, UIY, *_arrUI[i].alpha);
			}

			else
			{
				IMAGEMANAGER->findImage(_arrUI[i].UIImageName)->render(hdc, UIX, UIY);
			}
		}
	}
}

void UIUIManager::renderByRect(string strKey, HDC hdc)
{
	mapUIIter key = _mUIList.find(strKey);

	if (key != _mUIList.end())
	{
		for (int i = 0; i < key->second.size(); i++)
		{
			IMAGEMANAGER->findImage((key->second.begin())->UIImageName)->frameRender(hdc, key->second[i].rc->left, key->second[i].rc->top, *key->second[i].currentFrameX, *key->second[i].currentFrameY);
		}
	}
}

void UIUIManager::render(string strKey, HDC hdc, float UIX, float UIY)
{
	mapUIIter key = _mUIList.find(strKey);

	if (key != _mUIList.end())
	{
		IMAGEMANAGER->findImage((key->second.begin())->UIImageName)->render(hdc, UIX, UIY);
	}
}

void UIUIManager::render(string strKey, HDC hdc, float UIX, float UIY, float currentFrameX, float currentFrameY)
{
	mapUIIter key = _mUIList.find(strKey);

	if (key != _mUIList.end())
	{
		IMAGEMANAGER->findImage((key->second.begin() + 0)->UIImageName)->frameRender(hdc, UIX, UIY, currentFrameX, currentFrameY);
	}
}

void UIUIManager::addUI(string strKey, const char * UIImageName, float *UIX, float *UIY, int *currentFrameX, int *currentFrameY, int *alpha)
{
	UI _UI;
	_UI.UIImageName = UIImageName;
	_UI.x = UIX;
	_UI.y = UIY;
	_UI.currentFrameX = currentFrameX;
	_UI.currentFrameY = currentFrameY;
	_UI.alpha = alpha;
	_UI.isAlpha = true;
	_UI.isFrame = true;

	for (mapUIIter iter = _mUIList.begin(); iter != _mUIList.end(); iter++)
	{
		if (iter->first == strKey)
		{
			iter->second.push_back(_UI);
			return;
		}
	}

	arrUI array;
	array.push_back(_UI);
	_mUIList.insert(make_pair(strKey, array));
}

void UIUIManager::addUI(string strKey, const char * UIImageName, float *UIX, float *UIY, int *currentFrameX, int *currentFrameY)
{
	UI _UI;
	_UI.UIImageName = UIImageName;
	_UI.x = UIX;
	_UI.y = UIY;
	_UI.currentFrameX = currentFrameX;
	_UI.currentFrameY = currentFrameY;
	_UI.isAlpha = false;
	_UI.isFrame = true;

	for (mapUIIter iter = _mUIList.begin(); iter != _mUIList.end(); iter++)
	{
		if (iter->first == strKey)
		{
			iter->second.push_back(_UI);
			return;
		}
	}

	arrUI array;
	array.push_back(_UI);
	_mUIList.insert(make_pair(strKey, array));
}

void UIUIManager::addUI(string strKey, const char * UIImageName, float *UIX, float *UIY, int *alpha)
{
	UI _UI;
	_UI.UIImageName = UIImageName;
	_UI.x = UIX;
	_UI.y = UIY;
	_UI.alpha = alpha;
	_UI.isAlpha = true;
	_UI.isFrame = false;

	for (mapUIIter iter = _mUIList.begin(); iter != _mUIList.end(); iter++)
	{
		if (iter->first == strKey)
		{
			iter->second.push_back(_UI);
			return;
		}
	}

	arrUI array;
	array.push_back(_UI);
	_mUIList.insert(make_pair(strKey, array));
}

void UIUIManager::addUI(string strKey, const char * UIImageName, float *UIX, float *UIY)
{
	UI _UI;
	_UI.UIImageName = UIImageName;
	_UI.x = UIX;
	_UI.y = UIY;
	_UI.isAlpha = false;
	_UI.isFrame = false;

	for (mapUIIter iter = _mUIList.begin(); iter != _mUIList.end(); iter++)
	{
		if (iter->first == strKey)
		{
			iter->second.push_back(_UI);
			return;
		}
	}

	arrUI array;
	array.push_back(_UI);
	_mUIList.insert(make_pair(strKey, array));
}

void UIUIManager::addUI(string strKey, const char * UIImageName, RECT * rc, int* currentFrameX, int* currentFrameY)
{
	UI _UI;
	_UI.UIImageName = UIImageName;
	_UI.x = 0;
	_UI.y = 0;
	_UI.currentFrameX = currentFrameX;
	_UI.currentFrameY = currentFrameY;
	_UI.isAlpha = false;
	_UI.isFrame = false;
	_UI.rc = rc;

	for (mapUIIter iter = _mUIList.begin(); iter != _mUIList.end(); iter++)
	{
		if (iter->first == strKey)
		{
			iter->second.push_back(_UI);
			return;
		}
	}

	arrUI array;
	array.push_back(_UI);
	_mUIList.insert(make_pair(strKey, array));
}

bool UIUIManager::deleteUI(string strKey)
{
	mapUIIter key = _mUIList.find(strKey);

	if (key != _mUIList.end())
	{
		key->second.erase(key->second.begin());
		if (key->second.empty())
		{
			_mUIList.erase(key);
		}
		return true;
	}

	return false;
}

bool UIUIManager::deleteAll()
{
	mapUIIter iter = _mUIList.begin();

	for (; iter != _mUIList.end();)
	{
		if (!iter->second.empty())
		{
			iter->second.clear();
		}
		else ++iter;
	}

	_mUIList.clear();

	return false;
}

