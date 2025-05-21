#include "Player.h"




Player::Player(sf::Vector2f position, SpriteGenerator *spriteGenerator,InputManager * input):Character(position)
{ 

	m_active = true;
	m_input = input;
	m_speed = m_baseSpeed;
	m_startPosition = position;
	m_currentStats = characterStats(100.0f, 15.0f, 0);
	
	// add directional maps to the input manager through its refernce
	// this allows directions to be mapped to keys 
	// such as a being the directional value of -1 etc
	m_input->addDirectionalMapping(m_vertInputMapName, m_vertcialDirectionMap); 
	m_input->addDirectionalMapping(m_horiInputMapName, m_horizontalDirectionMap);
	m_debugCircle.setFillColor(sf::Color::Blue);
	m_debugCircle.setRadius(5.0f); 
	m_debugCircle.setOrigin(5.0f / 2.0f, 5.0f / 2.0f);
	m_debugCircle.setPosition(m_position); 
	m_commandFlag = std::make_unique<StaticObject>(StaticObject(position));

	getSprites(spriteGenerator); // get sprites for player from sprite generator 
}

Player::Player(sf::Vector2f position, SpriteGenerator* spriteGenerator, InputManager* input, Camera* camera):Character(position)
{
	m_active = true;
	m_input = input;
	m_speed = m_baseSpeed;
	// set up base stats for character
    // base health, damage, gold
	m_currentStats = characterStats(100.0f, 18.0f, 0);
	m_startPosition = position;
	m_input->addDirectionalMapping(m_vertInputMapName, m_vertcialDirectionMap);
	m_input->addDirectionalMapping(m_horiInputMapName, m_horizontalDirectionMap);
	
	m_debugCircle.setFillColor(sf::Color::Blue);
	m_debugCircle.setRadius(5.0f);
	m_debugCircle.setOrigin(5.0f / 2.0f, 5.0f / 2.0f);
	m_debugCircle.setPosition(m_position);
	m_commandFlag = std::make_unique<StaticObject>(StaticObject(position));

	getSprites(spriteGenerator);
	m_camera = camera;
	camera->setPosition(m_position); // camera that willl follow player 


}
Player::Player() {
	m_speed = m_baseSpeed;



}
Player::Player(sf::Vector2f position, SpriteGenerator* spriteGenerator) :Character(position) {

	m_active = true;
	m_speed = m_baseSpeed;
	m_startPosition = position;
	m_currentStats = characterStats(100.0f, 18.0f, 0);
	m_commandFlag = std::make_unique<StaticObject>(StaticObject(position));

	getSprites(spriteGenerator); // get sprites for player from sprite generator 
};
void Player::updateCamera(){

	if (m_camera != nullptr) {
		m_camera->moveToPos(m_position);
	}
}

void Player::update(float dt)
{
	// the input manager allows certain direction values to be assigned
	//to certain keys which can be accessed through the name of the directional 
	//mapping here we are querying the input manager to get the direction 
	// the player is currently inputting 
	float dirX = m_input->getDirectionFromKey(m_horiInputMapName); 
	float dirY = m_input->getDirectionFromKey(m_vertInputMapName);
	m_direction = normalize(sf::Vector2f(dirX, dirY)); 
	flipSpriteX(m_direction.x);
	updateLastKnownDirection(m_direction);
	updateAnimStates(); 
	m_animationController->update();
	updatePosition(dt,m_CurrentLevelAreaBounds);
	updateCamera();
	updateAllyMovementOrder();
	updateCommandFlag();
	updateHitEffect();
	m_debugCircle.setPosition(m_position);
	checkReset();
	
	
	


}

int Player::getCurrentScore() const
{
	std::cout << "player current score is " << m_currentScore << std::endl;
	return m_currentScore;
}

void Player::collision(GameObject* other)
{
	
	EnemyBase* enemy = CheckObjecType<EnemyBase>(other); 
	if (enemy != nullptr) {
		// ensure that the player is attacking in the right direction for the
		// enemy to take damage
		sf::Vector2f directionToEnemy = normalize( enemy->getPosition() - m_position);
		sf::Vector2f lastKnownLookingDir = normalize(sf::Vector2f(m_lastKnownDirection.x, 0.0f));
		float attackConfirm = v2Dot(lastKnownLookingDir, directionToEnemy);
		// if attack animation is at end and attack dir has beem confirmed 
		if (m_animationController->stateIsActive("attack")
			&& m_animationController->currentAnimAtEnd() && attackConfirm>=0.0f ){
			enemy->takeDamage(m_currentStats.damage);

			if (enemy->isDead()) {
				std::cout << "increasing player score " << std::endl;
				incrementCurrentScore();

				std::cout << "new score for player " << m_currentScore << std::endl;
			}

			std::cout << "player dealt damage to enemy " << m_currentStats.damage << std::endl;
		}
    
       
	}


    

}
sf::Vector2f Player::getMousePosition() {

	if (m_camera != nullptr) {
		return  m_camera->pixelToWorldCoords(m_input->getMousePos());
	}

	return  m_input->getMousePos();

}
void Player::draw(sf::RenderWindow* window)
{
	// draw the player sprite 
	window->draw(*m_baseSpriteRef.get());
	window->draw(m_debugCircle);
	m_commandFlag->draw(window);

}
void Player::updateCommandFlag()
{
	// if the player has toggled to recall allied npc's to them 
	if (m_recallAllies) {
		m_movmentOrderPos = m_position; // set the movement order posiiton to player 
		// move the recalled command flag indciator to the correct side of the player
		// based on their last movement direction 
		float commandFlagPosX = m_position.x + (m_baseSpriteRef->getGlobalBounds().getSize().x / 2.0f) * -m_lastKnownDirection.x;
		sf::Vector2f commandFlagPos = sf::Vector2f(commandFlagPosX, m_position.y);
		// update command flag position 
		m_commandFlag->setPosition(commandFlagPos);
		return;
	}
	// other wise set command flag indicator position to players last issued
	//movement order position
	m_commandFlag->setPosition(m_movmentOrderPos);


}
// allow access to the player input manager through the player class 
bool Player::isMouseReleased(sf::Mouse::Button button) {
	return m_input->mouseReleased(button); // if mouse was released(used to register single mouse presses)

}
bool Player::isMouseDown(sf::Mouse::Button button) 
{

	return m_input->isMouseDown(button); // if mouse is being constantly held down

}


void Player::getSprites(SpriteGenerator* spriteGenerator)
{

	m_baseSpriteRef = std::make_shared<sf::Sprite>();
	m_baseSpriteRef.reset(spriteGenerator->getAnimSection(0,m_idleAnimPath));

	// set up the animation states for the niamtion controller creating various 
	// animation  objects assigned to each of the state names we want for the player (attack,movem,idle)
	
	m_animStates["idle"] = spriteGenerator->generateAnimationObject(m_idleAnimPath, m_baseSpriteRef, m_idleAnimDelay);
	m_animStates["move"] = spriteGenerator->generateAnimationObject(m_runAnimPath, m_baseSpriteRef, m_runAnimDelay);
	m_animStates["attack"] = spriteGenerator->generateAnimationObject(m_attackAnimPath, m_baseSpriteRef, m_attackAnimDelay);

	updateBaseSprite(); 
	m_commandFlag->getSprites(spriteGenerator, m_commandFlagTexturePath);
	
	m_animationController = std::make_unique<AnimationController>(AnimationController(m_animStates, std::string("idle")));
}

void Player::setCurrentLevelAreaBounds(sf::FloatRect& levelAreaBounds)
{
	m_CurrentLevelAreaBounds = levelAreaBounds;

}

sf::Vector2f Player::getMovementOrderPos()
{
	return m_movmentOrderPos;
}

void Player::incrementCurrentScore()
{
	m_currentScore++;


}

bool Player::recallingAllies() const
{
	return m_recallAllies;
}

void Player::checkAttack()
{
	
	// if the player inputs a direction cancel their attack
	if (m_direction != sf::Vector2f(0.0f, 0.0f)) {
		m_animationController->setState("attack", false);
		return;
	} 
	m_canAttack = m_input->mouseReleased(sf::Mouse::Left);
	// if the player inputs an attack continue the attack animation
	// allowing the player to buffer attack inputs by continuing to 
	//cycle the animation 
	if (m_canAttack  ) {
		// if we have reached the full end of the animation then we have finished
		m_animationController->setState("attack", m_canAttack);
		
		//std::cout << "player attack finished" << attackFinished << std::endl;
	
	}
	// if no input buffered and our attack animation has reached the 
	// end stop the player from attacking this ensures that there 
	// is no point where the player's input could be missed due to 
	// them inputting the frame the animation ends
	if (!m_canAttack && m_animationController->stateIsActive("attack")
		&& m_animationController->currentAnimAtEndNoWait()) {
		m_animationController->setState("attack", false);

	}


	
}

void Player::updateAllyMovementOrder()
{

	if (m_input->getRealTime(m_allyFollowPlayerKey)) {
		m_recallAllies = true; 
	}
	if (m_input->mouseReleased(m_allyMoveMouseButton)) {
		m_recallAllies = false; 
		m_movmentOrderPos = getMousePosition();


	}

}

void Player::updateAnimStates()
{
	bool runAnim = m_direction != sf::Vector2f(0.0f, 0.0f);

	m_animationController->setState("move", runAnim);
	checkAttack();
	
	m_animationController->setDefault(!runAnim);

}

void Player::reset()
{
	    m_currentStats.health = m_currentStats.baseHealth;
		setPosition(m_startPosition);
		
}

void Player::checkReset()
{
	if (isDead()) {
		reset();
	}
}




