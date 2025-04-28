#pragma once
#include "StaticObject.h"
#include "DynamicObject.h"
#include "gridTile.h"
// abstract character class that describes a being in the world 
// storing data such as their stats 
// this can therefore be inherited by player and npcs to 
// reduce data copying between them 
// see fix for multiple inherits in the inherited classes
class Character : public StaticObject, public DynamicObject {

public:
	Character() {}
	virtual ~Character() {}
	Character(sf::Vector2f position);
	void setDamage(float& damage);
	void setHealth(float& health);
	void takeDamage(float& damage);
	void setCellWidth(int& cellWidsth);
	float getDamage() const;
	bool getIsAttacking() const;
	float getHealth() const;
	int getCellWidth() const;
	void setGridTile(gridTile* gridTile);
	int getCurrentGold();
	bool getAttackFinished()const;
protected:
	float m_damage = 0.0f;
	float m_health = 0.0f;
	int m_cellWidth = 1;
	gridTile* m_currentTile = nullptr;
	bool m_canAttack = false;
	bool m_attackFinished = false;
	// every character will have some sort of currency either gained from killing 
	// or to recurit others 
	int m_gold = 0;
};


