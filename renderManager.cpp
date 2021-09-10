#include "stdafx.h"
#include "renderManager.h"

renderManager::renderManager()
{
}

renderManager::~renderManager()
{
}

HRESULT renderManager::init()
{
	return S_OK;
}

void renderManager::release()
{
}

void renderManager::update()
{
	setObjArray();
	quickSort(0, _arrObj.size() - 1);
}

void renderManager::render(HDC hdc, const char* objectImageName, const char* petImageName)
{
	for (int i = 0; i < _arrObj.size(); i++)
	{
		if ((string)(_arrObj[i].objectImageName) == objectImageName)
		{
			IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->frameRender(hdc, *_arrObj[i].imageCenterX - (IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->getFrameWidth() / 2),
				*_arrObj[i].imageCenterY - (IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->getFrameHeight() / 2),
				*_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY);
		}

		if ((string)(_arrObj[i].objectImageName) == petImageName)
		{
			IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->frameRender(hdc, *_arrObj[i].imageCenterX - (IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->getFrameWidth() / 2),
				*_arrObj[i].imageCenterY - (IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->getFrameHeight() / 2),
				*_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY);
		}
	}
}


void renderManager::render(HDC hdc, const char* objectImageName)
{
	for (int i = 0; i < _arrObj.size(); i++)
	{
		//카메라 안에서만 렌더되게 하기위한 작업
		RECT temp;
		RECT cameraRect = RectMakeCenter(CAMERAMANAGER->getCameraLEFT() + (CAMERAX / 2), CAMERAMANAGER->getCameraTOP() + (CAMERAY / 2), CAMERAX + 300, CAMERAY + 300);
		RECT tileRect = RectMake(*_arrObj[i].centerX, *_arrObj[i].centerY, 64, 47);
		if (!IntersectRect(&temp, &cameraRect, &tileRect)) continue;

		//레드 베이직 서있을때 상태에 따라 변동줘야함
		if ((string)(_arrObj[i].objectImageName) == objectImageName)
		{
			IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->frameRender(hdc, *_arrObj[i].imageCenterX - (IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->getFrameWidth() / 2),
				*_arrObj[i].imageCenterY - (IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->getFrameHeight() / 2),
				*_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY);
		}

		else if (_arrObj[i].objectImageName == "structure")
		{
			IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->frameRender(hdc, *_arrObj[i].centerX - 350 + 32 - 32,
				*_arrObj[i].centerY - 350 - 235 - 23.5f + 141 + 70.5 - 23.5f,
				*_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY);
		}

		else if (_arrObj[i].objectImageName == "object")
		{
			IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->frameRender(hdc, *_arrObj[i].centerX - 168 - 32,
				*_arrObj[i].centerY - 203.5f - 23.5f,
				*_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY);
		}

		else if (_arrObj[i].objectImageName == "fence")
		{
			IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->frameRender(hdc, *_arrObj[i].centerX - 38 - 32,
				*_arrObj[i].centerY - 68.5f - 23.5f + 23.5f,
				*_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY);
		}

		else if (_arrObj[i].objectImageName == "gate")
		{
			IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->frameRender(hdc, *_arrObj[i].centerX - 118 + 18 - 32,
				*_arrObj[i].centerY - 203.5f - 125 + 10 - 23.5f,
				*_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY);
		}

		else if (_arrObj[i].objectImageName == "display")
		{
			IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->frameRender(hdc, *_arrObj[i].centerX - 125 + 32 - 32,
				*_arrObj[i].centerY - 125 + 47 - 94 - 23.5f - 47 + 70.5f,
				*_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY);
		}

		else if (_arrObj[i].objectImageName == "plants")
		{
			IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->frameRender(hdc, *_arrObj[i].centerX - 150 + 35 - 32,
				*_arrObj[i].centerY - 150 + 47 - 94 - 14 - 23.5f,
				*_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY);
		}

		else if (_arrObj[i].objectImageName == "rock")
		{
			IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->frameRender(hdc, *_arrObj[i].centerX - 50 + 32 - 32,
				*_arrObj[i].centerY - 50 - 23.5f,
				*_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY);
		}

		else if (_arrObj[i].objectImageName == "wall_basic")
		{
			IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->frameRender(hdc, *_arrObj[i].centerX - 200 + 32 - 32 + 16,
				*_arrObj[i].centerY - 200 + 23.5f - 96 - 23.5f + 11.75f,
				*_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY);
		}

		else if (_arrObj[i].objectImageName == "wall_dungeon")
		{
			IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->frameRender(hdc, *_arrObj[i].centerX - 200 + 34 - 32,
				*_arrObj[i].centerY - 250 + 23.5f - 141 - 23.5f,
				*_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY);
		}

		else if (_arrObj[i].objectImageName == "npc")
		{
			IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->frameRender(hdc, *_arrObj[i].centerX - 50 + 32 - 32,
				*_arrObj[i].centerY - 50 + 23.5f - 40 - 23.5f,
				*_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY);
		}
	}
}

void renderManager::render(HDC hdc)
{
	for (int i = 0; i < _arrObj.size(); i++)
	{
		IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->frameRender(hdc, *_arrObj[i].imageCenterX - (IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->getFrameWidth() / 2),
			*_arrObj[i].imageCenterY - (IMAGEMANAGER->findImage(_arrObj[i].objectImageName)->getFrameHeight() / 2),
			*_arrObj[i].currentFrameX, *_arrObj[i].currentFrameY);
	}
}

void renderManager::addObj(string strKey, const char* objectImageName, bool* objectRenderd, float* centerX, float* centerY, int* currentFrameX, int* currentFrameY)
{
	OBJ object;
	object.objectImageName = objectImageName;
	object.centerX = centerX;
	object.centerY = centerY;
	object.currentFrameX = currentFrameX;
	object.currentFrameY = currentFrameY;
	object.objRendered = objectRenderd;

	for (mapObjIter iter = _mObjList.begin(); iter != _mObjList.end(); iter++)
	{
		if (iter->first == strKey)
		{
			iter->second.push_back(object);
			return;
		}
	}
	arrObj array;
	array.push_back(object);
	_mObjList.insert(make_pair(strKey, array));
}

void renderManager::addObj(string strKey, const char * objectImageName, float * centerX, float * centerY, int * currentFrameX, int * currentFrameY)
{
	OBJ object;
	object.objectImageName = objectImageName;
	object.centerX = centerX;
	object.centerY = centerY;
	object.currentFrameX = currentFrameX;
	object.currentFrameY = currentFrameY;
	object.objRendered = false;

	for (mapObjIter iter = _mObjList.begin(); iter != _mObjList.end(); iter++)
	{
		if (iter->first == strKey)
		{
			iter->second.push_back(object);
			return;
		}
	}
	arrObj array;
	array.push_back(object);
	_mObjList.insert(make_pair(strKey, array));
}

void renderManager::addObj(string strKey, const char * objectImageName, float * centerX, float * centerY, float* imageCenterX, float* imageCenterY, int * currentFrameX, int * currentFrameY)
{
	OBJ object;
	object.objectImageName = objectImageName;
	object.centerX = centerX;
	object.centerY = centerY;
	object.currentFrameX = currentFrameX;
	object.currentFrameY = currentFrameY;
	object.imageCenterX = imageCenterX;
	object.imageCenterY = imageCenterY;
	object.objRendered = false;

	for (mapObjIter iter = _mObjList.begin(); iter != _mObjList.end(); iter++)
	{
		if (iter->first == strKey)
		{
			iter->second.push_back(object);
			return;
		}
	}
	arrObj array;
	array.push_back(object);
	_mObjList.insert(make_pair(strKey, array));
}

bool renderManager::deleteObj(string strKey, float* centerX, float* centerY)
{
	mapObjIter key = _mObjList.find(strKey);

	if (key != _mObjList.end())
	{
		for (int i = 0; i < _arrObj.size(); ++i)
		{
			if ((*(key->second.begin() + i)).centerX == centerX &&
				(*(key->second.begin() + i)).centerY == centerY)
			{
				key->second.erase(key->second.begin() + i);
				if (key->second.empty())
				{
					_mObjList.erase(key);
				}
				return true;
			}
		}
	}

	return false;
}

void renderManager::setObjArray()
{
	//arr 저장한사이즈가 다를경우, 즉 arr가 늘어날 경우 다시 set obj해라
	if (!_arrObj.empty())
	{
		_arrObj.clear();
	}

	for (mapObjIter mIter = _mObjList.begin(); mIter != _mObjList.end(); mIter++)
	{
		for (iterObj vIter = mIter->second.begin(); vIter != mIter->second.end(); vIter++)
		{
			_arrObj.push_back(*vIter);
		}
	}
}

void renderManager::quickSort(int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int pivot = left;
	int i = left + 1;
	int j = right;
	OBJ temp;

	while (i <= j)
	{
		while (i <= right && *_arrObj[i].centerY <= *_arrObj[pivot].centerY) i++;
		while (j > left && *_arrObj[j].centerY >= *_arrObj[pivot].centerY) j--;

		if (i > j)
		{
			temp = _arrObj[pivot];
			_arrObj[pivot] = _arrObj[j];
			_arrObj[j] = temp;
		}
		else
		{
			temp = _arrObj[j];
			_arrObj[j] = _arrObj[i];
			_arrObj[i] = temp;
		}
	}
	quickSort(left, j - 1);
	quickSort(j + 1, right);
}

bool renderManager::deleteAll()
{
	mapObjIter iter = _mObjList.begin();

	for (; iter != _mObjList.end();)
	{
		if (!iter->second.empty())
		{
			iter->second.clear();
		}
		else ++iter;
	}

	_mObjList.clear();

	return false;
}


