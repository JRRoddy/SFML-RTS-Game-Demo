#pragma once
#include "SFML/Graphics.hpp"
class Camera {

public:

	Camera(sf::RenderWindow * window,sf::FloatRect & initialArea);
	~Camera() {};
	void setWindow(sf::RenderWindow* window);
	void setPosition(sf::Vector2f& centrePos);
	sf::Vector2f pixelToWorldCoords(sf::Vector2f &position);
	sf::Vector2f worldToPixelCoords(sf::Vector2f& position);
	void resSize(sf::FloatRect& newView);
	void moveToPos(sf::Vector2f& pos);
	sf::View& getView();

private:
	sf::View m_cameraView;
	sf::RenderWindow* m_window;
};