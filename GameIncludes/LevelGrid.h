#pragma once
#include "LevelAreaContainer.h"
#include "Tile.h"
#include "gridTile.h"


class LevelGrid {

public:

	LevelGrid(int width, int height, sf::Vector2i tileDimensions);
	void generateTilesRelativeToArea(LevelAreaContainer* currentArea);
    Tile * getWorldToLocalPosition(sf::Vector2f worldPos); 
	gridTile* getGridTile(sf::Vector2f worldPos);
	void setNewWorldArea(LevelAreaContainer* levelArea);
	void imageMapPass(LevelAreaContainer* levelArea);
	void randomTilePlacementPass(LevelAreaContainer* levelArea);
	std::vector<gridTile*> getNeighbours(int& indexX, int& indexY);
	gridTile* getRandomLocationInGrid();
	void clampIndicies(int &indexX, int &indexY)const; 
	
	void randomiseTargetRow(int& currentY) const;
	int getResolution();
	sf::Vector2f getWorldPositionAtIndex(int & fullIndex);
	sf::Vector2i getDim();
	std::vector<gridTile>& getGridTiles();

private:
	
	int m_resolution;
	int m_width;
	int m_height; 
	int m_maxRowGenerationAttempts;
	int m_maxRowGenerationFailures;
	float m_tileWidth;
	float m_tileHeight;   
	sf::Vector2f m_currentWorldTopLeft;
	sf::Vector2f m_tileDimensions; 
	sf::Vector2f m_tileHalfExtents;
	LevelAreaContainer* m_playerArea = nullptr;
	std::vector<gridTile> m_localTiles;
     
	




};

