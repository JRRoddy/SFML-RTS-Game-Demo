#pragma once
#include "Character.h"
#include "AstarNode.h"
#include "AnimationController.h" 
#include "gridTile.h"
// abstract npc class for any characters that will make use of pathfinding see cpp for more detail
class Npc :public Character {

public:

	Npc() {}; 
	virtual ~Npc(){}

	Character * getPlayerCharacterRef();

	void setBaseSprite(std::shared_ptr<sf::Sprite>& spriteRef);

	void setPlayerCharacterRef(Character* playerRef);

	virtual void updateGridTileState(gridTile* gridTile);


	void copyAnimController(AnimationController* animController);
	bool getIsActive();
	virtual void clone(Npc* copy);

	virtual void getPathDir();

	void setPath(std::vector< node*>& path);

	Character* getCharacterTarget();

	virtual void setTargetPlayer();

	void setCharacterTarget(Character* character);

	virtual void setAnimStates();

	void getSprites(SpriteGenerator* spriteGenerator);
	
	// interact method that is generic across all npcs 
   // can be overriden to provide specifc npc's with specifc interactions with the player
	
	virtual void attackCharacter(Character* target);
	virtual void playerInteract() {};
	
	bool characterTargetDeathCheck();
	virtual sf::Vector2f getTargetPosition();
	bool deathAnimFinished();
protected:
	Character* m_characterTarget = nullptr;
	Character* m_playerCharacterRef = nullptr;
	sf::Vector2f m_currentTargetPos;
	std::vector<node*> m_requestedPath;
	std::unique_ptr<AnimationController> m_animationController;
	std::map<std::string, AnimationObject> m_animStates ={};
	std::string m_idleAnimPath;
	std::string m_runAnimPath;
	std::string m_deathAnimPath;
	std::string m_attackAnimPath;
	float m_attackAnimDelay = 0.0f;
	float m_runAnimDelay = 0.0f;
	float m_deathAnimDelay = 0.0f;
	float m_idleAnimDelay = 0.0f;
	
};