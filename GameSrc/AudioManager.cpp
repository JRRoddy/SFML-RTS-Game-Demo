#include "AudioManager.h"

void AudioManager::loadSounds(std::string& soundFilePaths)
{

	std::ifstream file; 

	file.open(soundFilePaths); 

	if (!file.is_open())
	{
		std::cout << "could not load path to audio files path: " << soundFilePaths << std::endl;
		return;
	}

	std::string line;

	while (std::getline(file, line)) {

	
		m_soundBuffers.emplace(std::make_pair(line,sf::SoundBuffer()));
		if (!m_soundBuffers[line].loadFromFile(line)) {
			std::cout << "could not load audio file path: " << line << std::endl;
			
		}
		else {
			std::cout << "loaded audio file path: " << line << std::endl;
		}

		

	}



}



std::shared_ptr<sf::Sound> AudioManager::getSoundObjectCopy(std::string& soundPath)
{
	std::shared_ptr<sf::Sound> soundObjectCopy = std::make_shared<sf::Sound>(sf::Sound());
	try {
		soundObjectCopy->setBuffer(m_soundBuffers.at(soundPath)); 
	}
	catch (...) {
		std::cout << "requested sound path couldnt be found path:" << soundPath << std::endl;
	}
	return soundObjectCopy;

}

