#include "Enemy.h"


Enemy::Enemy(const Player* plrPtr)
{
	heading = directions::NORTH;
	curAnim = animIndex::RIGHT;
	moveSpeed = 0.f;
	atTile = true;
	alive = true;
	playerPointer = plrPtr;
}


void Enemy::update(const float& dt)
{
	anims[int(curAnim)].update(dt);
	anims[int(curAnim)].applyToSprite(sprite);
}


void Enemy::moveForward(Tile* tilemap[33][15])
{
	sf::Vector2i tilePos = getTilePosition();
	switch (heading)
	{
	case directions::NORTH:
		if (tilePos.y >= 0 && sprite.getPosition().y >= 100 &&
			tilemap[tilePos.x][tilePos.y]->getType() == tileType::AIR)
			sprite.move(0, -moveSpeed);
		break;
	case directions::SOUTH:
		if (tilePos.y < 14 && sprite.getPosition().y < 48 * 12 + 100 &&
			tilemap[tilePos.x][tilePos.y + 1]->getType() == tileType::AIR)
			sprite.move(0, moveSpeed);
		break;
	case directions::EAST:
		if (tilePos.x >= 0 && sprite.getPosition().x < 48 * 30 &&
			tilemap[tilePos.x + 1][tilePos.y]->getType() == tileType::AIR)
			sprite.move(moveSpeed, 0);
		break;
	case directions::WEST:
		if (tilePos.x < 32 && sprite.getPosition().x >= 0 &&
			tilemap[tilePos.x][tilePos.y]->getType() == tileType::AIR)
			sprite.move(-moveSpeed, 0);
	}
}


void Enemy::moveForwardAndBounce(Tile* tilemap[33][15])
{
	sf::Vector2i tilePos = getTilePosition();
	switch (heading)
	{
	case directions::NORTH:
		if (tilePos.y >= 0 && sprite.getPosition().y >= 100 &&
			tilemap[tilePos.x][tilePos.y]->getType() == tileType::AIR)
			sprite.move(0, -moveSpeed);
		else
			heading = directions::SOUTH;
		break;
	case directions::SOUTH:
		if (tilePos.y < 14 && sprite.getPosition().y < 48 * 12 + 100 &&
			tilemap[tilePos.x][tilePos.y + 1]->getType() == tileType::AIR)
			sprite.move(0, moveSpeed);
		else
			heading = directions::NORTH;
		break;
	case directions::EAST:
		if (tilePos.x >= 0 && sprite.getPosition().x < 48 * 30 &&
			tilemap[tilePos.x + 1][tilePos.y]->getType() == tileType::AIR)
			sprite.move(moveSpeed, 0);
		else
		{
			heading = directions::WEST;
			curAnim = animIndex::LEFT;
		}
		break;
	case directions::WEST:
		if (tilePos.x < 32 && sprite.getPosition().x >= 0 &&
			tilemap[tilePos.x][tilePos.y]->getType() == tileType::AIR)
			sprite.move(-moveSpeed, 0);
		else
		{
			heading = directions::EAST;
			curAnim = animIndex::RIGHT;
		}
	}
}


void Enemy::changeHeadingRandomly(Tile* tilemap[33][15])
{
	sf::Vector2i t = getTilePosition();
	if (heading == directions::NORTH || heading == directions::SOUTH)
	{
		if (rand() % 2 == 0)
		{
			if (t.x > 1 &&
				tilemap[t.x - 1][t.y]->getType() == tileType::AIR)
			{
				heading = directions::WEST;
				curAnim = animIndex::LEFT;
			}
		}
		else
		{
			if (t.x < 31 &&
				tilemap[t.x + 1][t.y]->getType() == tileType::AIR)
			{
				heading = directions::EAST;
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
				heading = directions::NORTH;
		}
		else
		{
			if (t.y < 13 &&
				tilemap[t.x][t.y + 1]->getType() == tileType::AIR)
				heading = directions::SOUTH;
		}
	}
}


//Updates the atTile data member and returns its new value
bool Enemy::isAtTile(Tile* tilemap[33][15])
{
	sf::Vector2i tilePos = getTilePosition();
	atTile = false;
	if (((heading == directions::NORTH || heading == directions::SOUTH) &&
		abs(sprite.getPosition().y -
			tilemap[tilePos.x][tilePos.y]->getPosition().y) <
		clippingMargin() && sprite.getPosition().y >=
		tilemap[tilePos.x][tilePos.y]->getPosition().y) ||
		((heading == directions::EAST || heading == directions::WEST) &&
			abs(sprite.getPosition().x -
				tilemap[tilePos.x][tilePos.y]->getPosition().x) <
			clippingMargin() && sprite.getPosition().x >=
			tilemap[tilePos.x][tilePos.y]->getPosition().x))
		atTile = true;
	return atTile;
}


//Returns true if isAtTile returns true and
//the current tile position is the target tile
bool Enemy::atTargetTile(Tile* tilemap[33][15])
{
	bool at = false;
	if (isAtTile(tilemap) && getTilePosition() == targetTile)
		at = true;
	return at;
}


//Amount the enemy can clip into walls
//Larger margins result in more leniency within moveent system
double Enemy::clippingMargin() const
{
	return 1.;
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