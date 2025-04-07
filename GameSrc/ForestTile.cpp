#include "ForestTile.h"



ForestTile::ForestTile(sf::Vector2f position):Tile(position)
{
}

Tile* ForestTile::clone()
{

    ForestTile* copy = new ForestTile();
    copy->setPosition(this->getPosition());
    copy->setBaseSprite(this->m_baseSpriteRef);
    
    return copy;
}

void ForestTile::playerEffect(Player* player)
{
    std::cout << "forest tile PLAYER EFFECT called" << std::endl;
}
