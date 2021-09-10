#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "player.h"
#include "aStarTile.h"
#include "menuType.h"
#include "pet.h"
#include "item.h"
#include <vector>
#include <string>

enum SCENENAME
{
	SCENE_VILLAGE,		//마을 씬
	SCENE_DUNGEON1		//던전1 씬
};

struct tagPlayerAttribute3
{
	image* img;
	RECT rc;
	int currentFrameX;
	int currentFrameY;
};

struct tagPlayerInfo2
{
	string name;										//플레이어 이름
	int type;											//플레이어 종류
	int level;											//플레이어 레벨
	int totalStamina;									//플레이어 총내구력
	int currentStamina;									//플레이어 현재내구력
	int nextEXP;										//플레이어 다음레벨업경험치
	int currentEXP;										//플레이어 현재경험치
	int magicalEnergy;									//플레이어 기력 (최대 100)
	int attackPower;									//플레이어 공격력
	int defensePower;									//플레이어 방어력
	int speedPower;										//플레이어 순발력
	int charming;										//플레이어 매력
	int loginNum;										//플레이어 로그인횟수
	int playerStamina;									//플레이어 체력
	int playerStrength;									//플레이어 완력
	int playerHealth;									//플레이어 활력(건강)
	int playerSpeed;									//플레이어 스피드
	int attributeLand;									//플레이어 지속성
	int attributeWater;									//플레이어 수속성
	int attributeFire;									//플레이어 화속성
	int attributeWind;									//플레이어 풍속성
	image* playerFace;									//플레이어 페이스
	int faceCurrentFrameX;								//플레이어 현재 프레임X
	int faceCurrentFrameY;								//플레이어 현재 프레임Y
	tagPlayerAttribute3	_arrayAttributeFire[10];		//화속성 배열
	tagPlayerAttribute3	_arrayAttributeWater[10];		//수속성 배열
	tagPlayerAttribute3	_arrayAttributeLand[10];		//지속성 배열
	tagPlayerAttribute3	_arrayAttributeWind[10];		//풍속성 배열
};

class tileMap : public gameNode
{
protected:
	typedef vector<item*>			vItem;
	typedef vector<item*>::iterator viItem;

protected:
	int _tileMap[TILE_COUNT_X][TILE_COUNT_Y];
	int _isoX, _isoY;				// 현재 타일 인덱스
	int _playerIsoX, _playerIsoY;	// player 타일 인덱스
	int _corner;
	int _palyerCorner;				//플레이어 인덱스 4분면확인
	char str[128];
	int _count;						//framecount 용

	tagTile _tiles[TILE_COUNT_X][TILE_COUNT_Y];

	int _delayClickCount;			//화면 클릭일정시간 지나고 되도록하기위함
	bool _isPosibleClick;			//화면 바뀌었을때 바로 클릭못하도록하기위함

	float _cameraBufferX;				// 카메라이동에 따른 타일 검색 이동용
	float _cameraBufferY;				// 

	RECT _underBarRc;				// 언더바 렉트

	RECT _menuMapRc;				// menu 맵 렉트
	RECT _menuStateRc;				// menu 상태 렉트
	RECT _menuPetRc;				// menu 펫 렉트
	RECT _menuItemRc;				// menu 아이템 렉트
	RECT _menuMailRc;				// menu 메일 렉트
	RECT _menuAlbumRc;				// menu 앨범 렉트
	RECT _menuSystemRc;				// menu 시스템 렉트

	bool _isMenuBarOn;				//메뉴바가 다 올라왔는지 확인용

	float _toolY;					// 툴렉트 좌표값 변수

	bool _isMouseOnToolBar;			//마우스가 툴바에 올라가있는지 확인용
	
	int _pos[2];					//타일 검색용

	int _prePlayerCurrentIsoX;		// 이전 플레이어 인덱스 X
	int _prePlayerCurrentIsoY;		// 이전 플레이어 인덱스 Y
	float _prePlayerCenterX;		// 이전 플레이어 중심좌표 X
	float _prePlayerCenterY;		// 이전 플레이어 중심좌표 Y

	int _currentPlayerX;			// 이동 후 플레이어 인덱스 X
	int _currentPlayerY;			// 이동 후 플레이어 인덱스 Y
	float _currentPlayerCenterX;	// 이동 후 플레이어 중심좌표 X
	float _currentPlayerCenterY;	// 이동 후 플레이어 중심좌표 Y

	int frontPosX;					// 타일검색용 인덱스 
	int frontPosY;					// 타일검색용 인덱스 
	int leftPosX;					// 타일검색용 인덱스 
	int leftPosY;					// 타일검색용 인덱스 
	int rightPosX;					// 타일검색용 인덱스 
	int rightPosY;					// 타일검색용 인덱스 

	int _closeListCount;			//클로즈리스트 사이즈카운트용
	bool _isReSearchAStar;			//리서치 에이스타알고리즘

	player* _player;
	pet* _pet;

	/////////////////////////////////////////////////
	// ##### ### A* 적용 위한 정의 ### #####
	/////////////////////////////////////////////////
	//전체 타일을 담을 벡터
	vector<aStarTile*>				_vTotalList;
	vector<aStarTile*>::iterator	_viTotalList;

	//갈 수 있는 타일을 담을 벡터
	vector<aStarTile*>				_vOpenList;
	vector<aStarTile*>::iterator	_viOpenList;

	//가장 가까운 경로를 담을 벡터
	vector<aStarTile*>				_vCloseList;
	vector<aStarTile*>::iterator	_viCloseList;

	aStarTile* _startTile;
	aStarTile* _endTile;
	aStarTile* _currentTile;

	int _aStarCount;
	bool _isAStarStart;

	int _playerIdX;
	int _playerIdY;
	int _moveIdX;
	int _moveIdY;

	bool _isEndTotalList;   //토탈리스트 사이즈 확인용
	bool _isStartTotalList;

	bool _isDontMoveMent;  //이동할 수 없다고 얘기하셈
	int _mentCount;		   //멘트 뜨는시간 초기화

	//////////////////////////////////////////////////
	//########### 이니데이터 확인용  ################//
	/////////////////////////////////////////////////
	bool _isWriteInidata;		//이니데이타 읽어왔는지 확인용

	bool _isPlayerInfo;			//플레이어 정보 읽기

	/////////////////////////////////////////////////

	bool _isMouseOnBaseLeft;		//마우스를 베이스레프트위에 올려놨는지
	bool _isMouseOnBaseRight;		//마우스를 베이스라이트위에 올려놨는지
	bool _isMouseOnAction;			//마우스를 액션창에 올려놨는지
	bool _isMouseOnState;			//마우스를 상태창에 올려놨는지
	bool _isMouseOnPet;				//마우스를 펫창에 올려놨는지

	////////////////////////////////////////////////
	// ############# 펫 관리를위한 벡터설정 ##########
	////////////////////////////////////////////////
	typedef vector<pet*>			_vPet1;        //플레이어1 펫 저장소
	typedef vector<pet*>::iterator	_viPet1;	   //플레이어1 펫 이터

	typedef vector<pet*>			_vPet2;		   //플레이어2 펫 저장소
	typedef vector<pet*>::iterator  _viPet2;       //플레이어2 펫 이터

	//워프를위한 좌표 확인용
	int searchIsoX[4];
	int searchIsoY[4];

	//npc 서치를위한 좌표확인용
	int searchNPCIsoX[16];
	int searchNPCIsoY[16];

	string _mapName;

	bool _isDungeon;								//현재 던전일경우켜주기


public:
	menuType* _menuType;
	tagPlayerInfo2 _playerInfo;	//플레이어 정보읽어오기
	vItem	_vItem;				// 아이템 벡터
	viItem	_viItem;
	int _npcIsoX;				//npc가 있는지 확인용
	int _npcIsoY;				//

	bool _isAvailableClickNPC;		//NPC클릭이 가능하다
	bool _isClickArmorNPC;			//NPC를 클릭했다면 확인용(판매하는애들)
	bool _isClickWeaponNPC;			//NPC를 클릭했다면 확인용(판매하는애들)

	tileMap();
	~tileMap();

	void InputHandle();

	HRESULT init();
	void release();
	void update();
	void render();
	
	//카메라 움직이게 해주는 함수
	void moveCamera();

	//타일맵을 그려주는 함수
	void drawTileMap();

	//마름모를 그려주는 함수
	void drawRhombus(int left, int top);

	//코너 검출용(1 ~ 4분면)
	int getCornerIndex(int isoX, int isoY);

	//코너안에 들어왔는지 확인용
	bool isInRhombus(int corner, int isoX, int isoY);

	//마우스를 올렸을때 메뉴바 올려주는 함수
	void setMenuBar();
	void updateMenuBar();
	void renderMenuBar();

	//타일위에 마우스 올라간 위치에 select 버튼 나오게하기
	void mouseSelectTile();

	//카메라 세팅
	void setCamera(int isoX, int isoY);

	//지형, 오브젝트 타입 설정
	TERRAIN terrainSelect(int frameX, int frameY);
	TILETYPE tileTypeSelect(int frameX, int frameY);

	//렌더 순서 살짝 바꿔주기(인게임용)
	void renderSwitch();

	//타일 값 세팅
	void setTiles();

	//플레이어 무빙 세팅
	void playerMovePoint(float x, float y);
	void playerMove();
	void playerLastMove();

	//마우스 왼쪽 버튼눌렀을때 활서오하
	void mouseLButton();

	//마우스 오른쪽 버튼눌렀을때 활성화
	void mouseRButton();

	//현재 내가 무슨 타일에 있는지 활성화
	void currentPlayerTile();

	//플레이어 위치 인덱스검출함수
	int getCornerPlayerIndex(int isoX, int isoY);

	//플레이어 인덱스가 코너안에 들어왔는지 확인용
	bool isInPlayerRhombus(int corner, int isoX, int isoY);

	//플레이어 바라보는 방향 앞 인덱스 탐색하기
	void moveTileSearch();
	void clickNPC();

	//파일로드
	void load(string mapName);

	//A*적용을위한 함수
	void initAStar();
	void setAStarTiles();
	vector<aStarTile*> addOpenList(aStarTile* currentTile);
	void pathFinder(aStarTile* currentTile);
	void releaseAStar();
	void updateAStar();
	void renderAStar();
	//여기까지

	//이니데이용 함수
	void writeInidata();

	//장소이동 타일을 검색하기 위한 함수
	void whorfSpotSearch();

	//NPC가 있는 타일을 검색하기 위한 함수
	void NPCSpotSearch();

	//던전일 경우 배틀씬으로 이동시키기위한 함수
	void dungeonToBattle();

	////게터세터들

	RECT getMenuMapRect() { return _menuMapRc; }
	RECT getMenuStateRect() { return _menuStateRc; }
	RECT getMenuPetRect() { return _menuPetRc; }
	RECT getMenuItemRect() { return _menuItemRc; }
	RECT getMenuMailRect() { return _menuMailRc; }
	RECT getMenuAlbumRect() { return _menuAlbumRc; }
	RECT getMenuSystemRect() { return _menuSystemRc; }

	float getCameraBufferX() { return _cameraBufferX; }
	float getCameraBufferY() { return _cameraBufferY; }
	void setCameraBufferX(float cameraBufferX) { _cameraBufferX = cameraBufferX; }
	void setCameraBufferY(float cameraBufferY) { _cameraBufferY = cameraBufferY; }
	tagTile getTile(int i, int j) { return _tiles[i][j]; }

	int getPosFisrt() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }

	void setIsMouseOnBaseLeft(bool isMouseOnBaseLeft) { _isMouseOnBaseLeft = isMouseOnBaseLeft; }
	void setIsMouseOnBaseRight(bool isMouseOnBaseRight) { _isMouseOnBaseRight = isMouseOnBaseRight; }
	void setIsMouseOnAction(bool isMouseOnAction) { _isMouseOnAction = isMouseOnAction; }

	bool getIsMouseOnBaseLeft() { return _isMouseOnBaseLeft; }
	bool getIsMouseOnBaseRight() { return _isMouseOnBaseRight; }
	bool getIsMouseOnAction() { return _isMouseOnAction; }

	void setIsPosibleClick(bool isPosibleClick) { _isPosibleClick = isPosibleClick; }
	bool getIsPosibileClick() {	return _isPosibleClick;	}

	void setDelayClickCount(bool delayClickCount) { _delayClickCount = delayClickCount; }
	int getDelayClickCount() { return _delayClickCount; }

	void setIsPlayerInfo(bool isPlayerInfo) { _isPlayerInfo = isPlayerInfo; }
	bool getIsPlayerInfo() { return _isPlayerInfo; }

	void setIsMouseOnState(bool isMouseOnState) { _isMouseOnState = isMouseOnState; }
	bool getIsMouseOnState() { return _isMouseOnState;	}

	void setIsMouseOnPet(bool isMouseOnPet) { _isMouseOnPet = isMouseOnPet; }
	bool getIsMouseOnPet() { return _isMouseOnPet; }

	void setPlayerImageName(string playerImageName) { _player->_playerImageName = playerImageName; }
	void setPlayerImage(image* playerImage) { _player->_player.img = playerImage; }
	void setPlayerImageMoveX(float playerImageMoveX) { _player->setPlayerImageMoveX(playerImageMoveX); }
	void setPlayerImageMoveY(float playerImageMoveY) { _player->setPlayerImageMoveY(playerImageMoveY); }
	void setPlayerCurrentFrameX(int currentFrameX) { _player->setPlayerCurrentFrameX(currentFrameX); }
	void setPlayerCurrentFrameY(int currentFrameY) { _player->setPlayerCurrentFrameY(currentFrameY); }
	void setPlayerRect(RECT playerRect) { _player->setPlayerRect(playerRect); }
	void setPlayerImageCenterX(float ImageCenterX) { _player->setPlayerImageCenterX(ImageCenterX); }
	void setPlayerImageCenterY(float ImageCenterY) { _player->setPlayerImageCenterY(ImageCenterY); }
	void setPlayerFrameAdjustTime(float frameAdjust) { _player->setPlayerFrameAdjustTime(frameAdjust); }
	void setPlayerState(PLAYERSTATE playerState) { _player->setPlayerState(playerState); }
	void setPlayerActionRun(bool actionRun) { _player->setPlayerActionRun(actionRun); }

	image* getPlayerImage() { return _player->_player.img; }
	float getplayerImageMoveX() { return _player->getPlayerImageMoveX(); }
	float getplayerImageMoveY() { return _player->getPlayerImageMoveY(); }
	float getPlayerCenterX() { return _player->getPlayerCenterX(); }
	float getPlayerCenterY() { return _player->getPlayerCenterY(); }
	int getPlayerCurrentFrameX() { return _player->getPlayerCurrentFrameX(); }
	int getPlayerCurrentFrameY() { return _player->getPlayerCurrentFrameY(); }
	PLAYERSTATE getPlayerState() { return _player->getPlayerState(); }
	bool getPlayerActionRun() { return _player->getPlayerActionRun(); }

	PLAYERCHARACTER getPlayerCharacter() { return _player->_player.playerCharacter; }

	bool getIsPlayerMove() { return _player->getIsPlayerMove(); }

	void setPlayerMemoryAddressLink(player* player) { _player = player; }

	int getCorner() { return _corner; }
	void setCorner(int corner) { _corner = corner; }

	int getIsoX() { return _isoX; }
	void setIsoX(int isoX) { _isoX = isoX; }

	int getIsoY() { return _isoY; }
	void setIsoY(int isoY) { _isoY = isoY; }

	bool getIsWriteInidata() { return _isWriteInidata; }
	void setIsWriteInidata(bool isWriteInidata) { _isWriteInidata = isWriteInidata; }
};

