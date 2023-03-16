#include "ONeal.h"


ONeal::ONeal(const sf::Vector2i& tile) : Valcom(tile)
{
	init(tile, dir::NORTH);
}


ONeal::ONeal(const sf::Vector2i& tile, const dir& face) : Valcom(tile)
{
	init(tile, face);
}


void ONeal::init(const sf::Vector2i& tile, const dir& face)
{
	heading = face;
	moveSpeed = 3.f;

	sf::Texture* t = &TextureHolder::get(textures::PLAYER);

	anims[int(animIndex::WALKING_LEFT)].setUp(*t, 0, 16 * 0, 12, 16, 3);
	anims[int(animIndex::WALKING_RIGHT)].setUp(*t, 0, 16 * 1, 12, 16, 3);
	anims[int(animIndex::WALKING_DOWN)].setUp(*t, 0, 16 * 2, 12, 16, 3);
	anims[int(animIndex::WALKING_UP)].setUp(*t, 0, 16 * 3, 12, 16, 3);
	anims[int(animIndex::DEATH)].setUp(*t, 0, 16 * 4, 16, 16, 7);

	curAnim = animIndex::WALKING_RIGHT;
	anims[int(curAnim)].applyToSprite(sprite);

	sprite.setPosition(50 * tile.x, 100 + 50 * tile.y);
}


double ONeal::getClippingMargin() const
{
	return 1.5;
}


ONeal::~ONeal()
{
}