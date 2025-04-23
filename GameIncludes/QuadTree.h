#pragma once

#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include <array> 
#include "EnemyBase.h"
// a quad tree data structure is a spatial partitioning structure that is desgined to reduce the weight of collision checks 
/// the idea is to continously divide a space into smaller and smaller quads where each quad 
//  has a bucket of game objects who's bounds were able to fit into the quad, this divides 
// the space up meaning that each game object has its own section allocated to it 
// this reduces the amount of checks required when it comes to collision detection 
// as the quad tree can be queried based on an objects bounds i.e the range that object covers 
// and only the spaces within the quad tree data structure covered by the objects bounds need to be checked 

// the quad tree follows a recursive desgin patter with a root node that links all of the subsections/branches of the tree  togther
template<class objectType>
struct  quadTreeItem {

	sf::FloatRect bounds;
	objectType* gameObject = nullptr;
	quadTreeItem() {};
	quadTreeItem(sf::FloatRect _bounds, objectType* _gameObject) {
		
		bounds = _bounds;
		gameObject = _gameObject;
	
	}
	
};

template<class objectType>
class QuadTree {
public:
	QuadTree() {};
	QuadTree(sf::FloatRect bounds, int maxDepth)
	{

		m_bounds = bounds; // initial space the quad tree will cover
		m_maxDepth = maxDepth; // maxiumum depth of the tree in terms of height
		//std::cout << "quad tree initial bounds position left:" << bounds.left << " top:" << bounds.top << " width:" << bounds.width << " height:" << bounds.height << std::endl;

		sf::Vector2f sectionBounds = m_bounds.getSize() / 2.0f; // used to immdiealty calculate the bounds/space the children of this particualr section will cover 
		float centreX = m_bounds.getPosition().x + sectionBounds.x;
		float centreY = m_bounds.getPosition().y + sectionBounds.y;
		debugDraw.setPrimitiveType(sf::LinesStrip);

		boundsDebug.setSize(m_bounds.getSize());

		boundsDebug.setFillColor(sf::Color::Transparent);
		boundsDebug.setOutlineColor(sf::Color::Blue);
		boundsDebug.setOutlineThickness(2.0f);
		boundsDebug.setPosition(m_bounds.getPosition());



		// pre store the bounds for the next children 
		m_subSectionSizes = {
			sf::FloatRect(sf::Vector2f(m_bounds.getPosition()), sectionBounds),
			sf::FloatRect(sf::Vector2f(centreX - sectionBounds.x, centreY), sectionBounds),
			sf::FloatRect(sf::Vector2f(centreX, centreY - sectionBounds.y), sectionBounds),
			sf::FloatRect(sf::Vector2f(centreX ,centreY), sectionBounds),


		};

	}
	~QuadTree() {

		//clearChildren();
		//std::cout << "quad tree destructor called" << std::endl;
	}
	void insert(sf::FloatRect &objectBoundingBox,objectType * gameObjectRef) 
	{

		//std::cout << "inserting item into quad tree" << std::endl;



		if ((m_depth + 1) != m_maxDepth) { // if we have not hit max depth/height for this section of the tree
			if (!m_hasDivided) {
				//std::cout << "subdividing tree" << std::endl;
				subDivide(); // we first divide the space this section covers into smaller evenly spaced quads
			}

			// then once we have established the children for this section fo the tree and the space they cover we 
			// itterate through them checking if the game object to be inserted would be able to fit within the any bounds of each 
			// child's bounds based on the game objects bounding box
			for (std::shared_ptr<QuadTree<objectType>>& section : m_subSections) {
				/*std::cout << "looping through sections" << std::endl;*/

				if (rectContains(section.get()->m_bounds, objectBoundingBox)) {
					/*std::cout << "section could contain object" << std::endl;
					std::cout << "section bounds left:" << section.get()->m_bounds.left << " top:" << section.get()->m_bounds.top << " width:" << section.get()->m_bounds.width << " height:" << section.get()->m_bounds.height << std::endl;
					std::cout << "gameobject bounds left:" << gameObjectRef->getBounds().left << " top:" << gameObjectRef->getBounds().top << " width:" << gameObjectRef->getBounds().width << " height:" << gameObjectRef->getBounds().height << std::endl;*/

					section.get()->insert(objectBoundingBox, gameObjectRef);
					return;
				}


			}
		}
		else {
			std::cout << "maximum tree depth reached " << m_depth << std::endl;
		}
		/*std::cout << "final section could that could contain object" << std::endl;
		std::cout << "final section bounds " << m_bounds.left << ":" << m_bounds.top << ":" << m_bounds.width << ":" << m_bounds.height << std::endl;
		std::cout << "gameobject bounds " << objectBoundingBox.left << ":" << objectBoundingBox.top << ":" << objectBoundingBox.width << ":" << objectBoundingBox.height << std::endl;*/

		// if non of the children could completley contain the game objects bounding box then 
		// we insert it into this current section of the tree 
		m_objectItems.emplace_back(objectBoundingBox, gameObjectRef);

		return;

	}
	void setBounds(sf::FloatRect & newBounds) {
		
		std::cout << "setting new bounds for quad tree" << newBounds.left << newBounds.top << newBounds.width << newBounds.height << std::endl;
		std::cout << "max depth for tree" << m_maxDepth << std::endl;
		m_bounds = newBounds;
		sf::Vector2f sectionBounds = m_bounds.getSize() / 2.0f; // used to immdiealty calculate the bounds/space the children of this particualr section will cover 
		float centreX = m_bounds.getPosition().x + sectionBounds.x;
		float centreY = m_bounds.getPosition().y + sectionBounds.y;
		debugDraw.setPrimitiveType(sf::LinesStrip);

		boundsDebug.setSize(m_bounds.getSize());

		boundsDebug.setFillColor(sf::Color::Transparent);
		boundsDebug.setOutlineColor(sf::Color::Blue);
		boundsDebug.setOutlineThickness(2.0f);
		boundsDebug.setPosition(m_bounds.getPosition());



		// pre store the bounds for the next children 
		m_subSectionSizes = {
			sf::FloatRect(sf::Vector2f(m_bounds.getPosition()), sectionBounds),
			sf::FloatRect(sf::Vector2f(centreX - sectionBounds.x, centreY), sectionBounds),
			sf::FloatRect(sf::Vector2f(centreX, centreY - sectionBounds.y), sectionBounds),
			sf::FloatRect(sf::Vector2f(centreX ,centreY), sectionBounds),


		};

	}
	void subDivide()
	{
		//std::cout << "dividing tree" << std::endl;
		// didvindg the tree up into further branches/sections and increase the depth/height of the tree
		for (int i = 0; i < m_subSectionSizes.size(); i++) {

			m_subSections.emplace_back((new QuadTree<objectType>(m_subSectionSizes[i], m_maxDepth)));
			m_subSections.back().get()->setDepth(m_depth + 1);
		}
		m_hasDivided = true;
	}

	void query(sf::FloatRect &boundingBox, std::vector<quadTreeItem<objectType>> & result) {
		// querying the quad tree is a case of recursing down the tree and checking the items 
		// in each section that would overlap with the objects bounds
		//std::cout << "querying quad tree" << std::endl;
		for (quadTreeItem<objectType>& item : m_objectItems)
		{
			if (item.bounds.intersects(boundingBox)) {
				//std::cout << "quad tree item intersected with game object bounds" << std::endl;
				result.push_back(item);
			}

		}
		// check subsections
		if (m_hasDivided) {
			//std::cout << "section was divided searching into sub sections" << std::endl;
			for (std::shared_ptr<QuadTree<objectType>>& subSection : m_subSections) {
				// if the sub section could  fully fit inside our objects bounds then 
				// we can add all the items from its children and that subsection 
				// without needing anymore queries
				if (rectContains(boundingBox, subSection.get()->m_bounds)) {
					//std::cout << "section being searched could be fully contained in object bounds adding all items " << std::endl;

					subSection.get()->getAllItems(result);

				}
				// other wise if the sub section intersects but cant be fully contained within the bounds 
				// then we need to query the items(game objects) in each sub section and check for intersection 
				else if (subSection.get()->m_bounds.intersects(boundingBox)) {
					/*std::cout << "section being searched could contain object" << std::endl;
					std::cout << "section query bounds left:" << subSection.get()->m_bounds.left << " top:" << subSection.get()->m_bounds.top << " width:" << subSection.get()->m_bounds.width << " height:" << subSection.get()->m_bounds.height << std::endl;
					std::cout << "gameobject query bounds left:" << boundingBox.left << " top:" << boundingBox.top << " width:" << boundingBox.width << " height:" << boundingBox.height << std::endl;*/
					subSection.get()->query(boundingBox, result);
				}

			}
		}




	}
	void query(sf::Vector2f &position, std::vector<quadTreeItem<objectType>>& result) {
		// querying the quad tree is a case of recursing down the tree and checking the items 
		// in each section that would contain position with the  bounds
		for (quadTreeItem<objectType>& item : m_objectItems)
		{
			if (item.bounds.contains(position)) {
				result.push_back(item);
			}

		}
		// check subsections
		if (m_hasDivided) {
			//std::cout << "section was divided searching into sub sections" << std::endl;
			for (std::shared_ptr<QuadTree<objectType>>& subSection : m_subSections) {
				
				// if the sub section contains position within the bounds 
				 if (subSection.get()->m_bounds.contains(position)) {
					/*std::cout << "section being searched could contain object" << std::endl;
					std::cout << "section query bounds left:" << subSection.get()->m_bounds.left << " top:" << subSection.get()->m_bounds.top << " width:" << subSection.get()->m_bounds.width << " height:" << subSection.get()->m_bounds.height << std::endl;
					std::cout << "gameobject query bounds left:" << boundingBox.left << " top:" << boundingBox.top << " width:" << boundingBox.width << " height:" << boundingBox.height << std::endl;*/
					subSection.get()->query(position, result);
				}

			}
		}




	}
	void setMaxDepth(int& maxDepth) {
		m_maxDepth = maxDepth;
	}
	// clear the entire tree
	void clearChildren() {
		//std::cout << "clearning quad tree children" << std::endl;
		if (m_hasDivided) {
			for (std::shared_ptr<QuadTree<objectType>>& subSection:m_subSections) {
				subSection.get()->clearChildren();
			}

		}
		m_hasDivided = false;
		m_objectItems.clear();
		m_subSections.clear();
		return;
	}
	/// clear all items in the tree
	void clearItems() {
		//std::cout << "clearing quad tree section items" << std::endl;
		m_objectItems.clear();
		if (m_hasDivided) {
			for (std::shared_ptr<QuadTree<objectType>>& subSection : m_subSections) {
				subSection.get()->clearItems();
			}
		}

	}

	bool rectContains(sf::FloatRect& rect, sf::FloatRect& other) {

		sf::Vector2f max = rect.getPosition() + rect.getSize();
		sf::Vector2f omax = other.getPosition() + other.getSize();

		return (other.left >= rect.left && other.top >= rect.top) && (omax.x <= max.x && omax.y <= max.y);
	}
	void draw(sf::RenderWindow* window) {
		window->draw(boundsDebug);

		if (m_hasDivided) {

			for (int i = 0; i < m_subSections.size(); i++) {
				m_subSections[i].get()->draw(window);
			}

		}


	}
	void getAllItems(std::vector<quadTreeItem<objectType>>& insertInTo) {
		insertInTo.insert(insertInTo.end(), m_objectItems.begin(), m_objectItems.end());
		//std::cout << "inserting all items from sub section in tree size was  " << m_objectItems.size() << std::endl;
		if (m_hasDivided) {

			for (std::shared_ptr<QuadTree<objectType>>& subSection : m_subSections) {
				subSection.get()->getAllItems(insertInTo);
			}

		}


	}
	void setDepth(int depth) {
		m_depth = depth;
	}
private:
	
	sf::FloatRect m_bounds;
	sf::RectangleShape boundsDebug;
	int m_depth = 0;
	int m_maxDepth = 8;
	bool m_hasDivided = false;
	int m_sectionCount = 0;
	static const size_t m_subSectionCount = 4;
	sf::VertexArray debugDraw;
	std::vector<quadTreeItem<objectType>> m_objectItems;
	std::vector<std::shared_ptr<QuadTree<objectType>>> m_subSections;
	std::array<sf::FloatRect, 4> m_subSectionSizes;
	
	



};





