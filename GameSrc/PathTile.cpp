#include "PathTile.h"

PathTile::PathTile(sf::Vector2f position, float width, float height ):Tile(position,width,height)
{
   

}

PathTile::PathTile(sf::Vector2f position):Tile(position)
{
}

PathTile::PathTile()
{  
	m_texturePath = "../Assets/Textures/CobblePathTile.png";
}

Tile* PathTile::clone()
{
	PathTile* copy = new PathTile(); 

	Tile::clone(copy);

	return copy;
}

void PathTile::playerEffect(Player* player)
{
}

void PathTile::resetPlayerEffect(Player* player)
{
}
