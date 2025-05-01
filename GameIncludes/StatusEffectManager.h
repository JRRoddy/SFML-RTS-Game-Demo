#pragma once
#include "StatusEffect.h"
#include "StatusEffectIds.h"
#include "map"
#include "vector"
#include "iostream"
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