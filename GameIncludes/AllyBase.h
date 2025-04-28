#pragma once
#include "Npc.h"
#include "CheckObjectType.h" 
#include "EnemyBase.h"
#include "Player.h"
// base class of all ally objects
class AllyBase:public Npc {
public:

	AllyBase();
	// virtual constructor here to ensure that memory allocated on the heap for any derrived classes is deallocated 
	// correctly when delloacting the memory via the delete key word
	virtual ~AllyBase()
	{

		std::cout << "ally base destructor called" << std::endl;
	};

	void collision(GameObject* other);
	virtual AllyBase* clone() { return nullptr; }
	virtual void clone(AllyBase* copy);
	void draw(sf::RenderWindow* window);
	virtual void setAnimStates();
	sf::Vector2f getTargetPosition();
	void getSprites(SpriteGenerator* spriteGenerator);
	bool isRecurited() const; 
	void playerInteract(); 
	void setPlayerRef(Player* playerRef);
	Player* getPlayerRef();
	void setIsSelected(bool isSelected);
	bool getSelected();
	void reset();
	void checkFacingDirection();
	void getPathDir();
	void setTargetPlayer();
protected:
	bool m_selected = false;
	bool m_recruited = false;
	// since allies could be moving towards the player but be attacking enemies
	// we need to have a seperate direction for them to face when they are attacking 
	// and running towards the player 
	sf::Vector2f m_facingDirection;
	sf::Vector2f m_previousMovementOrder;
	sf::Vector2f m_worldPositionTarget;
	Player* m_playerRef = nullptr;



};