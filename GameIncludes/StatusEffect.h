#pragma once
#include "CharacterStats.h"
#include "StatusEffectIds.h"
#include "SFML//System.hpp"
#include "iostream"
class StatusEffect {

public:
	StatusEffect() {};
	virtual ~StatusEffect() {
		std::cout << "status effect destructor called" << std::endl;
	};
	void clone(StatusEffect* copy); 
	virtual bool canApply() = 0;
	virtual void effect(characterStats* characterStats) = 0;
	virtual bool finished() = 0;
	
	bool durationFinished();
	void setInitiater(characterStats*  statsForInitiater);
	void activate();
	virtual  void reset();
	float getDuration() const; 
	void setDuration(float & duration) ;
	void setStatusEffectId(StatusEffectIds id); 
	StatusEffectIds getStatusEffectId();
	bool hasDuration() const;
	bool getIsActive()const;
protected: 
	bool m_hasDuration = false; 
	bool m_isActive = false;
	float m_duration = 0.0f; 
	sf::Time m_endTime; 
	sf::Clock m_durationTimer;
	characterStats* m_initiaterStats = nullptr;
	StatusEffectIds m_statusEffectId = StatusEffectIds();


};