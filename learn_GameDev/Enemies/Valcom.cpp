#include "Valcom.h"
#include <math.h>


Valcom::Valcom()
{
	init(sf::Vector2i(0, 0), directions::NORTH);
}


Valcom::Valcom(const sf::Vector2i& tile)
{
	init(tile, directions::NORTH);
}


Valcom::Valcom(const sf::Vector2i& tile, const directions& face)
{
	init(tile, face);
}


void Valcom::init(const sf::Vector2i& tile, const directions& face)
{
	heading = face;
	moveSpeed = 1.f;

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


void Valcom::move(Tile* tilemap[33][15],
	const sf::Vector2i& tileSize)
{
	standardMovement(tilemap, tileSize);
}


double Valcom::getClippingMargin() const
{
	return 0.01;
}


int Valcom::getMovementChance() const
{
	return 25;
}


Valcom::~Valcom()
{

}