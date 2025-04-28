#pragma once
#include "AnimationObject.h"

// animation controller class that acts akin to a state machine for 
// multiple animations shared by one object
class AnimationController {

public:
   
	AnimationController(std::map<std::string, AnimationObject>& mapOfstates,std::string & defaultState);
	AnimationController(AnimationController* animationController, std::shared_ptr<sf::Sprite>& baseSpriteOverride);
	~AnimationController(); 
	void setDefault(bool  isActive); 
	void setStates(std::map<std::string, AnimationObject>& states);
	void setState(std::string state, bool  isActive); 
	bool currentAnimAtEnd();
	std::string getState();
	std::map<std::string, bool>& getTriggerMap();
	void setDefaultState(std::string& state);
	sf::Sprite* getSpriteRef();
	bool stateIsActive(std::string state);
	void update(); 
	std::map<std::string, AnimationObject>& getStateMap();
	std::string& getDefaultState();

private:
	std::string m_defaultState;
	std::string m_currentState;
	sf::Sprite* m_baseSpriteRef = nullptr;
	std::map<std::string, AnimationObject> m_mappedstates;
	std::map<std::string, bool> m_stateTriggerMap;

};


