#pragma once
#include "AllyBase.h"
class Pawn : public AllyBase {

public:
	Pawn();
	~Pawn()
	{
		std::cout << "Pawn destructor called" << std::endl;

	};
	AllyBase* clone();
	void update(float dt);

private:



};