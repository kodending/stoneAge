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

	arrObject _arrObj;			//오브젝트 정렬용 벡터

private:
	int _petAttackTiming;		//펫 어택타이밍 함수를위한 변수
	int _delayCount;			//딜레이카운트주기
	bool _isDamageCalculation;	//데미지계산했는지 확인용
	float _pushPowerX;			//공격당했을때 밀리는힘적용
	float _pushPowerY;			//공격당했을때 밀리는힘적용
	bool _isShortStop;			//잠깐스탑시키기
	int _happyTime;				//행복할타임
	int _enemyDeathCount;		//죽은 에너미 숫자확인
	int _deadCount;				//죽음카운트재기
	bool _isCatchSound;			//캐치사운드 나왔는지
	bool _isDeadSound;			//죽음의 사운드가 나왔는지
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

	//페트가 공격할때 공격 타이밍 주는 함수
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

