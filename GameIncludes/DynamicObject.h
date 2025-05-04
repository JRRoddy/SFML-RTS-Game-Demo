#pragma once
#include "GameObject.h"
#include "AnimationController.h"
// using virtual  iheritance for the game object here to ensure that only one instance of inheriatnce 
// when it comes to the classes such as the npc class that can be both dynamic and static
class DynamicObject: public virtual GameObject {

	
public:
	DynamicObject();
	DynamicObject(sf::Vector2f position); 

	DynamicObject(float speed); 
	DynamicObject(float speed, sf::Vector2f position); 
	virtual ~DynamicObject() {};
	float getSpeed();
	void setSpeed(float speed);
	virtual void updatePosition(float dt);
	void updatePosition(float dt, sf::FloatRect boundsToContainObject);
	sf::Vector2f& getNexPos(float dt);
	void updateLastKnownDirection(sf::Vector2f &direction);
	void resetSpeedModifier();
	void setSpeedModfier(float speedModifer);
	void setCanMoveToNextTile(bool canMoveToNextTile);
	float getSpeedModifier()const;
protected:
	sf::Vector2f m_nextPos;
	bool m_canMoveToNextTile = true;
	float m_speed = 0.0f; 
	float m_speedModifier = 1.0f; 
	float m_maxSpeedModifier = 1.0f;
	sf::Vector2f m_lastKnownDirection = sf::Vector2f(1.0f,1.0f);
	sf::Vector2f m_velocity = sf::Vector2f(0.0f,0.0f);
	sf::Vector2f m_direction = sf::Vector2f(0.0f, 0.0f);



};