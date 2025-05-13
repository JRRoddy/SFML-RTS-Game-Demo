#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include <map>
#include <set>
enum inputType
{
	REAL_TIME = 0,
	EVENT_INPUT = 1
};

struct keyState {  // basic strcut used to interpret the current state of a key

	keyState() : realTimeState(0), eventState(0) {}
	keyState(int _realtimeState, int _eventState) : realTimeState(_realtimeState), eventState(_eventState) {};

	int realTimeState = 0;
	int eventState = 0;
};

// class that manages and polls input using the sfml polling system and real time inut from sf keyboard
class InputManager {

public:
	InputManager( sf::Window* window);  // mian constrctor taking in the window to poll input from 
	void pollEvents(sf::Event& event); // takes in the sf event being used in conjunction with the window to poll input
	void resetEventState(sf::Keyboard::Key keyToReset); 
	bool isBound(sf::Keyboard::Key key);
	bool keyReleased(sf::Keyboard::Key key);
	bool mouseReleased(sf::Mouse::Button button);
	bool isMouseDown(sf::Mouse::Button button);
	bool keyEventStateUp(sf::Keyboard::Key key);
	void endFrame();
	bool isDragging(sf::Mouse::Button button);
	sf::Vector2f getMousePos();
	void addDirectionalMapping(std::string& name, std::map<sf::Keyboard::Key,float>& keyToDirectionMap);
	float getDirectionFromKey(std::string&directionalMapName);
	bool getRealTime(sf::Keyboard::Key keyInput);

private:
	bool m_mousePress = false;

	sf::Vector2f m_mousePosition;
	sf::Window* m_windowHandle;
	sf::Event* m_events;
	std::map< std::string, std::map<sf::Keyboard::Key, float>> m_directionalMappings;
	std::set<sf::Keyboard::Key> m_EventKeysCalled;
	keyState m_keyStates[sf::Keyboard::KeyCount]{}; // array of all the keys sfml provides
	bool m_mouseButtons[sf::Mouse::ButtonCount]{ false };

};