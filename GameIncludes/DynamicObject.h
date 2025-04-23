#pragma once
#include "GameObject.h"
#include "AnimationController.h"
// using virtual in heritance for the game object here to ensure that only one instance of inheriatnce 
// when it comes to the classes such as the npc class that can be both dynamic and static
class DynamicObject: public virtual GameObject {

	
public:
	DynamicObject();
	DynamicObject(sf::Vector2f position);
	DynamicObject(float speed); 
	DynamicObject(float speed, sf::Vector2f position); 

	float getSpeed();
	void setSpeed(float speed);
	void updatePosition(float dt);
	void resetSpeedModifier();
	void setSpeedModfier(float speedModifer);
protected:
	float m_speed = 0.0f; 
	float m_speedModifier = 1.0f; 
	float m_maxSpeedModifier = 1.0f;
	sf::Vector2f m_velocity = sf::Vector2f(0.0f,0.0f);
	sf::Vector2f m_direction = sf::Vector2f(0.0f, 0.0f);



};