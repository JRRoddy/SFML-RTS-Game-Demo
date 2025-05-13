#include "InputManager.h"


InputManager::InputManager(sf::Window* window)
{

	m_windowHandle = window;

}




void InputManager::pollEvents(sf::Event& event)
{
	m_mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_windowHandle)); // update mouse position held by input manager
	while (m_windowHandle->pollEvent(event)) { // poll events such as keyboard and program exit 
		//std::cout << "polling events" << std::endl;
		if (event.type == sf::Event::Closed) m_windowHandle->close(); 
		if (event.type == event.MouseButtonReleased) {
			std::cout << "mouse released" << std::endl;
			m_mouseButtons[event.mouseButton.button] = true; // update mouse state
		}
		// event polling is used to track singualr key presses therefore the state of a key being pressed is only updated on release 
		if (event.type == event.KeyReleased) { 
			m_keyStates[event.key.code].eventState = true;

		}


	}


}
// must be called after changing event state for the key if you dont want 
// repeat input for that key or only want repeat input for certain amount of time
void InputManager::resetEventState(sf::Keyboard::Key keyToReset) {

	m_keyStates[keyToReset].eventState = false;

}


bool InputManager::isBound(sf::Keyboard::Key key)
{
	try {

		m_keyStates[key];
		return true;

	}
	catch (...) {
		std::cout << "key not bound: " << key << std::endl;
		return false;

	}

}

bool InputManager::keyReleased(sf::Keyboard::Key key)
{
	if (m_keyStates[key].eventState) { /// check if a key is being pressed wihtin the key states array
		m_EventKeysCalled.insert(key); // if it is then we insert it into the event keys called map to be updated 
		// m_EventKeysCalled is also a set to avoid duplciates being inserted 
	} 
	// return the current key state of the key being checked
	return m_keyStates[key].eventState;
}


bool InputManager::mouseReleased(sf::Mouse::Button button)
{
	return m_mouseButtons[button]; // return current state of mouse button
}

bool InputManager::isMouseDown(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button);
}

bool InputManager::keyEventStateUp(sf::Keyboard::Key key)
{
	return !m_keyStates[key].eventState; /// get if key is not currenlty being pressed 
}

void InputManager::endFrame()
{
	// every update this method should be called if using the keyDown method as
	// for each time the key being checked is down it will be added to the m_eventKeysCalled set
	// which willl need to be refreshed for every key checked   
	for (int i = 0; i < m_EventKeysCalled.size(); i++) {
		// the keys are stored linearly in order so we can access the array of all the key states using the id value 
		// associated with the key inserted into the m_eventKeysCalled set
		m_keyStates[*m_EventKeysCalled.begin()++].eventState = false;
	}
	for (int i = 0; i < sf::Mouse::ButtonCount; i++) { // refresh mouse state
		m_mouseButtons[i] = false;
	}
	m_EventKeysCalled.clear(); // clear event keys that have been registered as pressed

}


sf::Vector2f InputManager::getMousePos()
{
	return sf::Vector2f(sf::Mouse::getPosition(*m_windowHandle));;
}

void InputManager::addDirectionalMapping(std::string & name, std::map<sf::Keyboard::Key, float>& keyToDirectionMap)
{

	m_directionalMappings.insert({ name,keyToDirectionMap });

}

float InputManager::getDirectionFromKey(std::string&directionalMapName)
{
	if (m_directionalMappings.find(directionalMapName) == m_directionalMappings.end()) {
		std::cout << " COULD NOT FIND DIRECTIONAL MAP NAME: " << directionalMapName << std::endl;
		return 0.0f;
	}

	for each (std::pair<sf::Keyboard::Key,float> linkedKeyFloatPair in  m_directionalMappings[directionalMapName])
	{
	    
		if (sf::Keyboard::isKeyPressed(linkedKeyFloatPair.first)){ 
			
			return linkedKeyFloatPair.second;
		}
	}

	return 0.0f;





}

bool InputManager::getRealTime(sf::Keyboard::Key keyInput)
{
	return sf::Keyboard::isKeyPressed(keyInput);
}