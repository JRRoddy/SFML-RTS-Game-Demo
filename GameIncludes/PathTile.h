
#include "Tile.h"
class PathTile : public Tile {
public:
	PathTile(sf::Vector2f position, float width, float height);
	PathTile(sf::Vector2f position);
	PathTile();
	Tile* clone() override;
	void playerEffect(Player* player)override;
	void resetPlayerEffect(Player* player)override;
private:


};