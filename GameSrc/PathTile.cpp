#include "PathTile.h"

PathTile::PathTile(sf::Vector2f position, float width, float height ):Tile(position,width,height)
{
	
	
}

PathTile::PathTile(sf::Vector2f position):Tile(position)
{
}

PathTile::PathTile()
{  
	m_speedModifier = 1.25f;
	m_texturePath = "../Assets/Textures/CobblePathTile.png";
}

Tile* PathTile::clone()
{
	PathTile* copy = new PathTile(); 

	Tile::clone(copy);

	return copy;
}

void PathTile::dynamicObjectEffect(DynamicObject* object)
{
	object->setSpeedModfier(m_speedModifier);
}

void PathTile::resetDynamicObjectEffect(DynamicObject* object)
{
	object->resetSpeedModifier();

}
