#pragma once
#include "AreaTypes.h"
#include "Tile.h"
#include "TileDeepCopyUtil.h"
#include "SFML/Graphics/Color.hpp"
#include "imageMapColour.h"
// this class will be the main representation of the current level area the player is in 
// and has things such as tiles that are in the current area and visible to the player 
// along with its draw method(overridden from the base game object class) being used to display the background image for 
// the current area 
class LevelAreaContainer: public GameObject  {

public:

	
	LevelAreaContainer(); 
	LevelAreaContainer(SpriteGenerator* spriteGenerator);
	LevelAreaContainer(SpriteGenerator* spriteGenerator, sf::Vector2f offsetPosition, std::string backGroundTexture, sf::Vector2i gridDimensions = sf::Vector2i(2,2), sf::Vector2f sectionSize = sf::Vector2f(512.0f,512.0f));
	LevelAreaContainer(SpriteGenerator* spriteGenerator, std::vector<TileInitialiser>& randomPostionedTiles,std::map<std::string, TileInitialiser> & imageMappedTiles, std::vector < std::string> & backgroundPaths,std::vector<std::string>& tileMapPaths);
	
	virtual ~LevelAreaContainer();
	
	void draw(sf::RenderWindow* window);
	
	void getSprites(SpriteGenerator * m_spriteGenerator); 
	
	// setters and getters for background textures used when drawing the area 
	void setBackgroundTexturePaths(std::vector<std::string>& paths);
	std::vector<std::string >& getBackgroundTexturePaths();
	
	// setters and getters for the area type 
	AreaTypes getAreaType();  
	void setAreaType(AreaTypes areaType);

	//setters and getters for the tile initialisers used to generate randomly positioned tiles in area
	void setRandomlyGeneratedTiles(std::vector<TileInitialiser>& tiles);
	std::vector<TileInitialiser>& getRandomlyGeneratedTiles();
	


	// setters and getters for the paths used to load the image maps to generate tiles from an image 
	std::vector<std::string>& getTileMapPaths(); 
	void setTileMapPaths(std::vector<std::string>& tileMapPaths);

	// sets a new image map being used to generate the tile map for the area
	void setNewTileMapImage();

	// setters for images used to parse tile maps 
	std::vector<sf::Image>& getTileMapImages(); 
	void setTileMapImages(std::vector<sf::Image>& tileMapImages);

	void setImageParsedTiles(std::map<std::string, TileInitialiser>& imageParsedTiles);
	std::map<std::string, TileInitialiser>& getImageParsedTiles();
	
	// setters and getters for colour mapped to tile ids(from parsing the image map info file associated with this area)
	void setTileInfoColoursMap(std::map<imageMapColour, std::string>& tileInfocoloursMap);
	std::map<imageMapColour, std::string>& getTileInfoColourMap();

	// initialsie grid associated with area 
	void initGrid();

	void init(SpriteGenerator * spriteGenerator);
	void setDimensionsForArea(sf::Vector2i gridDimensions,sf::Vector2f tileSize); 

	//setters for dimensions of area 
	void setGridDimensions(sf::Vector2i dim);
	void setGridAreaSize(sf::Vector2f dim); 

	void initTiles(SpriteGenerator * spriteGenerator);

	sf::Vector2f getTopLeft();
	int getRandomGeneratedTilesCap();
	Tile* initNewRandomTileInArea(sf::Vector2f position,float width,float height);
	
	// methods used by deep copy utilites 
	virtual LevelAreaContainer* clone();
	virtual void clone(LevelAreaContainer* copy);

	
	virtual void getTileFromSelectedMap(int x, int y);

	//getters for full width and height the area covers  
	float getFullWidth(); 
	float getFullHeight();


	
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
	std::map<std::string,TileInitialiser>  m_imageMappedTiles; 
	std::map<imageMapColour, std::string> m_tileInfocoloursMap;
	std::vector<std::string> m_backgroundTextures;
	std::vector<std::string> m_tileMapPaths;
	std::string m_tileMapDescriptorPath;
	std::vector<sf::Image> m_loadedTileMaps;
	sf::Image m_currentTileMapImage;
	int m_generatedTilesCap = 0;
	float m_fullWidth  = 0.0f;
	float m_fullheight = 0.0f;



};