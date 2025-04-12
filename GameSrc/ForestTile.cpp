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
}

Tile* ForestTile::clone()
{

    ForestTile* copy = new ForestTile();
    Tile::clone(copy);
    return copy;
}

void ForestTile::playerEffect(Player* player)
{
    player->setSpeedModfier(m_playerSpeedModifer);
}

void ForestTile::resetPlayerEffect(Player* player)
{
    player->resetSpeedModifier();

}
