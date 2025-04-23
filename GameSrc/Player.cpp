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
	updatePosition(dt);
	updateCamera();
	m_debugCircle.setPosition(m_position);
	
	


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
bool Player::isMouseReleased(sf::Mouse::Button button) {
	return m_input->mouseReleased(button);

}
bool Player::isMouseDown(sf::Mouse::Button button) 
{

	return m_input->isMouseDown(button);

}
void Player::getSprites(SpriteGenerator* spriteGenerator)
{
	m_idleAnim = spriteGenerator->GenerateAnim(m_idleAnimPath);

	m_baseSpriteRef = *m_idleAnim.data();  

	updateBaseSprite();
	
}









