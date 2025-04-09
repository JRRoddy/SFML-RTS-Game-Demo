#pragma once
#include "SFML/Graphics.hpp" 



sf::Vector2f normalize(sf::Vector2f& vector) {
	float lenght = sqrt((vector.x * vector.x + vector.y * vector.y)); 
	return sf::Vector2f(vector.x / lenght, vector.y / lenght);
}



