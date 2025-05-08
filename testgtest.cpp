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
class DynamicObjectTest: public::testing::Test {
public:

    
    DynamicObjectTest() {
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
TEST_F(DynamicObjectTest, dynamicObjectSpeedSetTest) {

     
    EXPECT_EQ(m_dynamic.getSpeed(), m_speedValue);


}
TEST_F(DynamicObjectTest, SpeedModifierTest) {


   
    EXPECT_EQ(m_dynamic.getSpeedModifier(), m_expectedSpeedModifer);

}
TEST_F(DynamicObjectTest, setDirectionTest) {


 
    EXPECT_EQ(m_dynamic.getDirection().x, m_directionToSet.x);
    EXPECT_EQ(m_dynamic.getDirection().y, m_directionToSet.y);

}

TEST_F(DynamicObjectTest,dynamicObjectMovementTestSixtyFramesAsecond) {

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
TEST_F(DynamicObjectTest, dynamicObjectMovementTestThirtyFramesAsecond) {
    
    
    m_elapsed = 1.0f / 30.0f;
    m_dynamic.updatePosition(m_elapsed);
    sf::Vector2f newExpectedPosition = m_positionToSet + ((m_directionToSet * m_speedValue) * m_expectedSpeedModifer) * m_elapsed;

    EXPECT_EQ(m_dynamic.getPosition().x, newExpectedPosition.x);
    EXPECT_EQ(m_dynamic.getPosition().y, newExpectedPosition.y);

    EXPECT_EQ(m_dynamic.getBaseSprite()->getPosition().x, newExpectedPosition.x);
    EXPECT_EQ(m_dynamic.getBaseSprite()->getPosition().y, newExpectedPosition.y);
   



}

TEST_F(DynamicObjectTest, VaryingFrameRateMovementTest) {

    m_elapsed = 1.0f / 60.0f;
    m_dynamic.updatePosition(m_elapsed);
    sf::Vector2f sixtyFPSExpectedPosition = m_positionToSet + ((m_directionToSet * m_speedValue) * m_expectedSpeedModifer) * m_elapsed;
    EXPECT_EQ(m_dynamic.getPosition().x, sixtyFPSExpectedPosition.x);
    EXPECT_EQ(m_dynamic.getPosition().y, sixtyFPSExpectedPosition.y);
    m_dynamic.setPosition(m_positionToSet);
    m_elapsed = 1.0f / 30.0f;
    m_dynamic.updatePosition(m_elapsed);
    sf::Vector2f thirtyFPSExpectedPosition = m_positionToSet + ((m_directionToSet * m_speedValue) * m_expectedSpeedModifer) * m_elapsed;
    EXPECT_EQ(m_dynamic.getPosition().x, thirtyFPSExpectedPosition.x);
    EXPECT_EQ(m_dynamic.getPosition().y, thirtyFPSExpectedPosition.y);

    // ensuring that positions for dynamic objects remain relative to eachother 
    // despite varying delta time(while removing any floating point precision)
    EXPECT_EQ(floor(thirtyFPSExpectedPosition.x), floor(sixtyFPSExpectedPosition.x));
    EXPECT_EQ(floor(thirtyFPSExpectedPosition.y), floor(sixtyFPSExpectedPosition.y));



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
  
   EXPECT_EQ(testAnimLoad.get()->size(), m_testAnimationFrameSize);

}

TEST_F(SpriteGeneratorTest, TestSingleSpriteGeneration) {

   std::shared_ptr<sf::Sprite> sprite =  m_spriteGenerator->GenerateSprite(m_singleSpritePath);
   // test the the sprite returned is not empty 
   // i.e  here we assert as all proceeding test will cause errors if null result
   ASSERT_NE(sprite.get(), nullptr); 
   // test that the sprite returned has the macthing texture rect for the expected texture
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


class PlayerTest:public::testing::Test {

public:
    
    PlayerTest() {

        m_textureManager = std::make_unique<TextureManager>(TextureManager()); 
        m_textureManager->loadTextures(m_pathToTextures);
        m_textureManager->loadAnims(m_animationsPath);
   
        m_spriteGenerator = std::make_unique<SpriteGenerator>(SpriteGenerator(m_textureManager.get())); 
        m_positionToSet = sf::Vector2f(400.0f, 300.0f);
        m_player = std::make_unique<Player>(Player(m_positionToSet, m_spriteGenerator.get()));
        m_elapsed = 1 / 60.0f;
    }
protected:
    std::unique_ptr<Player> m_player;
    std::unique_ptr<TextureManager> m_textureManager;
    std::unique_ptr<SpriteGenerator> m_spriteGenerator;
    sf::Vector2f m_positionToSet; 
    std::string m_animationsPath = "../Assets/Animations/PathsToAnimations.txt";
    std::string m_pathToTextures = "../Assets/Textures/PathsToTextures.txt";
    float m_elapsed;


};






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