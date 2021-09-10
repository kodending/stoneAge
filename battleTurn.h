#pragma once
#include "battleState.h"
#include <vector>
#include <string>

class battleMap;

class battleTurn : public battleState
{
private:
	typedef struct tagObject
	{
		int speedPower;
	}OBJECT;

	typedef vector<OBJECT>						arrObject;
	typedef vector<OBJECT>::iterator			iterObject;

	arrObject _arrObj;			//������Ʈ ���Ŀ� ����

private:
	int _petAttackTiming;		//�� ����Ÿ�̹� �Լ������� ����
	int _delayCount;			//������ī��Ʈ�ֱ�
	bool _isDamageCalculation;	//����������ߴ��� Ȯ�ο�
	float _pushPowerX;			//���ݴ������� �и���������
	float _pushPowerY;			//���ݴ������� �и���������
	bool _isShortStop;			//���ž��Ű��
	int _happyTime;				//�ູ��Ÿ��
	int _enemyDeathCount;		//���� ���ʹ� ����Ȯ��
	int _deadCount;				//����ī��Ʈ���
	bool _isCatchSound;			//ĳġ���� ���Դ���
	bool _isDeadSound;			//������ ���尡 ���Դ���
	int _turnOffCount;			//
	bool _isbattleEnd;
	bool _isCatchCatch;
public:
	virtual battleState* inputHandle(battleMap* battleMap);
	virtual void update(battleMap* battleMap);
	virtual void enter(battleMap* battleMap);
	virtual void render(battleMap* battleMap);
	virtual void exit(battleMap* battleMap);

	void setEnemySelect(battleMap* battleMap);
	void battleSort(battleMap* battleMap);
	void addObject(int speedPower);
	void addObjArray(battleMap* battleMap);
	void quickSort(int left, int right);

	void battleStart(battleMap* battleMap);
	void updateBattle(battleMap* battleMap);

	void turnEndBattle(battleMap* battleMap);

	void heatBattle(battleMap* battleMap);
	void hurtMove(battleMap* battleMap);
	void catchBattle(battleMap* battleMap);
	void moveFrameY(battleMap* battleMap);

	void deadMotion(battleMap* battleMap);

	void attackSelectConvert(battleMap* battleMap);

	void battleClosed(battleMap* battleMap);
	void battleClosed2(battleMap* battleMap);
	void happyTime(battleMap* battleMap);

	//��Ʈ�� �����Ҷ� ���� Ÿ�̹� �ִ� �Լ�
	int petAttackTiming(PETNAME petName)
	{
		if (petName == DURI) _petAttackTiming = 4;
		if (petName == SPOTTEDURI) _petAttackTiming = 5;
		if (petName == URI) _petAttackTiming = 4;
		if (petName == MAMONAS) _petAttackTiming = 6;
		if (petName == MANMO) _petAttackTiming = 6;
		if (petName == MANMOR) _petAttackTiming = 6;
		if (petName == GOLROS) _petAttackTiming = 2;
		if (petName == MOGAROS) _petAttackTiming = 7;
		if (petName == OGAROS) _petAttackTiming = 2;
		if (petName == GORGOR) _petAttackTiming = 2;
		if (petName == NORNOR) _petAttackTiming = 2;
		if (petName == VERGA) _petAttackTiming = 2;
		if (petName == VERURU) _petAttackTiming = 2;
		if (petName == BANBORO) _petAttackTiming = 5;
		if (petName == BANGINO) _petAttackTiming = 5;
		if (petName == BURDON) _petAttackTiming = 5;
		if (petName == RIBINO) _petAttackTiming = 5;
		if (petName == YANGIRO) _petAttackTiming = 5;

		return _petAttackTiming;
	}
};

