#include "Enemy.h"


Enemy::Enemy()
{
	// initialize visual attributes 
	sf::Texture* t = &TextureHolder::get(textures::PLAYER);

	// setup animations 
	anims[int(animIndex::WALKING_LEFT)].setUp(*t, 0, 16 * 0, 12, 16, 3);
	anims[int(animIndex::WALKING_RIGHT)].setUp(*t, 0, 16 * 1, 12, 16, 3);
	anims[int(animIndex::WALKING_DOWN)].setUp(*t, 0, 16 * 2, 12, 16, 3);
	anims[int(animIndex::WALKING_UP)].setUp(*t, 0, 16 * 3, 12, 16, 3);
	anims[int(animIndex::DEATH)].setUp(*t, 0, 16 * 4, 16, 16, 7);

	// set the starting animation
	curAnim = animIndex::WALKING_RIGHT;
	anims[int(curAnim)].applyToSprite(sprite);
}


Enemy::~Enemy()
{
}