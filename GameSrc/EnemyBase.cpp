#include "EnemyBase.h"



EnemyBase::EnemyBase()
{
}

void EnemyBase::collision(GameObject* other)
{  

	// if the type of object we are colliding with is a character
	Character* character = CheckObjecType<Character>(other); 
	if (character != nullptr && character == m_characterTarget) {
		// if that character was the enemy's target
		
		m_canAttack  = true;// enemy can attack 
		m_direction = sf::Vector2f(0.0f, 0.0f);
		//check if damage can be done based on current status of attack anim
		if ( m_animationController->stateIsActive("attack") && 	 
			 m_animationController->currentAnimAtEnd()) { 
			 attackCharacter(character); // call the attack method for this character 
		}
		characterTargetDeathCheck();

	}


}

void EnemyBase::clone(EnemyBase* copy)
{
	Npc::clone(copy); // call parent class clone to save on code duplication
}

void EnemyBase::reset()
{
	m_active = true; 
 	m_health = m_baseHealth; 
	m_characterTarget = nullptr;
    	
}

void EnemyBase::draw(sf::RenderWindow* window)
{
	window->draw(*m_baseSpriteRef.get());
	window->draw(m_debugCircle); 

	/*for (int i = 0; i < m_requestedPath.size(); i++) {
		m_requestedPath[i]->draw(window);
	}*/
}

void EnemyBase::update(float dt)
{
	flipSpriteX(m_direction.x);
	setAnimStates();
	m_animationController.get()->update();
	updatePosition(dt);
	m_debugCircle.setPosition(m_position);
}

sf::Vector2f EnemyBase::getTargetPosition()
{
	if (m_characterTarget == nullptr) {
		m_characterTarget = m_playerCharacterRef;
	}

	return m_characterTarget->getPosition();
}
void EnemyBase::setAnimStates()
{
	Npc::setAnimStates();
}

void EnemyBase::getSprites(SpriteGenerator* spriteGenerator)
{
	Npc::getSprites(spriteGenerator);
}







