#pragma once
#include "StaticObject.h"
#include "Player.h"



// base tile class for all tile objects in the game these inherit from static object obtaining 
// access to method such as set position and various properties such as rotation
class Tile: public StaticObject {

public:
	Tile();
	Tile(sf::Vector2f position);
	Tile(sf::Vector2f position, float width, float height);
	virtual ~Tile();
	virtual void playerEffect(Player* player);
	virtual void resetPlayerEffect(Player* player);
	void setVerticies(float width, float height, sf::Vector2f position);
	virtual Tile*clone(); 
	int getSpawnCap();
	void setSpawnCap(int spawnCap);
	void draw(sf::RenderWindow* window);


 protected:
	int m_spawnCap = 0;
	sf::VertexArray m_tileVerticies;
	size_t m_vertexCount = 4;
	sf::PrimitiveType m_primitveType = sf::Quads;

 private:

};



