#pragma once
#include "StatusEffect.h"
#include "StatusEffectIds.h"

class StatusEffectManager {

public:
	 
	StatusEffectManager(std::map<StatusEffectIds, StatusEffect*>& statusEffectsToManage, Character * characterRef); 

	void update();

	void activateStatusEffect(StatusEffectIds id, Character * initiater);





private:
	std::map<StatusEffectIds, StatusEffect*> m_statusEffects;
	std::vector<StatusEffect*> m_activeStatusEffects;
	Character* m_characterRef;
};