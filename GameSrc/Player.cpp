#include "Player.h"

Player::Player()
{
}



Player::Player(sf::Vector2f position):DynamicObject(position)
{
}

Player::Player(float speed,sf::Vector2f position):DynamicObject(speed,position)
{
	
}

Player::Player(float speed, float damage):DynamicObject(speed)
{
	m_damage = damage;
}


float Player::getDamage()
{
	return m_damage;
}

void Player::setDamage(float damage )
{
	m_damage = damage;
}
