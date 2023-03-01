#include "Enemy.h"


Enemy::Enemy()
{
	curAnim = animIndex::WALKING_LEFT;
	moveSpeed = 0.f;
	alive = true;
}


void Enemy::draw(sf::RenderWindow& w) const
{
	w.draw(sprite);
}


void Enemy::die()
{
	alive = false;
}


bool Enemy::isAlive() const
{
	return alive;
}

sf::Vector2f Enemy::getPosition() const
{
	return sprite.getPosition();
}


Enemy::~Enemy()
{
}