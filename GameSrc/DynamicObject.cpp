#include "DynamicObject.h"



DynamicObject::DynamicObject()
{
}

DynamicObject::DynamicObject(sf::Vector2f position)
{
	m_position = position;

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
	// update position based on current heading direction
	// of this dynamic object according to a current speed
	// along with taking into account any impact
	// on the objects speed through a speed modifier
	m_position += ((m_direction * m_speed)*m_speedModifier) * dt; // update position
	m_baseSpriteRef.get()->move((m_position - m_baseSpriteRef.get()->getPosition())); // move by offset from new pos

}

void DynamicObject::resetSpeedModifier()
{
	m_speedModifier = m_maxSpeedModifier;
}

void DynamicObject::setSpeedModfier(float speedModifer)
{
	m_speedModifier = speedModifer;
}
