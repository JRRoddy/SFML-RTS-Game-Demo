#include "ForestTile.h"



ForestTile::ForestTile(sf::Vector2f position, float width, float height ):Tile(position,width,height)
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
    std::cout << "clone forest location " << copy << "clone forest type " << typeid(*copy).name() << std::endl;
    return copy;
}

void ForestTile::playerEffect(Player* player)
{
    std::cout << "forest tile PLAYER EFFECT called" << std::endl;
}
