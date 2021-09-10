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
	SCENE_VILLAGE,		//���� ��
	SCENE_DUNGEON1		//����1 ��
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
	string name;										//�÷��̾� �̸�
	int type;											//�÷��̾� ����
	int level;											//�÷��̾� ����
	int totalStamina;									//�÷��̾� �ѳ�����
	int currentStamina;									//�÷��̾� ���系����
	int nextEXP;										//�÷��̾� ��������������ġ
	int currentEXP;										//�÷��̾� �������ġ
	int magicalEnergy;									//�÷��̾� ��� (�ִ� 100)
	int attackPower;									//�÷��̾� ���ݷ�
	int defensePower;									//�÷��̾� ����
	int speedPower;										//�÷��̾� ���߷�
	int charming;										//�÷��̾� �ŷ�
	int loginNum;										//�÷��̾� �α���Ƚ��
	int playerStamina;									//�÷��̾� ü��
	int playerStrength;									//�÷��̾� �Ϸ�
	int playerHealth;									//�÷��̾� Ȱ��(�ǰ�)
	int playerSpeed;									//�÷��̾� ���ǵ�
	int attributeLand;									//�÷��̾� ���Ӽ�
	int attributeWater;									//�÷��̾� ���Ӽ�
	int attributeFire;									//�÷��̾� ȭ�Ӽ�
	int attributeWind;									//�÷��̾� ǳ�Ӽ�
	image* playerFace;									//�÷��̾� ���̽�
	int faceCurrentFrameX;								//�÷��̾� ���� ������X
	int faceCurrentFrameY;								//�÷��̾� ���� ������Y
	tagPlayerAttribute3	_arrayAttributeFire[10];		//ȭ�Ӽ� �迭
	tagPlayerAttribute3	_arrayAttributeWater[10];		//���Ӽ� �迭
	tagPlayerAttribute3	_arrayAttributeLand[10];		//���Ӽ� �迭
	tagPlayerAttribute3	_arrayAttributeWind[10];		//ǳ�Ӽ� �迭
};

class tileMap : public gameNode
{
protected:
	typedef vector<item*>			vItem;
	typedef vector<item*>::iterator viItem;

protected:
	int _tileMap[TILE_COUNT_X][TILE_COUNT_Y];
	int _isoX, _isoY;				// ���� Ÿ�� �ε���
	int _playerIsoX, _playerIsoY;	// player Ÿ�� �ε���
	int _corner;
	int _palyerCorner;				//�÷��̾� �ε��� 4�и�Ȯ��
	char str[128];
	int _count;						//framecount ��

	tagTile _tiles[TILE_COUNT_X][TILE_COUNT_Y];

	int _delayClickCount;			//ȭ�� Ŭ�������ð� ������ �ǵ����ϱ�����
	bool _isPosibleClick;			//ȭ�� �ٲ������ �ٷ� Ŭ�����ϵ����ϱ�����

	float _cameraBufferX;				// ī�޶��̵��� ���� Ÿ�� �˻� �̵���
	float _cameraBufferY;				// 

	RECT _underBarRc;				// ����� ��Ʈ

	RECT _menuMapRc;				// menu �� ��Ʈ
	RECT _menuStateRc;				// menu ���� ��Ʈ
	RECT _menuPetRc;				// menu �� ��Ʈ
	RECT _menuItemRc;				// menu ������ ��Ʈ
	RECT _menuMailRc;				// menu ���� ��Ʈ
	RECT _menuAlbumRc;				// menu �ٹ� ��Ʈ
	RECT _menuSystemRc;				// menu �ý��� ��Ʈ

	bool _isMenuBarOn;				//�޴��ٰ� �� �ö�Դ��� Ȯ�ο�

	float _toolY;					// ����Ʈ ��ǥ�� ����

	bool _isMouseOnToolBar;			//���콺�� ���ٿ� �ö��ִ��� Ȯ�ο�
	
	int _pos[2];					//Ÿ�� �˻���

	int _prePlayerCurrentIsoX;		// ���� �÷��̾� �ε��� X
	int _prePlayerCurrentIsoY;		// ���� �÷��̾� �ε��� Y
	float _prePlayerCenterX;		// ���� �÷��̾� �߽���ǥ X
	float _prePlayerCenterY;		// ���� �÷��̾� �߽���ǥ Y

	int _currentPlayerX;			// �̵� �� �÷��̾� �ε��� X
	int _currentPlayerY;			// �̵� �� �÷��̾� �ε��� Y
	float _currentPlayerCenterX;	// �̵� �� �÷��̾� �߽���ǥ X
	float _currentPlayerCenterY;	// �̵� �� �÷��̾� �߽���ǥ Y

	int frontPosX;					// Ÿ�ϰ˻��� �ε��� 
	int frontPosY;					// Ÿ�ϰ˻��� �ε��� 
	int leftPosX;					// Ÿ�ϰ˻��� �ε��� 
	int leftPosY;					// Ÿ�ϰ˻��� �ε��� 
	int rightPosX;					// Ÿ�ϰ˻��� �ε��� 
	int rightPosY;					// Ÿ�ϰ˻��� �ε��� 

	int _closeListCount;			//Ŭ�����Ʈ ������ī��Ʈ��
	bool _isReSearchAStar;			//����ġ ���̽�Ÿ�˰���

	player* _player;
	pet* _pet;

	/////////////////////////////////////////////////
	// ##### ### A* ���� ���� ���� ### #####
	/////////////////////////////////////////////////
	//��ü Ÿ���� ���� ����
	vector<aStarTile*>				_vTotalList;
	vector<aStarTile*>::iterator	_viTotalList;

	//�� �� �ִ� Ÿ���� ���� ����
	vector<aStarTile*>				_vOpenList;
	vector<aStarTile*>::iterator	_viOpenList;

	//���� ����� ��θ� ���� ����
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

	bool _isEndTotalList;   //��Ż����Ʈ ������ Ȯ�ο�
	bool _isStartTotalList;

	bool _isDontMoveMent;  //�̵��� �� ���ٰ� ����ϼ�
	int _mentCount;		   //��Ʈ �ߴ½ð� �ʱ�ȭ

	//////////////////////////////////////////////////
	//########### �̴ϵ����� Ȯ�ο�  ################//
	/////////////////////////////////////////////////
	bool _isWriteInidata;		//�̴ϵ���Ÿ �о�Դ��� Ȯ�ο�

	bool _isPlayerInfo;			//�÷��̾� ���� �б�

	/////////////////////////////////////////////////

	bool _isMouseOnBaseLeft;		//���콺�� ���̽�����Ʈ���� �÷�������
	bool _isMouseOnBaseRight;		//���콺�� ���̽�����Ʈ���� �÷�������
	bool _isMouseOnAction;			//���콺�� �׼�â�� �÷�������
	bool _isMouseOnState;			//���콺�� ����â�� �÷�������
	bool _isMouseOnPet;				//���콺�� ��â�� �÷�������

	////////////////////////////////////////////////
	// ############# �� ���������� ���ͼ��� ##########
	////////////////////////////////////////////////
	typedef vector<pet*>			_vPet1;        //�÷��̾�1 �� �����
	typedef vector<pet*>::iterator	_viPet1;	   //�÷��̾�1 �� ����

	typedef vector<pet*>			_vPet2;		   //�÷��̾�2 �� �����
	typedef vector<pet*>::iterator  _viPet2;       //�÷��̾�2 �� ����

	//���������� ��ǥ Ȯ�ο�
	int searchIsoX[4];
	int searchIsoY[4];

	//npc ��ġ������ ��ǥȮ�ο�
	int searchNPCIsoX[16];
	int searchNPCIsoY[16];

	string _mapName;

	bool _isDungeon;								//���� �����ϰ�����ֱ�


public:
	menuType* _menuType;
	tagPlayerInfo2 _playerInfo;	//�÷��̾� �����о����
	vItem	_vItem;				// ������ ����
	viItem	_viItem;
	int _npcIsoX;				//npc�� �ִ��� Ȯ�ο�
	int _npcIsoY;				//

	bool _isAvailableClickNPC;		//NPCŬ���� �����ϴ�
	bool _isClickArmorNPC;			//NPC�� Ŭ���ߴٸ� Ȯ�ο�(�Ǹ��ϴ¾ֵ�)
	bool _isClickWeaponNPC;			//NPC�� Ŭ���ߴٸ� Ȯ�ο�(�Ǹ��ϴ¾ֵ�)

	tileMap();
	~tileMap();

	void InputHandle();

	HRESULT init();
	void release();
	void update();
	void render();
	
	//ī�޶� �����̰� ���ִ� �Լ�
	void moveCamera();

	//Ÿ�ϸ��� �׷��ִ� �Լ�
	void drawTileMap();

	//������ �׷��ִ� �Լ�
	void drawRhombus(int left, int top);

	//�ڳ� �����(1 ~ 4�и�)
	int getCornerIndex(int isoX, int isoY);

	//�ڳʾȿ� ���Դ��� Ȯ�ο�
	bool isInRhombus(int corner, int isoX, int isoY);

	//���콺�� �÷����� �޴��� �÷��ִ� �Լ�
	void setMenuBar();
	void updateMenuBar();
	void renderMenuBar();

	//Ÿ������ ���콺 �ö� ��ġ�� select ��ư �������ϱ�
	void mouseSelectTile();

	//ī�޶� ����
	void setCamera(int isoX, int isoY);

	//����, ������Ʈ Ÿ�� ����
	TERRAIN terrainSelect(int frameX, int frameY);
	TILETYPE tileTypeSelect(int frameX, int frameY);

	//���� ���� ��¦ �ٲ��ֱ�(�ΰ��ӿ�)
	void renderSwitch();

	//Ÿ�� �� ����
	void setTiles();

	//�÷��̾� ���� ����
	void playerMovePoint(float x, float y);
	void playerMove();
	void playerLastMove();

	//���콺 ���� ��ư�������� Ȱ������
	void mouseLButton();

	//���콺 ������ ��ư�������� Ȱ��ȭ
	void mouseRButton();

	//���� ���� ���� Ÿ�Ͽ� �ִ��� Ȱ��ȭ
	void currentPlayerTile();

	//�÷��̾� ��ġ �ε��������Լ�
	int getCornerPlayerIndex(int isoX, int isoY);

	//�÷��̾� �ε����� �ڳʾȿ� ���Դ��� Ȯ�ο�
	bool isInPlayerRhombus(int corner, int isoX, int isoY);

	//�÷��̾� �ٶ󺸴� ���� �� �ε��� Ž���ϱ�
	void moveTileSearch();
	void clickNPC();

	//���Ϸε�
	void load(string mapName);

	//A*���������� �Լ�
	void initAStar();
	void setAStarTiles();
	vector<aStarTile*> addOpenList(aStarTile* currentTile);
	void pathFinder(aStarTile* currentTile);
	void releaseAStar();
	void updateAStar();
	void renderAStar();
	//�������

	//�̴ϵ��̿� �Լ�
	void writeInidata();

	//����̵� Ÿ���� �˻��ϱ� ���� �Լ�
	void whorfSpotSearch();

	//NPC�� �ִ� Ÿ���� �˻��ϱ� ���� �Լ�
	void NPCSpotSearch();

	//������ ��� ��Ʋ������ �̵���Ű������ �Լ�
	void dungeonToBattle();

	////���ͼ��͵�

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

