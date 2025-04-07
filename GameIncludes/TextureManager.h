#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"
#include <fstream>
// class that will hold all of the texture refernces for sprites and load them into a map based on their file path 
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