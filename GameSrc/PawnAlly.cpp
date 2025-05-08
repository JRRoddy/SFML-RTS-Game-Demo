#include "PawnAlly.h"
#pragma once

Pawn::Pawn()
{
    // set up base stats for character
    // base health, damage, gold
    m_currentStats = characterStats(80.0f,12.0f,0);
    m_speed = 160.0f;
    m_idleAnimPath = "../Assets/Animations/PawnIdleAnim.png";
    m_runAnimPath = "../Assets/Animations/PawnRunAnim.png";
    m_attackAnimPath = "../Assets/Animations/PawnAttackAnim.png";
    m_deathAnimPath = "../Assets/Animations/EnemyDeathAnim.png";
    m_runAnimDelay = 70.0f;
    m_idleAnimDelay = 70.0f;
    m_attackAnimDelay = 95.0f;
    m_deathAnimDelay = 85.0f;
    m_spawnCap = 4;      
    m_debugCircle.setFillColor(sf::Color::Magenta);
    m_debugCircle.setRadius(5.0f);
    m_debugCircle.setOrigin(5.0f / 2.0f, 5.0f / 2.0f);
}

AllyBase* Pawn::clone()
{

	Pawn *copy  = new Pawn();
	AllyBase::clone(copy);
	return copy;
}
// overriden attack character method from npc class allowing the pawn to 
// apply the taunt status effect to a character on hit 
void Pawn::attackCharacter(Character* character)
{
    // pawns can force another character to attack them 
    // making the character focus them when attacking(until the pawn is dead which is handled by the status effct) 
    
    // if the character already has the taunt status effect 
    // then setting the character to target them if not 
    if (character->applyStatusEffect(TAUNT,&m_currentStats)) {
        character->setCharacterTarget(this);
        
    }
    character->takeDamage(m_currentStats.damage);



}



