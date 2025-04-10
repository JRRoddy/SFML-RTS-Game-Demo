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
    copy->setPosition(this->m_position);
    copy->setBaseSprite(this->m_baseSpriteRef);
    copy->setSpawnCap(this->m_spawnCap);
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
