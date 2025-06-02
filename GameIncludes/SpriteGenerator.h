#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h" 
#include "AnimationObject.h"
// class that is used to create a sprite using the texture refernces provided by the texture manager 
class SpriteGenerator {
	
public:
	
	SpriteGenerator(TextureManager * textureManager);
	std::shared_ptr<std::vector<sf::Sprite>>& SpriteGenerator::GenerateAnim(std::string& animPath);	
	std::shared_ptr<std::vector<sf::Sprite>>& SpriteGenerator::GenerateSprite(std::string& spriteSheetPath, int desiredWidth, int desiredHeight);
	std::shared_ptr<sf::Sprite> GenerateSpriteCopy(std::string& spriteTexturePath);
	std::shared_ptr<sf::Sprite> &GenerateSprite(std::string &spriteTexturePath);
	AnimationObject generateAnimationObject(std::string& animPath,std::shared_ptr<sf::Sprite> &baseSpriteRef,float & miliDelay);
	sf::Sprite * getAnimSection(int index,std::string & animPath);
private:
	// in this case each sprite is held in a map based on a path to its texture refernce giving it a unique id 
	
	std::map<std::string, std::shared_ptr<std::vector<sf::Sprite>>>   m_spriteSheets;

	std::map<std::string, std::shared_ptr<sf::Sprite>   > m_singleSprite;

	TextureManager * m_textureManager;



};