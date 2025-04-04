#pragma once

class EnemyBase {

public:


	virtual void attack() = 0;
	/*void takeDamage(float damage);*/



private:
	float m_attackPower = 0.0f;
	float m_health = 0.0f;
	bool isActive = false;


};