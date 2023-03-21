#include "ONeal.h"


ONeal::ONeal(const Player* plrPtr)
{
	init(plrPtr, sf::Vector2i(0, 0), directions::NORTH);
}


ONeal::ONeal(const Player* plrPtr, const sf::Vector2i& tile)
{
	init(plrPtr, tile, directions::NORTH);
}


ONeal::ONeal(const Player* plrPtr,
	const sf::Vector2i& tile, const directions& face)
{
	init(plrPtr, tile, face);
}


void ONeal::init(const Player* plrPtr,
	const sf::Vector2i& tile, const directions& face)
{
	playerPointer = plrPtr;
	heading = face;
	moveSpeed = 1.5f;
	chasePlayer = false;

	sf::Texture* t = &TextureHolder::get(textures::ENEMIES);
	anims[int(animIndex::RIGHT)].setUp(*t, 0, 16 * 3, 16, 16, 3);
	anims[int(animIndex::LEFT)].setUp(*t, 0, 16 * 4, 16, 16, 3);
	anims[int(animIndex::DEATH)].setUp(*t, 0, 16 * 5, 16, 16, 1);

	if (face == directions::WEST)
		curAnim = animIndex::LEFT;
	else
		curAnim = animIndex::RIGHT;

	curAnim = animIndex::RIGHT;
	anims[int(curAnim)].applyToSprite(sprite);

	sprite.setPosition(48 * tile.x, 100 + 48 * tile.y);
}


void ONeal::update(const float& dt)
{
	Enemy::update(dt);
}


void ONeal::move(Tile* tilemap[33][15],
	const sf::Vector2i& mapSize)
{
	chaseDebounce++;

	if (chasePlayer)
	{
		chasePlayerMovement(tilemap, mapSize, playerPointer);
	}
	else
	{
		standardMovement(tilemap, mapSize);
	}

	//Occassionally Chase the Player
	if (rand() % 100 < getChaseChance() && chaseDebounce >= CHASE_DEBOUNCE_MAX)
	{
		chaseDebounce = 0;
		chasePlayer = !chasePlayer;
	}
}


double ONeal::getClippingMargin() const
{
	return 1.5;
}


int ONeal::getMovementChance() const
{
	return 80;
}


int ONeal::getChaseChance() const
{
	return 2;
}


ONeal::~ONeal()
{
}