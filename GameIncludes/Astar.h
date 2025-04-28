#pragma once
#include "LevelGrid.h"
#include "AstarNode.h"

// class that encapsulates the astar algorithm used for pathfinding for npc's 
class Astar {

public:
	Astar() {};
	Astar(LevelGrid* levelGrid);

	std::vector<node*> getPath(sf::Vector2f& startPos, sf::Vector2f& endPos);
	void setGrid(LevelGrid* levelGrid);
	bool containsNode(std::vector<node*>& nodes, node &nodeToCheck);
	int getDistance(node* a, node* b); 
	
private:
	sf::Vector2i m_dim;
	LevelGrid* m_levelGrid = nullptr; 
	std::vector<node> m_nodeGrid;




};