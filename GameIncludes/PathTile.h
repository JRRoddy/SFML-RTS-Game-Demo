
#include "Tile.h"
class PathTile : public Tile {
public:
	PathTile(sf::Vector2f position, float width, float height);
	PathTile(sf::Vector2f position);
	PathTile();
	Tile* clone() override;
	void dynamicObjectEffect(DynamicObject* object)override;
	void resetDynamicObjectEffect(DynamicObject* object) override;
private:

	float m_movementSpeedModifier = 1.25;



};