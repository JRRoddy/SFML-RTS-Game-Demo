#pragma once
#include "AllyBase.h"


AllyBase::AllyBase()
{
}

void AllyBase::collision(GameObject* other)
{
	// if the type of object we are colliding with is a character
	
	
		Character* character = CheckObjecType<Character>(other);
		if (character != nullptr && character == m_characterTarget) {
			// if that character was the enemy's target

			m_canAttack = true;// enemy can attack 
			//check if damage can be done based on current status of attack anim
			if (m_animationController->stateIsActive("attack") &&
				m_animationController->currentAnimAtEnd()) {

				character->takeDamage(m_damage); // call that characters take damage method

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
