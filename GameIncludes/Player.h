#include "DynamicObject.h"
class Player: public DynamicObject {
 public:

	Player(float speed); 
	Player(float speed, float damage); 
	void setDamage(float damage);
	float getDamage();

 private:
	 float m_damage;
	 



};