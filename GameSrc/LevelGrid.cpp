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
	for (int i = 1; i <= m_height; i++){
		for (int j = 1; j <= m_width; j++){ 
			m_localTiles.emplace_back(sf::Vector2f(j * (m_tileDimensions.x) , i * (m_tileDimensions.y) ),nullptr,j,i,i*m_width+j);
		}
	}



}

void LevelGrid::setNewWorldArea(LevelAreaContainer* levelArea) {
	m_playerArea = levelArea;
}

void LevelGrid::generateTilesRelativeToArea(LevelAreaContainer* currentArea)
{
	      
	      std::cout << "generating tiles relative to area size for grid is " << m_localTiles.size() << std::endl;
	      for(int i = 0; i<m_localTiles.size();i++)
		  {
			  // going from local tile space to world tile space for the current tile 
			  if (i % 2 == 0) {
				  sf::Vector2f position = (currentArea->getTopLeft() + m_localTiles[i].localPosition) - m_tileHalfExtents;

				  m_localTiles[i].worldTileRef = currentArea->initNewRandomTileInArea(position, m_tileDimensions.x, m_tileDimensions.y);

			  }
			  
		  }
	     
	 
}

Tile* LevelGrid::getWorldToLocalPosition(sf::Vector2f worldPos)
{

	sf::Vector2f difference =   worldPos - m_playerArea->getTopLeft();
	int indexX =  static_cast<int>( difference.x / m_tileDimensions.x);
	int indexY =  static_cast<int>( difference.y / m_tileDimensions.y);

	size_t finalIndex = static_cast<size_t>( (indexY * m_width) + indexX); 

	clampIndex(finalIndex);


	/*if (m_localTiles[finalIndex].worldTileRef != nullptr) {
		std::cout << "found filled tile" << std::endl;
		std::cout << "calcuated index base on world postion x " << indexX << " Y:" << indexY << " final:" << finalIndex << std::endl;
		std::cout << "tile world pos x:" << m_localTiles[finalIndex].localPosition.x << " y:" << m_localTiles[finalIndex].localPosition.x << std::endl;
	}*/
	return m_localTiles[finalIndex].worldTileRef;
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

void LevelGrid::clampIndex(size_t& index)
{
	
	if (index<0) {
		index = 0;
		return;
	}
     if (index >= m_resolution) {
		index = m_resolution - 1;
	}




}
