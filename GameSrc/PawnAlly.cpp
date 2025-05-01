#include "PawnAlly.h"
#pragma once

Pawn::Pawn()
{
    // set up base stats for character
    // base health, damage, gold
    m_currentStats = characterStats(150.0f,15.0f,0);
    m_speed = 150.0f;
    m_idleAnimPath = "../Assets/Animations/PawnIdleAnim.png";
    m_runAnimPath = "../Assets/Animations/PawnRunAnim.png";
    m_attackAnimPath = "../Assets/Animations/PawnAttackAnim.png";
    m_deathAnimPath = "../Assets/Animations/EnemyDeathAnim.png";
    m_runAnimDelay = 70.0f;
    m_idleAnimDelay = 70.0f;
    m_attackAnimDelay = 100.0f;
    m_deathAnimDelay = 85.0f;
    m_spawnCap = 5;
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

void Pawn::attackCharacter(Character* character)
{
    // pawns can force another character to attack them 
    // making the character focus them when attacking by first checking
    // if the character already has the taunt status effect 
    // then setting the character to target them if not 
    if (character->applyStatusEffect(TAUNT,&m_currentStats)) {
        std::cout << "pawn taunting character" << std::endl;
        character->setCharacterTarget(this);
        
    }
    character->takeDamage(m_currentStats.damage);
    std::cout << "pawn attacking target for " << m_currentStats.damage << "target  health " << character->getHealth() << std::endl;



}



