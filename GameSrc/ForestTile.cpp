#include "ForestTile.h"



ForestTile::ForestTile(sf::Vector2f position, float width, float height ):Tile(position,width,height)
{
   

}

ForestTile::ForestTile(sf::Vector2f position):Tile(position)
{
}

ForestTile::ForestTile()
{  
    m_texturePath = "../Assets/Textures/ForestTile.png";
    m_spawnCap = 20;
    m_rowCap = 3; 
    m_speedModifier = 0.75f;
}

Tile* ForestTile::clone()
{

    ForestTile* copy = new ForestTile();
    Tile::clone(copy);
    return copy;
}

void ForestTile::dynamicObjectEffect(DynamicObject* object)
{
    object->setSpeedModfier(m_speedModifier);
}

void ForestTile::resetDynamicObjectEffect(DynamicObject* object)
{
    object->resetSpeedModifier();

}
