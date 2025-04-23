#pragma once
#include "StaticObject.h"
#include "DynamicObject.h"


// base tile class for all tile objects in the game these inherit from static object obtaining 
// access to method such as set position and various properties such as rotation
class Tile: public StaticObject {

public:
	Tile();
	Tile(sf::Vector2f position);
	Tile(sf::Vector2f position, float width, float height);
	virtual ~Tile();
	
	// each tile will have a player effect and therefore this method has been made virtual allowing for it to have its own 
    // implmentation across each child that through dynamic linkage will be maintained when assigned to a base class refernce 
	virtual void dynamicObjectEffect(DynamicObject* object) = 0;
	virtual void resetDynamicObjectEffect(DynamicObject* object) = 0;
	void setVerticies(float width, float height, sf::Vector2f position);
	// used to get a deep copy of a tile allowing for a single instance of a tile to be held in a data structure 
     // and then copied throughout them game in order to create new tiles of different types
	virtual Tile*clone() = 0; 
	virtual void clone(Tile* copy);
	int getRowCap();
	void setSpawnCap(int spawnCap);
	void draw(sf::RenderWindow* window);
	void setSpeedModifier(float speedMod);

 protected:
	int m_rowCap = 0;
	float m_speedModifier = 1.0f;
	sf::VertexArray m_tileVerticies;
	size_t m_vertexCount = 4;
	sf::PrimitiveType m_primitveType = sf::Quads;

 private:

};



