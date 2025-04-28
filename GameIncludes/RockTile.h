#include "Tile.h"

class RockTile:public Tile {

public:
	RockTile(sf::Vector2f position, float width, float height);
	RockTile(sf::Vector2f position);
	RockTile();
	Tile* clone() override;
	void dynamicObjectEffect(DynamicObject* object)override;
	void resetDynamicObjectEffect(DynamicObject* object) override;


private:


};