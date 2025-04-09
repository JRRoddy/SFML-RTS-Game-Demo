#include "SpriteGenerator.h"

SpriteGenerator::SpriteGenerator(TextureManager* textureManager)
{
    m_textureManager = textureManager;


}

std::vector<std::shared_ptr<sf::Sprite>> SpriteGenerator::GenerateSprite(std::string& spriteSheetPath, int desiredWidth, int desiredHeight)
{

    if (m_spriteSheets.find(spriteSheetPath) != m_spriteSheets.end()){ // first we check if the sprite already exists based on the path to its texture
       
        return m_spriteSheets[spriteSheetPath]; // this will avoid duplication of data as we ensure that only one of the sprite is generated and it can be used by many objects 
    }
    m_spriteSheets.insert({ spriteSheetPath,std::vector < std::shared_ptr<sf::Sprite>>{}}); // if the sprite has not been generated we generate a new vector of shadred pointers if we are parsing multiple sprites 
    // we use shared pointers here as not only will they be deallocated automatically when the vector goes out of scope 
    // but this is also due to the fact many objects can hold a refernce to the same sprite and the shared pointer will keep track of its 
    // current refernce count and deallocate accordingly

    // parsing the sprite sheet 
    int textureRowSize = round(m_textureManager->getTexture(spriteSheetPath)->getSize().x / desiredWidth);
    int textureColumnSize = round(m_textureManager->getTexture(spriteSheetPath)->getSize().y / desiredHeight);
    for (int i = 0; i < textureColumnSize; i++) {
        for (int j = 0; j < textureRowSize; j++) {

            m_spriteSheets[spriteSheetPath].emplace_back((new sf::Sprite(
            *m_textureManager->getTexture(spriteSheetPath),
            sf::IntRect(j*desiredWidth, i*desiredHeight,(j+1)*desiredWidth,(i+1)*desiredHeight)
            )));
            
            m_spriteSheets[spriteSheetPath].back().get()->setOrigin(sf::Vector2f(desiredWidth / 2.0f, desiredHeight / 2.0f));
            
        }
        
    }
   

	return m_spriteSheets[spriteSheetPath] ;
}


// seperate method for single sprites using same methodology as above method 
std::shared_ptr<sf::Sprite> SpriteGenerator::GenerateSprite(std::string & spriteTexturePath)
{
    if (m_singleSprite.find(spriteTexturePath) != m_singleSprite.end()) {
        std::cout << "path to texture already existed in sprite generator returning pointer path was " << spriteTexturePath << std::endl;
        return m_singleSprite[spriteTexturePath];
    }
    std::cout << "path to texture didnt exist in sprite generator path was " << spriteTexturePath << std::endl;

    sf::Texture* temp = m_textureManager->getTexture(spriteTexturePath);
    if (temp == nullptr) {

        std::cout << "TEXTURE WAS NULL WHEN BEING ACCESSED IN SPRITE GENERATOR " << std::endl;
        return nullptr;
    }
    sf::Sprite sprite;
    
    m_singleSprite.insert(
    { 
    spriteTexturePath,std::shared_ptr<sf::Sprite>
    (new sf::Sprite(*temp,sf::IntRect(0,0,temp->getSize().x,temp->getSize().y)))
    
    });

    m_singleSprite[spriteTexturePath].get()->setOrigin(sf::Vector2f(temp->getSize()) / 2.0f);

	return m_singleSprite[spriteTexturePath] ;
}
