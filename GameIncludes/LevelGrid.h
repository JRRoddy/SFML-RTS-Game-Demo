#pragma once
#include "LevelAreaContainer.h"
#include "Tile.h"
// the level grid class will be used to place tile objects throughout the world keeping them uniform and at the same size 
struct localTile {
	// represents the tiles current local space position when it is not transformed to match the current level area 
	sf::Vector2f localPosition;
	Tile* worldTileRef; // refernce to allocated tile in world space

	localTile(sf::Vector2f _localPosition, Tile* _worldTileRef) :localPosition(_localPosition), worldTileRef(_worldTileRef) {};

};

class LevelGrid {

public:

	LevelGrid(int width, int height, sf::Vector2i tileDimensions);
	void generateTilesRelativeToArea(LevelAreaContainer* currentArea);


private:
	
	int m_resolution;
	int m_width;
	int m_height;
	float m_tileWidth;
	float m_tileHeight; 

	std::vector<localTile> m_localTiles;
     





};