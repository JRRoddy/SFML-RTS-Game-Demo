#include "Player.h"




Player::Player(sf::Vector2f position, InputManager * input):DynamicObject(position)
{
	m_input = input;
	m_speed = m_baseSpeed;

	m_input->addDirectionalMapping(m_vertInputMapName, m_vertcialDirectionMap); 
	m_input->addDirectionalMapping(m_horiInputMapName, m_horizontalDirectionMap);
}





float Player::getDamage()
{
	return m_damage;
}

void Player::update(float dt)
{



	float dirX = m_input->getDirectionFromKey(m_horiInputMapName); 
	float dirY = m_input->getDirectionFromKey(m_vertInputMapName);
	m_direction = normalize(sf::Vector2f(dirX, dirY)); 
	updatePosition(dt);
	



}

void Player::setDamage(float damage )
{
	m_damage = damage;
}



