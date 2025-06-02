#include "SpriteGenerator.h"

SpriteGenerator::SpriteGenerator(TextureManager* textureManager)
{
    m_textureManager = textureManager;

}

std::shared_ptr<std::vector<sf::Sprite>> &SpriteGenerator::GenerateSprite(std::string &spriteSheetPath, int desiredWidth, int desiredHeight)
{

    if (m_spriteSheets.find(spriteSheetPath) != m_spriteSheets.end()){ // first we check if the sprite already exists based on the path to its texture
       
        return m_spriteSheets[spriteSheetPath]; // this will avoid duplication of data as we ensure that only one of the sprite is generated and it can be used by many objects 
    }
    m_spriteSheets.insert({ spriteSheetPath,std::make_shared<std::vector<sf::Sprite>>(std::vector<sf::Sprite>{}) });
    // we use shared pointers to vectors  here as not only will they be deallocated automatically out of scope 
    // but this is also due to the fact many objects can hold a refernce to the same sprites and the shared pointer will keep track of its 
    // current refernce count and deallocate accordingly

    // parsing the sprite sheet 
    int textureRowSize = round(m_textureManager->getTexture(spriteSheetPath)->getSize().x / desiredWidth);
    int textureColumnSize = round(m_textureManager->getTexture(spriteSheetPath)->getSize().y / desiredHeight);
    for (int i = 0; i < textureColumnSize; i++) {
        for (int j = 0; j < textureRowSize; j++) {

            m_spriteSheets[spriteSheetPath]->emplace_back(
            *m_textureManager->getTexture(spriteSheetPath),
            sf::IntRect(j*desiredWidth, i*desiredHeight,(j+1)*desiredWidth,(i+1)*desiredHeight));
            
            m_spriteSheets[spriteSheetPath]->back().setOrigin(sf::Vector2f(desiredWidth / 2.0f, desiredHeight / 2.0f));
          
        }
        
    }
   

	return m_spriteSheets[spriteSheetPath] ;
}

std::shared_ptr<sf::Sprite> SpriteGenerator::GenerateSpriteCopy(std::string& spriteTexturePath)
{
    if (m_singleSprite.find(spriteTexturePath) == m_singleSprite.end()) {
        sf::Texture* temp = m_textureManager->getTexture(spriteTexturePath);
        m_singleSprite.insert(
            {
            spriteTexturePath,std::shared_ptr<sf::Sprite>
            (new sf::Sprite(*temp,sf::IntRect(0,0,temp->getSize().x,temp->getSize().y)))

            });
        m_singleSprite[spriteTexturePath].get()->setOrigin(
            sf::Vector2f(m_singleSprite[spriteTexturePath]->getTextureRect().getSize() / 2));


    }

    std::shared_ptr<sf::Sprite> copy = std::make_shared<sf::Sprite>(sf::Sprite(*m_singleSprite[spriteTexturePath]->getTexture(), m_singleSprite[spriteTexturePath]->getTextureRect()));
    copy->setOrigin(sf::Vector2f(copy->getTextureRect().getSize()) / 2.0f);
    
    return copy;
}


// seperate method for single sprites using same methodology as above method 
std::shared_ptr<sf::Sprite>& SpriteGenerator::GenerateSprite(std::string &spriteTexturePath)
{
    if (m_singleSprite.find(spriteTexturePath) != m_singleSprite.end()) {
        return m_singleSprite[spriteTexturePath];
    }

    sf::Texture* temp = m_textureManager->getTexture(spriteTexturePath);
   
    
    m_singleSprite.insert(
    { 
    spriteTexturePath,std::shared_ptr<sf::Sprite>
    (new sf::Sprite(*temp,sf::IntRect(0,0,temp->getSize().x,temp->getSize().y)))
    
    });

    m_singleSprite[spriteTexturePath].get()->setOrigin(
    sf::Vector2f(m_singleSprite[spriteTexturePath]->getTextureRect().getSize()/2));
	return m_singleSprite[spriteTexturePath];
}

AnimationObject SpriteGenerator::generateAnimationObject(std::string& animPath,std::shared_ptr<sf::Sprite>& baseSpirteRef,float &animDelay)
{
    // create and animation object 
    AnimationObject anim;
    // if the sprite sheet we want has already been parsed 
    // then return the vector containing the sprites 
    // avoids having to create another duplicate vector 
    if (m_spriteSheets.find(animPath) != m_spriteSheets.end()) {
       anim =  AnimationObject(m_spriteSheets[animPath], baseSpirteRef, animDelay);
       return anim;
    }

    sf::Texture* temp = m_textureManager->getTexture(animPath);


    m_spriteSheets.insert({ animPath,std::make_shared<std::vector<sf::Sprite>>(std::vector<sf::Sprite>{}) });
   // if the vector of sprites was not already created then we need 
    // to create one using the parsed animation data 
    for (sf::IntRect& rect : m_textureManager->getAnimationFrameData(animPath)) {
        // emplace back here to construct the shared ptr object in place within the vector 
       
        // create new sprite with the current texture rect and texture
        m_spriteSheets[animPath]->emplace_back(*temp, rect);
        // set origin of sprite using current texture rect 
        m_spriteSheets[animPath]->back().setOrigin(float(rect.width) / 2, float(rect.height) / 2);
        
    }
    // create the animtaion object with the new vector of sprites passing the shared
    // pointer to the vector allowing multiple animation objects to share the same 
    // frames with the base shared pointer created in the map keeping track of refernces
    // // to it
    // we also pass the base sprite reference(sprite to be animated) that was passed in
    // along with frame delay for each frame of animation 
    anim  = AnimationObject(m_spriteSheets[animPath], baseSpirteRef, animDelay);
    return anim;

}

// used to cut out a specifc part of a sprite sheet animation and 
// return a newly allaocted object to be assigned
sf::Sprite * SpriteGenerator::getAnimSection(int index,std::string & animPath)
{
    
    sf::IntRect textureRect = m_textureManager->getAnimationFrameData(animPath)[index];
    sf::Texture* temp = m_textureManager->getTexture(animPath);
    sf::Sprite * sprite = new sf::Sprite(*temp, textureRect);
    sprite->setOrigin(float(sprite->getTextureRect().width / 2.0f), float(sprite->getTextureRect().height / 2));
    return sprite;
}

std::shared_ptr<std::vector<sf::Sprite>> &SpriteGenerator::GenerateAnim(std::string &animPath)
{
    
    if (m_spriteSheets.find(animPath) != m_spriteSheets.end()) {
        return   m_spriteSheets[animPath];
    }

    sf::Texture* temp = m_textureManager->getTexture(animPath); 

    
    m_spriteSheets.insert({ animPath,std::make_shared<std::vector<sf::Sprite>>(std::vector<sf::Sprite>{}) });
    for (sf::IntRect& rect : m_textureManager->getAnimationFrameData(animPath)){

        m_spriteSheets[animPath]->emplace_back(*temp, rect); 
        m_spriteSheets[animPath]->back().setOrigin(float(rect.width) / 2, float(rect.height) / 2);

    }

    return m_spriteSheets[animPath];
}
