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
	if (m_canMoveToNextTile) {
		m_position += ((m_direction * m_speed) * m_speedModifier) * dt; // update position
		m_baseSpriteRef.get()->move((m_position - m_baseSpriteRef.get()->getPosition())); // move by offset from new pos

	}

}

// overload of update position to ensure the dynamic object is contained within the 
//  bounds specified
void DynamicObject::updatePosition(float dt, sf::FloatRect boundsToContainObject)
{
	
	sf::Vector2f potentialPosition = m_position + ((m_direction * m_speed) * m_speedModifier) * dt;
	 // update position
	
	// check if the position would be within the bounds 
	float currentX = potentialPosition.x + ((m_baseSpriteRef->getGlobalBounds().getSize().x / 2) * m_direction.x);
	float currentY = potentialPosition.y + ((m_baseSpriteRef->getGlobalBounds().getSize().y / 2) * m_direction.y);

	bool containedX = currentX>boundsToContainObject.left && currentX<(boundsToContainObject.left+boundsToContainObject.width);
	bool containedY = currentY > boundsToContainObject.top && currentY < (boundsToContainObject.top + boundsToContainObject.height);  
	if (containedX && containedY && m_canMoveToNextTile) { // update pos if its in the bounds
		m_position += ((m_direction * m_speed) * m_speedModifier) * dt;
		m_baseSpriteRef.get()->move((m_position - m_baseSpriteRef.get()->getPosition())); // move by offset from new pos

	}
	
	

}
sf::Vector2f& DynamicObject::getNexPos(float dt)
{
	sf::Vector2f potentialPosition = m_position + ((m_direction * m_speed) * m_speedModifier) * dt;
	// update position
	float currentX = potentialPosition.x + ((m_baseSpriteRef->getGlobalBounds().getSize().x / 2) * m_direction.x);
	float currentY = potentialPosition.y + ((m_baseSpriteRef->getGlobalBounds().getSize().y / 2) * m_direction.y);
	m_nextPos = sf::Vector2f(currentX, currentY);
	return m_nextPos;
}
// update last non zero direction values for the dynamic object
void DynamicObject::updateLastKnownDirection(sf::Vector2f& direction)
{

	if (direction.x != 0.0f) {
	   
		float dirx = direction.x < 0.0f ? -1.0f : 1.0f; 
		m_lastKnownDirection = sf::Vector2f(dirx, m_lastKnownDirection.y);
	}
	if (direction.y != 0.0f) {

		float diry = direction.y < 0.0f ? -1.0f : 1.0f;
		m_lastKnownDirection = sf::Vector2f(m_lastKnownDirection.x, diry);
	}

}

// all dynamic objects have a speed modifier that an be effected by tiles 
void DynamicObject::resetSpeedModifier()
{
	m_speedModifier = m_maxSpeedModifier;
}

void DynamicObject::setSpeedModfier(float speedModifer)
{
	m_speedModifier = speedModifer;
}

void DynamicObject::setCanMoveToNextTile(bool canMoveToNextTile)
{
	
	m_canMoveToNextTile = canMoveToNextTile;
}
