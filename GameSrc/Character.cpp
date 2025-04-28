#include "Character.h"

Character::Character(sf::Vector2f position):DynamicObject(position)
{
}


// getters and setters for stats shared across all beings in the world
void Character::setDamage(float& damage)
{ 
	m_damage = damage;
}

void Character::setHealth(float& health)
{
	m_health = health;
}

void Character::takeDamage(float& damage)
{
	
	m_health -= damage;

}

float Character::getDamage() const
{
	return m_damage;
}

float Character::getHealth() const
{
	return m_health;
}

void Character::setCellWidth(int& cellWidth) {
	m_cellWidth = cellWidth;
}

int Character::getCellWidth() const
{
	return m_cellWidth;
}

void Character::setGridTile(gridTile* gridTile)
{
	m_currentTile = gridTile;
}

bool Character::getIsAttacking() const
{
	return m_canAttack;
}
int Character::getCurrentGold()
{
	return m_gold;
}

bool Character::getAttackFinished()const
{
	return m_attackFinished;
}



