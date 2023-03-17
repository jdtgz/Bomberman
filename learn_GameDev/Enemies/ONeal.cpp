#include "ONeal.h"


ONeal::ONeal(const sf::Vector2i& tile) : Valcom(tile)
{
	init(tile, directions::NORTH);
}


ONeal::ONeal(const sf::Vector2i& tile, const directions& face) : Valcom(tile)
{
	init(tile, face);
}


void ONeal::init(const sf::Vector2i& tile, const directions& face)
{
	heading = face;
	moveSpeed = 1.5f;

	sf::Texture* t = &TextureHolder::get(textures::ENEMIES);
	anims[int(animIndex::RIGHT)].setUp(*t, 0, 16 * 3, 16, 16, 3);
	anims[int(animIndex::LEFT)].setUp(*t, 0, 16 * 4, 16, 16, 3);
	anims[int(animIndex::DEATH)].setUp(*t, 0, 16 * 5, 16, 16, 5);

	if (face == directions::WEST)
		curAnim = animIndex::LEFT;
	else
		curAnim = animIndex::RIGHT;

	curAnim = animIndex::RIGHT;
	anims[int(curAnim)].applyToSprite(sprite);

	sprite.setPosition(48 * tile.x, 100 + 48 * tile.y);
}


double ONeal::getClippingMargin() const
{
	return 1.5;
}


ONeal::~ONeal()
{
}