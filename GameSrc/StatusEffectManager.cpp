#pragma once
#include "StatusEffectManager.h"


StatusEffectManager::StatusEffectManager(std::map<StatusEffectIds, std::shared_ptr<StatusEffect>>& statusEffectsToManage, characterStats* characterStatsRef)
{
	std::cout << "initialising status effect manager" << std::endl;
	// takes in  a reference to the stats of the character it is managing based on 
	// and applying status effects to along with a map of status effect id's 
	// that key into known status effects that can be applied to the character 
	m_statusEffects = statusEffectsToManage;
	m_characterStatsRef = characterStatsRef;  
	std::cout <<"character stats base health"<< m_characterStatsRef->baseHealth << std::endl;
	
}

void StatusEffectManager::update()
{

	//if we have any active references in the active status 
	// effects vector then we go through them and apply their 
	// effect and remove them accordingly
	for (int i = 0; i < m_activeStatusEffects.size();i++) {
		m_activeStatusEffects[i]->effect(m_characterStatsRef);
		if (m_activeStatusEffects[i]->finished()){
			std::cout << "effect finished of type: " << typeid(*m_activeStatusEffects[i]).name() << std::endl;
			m_activeStatusEffects[i]->reset();
			m_activeStatusEffects.erase(m_activeStatusEffects.begin() + i);
		}
	}
} 



bool StatusEffectManager::activateStatusEffect(StatusEffectIds id,characterStats * initiaterStats)
{

	try {
		// if the status effect is not in the map this try block will throw an
		// exception which is handle by the catch which simply returns 
		//that the status effect failed to activate as this charater 
		// is not effected by it(its not in the known map of status effects
		//that effect the character)
		StatusEffect *statusEffect = m_statusEffects.at(id).get();
		// if we could apply the status effect
		if(statusEffect->canApply())
		{ 
			std::cout << "could apply status effect of type" << typeid(*statusEffect).name() << std::endl;
			// pass the stats of the initiater(character applying the status effect)
			// to the status effect being accessed in the map based on the id passed in
			statusEffect->setInitiater(initiaterStats);
            statusEffect->activate(); // activate the status effect
			// send a refernce to it into the active status effects vector
			m_activeStatusEffects.push_back(statusEffect); 
			return true;
		}

	}
	catch (...) {
		std::cout << "could not apply status effect was not in map"  << std::endl;
		// could not apply the status effect as it was not in the map 
		// meaning it couldnt be applied to this character
		return false;

	}
	std::cout << "could not apply status effect" << std::endl;
	// other wise we could not apply the status effect
	// due to it failing to apply 
	return false;

}

void StatusEffectManager::reset()
{
	std::cout << "resetting status effect manager" << std::endl;
	// reset all active status effects and clear the active status effect vector
	for (int i = 0; i < m_activeStatusEffects.size(); i++) {
		m_activeStatusEffects[i]->reset();
	}
	m_activeStatusEffects.clear();

}
