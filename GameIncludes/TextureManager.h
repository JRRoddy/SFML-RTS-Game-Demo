#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"
#include <fstream>
#include "sstream"
// class that will hold all of the texture refernces for sprites and load them into a map based on their file path 
class TextureManager {
 public:
	TextureManager();
	~TextureManager();


	void loadTextures(std::string &pathToTextures);
	void loadTexture(std::string &pathToTexture); 
	void loadAnims(std::string &pathToAnims);
	sf::Texture * getTexture(std::string &associatedPath);
	
	std::vector<sf::IntRect> getAnimationFrameData(std::string& animPath);

 private:
	
	 std::map<std::string, sf::Texture> m_storedTextures;
	 std::map<std::string, std::vector<sf::IntRect>> m_animationFrameData;
	 	 
};