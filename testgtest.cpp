/**
 * @file opponent_check.cpp
 * @brief Tests for Warrior and Goblin classes
 */

#include <gtest/gtest.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>



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