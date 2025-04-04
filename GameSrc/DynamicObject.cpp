#include "DynamicObject.h"

DynamicObject::DynamicObject(float speed)
{
	m_speed = speed;

}

DynamicObject::DynamicObject(float speed, sf::Vector2f position):GameObject(position)
{
	
	m_speed = speed;

}
