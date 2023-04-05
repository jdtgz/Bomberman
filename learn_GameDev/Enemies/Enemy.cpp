#include "Enemy.h"


Enemy::Enemy(const Player* plrPtr)
{
	heading = direction::NORTH;
	curAnim = animIndex::RIGHT;
	moveSpeed = 1.f;
	clippingMargin = 1.f;
	alive = true;
	playerRef = plrPtr;
}


void Enemy::update(const float& dt)
{
	anims[int(curAnim)].update(dt);
	anims[int(curAnim)].applyToSprite(sprite);
}


bool Enemy::moveForward(Tile* tilemap[33][15])
{
	sf::Vector2i t = getTilePosition();
	bool moved = false;
	switch (heading)
	{
	case direction::NORTH:
		if (t.y >= 0 && sprite.getPosition().y >= 100 &&
			tilemap[t.x][t.y]->getType() == tileType::AIR)
		{
			sprite.move(0, -moveSpeed);
			moved = true;
		}
		break;
	case direction::SOUTH:
		if (t.y < 14 && sprite.getPosition().y < 48 * 12 + 100 &&
			tilemap[t.x][t.y + 1]->getType() == tileType::AIR)
		{
			sprite.move(0, moveSpeed);
			moved = true;
		}
		break;
	case direction::EAST:
		if (t.x >= 0 && sprite.getPosition().x < 48 * 30 &&
			tilemap[t.x + 1][t.y]->getType() == tileType::AIR)
		{
			sprite.move(moveSpeed, 0);
			moved = true;
		}
		break;
	case direction::WEST:
		if (t.x < 32 && sprite.getPosition().x >= 0 &&
			tilemap[t.x][t.y]->getType() == tileType::AIR)
		{
			sprite.move(-moveSpeed, 0);
			moved = true;
		}
	}
	return moved;
}


void Enemy::bounce()
{
	switch (heading)
	{
	case direction::NORTH:
		heading = direction::SOUTH;
		break;
	case direction::SOUTH:
		heading = direction::NORTH;
		break;
	case direction::EAST:
		heading = direction::WEST;
		curAnim = animIndex::LEFT;
		break;
	case direction::WEST:
		heading = direction::EAST;
		curAnim = animIndex::RIGHT;
	}
}


void Enemy::randomHeading(Tile* tilemap[33][15])
{
	sf::Vector2i t = getTilePosition();
	if (heading == direction::NORTH || heading == direction::SOUTH)
	{
		if (rand() % 2 == 0)
		{
			if (t.x > 1 &&
				tilemap[t.x - 1][t.y]->getType() == tileType::AIR)
			{
				heading = direction::WEST;
				curAnim = animIndex::LEFT;
			}
		}
		else
		{
			if (t.x < 31 &&
				tilemap[t.x + 1][t.y]->getType() == tileType::AIR)
			{
				heading = direction::EAST;
				curAnim = animIndex::RIGHT;
			}
		}
	}
	else
	{
		if (rand() % 2 == 0)
		{
			if (t.y > 1 &&
				tilemap[t.x][t.y - 1]->getType() == tileType::AIR)
				heading = direction::NORTH;
		}
		else
		{
			if (t.y < 13 &&
				tilemap[t.x][t.y + 1]->getType() == tileType::AIR)
				heading = direction::SOUTH;
		}
	}
}


bool Enemy::atTile(Tile* tilemap[33][15])
{
	sf::Vector2i t = getTilePosition();
	bool at = false;

	if (((heading == direction::NORTH || heading == direction::SOUTH) &&
		abs(sprite.getPosition().y -
			tilemap[t.x][t.y]->getPosition().y) < clippingMargin &&
		sprite.getPosition().y >= tilemap[t.x][t.y]->getPosition().y) ||
		((heading == direction::EAST || heading == direction::WEST) &&
			abs(sprite.getPosition().x -
				tilemap[t.x][t.y]->getPosition().x) < clippingMargin &&
			sprite.getPosition().x >= tilemap[t.x][t.y]->getPosition().x))
		at = true;
	return at;
}


void Enemy::draw(sf::RenderWindow& w) const
{
	w.draw(sprite);
}


void Enemy::die()
{
	alive = false;
	curAnim = animIndex::DEATH;
}


bool Enemy::isAlive() const
{
	return alive;
}

sf::Vector2f Enemy::getPosition() const
{
	return sprite.getPosition();
}


sf::Vector2i Enemy::getTilePosition() const
{
	//Shift by one to adjust for border
	return sf::Vector2i(sprite.getPosition().x / 48 + 1,
		(sprite.getPosition().y - 100) / 48 + 1);
}


Enemy::~Enemy()
{
}