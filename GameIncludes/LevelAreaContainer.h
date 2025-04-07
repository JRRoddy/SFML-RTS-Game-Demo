#pragma once
#include "AreaTypes.h"
#include "Tile.h"
#include "TileDeepCopyUtil.h"

// this class will be the main representation of the current level area the player is in 
// and has things such as tiles that are in the current area and visbilie to the player 
// along with its draw method(overridden from the base game object class) being used to display the background image for 
// the current area 
class LevelAreaContainer: public GameObject  {

public:

	LevelAreaContainer(SpriteGenerator* spriteGenerator, sf::Vector2f offsetPosition, AreaTypes  areaType, std::string backGroundTexture, sf::Vector2i gridDimensions, sf::Vector2f sectionSize);
	void draw(sf::RenderWindow* window);
	void getSprites(SpriteGenerator * m_spriteGenerator,std::string spriteTexturePath);
	virtual Tile * initWorldTileFixed(sf::Vector2f position);
	virtual Tile * initWorldTileRandom(sf::Vector2f position);
	AreaTypes getType(); 


private:

	 
	//std::vector<LevelArea> m_areaPool; 

	std::vector<std::unique_ptr<Tile>>m_areaTiles; 
	
	sf::VertexArray m_tileVertecies;
	sf::VertexArray m_backgroundVertecies;
	sf::Vector2f m_centre;
	sf::Vector2f m_topLeft;
	int m_tileVertexCount = 4;
	sf::PrimitiveType tilePrimitiveType = sf::Quads;
	sf::Vector2i m_gridDimensions;
	sf::Vector2f m_gridSectionSize;
	AreaTypes m_areaType;
	
	
};