#include "DynamicObject.h"



DynamicObject::DynamicObject()
{
}

DynamicObject::DynamicObject(sf::Vector2f position):GameObject(position)
{
}

// dynamic object class that inherits from the game object class 
// this will be the base class for objects with mobility and those that can move around the scene
DynamicObject::DynamicObject(float speed)
{
	m_speed = speed;

}

DynamicObject::DynamicObject(float speed, sf::Vector2f position):GameObject(position)
{
	
	m_speed = speed;

}


//setters and getters for current speed of the object
float DynamicObject::getSpeed()
{
	return m_speed;
}

void DynamicObject::setSpeed(float speed)
{
	m_speed = speed;
}

void DynamicObject::updatePosition(float dt)
{

	m_position += (m_direction * m_speed) * dt;

}
