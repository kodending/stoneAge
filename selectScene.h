#pragma once
#include "gameNode.h"

struct tagCreateButton
{
	image* img;
	RECT rc;
};

struct tagLoginButton
{
	image* img;
	RECT rc;
};

struct tagDeleteButton
{
	image* img;
	RECT rc;
	bool isDeleteWindow;
};

struct tagPlayerAttribute2
{
	image* img;
	RECT rc;
	int currentFrameX;
	int currentFrameY;
};

struct tagInputWindow4
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	RECT decideRect;
	RECT rejectRect;
	RECT textRect;
};

struct tagPlayerInfo
{
	string name;										//플레이어 이름
	int type;											//플레이어 종류
	int level;											//플레이어 레벨
	int totalStamina;									//플레이어 총내구력
	int attackPower;									//플레이어 공격력
	int defensePower;									//플레이어 방어력
	int speedPower;										//플레이어 순발력
	int charming;										//플레이어 매력
	int loginNum;										//플레이어 로그인횟수
	int attributeLand;									//플레이어 지속성
	int attributeWater;									//플레이어 수속성
	int attributeFire;									//플레이어 화속성
	int attributeWind;									//플레이어 풍속성
	image* playerFace;									//플레이어 페이스
	int faceCurrentFrameX;								//플레이어 현재 프레임X
	int faceCurrentFrameY;								//플레이어 현재 프레임Y
	tagPlayerAttribute2	_arrayAttributeFire[10];		//화속성 배열
	tagPlayerAttribute2	_arrayAttributeWater[10];		//수속성 배열
	tagPlayerAttribute2	_arrayAttributeLand[10];		//지속성 배열
	tagPlayerAttribute2	_arrayAttributeWind[10];		//풍속성 배열
};

class selectScene : public gameNode
{
private:
	char* _player1;
	char* _player2;

	bool _isPlayer[2];  //플레이어가 있을경우

	tagCreateButton _createButton[2];   //캐릭터생성버튼
	tagLoginButton  _loginButton[2];	//로그인버튼
	tagDeleteButton _deleteButton[2];	//삭제버튼

	bool _isWriteInidata;				//이니데이타 읽어오는 용도

	tagPlayerInfo _playerInfo1;			//플레이어1 정보력
	tagPlayerInfo _playerInfo2;			//플레이어2 정보력

	tagInputWindow4 _deleteWindow;		//삭제 알림창 
	bool _isMusic;
	bool _isInit = false;

public:
	selectScene();
	~selectScene();

	HRESULT init();
	void release();
	void update();
	void render();

	//플레이어가 없을경우 함수
	void nonePlayer();
	void nonePlayerRender();

	//플레이어가 있을경우 함수
	void existPlayer();
	void existPlayerRender();

	//마우스올라갔을때 렌더
	void ptInRectRender();

	//이니데이타 확인용
	void writeInidata();

	//삭제알림창 불들어왔을때 쓰는 함수
	void deleteWindowUpdate();
	void deleteWindowRender();

	void writeInit();
};

