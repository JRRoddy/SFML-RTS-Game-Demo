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
	// setting up variables used for random placement of tiles in the grid
	m_maxRowGenerationAttempts = width / 2;
	m_maxRowGenerationFailures = width; 
	std::cout << "max row generation failures " << m_maxRowGenerationFailures << " max row generation attemps" << m_maxRowGenerationAttempts << std::endl;
	for (int i = 1; i <= m_height; i++){
		for (int j = 1; j <= m_width; j++){ 

			int indexX = j - 1; 
			int indexY = i - 1;
			// here we are emplacing a local space tile into the grid this tile struct is used to 
			// genertae world space positions relative to any area based on its top left along with being 
			// emplace back is used here to constrcuct the object in place within the vector so no copy
			// needed
			m_localTiles.emplace_back(sf::Vector2f(j * (m_tileDimensions.x) , i * (m_tileDimensions.y) ),nullptr,indexX,indexY,indexY*m_width+indexX);
		}
	}



}

void LevelGrid::setNewWorldArea(LevelAreaContainer* levelArea) {
	m_playerArea = levelArea;
}

void LevelGrid::imageMapPass(LevelAreaContainer* currentArea)
{
	for (int i = 0; i < m_localTiles.size(); i++)
	{
		// going from local tile space to world tile space for the current tile 
		sf::Vector2f position = (currentArea->getTopLeft() + m_localTiles[i].localPosition) - m_tileHalfExtents;
		// here we get the top left of the current local tile which will be used to access the top left pixel 
		// of each tile within the level map image that the current area being generated has assigned to it 
		sf::Vector2i imageMapPosition = sf::Vector2i(m_localTiles[i].localPosition) - sf::Vector2i(m_tileDimensions);
		m_localTiles[i].worldTileRef = currentArea->initTileFromSelectedMap(imageMapPosition, position, m_tileDimensions.x, m_tileDimensions.y);



	}

}

void LevelGrid::randomTilePlacementPass(LevelAreaContainer* currentArea)
{

	// this method will attemtp to generate tiles at a random location on the level grid 
	// attemtping to take into account repeat placements along with switching between 
	// rows after a certain number of attempts this method is used to place tiles like bushes 
	// that can be distributed ranodmly around the area unlike for uniform tiles such as paths

	int cap = currentArea->getRandomGeneratedTilesCap();  // get the sum of the spawn caps for each randomly generated tile that the level area can spawn
	std::cout << "spawn cap for random pass " << cap << std::endl;
	int count = 0; 
	int rowAttempts = 0; // number of attempts allowed on a specific row 
	// initial row x and y
	int randomY = (rand() % m_height)*m_width;
	int randomX = rand() % m_width; 
	int previousX = 0;
	int rowGenerationFailures = 0;
	int currentTileRowCap = 0;
	while (count < cap) {
		
		if (randomX == previousX) { 
			// if the previous x was a repeat we ensure that we do not get another duplicate 
			// based on the last x recorded by checking if it was lower or higher than half the max width for the grid 
			int randomXBoundLower = rand() % m_width / 2;  
			int randomXBoundHigher = (m_width / 2) + (rand() % ((m_width - 1) - (m_width / 2))); 
			 
			randomX < m_width / 2 ? randomXBoundHigher : randomXBoundLower;
		}

		size_t finalIndex = static_cast<size_t>( randomY + randomX);

		previousX = randomX; // keep track of previous x
		randomX = rand() % m_width;

		if (m_localTiles[finalIndex].worldTileRef != nullptr) {
			rowAttempts++; // if we get a tile that has already been filled then we increase the count for the number of times we have failed placing a tile on this particualr grid row 
			if (rowAttempts >= m_maxRowGenerationAttempts) { // if we reach the maximum number of attempts on particualr row we switch rows
				// same logic as for when we get a duplicate x value
				std::cout << "row generation max reached for particualr row" << std::endl;
				randomiseTargetRow(randomY);
				
				
				rowGenerationFailures++; // increase the generation failure each time we could not place a random tile on a row 
			
				currentTileRowCap = 0;
				rowAttempts = 0;
			   
			}

			// break if we reach the maximum number of times we can fail placing a tile across all the rows
			if (rowGenerationFailures == m_maxRowGenerationFailures-1) {
				std::cout<< "random generation pass ended " << std::endl;
				break;
			}
			continue;

		} 
	    
		sf::Vector2f position = (currentArea->getTopLeft() + m_localTiles[finalIndex].localPosition) - m_tileHalfExtents;
		m_localTiles[finalIndex].worldTileRef = currentArea->initNewRandomTileInArea(position, m_tileDimensions.x, m_tileDimensions.y);
		
		currentTileRowCap++;
		if (currentTileRowCap == m_localTiles[finalIndex].worldTileRef->getRowCap()) {
			std::cout << "row cap hit " << std::endl;
			randomiseTargetRow(randomY);
		}

		count++;
		std::cout << "count for random tile placement increased" << std::endl;
	}




}



// get neighbour tiles based on a x index and a y index
std::vector<gridTile*> LevelGrid::getNeighbours(int& indexX, int& indexY)
{
	std::vector<gridTile*> neighbours = {}; 

	for (int y = -1; y <= 1; y++) {

		for (int x = -1; x <= 1; x++) {

			int currentX = indexX + x;  //add current offsets to indcies
			int currentY = indexY + y;
			// if they are not the same indicies as args passed in
			if (currentX == indexX && currentY == indexY) {
				continue;
			}
			// if they are contained within the bounds
			// of our current grid 
			if (currentX >= 0 && currentX < m_width && 
			    currentY >= 0 && currentY < m_height) {
				// calculate full offset into the grid tiles vector 
				size_t finalIndex = size_t(currentY * m_width + currentX);
				// push back tile we want to the vector to be returned
				neighbours.push_back(&m_localTiles[finalIndex]);

			}
	
		}


	}
	return neighbours;


   
}
// main method for generating tiles on a particualr level area 
void LevelGrid::generateTilesRelativeToArea(LevelAreaContainer* currentArea)
{
	      std::cout << "generating tiles relative to area size for grid is " << m_localTiles.size() << std::endl;
		  imageMapPass(currentArea);
		  randomTilePlacementPass(currentArea);
	      
}

Tile* LevelGrid::getWorldToLocalPosition(sf::Vector2f worldPos)
{
	sf::Vector2f difference =   worldPos - m_playerArea->getTopLeft();
	int indexX =  static_cast<int>( difference.x / m_tileDimensions.x); 
	int indexY =  static_cast<int>(difference.y / m_tileDimensions.y);

	clampIndicies(indexX,indexY);
	size_t finalIndex = static_cast<size_t>((indexY * m_width) + indexX);

	return m_localTiles[finalIndex].worldTileRef;
}

gridTile* LevelGrid::getGridTile(sf::Vector2f worldPos)
{
	sf::Vector2f difference = worldPos - m_playerArea->getTopLeft();
	int indexX = static_cast<int>(difference.x / m_tileDimensions.x);
	int indexY = static_cast<int>(difference.y / m_tileDimensions.y);

	clampIndicies(indexX,indexY);
	size_t finalIndex = static_cast<size_t>((indexY * m_width) + indexX);

	return &m_localTiles[finalIndex];
}

gridTile* LevelGrid::getRandomLocationInGrid()
{
	int randIndex = rand() % m_resolution; 

	return &m_localTiles[randIndex];
}



void LevelGrid::clampIndicies(int &indexX,int &indexY) const
{

	indexX = std::clamp(indexX,0,m_width-1);
	indexY = std::clamp(indexY,0,m_height-1);
	 

}

void LevelGrid::randomiseTargetRow(int& currentY) const
{
	int randomYHigherBound = ((m_height / 2) + (rand() % ((m_height - 1) - m_height / 2))) * m_width;
	int randomYLowerBound = (rand() % m_height / 2) * m_width;
	currentY = currentY < m_resolution / 2 ? randomYHigherBound : randomYLowerBound;

}
sf::Vector2i LevelGrid::getDim()
{
	return sf::Vector2i(m_width,m_height);
}
std::vector<gridTile>& LevelGrid::getGridTiles()
{
	return m_localTiles;
}
int LevelGrid::getResolution()
{
	return m_resolution;
}

sf::Vector2f LevelGrid::getWorldPositionAtIndex(int &fullIndex)
{
	// calculate world position in grid and return it 
	sf::Vector2f position = (m_playerArea->getTopLeft() + m_localTiles[fullIndex].localPosition) - m_tileHalfExtents;

	return position;
}
