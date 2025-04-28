#pragma once
#include "Npc.h"
#include "Player.h"
#include "CheckObjectType.h"
// main abstract class for all enemies 
class EnemyBase : public Npc {

public:
	
	EnemyBase();
	// virtual constructor here to ensure that memory allocated on the heap for any derrived classes is deallocated 
    // correctly when delloacting the memory via the delete key word
	virtual ~EnemyBase() 
	{

		std::cout << "enemy base destructor called" << std::endl;
	};
	sf::Vector2f getTargetPosition();
	void collision(GameObject* other);
	
    virtual EnemyBase* clone() { return nullptr; } 
	virtual void clone(EnemyBase* copy);

	void draw(sf::RenderWindow * window);
	
	virtual void setAnimStates();
	void getSprites(SpriteGenerator* spriteGenerator);
protected:
	
	


	
};