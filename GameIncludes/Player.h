#pragma once
#include "DynamicObject.h"
class Player: public DynamicObject {
 public:
	Player();
	Player(sf::Vector2f position);
	Player(float speed,sf::Vector2f position);
	Player(float speed, float damage); 
	void setDamage(float damage);
	float getDamage();

 private:
	 float m_damage = 0.0f;
	 



};