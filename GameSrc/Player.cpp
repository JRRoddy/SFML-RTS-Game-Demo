#include "Player.h"


Player::Player(){}

Player::Player(sf::Vector2f position, SpriteGenerator *spriteGenerator,InputManager * input):Character(position)
{ 

	m_active = true;
	m_input = input;
	m_speed = m_baseSpeed;
	m_damage = 30.0f;

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
	std::cout <<"camera view" <<camera->getView().getCenter().x<<":"<< camera->getView().getCenter().y << std::endl;


}

void Player::updateCamera(){

	if (m_camera != nullptr) {

		m_camera->moveToPos(m_position);


	}
}





void Player::update(float dt)
{

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
	m_debugCircle.setPosition(m_nextPos);
	
	
	
	


}

void Player::collision(GameObject* other)
{
	
    

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
	window->draw(*m_commandFlag->getBaseSprite());

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

bool Player::recallingAllies() const
{
	return m_recallAllies;
}

bool Player::checkAttack()
{

	if (m_direction != sf::Vector2f(0.0f, 0.0f)) {
		m_canAttack = false; 
		m_attackFinished = false;
		return false;
	}

	// check if the player has inputted to attack 
	if (m_input->mouseReleased(sf::Mouse::Left) ) {

		m_canAttack = true;
	}
	// if they can attack update the current state of the attack
	if (m_canAttack) {
		// if we have reached the full end of the animation then we have finished
		m_attackFinished = m_animationController->currentAnimAtEnd(); 
		// the player is not attacking the frame after they've finished swinging 
		m_canAttack = !m_attackFinished;
	}
	// if the player has not completed the attack and can attack they are attacking 
	return m_canAttack && !m_attackFinished;
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
	m_animationController->setState("attack", checkAttack());
	
	m_animationController->setDefault(!runAnim);

}




