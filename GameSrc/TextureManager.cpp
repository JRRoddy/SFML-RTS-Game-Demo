#include "TextureManager.h"



TextureManager::TextureManager(){
}

TextureManager::~TextureManager(){}

void TextureManager::loadTextures(std::string pathToTextures)
{

	std::cout << "loading textures:" << std::endl;


	std::ifstream file; 
	std::string line; 
	file.open(pathToTextures); 

	if (!file.is_open()) {
		std::cout << "could not open path to textures " << pathToTextures << std::endl;
		return;
	}
	std::cout << "found texture paths " << pathToTextures << std::endl;
	while (std::getline(file, line)) {

		std::cout << "Texture path found " << line << std::endl;
		m_storedTextures.insert(std::pair<std::string, sf::Texture>(line, sf::Texture()));

		if (!m_storedTextures[line].loadFromFile(line)) {
			std::cout << "could not load path " << line << std::endl;
		
		
		};



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
