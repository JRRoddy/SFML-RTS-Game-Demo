#include "AllyManager.h"

AllyManager::AllyManager(Player* player, Astar* astar, LevelGrid* levelGrid)
{
	m_playerRef = player;
	m_levelGrid = levelGrid;
	m_maxCollisionTreeDepth = 8;
	m_AStar = astar;
	m_AllyCollisionHandler = std::make_shared<CollisonHandler<AllyBase>>(CollisonHandler<AllyBase>());
	m_AllyCollisionHandler.get()->setTreeMaxDepth(m_maxCollisionTreeDepth);

}
AllyManager::~AllyManager()
{


}

void AllyManager::spawnAllies()
{
	if (m_refreshAlliesTimer.getElapsedTime().asSeconds() >= m_refereshTime.asSeconds()) {
		// if we have hit our refresh timer cool down for refreshing ally spawns
		
		// as allies have an inactive state where the player has not recurited them 
		// we have a counter within the ally manager for each static ally which
		// gets decremented each time the player recurits on ally 
		// this is used to determine whether or not more ally objects need to 
		// be requested from the pool
		m_staticAlliesCount = std::max(0, m_staticAlliesCount);
		if (m_currentPool->hasAvailabeObject() && m_staticAlliesCount != m_currentArea->getMaxAllyCap()) {
			// if we had an avaialbe object in the current object pool we are using 
			m_staticAlliesCount++; // increase the count of static allies to recruit in the area
			AllyBase* ally = m_currentPool->activateObject();  // get  availabe object from pool
			gridTile* randomTile = m_levelGrid->getRandomLocationInGrid();// get ally loc
			// set ally  world pos based on grid tile generated 
			ally->setPosition(m_levelGrid->getWorldPositionAtIndex(randomTile->fullIndex));
			ally->setGridTile(randomTile); 
			m_activeBuffer.push_back(ally);
			
		}

		resetSpawnDelay();

	}





}

void AllyManager::update(float dt)
{

	for (int i = 0; i < m_activeBuffer.size(); i++) {

		if(checkAllyRemoval(i)) continue; // check if ally should be removed from active buffer
		AllyBase* ally = m_activeBuffer[i]; 
		updateAllySelectedStatus(ally); // update recruited status and selected status of ally
		updateAllyPath(ally); // update path for ally to follow 
		ally->update(dt);// call ally update function 
		// insert active ally into collision tree to check for collision 
		// between other objects 
		m_AllyCollisionHandler.get()->insertItem(ally->getBounds(), ally);

		
		

	}


	// check to see if we need to spawn allies 
	// and get them from the current ally object pool
	spawnAllies(); 

}




void AllyManager::initAllyPools(AreaTypes areaType, std::vector<AllyInitialiser> & alliesToInit, SpriteGenerator *spriteGenerator)
{

	// initialse all of the objects in each of the ally initialisers 
	// that will be used to instantiate all allies in the particualr 
	// pool being generated 
	for (int i = 0; i < alliesToInit.size(); i++)
	{ 
		alliesToInit[i].getHeldObject()->setPlayerRef(m_playerRef);
		alliesToInit[i].getHeldObject()->getSprites(spriteGenerator);
	}
	// generate object pool from the ally initialisers that hold the base 
    // objects to be copied from according to the current area type
	m_areaPools.emplace(areaType, alliesToInit);
	
}

void AllyManager::setCurrentArea(LevelAreaContainer* levelArea)
{
	m_currentArea = levelArea; // set current area object ref
	// time between refreshing ally spawns 
	m_refereshTime = sf::seconds(m_currentArea->getAllyRefreshCoolDown());
	
	// set the current ally pool based on area type
	m_currentPool = &m_areaPools[m_currentArea->getAreaType()];
	// reset the area being used by the collision handler to current area 
	m_AllyCollisionHandler.get()->resizeTree(sf::FloatRect(m_currentArea->getTopLeft(), m_currentArea->getWorldDimensions()));

}

bool AllyManager::checkAllyRemoval(int index)
{
	// if we need to remove an ally as it has been marked as inactive 
	if (!m_activeBuffer[index]->getIsActive()) {
		// remove it from active buffer and the active buffer of the pool we 
		// are using as they line up in memory 
		m_activeBuffer.erase(m_activeBuffer.begin() + index); 
		m_currentPool->resetActiveObject(index);
		return true;
	}
	return false;
}

void AllyManager::resetSpawnDelay()
{
	m_refreshAlliesTimer.restart(); 


}

void AllyManager::updateAllySelectedStatus(AllyBase * ally)
{

	// was the ally clicked 
	if (m_playerRef->isMouseReleased(sf::Mouse::Left) &&
		ally->getBounds().contains(m_playerRef->getMousePosition())) {
		bool isRecurited = ally->isRecurited(); // temporarily store if the ally 
		//was recurited or not to ensure that the inactive allies count is 
		// accurate
		ally->playerInteract(); // interact with ally and potentially recurit them 
		if (isRecurited == false && ally->isRecurited() ) {
			// if ally was recruited decriment the static ally count
			// as they are now movebale by the player 
			// this means we can now potentially spawn more allies based on pool
			// availabillity 
			m_staticAlliesCount--;
		}
		return;
	}
	// if ally's bounding box didnt contain mouse pos ally is not selected 
	ally->setIsSelected(false);

}
// update ally collisions with enemies using a passed in buffer of enemies 
// this buffer is of EnemyBase class pointers allowing it to be generic 
// and any enemy derrived from EnemyBase to be passed into the buffer
// this means there is no requirement for multiple vectors of enemies of different types
void AllyManager::updateEnemyCollision(std::vector<EnemyBase*> & Buffer)
{
	// go through the buffer
	for (EnemyBase* enemy : Buffer) { 

		std::vector<quadTreeItem<AllyBase>> result; 
		// query the collision tree within the ally manager 
		// with the bounding box of the current enemy being checked
		m_AllyCollisionHandler->queryCollisionTree(enemy->getBounds(), result);
		// if we had any items contained within the result i.e the enemy's 
		//collision box overlapped space that conatains allies
		for (quadTreeItem<AllyBase> &allyItem : result) {
			// call the collision method for the intersecting allies on the enemy
			// to be accounted for 
			allyItem.gameObject->collision(enemy);
			enemy->collision(allyItem.gameObject);

		}
        


	}
	
	// reset collision tree ready for next update 
	m_AllyCollisionHandler.get()->resetCollisionTreeItems();
}

void AllyManager::updateAllyPath(AllyBase* ally)
{
	if (ally->isRecurited()) { // if the ally is recurited it will be able to move around 
		// upate current tile grid state for ally applying tile effects
		ally->updateGridTileState(m_levelGrid->getGridTile(ally->getPosition()));
		// set the path for ally based on its current target 
		ally->setPath(m_AStar->getPath(ally->getPosition(), ally->getTargetPosition()));
		
	}
}

void AllyManager::drawAllies(sf::RenderWindow * window)
{

	for (int i = 0; i < m_activeBuffer.size(); i++) {

		m_activeBuffer[i]->draw(window);
	}
	//m_AllyCollisionHandler->drawCollisionTree(window);
} 

