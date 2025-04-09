#pragma once
#include "GameObject.h"
class DynamicObject: public GameObject {


public:
	DynamicObject();
	DynamicObject(sf::Vector2f position);
	DynamicObject(float speed); 
	DynamicObject(float speed, sf::Vector2f position); 

	float getSpeed();
	void setSpeed(float speed);
	void updatePosition(float dt);

protected:
	float m_speed = 0.0f;
	sf::Vector2f m_velocity = sf::Vector2f(0.0f,0.0f);
	sf::Vector2f m_direction = sf::Vector2f(0.0f, 0.0f);



};