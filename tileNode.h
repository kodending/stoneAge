#pragma once

#define CELL_WIDTH 64  //Ÿ���� ����ũ��
#define CELL_HEIGHT 47 //Ÿ���� ����ũ��

#define RADIUS_WIDTH	CELL_WIDTH / 2		//Ÿ���� ������(����)
#define RADIUS_HEIGHT	CELL_HEIGHT / 2		//Ÿ���� ������(����)

#define TILE_COUNT_X 80 // Ÿ�� ����
#define TILE_COUNT_Y 80

#define INIT_X (TILE_COUNT_X * CELL_WIDTH) / 4			//�ʱ� ��ǥ
#define INIT_Y -((TILE_COUNT_Y * CELL_HEIGHT) / 4)		//�ʱ� ��ǥ

#define SAMPLETILEX 14
#define SAMPLETILEY 21

/////////////////////////////////////////////////////////
// ## CTRL, DIRECTION ������ gameNode.h�� ! ####
////////////////////////////////////////////////////////

//����
enum TERRAIN
{
	TR_DESERT,			//�縷     
	TR_GRASS,			//Ǯ
	TR_DIRT,			//��
	TR_LAVAREGION,		//�������
	TR_LAVA,			//���
	TR_WATER,			//��	
	TR_UNMOVE,			//�������̴°�
	TR_WHORF,			//�����ϴ°�
	TR_EMPTY			//����
};

//���� �Ӽ��ο�
enum TERRAINATTRIBUTE
{
	ATTR_MOVE,				//������ ����
	ATTR_UNMOVE,			//�������̴� Ÿ��
	ATTR_WHORF_ITEMSHOP,	//�����ۼ� �̵�
	ATTR_WHORF_PETSHOP,		//�꼥 �̵�
	ATTR_WHORF_CHIEF,		//������ �̵�
	ATTR_WHORF_DUNGEON1,	//����1�� �̵�
	ATTR_WHORF_DUNGEON2,	//����2�� �̵�
	ATTR_WHORF_DUNGEON3,	//����3�� �̵�
	ATTR_WHORF_DUNGEON4		//����4�� �̵�
};

//������Ʈ(������)
enum OBJECT
{
	OBJ_WALL_BASIC,			//��	(����)	������Ʈ
	OBJ_WALL_DUNGEON,		//��	(����)	������Ʈ
	OBJ_DISPLAY,			//���ô�		������Ʈ
	OBJ_FENCE,				//��Ÿ��		������Ʈ
	OBJ_GATE,				//��			������Ʈ
	OBJ_NPC,				//npc		������Ʈ
	OBJ_OBJECT,				//������		������Ʈ
	OBJ_PLANTS,				//�Ĺ�		������Ʈ
	OBJ_ROCK,				//����		������Ʈ
	OBJ_STRUCTURE,			//�ǹ�		������Ʈ
	OBJ_NONE				//����
};

//�̵��������� �Ұ������� Ÿ�� ����
enum TILETYPE
{
	TYPE_MOVE,				//�̵����� Ÿ��
	TYPE_UNMOVE,			//�̵��Ұ��� Ÿ��
	TYPE_WHORF_CHIEF,		//������ ���� Ÿ��
	TYPE_WHORF_ITEMSHOP,	//������ �� ���� Ÿ��
	TYPE_WHORF_PETSHOP,		//�꼥 ���� Ÿ��
	TYPE_WHORF_HOSPITAL,	//���� ���� Ÿ��
	TYPE_WHORF_DUNGEON1,	//����1 ���� Ÿ��
	TYPE_WHORF_DUNGEON2,	//����2 ���� Ÿ��
	TYPE_WHORF_DUNGEON3,	//����3 ���� Ÿ��
	TYPE_WHORF_DUNGEON4,	//����4 ���� Ÿ��
	TYPE_WHORF_VILLAGE		//���� ���� Ÿ��
};

//Ÿ�� ������ ���� ����ü
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
	bool objRendered; //�̷̹����Ȱ����� Ȯ�ο�
	bool isPlayer;	  //�÷��̾ �ִ��� Ȯ�ο�
	bool isMovePoint; //�̵������� ������� Ȯ�ο�
	bool isPrePlayer; //�÷��̾ ������ �־��� Ÿ�� Ȯ�ο�
};

//Ÿ�ϼ� ������ ���� ����ü
struct tagSampleTile
{
	image* img;
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};


//���� Ÿ���� �޾ƿ� ����ü
struct tagCurrentTile
{
	image* img;
	int x;
	int y;
};

//������Ʈ�� ������ ���� ����ü


//���� �˾�â ����� ����ü
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
