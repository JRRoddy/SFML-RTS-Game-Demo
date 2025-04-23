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
		//check if damage can be done based on current status of attack anim
		if ( m_animationController->stateIsActive("attack") && 	 
			 m_animationController->currentAnimAtEnd()) { 
			
			character->takeDamage(m_damage); // call that characters take damage method
		
		}
	}


}

void EnemyBase::clone(EnemyBase* copy)
{
	std::cout << "enemyBase clone called" << std::endl;
	Npc::clone(copy); // call parent class clone to save on code duplication
}

void EnemyBase::draw(sf::RenderWindow* window)
{
	window->draw(*m_baseSpriteRef.get());
	window->draw(m_debugCircle); 

	/*for (int i = 0; i < m_requestedPath.size(); i++) {
		m_requestedPath[i]->draw(window);
	}*/
}


void EnemyBase::setAnimStates()
{
	Npc::setAnimStates();
}

void EnemyBase::getSprites(SpriteGenerator* spriteGenerator)
{
	Npc::getSprites(spriteGenerator);
}







