#include "LevelGrid.h"

LevelGrid::LevelGrid(int width, int height, sf::Vector2i tileDimensions)
{
	m_width = width;
	m_height = height;
	m_tileWidth = tileDimensions.x;
	m_tileHeight = tileDimensions.y;
	m_resolution = width * height;

	sf::Vector2f topLeftcentreLocal = sf::Vector2f(0.0f - m_tileWidth / 2.0f, 0.0f - m_tileHeight / 2.0f);

	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) { 
			m_localTiles.emplace_back(sf::Vector2f(j * m_tileWidth + topLeftcentreLocal.x, i * m_tileHeight + topLeftcentreLocal.y),nullptr);

		}
	}



}

void LevelGrid::generateTilesRelativeToArea(LevelAreaContainer* currentArea)
{
	 
	 
}
