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
		applyHitEffect();
		std::cout << "damage done is " << damage << std::endl;
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
}
void Character::applyHitEffect()
{
	if (!m_wasHit) {
		m_wasHit = true;
		m_hitEffectTimer.restart();
		
	}



}

void Character::updateHitEffect()
{
	if (m_wasHit && m_hitEffectTimer.getElapsedTime().asSeconds() <= m_hitEffectTime.asSeconds()) {
		// blend sprites colour while we have not hit the hit effect timer
		// used to modulate the sprites colour to indicate a hit
		m_baseSpriteRef.get()->setColor(m_hitEffectColour);
		return;
	}
	m_wasHit = false;
	m_baseSpriteRef->setColor(m_defaultColour);
}


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








