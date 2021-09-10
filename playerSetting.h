#pragma once
#include "gameNode.h"
#include <vector>

struct tagPlayerAttribute
{
	image* img;
	RECT rc;
	int currentFrameX;
	int currentFrameY;
};

struct tagPlayerType
{
	image* img;
	RECT rc;
	int currentFrameX;
	int currentFrameY;
};

struct tagInputWindow3
{
	image* frontImg;
	image* backImg;
	image* checkImg;
	RECT frontRect;
	RECT backRect;
	RECT checkRect;
	RECT textRect;
};

struct tagInputWindow2
{
	image* frontImg;
	image* backImg;
	RECT frontRect;
	RECT backRect;
	RECT decideRect;
	RECT rejectRect;
	RECT textRect;
};

class playerSetting : public gameNode
{
private:
	tagPlayerType _playerType;

	bool _isWriteInidata; //inidata �ҷ��Դ��� Ȯ�ο�

	string name;			//nickName �ۼ��ޱ����� �̸��뵵
	string _dialog;			//�Է¹��� Ű�� ����뵵
	RECT _nameRect;			//�г��� �ؽ�Ʈ ��ġ ���������ѿ뵵
	int _baseStatusCount;	//�⺻�ɷ�ġ 20��
	int _statusStamina;		//ü�´ɷ�ġ
	int _statusStrength;	//�Ϸ´ɷ�ġ
	int _statusHealth;		//�ǰ��ɷ�ġ
	int _statusSpeed;		//���ǵ�ɷ�ġ

	int _baseAttributeCount;		//�⺻�Ӽ� 10��
	int _attributeFire;				//ȭ�Ӽ�
	int _attributeWater;			//���Ӽ�
	int _attributeLand;				//���Ӽ�
	int _attributeWind;				//ǳ�Ӽ�

	bool _isDecideRect;			//������ư�� �������� Ȯ�ο�
	bool _isReturnRect;			//���Ϲ�ư�� �������� Ȯ�ο�
	bool _isIncompleteWindow;	//���� ������ ��������� �߰��ϱ�

	tagPlayerAttribute	_arrayAttributeFire[10];		//ȭ�Ӽ� �迭
	tagPlayerAttribute	_arrayAttributeWater[10];		//���Ӽ� �迭
	tagPlayerAttribute	_arrayAttributeLand[10];		//���Ӽ� �迭
	tagPlayerAttribute	_arrayAttributeWind[10];		//ǳ�Ӽ� �迭

	RECT _decideRect;			//������Ʈ
	RECT _returnRect;			//���ư��ⷺƮ
	RECT _statusRect[2][4];		//������ⷺƮ
	RECT _attributeRect[2][4];  //�Ӽ���ⷺƮ

	tagInputWindow3	_inCompleteWindow;	//�̿ϼ� ������â
	tagInputWindow2 _decideWindow;		//���� ������â
	tagInputWindow2 _returnWindow;		//���� ������â

public:
	playerSetting();
	~playerSetting();

	HRESULT init();
	void release();
	void update();
	void render();

	void selectRed();
	void selectBlue();

	//���̵� ���̾�α��Է¹ޱ����� �۾���
	void dialogSetNickName();
	void dialogInput();
	void dialogRender();

	//�������ͽ���Ʈ ��°Ϳ����� �۾���
	void statusSelect();

	//�Ӽ���Ʈ ��°Ϳ����� �۾���
	void attributeSelect();
	void attributeRect();
	void attributeRender();

	//���콺�ø��� ��Ʈ�׷��ֱ�
	void ptInRectRender();

	//�ؽ�Ʈ �׷�����
	void textOutRender();

	//������ư, ���ư����ư
	void decideButton();
	void returnButton();

	//��ư Ȱ��ȭȮ��
	void buttonActive();
	void buttonRender();

	//�̴ϵ���Ÿ ���̺�
	void saveInidata();
};

