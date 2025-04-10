#include "Tile.h"




Tile::Tile(){}

Tile::Tile(sf::Vector2f position):StaticObject(position){
    
       
}

Tile::Tile(sf::Vector2f position, float width, float height)
{
    m_tileVerticies.setPrimitiveType(sf::Quads); 

    m_tileVerticies[0] = sf::Vertex(sf::Vector2f(position.x - width / 2.0f, position.y - height / 2.0f), sf::Vector2f(0.0f, 0.0f));
    m_tileVerticies[1] = sf::Vertex(sf::Vector2f(position.x - width / 2.0f, position.y + height / 2.0f), sf::Vector2f(0.0f, height));
    m_tileVerticies[2] = sf::Vertex(sf::Vector2f(position.x + width / 2.0f, position.y + height / 2.0f), sf::Vector2f(width, height));
    m_tileVerticies[3] = sf::Vertex(sf::Vector2f(position.x + width / 2.0f, position.y - height / 2.0f), sf::Vector2f(width, 0.0f));

    

}

Tile::~Tile(){}
// each tile will have a player effect and therefore this method has been made virtual allowing for it to have its own 
// implmentation across each child that through dynamic linkage will be maintained when assigned to a base class refernce 
void Tile::playerEffect(Player* player){}

void Tile::resetPlayerEffect(Player* player){}



void Tile::setVerticies(float width, float height, sf::Vector2f position)
{
    m_position = position;
    m_tileVerticies.setPrimitiveType(m_primitveType);
    m_tileVerticies.resize(m_vertexCount);
    m_tileVerticies[0] = sf::Vertex(sf::Vector2f(position.x - width / 2.0f, position.y - height / 2.0f), sf::Vector2f(0.0f, 0.0f));
    m_tileVerticies[1] = sf::Vertex(sf::Vector2f(position.x - width / 2.0f, position.y + height / 2.0f), sf::Vector2f(0.0f, height));
    m_tileVerticies[2] = sf::Vertex(sf::Vector2f(position.x + width / 2.0f, position.y + height / 2.0f), sf::Vector2f(width, height));
    m_tileVerticies[3] = sf::Vertex(sf::Vector2f(position.x + width / 2.0f, position.y - height / 2.0f), sf::Vector2f(width, 0.0f));
   
}

Tile* Tile::clone(){
    // used to get a deep copy of a tile allowing for a single instance of a tile to be held in a data structure 
    // and then copied throughout them game in order to create new tiles of different types
    Tile* copy = new Tile();
    copy->setPosition(this->getPosition());
    copy->setBaseSprite(this->m_baseSpriteRef);
    return copy;
}

int Tile::getSpawnCap()
{
    return m_spawnCap;
}

void Tile::setSpawnCap(int spawnCap)
{
    m_spawnCap = spawnCap;

}

void Tile::draw(sf::RenderWindow* window)
{

    window->draw(m_tileVerticies, m_baseSpriteRef.get()->getTexture());

}

