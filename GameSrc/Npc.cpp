#include "Npc.h"


Character * Npc::getPlayerCharacterRef()
{
	return m_playerCharacterRef;
}
void Npc::setBaseSprite(std::shared_ptr<sf::Sprite>& spriteRef)
{
	// have to copy the sprite in this case to ensure that NPC's do not all share same base sprite 
	if (spriteRef.get()) {
		sf::Sprite* copy = new sf::Sprite(*spriteRef.get()->getTexture(), spriteRef.get()->getTextureRect());
		m_baseSpriteRef = std::make_shared<sf::Sprite>();
		m_baseSpriteRef.reset(copy);
		m_baseSpriteRef.get()->setOrigin(copy->getTextureRect().width / 2.0f, copy->getTextureRect().height / 2.0f);

	}
}
void Npc::setPlayerCharacterRef(Character* playerRef)
{
	m_playerCharacterRef = playerRef;
}
// update the current tile state of an npc 
void Npc::updateGridTileState(gridTile* gridTile)
{
	if (m_currentTile != gridTile) { // if the tile argument is not equal to the current tile npc is standing on 

		if (m_currentTile->worldTileRef) { // if it had a tile object
			// reset nay effects the tile had on this npc
			m_currentTile->worldTileRef->resetDynamicObjectEffect(this);
		}
		m_currentTile = gridTile; // set new tile 
	}

	if (m_currentTile->worldTileRef) { // check if any effects need to be applied from current tile 
		m_currentTile->worldTileRef->dynamicObjectEffect(this);
	}



}


// used to copy an animation controller from one npc to another
void Npc::copyAnimController(AnimationController* animationController)
{
	m_animationController = std::make_unique<AnimationController>(AnimationController(animationController, m_baseSpriteRef));

}

bool Npc::getIsActive()
{
	// an npc is active if haven't died and finished their death animation
	return !deathAnimFinished();
}
// deep copy method 
void Npc::clone(Npc* copy)
{

	copy->setDamage(m_damage);
	copy->setHealth(m_health);
	copy->setSpeed(m_speed);
	copy->setPlayerCharacterRef(m_playerCharacterRef);
	copy->setBaseSprite(m_baseSpriteRef);
	copy->copyAnimController(m_animationController.get());
	copy->setCharacterTarget(m_characterTarget);

}
// get the direction to the current waypoint the npc is moving towards taking 
//into account their current actions
void Npc::getPathDir()
{
	if (m_requestedPath.size()) {
		sf::Vector2f positionToMoveTo = m_requestedPath[0]->worldPosition;
		m_direction = normalize(positionToMoveTo - m_position);
		updateLastKnownDirection(m_direction);
		m_canAttack = false;
	}
	else {
		m_direction = sf::Vector2f(0.0f, 0.0f);

	}

	m_direction* float((!getIsAttacking()));
}

void Npc::setPath(std::vector<node*>& path)
{
	m_requestedPath = path;
	getPathDir();
}
// setters and getters for target char for npc to move towards
Character* Npc::getCharacterTarget()
{
	return m_characterTarget;
}

void Npc::setTargetPlayer()
{
	m_characterTarget = m_playerCharacterRef;
}

void Npc::setCharacterTarget(Character* character)
{
	m_characterTarget = character;

}
// setting the default booleans for when animations should trigger
// according to default animations of npc class method can be overidden
void Npc::setAnimStates()
{
	bool runAnimBool = m_direction != sf::Vector2f(0.0f, 0.0f);
	m_animationController->setState("move", runAnimBool);
	m_animationController->setState("attack", m_canAttack && m_characterTarget != nullptr && !isDead());
	m_animationController->setState("death", isDead());
	bool defaultAnimBool = (m_direction == sf::Vector2f(0.0f, 0.0f));
	m_animationController->setDefault(defaultAnimBool);
}
// every npc is assumed to have an attack idle and move anim
// however this method can be overidden by derived classes if that is not the case
void Npc::getSprites(SpriteGenerator* spriteGenerator)
{
	std::cout << "Npc base get sprites called " << std::endl;
	m_baseSpriteRef = std::make_shared<sf::Sprite>();
	m_baseSpriteRef.reset(spriteGenerator->getAnimSection(0, m_idleAnimPath));
	std::cout << "base sprite ref after getting anim section " << m_baseSpriteRef.get() << std::endl;
	m_animStates["idle"] = spriteGenerator->generateAnimationObject(m_idleAnimPath, m_baseSpriteRef, m_idleAnimDelay);
	m_animStates["move"] = spriteGenerator->generateAnimationObject(m_runAnimPath, m_baseSpriteRef, m_runAnimDelay);
	m_animStates["attack"] = spriteGenerator->generateAnimationObject(m_attackAnimPath, m_baseSpriteRef, m_attackAnimDelay);
	m_animStates["death"] = spriteGenerator->generateAnimationObject(m_deathAnimPath,m_baseSpriteRef,m_deathAnimDelay);
	
	m_animationController = std::make_unique<AnimationController>(AnimationController(m_animStates, std::string("idle")));


}

void Npc::attack(Character* target)
{
	target->takeDamage(m_damage);


}

bool Npc::characterTargetDeathCheck()
{
	if (m_characterTarget->isDead())
	{
		
		m_characterTarget = nullptr;
		m_canAttack = false;
	}
	
	return m_characterTarget == nullptr;
}

sf::Vector2f Npc::getTargetPosition()
{
	

	return m_characterTarget->getPosition();
}

bool Npc::deathAnimFinished()
{   
	
  // otherwise return if death animation has finished
	return isDead()&& (m_animationController->stateIsActive("death") && 
		   m_animationController->currentAnimAtEndNoWait());
}
