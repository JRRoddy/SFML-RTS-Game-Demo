#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h"
class SpriteGenerator {

public:



	
	SpriteGenerator(TextureManager * textureManager);
	std::vector<std::shared_ptr<sf::Sprite>> GenerateSprite(std::string& spriteSheetPath, int sectionWidth, int sectionHeight);
	std::shared_ptr<sf::Sprite> GenerateSprite(std::string& spriteTexturePath);




     


private:
	std::map<std::string, std::vector<std::shared_ptr<sf::Sprite>>>   m_spriteSheets;

	std::map<  std::string, std::shared_ptr<sf::Sprite>   > m_singleSprite;




	TextureManager * m_textureManager;










};