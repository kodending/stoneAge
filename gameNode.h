#pragma once
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", BACKGROUNDX, BACKGROUNDY);

enum ITEMNAME
{
	ITEM_NONE,
	ITEM_POTION,
	ITEM_LOTTO,
	ITEM_GORGOR_RIDE_BOOK,
	ITEM_VERGA_RIDE_BOOK,
	ITEM_SEA_SPEAR,
	ITEM_TREE_SPEAR,
	ITEM_GOLD_HATCHAT,
	ITEM_MABURI_HATCHAT,
	ITEM_SANTA_CLUB,
	ITEM_FISH_CLUB,
	ITEM_SEA_ARMOR,
	ITEM_ANCIENT_ARMOR,
	ITEM_DORDOR_ARMOR,
	ITEM_HESTIA_HELMET,
	ITEM_MABURI_HELMET,
	ITEM_SEA_HELMET
};

enum NPCTYPE
{
	NPC_AGENT_ONE,						//1번째 정보원
	NPC_GAURD_ONE,						//첫번째 보초
	NPC_GAURD_TWO,						//두번째 보초
	NPC_AGENT_TWO,						//2번째 정보원
	NPC_GAURD_THREE,					//세번째 보초
	NPC_AGENT_THREE,					//3번째 정보원
	NPC_GAURD_FOUR,						//네번째 보초
	NPC_VILLAGE_CHIEF,					//마을 촌장
	NPC_FLOWER_GIRL_LEFT,				//왼쪽을 바라보는 꽃을든 아이
	NPC_FLOWER_GIRL_RIGHT,				//오른쪽을 바라보는 꽃을든 아이
	NPC_BABY_GIRL,						//물통을든 여자아이
	NPC_AGENT_FOUR,						//4번째 정보원
	NPC_AGENT_FIVE,						//5번째 정보원
	NPC_AGENT_SIX,						//6번째 정보원
	NPC_NURSE_LEFT,						//왼쪽을 바라보는 간호사
	NPC_WRESTLER_RIGHT,					//오른쪽을 바라보는 레슬러
	NPC_WERSTLER_LEFT,					//왼쪽을바라보는 레슬러
	NPC_BOXER_RIGHT,					//오른족을바라보는 복서
	NPC_BOXER_LEFT,						//왼쪽을바라보는 복서
	NPC_OLDMAN_LEFT,					//왼쪽을바라보며 앉아있는 노인
	NPC_ORANGE_GIRL_LEFT,				//왼쪽을바라보고 있는 오렌지머리 소녀
	NPC_ORANGE_GIRL_RIGHT,				//오른쪽을바라보고 있는 오렌지머리 소녀
	NPC_DOCTOR_LEFT,					//왼쪽을바라보고있는 의사
	NPC_BUTCHER_RIGHT,					//오른쪽을바라보고있는 정육사
	NPC_BOY_RIGHT,						//오른쪽을바라보고있는 소년
	NPC_BUTCHER_LEFT,					//왼쪽을 바라보고있는 정육사
	NPC_KUNGFU_BOY,						//왼쪽을바라보고있는 쿵푸보이
	NPC_VEGRA_OLDMAN,					//베르가 키우신느 할아버지
	NPC_AXEMAN_RIGHT,					//오른쪽을바라보고있는 도끼전사
	NPC_AXEMAN_LEFT,					//왼쪽을 바라보고있는 도끼전사
	NPC_BOY_LEFT,						//왼쪽을바라보며 고민중인 소년
	NPC_BROWN_BOY,						//오른쪽을바라보는 갈색머리소년
	NPC_MAN1_DOWN,
	NPC_WOMEN1_DOWN,
	NPC_MAN2_DOWN,
	NPC_MAN3_DOWN,
	NPC_MAN4_DOWN,
	NPC_GIRL1_DOWN,
	NPC_GIRL2_DOWN,
	NPC_FLOWER_OGRNGE_GIRL_LEFT,		//왼쪽을바라보며 꽃을든 오렌지머리 소녀
	NPC_GIRL3_DOWN,
	NPC_GIRL4_DOWN,
	NPC_LOTTO_SALESWOMEN_LEFT,			//복권판매원 (왼쪽바라봄)
	NPC_WOMEN2_DOWN,
	NPC_BLUE_NURSE_RIGHT,				//오른쪽을바라보는 파란간호사
	NPC_DUCK_GIRL_LEFT,					//왼쪽을바라보는 오리를든 소녀
	NPC_NURSE_RIGHT,					//오른쪽을 바라보는 간호사
	NPC_OLDMAN_RIGHT,					//오른쪽을 바라보며 앉아있는 노인
	NPC_ARMOR_SALESMAN,					//방어구판매원
	NPC_BUNNY_GIRL_RIGHT,				//고기를든바니걸 (오른쪽바라봄)
	NPC_WHITE_GIRL_RIGHT,				//양갈래머리 소녀 (오른쪽)
	NPC_SYRINGE_NURSE_RIGHT,			//주사기를든 간호사(오른쪽)
	NPC_BUNNY_GIRL_LEFT,				//왼쪽을바라보는 바니걸
	NPC_LOTTO_SALESWOMEN_RIGHT,			//로또판매원 (오른쪽)
	NPC_MAN5_RIGHT,
	NPC_WEAPON_SALESMAN					//무기 판매원
};

//플레이어 정보저장할때 필요한 enum문
enum characterInfo
{
	INFO_YES = 1,
	INFO_NO,
	INFO_RED,
	INFO_BLUE
};

//맵툴할때 필요한 enum문
enum CTRL
{
	CTRL_SAVE,				//세이브			버튼
	CTRL_LOAD,				//로드			버튼
	CTRL_TERRAINDRAW,		//지형			그리기
	CTRL_OBJECTDRAW,		//구조물			그리기
	CTRL_DISPLAYDRAW,		//전시품			그리기
	CTRL_FENCEDRAW,			//펜스			그리기
	CTRL_GATEDRAW,			//대문			그리기
	CTRL_PLANTSDRAW,		//식물			그리기
	CTRL_ROCKDRAW,			//바위			그리기
	CTRL_STRUCTUREDRAW,		//건물			그리기
	CTRL_WALLBASICDRAW,		//일반벽			그리기
	CTRL_WALLDUNGEONDRAW,	//던전벽			그리기
	CTRL_NPCDRAW,			//NPC			그리기
	CTRL_ERASER,			//지우개			버튼
	CTRL_TILETYPEDRAW,		//타일타입(이동가능, 불가능, 워프 등) 설정
	CTRL_END				//아무반응없는 이곳
};

//방향부여
enum DIRECTION
{
	DIR_SIX,				//6시		방향
	DIR_SEVEN,				//7시		방향
	DIR_NINE,				//9시		방향
	DIR_ELEVEN,				//11시		방향
	DIR_TWELVE,				//12시		방향
	DIR_ONE,				//1시		방향
	DIR_THREE,				//3시		방향
	DIR_FIVE				//5시		방향	
};

enum CATEGORY
{
	CATEGORY_TILE,			//타일 카테고리
	CATEGORY_STRUCTURE,		//건축물 카테고리
	CATEGORY_OBJECT,		//구조물 카테고리
	CATEGORY_NPC,			//NPC 카테고리
	CATEGORY_EMPTY			//카테고리 없을때
};

enum PLAYERWEAPON
{
	WEAPON_NONE,		//장비없음
	WEAPON_CLUB,		//클럽착용
	WEAPON_HATCHAT		//도끼착용
};

enum PLAYERCHARACTER
{
	RED,		//레드 꼬마
	BLUE		//블루 사나이
};

enum PETNAME
{
	DURI,			//두리
	SPOTTEDURI,		//얼룩우리
	URI,			//우리
	MAMONAS,		//마모나스
	MANMO,			//만모
	MANMOR,			//만모르
	MOGAROS,		//모가로스
	OGAROS,			//오가로스
	GORGOR,			//고르고르
	VERGA,			//베르가
	VERURU,			//베루루
	BANBORO,		//반보로
	BANGINO,		//반기노
	BURDON,			//부르돈
	RIBINO,			//리비노
	YANGIRO,		//얀기로
	NORNOR,			//노르노르
	GOLROS			//골로스
};

enum PETSKILL
{
	PET_SKILL_NONE,			//스킬 없음
	PET_SKILL_ATTACK,		//페트 공격
	PET_SKILL_DEFENSE		//페트 방어
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	gameNode();
	virtual ~gameNode();

	int _ctrSelect;	//마우스클릭했을때

	//HRESULT 마소 전용 반환형식인데
	//S_OK, E_FAIL, SUCCEDED
	virtual HRESULT init();			//초기화 함수
	virtual HRESULT init(bool managerInit);
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 함수
	virtual void render();	//그리기 함수

	image* getBackBuffer() { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

