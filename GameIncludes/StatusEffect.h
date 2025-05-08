#pragma once
#include "CharacterStats.h"
#include "StatusEffectIds.h"
#include "SFML//System.hpp"
#include "iostream"
//abstract status effect class that has all the basic properties 
// stored within in it relating to status effects
// and pure virtual methods that would be 
// implmented in different ways across the derrived classes such as
// the effect method that impacts a particualr characters stats
class StatusEffect {

public:
	StatusEffect() {};
	virtual ~StatusEffect() {};
	void clone(StatusEffect* copy); 
	virtual bool canApply() = 0;
	virtual void effect(characterStats* characterStats) = 0;
	virtual bool finished() = 0;
	
	bool durationFinished();
	void setInitiater(characterStats*  statsForInitiater);
	void activate();
	virtual  void reset();
	float getDuration() const; 
	void setDuration(float & duration);
	bool hasDuration() const;
	bool getIsActive()const;
protected: 
	
	bool m_hasDuration = false; 
	//status effects can be active and inactive 
	bool m_isActive = false;
	// status effects may have duration
	float m_duration = 0.0f; 
	sf::Time m_endTime; 
	sf::Clock m_durationTimer;
	// refernce to stats of character that initiated/activated this status effect
	characterStats* m_initiaterStats = nullptr;



};