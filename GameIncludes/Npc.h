#pragma once
#include "Character.h"
#include "AstarNode.h"
#include "AnimationController.h" 

// abstract npc class for any characters that will make use of pathfinding see cpp for more detail
class Npc :public Character {

public:

	Npc() {}; 
	virtual ~Npc(){}

	Character* getPlayerRef();

	void setBaseSprite(std::shared_ptr<sf::Sprite>& spriteRef);

	void setPlayerRef(Character* playerRef);

	virtual void updateGridTileState(gridTile* gridTile);

	bool getIsAttacking() const;

	void copyAnimController(AnimationController* animController);

	virtual void clone(Npc* copy);

	virtual void getPathDir();

	void setPath(std::vector< node*>& path);

	Character* getCharacterTarget();

	void setTargetPlayer();

	void setCharacterTarget(Character* character);

	virtual void setAnimStates();

	void getSprites(SpriteGenerator* spriteGenerator);
	
	// interact method that is generic across all npcs 
   // can be overriden to provide specifc npc's with specifc interactions with the player
	virtual void playerInteract() {};

	virtual sf::Vector2f getTargetPosition() ;
protected:
	Character* m_characterTarget = nullptr;
	Character* m_playerRef = nullptr;
	sf::Vector2f m_currentTargetPos;
	std::vector<node*> m_requestedPath;
	std::unique_ptr<AnimationController> m_animationController;
	bool m_canAttack = false;
	std::map<std::string, AnimationObject> m_animStates ={};
	std::string m_idleAnimPath;
	std::string m_runAnimPath;
	std::string m_attackAnimPath;
	float m_attackAnimDelay = 0.0f;
	float m_runAnimDelay = 0.0f;
	float m_idleAnimDelay = 0.0f;
	
};