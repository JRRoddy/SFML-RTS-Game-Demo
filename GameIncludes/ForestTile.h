#pragma once
#include "Tile.h"
class ForestTile : public Tile {
public: 
	  ForestTile(sf::Vector2f position,float width, float height);
	  ForestTile(sf::Vector2f position);
	  ForestTile();
	  Tile* clone() override;
	  void playerEffect(Player * player)override;
	  void resetPlayerEffect(Player* player)override;
private:
	float m_playerSpeedModifer = 0.75f;



};