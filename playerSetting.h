#pragma once
#include "gameNode.h"
#include <vector>

struct tagPlayerAttribute
{
	image* img;
	RECT rc;
	int currentFrameX;
	int currentFrameY;
};

struct tagPlayerType
{
	image* img;
	RECT rc;
	int currentFrameX;
	int currentFrameY;
};

struct tagInputWindow3
{
	image* frontImg;
	image* backImg;
	image* checkImg;
	RECT frontRect;
	RECT backRect;
	RECT checkRect;
	RECT textRect;
};

struct tagInputWindow2
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	RECT decideRect;
	RECT rejectRect;
	RECT textRect;
};

class playerSetting : public gameNode
{
private:
	tagPlayerType _playerType;

	bool _isWriteInidata; //inidata 불러왔는지 확인용

	string name;			//nickName 작성받기위한 이름용도
	string _dialog;			//입력받은 키값 저장용도
	RECT _nameRect;			//닉네임 텍스트 위치 교정을위한용도
	int _baseStatusCount;	//기본능력치 20개
	int _statusStamina;		//체력능력치
	int _statusStrength;	//완력능력치
	int _statusHealth;		//건강능력치
	int _statusSpeed;		//스피드능력치

	int _baseAttributeCount;		//기본속성 10개
	int _attributeFire;				//화속성
	int _attributeWater;			//수속성
	int _attributeLand;				//지속성
	int _attributeWind;				//풍속성

	bool _isDecideRect;			//결정버튼을 눌렀는지 확인용
	bool _isReturnRect;			//리턴버튼을 눌렀는지 확인용
	bool _isIncompleteWindow;	//아직 스탯을 못찍었을때 뜨게하기

	tagPlayerAttribute	_arrayAttributeFire[10];		//화속성 배열
	tagPlayerAttribute	_arrayAttributeWater[10];		//수속성 배열
	tagPlayerAttribute	_arrayAttributeLand[10];		//지속성 배열
	tagPlayerAttribute	_arrayAttributeWind[10];		//풍속성 배열

	RECT _decideRect;			//결정렉트
	RECT _returnRect;			//돌아가기렉트
	RECT _statusRect[2][4];		//스탯찍기렉트
	RECT _attributeRect[2][4];  //속성찍기렉트

	tagInputWindow3	_inCompleteWindow;	//미완성 윈도우창
	tagInputWindow2 _decideWindow;		//결정 윈도우창
	tagInputWindow2 _returnWindow;		//리턴 윈도우창

public:
	playerSetting();
	~playerSetting();

	HRESULT init();
	void release();
	void update();
	void render();

	void selectRed();
	void selectBlue();

	//아이디 다이얼로그입력받기위한 작업쓰
	void dialogSetNickName();
	void dialogInput();
	void dialogRender();

	//스테이터스렉트 찍는것에대한 작업쓰
	void statusSelect();

	//속성렉트 찍는것에대한 작업쓰
	void attributeSelect();
	void attributeRect();
	void attributeRender();

	//마우스올리면 렉트그려주기
	void ptInRectRender();

	//텍스트 그려내기
	void textOutRender();

	//결정버튼, 돌아가기버튼
	void decideButton();
	void returnButton();

	//버튼 활성화확인
	void buttonActive();
	void buttonRender();

	//이니데이타 세이브
	void saveInidata();
};

