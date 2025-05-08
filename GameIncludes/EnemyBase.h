#pragma once
#include "Npc.h"
#include "CheckObjectType.h"
// main abstract class for all enemies 
class EnemyBase : public Npc {

public:
	
	EnemyBase();
	// virtual constructor here to ensure that memory allocated on the heap for any derrived classes is deallocated 
    // and interrpreted correctly when doing so 
	virtual ~EnemyBase() {};
	sf::Vector2f getTargetPosition();
	void collision(GameObject* other);
	
    virtual EnemyBase* clone() { return nullptr; } 
	virtual void clone(EnemyBase* copy);
	void reset();
	void draw(sf::RenderWindow * window);
	void update(float dt);
	virtual void setAnimStates();
	void getSprites(SpriteGenerator* spriteGenerator);
protected:
	
	


	
};