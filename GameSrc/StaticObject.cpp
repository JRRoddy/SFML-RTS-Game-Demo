#include "StaticObject.h"

StaticObject::StaticObject(sf::Vector2f position) 
{
	m_position = position;
}

StaticObject::StaticObject(sf::Sprite* sprite)
{
	m_position = sprite->getPosition();
	m_baseSpriteRef.reset(sprite);

}

StaticObject::~StaticObject(){}
