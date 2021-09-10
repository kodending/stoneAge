#include "stdafx.h"
#include "UI.h"

UI::UI()
{
}

UI::~UI()
{
}

HRESULT UI::init()
{
	return S_OK;
}

HRESULT UI::init(const char * imageName, int vectorSize)
{
	_currentFrameX = _currentFrameY = 0;
	_elapsedTime = 0;

	_imageName = IMAGEMANAGER->findImage(imageName);

	for (int i = 0; i < vectorSize; ++i)
	{
		RECT _rc;

		_vRc.push_back(_rc);
	}

	return S_OK;
}

void UI::release()
{

}

void UI::update(float frameSpeed)
{
	_elapsedTime += TIMEMANAGER->getElapsedTime();

	if (_elapsedTime >= frameSpeed)
	{
		_elapsedTime -= frameSpeed;

		if (_currentFrameX == _imageName->getMaxFrameX())
		{
			_currentFrameX = 0;
		}

		else _currentFrameX++;
	}
}

void UI::render()
{

}

void UI::rectMake(float left, float top, float width, float height, int vectorSize)
{
	(*(_vRc.begin() + vectorSize)) = RectMake(left, top, width, height);
}

void UI::draw(float startX, float startY)
{
	_imageName->render(getMemDC(), startX, startY);

	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		Rectangle(getMemDC(), (*(_vRc.begin() + 0)));
	}
}

void UI::frameDraw(float startX, float startY)
{
	_imageName->frameRender(getMemDC(), startX, startY, _currentFrameX, _currentFrameY);
}
