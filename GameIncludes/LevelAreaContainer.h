#pragma once
#include "AreaTypes.h"
#include "Tile.h"
#include "TileDeepCopyUtil.h"
#include "SFML/Graphics/Color.hpp"
// this class will be the main representation of the current level area the player is in 
// and has things such as tiles that are in the current area and visible to the player 
// along with its draw method(overridden from the base game object class) being used to display the background image for 
// the current area 
class LevelAreaContainer: public GameObject  {

public:

	
	LevelAreaContainer(); 
	LevelAreaContainer(SpriteGenerator* spriteGenerator);
	LevelAreaContainer(SpriteGenerator* spriteGenerator, sf::Vector2f offsetPosition, std::string backGroundTexture, sf::Vector2i gridDimensions = sf::Vector2i(2,2), sf::Vector2f sectionSize = sf::Vector2f(512.0f,512.0f));
	LevelAreaContainer(SpriteGenerator* spriteGenerator, std::vector<TileInitialiser>& randomPostionedTiles, std::vector < std::string> & backgroundPaths);
	
	
	void draw(sf::RenderWindow* window);
	void getSprites(SpriteGenerator * m_spriteGenerator); 
	void setBackgroundTexturePaths(std::vector<std::string>& paths);
	AreaTypes getType();  
	void setAreaType(AreaTypes areaType);
	virtual ~LevelAreaContainer(); 
	void setRandomlyGeneratedTiles(std::vector<TileInitialiser>& tiles);
	void setMappedTiles(std::map<const sf::Color,TileInitialiser>& tiles);
	void initGrid();
	void initTiles(SpriteGenerator * spriteGenerator);
	void setDimensionsForArea(sf::Vector2i gridDimensions,sf::Vector2f tileSize); 
	void setGridDimensions(sf::Vector2i dim);
	void setGridAreaSize(sf::Vector2f dim); 
	void setBackgroundTextures(std::vector<std::string>& backgroundTexturePaths);
	sf::Vector2f getTopLeft();
	int getRandomGeneratedTilesCap();
	Tile* initNewRandomTileInArea(sf::Vector2f position,float width,float height);
	virtual LevelAreaContainer* clone();



	
protected:
	
	 
	//std::vector<LevelArea> m_areaPool; 

	std::vector<Tile* > m_worldTiles ;
	sf::VertexArray m_tileVertecies;
	sf::VertexArray m_backgroundVertecies;
	sf::Vector2f m_centre;
	sf::Vector2f m_topLeft;
	int m_tileVertexCount = 4;
	sf::PrimitiveType tilePrimitiveType = sf::Quads;
	sf::Vector2i m_gridDimensions;
	sf::Vector2f m_gridSectionSize;
	AreaTypes m_areaType = NONE;
	std::vector<TileInitialiser>  m_randomPositionedTiles;
	std::map<const sf::Color, TileInitialiser> m_mappedTiles;
	std::vector<std::string> m_backgroundTextures;
	int m_generatedTilesCap = 0;




};