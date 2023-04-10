#include "ONeal.h"
#include <math.h>


ONeal::ONeal(const Player* plrPtr)
	: Enemy(plrPtr)
{
	init(sf::Vector2i(1, 1), direction::NORTH);
}


ONeal::ONeal(const Player* plrPtr, const sf::Vector2i& tile)
	: Enemy(plrPtr)
{
	init(tile, direction::NORTH);
}


ONeal::ONeal(const Player* plrPtr,
	const sf::Vector2i& tile, const direction& face)
	: Enemy(plrPtr)
{
	init(tile, face);
}


void ONeal::init(const sf::Vector2i& tile, const direction& face)
{
	heading = face;
	moveSpeed = 1.5f;
	clippingMargin = 1.25f;
	dirDebounce = 0;

	sf::Texture* t = &TextureHolder::get(textures::ENEMIES);
	anims[int(animIndex::RIGHT)].setUp(*t, 0, 16 * 3, 16, 16, 3);
	anims[int(animIndex::LEFT)].setUp(*t, 0, 16 * 4, 16, 16, 3);
	anims[int(animIndex::DEATH)].setUp(*t, 0, 16 * 5, 16, 16, 1);

	if (face == direction::WEST)
		curAnim = animIndex::LEFT;
	else
		curAnim = animIndex::RIGHT;

	anims[int(curAnim)].applyToSprite(sprite);

	//Adjust tile position to world position
	sprite.setPosition(48 * (tile.x - 1), 100 + 48 * (tile.y - 1));
}


void ONeal::move(Tile* tilemap[33][15])
{
	//Move forward
	bool moved = moveForward(tilemap);

	//If no movement occurred (wall in front)
	if (!moved)
		//Bounce off of the wall
		bounce();

	//If at a tile and the debounce is valid
	if (atTile(tilemap) && ++dirDebounce >= 5)
	{
		//Reset debounce counter
		dirDebounce = 0;

		//Attempt to assign random heading
		randomHeading(tilemap);
	}
}


ONeal::~ONeal()
{

}