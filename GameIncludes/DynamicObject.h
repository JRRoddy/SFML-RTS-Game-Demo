#pragma once
#include "GameObject.h"
class DynamicObject: public GameObject {


public:
	
	DynamicObject(float speed); 
	DynamicObject(float speed, sf::Vector2f position);



protected:
	float m_speed = 0.0f;
	sf::Vector2f m_velocity = sf::Vector2f(0.0f,0.0f);



};