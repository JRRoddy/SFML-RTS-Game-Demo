#include "LevelGenerator.h"



LevelGenerator::LevelGenerator(LevelArea* initialAreas, int areasCount, SpriteGenerator * spriteGenerator,sf::Vector2f startAreaPosition)
{
	m_areaCount = areasCount;
	m_spriteGenerator = spriteGenerator;
	for (int i = 0; i < areasCount; i++) {
		LevelArea area = initialAreas[i];  
		area.setPosition(sf::Vector2f(10.0f, 10.0f)); 
		std::cout << "area type is "<< area.getAreaType() << std::endl;
		std::cout << "initial copy position "<<initialAreas[i].getPosition().x << std::endl;
		m_areaPool.push_back(area);
	}
	

	m_currentArea  = m_areaPool.data();
	m_currentArea->setPosition(startAreaPosition);
	initCurrentArea();
}







void LevelGenerator::initCurrentArea()
{
	m_currentArea->setVerticies();
	m_currentArea->getSprites(m_spriteGenerator);


}
