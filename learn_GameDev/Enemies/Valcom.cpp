#include "Valcom.h"
#include <math.h>


Valcom::Valcom(const Player* plrPtr) : Enemy(plrPtr)
{
	init(sf::Vector2i(0, 0), directions::NORTH);
}


Valcom::Valcom(const Player* plrPtr,
	const sf::Vector2i& tile) : Enemy(plrPtr)
{
	init(tile, directions::NORTH);
}


Valcom::Valcom(const Player* plrPtr,
	const sf::Vector2i& tile, const directions& face) : Enemy(plrPtr)
{
	init(tile, face);
}


void Valcom::init(const sf::Vector2i& tile, const directions& face)
{
	heading = face;
	moveSpeed = 1.f;
	dirDebounce = 0;

	sf::Texture* t = &TextureHolder::get(textures::ENEMIES);
	anims[int(animIndex::RIGHT)].setUp(*t, 0, 16 * 0, 16, 16, 3);
	anims[int(animIndex::LEFT)].setUp(* t, 0, 16 * 1, 16, 16, 3);
	anims[int(animIndex::DEATH)].setUp(*t, 0, 16 * 2, 16, 16, 5);

	if (face == directions::WEST)
		curAnim = animIndex::LEFT;
	else
		curAnim = animIndex::RIGHT;

	anims[int(curAnim)].applyToSprite(sprite);

	sprite.setPosition(48 * tile.x, 100 + 48 * tile.y);
}


void Valcom::move(Tile* tilemap[33][15])
{
	moveForwardAndBounce(tilemap);

	if (isAtTile(tilemap) && ++dirDebounce >= 10)
	{
		dirDebounce = 0;
		changeHeadingRandomly(tilemap);
	}
}


double Valcom::clippingMargin() const
{
	return 0.25;
}


Valcom::~Valcom()
{

}