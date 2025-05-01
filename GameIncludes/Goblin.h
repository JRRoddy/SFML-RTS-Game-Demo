#pragma once
#include "EnemyBase.h"
#include "TauntStatusEffect.h"
class Goblin :public EnemyBase {

public:
	Goblin();
	~Goblin()
	{ 
	
	};
	EnemyBase* clone(); 

private: 

};


