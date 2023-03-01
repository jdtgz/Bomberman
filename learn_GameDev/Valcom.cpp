#include "Valcom.h"


Valcom::Valcom()
{
	vertical = true;
	positive = true;
	moveSpeed = 3.f;

	sf::Texture* t = &TextureHolder::get(textures::PLAYER);

	anims[int(animIndex::WALKING_LEFT)].setUp(*t, 0, 16 * 0, 12, 16, 3);
	anims[int(animIndex::WALKING_RIGHT)].setUp(*t, 0, 16 * 1, 12, 16, 3);
	anims[int(animIndex::WALKING_DOWN)].setUp(*t, 0, 16 * 2, 12, 16, 3);
	anims[int(animIndex::WALKING_UP)].setUp(*t, 0, 16 * 3, 12, 16, 3);
	anims[int(animIndex::DEATH)].setUp(*t, 0, 16 * 4, 16, 16, 7);

	curAnim = animIndex::WALKING_RIGHT;
	anims[int(curAnim)].applyToSprite(sprite);

	sprite.setPosition(105, 100);
}


void Valcom::move(Tile* tilemap[31][13],
	const sf::Vector2i& mapSize, const sf::Vector2i& closestTile)
{
	if (vertical)
	{

	}
}


void Valcom::update(const float& dt)
{
	return;
}


Valcom::~Valcom()
{

}