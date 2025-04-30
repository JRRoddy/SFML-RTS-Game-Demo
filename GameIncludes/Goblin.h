#pragma once
#include "EnemyBase.h"

class Goblin :public EnemyBase {

public:
	Goblin();
	~Goblin()
	{ 
	
	};
	EnemyBase* clone(); 

private: 

};


