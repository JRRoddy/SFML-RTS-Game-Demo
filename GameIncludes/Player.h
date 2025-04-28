#pragma once
#include "Character.h"
#include "InputManager.h"
#include "Camera.h"
#include "AnimationController.h"
class Player: public Character {
 public:
	Player();
	Player(sf::Vector2f position, SpriteGenerator * spriteGenerator,InputManager * input);
	Player(sf::Vector2f position, SpriteGenerator* spriteGenerator, InputManager* input, Camera * camera);
	bool isMouseDown(sf::Mouse::Button button);
	bool isMouseReleased(sf::Mouse::Button button);
	sf::Vector2f getMousePosition();
	void draw(sf::RenderWindow* window);
	void updateCommandFlag();
	void updateCamera(); 
	void update(float dt);
	void collision(GameObject* other);
	void getSprites(SpriteGenerator * spriteGenerator);
	void setCurrentLevelAreaBounds(sf::FloatRect& levelAreaBounds);
	bool recallingAllies() const;
	bool checkAttack();
	void updateAllyMovementOrder();
	void updateAnimStates();
	void reset();
	void checkReset();
	sf::Vector2f getMovementOrderPos();
	

	

 private:
	 
	 float m_baseSpeed = 300.0f;
	 bool m_recallAllies = true;
	 
	 sf::Vector2f m_startPosition;
	 sf::Vector2f m_movmentOrderPos;
	 sf::Keyboard::Key m_allyFollowPlayerKey = sf::Keyboard::Key::F;
	 sf::Mouse::Button m_allyMoveMouseButton = sf::Mouse::Right;
	 InputManager* m_input = nullptr;
	 std::string m_idleAnimPath = "../Assets/Animations/KnightIdleBlue.png";
	 std::string m_runAnimPath = "../Assets/Animations/KnightRunAnim.png";
	 std::string m_attackAnimPath = "../Assets/Animations/KnightAttackAnim.png ";
	 std::string m_commandFlagTexturePath = "../Assets/Textures/flagIndicator.png";
	 std::string m_vertInputMapName = "playerVertical"; 
	 std::string m_horiInputMapName = "playerHorizontal";
	 std::map<sf::Keyboard::Key, float> m_vertcialDirectionMap = { {sf::Keyboard::W,-1.0f},{sf::Keyboard::S,1.0f} };
	 std::map<sf::Keyboard::Key, float> m_horizontalDirectionMap = { {sf::Keyboard::A,-1.0f},{sf::Keyboard::D,1.0f} };
	 Camera* m_camera = nullptr;
	 sf::FloatRect m_CurrentLevelAreaBounds;
	 std::unique_ptr<StaticObject> m_commandFlag;
	 std::unique_ptr<AnimationController> m_animationController;
	 std::map<std::string, AnimationObject> m_animStates;
	 float m_idleAnimDelay = 70.0f;
	 float m_runAnimDelay = 70.0f;
	 float m_attackAnimDelay = 100.0f;



};