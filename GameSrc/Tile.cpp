#include "Tile.h"




Tile::Tile(){}

Tile::Tile(sf::Vector2f position):StaticObject(position){
    
       
}

Tile::~Tile(){}
// each tile will have a player effect and therefore this method has been made virtual allowing for it to have its own 
// implmentation across each child that through dynamic linkage will be maintained when assigned to a base class refernce 
void Tile::playerEffect(Player* player){
    std::cout << "base tile effect called " << std::endl;
}

Tile* Tile::clone(){
    // used to get a deep copy of a tile allowing for a single intance of a tile to be held in a data structure 
    // and then copied throughout them game in order to create new tiles of different types
    Tile* copy = new Tile();
    copy->setPosition(this->getPosition());
    copy->setBaseSprite(this->m_baseSpriteRef);


    return copy;
}

