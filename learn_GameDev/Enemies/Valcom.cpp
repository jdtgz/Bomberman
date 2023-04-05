#include "Valcom.h"
#include <math.h>


Valcom::Valcom(const Player* plrPtr)
	: Enemy(plrPtr)
{
	init(sf::Vector2i(0, 0), direction::NORTH);
}


Valcom::Valcom(const Player* plrPtr, const sf::Vector2i& tile)
	: Enemy(plrPtr)
{
	init(tile, direction::NORTH);
}


Valcom::Valcom(const Player* plrPtr,
	const sf::Vector2i& tile, const direction& face)
	: Enemy(plrPtr)
{
	init(tile, face);
}


void Valcom::init(const sf::Vector2i& tile, const direction& face)
{
	heading = face;
	moveSpeed = 1.f;
	clippingMargin = 0.25f;
	dirDebounce = 0;

	sf::Texture* t = &TextureHolder::get(textures::ENEMIES);
	anims[int(animIndex::RIGHT)].setUp(*t, 0, 16 * 0, 16, 16, 3);
	anims[int(animIndex::LEFT)].setUp(* t, 0, 16 * 1, 16, 16, 3);
	anims[int(animIndex::DEATH)].setUp(*t, 0, 16 * 2, 16, 16, 5);

	if (face == direction::WEST)
		curAnim = animIndex::LEFT;
	else
		curAnim = animIndex::RIGHT;

	anims[int(curAnim)].applyToSprite(sprite);

	sprite.setPosition(48 * tile.x, 100 + 48 * tile.y);
}


void Valcom::move(Tile* tilemap[33][15])
{
	bool moved = moveForward(tilemap);

	if (!moved)
		bounce();

	if (atTile(tilemap) && ++dirDebounce >= 10)
	{
		dirDebounce = 0;
		randomHeading(tilemap);
	}
}


Valcom::~Valcom()
{

}