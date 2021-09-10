#pragma once
#include "gameNode.h"

struct tagMainMenu
{
	image* menuImg;				//���θ޴� �̹���
	image* backImg;				//�޴�����ȭ�� �̹���
	RECT gameStartRect;			//���ӽ��� ��Ʈ
	RECT mapToolRect;			//�������� ��Ʈ
	RECT exitRect;				//������ ��Ʈ
	RECT mainRect;				//���η�Ʈ
	RECT backRect;				//���ι���ȭ�� ��Ʈ
};

struct tagInputWindow
{
	image* frontImg;			//�չ��ȭ��
	image* backImg;				//�޹��ȭ��
	RECT windowRect;			//�����췺Ʈ
	RECT backRect;				//�޹�淺Ʈ
	RECT permitRect;			//������Ʈ
	RECT rejectRect;			//������Ʈ
	RECT textRect;				//�ؽ�Ʈ��Ʈ
};

class mainScene : public gameNode
{
private:

	tagMainMenu _mainMenu;
	tagInputWindow _exitWindow;

	bool _isExitOn; //�������ư�� �������� Ȱ��ȭ
	bool _isWriteInidata; //������ �о���� �뵵
	bool _isMusic;

public:
	mainScene();
	~mainScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void exitWindow();

	void textBoxRender();
	void textRender();
	void exitRender();
	void wirteInidata();
};

