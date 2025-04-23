#pragma once
#include "Tile.h"
class ForestTile : public Tile {
public: 
	  ForestTile(sf::Vector2f position,float width, float height);
	  ForestTile(sf::Vector2f position);
	  ForestTile();
	  Tile* clone() override;
	  void  dynamicObjectEffect(DynamicObject * player)override;
	  void resetDynamicObjectEffect(DynamicObject* player)override;
private:



};