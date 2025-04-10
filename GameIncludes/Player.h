#pragma once
#include "DynamicObject.h"
#include "InputManager.h"

class Player: public DynamicObject {
 public:
	Player();
	Player(sf::Vector2f position, SpriteGenerator * spriteGenerator,InputManager * input);
	void setDamage(float damage);
	float getDamage();
	void update(float dt);
	void getSprites(SpriteGenerator * spriteGenerator); 

 private:
	 float m_damage = 0.0f;
	 float m_baseSpeed = 300.0f;
	 InputManager* m_input = nullptr;
	 std::vector<std::shared_ptr< sf::Sprite>> m_idleAnim; 
	 std::string m_idleAnimPath = "../Assets/Animations/KnightIdleBlue.png";
	 std::string m_vertInputMapName = "playerVertical"; 
	 std::string m_horiInputMapName = "playerHorizontal";
	 std::map<sf::Keyboard::Key, float> m_vertcialDirectionMap = { {sf::Keyboard::W,-1.0f},{sf::Keyboard::S,1.0f} };
	 std::map<sf::Keyboard::Key, float> m_horizontalDirectionMap = { {sf::Keyboard::A,-1.0f},{sf::Keyboard::D,1.0f} };

	 


};