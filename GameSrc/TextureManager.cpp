#include "TextureManager.h"



TextureManager::TextureManager(){
}

TextureManager::~TextureManager(){}

void TextureManager::loadTextures(std::string &pathToTextures)
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
	file.close();

}

void TextureManager::loadTexture(std::string &pathToTexture)
{
	m_storedTextures.insert(std::pair<std::string, sf::Texture>(pathToTexture, sf::Texture()));

	m_storedTextures[pathToTexture].loadFromFile(pathToTexture);



}

void TextureManager::loadAnims(std::string &pathToAnims)
{
	
	std::ifstream file;
	std::string line;
	std::istringstream inputData;

	file.open(pathToAnims);

	if (!file.is_open()) {
		std::cout << "could not open path to animations  " << pathToAnims << std::endl;
		return;
	}
	std::cout << "found animation paths " << pathToAnims << std::endl;


	std::string path; // current path to the animation 
	size_t pos;// used to store current position within the string we are parsing from the file 
	bool animationDataContainerInserted = false; // check if we have inserted a vector for each of the top lef positions for  the frame of the animation(avoids using the find method each time) 
	
	// loop that parses animations based on the top left position of each frame of the animation in the sprite sheet 
	while (std::getline(file, line)) { // while we have not reached the end of the file 
		if (line.find("id") != std::string::npos) { // if the line we hit contains the path to the animation sprite sheet texture s
			std::cout << "line " << line << std::endl;
			animationDataContainerInserted = false; // we have not yet inserted the positions into the positions map 
			pos = line.find("id:");  
			path = line.erase(pos, line.find(":") + 1);  // get the current path by erasing the line identifier
			std::cout << "currrent animation path being parsed:" << path << std::endl;
			m_storedTextures.insert({ path, sf::Texture() }); // insert new texture object into the textures map 
			if (!m_storedTextures[path].loadFromFile(path))  // load the animation sprite sheet
			{ 
				std::cout << "could not load animation from path:" << path << std::endl;
				continue;
			}
			std::cout << "animation path found:" << path << std::endl;
			continue;
		}

		// if we dont find any line identifiers
		// we assume the line contains  
		// position and size data  that represent the frame of the animation
		if (animationDataContainerInserted == false) { 
			m_animationFrameData.insert({ path, std::vector<sf::IntRect>() }); // we insert a new vector with the recorded path into the map if we havent already 
			animationDataContainerInserted = true;

		}
		inputData.str(line); // assign the current line as the str buffer being used by the input string stream 
		std::cout << "current frame data being parsed: " << inputData.str() << std::endl;
		int x, y;
		int width, height;
		// parse frame data from the current animation id we are on 
		inputData >> x; 
		inputData >> y; 
		inputData >> width;
		inputData >> height; 
		std::cout << "new anim data x:" << x << " y:" <<y<< " width:" << width << " height:" << height << std::endl;
		// read in the data for this particualr frame within the animation 
		// and emplace it into the vector constructing the object in place meaning no copy 
		m_animationFrameData[path].emplace_back(x, y,width,height); 
		inputData.str(""); 
		inputData.clear();
		
		
	}

	file.close();


}

sf::Texture * TextureManager::getTexture(std::string &associatedPath)
{

	if (m_storedTextures.find(associatedPath) ==m_storedTextures.end()) {
		std::cout << "texture path did not exsist : " << associatedPath << std::endl;
	}

	return &m_storedTextures[associatedPath];
}

std::vector<sf::IntRect> TextureManager::getAnimationFrameData(std::string &animPath)
{
	return m_animationFrameData[animPath];
}


