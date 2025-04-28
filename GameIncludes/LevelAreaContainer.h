#pragma once
#include "AreaTypes.h"
#include "Tile.h"
#include "TileDeepCopyUtil.h"
#include "SFML/Graphics/Color.hpp"
#include "imageMapColour.h"
#include "EnemyInitialsier.h"
#include "AllyInitialiser.h"
#include "random.h"
#include "collisionHandler.h"

// this class will be the main representation of the current level area the player is in 
// and has things such as tiles that are in the current area and visible to the player 
// along with its draw method(overridden from the base game object class) being used to display the background image for 
// the current area its main responsibility is storing data associated with level areas and processing the data when needed  

class LevelAreaContainer: public GameObject  {

public:

	
	LevelAreaContainer(); 
	LevelAreaContainer(SpriteGenerator* spriteGenerator);
	LevelAreaContainer(SpriteGenerator* spriteGenerator, sf::Vector2f offsetPosition, std::string backGroundTexture, sf::Vector2i gridDimensions = sf::Vector2i(2,2), sf::Vector2f sectionSize = sf::Vector2f(512.0f,512.0f));

	// constructor for initialsing alll data associated with particualr area
	LevelAreaContainer(SpriteGenerator* spriteGenerator, std::vector<TileInitialiser>& randomPostionedTiles,std::map<std::string, TileInitialiser> & imageMappedTiles, std::vector < std::string> & backgroundPaths,std::vector<std::string>& tileMapPaths);
	
	virtual ~LevelAreaContainer();
	
	void draw(sf::RenderWindow* window);
	
	void getSprites(SpriteGenerator * m_spriteGenerator); 
	void setMaxAllySpawnCap(int spawnCap);

	// setters and getters for background textures used when drawing the area 
	void setBackgroundTexturePaths(std::vector<std::string>& paths);

	std::vector<std::string >& getBackgroundTexturePaths();
	
	bool testForUnwalkableTileCollisions(sf::Vector2f &pos);
	// setters and getters for the area type 
	AreaTypes getAreaType();  
	void setAreaType(AreaTypes areaType);

	//setters and getters for the tile initialisers used to generate randomly positioned tiles in area
	void setRandomlyGeneratedTiles(std::vector<TileInitialiser>& tiles);
	std::vector<TileInitialiser> getRandomlyGeneratedTiles();
	
	
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
	sf::FloatRect getBounds();
	// initialsie grid associated with area 
	void initGrid();

	void init(SpriteGenerator * spriteGenerator);
	void setDimensionsForArea(sf::Vector2i &gridDimensions,sf::Vector2f &tileSize); 

	//setters for dimensions of area 
	void setGridDimensions(sf::Vector2i &dim);
	void setGridAreaSize(sf::Vector2f &dim); 

	void initTiles(SpriteGenerator * spriteGenerator);
	void initLevelMaps();
	sf::Vector2f getTopLeft();

	sf::Vector2f getRandomPosition() const;
	sf::Vector2f getRandomEdgePosition()const;
	sf::Vector2f getRandomEdgePosition(sf::FloatRect boundsToAccomodate) const;
	int getRandomGeneratedTilesCap();
	void setRandomGeneratedTilesCap(int cap);
	Tile* initNewRandomTileInArea(sf::Vector2f position,float width,float height);
	
	//get a spawn position for an enemy wihtin the area 
	// can be overidden by child classses of this area for custom spawn mechanics for specific 
	//areas 
	// methods used by deep copy utilites 
	virtual LevelAreaContainer* clone();
	virtual void clone(LevelAreaContainer* copy);

	// intialise world tile from image map 
	Tile* initTileFromSelectedMap(sf::Vector2i imageMapTexcoords, sf::Vector2f position, float width, float height);

	// get enemy initialisers associated with area
	std::vector<EnemyInitialiser>& getEnemyIntialisers();
	std::vector<AllyInitialiser>& getAllyIntialisers();
	void initCollisionTree(int maxCollisionTreeDepth);
	void setEnemyIntialisers(std::vector<EnemyInitialiser>& enemyInitialisers); 
	void setAllyInitialisers(std::vector<AllyInitialiser>& allyInitalisers);
	float getRandomSpawnDelay();
	virtual sf::Vector2f getEnemySpawnPosition(GameObject* Enemy);
	void setSpawnDelays(float &min, float& max);
	//getters for full width and height the area covers  
	float getFullWidth(); 
	float getFullHeight();
	float &getSpawnDelayMin();
	float &getSpawnDelayMax();
	float &getAllyRefreshCoolDown();
	void setAllyRefreshCoolDown(float& coolDown);
	int   &getMaxAllyCap();
	sf::Vector2f getWorldDimensions();

	
	
protected:
	
	std::vector<Tile* > m_worldTiles;

	sf::VertexArray m_tileVertecies; 
	sf::VertexArray m_backgroundVertecies;

	sf::Vector2f m_centre; // centre position of area
	sf::Vector2f m_topLeft;
	sf::Vector2f m_bottomRight;
	float m_fullWidth = 0.0f;
	float m_fullheight = 0.0f;
	// tile information 
	int m_tileVertexCount = 4;
	sf::PrimitiveType tilePrimitiveType = sf::Quads;

	sf::Vector2i m_gridDimensions; // dimensions for the area alowing calculation of full width and height of the area 
	sf::Vector2f m_gridSectionSize;
	
	AreaTypes m_areaType = NONE;

	std::vector<TileInitialiser>  m_randomPositionedTiles;
	int m_generatedTilesCap = 0;
	// map all the tiles that will be generated from the level image map being used for the area 
	// to a string id which will be parsed from the level image map info file for this area(see the parse image map class for more details)
	std::map<std::string,TileInitialiser>  m_imageMappedTiles; 
	// map the colours within the level map to an  associated  tile id 
	std::map<imageMapColour, std::string> m_tileInfocoloursMap; 

	// store background textures associated with area 
	std::vector<std::string> m_backgroundTextures;
	// store the paths to the level image maps associated with the area
	std::vector<std::string> m_tileMapPaths;

	// used to store all loaded level image maps for an area 
	std::vector<sf::Image> m_loadedTileMaps;
	// store the current level image map being used by the area
	sf::Image * m_currentTileMapImage  = nullptr;

	// store specifc enemy instialisers associated 
	// with this area used to generate pooling objects for enemies 
	std::vector<EnemyInitialiser> m_enemies;
	float m_minSpawnCoolDown = 0.0f; 
	float m_maxSpawnCoolDown = 0.0f;


	//allies in area 
	std::vector<AllyInitialiser> m_allies;
	float m_allyRefreshCoolDown = 0.0f;
	int m_maxAllyCap = 0;

private:

	std::shared_ptr<CollisonHandler<Tile>> m_collisionTreeForUnwalkableTiles;

	
};