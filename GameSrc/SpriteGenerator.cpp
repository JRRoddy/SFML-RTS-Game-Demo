#include "SpriteGenerator.h"

SpriteGenerator::SpriteGenerator(TextureManager* textureManager)
{
    m_textureManager = textureManager;
    /*m_path = path;
    m_texture.loadFromFile(path);
    m_spriteRef  = std::make_shared<sf::Sprite>( new sf::Sprite(m_texture));*/

}

std::vector<std::shared_ptr<sf::Sprite>> SpriteGenerator::GenerateSprite(std::string& spriteSheetPath, int desiredWidth, int desiredHeight)
{

    if (m_spriteSheets.find(spriteSheetPath) != m_spriteSheets.end()){
       
        return m_spriteSheets[spriteSheetPath];
    }


    m_spriteSheets.insert({ spriteSheetPath,std::vector < std::shared_ptr<sf::Sprite>>{}});

    

    int textureRowSize = round(m_textureManager->getTexture(spriteSheetPath)->getSize().x / desiredWidth);
    int textureColumnSize = round(m_textureManager->getTexture(spriteSheetPath)->getSize().y / desiredHeight);

    
    for (int i = 0; i < textureColumnSize; i++) {
        for (int j = 0; j < textureRowSize; j++) {

            m_spriteSheets[spriteSheetPath].emplace_back((new sf::Sprite(
            *m_textureManager->getTexture(spriteSheetPath),
            sf::IntRect(j*desiredWidth, i*desiredHeight,(j+1)*desiredWidth,(i+1)*desiredHeight)
            )));
            


        }

    }
   

	return m_spriteSheets[spriteSheetPath] ;
}

std::shared_ptr<sf::Sprite> SpriteGenerator::GenerateSprite(std::string & spriteTexturePath)
{
    if (m_singleSprite.find(spriteTexturePath) != m_singleSprite.end()) {

        return m_singleSprite[spriteTexturePath];
    }
    sf::Texture* temp = m_textureManager->getTexture(spriteTexturePath);

    sf::Sprite sprite;
    
    m_singleSprite.insert(
    { 
    spriteTexturePath,std::shared_ptr<sf::Sprite>
    (new sf::Sprite(*temp,sf::IntRect(0,0,temp->getSize().x,temp->getSize().y)))

    });

	return m_singleSprite[spriteTexturePath] ;
}
