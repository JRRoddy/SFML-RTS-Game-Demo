#pragma once
#include "DynamicObject.h"
#include "InputManager.h"
#include "vectorMath.h"
class Player: public DynamicObject {
 public:
	Player(sf::Vector2f position, InputManager * input);
	void setDamage(float damage);
	float getDamage();
	void update(float dt);

 private:
	 float m_damage = 0.0f;
	 float m_baseSpeed = 3.0f;
	 InputManager* m_input;
	 
	 std::string m_vertInputMapName = "playerVertical"; 
	 std::string m_horiInputMapName = "playerHorizontal";
	 std::map<sf::Keyboard::Key, float> m_vertcialDirectionMap = { {sf::Keyboard::W,-1.0f},{sf::Keyboard::S,1.0f} };
	 std::map<sf::Keyboard::Key, float> m_horizontalDirectionMap = { {sf::Keyboard::A,-1.0f},{sf::Keyboard::D,1.0f} };

	 


};