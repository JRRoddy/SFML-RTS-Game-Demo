#pragma once
#include "LevelAreaContainer.h"
#include "Tile.h"
// the level grid class will be used to place tile objects throughout the world keeping them uniform and at the same size 
struct localTile {
	// represents the tiles current local space position when it is not transformed to match the current level area 
	sf::Vector2f localPosition;
	Tile* worldTileRef; // refernce to allocated tile in world space
	int indexX = 0;
	int indexY = 0; 
	int fullIndex = 0;
	localTile(sf::Vector2f _localPosition, Tile* _worldTileRef,int _indexX, int _indexY, int _fullIndex)  {
		localPosition = _localPosition;
	    worldTileRef = _worldTileRef; // ref
		indexX = _indexX;
		indexY = _indexY;
		fullIndex = _fullIndex;
	};

};

class LevelGrid {

public:

	LevelGrid(int width, int height, sf::Vector2i tileDimensions);
	void generateTilesRelativeToArea(LevelAreaContainer* currentArea);
    Tile * getWorldToLocalPosition(sf::Vector2f worldPos); 
	void setNewWorldArea(LevelAreaContainer* levelArea);
	localTile* getRandomLocationInGrid();
	void clampIndex(size_t& index);
private:
	
	int m_resolution;
	int m_width;
	int m_height; 
	
	float m_tileWidth;
	float m_tileHeight;   
	sf::Vector2f m_currentWorldTopLeft;
	sf::Vector2f m_tileDimensions; 
	sf::Vector2f m_tileHalfExtents;
	LevelAreaContainer* m_playerArea = nullptr;
	std::vector<localTile> m_localTiles;
     





};