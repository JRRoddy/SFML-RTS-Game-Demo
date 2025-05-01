#include "Character.h"

Character::Character(sf::Vector2f position):DynamicObject(position)
{
}


// getters and setters for stats shared across all beings in the world
void Character::setDamage(float& damage)
{ 
	
	m_currentStats.damage = damage;
}

void Character::setHealth(float& health)
{
	m_currentStats.baseHealth = health;
	m_currentStats.health = health;
}

void Character::takeDamage(float& damage)
{
	if (!isDead()) {
		m_currentStats.health -= damage;
	}
	

}

Character* Character::getCharacterTarget()
{
	return m_characterTarget;
}
void Character::setCharacterTarget(Character* character)
{
	m_characterTarget = character;

}
bool Character::hasApplicableStatusEffects()
{
	return m_appliableStatusEffectsMap.size() > 0;
}
void Character::resetStatusEffectManager()
{
	if (hasApplicableStatusEffects()) {
		m_statusEffectManager.get()->reset();
	}
}
bool Character::applyStatusEffect(StatusEffectIds id, characterStats* initiaterStatsRef) {
	
	return m_statusEffectManager->activateStatusEffect(id, initiaterStatsRef);
};

StatusEffectManager* Character::getStatusEffectManager()
{
	return m_statusEffectManager.get();
}
float Character::getDamage() const
{
	return m_currentStats.damage;
}

float Character::getHealth() const
{
	return m_currentStats.health;
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
	return m_currentStats.gold;
}

bool Character::getAttackFinished()const
{
	return m_attackFinished;
}

bool Character::isDead() const
{
	return m_currentStats.health <= 0.0f;
}

bool Character::isTaunted() const
{
	return m_taunted;
}

void Character::setTaunted(bool taunted)
{
	m_taunted = taunted;
}





