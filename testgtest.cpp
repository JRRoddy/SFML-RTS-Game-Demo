/**
 * @file opponent_check.cpp
 * @brief Tests for Warrior and Goblin classes
 */

#include <gtest/gtest.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GameIncludes/GameObject.h"
#include "GameIncludes/TileDeepCopyUtil.h"
#include "GameIncludes/ForestTile.h"
#include "PathTile.h"
#include "RockTile.h"
#include "GameIncludes/Player.h"
#include "GameIncludes/DynamicObject.h"
#include "TextureManager.h" 
#include "PawnAlly.h"
#include "Camera.h"
#include "Goblin.h"
#include "QuadTree.h"
#include "LevelAreaBuilder.h"
#include "LevelAreaManufacturer.h"
#include "LevelGrid.h"
#include "ScoreMenu.h"
// GameObject class unit tests:
class GameObjectTests: public::testing::Test {

public:
    GameObjectTests() {
        m_rotationToSet =  0.0f; 
        m_positionToSet = sf::Vector2f(0.0f, 0.0f);
        m_scaleToSet = sf::Vector2f(0.0f, 0.0f);
    };
protected:
    StaticObject m_GameObjectTest = StaticObject(); 
    sf::Vector2f m_positionToSet;
    sf::Vector2f m_scaleToSet;
    float m_rotationToSet;
  
    
    void SetUp() {

        m_positionToSet = sf::Vector2f(10.0f, 10.0f);
        m_rotationToSet = 10.0f; 
        m_scaleToSet = sf::Vector2f(1.5f, 1.5f);
        

        m_GameObjectTest.setPosition(m_positionToSet); 
        m_GameObjectTest.setRotation(m_rotationToSet); 
        m_GameObjectTest.setScale(m_scaleToSet); 


        



    }










}; 


TEST_F(GameObjectTests, GameObjectUnitTest) {

    // testing getters and setters for gameObject i.e setting postion rot and scale
    EXPECT_EQ(m_positionToSet.x, m_GameObjectTest.getPosition().x);
    EXPECT_EQ(m_rotationToSet, m_GameObjectTest.getRotation());
    EXPECT_EQ(m_scaleToSet.y, m_GameObjectTest.getScale().y);



}

// test for deep copying a specifc tile
class tileDeepCopytest : public::testing::Test {
public:
   

    tileDeepCopytest() {
        m_player = Player();
        m_forest = new ForestTile(sf::Vector2f(10.0f, 15.0f));;// set the position of the tile that will be used for the deep copy
        m_newDeepCopyObject = TileInitialiser(m_forest);
    }



protected:
    std::unique_ptr<Tile> m_tileCopyDestination;
    TileInitialiser m_newDeepCopyObject;
    Tile * m_forest;
    Player m_player;


};

TEST_F(tileDeepCopytest, deepCopyingTilesTest) {
    
    std::cout << "DEEP COPY TEST" << std::endl;
    EXPECT_EQ(m_newDeepCopyObject.getHeldObject()->getPosition().x, 10.0f); // testing the setting of the position for the tile we are copying 
    
    m_tileCopyDestination.reset(  m_newDeepCopyObject.getHeldObjectCopy()); // assingin the other ptr to a supossed copy of the one held in the deep copy object
    bool isEqual = m_tileCopyDestination.get() == m_newDeepCopyObject.getHeldObject();
    EXPECT_EQ(m_tileCopyDestination->getPosition().x, m_newDeepCopyObject.getHeldObject()->getPosition().x);
    EXPECT_EQ(m_tileCopyDestination->getPosition().y, m_newDeepCopyObject.getHeldObject()->getPosition().y);

    std::cout <<"POINTER for the copy :"<< m_tileCopyDestination.get() << " pointer for the object held wihtin the deep copy object " << m_newDeepCopyObject.getHeldObject() << std::endl;
    ASSERT_FALSE(isEqual);  // checking if the deep copy we made is not equal in address( if it fails non of the other test will be valid so we break out of this test)
    m_tileCopyDestination.get()->setPosition(sf::Vector2f(20.0f, 0.0f)); 

    EXPECT_NE(m_tileCopyDestination.get()->getPosition().x, m_newDeepCopyObject.getHeldObject()->getPosition().x); // expect the new set position for the copy to not be equal to the object held in the deep copy object 
    std::cout << "new copy type "<<typeid(*m_tileCopyDestination.get()).name() << std::endl;
    m_tileCopyDestination.get()->dynamicObjectEffect(&m_player);




}
// test fixture to wrap all the tile types under one test class 
class TileTesting:public::testing::Test {

public:
    
    TileTesting() {

        m_forestTile = std::make_unique<ForestTile>(ForestTile());
        m_pathTile = std::make_unique<PathTile>(PathTile());
        m_rockTile = std::make_unique<RockTile>(RockTile());

        m_player = std::make_unique<Player>(Player());
        // setting up data that will be used for tile testing such as 
        // the width and height for each tile and the expected vertices 
        // once they are set for the tile objects defined above
        m_tileWidth = 64.0f;
        m_tileHeight = 64.0f;
        m_positionToSet = sf::Vector2f(10.0f, 0.0f);
        m_tileExpectedVertices.setPrimitiveType(sf::Quads);
        m_tileExpectedVertices.resize(4);
        m_tileExpectedVertices[0] = sf::Vertex(sf::Vector2f(m_positionToSet.x - m_tileWidth / 2.0f, m_positionToSet.y - m_tileHeight / 2.0f), sf::Vector2f(0.0f, 0.0f));
        m_tileExpectedVertices[1] = sf::Vertex(sf::Vector2f(m_positionToSet.x - m_tileWidth / 2.0f, m_positionToSet.y + m_tileHeight / 2.0f), sf::Vector2f(0.0f, m_tileHeight));
        m_tileExpectedVertices[2] = sf::Vertex(sf::Vector2f(m_positionToSet.x + m_tileWidth / 2.0f, m_positionToSet.y + m_tileHeight / 2.0f), sf::Vector2f(m_tileWidth, m_tileHeight));
        m_tileExpectedVertices[3] = sf::Vertex(sf::Vector2f(m_positionToSet.x + m_tileWidth / 2.0f, m_positionToSet.y - m_tileHeight / 2.0f), sf::Vector2f(m_tileWidth, 0.0f));


        
    };
    ~TileTesting() {};


protected:
    std::unique_ptr<ForestTile> m_forestTile;
    std::unique_ptr<PathTile> m_pathTile;
    std::unique_ptr<RockTile> m_rockTile;
    std::unique_ptr<Player> m_player;
    float m_tileWidth = 0.0f;
    float m_tileHeight = 0.0f; 
    sf::Vector2f m_positionToSet;
    sf::VertexArray m_tileExpectedVertices; 





};
// testing tile effects and intergatting them with the player 
TEST_F(TileTesting, ForestTileEffectTest) {

    m_forestTile->dynamicObjectEffect(m_player.get()); 

    EXPECT_EQ(m_player->getSpeedModifier(),m_forestTile->getSpeedModifier());
    




}
TEST_F(TileTesting, PathTileEffectTest) {

    m_pathTile->dynamicObjectEffect(m_player.get());

    EXPECT_EQ(m_player->getSpeedModifier(), m_pathTile->getSpeedModifier());


}
// testing setting position of tiles and ensuring the verticies 
// end up in the correct positions based on defined width and height 
// for the tile 
TEST_F(TileTesting, TilePositionTest) {

    
    m_forestTile->setVerticies(m_tileWidth,m_tileHeight,m_positionToSet );
    EXPECT_EQ(m_forestTile->getPosition().x, m_positionToSet.x);
    EXPECT_EQ(m_tileWidth, m_forestTile->getWidth()); 
    EXPECT_EQ(m_tileHeight, m_forestTile->getHeight());

    // loop through the ste up data for  expected verts and check against set ones
    for (int i = 0; i < 4; i++) {

        EXPECT_EQ(m_tileExpectedVertices[i].position.x, m_forestTile->getVerticies()[i].position.x);
        EXPECT_EQ(m_tileExpectedVertices[i].position.y, m_forestTile->getVerticies()[i].position.y);

    }





}

TEST_F(TileTesting, TileWorldAttributesTest) {

    // testing default walakble values for tiles
    EXPECT_TRUE(m_forestTile->isWalkable());
    EXPECT_TRUE(m_pathTile->isWalkable());
    EXPECT_FALSE(m_rockTile->isWalkable());
    //testing setting walkable values
    m_forestTile->setIsWalkable(false);
    EXPECT_FALSE(m_forestTile->isWalkable());
    // testing spawn cap setting
    m_rockTile->setSpawnCap(4);
    EXPECT_EQ(m_rockTile->getSpawnCap(), 4);







}


// camera test class 
class CameraTest : public::testing::Test {

public:

    CameraTest() {
        // setting up various pieces of data for the camera such as 
        // position reszie data and a position to move the camera to 
        m_positionToSet = sf::Vector2f(10.0f, 10.0f);
        m_positionToMoveTo = sf::Vector2f(20.0f, 20.0f); 
        m_defaultView = sf::FloatRect(0.0f, 0.0f, 200.0f, 200.0f);
        m_resizedView = sf::FloatRect(0.0, 0.0f, 800.0f, 600.0f);
    };
    ~CameraTest() {}; 



protected:
    sf::Vector2f m_positionToSet; 
    sf::Vector2f m_positionToMoveTo;
    sf::FloatRect m_defaultView;
    sf::FloatRect m_resizedView;



};

// checking camera positioning 
TEST_F(CameraTest,CameraPositioningTest) {
    
    sf::RenderWindow window = sf::RenderWindow();
    Camera cam = Camera(&window, m_defaultView);  

    cam.setPosition(m_positionToSet); 

    EXPECT_EQ(cam.getView().getCenter().x, m_positionToSet.x);
    
}

// checking the process of resizing the camera view port  
TEST_F(CameraTest, CameraResizeViewTest) {

    sf::RenderWindow window = sf::RenderWindow();
    Camera cam = Camera(&window, m_defaultView);
   
    cam.resize(m_resizedView);

    EXPECT_EQ(cam.getView().getViewport().width, m_resizedView.getSize().x);
    EXPECT_EQ(cam.getView().getViewport().height, m_resizedView.getSize().y);

}
// testing the process of rellocating the camera position 
TEST_F(CameraTest, CameraRepositionTest) {

    sf::RenderWindow window = sf::RenderWindow();
    Camera cam = Camera(&window, m_defaultView);
   
    cam.setPosition(m_positionToSet); 
    cam.moveToPos(m_positionToMoveTo);
    EXPECT_EQ(cam.getView().getCenter().x, m_positionToMoveTo.x);
    EXPECT_EQ(cam.getView().getCenter().y, m_positionToMoveTo.y);



}


// character tests for setting various properties 
class  CharacterStatsTest: public::testing::Test {
public:
     
    CharacterStatsTest() {
        m_charactersToTest = { new Goblin(),new Pawn() };
        m_positionToSet = sf::Vector2f(10.0f, 50.0f); 
        m_damageToSet = 10.0f;
        m_healthToSet = 50.0f;
    }; 
    ~CharacterStatsTest() {
        for (int i = 0; i < m_charactersToTest.size(); i++) {
            delete m_charactersToTest[i];
        }
    }
    
    
protected:
    std::vector<Character*> m_charactersToTest;
    sf::Vector2f m_positionToSet; 
    float m_damageToSet; 
    float m_healthToSet;


};

// test all stat setting of characters 
TEST_F(CharacterStatsTest, characterStatsTest) {
    std::cout << "testing stats of enemies" << std::endl;
    // loop through al characters contained within the ccharacter vector 
    // whihc is the base class for all npc's allowing for any npc to be included within this 
    //test via upcating them to a character 
    for (int i = 0; i < m_charactersToTest.size(); i++) {
        // set and check various values for the character we are currently 
        // at accessing it via its index 
        m_charactersToTest[i]->setDamage(m_damageToSet); 
        m_charactersToTest[i]->setHealth(m_healthToSet); 
        m_charactersToTest[i]->setPosition(m_positionToSet); 
        EXPECT_TRUE(m_positionToSet.x == m_charactersToTest[i]->getPosition().x); 
        EXPECT_TRUE(m_damageToSet == m_charactersToTest[i]->getDamage());
        EXPECT_TRUE(m_healthToSet == m_charactersToTest[i]->getHealth());

    }


}



// dynamic object unit tests
// side note since the dynamic object encapsulates movement for all dynamic objects player,enemy, and ally 
// the movement tests are carried out on this parent class only as all the movement code is provided to 
// child dynamic objects by this class therefore there is no need to test movement across all dynamic objects 
// just the dynamic object class itself 
class DynamicObjectMovementTest: public::testing::Test {
public:

    
    DynamicObjectMovementTest() {
        m_dynamic = DynamicObject();
        m_sprite = std::make_shared<sf::Sprite>(sf::Sprite());
        m_dynamic.setBaseSprite(m_sprite);
        m_speedValue = 0.0f; 
        m_expectedSpeedModifer = 0.0f;
     
        m_elapsed = 0.0f;
        m_positionToSet = sf::Vector2f(10.0f, 0.0f);
    }
    void SetUp() {

        m_speedValue = 10.0f;
        m_expectedSpeedModifer = 1.0f;
        m_directionToSet = sf::Vector2f(1.0f, 0.0f);
        m_dynamic.setSpeed(m_speedValue);
        m_dynamic.setSpeedModfier(m_expectedSpeedModifer);
        m_dynamic.setDirection(m_directionToSet);
        m_dynamic.setPosition(m_positionToSet);
        
        
    }

    void setMoveDirNegative() {
        m_directionToSet = sf::Vector2f(-1.0f, -1.0f);
        m_dynamic.setDirection(m_directionToSet);

    }

    void setMoveDirPositive() {
        m_directionToSet = sf::Vector2f(1.0f, 1.0f);
        m_dynamic.setDirection(m_directionToSet);
    }
protected:
    float m_elapsed;
    sf::Vector2f m_positionToSet;
    std::shared_ptr <sf::Sprite> m_sprite;
    DynamicObject m_dynamic;
    float m_speedValue;
    float m_expectedSpeedModifer;
    sf::Vector2f m_directionToSet;
    
    

};


// testing setting speed value of dynamic objects
TEST_F(DynamicObjectMovementTest, dynamicObjectSpeedSetTest) {

     
    EXPECT_EQ(m_dynamic.getSpeed(), m_speedValue);


}
TEST_F(DynamicObjectMovementTest, SpeedModifierTest) {


   
    EXPECT_EQ(m_dynamic.getSpeedModifier(), m_expectedSpeedModifer);

}
TEST_F(DynamicObjectMovementTest, setDirectionTest) {

    EXPECT_EQ(m_dynamic.getDirection().x, m_directionToSet.x);
    EXPECT_EQ(m_dynamic.getDirection().y, m_directionToSet.y);

}

TEST_F(DynamicObjectMovementTest,dynamicObjectMovementTestSixtyFramesAsecond) {

    m_elapsed = 1.0f / 60.0f;
    m_dynamic.updatePosition(m_elapsed); 
    // the expected postion for dynamic object based its set movement parameters
    sf::Vector2f newExpectedPosition = m_positionToSet + ((m_directionToSet * m_speedValue)*m_expectedSpeedModifer) * m_elapsed;
    
    EXPECT_EQ(m_dynamic.getPosition().x, newExpectedPosition.x);
    EXPECT_EQ(m_dynamic.getPosition().y, newExpectedPosition.y);
    // check that the sprites position was set correctly based on the dynamic object's new position
    EXPECT_EQ(m_dynamic.getBaseSprite()->getPosition().x, newExpectedPosition.x);
    EXPECT_EQ(m_dynamic.getBaseSprite()->getPosition().y, newExpectedPosition.y);

}
TEST_F(DynamicObjectMovementTest, dynamicObjectMovementTestThirtyFramesAsecond) {
    
    
    m_elapsed = 1.0f / 30.0f;
    m_dynamic.updatePosition(m_elapsed);
    sf::Vector2f newExpectedPosition = m_positionToSet + ((m_directionToSet * m_speedValue) * m_expectedSpeedModifer) * m_elapsed;

    EXPECT_EQ(m_dynamic.getPosition().x, newExpectedPosition.x);
    EXPECT_EQ(m_dynamic.getPosition().y, newExpectedPosition.y);

    EXPECT_EQ(m_dynamic.getBaseSprite()->getPosition().x, newExpectedPosition.x);
    EXPECT_EQ(m_dynamic.getBaseSprite()->getPosition().y, newExpectedPosition.y);
   



}

TEST_F(DynamicObjectMovementTest, VaryingFrameRateMovementTest) {

    m_elapsed = 1.0f / 60.0f;
    
    m_dynamic.updatePosition(m_elapsed);
    sf::Vector2f sixtyFrameSecondPos = m_dynamic.getPosition();
    sf::Vector2f sixtyFPSExpectedPosition = m_positionToSet + ((m_directionToSet * m_speedValue) * m_expectedSpeedModifer) * m_elapsed;
    EXPECT_EQ(m_dynamic.getPosition().x, sixtyFPSExpectedPosition.x);
    EXPECT_EQ(m_dynamic.getPosition().y, sixtyFPSExpectedPosition.y);
    m_dynamic.setPosition(m_positionToSet); 

    m_elapsed = 1.0f / 30.0f;
    m_dynamic.updatePosition(m_elapsed); 
    sf::Vector2f thiryFrameSecondPos = m_dynamic.getPosition();
    sf::Vector2f thirtyFPSExpectedPosition = m_positionToSet + ((m_directionToSet * m_speedValue) * m_expectedSpeedModifer) * m_elapsed;
    EXPECT_EQ(m_dynamic.getPosition().x, thirtyFPSExpectedPosition.x);
    EXPECT_EQ(m_dynamic.getPosition().y, thirtyFPSExpectedPosition.y);

    // ensuring that positions for dynamic objects remain relative to eachother 
    // despite varying delta time(while removing any floating point precision)
    EXPECT_EQ(floor(sixtyFrameSecondPos.x), floor(thiryFrameSecondPos.x));
    EXPECT_EQ(floor(sixtyFrameSecondPos.y), floor(thiryFrameSecondPos.y));


}

// this test checks that the dynamic object moves according to the set direction 
// by checking if it has moved further than the set position or behind it depending on if the direction 
// set for the movement of the dynamic object is positive or negative
TEST_F(DynamicObjectMovementTest, TestingDirectionalMovementForDynamicObjects) {

    m_elapsed = 1 / 60.0f; 
    setMoveDirNegative(); 
    m_dynamic.updatePosition(m_elapsed);
    EXPECT_LT(m_dynamic.getPosition().x, m_positionToSet.x);
    EXPECT_LT(m_dynamic.getPosition().x, m_positionToSet.x);

   
    m_dynamic.setPosition(m_positionToSet);
    setMoveDirPositive();
    m_dynamic.updatePosition(m_elapsed);
    EXPECT_GT(m_dynamic.getPosition().x, m_positionToSet.x);
    EXPECT_GT(m_dynamic.getPosition().x, m_positionToSet.x);









}

// texture manager unit test
class TextureManagerTest : public::testing::Test {
public:

    TextureManagerTest() {

        m_textureManager = TextureManager();
        
    }
    void SetUp() {
        m_pathToLoad = "../Assets/Textures/GrassBackground0.png";       
    }
protected:
    std::string m_pathToLoad;
    std::string m_pathToAnimations = "../Assets/Animations/PathsToAnimations.txt";
    std::string m_knownAnimationPath = "../Assets/Animations/goblinRunAnim.png";
    TextureManager m_textureManager;
 

};

TEST_F(TextureManagerTest, LoadingAnimationsTest) {

    m_textureManager.loadAnims(m_pathToAnimations); 
    std::map<std::string, std::vector<sf::IntRect>> expectedAnimationFrameData = m_textureManager.getAnimationFrameDataMap();

    ASSERT_NE(expectedAnimationFrameData.size(), 0); 
    // asserting that the map used to link animation frame data to a particualr animation 
    // file path does not throw an exception when we attempt to key into a known animation 
    // that should have been loaded using the file path for the animation
    std::map<std::string, std::vector<sf::IntRect>>::iterator it; 
    // testing the stl find algorithm whihc will search through the  tree associated with a map and 
    // return the itterator associated with a particualr item 
    // this test is to ensure that data for a known animation 
    // that should have been inserted when we loaded animations 
    // in the texture manager is present within the map that stores 
    // animations linked to their asset path(the key value in the map)
    it = expectedAnimationFrameData.find(m_knownAnimationPath);
    ASSERT_NE(it, expectedAnimationFrameData.end());

}


// load from file and accessing map of texture in texture manager test
// ensuring that the texture returned was properly created when we key 
// into the map that stores all the textures 
TEST_F(TextureManagerTest, loadFileTest) {

    m_textureManager.loadTexture(m_pathToLoad); 
    EXPECT_NE(m_textureManager.getTexture(m_pathToLoad), nullptr);
}


class SpriteGeneratorTest: public::testing::Test {


public:

    SpriteGeneratorTest() {
        m_textureManager = std::make_unique<TextureManager>(TextureManager());
        m_textureManager->loadTextures(m_pathToTextures);
        m_textureManager->loadAnims(m_pathToAnimations);
        m_baseSpriteRef = std::make_shared<sf::Sprite>(sf::Sprite());
        m_spriteGenerator = std::make_unique<SpriteGenerator>(SpriteGenerator(m_textureManager.get()));
        m_singleSpriteTestDim = sf::Vector2f(35.0f, 64.0f);
    }
    ~SpriteGeneratorTest() { 
    
       
    }




protected:
    
    std::unique_ptr<TextureManager> m_textureManager; 
    std::unique_ptr<SpriteGenerator> m_spriteGenerator;
    std::shared_ptr<sf::Sprite> m_baseSpriteRef;
    std::string m_pathToTextures = "../Assets/Textures/PathsToTextures.txt";
    std::string m_animationPathToTest = "../Assets/Animations/KnightIdleBlue.png";
    std::string m_pathToAnimations = "../Assets/Animations/PathsToAnimations.txt";
    std::string m_singleSpritePath = "../Assets/Textures/flagIndicator.png";
    size_t m_testAnimationFrameSize = 6;
    sf::Vector2f m_singleSpriteTestDim;
    float m_testAnimationMiliDelay = 70.0f;
};


// test the generation of a single animation
TEST_F(SpriteGeneratorTest, TestSingleAnimationCreation) {


   std::shared_ptr<std::vector<sf::Sprite>> testAnimLoad =  m_spriteGenerator->GenerateAnim(m_animationPathToTest);
   // test that the number of frames in the animation provided by sprite generator  is equal to the expected amount
   ASSERT_NE(testAnimLoad.get(), nullptr);
   EXPECT_EQ(testAnimLoad.get()->size(), m_testAnimationFrameSize);

}

TEST_F(SpriteGeneratorTest, TestSingleSpriteGeneration) {

   std::shared_ptr<sf::Sprite> sprite =  m_spriteGenerator->GenerateSprite(m_singleSpritePath);
   // test the the sprite returned is not empty 
   // i.e  here we assert as all proceeding test will cause errors if null result
   ASSERT_NE(sprite.get(), nullptr); 
   // test that the sprite returned by the sprite generator has the macthing texture rect for the expected texture
   EXPECT_EQ(sprite.get()->getTextureRect().getSize().x, m_singleSpriteTestDim.x);
   EXPECT_EQ(sprite.get()->getTextureRect().getSize().y, m_singleSpriteTestDim.y);


}

TEST_F(SpriteGeneratorTest, AnimationObjectGenerationTest) {

    
    AnimationObject animationObject = m_spriteGenerator->generateAnimationObject(m_animationPathToTest, m_baseSpriteRef, m_testAnimationMiliDelay);
    // test that animation object was set up correctly on generation in sprite generator
    EXPECT_EQ(animationObject.getFrameDelay().asMilliseconds(), m_testAnimationMiliDelay); 
    EXPECT_EQ(animationObject.getframes()->size(), m_testAnimationFrameSize); 
    EXPECT_FALSE(animationObject.animAtEnd());

}
// testing an animation object which encapsulates a singlar animation
class AnimationObjectTests:public::testing::Test {

public:
    AnimationObjectTests() {
        // setting up sprite and texture data for the animation(these were previously tested above)
        m_textureManager = std::make_unique<TextureManager>(TextureManager());
        m_textureManager->loadAnims(m_pathToAnimations);
        m_baseSpriteRef = std::make_shared<sf::Sprite>(sf::Sprite());
        m_spriteGenerator = std::make_unique<SpriteGenerator>(SpriteGenerator(m_textureManager.get()));
        // set up the animation object by generating it using the sprite generator
        m_animationMiliDelayTest = 70.0f;
        m_animationObjectTest = std::make_unique<AnimationObject>(m_spriteGenerator->generateAnimationObject(m_animationPathToTest, m_baseSpriteRef, m_animationMiliDelayTest));
   
    };
    ~AnimationObjectTests() {};

protected:
    std::unique_ptr<TextureManager> m_textureManager;
    std::unique_ptr<AnimationObject> m_animationObjectTest;
    std::unique_ptr<SpriteGenerator> m_spriteGenerator;
    std::shared_ptr<sf::Sprite> m_baseSpriteRef;
    float m_animationMiliDelayTest;
    size_t m_testAnimationFrameSize = 6;
    std::string m_pathToAnimations = "../Assets/Animations/PathsToAnimations.txt";
    std::string m_animationPathToTest = "../Assets/Animations/KnightIdleBlue.png";

};


TEST_F(AnimationObjectTests, animationplayTest) {

    // assert that the animation object was generated correctly with the correct number of frames
    ASSERT_EQ(m_animationObjectTest->getframes()->size(), m_testAnimationFrameSize);
    EXPECT_FALSE(m_animationObjectTest->animAtEnd()); 
    // ensure that the last index into the frames stored in the anim object
    // is equal to the expected value 
    size_t lastFrameIndex = m_animationObjectTest->getframes()->size() - 1;
    ASSERT_EQ(lastFrameIndex, m_testAnimationFrameSize-1);

    while (!m_animationObjectTest->animAtEnd()) {
        m_animationObjectTest->play();
    }

    sf::IntRect lastFrameSize = m_animationObjectTest->getframes()->at(lastFrameIndex).getTextureRect(); 
    // expect the frame sizes of the sprite to be the same as the last frame of the animation
    // being used by the animation object as we passed the base sprite ref variable by refernce 
    // to the animation object for that sprite to be animated by the animation object
    EXPECT_EQ(m_baseSpriteRef->getTextureRect().getSize().x, lastFrameSize.getSize().x);
    EXPECT_EQ(m_baseSpriteRef->getTextureRect().getSize().y ,lastFrameSize.getSize().y);

  
   
   
} 


// main test fixture for testing collision s between dyanmic objects and performing out of bounds tests on 
// dynamic objects this class sets up various data such as positions for colliding game objects and various 
// positions for out of bound testing to ensure that all cases and directions are convered when a dynamic 
// object attempts to leave its defined bounding box that contains it 
class DynamicObjectCollisionTests:public::testing::Test {

public:

    DynamicObjectCollisionTests() {
        
        m_defaultColliderWidth = 20;
        m_defaultColliderHeight = 30; 
        m_gameObjectOtherPosition = sf::Vector2f(200.0f, 300.0f);
        m_gameObjectPosition = sf::Vector2f(200.0f, 300.0f);
        m_gameObjectOtherRect = sf::IntRect(0, 0, 20, 30);
        m_gameObjectRect = sf::IntRect(0, 0, 20, 30);
        


        m_gameObject = std::make_unique<DynamicObject>(DynamicObject(new sf::Sprite(sf::Texture(), m_gameObjectOtherRect)));
        m_gameObjectOther = std::make_unique<DynamicObject>(DynamicObject(new sf::Sprite(sf::Texture(), m_gameObjectRect)));
        
        
    };
    ~DynamicObjectCollisionTests() {
      
       
    };

    void setBoundsToContainDynamicObject(sf::FloatRect bounds) {

        m_boundsToContainDynamicObject = bounds;
    }

    void setGameObjectOtherBounds(int width, int height) {
        m_gameObjectOtherRect = sf::IntRect(m_gameObjectOtherRect.left, m_gameObjectOtherRect.top, width, height);
        m_gameObjectOther->setCollisionBounds(m_gameObjectOtherRect);
        
    }

    void setGameObjectBounds(int width, int height) {
        m_gameObjectRect = sf::IntRect(m_gameObjectOtherRect.left, m_gameObjectOtherRect.top, width, height);
        m_gameObject->setCollisionBounds(m_gameObjectRect);
    }

    void setNoCollision() {
      
        m_gameObject->setPosition(sf::Vector2f(0.0f, 0.0f));
    }

    void setDefaultBoundsTestData() {
        m_defaultContainerWidth = 800.0f;
        m_defaultContainerHeight = 600.0f;
        m_elapsed = 1.0f / 60.0f;
        m_boundsToContainDynamicObject = sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(m_defaultContainerWidth, m_defaultContainerHeight));

        setPositionsForBoundaryChecks(m_gameObject->getBounds().width,m_gameObject->getBounds().height);

        

    }
    bool checkForDynamicObjectOutOfBounds(DynamicObject * dynamicObject) {

        bool checkTop = dynamicObject->getPosition().x < m_boundsToContainDynamicObject.left || dynamicObject->getPosition().y < m_boundsToContainDynamicObject.top;
        bool checkBottom =  dynamicObject->getPosition().x > m_boundsToContainDynamicObject.left + m_boundsToContainDynamicObject.width
                            || dynamicObject->getPosition().y > m_boundsToContainDynamicObject.top + m_boundsToContainDynamicObject.height;
        return checkTop || checkBottom;
    }
    void setPositionsForBoundaryChecks(float colliderWidth, float colliderHeight) {

        
        
        m_positionsToTestAgainstBounds = 
        {
            
            sf::Vector2f(m_boundsToContainDynamicObject.left + colliderWidth/2.0f, m_boundsToContainDynamicObject.top + colliderHeight/2.0f),
            sf::Vector2f(m_boundsToContainDynamicObject.left + colliderWidth/2.0f, (m_boundsToContainDynamicObject.top + m_boundsToContainDynamicObject.height) - colliderHeight/2.0f),
            sf::Vector2f((m_boundsToContainDynamicObject.left + m_boundsToContainDynamicObject.width) - colliderWidth/2.0f, m_boundsToContainDynamicObject.top + colliderHeight/2.0f),
            sf::Vector2f((m_boundsToContainDynamicObject.left + m_boundsToContainDynamicObject.width) - colliderWidth/2.0f, (m_boundsToContainDynamicObject.top + m_boundsToContainDynamicObject.height) - colliderHeight/2.0f),


        };







    }
    void SetUp() {
        m_gameObjectOther->setPosition(m_gameObjectOtherPosition);
        m_gameObject->setPosition(m_gameObjectPosition);
        m_gameObject->setCollisionBounds(m_gameObjectRect);
        m_gameObjectOther->setCollisionBounds(m_gameObjectRect);

    }
    void TearDown() {
        
    }

protected:
    std::unique_ptr<DynamicObject> m_gameObject; 
    std::unique_ptr<DynamicObject> m_gameObjectOther;
    std::shared_ptr<sf::Sprite> m_gameObjectSprite; 
    std::shared_ptr<sf::Sprite> m_gameObjectOtherSprite;
    sf::FloatRect m_boundsToContainDynamicObject;
    sf::IntRect m_gameObjectOtherRect;
    sf::IntRect m_gameObjectRect;
    sf::Vector2f m_gameObjectPosition; 
    sf::Vector2f m_gameObjectOtherPosition;
    std::vector<sf::Vector2f> m_positionsToTestAgainstBounds;
    std::vector<sf::Vector2f> m_directionsToPush;
    int m_defaultColliderWidth = 0;
    int m_defaultColliderHeight = 0;
    float m_defaultContainerWidth = 0.0f;
    float m_defaultContainerHeight = 0.0f;
    float m_elapsed = 0.0f;


};


// testing the collision between two dynamic game objects based on their bounds 
// set by the default values wihtin the GameObjectCollisionTests test fixture 
// which based on those default values in the fixture
// should result in a direct overlap collision between the two game objects
TEST_F(DynamicObjectCollisionTests, DefaultCollisionValuesTest) {

    EXPECT_EQ(m_gameObject->getBounds().getSize().x, m_defaultColliderWidth);
    EXPECT_EQ(m_gameObject->getBounds().getSize().y, m_defaultColliderHeight);

    EXPECT_TRUE(m_gameObject->getBounds().intersects(m_gameObjectOther->getBounds()));

}
// testing that that the bounds used by the dynamic game object for collsion are shifted correctly 
// by testing that there is no collision in a scenario where one game object was moved away from
// the other by a distance that should not result in collision
TEST_F(DynamicObjectCollisionTests, NoCollisionTest) {

    setNoCollision();
    EXPECT_FALSE(m_gameObject->getBounds().intersects(m_gameObjectOther->getBounds()));


}

// test that the collsion box of a dynamic game object camn be resized corretly with a new 
// widht and height and then test that the two dynamic game objects being tested still collide 
// based on the new resized collision box of one of the dynamic game objects
TEST_F(DynamicObjectCollisionTests, ModifyBoundsTest) {

    int newBoundsWidth = 40;
    int newBoundsHeight = 45;
    setGameObjectBounds(newBoundsWidth, newBoundsHeight);

    EXPECT_EQ(m_gameObject->getBounds().getSize().x, float(newBoundsWidth));
    EXPECT_EQ(m_gameObject->getBounds().getSize().y, float(newBoundsHeight));

    EXPECT_TRUE(m_gameObject->getBounds().intersects(m_gameObjectOther->getBounds()));


}
// this test is a stress test for constraining dyanmic objects to a particualr conatiner
// meaning that their position cant go beyond the bounds defined 
// we place the dynamic object in various preset positions defined in the test fixture 
// which places the dynamic object in the very corners of the bounding box that the dynamic object is restricted to 
// and pushes against those bounds diagonally testing many different directions based on the current corner the
// of the bounding box that the dynamic object is contained in 
TEST_F(DynamicObjectCollisionTests, BoundsContainmentTest) {

    setDefaultBoundsTestData();
    // set the direction to be fully diagonal 
    sf::Vector2f directionToPush = sf::Vector2f(1.0f, 1.0f);
    // get the centre of the current bounding box that will restrict the movement of the dynamic object 
    sf::Vector2f boundsCentrePos = sf::Vector2f(m_boundsToContainDynamicObject.left + m_defaultContainerWidth / 2.0f, m_boundsToContainDynamicObject.top + m_defaultContainerHeight / 2.0f);
    // itterate through the defined data set of positions by the test fixture 
    for (std::vector<sf::Vector2f>::iterator it = m_positionsToTestAgainstBounds.begin(); it != m_positionsToTestAgainstBounds.end(); it++) {
        m_gameObject->setPosition(*it);
        // reset direction per itteration 
        directionToPush = sf::Vector2f(abs(directionToPush.x), abs(directionToPush.y));
        
        // set the direction based on current corner position of the dynamic object 
        if (it->x < boundsCentrePos.x) {

            directionToPush = sf::Vector2f(abs(directionToPush.x) * -1.0f, directionToPush.y); 
            std::cout << "bounds centre pos x " << boundsCentrePos.x << std::endl;
        }
        if (it->y < boundsCentrePos.y ) {

            directionToPush = sf::Vector2f(directionToPush.x ,abs( directionToPush.y) * -1.0f);
            std::cout << "bounds centre pos y  " << boundsCentrePos.y << std::endl;

        }
        std::cout << "direction for object " << directionToPush.x << ":" << directionToPush.y << std::endl; 
        std::cout << "position set for object " << it->x << ":" << it->y << std::endl;

        // set the direction for the dynamic object to move 
        m_gameObject->setDirection(directionToPush);
        // update the position passing in the bounds that the dynamic object should be restricted to 
        m_gameObject->updatePosition(m_elapsed, m_boundsToContainDynamicObject);

        // this function will check for if the dynamic object's position slips out of bounds 
        // which should be false as the movement function of the dynamic object should be restricted to the defined 
        // bounding box 
        ASSERT_FALSE(checkForDynamicObjectOutOfBounds(m_gameObject.get()));


    }


}


// this calss is desgined to test the quad tree data structure which is used as part of the collision detection throughout 
// the game as it is running this data structure acts as a method of braod phase collision that stores gameObjects along side their bounding box 
// using that bounding box to then divdie up the space that the game object is considered to be in until that space roughly matches its bounding box 
// this means that when we query the quad tree we only check for the objects that could potentially intersect the bounding box 
// we are using to query it by traversing down the tree in directions that are based on whether or not the game object is conatined whtin 
// a particualr space defined by the quad tree and the other objects bound volumes contained within the tree 
class CollisionQuadTreeTesting:public::testing::Test {

public:

    CollisionQuadTreeTesting() {

        m_collisionTreeBounds = sf::FloatRect(0, 0, 800, 600);
        // the quad tree is a tempate class meaning that it can be used to store objects of any type 
        // therefore we define two trees of different types using the enemy base class and the ally base class 
        // ensuring the behaviour of the quad tree template class remains the same no matter the type passed in 
        m_enemyCollisionTree = std::make_shared<QuadTree<EnemyBase>>(QuadTree<EnemyBase>(m_collisionTreeBounds, 8));
        m_allyCollisionTree = std::make_shared<QuadTree<AllyBase>>(QuadTree<AllyBase>(m_collisionTreeBounds, 8));

    }
    void addAllyToCollisionTree(AllyBase * ally,sf::FloatRect bounds ){
       
        m_allyCollisionTree->insert(bounds, ally);
    
    }
    void addEnemyToCollisionTree(EnemyBase* enemy,sf::FloatRect bounds) {

        m_enemyCollisionTree->insert(bounds, enemy);

    }


    void setBoudningboxToUseForQuery(sf::FloatRect boundingBox) {
        m_boundingBoxUsedForQuery = boundingBox;
    }
    //clear all items for trees at the end of each test
    void TearDown() {

        m_allyCollisionTree->clearItems();
        m_enemyCollisionTree->clearItems();
    }

protected:

    std::shared_ptr<QuadTree<EnemyBase>> m_enemyCollisionTree;
    std::shared_ptr<QuadTree<AllyBase>> m_allyCollisionTree;
    sf::FloatRect m_boundingBoxUsedForQuery;
    sf::FloatRect m_collisionTreeBounds;

};




// testing the insertsion and querying of the quad tree data structure this query should 
// return all the objects that were inserted into the tree as the bounding box used for the tree is the same size as 
// the area the tree is managing 
TEST_F (CollisionQuadTreeTesting, allQueryTestForAllyBaseType) {


    std::vector<std::shared_ptr<AllyBase>> allies;
    
    int amountOfAlliesToAddToTree = 5;

    sf::FloatRect boundingBox = sf::FloatRect(m_collisionTreeBounds.getSize() / 2.0f, sf::Vector2f(40.0f,40.0f));
    // create shared pointers to ally objects of a particualr number 
   for (int i = 0; i < amountOfAlliesToAddToTree; i++) {
        
        allies.emplace_back();
        allies.back().reset(new AllyBase());
        m_allyCollisionTree->insert(boundingBox, allies.back().get());


   }
   // set up the vetcor that will have the results pushed to it from the query
    std::vector<quadTreeItem<AllyBase>> allyCollisionTreeQueryResult;  
    // set the bounding box that will be used to query the tree with a particualr space 
    setBoudningboxToUseForQuery(m_collisionTreeBounds);
    /// query the tree containing alll the ally base object references 
    m_allyCollisionTree->query(m_boundingBoxUsedForQuery,allyCollisionTreeQueryResult);

    // expect that we get the same amount of allies from the collsion tree query reuslt as we inserted 
    // as we used a bounding box that covered the entire area the tree was managing 
    EXPECT_EQ(amountOfAlliesToAddToTree, allyCollisionTreeQueryResult.size());
    // clear vector for next query 
    allyCollisionTreeQueryResult.clear();
    // this time we query the tree with the defined bounding box that was defined for each ally object 

    m_allyCollisionTree->query(boundingBox, allyCollisionTreeQueryResult);
    // we should also get all the ally objects back in this case as all the bounding boxes were set to the same 
    // size and position when inserted into the quad tree 
    EXPECT_EQ(amountOfAlliesToAddToTree, allyCollisionTreeQueryResult.size());


}



// here we conduct the same unit test for the collision tree as above however this time it is using the quad tree template
//class with a template argument of enemy base instead of ally base this test ensures that the quad tree class does not 
// exhibit any undefined behaviour when making use of different types(that it may store) for its template argument 
// demonstraing its ability to handle multiple types under the same conditions
TEST_F(CollisionQuadTreeTesting, enemyQueryTestForAllyBaseType) {


    std::vector<std::shared_ptr<EnemyBase>> enemies;

    int amountOfEnemiesToAddToTree = 5;

    sf::FloatRect boundingBox = sf::FloatRect(m_collisionTreeBounds.getSize() / 2.0f, sf::Vector2f(40.0f, 40.0f));
    // create shared pointers to enemy objects of a particualr number 
    for (int i = 0; i < amountOfEnemiesToAddToTree; i++) {

        enemies.emplace_back();
        enemies.back().reset(new EnemyBase());
        m_enemyCollisionTree->insert(boundingBox, enemies.back().get());


    }
    // set up the vetcor that will have the results pushed to it from the query
    std::vector<quadTreeItem<EnemyBase>> enemyCollisionTreeQueryResult;
    // set the bounding box that will be used to query the tree with a particualr space 
    setBoudningboxToUseForQuery(m_collisionTreeBounds);
    /// query the tree containing alll the enemy base object references 
    m_enemyCollisionTree->query(m_boundingBoxUsedForQuery, enemyCollisionTreeQueryResult);

    // expect that we get the same amount of enemies from the collsion tree query reuslt as we inserted 
   // as we used a bounding box that covered the entire area the tree was managing 
    EXPECT_EQ(amountOfEnemiesToAddToTree, enemyCollisionTreeQueryResult.size());

    // clear vector for next query 
    enemyCollisionTreeQueryResult.clear();
    // this time we query the tree with the defined bounding box that was defined for each enemy object 

    m_enemyCollisionTree->query(boundingBox, enemyCollisionTreeQueryResult);
    // we should also get all the enemy objects back in this case as all the bounding boxes were set to the same 
    // size and position when inserted into the quad tree 
    EXPECT_EQ(amountOfEnemiesToAddToTree, enemyCollisionTreeQueryResult.size());





}

// this test ensures that the collsion tree does not return any unexpected results when there are two ally objects that 
// should not share the same space, ensuring that there are no ally objects that are returned in results when there shouldnt be 
TEST_F(CollisionQuadTreeTesting, emptyQueryAlliesTest) {

    std::shared_ptr<AllyBase> ally;
    std::shared_ptr<AllyBase> allyOther; 
    // defining the bounding boxes of the two ally obejcts 
    sf::FloatRect allyBoundingBox = sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(10.0f, 10.0f)); 
    sf::FloatRect allyOtherBoundingBox = sf::FloatRect(400.0f,400.0f,10.0f,10.0f);


    ally.reset(new AllyBase());
    allyOther.reset(new AllyBase());

    // inserting the ally objects and their bounding boxes into the quad tree 
    m_allyCollisionTree->insert(allyBoundingBox, ally.get());
    m_allyCollisionTree->insert(allyOtherBoundingBox, allyOther.get());


    std::vector<quadTreeItem<AllyBase>> allies; 
    // getting the results back from the quad tree by querying it with one of the ally object bounding boxes 
    m_allyCollisionTree->queryExlusive(allyBoundingBox, allies, ally.get()); 

    // here we expect there to be no results returned by the collision tree 
    // as the two ally objects inserted should not share the same space within the collision tree 
    EXPECT_EQ(allies.size(), 0);


}
// this test ensures that the collsion tree does not return any unexpected results when there are two enemy objects that 
// should not share the same space, ensuring that there are no enemy objects that are returned in results when there shouldnt be 
TEST_F(CollisionQuadTreeTesting, emptyQueryEnemiesTest) {

    std::shared_ptr<EnemyBase> enemy;
    std::shared_ptr<EnemyBase> enemyOther;
    // defining the bounding boxes of the two enemy obejcts 
    sf::FloatRect enemyBoundingBox = sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(10.0f, 10.0f));
    sf::FloatRect enemyOtherBoundingBox = sf::FloatRect(400.0f, 400.0f, 10.0f, 10.0f);


    enemy.reset(new EnemyBase());
    enemyOther.reset(new EnemyBase());

    // inserting the enemy objects and their bounding boxes into the quad tree 
    m_enemyCollisionTree->insert(enemyBoundingBox, enemy.get());
    m_enemyCollisionTree->insert(enemyOtherBoundingBox, enemyOther.get());


    std::vector<quadTreeItem<EnemyBase>> enemies;
    // getting the results back from the quad tree by querying it with one of the enemy object bounding boxes 
    m_enemyCollisionTree->queryExlusive(enemyBoundingBox, enemies, enemy.get());

    // here we expect there to be no results returned by the collision tree 
    // as the two enemy objects inserted should not share the same space within the collision tree 

    EXPECT_EQ(enemies.size(), 0);


}


// this particualr test fixure is desginig to test the level builders ability to configure all the properties of a level 
// area and ensure that all the properies configured were set correctly according to the desired values both when 
// set indivually and when combined ensuring that there is no issues when performing initialisation of certain 
// properties for the level areas through the level builder both on there own and combined with other properties
class LevelAreaBuilderTests:public::testing::Test{

public:
   
    LevelAreaBuilderTests() {

        m_textureManager = std::make_unique<TextureManager>(TextureManager());
        m_textureManager->loadTextures(m_pathToTextures);
        m_spriteGenerator = std::make_unique<SpriteGenerator>(SpriteGenerator(m_textureManager.get())); 

        m_levelAreaBuilder = std::make_unique<LevelAreaBuilder>(LevelAreaBuilder(m_spriteGenerator.get()));
        m_allyNpcsForAreaTobeConstructed = { AllyInitialiser(new AllyBase()) };
        m_enemyNpcsForAreaTobeConstructed = { EnemyInitialiser(new EnemyBase()) };  
        
        m_backGroundPathsForLevelArea = {
            "../Assets/Textures/GrassBackground0.png"

        };

        m_randomlyGeneratedTilesToBeUsedInConstruction = {

            TileInitialiser(new RockTile()),
            TileInitialiser(new ForestTile()),



        };
        m_imageMappedTilesToBeUsedInConstruction = {

            {"Path",TileInitialiser(new PathTile())}



         };




    }

    LevelAreaContainer* getCurrentAreaBeingConstructedInBuilder() {
       
        return m_levelAreaBuilder->levelAreaRef();
    };

    void SetUp() {
    
        m_positionForAreaToBeConstructed = sf::Vector2f(0.0f, 0.0f); 
        m_gridDimForAreaToBeConstructed = sf::Vector2i(2, 2);
        m_tileSizeForAreaToBeConstructed = sf::Vector2f(64.0f, 64.0f);  
        m_allyfactionToAssign = KNIGHTS; 
        m_enemyfactionToAssign = GOBLINS; 
        m_areaTypeForAreaToBeConstructed = GRASSLANDS;
        
    };


    



protected:

    std::unique_ptr<LevelAreaBuilder> m_levelAreaBuilder;
    std::unique_ptr<SpriteGenerator> m_spriteGenerator;
    std::unique_ptr<TextureManager> m_textureManager;
    std::string m_pathToTextures = "../Assets/Textures/PathsToTextures.txt";
    sf::Vector2f m_positionForAreaToBeConstructed;
    sf::Vector2f m_tileSizeForAreaToBeConstructed;
    sf::Vector2i m_gridDimForAreaToBeConstructed;
    std::vector<AllyInitialiser> m_allyNpcsForAreaTobeConstructed;
    std::vector<EnemyInitialiser> m_enemyNpcsForAreaTobeConstructed;
    AreaTypes m_areaTypeForAreaToBeConstructed = AreaTypes();
    AllyFactionIds m_allyfactionToAssign = AllyFactionIds();
    EnemyFactionIds m_enemyfactionToAssign = EnemyFactionIds();
    std::vector<std::string> m_backGroundPathsForLevelArea;
    std::vector<TileInitialiser> m_randomlyGeneratedTilesToBeUsedInConstruction;
    std::map<std::string,TileInitialiser> m_imageMappedTilesToBeUsedInConstruction;

};


// testing the level builder as part of the builder design pattern 
// this test ensures that the builder is able to assign the basic properties required for a level area to be drawn to the 
// screen that being the background textures that the level area will use along with the position, tile dimensions, and grid dimensions 
// for the area 
TEST_F(LevelAreaBuilderTests, ConstructDefaultLevelArea) {


    // tell the level builder to construct a default level area 
    m_levelAreaBuilder->initNewArea(); 
    
    // refernce to the current level area being constructed by the level area builder 
    LevelAreaContainer* areaBeingConstructedRef = getCurrentAreaBeingConstructedInBuilder();
    ASSERT_NE(areaBeingConstructedRef, nullptr); // assert that the constrcuted default level area is not nullPtr 
    // to ensure that it was properly created and to break out of the test if not as it will cause the prorgam 
    // to crash if it is null and execution of the test goes further
    
    // assign background texture paths to the level area being constrcuted through the level area builder 
    // telling it what texture background paths to use for the  construction of the level area
    m_levelAreaBuilder->assignBackgroundTexturePaths(m_backGroundPathsForLevelArea);  
    // ensure that the vector of background image paths assigned to the level area
    // being constructed through the level area builder is of the size expected 
    ASSERT_EQ(areaBeingConstructedRef->getBackgroundTexturePaths().size(), m_backGroundPathsForLevelArea.size());
    // ensure that the contents of the vector of background images assigned to the level area being constructed 
    // are correct by checking the equality of the asset paths within the desired vector and that which was 
    // assigned to the level area through the level builder(in this case we check the first element of the vector)
    EXPECT_STREQ(areaBeingConstructedRef->getBackgroundTexturePaths()[0].c_str(), m_backGroundPathsForLevelArea[0].c_str());

    // assign the position of the area to be constrcuted through the level area builder 
    m_levelAreaBuilder->assignPositionForArea(m_positionForAreaToBeConstructed); 
    // test that those values are properly set by the level area builder 
    EXPECT_EQ(areaBeingConstructedRef->getPosition().x, m_positionForAreaToBeConstructed.x);
    EXPECT_EQ(areaBeingConstructedRef->getPosition().y ,m_positionForAreaToBeConstructed.y);

    // assign dimensions for the grid section sizes of the area and the tile size fo the area
    m_levelAreaBuilder->assignDimensionsForArea(m_gridDimForAreaToBeConstructed,m_tileSizeForAreaToBeConstructed);

    // expect the desired dimensions of the grid to be equal to those used by the level area builder 
   // that were set for the current level area being built by the level area builder 
    EXPECT_EQ(areaBeingConstructedRef->getTileDim().x, m_tileSizeForAreaToBeConstructed.x);

    EXPECT_EQ(areaBeingConstructedRef->getTileDim().y, m_tileSizeForAreaToBeConstructed.y);


    EXPECT_EQ(areaBeingConstructedRef->getGridDim().x, m_gridDimForAreaToBeConstructed.x);

    EXPECT_EQ(areaBeingConstructedRef->getGridDim().y, m_gridDimForAreaToBeConstructed.y);



}

// testing the creation of a level area with npc factions assigned to it along 
/// with a position and dimensions for the grid these faction id's are used to 
// select specifc enemy and ally pooling objects used to spawn allies and enemies 
//associated with that area therefore by assigning a faction id to the level area 
// it will be assignined specifc npc's for spanwing, and through the builder desgin 
// pattern the assignment of npc factions to an area is optional allowing for 
// more mixing and matching for what a level area does and doesnt have 
TEST_F(LevelAreaBuilderTests, ConstructLevelAreaWithNPCs ) {

    // creat a new area in the builder 
    m_levelAreaBuilder->initNewArea();
    // get a refernce to that area within the builder for ease of testing 
    LevelAreaContainer* areaBeingConstructedRef = getCurrentAreaBeingConstructedInBuilder();
    ASSERT_NE(areaBeingConstructedRef, nullptr); // ensure the level area was created properly before continuing 
    
    // assigning an areaType id to an area which is used to access certain associative maps 
    // that contain data relating to a particualr areaType  such as data for tilemaps along with 
    // background textures for a specifc area type id 
    m_levelAreaBuilder->assignAreaType(m_areaTypeForAreaToBeConstructed);
    // check that the areaType id was assigned correctly to the level area being constructed by the level area builder 
    EXPECT_EQ(m_areaTypeForAreaToBeConstructed, areaBeingConstructedRef->getAreaType());
    // assign position and dim for area 
    m_levelAreaBuilder->assignDimensionsForArea(m_gridDimForAreaToBeConstructed, m_tileSizeForAreaToBeConstructed);
    m_levelAreaBuilder->assignPositionForArea(m_positionForAreaToBeConstructed);

    // assign an ally faction id for the area meaning it will now have specifc allies related to 
    // that faction spawn within the area 
    m_levelAreaBuilder->assignAllyFaction(m_allyfactionToAssign);
    // ensure that the level area being constructed by the builder has the correct ally faction id 
    EXPECT_EQ(areaBeingConstructedRef->getAssociatedAllyFaction(), m_allyfactionToAssign);

    // assign an enemy faction id for the area meaning it will now have specifc enemies related to 
    // that faction spawn within the area 
    m_levelAreaBuilder->assignEnemyFaction(m_enemyfactionToAssign);
    // ensure that the level area being constructed by the builder has the correct enemy faction id 
    EXPECT_EQ(areaBeingConstructedRef->getAssociatedEnemyFaction(), m_enemyfactionToAssign);




}

TEST_F(LevelAreaBuilderTests, ConstructLevelAreaWithDataForGeneratedTiles) {

    m_levelAreaBuilder->initNewArea(); 
    // get a refernce to that area within the builder for ease of testing 
    LevelAreaContainer* areaBeingConstructedRef = getCurrentAreaBeingConstructedInBuilder();

    // some level areas may have tiles to be randomly generated within the area therefore through the 
    // level builder that property of the level area container can be configured and set if needed 
    // allowing  for areas that have randomly generated tiles and those that do not 
    m_levelAreaBuilder->assignRandomlyGeneratedTiles(m_randomlyGeneratedTilesToBeUsedInConstruction);

    // ensure that the size of the STL sequence container(vector in this case) is equal to the desired container 
    // of randomly generated tiles set by the level area builder 
    ASSERT_EQ(m_randomlyGeneratedTilesToBeUsedInConstruction.size(), areaBeingConstructedRef->getRandomlyGeneratedTiles().size());
    
    // some level areas may have tiles that area going to the initilaised based on a particualr tile image map 
    // therefore this property can also be configured via the level area builder meaning some level areas 
    // could have image maps for tiles and other may not 
    m_levelAreaBuilder->assignImageParsedTiles(m_imageMappedTilesToBeUsedInConstruction);
    // ensure that the two assocative container maps are of equal size before continuing testing 
    
    // ensure that the size of the associative conatiner used to store image mapped tile initilaiser object and a particualr id 
    // is as expected before ittertaing through the data to ensure it matches what was set in the level area by the 
    // level builder 
    ASSERT_EQ(areaBeingConstructedRef->getImageParsedTiles().size(), m_imageMappedTilesToBeUsedInConstruction.size()); 
    
    std::map<std::string, TileInitialiser>::iterator levelAreaTileImageMapData = areaBeingConstructedRef->getImageParsedTiles().begin();
    for  (std::map<std::string,TileInitialiser>::iterator it = m_imageMappedTilesToBeUsedInConstruction.begin(); it != m_imageMappedTilesToBeUsedInConstruction.end();it++)
    {
        
        // ensure that all the tile id's for the image mapped tiles that were set for the level area being constructed  
        // macth the desired data as the tile ids are used for further data processing when reading the image map 
        //  that signifies fixed tile placements within the area
        EXPECT_STREQ(it->first.c_str(), (levelAreaTileImageMapData)->first.c_str());
        levelAreaTileImageMapData++;
    

    }
    
}


class LevelManufacturerTests :public::testing::Test {

public:

    LevelManufacturerTests() {
    
        m_textureManager = std::make_unique<TextureManager>(TextureManager());
        m_textureManager->loadTextures(m_pathToTextures);
        m_spriteGenerator = std::make_unique<SpriteGenerator>(SpriteGenerator(m_textureManager.get()));

        m_levelAreaBuilder = std::make_unique<LevelAreaBuilder>(LevelAreaBuilder(m_spriteGenerator.get()));
        m_levelAreaManufacturer = std::make_unique<LevelAreaManufacturer>(LevelAreaManufacturer());
        
        m_backGroundPathsForLevelArea = {
         "../Assets/Textures/GrassBackground0.png"

        };
        m_allyNpcsForAreaTobeConstructed = { AllyInitialiser(new Pawn()) };
        m_enemyNpcsForAreaTobeConstructed = { EnemyInitialiser(new Goblin()) };

        m_randomlyGeneratedTilesToBeUsedInConstruction = {

          TileInitialiser(new RockTile()),
          TileInitialiser(new ForestTile()),



        };
        m_imageMappedTilesToBeUsedInConstruction = {

            {"Path",TileInitialiser(new PathTile())}



        };
        std::vector<std::string> m_tileMapImagesToBeUsedInConstruction ={
            "../Assets/TileMapImages/GrassLands/GrassLandsMap.png"
        };

        m_tileImageMapInformation = {

            {imageMapColour(0,0,0,255),"path"}

        };
    
    };
    ~LevelManufacturerTests() {};


    void SetUp() {

        m_positionForAreaToBeConstructed = sf::Vector2f(0.0f, 0.0f);
        m_gridDimForAreaToBeConstructed = sf::Vector2i(2, 2);
        m_tileSizeForAreaToBeConstructed = sf::Vector2f(64.0f, 64.0f);
        m_allyfactionToAssign = KNIGHTS;
        m_enemyfactionToAssign = GOBLINS;
        m_areaTypeForAreaToBeConstructed = GRASSLANDS;

    };






protected:

    std::unique_ptr<LevelAreaBuilder> m_levelAreaBuilder;
    std::unique_ptr<SpriteGenerator> m_spriteGenerator;
    std::unique_ptr<TextureManager> m_textureManager;
    std::unique_ptr<LevelAreaManufacturer> m_levelAreaManufacturer;
    std::string m_pathToTextures = "../Assets/Textures/PathsToTextures.txt";
    std::vector<std::string> m_tileMapImagesToBeUsedInConstruction;
    std::vector<std::string> m_backGroundPathsForLevelArea;

    sf::Vector2f m_positionForAreaToBeConstructed;
    sf::Vector2f m_tileSizeForAreaToBeConstructed;
    sf::Vector2i m_gridDimForAreaToBeConstructed;
    AreaTypes m_areaTypeForAreaToBeConstructed = AreaTypes();
    AllyFactionIds m_allyfactionToAssign = AllyFactionIds();
    EnemyFactionIds m_enemyfactionToAssign = EnemyFactionIds();
    std::vector<AllyInitialiser> m_allyNpcsForAreaTobeConstructed;
    std::vector<EnemyInitialiser> m_enemyNpcsForAreaTobeConstructed;
    std::vector<TileInitialiser> m_randomlyGeneratedTilesToBeUsedInConstruction;
    std::map<std::string, TileInitialiser> m_imageMappedTilesToBeUsedInConstruction;
    std::map<imageMapColour, std::string> m_tileImageMapInformation;
};


// this specifc test for the level manufeactueerer test the conrtsctuion of  a level area with 
// the minmal amount of properties required for it to be drawn to the screen essentially the 
// conrtction and manufacturing of a default level area via the level manufacurer that also makes 
// use of the assigned level area builder through out the manufacturing process of the level area 
// istelf 
TEST_F(LevelManufacturerTests, manufactureDefaultArea) {


    m_levelAreaManufacturer->createLevelArea(m_levelAreaBuilder.get(), m_areaTypeForAreaToBeConstructed, m_backGroundPathsForLevelArea); 
    
    std::shared_ptr<LevelAreaContainer> constructedArea  = std::make_shared<LevelAreaContainer>();
    // here we define the final properties for the area and complete its construction 
    // configuring things likes tile size for the area and its position allowing those 
    // properties to be easily changed per level area generated through the manufactuerer and its 
    // provided level area builder 
    LevelAreaContainer* manufactueredLevelArea = m_levelAreaManufacturer->manufactureLevelArea(m_positionForAreaToBeConstructed, m_gridDimForAreaToBeConstructed, m_tileSizeForAreaToBeConstructed);
    //// manufactuerer the final area and hand it allocated memory to a smart pointer to be managed 
    //// and deallocated when it goes out of scope
    constructedArea.reset(m_levelAreaManufacturer->manufactureLevelArea(m_positionForAreaToBeConstructed, m_gridDimForAreaToBeConstructed, m_tileSizeForAreaToBeConstructed));
    
    EXPECT_EQ(constructedArea->getBackgroundTexturePaths().size(), m_backGroundPathsForLevelArea.size());

    // test that the area type for the level area was set correctly via the default construction performed 
    // by the manuafcturer and current level builder it is using to produce the level area 
    EXPECT_EQ(constructedArea->getAreaType(), m_areaTypeForAreaToBeConstructed);


    // test that the grid dirmension for the area are correct according to those defined for the manufactruer 
    // and past into the current builder it is using 
    EXPECT_EQ(constructedArea->getGridDim().x, m_gridDimForAreaToBeConstructed.x);
    EXPECT_EQ(constructedArea->getGridDim().y, m_gridDimForAreaToBeConstructed.y);

    // test that the grid tile dimensions for the area are correct according to those defined for the manufactruer 
// and past into the current builder it is using 
    EXPECT_EQ(constructedArea->getTileDim().x, m_tileSizeForAreaToBeConstructed.x);
    EXPECT_EQ(constructedArea->getTileDim().y, m_tileSizeForAreaToBeConstructed.y);

    // test that the position for the area are correct according to what was defined for the manufactruer 
    // and assigned to the current level area builder being used by the manufacturer
    EXPECT_EQ(constructedArea->getPosition().x, m_positionForAreaToBeConstructed.x);
    EXPECT_EQ(constructedArea->getPosition().y, m_positionForAreaToBeConstructed.y);



}

// this test is ensuring that the level manufactuerer is able to correctly pass through the data required for a level area 
// to contain npcs to the level builder testing that the resulting containers for various infomration reuqired for npc's to be spawned 
// within a particualr level area is correct along with ensuring that idenfifiers such as the faction id 
// for the particualr enemies and allies being assigned to the area are also assigned correctly by the manufacturer 
// and correctly accounted for during the constrcution performed by the level builder.
TEST_F(LevelManufacturerTests, manufactureLevelAreaWithNpcs) {


    // create the default level area 
    m_levelAreaManufacturer->createLevelArea(m_levelAreaBuilder.get(), m_areaTypeForAreaToBeConstructed, m_backGroundPathsForLevelArea);

    // add ally npcs to the construction process of the level area allowing for certain level areas 
    // to have ally npc's while others do not allowing for more flexibility in configuing what level areas  do and do not have 
    // through the builder design pattern used for level areas
    m_levelAreaManufacturer->addAlliesToArea(m_allyfactionToAssign, m_allyNpcsForAreaTobeConstructed);
    
    // in this case we are adding enemy npc's to the constrction process of the level area again allowing 
    // for enemies for the level area to be configured and for some level areas to have enemies and others to not 
    m_levelAreaManufacturer->addEnemiesToArea(m_enemyfactionToAssign, m_enemyNpcsForAreaTobeConstructed);

    //// manufactuerer the final area and hand it allocated memory to a smart pointer to be managed 
    //// and deallocated when it goes out of scope
    std::shared_ptr<LevelAreaContainer> constructedArea = std::make_shared<LevelAreaContainer>();
    constructedArea.reset(m_levelAreaManufacturer->manufactureLevelArea(m_positionForAreaToBeConstructed, m_gridDimForAreaToBeConstructed, m_tileSizeForAreaToBeConstructed));

    // test all the properties that were set based on what is needed for a level area to have npc's spawn within it 
    // that being a vector containing initiliasiers for the npc's along with a particualr faction id to 
    // single what particualr enemy or ally pooling objects should be used to spawn the npc's associated
    // with the level area that was constrcuted and manfactured
    EXPECT_EQ(constructedArea->getAssociatedAllyFaction(), m_allyfactionToAssign);
    EXPECT_EQ(constructedArea->getAllyIntialisers().size(), m_allyNpcsForAreaTobeConstructed.size());
   
    EXPECT_EQ(constructedArea->getAssociatedEnemyFaction(), m_enemyfactionToAssign);
    EXPECT_EQ(constructedArea->getEnemyIntialisers().size(), m_enemyNpcsForAreaTobeConstructed.size());
    


}

// this particualr tests ensures that alll the data for assinging tiles that can be randomly egenerated and also tiles that
// can be generated based on an image map is correctly passed through the level manufacturer to the level builder 
// ensuring that all the data is correct and accurate according to what has been defined in the test fixture
TEST_F(LevelManufacturerTests, manufactureLevelAreaWithGeneratedTiles) {

    // create the default level area 
    m_levelAreaManufacturer->createLevelArea(m_levelAreaBuilder.get(), m_areaTypeForAreaToBeConstructed, m_backGroundPathsForLevelArea);

    // here wer define that we want the area to have ranodmly generated tiles adding that to the conrtsution process within the elevel builder 
    // through the level area manufacturer further splitting up the initialisation process of a level area 
    // into more configurable and optinal steps rather than having to manage multiple large constrctors for level areas 
    // that may need a lot of data 
    m_levelAreaManufacturer->addRandomlyGeneratedTileToArea(m_randomlyGeneratedTilesToBeUsedInConstruction); 
    // here we define that we want tile maps for the level area to be considered within the construction process defined 
    // for the level area builder assigning various pieces of data through the level manufacturer to be used in that process. 
    // Such as the path to the particualr image map the tiles to be generated through the image map and various 
    // information that describes the image map. Such as what colours within the image map, map to a particualr tile id within the 
    // map of tile initialisers passed in. Again segementing  the initialistion process of a level area 
    // via the builder desgin pattern into more managable and optional steps
    m_levelAreaManufacturer->addTileMapsToArea(m_tileMapImagesToBeUsedInConstruction, m_imageMappedTilesToBeUsedInConstruction, m_tileImageMapInformation);

    // manufactuerer the final area and hand it allocated memory to a smart pointer to be managed 
    // and deallocated when it goes out of scope
    std::shared_ptr<LevelAreaContainer> constructedArea = std::make_shared<LevelAreaContainer>();
    constructedArea.reset(m_levelAreaManufacturer->manufactureLevelArea(m_positionForAreaToBeConstructed, m_gridDimForAreaToBeConstructed, m_tileSizeForAreaToBeConstructed));

    // testing that the data container for randomly generated tiles ste for the manufactured level area  is of correct size  
    // and that the data within the vector container is accurate 
    ASSERT_EQ(constructedArea->getRandomlyGeneratedTiles().size(), m_randomlyGeneratedTilesToBeUsedInConstruction.size());
    EXPECT_EQ(constructedArea->getRandomlyGeneratedTiles()[0].getHeldObject()->getRowCap(), m_randomlyGeneratedTilesToBeUsedInConstruction[0].getHeldObject()->getRowCap());
    

    
    // testing that the data container for randomly generated tiles ste for the manufactured level area  is of correct size
    // and that the data within the vector container is accurate 
    ASSERT_EQ(constructedArea->getImageParsedTiles().size(), m_imageMappedTilesToBeUsedInConstruction.size());
   
    std::map<std::string, TileInitialiser>::iterator levelAreaTileImageMapData = constructedArea->getImageParsedTiles().begin();
    for (std::map<std::string, TileInitialiser>::iterator it = m_imageMappedTilesToBeUsedInConstruction.begin(); it != m_imageMappedTilesToBeUsedInConstruction.end(); it++)
    {

        // ensure that the key values are equal in the map that stores a string identifier and 
        // a tile initialiser related to that string id 
        ASSERT_STREQ (it->first.c_str(), (levelAreaTileImageMapData)->first.c_str());

        // check that the speed modifier property returns the same result for the 
        // desired tile initialisers stored in the map in the test fixture and 
        // that the manufactured level area has the same tile initilaisers by also 
        // checking the speed modifier property of each tile object held within those 
        // tile initialisers
        float desiredTileSpeedMod = m_imageMappedTilesToBeUsedInConstruction[it->first].getHeldObject()->getSpeedModifier(); 
        float manufacturedLevelAreaSpeedMod = constructedArea->getImageParsedTiles()[it->first].getHeldObject()->getSpeedModifier();
        EXPECT_EQ(desiredTileSpeedMod, manufacturedLevelAreaSpeedMod);
        // continue to itterate through the map of tile initialisers and string id's 
        // contained within the manufactured level area 
        levelAreaTileImageMapData++;


    }





}

class ScoreMenuTest:public::testing::Test {

public:

    ScoreMenuTest(){
      
        m_scoresToSort = { 4,3,2 };
        createTestScoreDataFile();
        m_expectedScoreDataSorted = m_scoresToSort;
        std::sort(m_expectedScoreDataSorted.begin(), m_expectedScoreDataSorted.end(), std::greater<int>());
        m_scoreMenuObject = std::make_unique<ScoreMenu>(ScoreMenu());
        
    };
    ~ScoreMenuTest() {}; 

    void setScoresToScore(std::vector<int> scores) {
        m_scoresToSort = scores;
        m_expectedScoreDataSorted = m_scoresToSort;
        std::sort(m_expectedScoreDataSorted.begin(), m_expectedScoreDataSorted.end(), std::greater<int>());
    }

    void createTestScoreDataFile() {
         
        std::ofstream fileData(m_testDataFilePath); 

        for (int i = 0; i < m_scoresToSort.size();i++){
            
            fileData << std::to_string(m_scoresToSort[i]) + "\n";
            
            
        }






    
    };

    std::string makeScoreTextLesser() {

        // make the a score string that will be passed into the functor used for 
        // extracting the score values from two strings that are used to 
        // display scores in the score menu this specifc score string will be considered 
        // should always be considered lesser then the one generated by the makeScoreTextGreater method 
        // of this test fixture 
        m_scoreLesserValue = rand() % m_scorevalueRangeMax;
        std::string scoreText = "Run/session:" + std::to_string(0) + " Score:" + std::to_string(m_scoreLesserValue);
        return scoreText;

    }
    std::string makeScoreTextGreater() {

        m_scoreGreaterValue = m_scoreLesserValue + (rand() % m_scorevalueRangeMax);
        std::string scoreText = "Run/session:" + std::to_string(0) + " Score:" + std::to_string(m_scoreGreaterValue);
        return scoreText;

    }



protected:

    std::unique_ptr<ScoreMenu> m_scoreMenuObject; 
    int m_scoreLesserValue = 0; 
    int m_scoreGreaterValue = 0; 
    int m_scorevalueRangeMax = 10; 
    std::string m_testDataFilePath = "../Assets/TestFileData/readingScoresTestData.txt";
    std::vector<int> m_scoresToSort;
    std::vector<int> m_expectedScoreDataSorted;

};

TEST_F(ScoreMenuTest,scoresSortingFunctorTrueResultTest) {

    // create two score strings that will be passed into the functor predicate 
    // used within the score menu class to sort the scores using std::sort 
    // these strings follow the same structure as they are in the UI 
    // with the score value located at the end of the score string 
    std::string scoreTextConsideredLesser = makeScoreTextLesser();
    std::string scoreTextConsideredGreater = makeScoreTextGreater();

    scoreSort sortScoresFunctionObject = {};  
    // expect that the score text greater is considered greater than the score text lesser that was created 
    // meaning that the functor has correctly processed the two score strings and extracted and compared the score values 
    EXPECT_TRUE(sortScoresFunctionObject(scoreTextConsideredGreater, scoreTextConsideredLesser));

}
TEST_F(ScoreMenuTest, scoresSortingFunctorFalseResultTest) {
    // create two score strings that will be passed into the functor predicate 
    // used within the score menu class to sort the scores using std::sort 
    // these strings follow the same structure as they are in the UI 
    // with the score value located at the end of the score string 
    std::string scoreTextConsideredLesser = makeScoreTextLesser();
    std::string scoreTextConsideredGreater = makeScoreTextGreater();
    
    scoreSort sortScoresFunctionObject = {};
    // in this case we reverse the order of the two score strings placing the lesser one 
    // as the first argument for the functor predciate used to compare the two score strings 
    // the lesser score string score value will be on the left hand side of the > boolean operation 
    // within the function predicate used to extract the two score values from the score strings 
    // meaning that in this case the  functor should return false
    EXPECT_FALSE(sortScoresFunctionObject(scoreTextConsideredLesser, scoreTextConsideredGreater));

}

// this test itterates through the expected sorted score data and goes through the sorted 
// score strings provided by the readScoreValues method of the score menu object compare the extracted 
// score values comparing the scores extracted from the score strings provided by the readScoreValues method 
// to the expected sorted data 
TEST_F(ScoreMenuTest, sortingScoresAlgorithmTest) {

    // get the sorted score strings that would be displayed within the score menu ui 
    // these strings should be sorted from decending order by the std::sort algorhtm using the previously tested functor as the predicate 
   // sorting is based on the score value contained withn the strings 
    std::vector<std::string> sortedScoresResult = m_scoreMenuObject->readScoreValues(m_testDataFilePath);
    
    // get an itterator pointer to the beggining of the test data 
    std::vector<int>::iterator sortedScoresData = m_expectedScoreDataSorted.begin();
    // loop through the vector containing the supposed sorted score strings 
    for (std::vector<std::string>::iterator it = sortedScoresResult.begin(); it != sortedScoresResult.end(); it++) {

        // get the current sorted score string we are itterating through 
        std::string sortedScoreText = *it; 
        // get the start and end index for the score value contained within the score string 
        size_t sortedScoreInTextStart = sortedScoreText.find_last_of(":") + 1; 
        size_t sortedScoreInTextEnd = sortedScoreText.find("\n");
        // extract the score value from the supposed sorted score string vector
        int sortedScoreValueInText = std::stoi(sortedScoreText.substr(sortedScoreInTextStart,sortedScoreInTextEnd));
        
        if (sortedScoresData == m_expectedScoreDataSorted.end()) {
            std::cout << "expected score data didnt match the size of the data in the test file" << std::endl;
            continue;
        }
        // expect that the sorted score data extracted from the score string matches the expected score data defined in the test fixture 
        // the expected score data is pre stored in the test fixture in the order expected 
        // therefore we can just itterate through the returned sorted scores string from the read score method
        // and compare each extracted score value to the pre sorted score integers
        EXPECT_EQ(*sortedScoresData,sortedScoreValueInText);
        sortedScoresData++;




    }

}

class UIsliderUnitTest :public::testing::Test {

public:

    UIsliderUnitTest() {}
    ~UIsliderUnitTest() {};

    void SetUp() {



        m_startingValuePercent = 0.75f;
        m_positionToSet = sf::Vector2f(200.0f, 200.0f);
        m_sizeToSet = sf::Vector2f(200.0f, 60.0f);
        m_backgroundColourToSet = sf::Color::White;
        m_sliderIndciatorColourToSet = sf::Color::Black;
        m_sliderIndicatorRadiToSet = 10.0f;
        m_slider = std::make_unique<UiSlider>(UiSlider(m_startingValuePercent, m_sizeToSet, m_positionToSet, m_backgroundColourToSet, m_sliderIndicatorRadiToSet, m_sliderIndciatorColourToSet));
    } 

    float ExpectedSliderPositionValue() const {
        float startX = m_positionToSet.x - m_sizeToSet.x / 2.0f;
        float EndX = m_positionToSet.x + m_sizeToSet.x / 2.0f;

        float expectedResultX = startX + (EndX - startX) * m_startingValuePercent;
        return expectedResultX;
    }

protected:

    std::unique_ptr<UiSlider> m_slider;
    float m_startingValuePercent = 0.0f;
    sf::Vector2f m_positionToSet;
    sf::Vector2f m_sizeToSet;
    sf::Color m_backgroundColourToSet;
    sf::Color m_sliderIndciatorColourToSet;
    float m_sliderIndicatorRadiToSet = 0.0f;




};


TEST_F(UIsliderUnitTest,TestingSliderStartPosition) {


    
    float expectedSliderIndicatorX = ExpectedSliderPositionValue(); 

    EXPECT_EQ(expectedSliderIndicatorX, m_slider->getSliderIndicatorPos().x);
    





}


 /**
  * Class WarriorTest
  */
class WarriorTest {
private:
    /**
     * Locality of the warrior
     */
    sf::Vector2f v2_locality;
    /**
     * Speed direction of the warrior
     */
    sf::Vector3f v3_speed_direction;
    /**
     * Name of the warrior
     */
    std::string str_name;
    /**
    * Damage of the warrior
   */
    int int_damage = 0;

public:
    /**
     * Default constructor for WarriorTest
     */
    WarriorTest() = default;
    /**
     * Destructor for WarriorTest
     */
    ~WarriorTest() = default;
    /**
     * Constructor for WarriorTest
     *
     * @param v2_locality the locality of the warrior
     * @param v3_speed_direction the speed direction of the warrior
     * @param str_name the name of the warrior
     */
    WarriorTest(sf::Vector2f v2_locality, sf::Vector3f v3_speed_direction, std::string str_name, int damage) {
        this->v2_locality = v2_locality;
        this->v3_speed_direction = v3_speed_direction;
        this->str_name = str_name;
        this->int_damage = damage;
    }
    /**
     * Get the locality of the warrior
     *
     * @return the locality of the warrior
     */
    sf::Vector2f getLocation() {
        return v2_locality;
    }

    /**
     * Get the speed direction of the warrior
     *
     * @return the speed direction of the warrior
     */
    sf::Vector3f getSpeedDirection() {
        return v3_speed_direction;
    }

    /**
     * Get the name of the warrior
     *
     * @return the name of the warrior
     */
    std::string getName() {
        return str_name;
    }
    /**
    * Get the damage of the warrior
    *
    * @return the damage of the warrior
    */
    int getDamage() {
        return int_damage;
    } 


};



/**
 * Class GoblinTest
 */
class GoblinTest {
private:
    /**
     * Locality of the goblin
     */
    sf::Vector2f v2_locality;
    /**
     * Speed direction of the goblin
     */
    sf::Vector3f v3_speed_direction;
    /**
     * Name of the goblin
     */
    std::string str_name;
    /*
      damage of goblin 


    */
    int int_damage = 0; 





    
public:
    /**
     * Default constructor for GoblinTest
     */
    GoblinTest() = default;
    /**
     * Destructor for GoblinTest
     */
    ~GoblinTest() = default;
    /**
     * Constructor for GoblinTest
     *
     * @param v2_locality the locality of the goblin
     * @param v3_speed_direction the speed direction of the goblin
     * @param str_name the name of the goblin
     */
    GoblinTest(sf::Vector2f v2_locality, sf::Vector3f v3_speed_direction, std::string str_name, int damage) {
        this->v2_locality = v2_locality;
        this->v3_speed_direction = v3_speed_direction;
        this->str_name = str_name;
        this->int_damage = damage;
    }

    /**
     * Get the locality of the goblin
     *
     * @return the locality of the goblin
     */
    sf::Vector2f getLocation() {
        return v2_locality;
    }

    /**
     * Get the speed direction of the goblin
     *
     * @return the speed direction of the goblin
     */
    sf::Vector3f getSpeedDirection() {
        return v3_speed_direction;
    }

    /**
     * Get the name of the goblin
     *
     * @return the name of the goblin
     */
    std::string getName() {
        return str_name;
    }
    /**
 * Get the damage of the goblin
 *
 * @return the famage of the goblin
 */
    int getDamage() {
        return int_damage;
    }
};

// create a test fixture that will wrap both the goblin and warrior test classes under a singular test class that inhetis from the base test class 
// this means that the objects to test for the warrior and goblin do not have to be constantly redclared within multiple seperate test functions
class EnemyTest : public::testing::Test {

protected:
    WarriorTest myWarrior;
    GoblinTest myGoblin;
    EnemyTest() {

        myWarrior = WarriorTest(sf::Vector2f(10.f, 10.f), sf::Vector3f(100.f, 10.f, 2.5f), "The Brave",30);
        myGoblin = GoblinTest(sf::Vector2f(10.f, 10.f), sf::Vector3f(150.f, 20.5f, 1.5f), "Mighty",20);

    }
};

//



/**
 * Test for opponent check position
 */
TEST(OpponentCheck, position) {
    WarriorTest wt(sf::Vector2f(10.f, 10.f), sf::Vector3f(100.f, 10.f, 2.5f), "The Brave",40);
    GoblinTest gt(sf::Vector2f(10.f, 10.f), sf::Vector3f(150.f, 20.5f, 1.5f), "The Mighty",35);

    EXPECT_EQ(wt.getLocation().x, wt.getLocation().y);
    
}

/**
 * Test for opponent check name
 */
TEST(OpponentCheck, name) {
    WarriorTest wt(sf::Vector2f(10.f, 10.f), sf::Vector3f(100.f, 10.f, 2.5f), "The Brave",40);
    GoblinTest gt(sf::Vector2f(10.f, 10.f), sf::Vector3f(150.f, 20.5f, 1.5f), "Mighty",35);

    //Can't use string comparison with c++ string.
    EXPECT_EQ(wt.getName(), gt.getName());

    const char* bossName = "Fierce"; // used to create a c string array to test if the two char arrays are equal 
    const char* heroName = "Falcon";

    ASSERT_STREQ(bossName, heroName); // check if two char arrays are equal
}

// test if the names of the warrior and the goblin are equal
TEST(OpponentCheck, nameEqual) {
    WarriorTest wt(sf::Vector2f(10.f, 10.f), sf::Vector3f(100.f, 10.f, 2.5f), "Mighty", 40);
    GoblinTest gt(sf::Vector2f(10.f, 10.f), sf::Vector3f(150.f, 20.5f, 1.5f), "Mighty", 35);

   
    EXPECT_STREQ(wt.getName().c_str(), gt.getName().c_str());
}
TEST(OpponentCheck, nameNotEqual) {
    WarriorTest wt(sf::Vector2f(10.f, 10.f), sf::Vector3f(100.f, 10.f, 2.5f), "The Brave", 40);
    GoblinTest gt(sf::Vector2f(10.f, 10.f), sf::Vector3f(150.f, 20.5f, 1.5f), "Mighty", 35);


    EXPECT_STRNE(wt.getName().c_str(), gt.getName().c_str());
}
TEST(OpponentCheck, nameNotEqualCase) {
    WarriorTest wt(sf::Vector2f(10.f, 10.f), sf::Vector3f(100.f, 10.f, 2.5f), "mighty", 40);
    GoblinTest gt(sf::Vector2f(10.f, 10.f), sf::Vector3f(150.f, 20.5f, 1.5f), "Mighty", 35);
    EXPECT_STRCASENE(wt.getName().c_str(), gt.getName().c_str());// will fail due to the ne ignoring case 
}
TEST(OpponentCheck, nameEqualCase) {
    WarriorTest wt(sf::Vector2f(10.f, 10.f), sf::Vector3f(100.f, 10.f, 2.5f), "mighty", 40);
    GoblinTest gt(sf::Vector2f(10.f, 10.f), sf::Vector3f(150.f, 20.5f, 1.5f), "MIGHTY", 35);
    EXPECT_STRCASEEQ(wt.getName().c_str(), gt.getName().c_str());// will pass as  it ignores case
}

TEST(OpponentCheck, WarriorVSGoblinSpeedCheck) { 
    // used to check if the speedDirection variable within the warrior test object is equal to the speedDirection vairiable in the GoblinTest object 
    WarriorTest wt(sf::Vector2f(10.f, 10.f), sf::Vector3f(100.f, 10.f, 2.5f), "The Brave",40);
    GoblinTest gt(sf::Vector2f(10.f, 10.f), sf::Vector3f(110.f, 15.5f, 1.5f), "Mighty",35);

   
    EXPECT_EQ(wt.getSpeedDirection().x, gt.getSpeedDirection().x);
    EXPECT_LE(wt.getSpeedDirection().y, gt.getSpeedDirection().y);//values are expected to be less than or equal meaning test should pass 
    EXPECT_EQ(wt.getSpeedDirection().z, gt.getSpeedDirection().z);

}
TEST(OpponentCheck, WarriorVSGoblinDamageCheck) {
    // used to check if the speedDirection variable within the warrior test object is equal to the speedDirection vairiable in the GoblinTest object 
    WarriorTest wt(sf::Vector2f(10.f, 10.f), sf::Vector3f(100.f, 10.f, 2.5f), "The Brave", 40);
    GoblinTest gt(sf::Vector2f(10.f, 10.f), sf::Vector3f(110.f, 15.5f, 1.5f), "Mighty", 35);


    ASSERT_NE(wt.getDamage(), gt.getDamage());// values should be different as they are expected to be different this will force a non 0 exit if they are equal

}

// test fixture will create an object of the past in class that inherits from the test base class allowing us to access the memebers of 
// that created object making it easier to test data for specifc classes without having to constantly redeclare objects wihtin the test macro function
TEST_F(EnemyTest, testWarriorAndGoblinTestFixture) {
      
  
    std::cout << "test fixture:" << std::endl;
    EXPECT_LE(myWarrior.getSpeedDirection().y, myGoblin.getSpeedDirection().y); 
    EXPECT_EQ(myWarrior.getName(), myGoblin.getName()); 
    ASSERT_EQ(myWarrior.getLocation().x, myGoblin.getLocation().x); // assert that the two locations for the enemies are equal will exit the prorgam if they are not 
    ASSERT_EQ(myWarrior.getDamage(), myGoblin.getDamage());
    ASSERT_STRCASENE(myWarrior.getName().c_str(), myGoblin.getName().c_str()); // ASSERT that the string vairbale name wihtin the warrior class is not equal to the goblin class regardless of case 
        



}

// generic class for setting up a sprite with a texture, bounds and position
class Sprite {

public:
    Sprite()
    {

        m_worldPosition = sf::Vector2f();
        m_spriteRect = sf::Rect<float>(m_worldPosition, m_boundsSize);


    }
    Sprite(std::string assetLocation) {

        m_assetLocation = assetLocation;
        m_texture.loadFromFile(m_assetLocation);

    };
    Sprite(std::string assetLocation, sf::Vector2f worldPosition) {

        m_worldPosition = worldPosition;
        m_assetLocation = assetLocation;
        m_spriteRect = sf::Rect<float>(m_worldPosition, m_boundsSize);
        m_texture.loadFromFile(m_assetLocation);
    };
    Sprite(std::string assetLocation, sf::Vector2f worldPosition, float angle, sf::Vector2f boundsSize) {
        m_worldPosition = worldPosition;
        m_assetLocation = assetLocation;
        m_rotation = angle;
        m_boundsSize = boundsSize;
        m_spriteRect = sf::Rect<float>(m_worldPosition, m_boundsSize);
        m_texture.loadFromFile(m_assetLocation);

    };


    void setWorldPosition(sf::Vector2f position) {

        m_worldPosition = position;
        updateRect();

    }
    void setBoundsSize(sf::Vector2f size) {

        m_boundsSize = size;
        updateRect();


    }

    void setRotation(float angle) {
        m_rotation = angle;

    }
    void setTexture(std::string path) {

        m_texture.loadFromFile(path);

    }
    // when sprite position is changed update the bounding box that surrounds the sprite 
    void updateRect() {
        m_spriteRect = sf::Rect(m_worldPosition, m_boundsSize);
    }


    sf::Vector2f getPosition() {

        return m_worldPosition;
    }

    sf::Vector2f getBoundsSize() {

        return m_boundsSize;
    }
    // use the sf intersects method to check if two bounding rects for this sprite and another intersect
    bool intersection(Sprite other) {

        return m_spriteRect.intersects(other.getSpriteRect());


    }

    sf::Rect<float> getSpriteRect() {
        return m_spriteRect;
    }

    float getRotation() {
        return m_rotation;
    }
private:
    //setting up default values for the sprite 
    sf::Vector2f m_worldPosition = sf::Vector2f(0.0f, 0.0f);
    std::string m_assetLocation = "";
    float m_rotation = 0.0f;
    sf::Vector2f m_boundsSize = sf::Vector2f(10.0f, 10.0f);
    sf::Rect<float> m_spriteRect = sf::Rect<float>(m_worldPosition, m_boundsSize);
    sf::Texture m_texture = sf::Texture();


};




class SpriteTest : public testing::Test {


protected:
     
    Sprite m_sprite1;
    Sprite m_sprite2;
    int m_currentPositionIndex = 0;
    sf::Vector2f m_positionToTest;
    SpriteTest() {

        m_sprite1 = Sprite("", sf::Vector2f(9.0f, 9.0f), 10.0f, sf::Vector2f(20.0f, 20.0f));
        m_sprite2 = Sprite();

    }


    std::vector<sf::Vector2f> m_positionsToTest = { sf::Vector2f(0.0f,0.0f),sf::Vector2f(10.0f,0.0f),sf::Vector2f(30.0f,50.0f) };
    /*
      use set up to increment through the position we want to set our sprite to and check 
      as set up  is called each time a test associated with the test class is called
    */
    void  SetUp() {
        
      std::cout << "set up for sprite test called" << std::endl;
      m_currentPositionIndex = (m_currentPositionIndex++)%m_positionsToTest.size(); // increment the current index into the positions we want to set the sprite2 object to and check that it becomes equal to that position
      m_positionToTest = m_positionsToTest[m_currentPositionIndex]; // assign the current position by accessing the current index 
      m_sprite2.setWorldPosition(m_positionToTest); // set the supposed position of the sprite to that we want to test for 


    }





};


TEST_F(SpriteTest, testSprites) {

    std::cout << "sprite test fixture happened" << std::endl;
    for (int i = 0; i < m_positionsToTest.size(); i++) { // loop through all the positions and ensure that the sprite becomes equal to them
        EXPECT_EQ(m_sprite2.getPosition().x, m_positionToTest.x);
    }
    EXPECT_EQ(m_sprite1.getPosition().x, 9.0f);
    EXPECT_TRUE(m_sprite1.intersection(m_sprite2));


}










int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}