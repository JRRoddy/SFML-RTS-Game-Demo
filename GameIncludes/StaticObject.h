#pragma once
#include "GameObject.h"

// using virtual in heritance for the game object here to ensure that only one instance of inheriatnce 
// when it comes to the classes such as the npc class that can be both dynamic and static
class StaticObject : public virtual GameObject { // a game object class that will be used to represent objects that have no mobility in the world
public:
	StaticObject() {};
	StaticObject(sf::Vector2f position);
	
	StaticObject(sf::Sprite* sprite);
	virtual ~StaticObject();
     

};


