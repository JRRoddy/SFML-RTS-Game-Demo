#pragma once
#include "AllyBase.h"


AllyBase::AllyBase()
{
}

void AllyBase::collision(GameObject* other)
{

	  // ally targeting for enemies is based on when an enemy enters the space 
	// they cover around them i.e their collision box 
	// therfore if we dont have a current target we check if the target 
	// is an enemy through the CheckObjectType utility which makes use of 
	// a dynmaic cast to attempt ot downcast the object to an enemy
	// if this function fails it returns nullptr allowing for us to check 
	// if the down cast was safe by check if the assigment to the m_characterTarget
	//pointer was null or not 

	// if ally is recruited by the player and the ally doesnt have a target 
	   if (m_recruited && m_characterTarget == nullptr) {
		    
		   m_characterTarget = CheckObjecType<EnemyBase>(other);
	   }
		
		if ( m_characterTarget != nullptr) {
			// if that character was a valid target i.e an enemy
			m_canAttack = true;// ally can attack the enemy its colliding with 
			//check if damage can be done based on current status of attack anim
			if (m_animationController->stateIsActive("attack") &&
				m_animationController->currentAnimAtEnd()) {

				m_characterTarget->takeDamage(m_damage); // call that characters take damage method

			}
		}
	
		
	
	
	
}

void AllyBase::clone(AllyBase* copy)
{
	Npc::clone(copy); // call parent class clone to save on code duplication
}

void AllyBase::draw(sf::RenderWindow* window)
{
	window->draw(*m_baseSpriteRef.get());
	window->draw(m_debugCircle);

	for (int i = 0; i < m_requestedPath.size(); i++) {
		m_requestedPath[i]->draw(window);
	}
}

void AllyBase::setAnimStates()
{

	Npc::setAnimStates();
}

sf::Vector2f AllyBase::getTargetPosition()
{
    
	if (!m_playerRef->recallingAllies()) {
		// if the ally is in combat and the player gives a movement order 
		// then they are no longer considered in combat
		if (m_previousMovementOrder != m_playerRef->getMovementOrderPos() && m_canAttack ) 
		{
			// no longer target the character so that the ally moves towards
			// the player's movement order
			m_characterTarget = nullptr;
		}
		// check if the ally has a target if not move to the last given player movement 
		//order(if the player is not recalling all their allies)
		m_worldPositionTarget = m_characterTarget == nullptr ? m_playerRef->getMovementOrderPos() : m_characterTarget->getPosition();
		return m_worldPositionTarget;
	}
	
    return m_worldPositionTarget = m_playerRef->getPosition();
	

	
}

void AllyBase::getSprites(SpriteGenerator* spriteGenerator)
{
	Npc::getSprites(spriteGenerator);
}

bool AllyBase::isRecurited() const
{
	return m_recruited;
}

void AllyBase::playerInteract()
{

	if (!m_recruited && m_playerRef->getCurrentGold() >= m_gold) {
		std::cout << "recuriting ally" << std::endl;
		m_recruited = true;
	  	
	}
	if (m_recruited) {
		m_selected = true;
	}


}

void AllyBase::setIsSelected(bool isSelected)
{
	m_selected = isSelected;
}

bool AllyBase::getSelected()
{
	return m_selected;
}

void AllyBase::reset()
{
	m_health = m_baseHealth; 
	m_recruited = false; 



}

void AllyBase::checkFacingDirection()
{
	if (m_characterTarget != nullptr && m_canAttack) {

		m_facingDirection = normalize(m_characterTarget->getPosition() - m_position);
		return;
	}
	m_facingDirection = m_direction;

}

void AllyBase::getPathDir()
{
	if (m_requestedPath.size()) {
		sf::Vector2f positionToMoveTo = m_requestedPath[0]->worldPosition;
		m_direction = normalize(positionToMoveTo - m_position);
		updateLastKnownDirection(m_direction);
		m_canAttack = false;
	}
	else {
		// ensure to update the previous movement order to the current player 
		// movement order for the ally helping to keep track of when the ally needs
		// to move out of things such as combat 
		m_previousMovementOrder = m_playerRef->getMovementOrderPos();
		m_direction = sf::Vector2f(0.0f, 0.0f);
		
	}

	m_direction* float((!getIsAttacking()));

}
