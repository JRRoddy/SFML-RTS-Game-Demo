#pragma once
#include "SFML/Audio.hpp"
#include "map"
#include "string"
#include "vector"
#include "memory"
#include "fstream"
#include "iostream"

class AudioManager {

public:

	AudioManager() {};
	~AudioManager() {};
	void loadSounds(std::string& soundFilePaths); 
	std::shared_ptr<sf::Sound> getSoundObjectCopy(std::string & soundPath);
private:
	std::map<std::string,sf::SoundBuffer> m_soundBuffers;
	




};