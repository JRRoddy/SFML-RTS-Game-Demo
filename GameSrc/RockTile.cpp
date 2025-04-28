#include "RockTile.h"

RockTile::RockTile(sf::Vector2f position, float width, float height) :Tile(position, width, height)
{


}

RockTile::RockTile(sf::Vector2f position) :Tile(position)
{
}

RockTile::RockTile()
{
	m_texturePath = "../Assets/Textures/RockTile.png";
	m_spawnCap = 4;
	m_rowCap = 2;
	m_walkable = false;
}

Tile* RockTile::clone()
{
	RockTile* copy = new RockTile();
	
	Tile::clone(copy);

	return copy;
}

void RockTile::dynamicObjectEffect(DynamicObject* object)
{

	

}

void RockTile::resetDynamicObjectEffect(DynamicObject* object)
{
}
