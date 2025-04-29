#include "AnimationController.h"



AnimationController::AnimationController(std::map<std::string, AnimationObject> &mapOfstates, std::string & defaultState)
{
	std::cout << "generating anim controller" << std::endl;
	m_mappedstates = mapOfstates;
	std::cout << "mapped states size  " << m_mappedstates.size() << std::endl;
	

	m_defaultState = defaultState;
	std::cout << "default state " << m_defaultState <<std::endl;
	m_currentState = m_defaultState; 
	m_baseSpriteRef = m_mappedstates[defaultState].getSpriteRef();

	// for each animation we will have a set of booleans that represent its current state
	//allowing us to check when a particualr animation is playing 
	// in this insatnce we itterate through the map using an itterator object
	// inserting the key value pair of a state name and a boolean 
	for (std::map<std::string, AnimationObject>::iterator it = m_mappedstates.begin(); it != m_mappedstates.end(); it++) {

		m_stateTriggerMap.insert({ it->first, false });



	}

	m_stateTriggerMap[m_defaultState] = true; // ensure that the deafault state for the anim controller is true 
}

AnimationController::AnimationController(AnimationController* animationController,std::shared_ptr<sf::Sprite>& baseSpriteOverride)
{
	// used to copy an animation controller to another if it is valid 
	if (animationController != nullptr) {
	    m_defaultState = animationController->m_defaultState; // set default state for this anim controller
		// copy the animation objects from the mapped states of the other animation controller
		for (std::pair<std::string, AnimationObject> pair : animationController->getStateMap()) {
		
			m_mappedstates.insert(pair);
			// set the base sprite ref for this animation controller to the one passed in 
			// allowing for a new sprite ref to be assigned to this anim controller
			m_mappedstates[pair.first].setBaseSpirteRef(baseSpriteOverride.get());
		}
		// update members such as current states and trigger map 
		m_baseSpriteRef = m_mappedstates[m_defaultState].getSpriteRef();
		m_currentState = m_defaultState;
		m_stateTriggerMap = animationController->getTriggerMap();

		if (m_stateTriggerMap.find(m_defaultState) != m_stateTriggerMap.end()) {
			std::cout << "trigger map default state found" << std::endl;
		}
		m_stateTriggerMap[m_defaultState] = true; // set default state for this anim controller to true


	}
	
}

AnimationController::~AnimationController()
{
}


// used to determine if default state should be active or not
void AnimationController::setDefault(bool isActive)
{
	
	m_stateTriggerMap[m_defaultState] = isActive;
	// if our current state is not default 
	// and our current state is not active 
	// if we want our default state to be active 
	if (m_currentState != m_defaultState && 
	   !(m_stateTriggerMap[m_currentState]) && isActive) {
		
		// reset the current state and set 
		// current state to default
		m_mappedstates[m_currentState].reset();
		m_mappedstates[m_defaultState].reset();
		m_currentState = m_defaultState;

	}
	
}

void AnimationController::setStates(std::map<std::string, AnimationObject>& states)
{
	m_mappedstates = states;

}

void AnimationController::setState(std::string state, bool isActive)
{
	
	m_stateTriggerMap[state] = isActive;
	// set current state to state being passed in 
	// if it should be active 
	if (state == "death" && isActive) {
		std::cout << "switching to death animation" << std::endl;
	}
	if (state != m_currentState && isActive == true) {
		// reset current state and set to state passed in
		m_mappedstates[m_currentState].reset(); 
		m_mappedstates[state].reset(); 
		m_currentState = state;
	}

	
}

bool AnimationController::currentAnimAtEndNoWait() {
	return m_mappedstates[m_currentState].animEndNoWait();
}
bool AnimationController::currentAnimAtEnd()
{ 
	return m_mappedstates[m_currentState].animAtEnd();
}


std::string AnimationController::getState()
{
	return m_currentState;
}

std::map<std::string, bool>& AnimationController::getTriggerMap()
{
	return m_stateTriggerMap;
}

void AnimationController::setDefaultState(std::string& state)
{
	m_defaultState = state;
}

sf::Sprite* AnimationController::getSpriteRef()
{
	return m_baseSpriteRef ;
}

bool AnimationController::stateIsActive(std::string state)
{
	try {

		return m_stateTriggerMap.at(state);
		
	}
	catch (...) {
		std::cout << "state being checked " << state << " was not int anim controller" << std::endl;
	}

	return false;
}

void AnimationController::update()
{
	m_mappedstates[m_currentState].play();
}



std::map<std::string, AnimationObject>& AnimationController::getStateMap()
{
	return m_mappedstates;
}

std::string& AnimationController::getDefaultState()
{
	return m_defaultState;
}
