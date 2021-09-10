#include "stdafx.h"
#include "streamManager.h"


streamManager::streamManager()
{
}


streamManager::~streamManager()
{
}

HRESULT streamManager::init(void)
{
	_isPlay = false;

	return S_OK;
}

void streamManager::release()
{
}

video* streamManager::addVideo(const char * fileName, string strKey)
{
	
	video* _video = findVideo(strKey);
	if (_video) return _video;
	_video = new video;
	//_video->setVideo(fileName);
	if (FAILED(_video->setVideo(fileName)))
	{
		SAFE_DELETE(_video);

		return nullptr;
	}

	_mapVideoList.insert(make_pair(strKey, _video));

	return _video;

}

void streamManager::startVideo(string strKey)
{
	video* _video = findVideo(strKey);
	for (mapVideoIter iter = _mapVideoList.begin(); iter != _mapVideoList.end(); iter++) 
	{
		if(_video != iter->second)
		iter->second->closeVideo();

	}
	_video->playVideo();
	_isPlay = true;
}

void streamManager::closeVideo(string strKey)
{
	video* _video = findVideo(strKey);
	_video->closeVideo();
	_video->deletVideo();
//	_mapVideoList.erase(strKey);
	_isPlay = false;
}

void streamManager::deletVideo(string strKey)
{
	video* _video = findVideo(strKey);
	_video->closeVideo();
	//_video->deletVideo();
	_mapVideoList.erase(strKey);
	_isPlay = false;
}
void streamManager::playVido(string strKey)
{
	video* _video = findVideo(strKey);
	_video->playVideo();
	_isPlay = true;
}





video * streamManager::findVideo(string strKey)
{
	mapVideoIter key = _mapVideoList.find(strKey);

	if (key != _mapVideoList.end())
	{
		return key->second;
	}

	return nullptr;
}


