#pragma once
#include "Npc.h"
#include "CheckObjectType.h"
// base class of all ally objects
class AllyBase:public Npc {
public:

	AllyBase();
	// virtual constructor here to ensure that memory allocated on the heap for any derrived classes is deallocated 
	// correctly when delloacting the memory via the delete key word
	virtual ~AllyBase()
	{

		std::cout << "ally base destructor called" << std::endl;
	};

	void collision(GameObject* other);
	virtual AllyBase* clone() { return nullptr; }
	virtual void clone(AllyBase* copy);
	void draw(sf::RenderWindow* window);
	virtual void setAnimStates();
	void getSprites(SpriteGenerator* spriteGenerator);
	bool isRecurited() const; 
	void playerInteract(); 
	void setIsSelected(bool isSelected);
	bool getSelected();
	
protected:
	bool m_selected = false;
	bool m_recruited = false;
	sf::Vector2f m_worldPositionTarget;


};