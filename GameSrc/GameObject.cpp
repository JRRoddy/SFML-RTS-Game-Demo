#include "GameObject.h"

GameObject::GameObject() {};

GameObject::GameObject(sf::Vector2f position) { 
	m_position = position; 


}

GameObject::GameObject(sf::Vector2f position, float rotation, sf::Vector2f scale)
{
	m_position = position;
	m_rotation = rotation;
	m_scale = scale; 


}

GameObject::GameObject(sf::Vector2f position, float rotation) {
	m_position = position;
	m_rotation = rotation;
	
}

GameObject::~GameObject(){}

void GameObject::updateBaseSprite()
{
	if (m_baseSpriteRef.get()!= nullptr) {
		m_baseSpriteRef.get()->setPosition(m_position);
		m_baseSpriteRef.get()->setRotation(m_rotation);
		m_baseSpriteRef.get()->setScale(m_scale);
	
	}		
	
}

void GameObject::setPosition(sf::Vector2f position)
{
	m_position = position; 

}

void GameObject::setRotation(float rotation)
{
	m_rotation = rotation; 
}

void GameObject::setScale(sf::Vector2f scale)
{
	m_scale = scale;
}

void GameObject::setBaseSprite(std::shared_ptr<sf::Sprite>& spriteRef)
{
	m_baseSpriteRef = spriteRef;
	updateBaseSprite();
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

void GameObject::update(float dt){}

void GameObject::draw(sf::RenderWindow * window)
{
	window->draw(*m_baseSpriteRef.get());
}

void GameObject::getSprites(SpriteGenerator* spriteGenerator)
{ 
	
	m_baseSpriteRef = spriteGenerator->GenerateSprite(m_texturePath);
	updateBaseSprite();
}

void GameObject::getSprites(SpriteGenerator* spriteGenerator, std::string spriteTexturePath)
{
	m_texturePath = spriteTexturePath;
	m_baseSpriteRef = spriteGenerator->GenerateSprite(m_texturePath);
	updateBaseSprite();
}









