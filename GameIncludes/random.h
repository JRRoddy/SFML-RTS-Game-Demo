#pragma once
#include "iostream"

inline float randomFloat(float min, float max) {

	float random = min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));

	return random;
}

inline int randomInt(int min, int max) {

	int random = min + (rand() % (max - min)); 

	return random;
	

}