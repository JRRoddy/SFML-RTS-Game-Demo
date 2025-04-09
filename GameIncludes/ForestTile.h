#pragma once
#include "Tile.h"
class ForestTile : public Tile {
public: 
	  ForestTile(sf::Vector2f position,float width, float height);
	  ForestTile();
	  Tile* clone() override;
	  void playerEffect(Player * player)override;
	  
private:


};