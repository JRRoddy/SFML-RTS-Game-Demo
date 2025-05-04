#pragma once
#include "StatusEffect.h"
#include "StatusEffectIds.h"
#include "map"
#include "vector"
#include "iostream"

// this class can be constructed within any character and is responsible 
// for managing all of the status effects that have been applied to them
// performing operations such as removing status effects that have finished along with 
// applying each effect of active status effects to the character it is attached to
class StatusEffectManager {

public:
	StatusEffectManager() {};
	~StatusEffectManager() {};
	StatusEffectManager(std::map<StatusEffectIds, std::shared_ptr<StatusEffect>>& statusEffectsToManage,characterStats * characterRef);
	void update();
	bool activateStatusEffect(StatusEffectIds id, characterStats * initiater);
	void reset();




private:
	std::map<StatusEffectIds, std::shared_ptr<StatusEffect>> m_statusEffects;
	std::vector<StatusEffect*> m_activeStatusEffects;
	characterStats* m_characterStatsRef = nullptr;
};