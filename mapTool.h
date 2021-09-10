#pragma once
#include "tileNode.h"
#include "gameNode.h"
#include "toolType.h"
#include <vector>

struct tagToolType
{
	image* img;
	RECT rc;
	int currentFrameX;
	int currentFrameY;
};

struct tagLeftButton
{
	image* img;
	RECT rc;
	int currentFrameX;
	int currentFrameY;
};

struct tagRightButton
{
	image* img;
	RECT rc;
	int currentFrameX;
	int currentFrameY;
};

struct tagSaveInput
{
	image* img;
	RECT saveRect;
	RECT saveButtonRect;
	RECT cancelButtonRect;
	RECT textInputRect;
	bool isSaveButton;
};

class mapTool : public gameNode
{
private:
	int _tileMap[TILE_COUNT_X][TILE_COUNT_Y];
	int _isoX, _isoY;				// 현재 타일 인덱스
	int _saveIsoX, _saveIsoY;		// 저장할 타일 인덱스
	int _corner;
	char str[128];
	int _count;						//framecount 용
	int _instantCnt;				//임시용카운트

	tagTile _tiles[TILE_COUNT_X][TILE_COUNT_Y];

	int _cameraBufferX;				// 카메라이동에 따른 타일 검색 이동용
	int _cameraBufferY;				// 

	float _moveX;					// 위와 상동
	float _moveY;

	RECT _underBarRc;				// 언더바 렉트

	RECT _tileRc;					// tool 타일 렉트
	RECT _structureRc;				// tool 건축물 렉트
	RECT _objectRc;					// tool 구조물 렉트
	RECT _NPCRc;					// tool NPC 렉트
	RECT _eraserRc;					// tool 지우개 렉트
	RECT _saveRc;					// tool 저장 렉트
	RECT _loadRc;					// tool 불러오기 렉트
	RECT _exitRc;					// tool 나가기 렉트

	float _toolY;					// 툴렉트 좌표값 변수

	bool _isMouseOnToolBar;			//마우스가 툴바에 올라가있는지 확인용
	bool _isClickTile;				//타일을 선택했는지 확인
	bool _isExitButton;				//팝업창 exit 버튼눌렀는지 확인용

	bool _isToolTile;				//현재 tooltile에 있는지
	bool _isToolStructure;			//현재 toolstructure에 있는지
	bool _isToolObject;				//현재 toolObject에있는지
	bool _isToolFence;				//현재 toolfence에 있는지
	bool _isToolGate;				//현재 toolgate에 있는지
	bool _isToolDisplay;			//현재 tooldisplay에 있는지
	bool _isToolPlants;				//현재 toolPlants에 있는지
	bool _isToolRock;				//현재 toolRock에 있는지 
	bool _isToolWallBasic;			//현재 toolWallBasic에 있는지
	bool _isToolWallDungeon;		//현재 toolWallDungeon에 있는지
	bool _isToolNpc;				//현재 toolNpc에 있는지
	bool _isToolEraser;				//현재 toolEraser에 있는지
	bool _isToolTileType;			//현재 toolTypeTile에 있는지
	bool _isToolSaveInput;			//현재 toolSaveInput에 있는지

	string _dialog;					//입력창에 글씨를 받기위한 스트링변수
	string name;					//입력창에 최종저장하기위한 변수

public:
	toolType* _toolType;
	tagSampleTile	_sampleTile;	// 타일 샘플
	tagCurrentTile	_currentTile;	//현재 선택한 타일
	tagPopUp		_popUp;			//팝업창
	tagToolType		_toolName;		//툴타입 명칭 선언
	tagLeftButton	_leftButton;	//왼쪽버튼
	tagRightButton	_rightButton;	//오른쪽버튼
	tagSaveInput	_saveInput;		//세이브인풋 창 띄우기
	
	mapTool();
	~mapTool();

	void InputHandle();

	HRESULT init();
	void release();
	void update();
	void render();
	void moveCamera();

	//타일맵 그려주는 함수
	void drawTileMap();
	//마름모 그려주는 함수
	void drawRhombus(int left, int top);
	//코너 검출(1 ~ 4분면)
	int getCornerIndex(int isoX, int isoY);
	//코너안에 왔는지 검출하는 함수
	bool isInRhombus(int corner, int isoX, int isoY);
	//마우스 올렸을때 툴바 올리는 함수
	void setToolBar();
	void updateToolBar();
	void renderToolBar();

	//내가 현재 선택한 현재 타일 정보를 저장하기위한 함수
	void selectCurrentTile();

	//타일위에 마우스 올라간 위치에 select 버튼 나오게하기
	void mouseSelectTile();

	//지형, 오브젝트 타입 설정
	TERRAIN terrainSelect(int frameX, int frameY);
	TILETYPE tileTypeSelect(int frameX, int frameY);

	//CTRL 구분하여 설정하기
	void devideCTRL(int isoX, int isoY);

	//상태에 따른 CTRL 구분하기
	void updateCtrSelect();

	//버튼 1들어왔을때 시간주고 바꿔주기
	void buttonFrame();

	//save, load 구현하기
	void saveMap();
	void loadMap();

	//렌더 순서 살짝 바꿔주기(인게임용)
	void renderSwitch();

	//오브젝트 렌더해주기(맵툴용)
	void objectRender();

	//문자입력 함수만들기
	void dialogSet();
	void dialogInput();
	void renderDialog();

	//렉트 게터설정
	RECT getUnderBarRc() { return _underBarRc; }
	RECT getTileRc() { return _tileRc; }
	RECT getStructureRc() { return _structureRc; }
	RECT getObjectRc() { return _objectRc;	}
	RECT getNpcRc() { return _NPCRc; }
	RECT getEraserRc() { return _eraserRc; }
	RECT getSaveRc() { return _saveRc; }
	
	//네임사이즈 게터
	int getNameSize() { return name.size(); }
	void setName(string Name) { name = Name; }
	string getName() { return name; }

	float getCameraBufferX() { return _cameraBufferX; }
	float getCameraBufferY() { return _cameraBufferY; }

	void setIsExitButton(bool isExitButton) { _isExitButton = isExitButton; }
	void setIsToolTile(bool isToolTile) { _isToolTile = isToolTile; }
	void setIsToolStructure(bool isToolStructure) { _isToolStructure = isToolStructure; }
	void setIsToolObject(bool isToolObject) { _isToolObject = isToolObject; }
	void setIsToolFence(bool isToolFence) { _isToolFence = isToolFence; }
	void setIsToolGate(bool isToolGate) { _isToolGate = isToolGate; }
	void setIsToolDisplay(bool isToolDisplay) { _isToolDisplay = isToolDisplay; }
	void setIsToolPlants(bool isToolPlants) { _isToolPlants = isToolPlants; }
	void setIsToolRock(bool isToolRock) { _isToolRock = isToolRock; }
	void setIsToolWallBasic(bool isToolWallBasic) { _isToolWallBasic = isToolWallBasic; }
	void setIsToolWallDungeon(bool isToolWallDungeon) { _isToolWallDungeon = isToolWallDungeon; }
	void setIsToolNpc(bool isToolNpc) { _isToolNpc = isToolNpc; }
	void setIsToolEraser(bool isToolEraser) { _isToolEraser = isToolEraser; }
	void setIsToolTileType(bool isToolTileType) { _isToolTileType = isToolTileType; }
	void setIsSaveInput(bool isToolSaveInput) { _isToolSaveInput = isToolSaveInput; }
};

