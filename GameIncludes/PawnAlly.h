#pragma once
#include "AllyBase.h"
class Pawn : public AllyBase {

public:
	Pawn();
	~Pawn(){};
	AllyBase* clone();
	void attackCharacter(Character * character);

private:



};