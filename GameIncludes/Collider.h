#include "SFML/Graphics.hpp"
class Collider {
public:

	Collider(){};
	~Collider(){};
	Collider(sf::Vector2f position, sf::Vector2f sizeDim);
	void updatePosition(sf::Vector2f newCentre);
	void draw(sf::RenderWindow* window);
private:
	sf::Vector2f m_sizeDim;
	sf::RectangleShape m_debugDraw;
	sf::Vector2f m_position; 
	sf::FloatRect m_bounds;
	float m_boundsWidth = 0.0f; 
	float m_boundsHeight = 0.0f;
	bool enabled = true;

};