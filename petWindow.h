#pragma once
#include "menuType.h"

class tileMap;

struct tagPetWindow
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	RECT infoRect;
	RECT exitRect;
	RECT petNameRect[5];			//���̸� Ȱ��ȭ
	RECT petButtonRect[5];			//���ư ��Ʈ Ȱ��ȭ
	image* petButtonImg[5];			//��â�� ���� ������ ��ư �̹��� Ȱ��ȭ
	bool isPetNum[5];				//��â�� ���� �ִ���
	string petModeName[5];			//�� ��� �̸�
	string petAvailableRide[5];		//�� ž�°��ɿ��� Ȯ��
};


class petWindow : public menuType
{
private:
	tagPetWindow _petWindow;

	int _petModeColorR[5];				//���� RGB ����
	int _petModeColorG[5];				//���� RGB ����
	int _petModeColorB[5];				//���� RGB ����

public:
	virtual menuType* inputHandle(tileMap * tileMap);
	virtual void update(tileMap * tileMap);
	virtual void enter(tileMap * tileMap);
	virtual void render(tileMap * tileMap);
	virtual void exit(tileMap * tileMap);

	void writeIniData();

	void petInfoRender();
};
