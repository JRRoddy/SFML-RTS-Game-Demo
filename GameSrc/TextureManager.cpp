#include "TextureManager.h"



TextureManager::TextureManager(){
}

TextureManager::~TextureManager(){}

void TextureManager::loadTextures(std::string pathToTextures)
{

	std::ifstream file; 
	std::string line;
	while (std::getline(file, line)) {

		m_storedTextures.insert(std::pair<std::string, sf::Texture>(line, sf::Texture()));

		m_storedTextures[line].loadFromFile(line);



	}




	




}

void TextureManager::loadTexture(std::string pathToTexture)
{
	m_storedTextures.insert(std::pair<std::string, sf::Texture>(pathToTexture, sf::Texture()));

	m_storedTextures[pathToTexture].loadFromFile(pathToTexture);



}

sf::Texture * TextureManager::getTexture(std::string associatedPath)
{
	return &m_storedTextures[associatedPath];
}
