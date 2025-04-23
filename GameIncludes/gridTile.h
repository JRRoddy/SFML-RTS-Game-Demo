#pragma once
#include "SFML/Graphics.hpp"
#include "Tile.h"
// the level grid class will be used to place tile objects through out the world keeping them uniform and at the same size 
struct gridTile {
	// represents the tiles current local space position when it is not transformed to match the current level area 
	sf::Vector2f localPosition;
	Tile* worldTileRef; // refernce to allocated tile in world space
	int indexX = 0;
	int indexY = 0;
	int fullIndex = 0;
	gridTile(sf::Vector2f _localPosition, Tile* _worldTileRef, int _indexX, int _indexY, int _fullIndex) {
		localPosition = _localPosition; // current local position based on indcices of local tile
		worldTileRef = _worldTileRef; // ref to world tile
		indexX = _indexX; // index positions in grid 
		indexY = _indexY;
		fullIndex = _fullIndex; // full location index in grid 
	};

};