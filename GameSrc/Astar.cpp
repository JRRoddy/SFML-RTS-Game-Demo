#include "Astar.h"
// astar object that can be used for npcs that need pathfiding 
Astar::Astar(LevelGrid* levelGrid)
{
	m_levelGrid = levelGrid; // astar has a level grid
	// initialise a node grid used by the algorithm 
	// to calculate cost of movement and positions of waypoints
	m_nodeGrid.resize(m_levelGrid->getResolution()); 
	m_dim = m_levelGrid->getDim();  
	std::vector<gridTile> localGridTiles = m_levelGrid->getGridTiles();
	for (int i = 0; i < m_nodeGrid.size(); i++) {
		m_nodeGrid[i] = { &localGridTiles[i] };// initial node used tiles
		//from the global level grid
	}
}

std::vector<node*> Astar::getPath(sf::Vector2f& startPos, sf::Vector2f& endPos)
{ 

	node * startNode = &m_nodeGrid[ m_levelGrid->getGridTile(startPos)->fullIndex] ; 
	node * endNode = &m_nodeGrid[m_levelGrid->getGridTile(endPos)->fullIndex];
	// vector of nodes to be evaluated
	std::vector<node*> openSet = {startNode}; 
	// vector of most optimal nodes chosen
	std::vector<node*> closedSet = {};
	int currentNodeIndex = 0; 

	if (!endNode->walkable) {
		return {};
	}

	while (openSet.size() > 0) {

		node * currentNode = openSet[0]; // set current node 
		// to initial index

		for (int i = 1; i < openSet.size(); i++) {

			// evaulate all potential nodes accoridng to fcost
			// and hcost(distance from node to end node)
			if (openSet[i]->getFcost() < currentNode->getFcost() || 
			   ((openSet[i]->getFcost() == currentNode->getFcost()) && 
			    openSet[i]->hcost < currentNode->hcost)) {
				currentNode = openSet[i];
				currentNodeIndex = i;
			}

		}

		// push back the chosen node with lowest cost
		closedSet.push_back(currentNode); 
		// remove it from the open set so its no longer evaled
		openSet.erase(openSet.begin() + currentNodeIndex); 
		

		if (*currentNode == *endNode) { // if we reach the end node break
			break;
			
		}
		// get the neibouring tiles of the chosen current node 
		for (gridTile * neighbourTile : m_levelGrid->getNeighbours(currentNode->indexX, currentNode->indexY)) 
		{

			size_t nodeGridIndex = size_t(neighbourTile->fullIndex);
			node * potentialNode = &m_nodeGrid [ nodeGridIndex];
			// if the neighbour is in closed set that means
			// it has already been evaled or if its not a walkable tile skip it 
			if (!(potentialNode->walkable) ||  containsNode(closedSet, *potentialNode)) {
				//std::cout << "skipping node as it is in closed set or not walkable indicies x: "<< potentialNode->indexX<<" y:"<<potentialNode->indexY << std::endl;
				continue;
			}
			// caluate the cost to move from the current node to the neighbour
			int newGcost = getDistance(currentNode, potentialNode);
			
			bool wasContained = containsNode(openSet, *currentNode);
			if (!wasContained || 
			   (newGcost<potentialNode->gcost)) {

				// if the node was not evaulated already as it was not in the opsent 
				// or the distance between the neighbour node was shorter than 
				// previously recorded
				
				// set the node data using the neighbour tiles data
				potentialNode->tileRef = neighbourTile->worldTileRef;
				
				// set new costs for movement
				potentialNode->gcost = newGcost; 
				potentialNode->hcost = getDistance(endNode, potentialNode); 
				potentialNode->parent = currentNode;
				// set world pos of node in the grid
				potentialNode->worldPosition = m_levelGrid->getWorldPositionAtIndex(neighbourTile->fullIndex);
				potentialNode->setDebugPointPos(potentialNode->worldPosition);
				
				// final check to ensure that there is no
				//duplicate nodes in the openset
				if (!wasContained) {
					//std::cout << "adding node to open set position x: " << potentialNode->worldPosition.x << " y: " << potentialNode->worldPosition.y << std::endl;
					openSet.push_back(potentialNode);

				}


			}
		}

	}

	closedSet.erase(closedSet.begin());
	return closedSet;

}


void Astar::setGrid(LevelGrid* levelGrid)
{
	m_levelGrid = levelGrid;
}

bool Astar::containsNode(std::vector<node*>& nodes, node& nodeToCheck)
{

	for (node* node : nodes) {

		if (*node == nodeToCheck) {
			
			return true;
		}

	}

	return false;
}

int Astar::getDistance(node* a, node* b)
{
	
	int distX = abs( a->indexX - b->indexX); 
	int distY = abs(a->indexY - b->indexY); 

	if (distX > distY) {
		return 14 * distY + 10 * (distX - distY);
	}
	return 14 * distX + 10 * (distY - distX);
}




