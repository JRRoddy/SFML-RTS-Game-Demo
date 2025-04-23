#pragma once
#include "gridTile.h"
#include "SFML/Graphics.hpp"

// node struct used by astar algorithm 
// used to make up the path generate bby the algorithm
struct node
{
	//positions in grid used for generating paths
	int indexX = 0;
	int indexY = 0;
	//world tile refernce
	Tile* tileRef = nullptr;
	node* parent = nullptr;
	sf::Vector2f worldPosition;
	// costs
	int gcost = 0; // cost to move from current node to neighbour
	int hcost = 0; // cost to move from node to target end node
	int fcost = 0;  //sum of above costs
	sf::CircleShape m_pathPoint;

	//constructors
	node() {};
	node(gridTile* localTileRef) {
		indexX = localTileRef->indexX;
		indexY = localTileRef->indexY;
		tileRef = localTileRef->worldTileRef;
		m_pathPoint.setFillColor(sf::Color::Cyan);
		m_pathPoint.setRadius(8.0f); 
		m_pathPoint.setOrigin(4.0f, 4.0f); 
		


	}

	void setDebugPointPos(sf::Vector2f& position) {
		m_pathPoint.setPosition(position);
	}
	// operator overload to check if two nodes are equal
	bool operator == (node& other) const {

		return indexX == other.indexX && indexY == other.indexY;

	}
	// operator overload to check if two nodes are not equal

	bool operator != (node& other) const {

		return  indexX != other.indexX && indexY != other.indexY;

	}


	int getFcost() { // get and set sum of costs
		fcost = hcost + gcost;
		return fcost;
	}


	void draw(sf::RenderWindow* window) {

		window->draw(m_pathPoint);

	}

};
