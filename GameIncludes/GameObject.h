#pragma once
#include "SFML/Graphics.hpp"
#include "SpriteGenerator.h"
#include "vectorMath.h"


// base game object class that will be used to provide functionaility across all the objects wihtin the game 
// that being things such as setting the position or scale of the object reducing the amount of code duplication 
class GameObject {

public:

	GameObject();
	GameObject(sf::Vector2f position, float rotation);
	GameObject(sf::Vector2f position);
	GameObject(sf::Vector2f position, float rotation,sf::Vector2f scale);
	GameObject(sf::Sprite *sprite);
	virtual ~GameObject() {};
	void updateBaseSprite();
	void setPosition(sf::Vector2f position);
	void setRotation(float rotation); 
	void setScale(sf::Vector2f scale);
	int getSpawnCap(); 
	void setIsActive(bool isActive);
	virtual bool getIsActive();
	virtual void setBaseSprite(std::shared_ptr<sf::Sprite>& spriteRef);
	sf::Vector2f getScale();
	sf::Vector2f getPosition();
	float getRotation();
	sf::Sprite* getBaseSprite();
	sf::FloatRect getBounds();
	void flipSpriteX(float direction);

	// virtual functions to update and draw the object allowing for different methods of vertices for drawing i.e vertcies or using the sfml shape classes
	// update will define what the game object will be doing during 
	virtual void collision(GameObject* other) {};
	virtual void collisionResponse(GameObject* other) {};
	virtual void reset() {};
	virtual void update(float dt);
	virtual void draw(sf::RenderWindow * window) ;
	virtual void getSprites(SpriteGenerator* spriteGenerator);
	virtual void getSprites(SpriteGenerator* spriteGenerator, std::string spriteTexturePath);
	
protected: 
	sf::CircleShape m_debugCircle;
	sf::Vector2f m_position = sf::Vector2f(0.0f,0.0f);
	sf::Vector2f m_scale = sf::Vector2f(1.0f, 1.0f);
	float m_rotation = 0.0f; 
	std::shared_ptr<sf::Sprite> m_baseSpriteRef;
	std::string m_texturePath;
	bool m_active = false;
	int m_spawnCap = 0;
	




};



