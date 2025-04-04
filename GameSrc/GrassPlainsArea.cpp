#include "GrassPlainsArea.h"

GrassPlainsArea::GrassPlainsArea()
{
	m_areaType = GRASSLANDS;
	m_enemyCap = 10;
}

GrassPlainsArea::GrassPlainsArea(sf::Vector2f position):LevelArea(position)
{
	m_areaType = GRASSLANDS;
	m_enemyCap = 10;
}
