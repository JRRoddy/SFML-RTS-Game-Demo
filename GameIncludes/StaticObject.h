#pragma once
#include "GameObject.h"

class StaticObject : public GameObject { // a game object class that will be used to represent objects that have no mobility in the world
public:
	StaticObject() {};
	StaticObject(sf::Vector2f position);
	~StaticObject();
  

};


