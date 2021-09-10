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
	int _isoX, _isoY;				// ���� Ÿ�� �ε���
	int _saveIsoX, _saveIsoY;		// ������ Ÿ�� �ε���
	int _corner;
	char str[128];
	int _count;						//framecount ��
	int _instantCnt;				//�ӽÿ�ī��Ʈ

	tagTile _tiles[TILE_COUNT_X][TILE_COUNT_Y];

	int _cameraBufferX;				// ī�޶��̵��� ���� Ÿ�� �˻� �̵���
	int _cameraBufferY;				// 

	float _moveX;					// ���� ��
	float _moveY;

	RECT _underBarRc;				// ����� ��Ʈ

	RECT _tileRc;					// tool Ÿ�� ��Ʈ
	RECT _structureRc;				// tool ���๰ ��Ʈ
	RECT _objectRc;					// tool ������ ��Ʈ
	RECT _NPCRc;					// tool NPC ��Ʈ
	RECT _eraserRc;					// tool ���찳 ��Ʈ
	RECT _saveRc;					// tool ���� ��Ʈ
	RECT _loadRc;					// tool �ҷ����� ��Ʈ
	RECT _exitRc;					// tool ������ ��Ʈ

	float _toolY;					// ����Ʈ ��ǥ�� ����

	bool _isMouseOnToolBar;			//���콺�� ���ٿ� �ö��ִ��� Ȯ�ο�
	bool _isClickTile;				//Ÿ���� �����ߴ��� Ȯ��
	bool _isExitButton;				//�˾�â exit ��ư�������� Ȯ�ο�

	bool _isToolTile;				//���� tooltile�� �ִ���
	bool _isToolStructure;			//���� toolstructure�� �ִ���
	bool _isToolObject;				//���� toolObject���ִ���
	bool _isToolFence;				//���� toolfence�� �ִ���
	bool _isToolGate;				//���� toolgate�� �ִ���
	bool _isToolDisplay;			//���� tooldisplay�� �ִ���
	bool _isToolPlants;				//���� toolPlants�� �ִ���
	bool _isToolRock;				//���� toolRock�� �ִ��� 
	bool _isToolWallBasic;			//���� toolWallBasic�� �ִ���
	bool _isToolWallDungeon;		//���� toolWallDungeon�� �ִ���
	bool _isToolNpc;				//���� toolNpc�� �ִ���
	bool _isToolEraser;				//���� toolEraser�� �ִ���
	bool _isToolTileType;			//���� toolTypeTile�� �ִ���
	bool _isToolSaveInput;			//���� toolSaveInput�� �ִ���

	string _dialog;					//�Է�â�� �۾��� �ޱ����� ��Ʈ������
	string name;					//�Է�â�� ���������ϱ����� ����

public:
	toolType* _toolType;
	tagSampleTile	_sampleTile;	// Ÿ�� ����
	tagCurrentTile	_currentTile;	//���� ������ Ÿ��
	tagPopUp		_popUp;			//�˾�â
	tagToolType		_toolName;		//��Ÿ�� ��Ī ����
	tagLeftButton	_leftButton;	//���ʹ�ư
	tagRightButton	_rightButton;	//�����ʹ�ư
	tagSaveInput	_saveInput;		//���̺���ǲ â ����
	
	mapTool();
	~mapTool();

	void InputHandle();

	HRESULT init();
	void release();
	void update();
	void render();
	void moveCamera();

	//Ÿ�ϸ� �׷��ִ� �Լ�
	void drawTileMap();
	//������ �׷��ִ� �Լ�
	void drawRhombus(int left, int top);
	//�ڳ� ����(1 ~ 4�и�)
	int getCornerIndex(int isoX, int isoY);
	//�ڳʾȿ� �Դ��� �����ϴ� �Լ�
	bool isInRhombus(int corner, int isoX, int isoY);
	//���콺 �÷����� ���� �ø��� �Լ�
	void setToolBar();
	void updateToolBar();
	void renderToolBar();

	//���� ���� ������ ���� Ÿ�� ������ �����ϱ����� �Լ�
	void selectCurrentTile();

	//Ÿ������ ���콺 �ö� ��ġ�� select ��ư �������ϱ�
	void mouseSelectTile();

	//����, ������Ʈ Ÿ�� ����
	TERRAIN terrainSelect(int frameX, int frameY);
	TILETYPE tileTypeSelect(int frameX, int frameY);

	//CTRL �����Ͽ� �����ϱ�
	void devideCTRL(int isoX, int isoY);

	//���¿� ���� CTRL �����ϱ�
	void updateCtrSelect();

	//��ư 1�������� �ð��ְ� �ٲ��ֱ�
	void buttonFrame();

	//save, load �����ϱ�
	void saveMap();
	void loadMap();

	//���� ���� ��¦ �ٲ��ֱ�(�ΰ��ӿ�)
	void renderSwitch();

	//������Ʈ �������ֱ�(������)
	void objectRender();

	//�����Է� �Լ������
	void dialogSet();
	void dialogInput();
	void renderDialog();

	//��Ʈ ���ͼ���
	RECT getUnderBarRc() { return _underBarRc; }
	RECT getTileRc() { return _tileRc; }
	RECT getStructureRc() { return _structureRc; }
	RECT getObjectRc() { return _objectRc;	}
	RECT getNpcRc() { return _NPCRc; }
	RECT getEraserRc() { return _eraserRc; }
	RECT getSaveRc() { return _saveRc; }
	
	//���ӻ����� ����
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

