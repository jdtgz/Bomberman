#include "Enemy.h"


Enemy::Enemy()
{
	heading = directions::NORTH;
	curAnim = animIndex::RIGHT;
	moveSpeed = 0.f;
	alive = true;
	tilePos = sf::Vector2i(0, 0);
}


void Enemy::update(const float& dt)
{
	anims[int(curAnim)].update(dt);
	anims[int(curAnim)].applyToSprite(sprite);
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


double Enemy::getClippingMargin() const
{
	return 1.;
}


int Enemy::getMovementChance() const
{
	return 50; // Default 50%
}


void Enemy::standardMovement(Tile* tilemap[33][15],
	const sf::Vector2i& mapSize)
{
	//Update current tile position
	tilePos = sf::Vector2i(sprite.getPosition().x / 48,
		(sprite.getPosition().y - 100) / 48);

	debounce++;

	//Update current position or change heading
	switch (heading)
	{
	case directions::NORTH:
		if (tilePos.y >= 0 && sprite.getPosition().y >= 100 &&
			tilemap[tilePos.x + 1][tilePos.y + 1]->getType() == tileType::AIR)
			sprite.move(0, -moveSpeed);
		else
			heading = directions::SOUTH;
		break;
	case directions::SOUTH:
		if (tilePos.y < mapSize.y - 2 && sprite.getPosition().y < 48 * 12 + 100 &&
			tilemap[tilePos.x + 1][tilePos.y + 2]->getType() == tileType::AIR)
			sprite.move(0, moveSpeed);
		else
			heading = directions::NORTH;
		break;
	case directions::EAST:
		if (tilePos.x >= 0 && sprite.getPosition().x < 48 * 30 &&
			tilemap[tilePos.x + 2][tilePos.y + 1]->getType() == tileType::AIR)
			sprite.move(moveSpeed, 0);
		else
		{
			heading = directions::WEST;
			curAnim = animIndex::LEFT;
		}
		break;
	case directions::WEST:
		if (tilePos.x < mapSize.x - 1 && sprite.getPosition().x >= 0 &&
			tilemap[tilePos.x + 1][tilePos.y + 1]->getType() == tileType::AIR)
			sprite.move(-moveSpeed, 0);
		else
		{
			heading = directions::EAST;
			curAnim = animIndex::RIGHT;
		}
	}

	//Change direction
	if (rand() % 100 < getMovementChance() && debounce >= DEBOUNCE_MAX)
	{
		if ((heading == directions::NORTH || heading == directions::SOUTH) &&
			abs(sprite.getPosition().y -
				tilemap[tilePos.x + 1][tilePos.y + 1]->getPosition().y) <
			getClippingMargin() && sprite.getPosition().y >=
			tilemap[tilePos.x + 1][tilePos.y + 1]->getPosition().y)
		{
			//Go West
			if (rand() % 2)
			{
				if (tilePos.x > 1 &&
					tilemap[tilePos.x][tilePos.y + 1]->getType() == tileType::AIR)
				{
					heading = directions::WEST;
					debounce = 0;
				}
			}
			//Go East
			else
			{
				if (tilePos.x < mapSize.x - 2 &&
					tilemap[tilePos.x + 2][tilePos.y + 1]->getType() == tileType::AIR)
				{
					heading = directions::EAST;
					debounce = 0;
				}
			}
		}
		else if ((heading == directions::EAST || heading == directions::WEST) &&
			abs(sprite.getPosition().x -
				tilemap[tilePos.x + 1][tilePos.y + 1]->getPosition().x) <
			getClippingMargin() && sprite.getPosition().x >=
			tilemap[tilePos.x + 1][tilePos.y + 1]->getPosition().x)
		{
			//Go North
			if (rand() % 2)
			{
				if (tilePos.y > 1 &&
					tilemap[tilePos.x + 1][tilePos.y]->getType() == tileType::AIR)
				{
					heading = directions::NORTH;
					debounce = 0;
				}
			}
			//Go South
			else
			{
				if (tilePos.y < mapSize.y - 2 &&
					tilemap[tilePos.x + 1][tilePos.y + 2]->getType() == tileType::AIR)
				{
					heading = directions::SOUTH;
					debounce = 0;
				}
			}
		}
	}
}


void Enemy::chasePlayerMovement(Tile* tilemap[33][15],
	const sf::Vector2i& mapSize, const Player* plrPtr)
{
	//Player tile position
	sf::Vector2i pTilePos(plrPtr->getPosition().x,
		plrPtr->getPosition().y);

	//Enemy tile position
	sf::Vector2i pos(tilePos.x, tilePos.y);
}


Enemy::~Enemy()
{
}