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
	NPC_AGENT_ONE,						//1��° ������
	NPC_GAURD_ONE,						//ù��° ����
	NPC_GAURD_TWO,						//�ι�° ����
	NPC_AGENT_TWO,						//2��° ������
	NPC_GAURD_THREE,					//����° ����
	NPC_AGENT_THREE,					//3��° ������
	NPC_GAURD_FOUR,						//�׹�° ����
	NPC_VILLAGE_CHIEF,					//���� ����
	NPC_FLOWER_GIRL_LEFT,				//������ �ٶ󺸴� ������ ����
	NPC_FLOWER_GIRL_RIGHT,				//�������� �ٶ󺸴� ������ ����
	NPC_BABY_GIRL,						//�������� ���ھ���
	NPC_AGENT_FOUR,						//4��° ������
	NPC_AGENT_FIVE,						//5��° ������
	NPC_AGENT_SIX,						//6��° ������
	NPC_NURSE_LEFT,						//������ �ٶ󺸴� ��ȣ��
	NPC_WRESTLER_RIGHT,					//�������� �ٶ󺸴� ������
	NPC_WERSTLER_LEFT,					//�������ٶ󺸴� ������
	NPC_BOXER_RIGHT,					//���������ٶ󺸴� ����
	NPC_BOXER_LEFT,						//�������ٶ󺸴� ����
	NPC_OLDMAN_LEFT,					//�������ٶ󺸸� �ɾ��ִ� ����
	NPC_ORANGE_GIRL_LEFT,				//�������ٶ󺸰� �ִ� �������Ӹ� �ҳ�
	NPC_ORANGE_GIRL_RIGHT,				//���������ٶ󺸰� �ִ� �������Ӹ� �ҳ�
	NPC_DOCTOR_LEFT,					//�������ٶ󺸰��ִ� �ǻ�
	NPC_BUTCHER_RIGHT,					//���������ٶ󺸰��ִ� ������
	NPC_BOY_RIGHT,						//���������ٶ󺸰��ִ� �ҳ�
	NPC_BUTCHER_LEFT,					//������ �ٶ󺸰��ִ� ������
	NPC_KUNGFU_BOY,						//�������ٶ󺸰��ִ� ��Ǫ����
	NPC_VEGRA_OLDMAN,					//������ Ű��Ŵ� �Ҿƹ���
	NPC_AXEMAN_RIGHT,					//���������ٶ󺸰��ִ� ��������
	NPC_AXEMAN_LEFT,					//������ �ٶ󺸰��ִ� ��������
	NPC_BOY_LEFT,						//�������ٶ󺸸� ������� �ҳ�
	NPC_BROWN_BOY,						//���������ٶ󺸴� �����Ӹ��ҳ�
	NPC_MAN1_DOWN,
	NPC_WOMEN1_DOWN,
	NPC_MAN2_DOWN,
	NPC_MAN3_DOWN,
	NPC_MAN4_DOWN,
	NPC_GIRL1_DOWN,
	NPC_GIRL2_DOWN,
	NPC_FLOWER_OGRNGE_GIRL_LEFT,		//�������ٶ󺸸� ������ �������Ӹ� �ҳ�
	NPC_GIRL3_DOWN,
	NPC_GIRL4_DOWN,
	NPC_LOTTO_SALESWOMEN_LEFT,			//�����Ǹſ� (���ʹٶ�)
	NPC_WOMEN2_DOWN,
	NPC_BLUE_NURSE_RIGHT,				//���������ٶ󺸴� �Ķ���ȣ��
	NPC_DUCK_GIRL_LEFT,					//�������ٶ󺸴� �������� �ҳ�
	NPC_NURSE_RIGHT,					//�������� �ٶ󺸴� ��ȣ��
	NPC_OLDMAN_RIGHT,					//�������� �ٶ󺸸� �ɾ��ִ� ����
	NPC_ARMOR_SALESMAN,					//���Ǹſ�
	NPC_BUNNY_GIRL_RIGHT,				//��⸦��ٴϰ� (�����ʹٶ�)
	NPC_WHITE_GIRL_RIGHT,				//�簥���Ӹ� �ҳ� (������)
	NPC_SYRINGE_NURSE_RIGHT,			//�ֻ�⸦�� ��ȣ��(������)
	NPC_BUNNY_GIRL_LEFT,				//�������ٶ󺸴� �ٴϰ�
	NPC_LOTTO_SALESWOMEN_RIGHT,			//�ζ��Ǹſ� (������)
	NPC_MAN5_RIGHT,
	NPC_WEAPON_SALESMAN					//���� �Ǹſ�
};

//�÷��̾� ���������Ҷ� �ʿ��� enum��
enum characterInfo
{
	INFO_YES = 1,
	INFO_NO,
	INFO_RED,
	INFO_BLUE
};

//�����Ҷ� �ʿ��� enum��
enum CTRL
{
	CTRL_SAVE,				//���̺�			��ư
	CTRL_LOAD,				//�ε�			��ư
	CTRL_TERRAINDRAW,		//����			�׸���
	CTRL_OBJECTDRAW,		//������			�׸���
	CTRL_DISPLAYDRAW,		//����ǰ			�׸���
	CTRL_FENCEDRAW,			//�潺			�׸���
	CTRL_GATEDRAW,			//�빮			�׸���
	CTRL_PLANTSDRAW,		//�Ĺ�			�׸���
	CTRL_ROCKDRAW,			//����			�׸���
	CTRL_STRUCTUREDRAW,		//�ǹ�			�׸���
	CTRL_WALLBASICDRAW,		//�Ϲݺ�			�׸���
	CTRL_WALLDUNGEONDRAW,	//������			�׸���
	CTRL_NPCDRAW,			//NPC			�׸���
	CTRL_ERASER,			//���찳			��ư
	CTRL_TILETYPEDRAW,		//Ÿ��Ÿ��(�̵�����, �Ұ���, ���� ��) ����
	CTRL_END				//�ƹ��������� �̰�
};

//����ο�
enum DIRECTION
{
	DIR_SIX,				//6��		����
	DIR_SEVEN,				//7��		����
	DIR_NINE,				//9��		����
	DIR_ELEVEN,				//11��		����
	DIR_TWELVE,				//12��		����
	DIR_ONE,				//1��		����
	DIR_THREE,				//3��		����
	DIR_FIVE				//5��		����	
};

enum CATEGORY
{
	CATEGORY_TILE,			//Ÿ�� ī�װ�
	CATEGORY_STRUCTURE,		//���๰ ī�װ�
	CATEGORY_OBJECT,		//������ ī�װ�
	CATEGORY_NPC,			//NPC ī�װ�
	CATEGORY_EMPTY			//ī�װ� ������
};

enum PLAYERWEAPON
{
	WEAPON_NONE,		//������
	WEAPON_CLUB,		//Ŭ������
	WEAPON_HATCHAT		//��������
};

enum PLAYERCHARACTER
{
	RED,		//���� ����
	BLUE		//��� �糪��
};

enum PETNAME
{
	DURI,			//�θ�
	SPOTTEDURI,		//���츮
	URI,			//�츮
	MAMONAS,		//���𳪽�
	MANMO,			//����
	MANMOR,			//����
	MOGAROS,		//�𰡷ν�
	OGAROS,			//�����ν�
	GORGOR,			//����
	VERGA,			//������
	VERURU,			//�����
	BANBORO,		//�ݺ���
	BANGINO,		//�ݱ��
	BURDON,			//�θ���
	RIBINO,			//�����
	YANGIRO,		//����
	NORNOR,			//�븣�븣
	GOLROS			//��ν�
};

enum PETSKILL
{
	PET_SKILL_NONE,			//��ų ����
	PET_SKILL_ATTACK,		//��Ʈ ����
	PET_SKILL_DEFENSE		//��Ʈ ���
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	gameNode();
	virtual ~gameNode();

	int _ctrSelect;	//���콺Ŭ��������

	//HRESULT ���� ���� ��ȯ�����ε�
	//S_OK, E_FAIL, SUCCEDED
	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� �Լ�
	virtual void render();	//�׸��� �Լ�

	image* getBackBuffer() { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

