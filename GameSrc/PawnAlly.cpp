#include "PawnAlly.h"
#pragma once

Pawn::Pawn()
{
    m_damage = 15.0f;
    m_health = 40.0f;
    m_speed = 150.0f;
    m_idleAnimPath = "../Assets/Animations/PawnIdleAnim.png";
    m_runAnimPath = "../Assets/Animations/PawnRunAnim.png";
    m_attackAnimPath = "../Assets/Animations/PawnAttackAnim.png";
    m_runAnimDelay = 70.0f;
    m_idleAnimDelay = 70.0f;
    m_attackAnimDelay = 70.0f;
    m_spawnCap = 5;
    m_gold = 0;
    m_debugCircle.setFillColor(sf::Color::Magenta);
    m_debugCircle.setRadius(5.0f);
    m_debugCircle.setOrigin(5.0f / 2.0f, 5.0f / 2.0f);
}

AllyBase* Pawn::clone()
{

	Pawn *copy  = new Pawn();
	Npc::clone(copy);
	return copy;
}

void Pawn::update(float dt)
{

    flipSpriteX(m_direction.x);
    setAnimStates();
    m_animationController.get()->update();
    updatePosition(dt);
    m_debugCircle.setPosition(m_position);

}
