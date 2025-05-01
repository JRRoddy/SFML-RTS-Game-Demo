#pragma once
// data storage to encapsulate all the generic stats shared
// across characters
struct characterStats {

	float health;
	float baseHealth;
	float damage; 
	float gold; 

	characterStats() {
		health = 0.0f;
		baseHealth = 0.0f;
		damage = 0.0f;
		gold = 0.0f;
	}
	characterStats(float _baseHealth, float _damage, float _gold) {
		baseHealth = _baseHealth;
		health = _baseHealth;
		damage = _damage;
		gold = _gold;

	}
	// copy constructors
	characterStats(const characterStats& other) {

		baseHealth = other.baseHealth;
		health = other.health;
		gold = other.gold;
		damage = other.damage;
	}

	characterStats operator = (const characterStats& other) {
		baseHealth = other.baseHealth;
		health = other.health;
		gold = other.gold;
		damage = other.damage;
		return *this;
	}



};