#include "ONeal.h"
#include <math.h>


ONeal::ONeal(const Player* plrPtr) : Enemy(plrPtr)
{
	init(sf::Vector2i(0, 0), directions::NORTH);
}


ONeal::ONeal(const Player* plrPtr,
	const sf::Vector2i& tile) : Enemy(plrPtr)
{
	init(tile, directions::NORTH);
}


ONeal::ONeal(const Player* plrPtr,
	const sf::Vector2i& tile, const directions& face) : Enemy(plrPtr)
{
	init(tile, face);
}


void ONeal::init(const sf::Vector2i& tile, const directions& face)
{
	heading = face;
	moveSpeed = 1.5f;
	dirDebounce = 0;

	sf::Texture* t = &TextureHolder::get(textures::ENEMIES);
	anims[int(animIndex::RIGHT)].setUp(*t, 0, 16 * 3, 16, 16, 3);
	anims[int(animIndex::LEFT)].setUp(*t, 0, 16 * 4, 16, 16, 3);
	anims[int(animIndex::DEATH)].setUp(*t, 0, 16 * 5, 16, 16, 1);

	if (face == directions::WEST)
		curAnim = animIndex::LEFT;
	else
		curAnim = animIndex::RIGHT;

	anims[int(curAnim)].applyToSprite(sprite);

	sprite.setPosition(48 * tile.x, 100 + 48 * tile.y);
}


void ONeal::move(Tile* tilemap[33][15])
{
	moveForwardAndBounce(tilemap);

	if (isAtTile(tilemap) && ++dirDebounce >= 5)
	{
		dirDebounce = 0;
		changeHeadingRandomly(tilemap);
	}
}


double ONeal::clippingMargin() const
{
	return 1.25;
}


ONeal::~ONeal()
{

}