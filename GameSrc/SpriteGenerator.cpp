#include "SpriteGenerator.h"

SpriteGenerator::SpriteGenerator(TextureManager* textureManager)
{
    m_textureManager = textureManager;

}

std::vector<std::shared_ptr<sf::Sprite>> &SpriteGenerator::GenerateSprite(std::string &spriteSheetPath, int desiredWidth, int desiredHeight)
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
std::shared_ptr<sf::Sprite>& SpriteGenerator::GenerateSprite(std::string &spriteTexturePath)
{
    if (m_singleSprite.find(spriteTexturePath) != m_singleSprite.end()) {
        std::cout << "path to texture already existed in sprite generator returning pointer path was " << spriteTexturePath << std::endl;
        return m_singleSprite[spriteTexturePath];
    }

    sf::Texture* temp = m_textureManager->getTexture(spriteTexturePath);
    if (temp == nullptr) {

        std::cout << "TEXTURE WAS NULL WHEN BEING ACCESSED IN SPRITE GENERATOR " << std::endl;
       
    }
    std::cout << "creating sprite for texture path "<<spriteTexturePath << std::endl;
    
    m_singleSprite.insert(
    { 
    spriteTexturePath,std::shared_ptr<sf::Sprite>
    (new sf::Sprite(*temp,sf::IntRect(0,0,temp->getSize().x,temp->getSize().y)))
    
    });

    m_singleSprite[spriteTexturePath].get()->setOrigin(
    sf::Vector2f(m_singleSprite[spriteTexturePath]->getTextureRect().getSize()/2));
	return m_singleSprite[spriteTexturePath] ;
}

AnimationObject SpriteGenerator::generateAnimationObject(std::string& animPath,std::shared_ptr<sf::Sprite>& baseSpirteRef,float &animDelay)
{
    std::cout << "sprite generator generating anim object" << std::endl;
    // create and animation object 
    AnimationObject anim;
    // if the sprite sheet we want has already been parsed 
    // then return the vector containing the sprites 
    // avoids having to create another duplicate vector 
    if (m_spriteSheets.find(animPath) != m_spriteSheets.end()) {
        std::cout << "returining anim object anim was already generated" <<std::endl;
       anim =  AnimationObject(m_spriteSheets[animPath], baseSpirteRef, animDelay);
       return anim;
    }
    std::cout << "returining anim object anim was not already generated" << std::endl;

    sf::Texture* temp = m_textureManager->getTexture(animPath);


    m_spriteSheets.insert({ animPath,std::vector<std::shared_ptr<sf::Sprite>>() });
    std::cout << "looping over anim vector" << std::endl;
   // if the vector of sprites was not already created then we need 
    // to create one using the parsed animation data 
    for (sf::IntRect& rect : m_textureManager->getAnimationFrameData(animPath)) {
        std::cout << "itterating texture rects"<<rect.left <<" " << rect.top << " " << " "<< rect.width <<" " << rect.height << std::endl;
        // emplace back here to construct the shared ptr object in place within the vector 
       
        // create new sprite with the current texture rect and texture
        m_spriteSheets[animPath].emplace_back((new sf::Sprite(*temp, rect)));
        // set origin of sprite using current texture rect 
        m_spriteSheets[animPath].back().get()->setOrigin(float(rect.width) / 2, float(rect.height) / 2);
        
    }
    std::cout << "returning anim" << std::endl;
    // create the animtaion object with the new vector of sprite shared pointers 
    // and the base sprite reference(sprite to be animated) that was passed in
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
    sprite->setOrigin(sprite->getTextureRect().width / 2.0f, sprite->getTextureRect().height / 2);
    return sprite;
}

std::vector<std::shared_ptr<sf::Sprite>> &SpriteGenerator::GenerateAnim(std::string &animPath)
{
    
    if (m_spriteSheets.find(animPath) != m_spriteSheets.end()) {
        return   m_spriteSheets[animPath];
    }

    sf::Texture* temp = m_textureManager->getTexture(animPath); 

    
    m_spriteSheets.insert({ animPath,std::vector<std::shared_ptr<sf::Sprite>>() });
    for (sf::IntRect& rect : m_textureManager->getAnimationFrameData(animPath)){

        m_spriteSheets[animPath].emplace_back((new sf::Sprite(*temp, rect))); 
        m_spriteSheets[animPath].back().get()->setOrigin(float(rect.width) / 2, float(rect.height) / 2);

    }

    return m_spriteSheets[animPath];
}
