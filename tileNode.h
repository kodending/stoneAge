#pragma once

#define CELL_WIDTH 64  //타일의 가로크기
#define CELL_HEIGHT 47 //타일의 세로크기

#define RADIUS_WIDTH	CELL_WIDTH / 2		//타일의 반지름(길이)
#define RADIUS_HEIGHT	CELL_HEIGHT / 2		//타일의 반지름(높이)

#define TILE_COUNT_X 80 // 타일 갯수
#define TILE_COUNT_Y 80

#define INIT_X (TILE_COUNT_X * CELL_WIDTH) / 4			//초기 좌표
#define INIT_Y -((TILE_COUNT_Y * CELL_HEIGHT) / 4)		//초기 좌표

#define SAMPLETILEX 14
#define SAMPLETILEY 21

/////////////////////////////////////////////////////////
// ## CTRL, DIRECTION 정리는 gameNode.h에 ! ####
////////////////////////////////////////////////////////

//지형
enum TERRAIN
{
	TR_DESERT,			//사막     
	TR_GRASS,			//풀
	TR_DIRT,			//흙
	TR_LAVAREGION,		//용암지대
	TR_LAVA,			//용암
	TR_WATER,			//물	
	TR_UNMOVE,			//못움직이는곳
	TR_WHORF,			//워프하는곳
	TR_EMPTY			//없음
};

//지형 속성부여
enum TERRAINATTRIBUTE
{
	ATTR_MOVE,				//움직임 가능
	ATTR_UNMOVE,			//못움직이는 타일
	ATTR_WHORF_ITEMSHOP,	//아이템샵 이동
	ATTR_WHORF_PETSHOP,		//펫샵 이동
	ATTR_WHORF_CHIEF,		//촌장집 이동
	ATTR_WHORF_DUNGEON1,	//던전1층 이동
	ATTR_WHORF_DUNGEON2,	//던전2층 이동
	ATTR_WHORF_DUNGEON3,	//던전3층 이동
	ATTR_WHORF_DUNGEON4		//던전4층 이동
};

//오브젝트(구조물)
enum OBJECT
{
	OBJ_WALL_BASIC,			//벽	(마을)	오브젝트
	OBJ_WALL_DUNGEON,		//벽	(던전)	오브젝트
	OBJ_DISPLAY,			//전시대		오브젝트
	OBJ_FENCE,				//울타리		오브젝트
	OBJ_GATE,				//문			오브젝트
	OBJ_NPC,				//npc		오브젝트
	OBJ_OBJECT,				//구조물		오브젝트
	OBJ_PLANTS,				//식물		오브젝트
	OBJ_ROCK,				//바위		오브젝트
	OBJ_STRUCTURE,			//건물		오브젝트
	OBJ_NONE				//없음
};

//이동가능한지 불가능한지 타일 결정
enum TILETYPE
{
	TYPE_MOVE,				//이동가능 타일
	TYPE_UNMOVE,			//이동불가능 타일
	TYPE_WHORF_CHIEF,		//촌장집 워프 타일
	TYPE_WHORF_ITEMSHOP,	//아이템 샵 워프 타일
	TYPE_WHORF_PETSHOP,		//펫샵 워프 타일
	TYPE_WHORF_HOSPITAL,	//병원 워프 타일
	TYPE_WHORF_DUNGEON1,	//던전1 워프 타일
	TYPE_WHORF_DUNGEON2,	//던전2 워프 타일
	TYPE_WHORF_DUNGEON3,	//던전3 워프 타일
	TYPE_WHORF_DUNGEON4,	//던전4 워프 타일
	TYPE_WHORF_VILLAGE		//마을 워프 타일
};

//타일 정보를 담을 구조체
struct tagTile
{
	TERRAIN terrain;
	TERRAINATTRIBUTE terrainAttribute;
	TILETYPE tileType;
	OBJECT obj;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
	int tileTypeFrameX;
	int tileTypeFrameY;
	float left;
	float top;
	float centerX;
	float centerY;
	bool objRendered; //이미렌더된것인지 확인용
	bool isPlayer;	  //플레이어가 있는지 확인용
	bool isMovePoint; //이동지점을 찍었는지 확인용
	bool isPrePlayer; //플레이어가 이전에 있었단 타일 확인용
};

//타일셋 정보를 담을 구조체
struct tagSampleTile
{
	image* img;
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};


//현재 타일을 받아올 구조체
struct tagCurrentTile
{
	image* img;
	int x;
	int y;
};

//오브젝트셋 정보를 담을 구조체


//현재 팝업창 띄어줄 구조체
struct tagPopUp
{
	image* img;
	RECT PopUpRc;
	RECT leftButtonRc;
	RECT upButtonRc;
	RECT rightButtonRc;
	RECT downButtonRc;
	RECT exitButtonRc;
};
