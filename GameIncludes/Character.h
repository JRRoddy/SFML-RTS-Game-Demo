#pragma once
#include "StaticObject.h"
#include "DynamicObject.h"
#include "gridTile.h"
#include "StatusEffectIds.h"
#include "StatusEffectManager.h"

// character class that describes a being in the world 
// storing data such as their stats 
// this can therefore be inherited by player and npcs to 
// reduce code duplication between them 
// see fix for multiple inherits in the inherited classes

class Character : public StaticObject, public DynamicObject {

public:
	Character() {}

	virtual ~Character() {}
	Character(sf::Vector2f position);
	void setDamage(float& damage);
	void setHealth(float& health);
	void takeDamage(float& damage);
	void setCellWidth(int& cellWidth);
	float getDamage() const;
	bool getIsAttacking() const;
	float getHealth() const;
	int getCellWidth() const;
	void setGridTile(gridTile* gridTile);
	int getCurrentGold();
	bool getAttackFinished()const;
	bool isDead() const;
	bool isTaunted() const;
	void setTaunted(bool taunted);
	void setCharacterTarget(Character* character);
	bool hasApplicableStatusEffects();
	void resetStatusEffectManager();
	bool applyStatusEffect(StatusEffectIds id, characterStats* initiaterStatsRef);
	StatusEffectManager* getStatusEffectManager(); 

	Character* getCharacterTarget();
	
protected:

	// stats for character
	characterStats m_currentStats;


	
	// character may have another character they are targetting 
	Character* m_characterTarget = nullptr;

	// if the character is attacking another character but cant switch target
	bool m_taunted = false;
	// default health
	int m_cellWidth = 1;
	gridTile* m_currentTile = nullptr;
	bool m_canAttack = false;
	bool m_attackFinished = false;
	// map of status effects that can be applied to a character
	std::map<StatusEffectIds, std::shared_ptr<StatusEffect>> m_appliableStatusEffectsMap;
	// status effect manager for keeping track of applied status effects
	std::shared_ptr<StatusEffectManager> m_statusEffectManager;
	
	

};

