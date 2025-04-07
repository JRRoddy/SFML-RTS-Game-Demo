#pragma once
#include "StaticObject.h"
#include "Player.h"



// base tile class for all tile objects in the game these inherit from static object obtaining 
// access to method such as set position and various properties such as rotation
class Tile: public StaticObject {

public:
	Tile() ;
	Tile(sf::Vector2f position);
	virtual ~Tile() ;
	virtual void playerEffect(Player* player);
    
	virtual Tile*clone(); 




private:
    




};



