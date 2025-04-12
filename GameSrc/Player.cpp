#include "Player.h"




Player::Player(){}

Player::Player(sf::Vector2f position, SpriteGenerator *spriteGenerator,InputManager * input):DynamicObject(position)
{
	m_input = input;
	m_speed = m_baseSpeed;
	m_input->addDirectionalMapping(m_vertInputMapName, m_vertcialDirectionMap); 
	m_input->addDirectionalMapping(m_horiInputMapName, m_horizontalDirectionMap);
	getSprites(spriteGenerator);
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

void Player::getSprites(SpriteGenerator* spriteGenerator)
{
	
	m_idleAnim = spriteGenerator->GenerateAnim(m_idleAnimPath);

	m_baseSpriteRef = *m_idleAnim.data();  

	updateBaseSprite();
	
}



void Player::setDamage(float damage )
{
	m_damage = damage;
}



