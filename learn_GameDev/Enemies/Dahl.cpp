#include "Dahl.h"


Dahl::Dahl(const Player* plrPtr)
	: ONeal(plrPtr)
{
	init(sf::Vector2i(1, 1), direction::NORTH);
}


Dahl::Dahl(const Player* plrPtr, const sf::Vector2i& tile)
	: ONeal(plrPtr)
{
	init(tile, direction::NORTH);
}


Dahl::Dahl(const Player* plrPtr,
	const sf::Vector2i& tile, const direction& face)
	: ONeal(plrPtr)
{
	init(tile, face);
}


void Dahl::init(const sf::Vector2i& tile, const direction& face)
{
	heading = face;
	moveSpeed = 1.75f;
	clippingMargin = 1.5f;

	sf::Texture* t = &TextureHolder::get(textures::ENEMIES);
	anims[int(animIndex::RIGHT)].setUp(*t, 0, 16 * 6, 16, 16, 3);
	anims[int(animIndex::LEFT)].setUp(*t, 0, 16 * 7, 16, 16, 3);
	anims[int(animIndex::DEATH)].setUp(*t, 0, 16 * 8, 16, 16, 5);

	if (face == direction::WEST)
		curAnim = animIndex::LEFT;
	else
		curAnim = animIndex::RIGHT;

	anims[int(curAnim)].applyToSprite(sprite);

	sprite.setPosition(48 * (tile.x - 1), 100 + 48 * (tile.y - 1));
}


Dahl::~Dahl()
{
}