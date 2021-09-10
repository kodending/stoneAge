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
	string name;										//�÷��̾� �̸�
	int type;											//�÷��̾� ����
	int level;											//�÷��̾� ����
	int totalStamina;									//�÷��̾� �ѳ�����
	int attackPower;									//�÷��̾� ���ݷ�
	int defensePower;									//�÷��̾� ����
	int speedPower;										//�÷��̾� ���߷�
	int charming;										//�÷��̾� �ŷ�
	int loginNum;										//�÷��̾� �α���Ƚ��
	int attributeLand;									//�÷��̾� ���Ӽ�
	int attributeWater;									//�÷��̾� ���Ӽ�
	int attributeFire;									//�÷��̾� ȭ�Ӽ�
	int attributeWind;									//�÷��̾� ǳ�Ӽ�
	image* playerFace;									//�÷��̾� ���̽�
	int faceCurrentFrameX;								//�÷��̾� ���� ������X
	int faceCurrentFrameY;								//�÷��̾� ���� ������Y
	tagPlayerAttribute2	_arrayAttributeFire[10];		//ȭ�Ӽ� �迭
	tagPlayerAttribute2	_arrayAttributeWater[10];		//���Ӽ� �迭
	tagPlayerAttribute2	_arrayAttributeLand[10];		//���Ӽ� �迭
	tagPlayerAttribute2	_arrayAttributeWind[10];		//ǳ�Ӽ� �迭
};

class selectScene : public gameNode
{
private:
	char* _player1;
	char* _player2;

	bool _isPlayer[2];  //�÷��̾ �������

	tagCreateButton _createButton[2];   //ĳ���ͻ�����ư
	tagLoginButton  _loginButton[2];	//�α��ι�ư
	tagDeleteButton _deleteButton[2];	//������ư

	bool _isWriteInidata;				//�̴ϵ���Ÿ �о���� �뵵

	tagPlayerInfo _playerInfo1;			//�÷��̾�1 ������
	tagPlayerInfo _playerInfo2;			//�÷��̾�2 ������

	tagInputWindow4 _deleteWindow;		//���� �˸�â 
	bool _isMusic;
	bool _isInit = false;

public:
	selectScene();
	~selectScene();

	HRESULT init();
	void release();
	void update();
	void render();

	//�÷��̾ ������� �Լ�
	void nonePlayer();
	void nonePlayerRender();

	//�÷��̾ ������� �Լ�
	void existPlayer();
	void existPlayerRender();

	//���콺�ö����� ����
	void ptInRectRender();

	//�̴ϵ���Ÿ Ȯ�ο�
	void writeInidata();

	//�����˸�â �ҵ������� ���� �Լ�
	void deleteWindowUpdate();
	void deleteWindowRender();

	void writeInit();
};

