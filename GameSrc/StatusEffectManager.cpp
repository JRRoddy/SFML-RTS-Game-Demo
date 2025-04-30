#include "StatusEffectManager.h"
#pragma once

StatusEffectManager::StatusEffectManager(std::map<StatusEffectIds, StatusEffect*>& statusEffectsToManage, Character * characterRef)
{
	m_statusEffects = statusEffectsToManage;
	m_characterRef = characterRef;
}

void StatusEffectManager::update()
{
	for (int i = 0; i < m_activeStatusEffects.size();i++) {
		m_activeStatusEffects[i]->effect(m_characterRef);
		if (m_activeStatusEffects[i]->finished()) {
			m_activeStatusEffects.erase(m_activeStatusEffects.begin() + i);
		}

	}
}

void StatusEffectManager::activateStatusEffect(StatusEffectIds id,Character * initiater)
{
	try {

		StatusEffect*& status = m_statusEffects.at(id);

		if(!status->getIsActive())
		{
			status->setInitiater(initiater); 
			status->activate();
			
		
		}

	}
	catch (...) {

		return;

	}


}
