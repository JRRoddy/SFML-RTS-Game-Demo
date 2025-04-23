#pragma once
#include "EnemyBase.h"

class Goblin :public EnemyBase {

public:
	Goblin();
	~Goblin()
	{ 
		std::cout << "goblin destructor called" << std::endl;
	
	};
	EnemyBase* clone(); 
	void update(float dt);

private: 

};


