#pragma once
#include "GameObject.h"
#include "EnemyBase.h"
#include "AreaTypes.h"
#include "iostream"


class LevelArea: public GameObject{

public:

	LevelArea();
	LevelArea(sf::Vector2f position);
	int getSpawnCount();
	void setBounds();
	void setVerticies();
	void draw(sf::RenderWindow * window) override;
	void getSprites(SpriteGenerator * spriteGenerator) override;
	AreaTypes getAreaType();
private:
	sf::Texture m_backGroundImage;
	float m_width;
    float m_height;
	sf::VertexArray * m_areaVertexArray;

protected:
	int m_enemyCap = 0;
	int m_maxSpawnCount = 0;
	std::vector<std::string> m_backgroundImagePaths;
	AreaTypes m_areaType;

};