#include "Tile.h"

Tile::Tile(){}



Tile::Tile(sf::Vector2f position):StaticObject(position){
    
       
}

Tile::Tile(sf::Vector2f position, float width, float height)
{
    // set up vertcies for this tile based on width and height
    m_tileVerticies.setPrimitiveType(sf::Quads); 

    m_tileVerticies[0] = sf::Vertex(sf::Vector2f(position.x - width / 2.0f, position.y - height / 2.0f), sf::Vector2f(0.0f, 0.0f));
    m_tileVerticies[1] = sf::Vertex(sf::Vector2f(position.x - width / 2.0f, position.y + height / 2.0f), sf::Vector2f(0.0f, height));
    m_tileVerticies[2] = sf::Vertex(sf::Vector2f(position.x + width / 2.0f, position.y + height / 2.0f), sf::Vector2f(width, height));
    m_tileVerticies[3] = sf::Vertex(sf::Vector2f(position.x + width / 2.0f, position.y - height / 2.0f), sf::Vector2f(width, 0.0f));

    

}

Tile::~Tile(){}




void Tile::setVerticies(float width, float height, sf::Vector2f position)
{
    // set up vertcies for this tile ot be drawn
    m_position = position;
    m_tileVerticies.setPrimitiveType(m_primitveType);
    m_tileVerticies.resize(m_vertexCount);
    m_tileVerticies[0] = sf::Vertex(sf::Vector2f(position.x - width / 2.0f, position.y - height / 2.0f), sf::Vector2f(0.0f, 0.0f));
    m_tileVerticies[1] = sf::Vertex(sf::Vector2f(position.x - width / 2.0f, position.y + height / 2.0f), sf::Vector2f(0.0f, height));
    m_tileVerticies[2] = sf::Vertex(sf::Vector2f(position.x + width / 2.0f, position.y + height / 2.0f), sf::Vector2f(width, height));
    m_tileVerticies[3] = sf::Vertex(sf::Vector2f(position.x + width / 2.0f, position.y - height / 2.0f), sf::Vector2f(width, 0.0f));
   
}


// used for deep copying tiles
void Tile::clone(Tile* copy)
{


    copy->setPosition(this->m_position);
    copy->setBaseSprite(this->m_baseSpriteRef);
    copy->setSpawnCap(this->m_spawnCap);
    copy->setSpeedModifier(this->m_speedModifier);
}


// get number of tiles that can spawn by chance on a singular row
int Tile::getRowCap()
{
    return m_rowCap;
}

void Tile::setSpawnCap(int spawnCap)
{
    m_spawnCap = spawnCap;

}

void Tile::draw(sf::RenderWindow* window)
{
    // draw tile verts
    window->draw(m_tileVerticies, m_baseSpriteRef.get()->getTexture());

}

void Tile::setSpeedModifier(float speedMod)
{
    // set any movement effects of this tile
    m_speedModifier = speedMod;
}

