#include "Valcom.h"
#include <math.h>


Valcom::Valcom(const Player* plrPtr)
	: Enemy(plrPtr)
{
	init(sf::Vector2i(1, 1), direction::NORTH);
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

	//Adjust tile position to world position
	sprite.setPosition(48 * (tile.x - 1), 100 + 48 * (tile.y - 1));

	Enemy::setPointValue(100);
}


void Valcom::move(Tile* tilemap[33][15])
{
	//If no movement occurred (wall in front)
	if (!moveForward(tilemap))
		//Bounce off of the wall
		bounce();

	//If at a tile and the debounce is valid (more likely to when player is close)
	if (atTile(tilemap) && (++dirDebounce >= 10 ||
		(distanceToPlayer() < 3 && dirDebounce >= 3)))
	{
		//Reset debounce counter
		dirDebounce = 0;

		//Attempt to assign random heading
		randomHeading(tilemap);
	}
}


Valcom::~Valcom()
{

}