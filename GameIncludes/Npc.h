#pragma once
#include "Character.h"
#include "AstarNode.h"
#include "AnimationController.h" 
#include "gridTile.h"
#include "StatusEffectManager.h"
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
	void checkAttackingFacingDirection();
	virtual void getPathDir();

	void setPath(std::vector< node*>& path);
	
	virtual void setTargetPlayer();



	virtual void setAnimStates();

	void getSprites(SpriteGenerator* spriteGenerator);
	void copyStats(characterStats& stats);
	// interact method that is generic across all npcs 
   // can be overriden to provide specifc npc's with specifc interactions with the player
	
	virtual void attackCharacter(Character* target);
	virtual void playerInteract() {};
	virtual void onPathEnd() {};
	bool characterTargetDeathCheck();
	virtual sf::Vector2f getTargetPosition();
	bool deathAnimFinished();
protected:
	
	Character* m_playerCharacterRef = nullptr;
	// since allies and enemies could be moving towards the player but be attacking other npcs
    // we need to have a seperate direction for them to face when they are attacking and running
	sf::Vector2f m_facingDirection;
	// current position for npc to move to 
	sf::Vector2f m_currentTargetPos;
	// path of astar nodes for npc to follow
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