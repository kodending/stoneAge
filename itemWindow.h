#pragma once
#include "menuType.h"

enum PLAYERWEARTYPE
{
	WEAR_NONE,
	WEAR_WEAPON,
	WEAR_HELMET,
	WEAR_ARMOR,
	WEAR_RIDE_BOOK
};

struct tagPlayerWear
{
	RECT rc;					// �÷��̾� ���뷺Ʈ
	PLAYERWEARTYPE playerWear;	// �÷��̾� ����Ÿ��
	int centerX;				// ����x
	int centerY;				// ����y
	bool isExistItem;			//�������� �ִ�Ȯ�ο�
	int itemPos;				//����������
};

struct tagItem2
{
	RECT rc;					//������ĭ ��Ʈ
	int centerX;				//������ĭ �߽���ǥ x
	int centerY;				//������ĭ �߽���ǥ y
	bool isExistItem;			//�������� �ִ�Ȯ�ο�
	int itemPos;
};

struct tagItemWindow2
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	RECT arrangeRect;			//�������� ��Ʈ
	RECT exitRect;				//�ݱ� ��Ʈ
	tagPlayerWear pw[3][4];		//�÷��̾� ����κ�
	tagItem2 item[5][3];			//������ ��Ʈ
};

class tileMap;

class itemWindow : public menuType
{
private:
	tagItemWindow2 _itemWindow;

	bool _isLoadSetItem;		//�����ۼ��� �Ұ�
	int _playerStone;			//�÷��̾��� ������
	bool _isClickItem;
	int _clickDelayTime;		//������Ÿ���ֱ�
	bool _isAbleSameClick;		//���ڸ��� �ٽ� �Ѽ��ֵ����ϱ�����
	bool _isTime;				//Ÿ�����ֱ�

public:
	virtual menuType* inputHandle(tileMap * tileMap);
	virtual void update(tileMap * tileMap);
	virtual void enter(tileMap * tileMap);
	virtual void render(tileMap * tileMap);
	virtual void exit(tileMap * tileMap);

	void updateRect(tileMap* tileMap);
	void PtInRender(tileMap * tileMap);

	void setItem(tileMap* tileMap);
	void selectItem(tileMap* tileMap);
	void switchItem(tileMap* tileMap);
	void updateSelectItem(tileMap* tileMap);

	void updateItem(tileMap* tileMap);

	void itemRender(tileMap* tileMap);

	void textRender(tileMap* tileMap);

	void deleteInidata(tileMap* tileMap, int itemPos);
	void saveInidata(tileMap* tileMap, int itemPos);

	void lineUpItem(tileMap* tileMap);
};

