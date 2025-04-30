#pragma once
#include "Character.h"
class StatusEffect {

public:
	StatusEffect() {};
	virtual ~StatusEffect() {};
	virtual void effect(Character *character) = 0;
	virtual void resetEffect(Character* character) = 0;
	virtual bool finished() = 0;
	bool durationFinished();
	void setInitiater(Character* character);
	void activate();
	void reset();
	float getDuration() const; 
	bool hasDuration() const;
	bool getIsActive()const;
protected: 
	bool m_hasDuration = false; 
	bool m_isActive = false;
	float m_duration = 0.0f; 
	sf::Time m_endTime; 
	sf::Clock m_durationTimer;
	Character* m_initiater = nullptr;
	


};