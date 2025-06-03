#pragma once
struct GameSettings {

	inline static float soundVolumeModifier ; 
	inline static float menuSFXModifier;
	inline static float musicModifier;
	inline static float maxVolume = 100.0f; 
	GameSettings() {}
	~GameSettings() {}

	
	static void modifySoundObject(sf::Sound* sound) {
		std::cout << "modifying sound " << soundVolumeModifier << std::endl;
		sound->setVolume(maxVolume * soundVolumeModifier);
	}

	static void modifyMenuSoundObject(sf::Sound* sound) {
		std::cout << "modifying menu sound " << menuSFXModifier << std::endl;
		sound->setVolume(maxVolume * menuSFXModifier);
	}

	static void modifyMusicObject(sf::Music * music) {

		music->setVolume(maxVolume * musicModifier);
	}
};