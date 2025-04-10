#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h" 
// class that is used to create a sprite using the texture refernces provided by the texture manager 
class SpriteGenerator {

public:
	
	SpriteGenerator(TextureManager * textureManager);
	std::vector<std::shared_ptr<sf::Sprite>> &GenerateAnim(std::string &animPath);
	std::vector<std::shared_ptr<sf::Sprite>> &GenerateSprite(std::string &spriteSheetPath, int sectionWidth, int sectionHeight);
	std::shared_ptr<sf::Sprite> &GenerateSprite(std::string &spriteTexturePath);


private:
	// in this case each sprite is held in a map based on a path to its texture refernce giving it a unique id 
	
	std::map<std::string, std::vector<std::shared_ptr<sf::Sprite>>>   m_spriteSheets;

	std::map<  std::string, std::shared_ptr<sf::Sprite>   > m_singleSprite;

	TextureManager * m_textureManager;



};