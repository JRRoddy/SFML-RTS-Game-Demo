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
		
		if ( m_characterTarget != nullptr ) {
			// if that character was a valid target i.e an enemy
			
			m_canAttack = true;// ally can attack the enemy its colliding with 
			//check if damage can be done based on current status of attack anim
			if (m_animationController->stateIsActive("attack") &&
				m_animationController->currentAnimAtEnd()) {
				attackCharacter(m_characterTarget); // call that characters take damage method
			}
			characterTargetDeathCheck(); // check that the target is not dead 

		}
	   

		
	
	
	
}

void AllyBase::clone(AllyBase* copy)
{

	Npc::clone(copy); // call parent class clone to save on code duplication
	copy->setPlayerRef(m_playerRef);

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
void AllyBase::onPathEnd()
{
	// ensure to update the previous movement order to the current player 
	// movement order for the ally helping to keep track of when the ally needs
	// to move out of things such as combat 
	m_previousMovementOrder = m_playerRef->getMovementOrderPos();

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
Player* AllyBase::getPlayerRef()
{
	return m_playerRef;
}
void AllyBase::setPlayerRef(Player* playerRef)
{
	m_playerCharacterRef = playerRef;
	m_playerRef = playerRef;
}
void AllyBase::playerInteract()
{

	if (!m_recruited && m_playerRef->getCurrentGold() >= m_currentStats.gold) {
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
	// resetting ally object for when it is chosen from its associated pool
	// prepping it to be spawned in
	m_active = true;
	m_currentStats.health = m_currentStats.baseHealth; 
	m_recruited = false;
	m_characterTarget = nullptr;
	m_requestedPath.clear();


}

// generic update function for allies 
// controlling their facing direction and updating their position
void AllyBase::update(float dt)
{
	checkAttackingFacingDirection();
	flipSpriteX(m_facingDirection.x);
	setAnimStates();
	m_animationController.get()->update();
	updatePosition(dt);
	m_debugCircle.setPosition(m_position);

}


void AllyBase::setTargetPlayer()
{
	m_characterTarget = m_playerRef;
}
