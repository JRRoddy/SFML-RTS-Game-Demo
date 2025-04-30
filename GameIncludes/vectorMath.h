#pragma once
#include "SFML/Graphics.hpp" 

#ifndef VECTOR_MATH
#define VECTOR_MATH

inline sf::Vector2f normalize(sf::Vector2f& vector) {
	float lenght = sqrt((vector.x * vector.x + vector.y * vector.y));

	if (lenght == 0.0f) {// prevents divide by 0
		return sf::Vector2f(0.0f, 0.0f);
	}

	return sf::Vector2f(vector.x / lenght, vector.y / lenght);
}

inline float v2Dot(sf::Vector2f left, sf::Vector2f right) {

	return left.x * right.x + left.y * right.y;
}

#endif // !VECTOR_MATH





