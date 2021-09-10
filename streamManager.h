#pragma once
#include "singletonBase.h"
#include "video.h"
#include <map>

class streamManager : public singletonBase<streamManager>
{
private:
	typedef map<string, video*>				mapVideoList;
	typedef map<string, video*>::iterator		mapVideoIter;

	mapVideoList _mapVideoList;
	string currentVideo;

	bool _isPlay; //스트림이시작했는지 확인용

public:
	streamManager();
	~streamManager();
	HRESULT init(void);
	void release();

	video* addVideo(const char* fileName, string strKey);
	void startVideo(string strKey);
	void closeVideo(string strKey);
	void deletVideo(string strKey);
	void playVido(string strKey);

	//void getPosition();
	//void getLenthEnd();
	
	video* findVideo(string strKey);

	long getPosition(string strKey) { video* _video = findVideo(strKey); return _video->getLnagStart(); }
	long getLenthEnd(string strKey) { video* _video = findVideo(strKey); return _video->getLangEnd(); }
	long getLenthTheEnd(string strKey) { video* _video = findVideo(strKey); return _video->getLangthEnd(); }
	long getLenthStop(string strKey) { video* _video = findVideo(strKey); return _video->getStop(); }

	bool getIsPlay() { return _isPlay; }
};



	

