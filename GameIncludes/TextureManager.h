#pragma once
#include "SFML/Graphics.hpp"
#include <fstream>
class TextureManager {
 public:
	TextureManager();
	~TextureManager();


	void loadTextures(std::string pathToTextures);
	void loadTexture(std::string pathToTexture);
	sf::Texture * getTexture(std::string associatedPath);
 private:
	
	 std::map<std::string, sf::Texture> m_storedTextures;

};