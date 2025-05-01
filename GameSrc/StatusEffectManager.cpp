#pragma once
#include "StatusEffectManager.h"


StatusEffectManager::StatusEffectManager(std::map<StatusEffectIds, std::shared_ptr<StatusEffect>>& statusEffectsToManage, characterStats* characterStatsRef)
{
	std::cout << "initialising status effect manager" << std::endl;
	m_statusEffects = statusEffectsToManage;
	m_characterStatsRef = characterStatsRef;  
	std::cout <<"character stats base health"<< m_characterStatsRef->baseHealth << std::endl;
	
}

void StatusEffectManager::update()
{
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

		StatusEffect *statusEffect = m_statusEffects.at(id).get();

		if(statusEffect->canApply())
		{ 
			std::cout << "could apply status effect of type" << typeid(*statusEffect).name() << std::endl;
			statusEffect->setInitiater(initiaterStats);
            statusEffect->activate();
			m_activeStatusEffects.push_back(statusEffect);
			return true;
		}

	}
	catch (...) {
		std::cout << "could not apply status effect was not in map"  << std::endl;

		return false;

	}
	std::cout << "could not apply status effect" << std::endl;

	return false;

}

void StatusEffectManager::reset()
{
	std::cout << "resetting status effect manager" << std::endl;
	for (int i = 0; i < m_activeStatusEffects.size(); i++) {
		m_activeStatusEffects[i]->reset();
	}
	m_activeStatusEffects.clear();

}
