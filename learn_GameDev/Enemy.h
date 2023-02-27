#pragma once
#include "TextureHolder.h"
#include "Animation.h"

class Enemy
{
public:
	Enemy();

	~Enemy();
private:
	enum class animIndex
	{
		WALKING_LEFT = 0,
		WALKING_RIGHT,
		WALKING_DOWN,
		WALKING_UP,
		DEATH,
		COUNT
	};
	sf::Sprite sprite;
	Animation anims[int(animIndex::COUNT)];
	animIndex curAnim;
};