#include "Player.h"

Player::Player(float speed):DynamicObject(speed)
{
	m_damage = 10.0f;
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
