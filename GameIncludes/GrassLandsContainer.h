#pragma once
#include "LevelAreaContainer.h"
class GrassLandsArea : public LevelAreaContainer {

public:
	GrassLandsArea();
	~GrassLandsArea();
	GrassLandsArea(SpriteGenerator* spriteGenerator, std::vector<TileInitialiser>& randomPostionedTiles, std::map<std::string, TileInitialiser>& imageMappedTiles, std::vector<std::string>& backgroundPaths, std::vector<std::string>& tileMapPaths);
	void getTileFromSelectedMap(int x, int y);
	
	LevelAreaContainer*  clone();

    


private:
	

};