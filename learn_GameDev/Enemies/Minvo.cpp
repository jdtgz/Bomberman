#include "Minvo.h"


Minvo::Minvo(const Player* plrPtr)
	: ONeal(plrPtr)
{
	init(sf::Vector2i(1, 1), direction::NORTH);
}


Minvo::Minvo(const Player* plrPtr, const sf::Vector2i& tile)
	: ONeal(plrPtr)
{
	init(tile, direction::NORTH);
}


Minvo::Minvo(const Player* plrPtr,
	const sf::Vector2i& tile, const direction& face)
	: ONeal(plrPtr)
{
	init(tile, face);
}


void Minvo::init(const sf::Vector2i& tile, const direction& face)
{
	setHeading(face);
	moveSpeed = 2.25f;
	clippingMargin = 2.f;

	distance = 3;
	chaseChance = 4;
	debounceMax = 3;

	sf::Texture* t = &TextureHolder::get(textures::ENEMIES);
	anims[int(animIndex::RIGHT)].setUp(*t, 0, 16 * 9, 16, 16, 3);
	anims[int(animIndex::LEFT)].setUp(*t, 0, 16 * 10, 16, 16, 3);
	anims[int(animIndex::DEATH)].setUp(*t, 0, 16 * 11, 16, 16, 5);
	anims[int(curAnim)].applyToSprite(sprite);

	//Adjust tile position to world position
	sprite.setPosition(48 * (tile.x - 1), 100 + 48 * (tile.y - 1));
}


Minvo::~Minvo()
{

}