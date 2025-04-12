#include "InputManager.h"


InputManager::InputManager(sf::Window* window)
{

	m_windowHandle = window;

}




void InputManager::pollEvents(sf::Event& event)
{
	m_mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_windowHandle));
	while (m_windowHandle->pollEvent(event)) {

		if (event.type == sf::Event::Closed) m_windowHandle->close();
		if (event.type == event.MouseButtonReleased) m_mouseButtons[event.mouseButton.button] = true;

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

bool InputManager::keyEventStateDown(sf::Keyboard::Key key)
{
	if (m_keyStates[key].eventState) {
		m_EventKeysCalled.insert(key);

	}

	return m_keyStates[key].eventState;
}


bool InputManager::isMouseDown(sf::Mouse::Button button)
{
	return m_mouseButtons[button];
}

bool InputManager::keyEventStateUp(sf::Keyboard::Key key)
{
	return !m_keyStates[key].eventState;
}

void InputManager::endFrame()
{

	for (int i = 0; i < m_EventKeysCalled.size(); i++) {

		m_keyStates[*m_EventKeysCalled.begin()++].eventState = false;
	}
	for (int i = 0; i < sf::Mouse::ButtonCount; i++) {
		m_mouseButtons[i] = false;
	}
	m_EventKeysCalled.clear();

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