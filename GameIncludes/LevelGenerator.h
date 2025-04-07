#pragma once

#include "LevelGrid.h" 
#include "EnemyBase.h"
// main class that is used to generate the current area for the player with it having classes such as a tile generator 
// and a vector that holds all of the level area containers
// currenlty on the map along with keeping track of the current level area container the player is in 
class LevelGenerator {

public:
	LevelGenerator(SpriteGenerator* spriteGenerator, sf::Vector2f startAreaOffsetPosition,sf::Vector2i tileDimensions, float areaGridWidth = 512.0f, float areaGridHeight = 512.0f);
	void generateNewAreaGrid(AreaTypes areaType,sf::Vector2f offsetPosition);
	LevelAreaContainer* getCurrentAreaGrid();
	float getGridAreaWidth()const;
	float getGridAreaHeight()const; 
	int getLevelChunkWidth() const;
	int getlevelChunkHeight() const;
	std::string getRandomAreaBackgroundTexturePath(AreaTypes areaType);


private:
	LevelAreaContainer* m_currentArea; 
	SpriteGenerator* m_spriteGenerator;
	std::unique_ptr<LevelGrid> m_levelGrid;
	float m_areaGridWidth; 
	float m_areaGridHeight;
	std::map<AreaTypes, std::vector<std::string>>m_levelAreaBackgroundImages{ {GRASSLANDS,{"../Assets/Textures/GrassBackground0.png"}}};
	int m_levelChunkGridWidth = 2;
	int m_levelChunkGridHeight = 2;

	std::vector<LevelAreaContainer> m_areaContainersPool;
	std::map<AreaTypes, std::vector<EnemyBase*> >m_areaEnemyPools{ {GRASSLANDS,{}} };
    

		


	

};