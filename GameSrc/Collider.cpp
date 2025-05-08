#include "Collider.h"

Collider::Collider(sf::Vector2f position, sf::Vector2f sizeDim)
{
	m_position = position; 
	m_boundsWidth = sizeDim.x;
	m_boundsHeight = sizeDim.y; 
	m_sizeDim = sizeDim;

	m_bounds = sf::FloatRect(position.x - m_boundsWidth/2.0f, position.y - m_boundsHeight/2.0f, m_boundsWidth, m_boundsHeight);

	m_debugDraw.setSize(sizeDim);
	m_debugDraw.setPosition(position);
	m_debugDraw.setOutlineColor(sf::Color::Blue);
	m_debugDraw.setOrigin(m_sizeDim / 2.0f);
	m_debugDraw.setOutlineThickness(2.0f);
	

	




}

void Collider::updatePosition(sf::Vector2f newCentre)
{
	m_bounds.left = newCentre.x - m_boundsWidth / 2.0f;
	m_bounds.top = newCentre.y - m_boundsHeight / 2.0f;
	m_debugDraw.setPosition(newCentre);

}

void Collider::draw(sf::RenderWindow* window)
{
	window->draw(m_debugDraw);
}
