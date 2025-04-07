#include "LevelGenerator.h"




// this class is responsible for holding the main data that is used for level generation keeping things such as various 
// background textures for level area containers and tile data all wrapped under a single class. All of this data  is 
// also stored within maps and vectors allowing it to then be easily accessed by other classes such as the tile generator
LevelGenerator::LevelGenerator(SpriteGenerator * spriteGenerator,sf::Vector2f startAreaOffsetPosition, sf::Vector2i tileDimensions,float areaGridWidth , float areaGridHeight) {
	std::cout << "initialsing level generator" <<std::endl;;
	m_spriteGenerator = spriteGenerator;
	m_areaGridWidth = areaGridWidth;
	m_areaGridHeight = areaGridHeight;
	
	m_levelGrid = std::make_unique<LevelGrid>(LevelGrid((m_levelChunkGridWidth * m_areaGridWidth) / tileDimensions.x, (m_levelChunkGridHeight * m_areaGridHeight) / tileDimensions.y,tileDimensions));
	generateNewAreaGrid(GRASSLANDS, startAreaOffsetPosition);
	m_currentArea = &m_areaContainersPool.back(); 
	
	
    


}

void LevelGenerator::generateNewAreaGrid(AreaTypes areaType, sf::Vector2f offsetPosition)
{

	m_areaContainersPool.emplace_back(m_spriteGenerator,offsetPosition,areaType,getRandomAreaBackgroundTexturePath(areaType),sf::Vector2i(m_levelChunkGridWidth,m_levelChunkGridHeight),sf::Vector2f(m_areaGridWidth,m_areaGridHeight));

}



LevelAreaContainer* LevelGenerator::getCurrentAreaGrid()
{
	return m_currentArea;
}



float LevelGenerator::getGridAreaWidth()const  
{
	return m_areaGridWidth;
}

float LevelGenerator::getGridAreaHeight()const 
{
	return m_areaGridHeight;
}

int LevelGenerator::getLevelChunkWidth() const
{
	return m_levelChunkGridWidth;
}

int LevelGenerator::getlevelChunkHeight()const
{
	return m_levelChunkGridHeight;
}

std::string LevelGenerator::getRandomAreaBackgroundTexturePath(AreaTypes areaType) 
{

	std::vector<std::string>& temp = m_levelAreaBackgroundImages[areaType]; 

	return temp[rand() % temp.size()];



	
}
