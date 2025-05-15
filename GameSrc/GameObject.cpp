#include "GameObject.h"

GameObject::GameObject() 
{
  
};

GameObject::GameObject(sf::Vector2f position) { 
	m_position = position; 

}


GameObject::GameObject(sf::Vector2f position, float rotation, sf::Vector2f scale)
{
	m_position = position;
	m_rotation = rotation;
	m_scale = scale; 


}

GameObject::GameObject(sf::Sprite *sprite)
{
	sprite->setOrigin(sf::Vector2f(sprite->getTextureRect().getSize() / 2));
	m_position = sprite->getPosition();
	
	m_baseSpriteRef.reset(sprite);


}

GameObject::GameObject(sf::Vector2f position, float rotation) {
	m_position = position;
	m_rotation = rotation;
	
}


// updates the current assigned sprites properties 
// such as position and rotation if it has been assigned
void GameObject::updateBaseSprite()
{
	if (m_baseSpriteRef.get()!= nullptr) {
		// set sprite properties
		m_baseSpriteRef.get()->setPosition(m_position);
		m_baseSpriteRef.get()->setRotation(m_rotation);
		m_baseSpriteRef.get()->setScale(m_scale);
	    
	}		
	
}

void GameObject::setPosition(sf::Vector2f position)
{
	m_position = position; 
	updateBaseSprite();
}

void GameObject::setRotation(float rotation)
{
	m_rotation = rotation; 
}

void GameObject::setScale(sf::Vector2f scale)
{
	m_scale = scale;
}

void GameObject::setCollisionBounds(sf::IntRect& newBounds)
{
	m_baseSpriteRef->setTextureRect(newBounds);
}

int GameObject::getSpawnCap()
{
	return m_spawnCap;
}

void GameObject::setIsActive(bool isActive)
{
	m_active = isActive;

}

bool GameObject::getIsActive()
{
	return m_active;
}

void GameObject::setBaseSprite(std::shared_ptr<sf::Sprite>& spriteRef)
{
	m_baseSpriteRef = spriteRef;
}

sf::Vector2f GameObject::getScale()
{
	return m_scale;
}

sf::Vector2f GameObject::getPosition()
{
	return m_position;
}

float GameObject::getRotation()
{
	return m_rotation;
}

sf::Sprite* GameObject::getBaseSprite()
{
	return m_baseSpriteRef.get();
}

sf::FloatRect GameObject::getBounds()
{
	return m_baseSpriteRef.get()->getGlobalBounds();
}

// flip the sprite in x depending on the passed in direction value
void GameObject::flipSpriteX(float direction)
{   
	if (direction == 0.0f) {
		return;
	}

	float dir = direction < 0.0f ? -1.0f : 1.0f;

	sf::Sprite* sprite = m_baseSpriteRef.get();
	// update current scale of game object based on current direction scalar
	m_scale = sf::Vector2f(abs(sprite->getScale().x) *dir, sprite->getScale().y);
	m_baseSpriteRef.get()->setScale(m_scale);


}


void GameObject::update(float dt){}

void GameObject::draw(sf::RenderWindow * window)
{
	updateBaseSprite();
	window->draw(*m_baseSpriteRef.get());
	window->draw(m_debugCircle);
}

// base get sprites method used across all children 
// to generate and assign their sprites from the sprite generator 
// instance 
void GameObject::getSprites(SpriteGenerator* spriteGenerator)
{ 
	m_baseSpriteRef = spriteGenerator->GenerateSprite(m_texturePath);
}
// overload for get sprites 
void GameObject::getSprites(SpriteGenerator* spriteGenerator, std::string spriteTexturePath)
{
	m_texturePath = spriteTexturePath;
	m_baseSpriteRef = spriteGenerator->GenerateSprite(m_texturePath);
}









