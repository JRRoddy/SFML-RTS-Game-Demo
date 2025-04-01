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
    WarriorTest(sf::Vector2f v2_locality, sf::Vector3f v3_speed_direction, std::string str_name) {
        this->v2_locality = v2_locality;
        this->v3_speed_direction = v3_speed_direction;
        this->str_name = str_name;
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
    GoblinTest(sf::Vector2f v2_locality, sf::Vector3f v3_speed_direction, std::string str_name) {
        this->v2_locality = v2_locality;
        this->v3_speed_direction = v3_speed_direction;
        this->str_name = str_name;
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
};

/**
 * Test for opponent check position
 */
TEST(OpponentCheck, position) {
    WarriorTest wt(sf::Vector2f(10.f, 10.f), sf::Vector3f(100.f, 10.f, 2.5f), "The Brave");
    GoblinTest gt(sf::Vector2f(10.f, 10.f), sf::Vector3f(150.f, 20.5f, 1.5f), "The Mighty");

    EXPECT_EQ(wt.getLocation().x, wt.getLocation().y);
}

/**
 * Test for opponent check name
 */
TEST(OpponentCheck, name) {
    WarriorTest wt(sf::Vector2f(10.f, 10.f), sf::Vector3f(100.f, 10.f, 2.5f), "The Brave");
    GoblinTest gt(sf::Vector2f(10.f, 10.f), sf::Vector3f(150.f, 20.5f, 1.5f), "Mighty");

    //Can't use string comparison with c++ string.
    EXPECT_EQ(wt.getName(), gt.getName());

    const char* bossName = "Fierce";
    const char* heroName = "Falcon";

    ASSERT_STREQ(bossName, heroName);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}