#pragma once
#include "SFML/Graphics.hpp"
#include "SpriteGenerator.h"
class GameObject {

public:

	GameObject();
	GameObject(sf::Vector2f position, float rotation);
	GameObject(sf::Vector2f position);
	~GameObject();

	void setPosition(sf::Vector2f position);
	void setRotation(float rotation); 
	void setScale(sf::Vector2f scale);
	sf::Vector2f getScale();
	sf::Vector2f getPosition();
	float getRotation();
	// virtual functions to update and draw the object allowing for different methods of vertices for drawing i.e vertcies or using the sfml shape classes
	// update will define what the game object will be doing during 
	virtual void update(float dt);
	virtual void draw(sf::RenderWindow * window);
	virtual void getSprites(SpriteGenerator* spriteGenerator);
protected: 
	sf::Vector2f m_position = sf::Vector2f(0.0f,0.0f);
	sf::Vector2f m_scale = sf::Vector2f(1.0f, 1.0f);
	float m_rotation = 0.0f; 
	std::shared_ptr<sf::Sprite> m_baseSpriteRef;
	




};



