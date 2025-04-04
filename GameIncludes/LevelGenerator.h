#pragma once
#include "LevelArea.h"
#include "GrassPlainsArea.h"
class LevelGenerator {

public:
    
	LevelGenerator(LevelArea * initialAreas, int areasCount,SpriteGenerator * spriteGenerator,sf::Vector2f startAreaPosition);
	void initCurrentArea();
	
private:
	LevelArea* m_currentArea; 
	int m_areaCount;
	SpriteGenerator* m_spriteGenerator;
	std::vector<LevelArea> m_areaPool;
	std::map<AreaTypes, std::vector<EnemyBase*> >m_areaEnemyPools{ {GRASSLANDS,{}} };
	

};