#include "Tile.h"

Tile::Tile(){}



Tile::Tile(sf::Vector2f position):StaticObject(position){
    
       
}

Tile::Tile(sf::Vector2f position, float width, float height):StaticObject(position)
{
    // set up vertcies for this tile based on width and height
    m_width = width;
    m_height = height;
    m_tileVerticies.setPrimitiveType(sf::Quads); 

    m_tileVerticies[0] = sf::Vertex(sf::Vector2f(position.x - width / 2.0f, position.y - height / 2.0f), sf::Vector2f(0.0f, 0.0f));
    m_tileVerticies[1] = sf::Vertex(sf::Vector2f(position.x - width / 2.0f, position.y + height / 2.0f), sf::Vector2f(0.0f, height));
    m_tileVerticies[2] = sf::Vertex(sf::Vector2f(position.x + width / 2.0f, position.y + height / 2.0f), sf::Vector2f(width, height));
    m_tileVerticies[3] = sf::Vertex(sf::Vector2f(position.x + width / 2.0f, position.y - height / 2.0f), sf::Vector2f(width, 0.0f));

    

}

Tile::~Tile(){}

sf::FloatRect Tile::getBounds()
{


    return sf::FloatRect(sf::Vector2f(m_position - sf::Vector2f(m_width,m_height)/2.0f),sf::Vector2f(m_width,m_height));
}




void Tile::setVerticies(float width, float height, sf::Vector2f position)
{
    // set up vertcies for this tile ot be drawn
    m_width = width; 
    m_height = height;
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
    copy->setPosition(this->getPosition());
    copy->setBaseSprite(this->m_baseSpriteRef);
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

bool Tile::isWalkable() const
{
    return m_walkable;
}

void Tile::setIsWalkable(bool walkable)
{
    m_walkable = walkable;
}

float Tile::getWidth() const
{
    return m_width;
}
float Tile::getHeight() const
{
    return m_height;
}

void Tile::setHeight(float& height) {
    m_height = height;
}
void Tile::setWidth(float& width) {
    m_width = width;
}
