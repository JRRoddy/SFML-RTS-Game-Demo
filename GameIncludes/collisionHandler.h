#pragma once
#include "SFML/Graphics.hpp"
#include "QuadTree.h"
#include "EnemyBase.h"
#include "GameObject.h"

// wrapper class around the quad tree class
/// this class is also a genric class that uses templates to ensure that it can handle any type 
// of object that requires collision
template<class objectType>
class CollisonHandler {

public:

	CollisonHandler() {
	    
		m_CollisionTree = std::make_shared<QuadTree<objectType>>(QuadTree<objectType>());
	}
	CollisonHandler(sf::FloatRect& totalAreaForCollisionTree , int maxTreeDepth )
	{
		m_CollisionTree = std::make_shared<QuadTree<objectType>>( ( QuadTree<objectType>(totalAreaForCollisionTree, maxTreeDepth)));
	}
	// when resizing the tree it will invalidate the current section of all the children so 
	// we will need to clear the entire tree and set the new bounds
	void setCollisionTreeProperties(sf::FloatRect& totalAreaForCollisionTree, int maxTreeDepth ) {


		m_CollisionTree->setMaxDepth(maxTreeDepth);
		resizeTree(totalAreaForCollisionTree); 
		

	}

	void resizeTree(sf::FloatRect& newBounds) {
		m_CollisionTree.get()->setBounds(newBounds);
		m_CollisionTree.get()->clearChildren();
	}
	void resetCollisionTreeItems() {
		m_CollisionTree.get()->clearItems();
	
	}
	void setTreeMaxDepth(int& maxDepth) {
		m_CollisionTree.get()->setMaxDepth(maxDepth);
	}
	void insertItem(sf::FloatRect &objectBounds, objectType* object) {
		m_CollisionTree.get()->insert(objectBounds, object);
	}

	void queryCollisionTree(sf::FloatRect & objectBounds, std::vector<quadTreeItem<objectType>>& insert) {

		m_CollisionTree.get()->query(objectBounds, insert);

	}

	void queryCollisionTree(sf::Vector2f& position, std::vector<quadTreeItem<objectType>>& insert) {
		m_CollisionTree.get()->query(position, insert);
	}

	void drawCollisionTree(sf::RenderWindow * window) {

		m_CollisionTree.get()->draw(window);

	}

	

	~CollisonHandler() {

	}
	
private:
	std::shared_ptr<QuadTree<objectType>>  m_CollisionTree;

	 


};