#include "LevelGrid.h"



LevelGrid::LevelGrid(int width, int height, sf::Vector2i tileDimensions)
{
	m_width = width;
	m_height = height;
	m_tileDimensions = sf::Vector2f(tileDimensions);
	m_tileHalfExtents = m_tileDimensions / 2.0f;
	m_tileWidth = tileDimensions.x;
	m_tileHeight = tileDimensions.y;
	m_resolution = width * height;
	std::cout << "tile height for level grid "<<m_tileHeight << std::endl;
	
	for (int i = 1; i <= m_height; i++){
		for (int j = 1; j <= m_width; j++){ 
			m_localTiles.emplace_back(sf::Vector2f(j * (m_tileDimensions.x) , i * (m_tileDimensions.y) ),nullptr,j,i,i*m_width+j);
			std::cout << "calculated local position " << m_localTiles.back().localPosition.x << ":" << m_localTiles.back().localPosition.y << std::endl;
		}
	}



}

void LevelGrid::generateTilesRelativeToArea(LevelAreaContainer* currentArea)
{
	      std::cout << "generating tiles relative to area size for grid is " << m_localTiles.size() << std::endl;
	      for(int i = 0; i<m_localTiles.size();i++)
		  {
			  std::cout << "generating tile at index in local grid index: " << i << std::endl;
			  // going from local tile space to world tile space for the current tile 
			  sf::Vector2f position = (currentArea->getTopLeft() + m_localTiles[i].localPosition) - m_tileHalfExtents;  
			  
			  m_localTiles[i].worldTileRef = currentArea->initNewRandomTileInArea(position,m_tileDimensions.x,m_tileDimensions.y);
              
			  
			  
		  }
	     
	 
}

localTile* LevelGrid::getRandomLocationInGrid()
{
	int randIndex = rand() % m_resolution; 

	if (m_localTiles[randIndex].worldTileRef != nullptr) {

		while (m_localTiles[randIndex].worldTileRef != nullptr) {

			randIndex = rand() % m_resolution;


		}
	}

	return &m_localTiles[randIndex];
}
