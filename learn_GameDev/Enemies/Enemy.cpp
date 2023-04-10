#include "Enemy.h"


Enemy::Enemy(const Player* plrPtr)
{
	//Default values
	heading = direction::NORTH;
	curAnim = animIndex::RIGHT;
	anims[animIndex::DEATH].showOnce();
	moveSpeed = 1.f;
	clippingMargin = 1.f;
	alive = true;
	dead = false;
	playerRef = plrPtr;
}


void Enemy::update(const float& dt)
{
	anims[int(curAnim)].update(dt);
	anims[int(curAnim)].applyToSprite(sprite);

	if (alive)
	{
		sf::FloatRect enemyBounds = sprite.getGlobalBounds();
		enemyBounds.height /= 1.1;
		Collidable::updateRect(enemyBounds);
	}

	if (curAnim == animIndex::DEATH &&
		anims[curAnim].getCurrentFrame() == anims[curAnim].getFrameCount() - 1)
		dead = true;
}


bool Enemy::moveForward(Tile* tilemap[33][15])
{
	sf::Vector2i t = getTilePosition();
	bool moved = false; //Whether or not any movement occured this call
	switch (heading)
	{
	case direction::NORTH:
		//If the tile position is on the map and the sprite is
		//below the top bound and the northern tile is air, move
		if (t.y >= 0 && sprite.getPosition().y >= 100 &&
			tilemap[t.x][t.y]->getType() == tileType::AIR)
		{
			sprite.move(0, -moveSpeed);
			moved = true;
		}
		break;
	case direction::SOUTH:
		//If the tile position is on the map and the sprite is
		//above the bottom bound and the southern tile is air, move
		if (t.y < 14 && sprite.getPosition().y < 48 * 12 + 100 &&
			tilemap[t.x][t.y + 1]->getType() == tileType::AIR)
		{
			sprite.move(0, moveSpeed);
			moved = true;
		}
		break;
	case direction::EAST:
		//If the tile position is on the map and the sprite is
		//left of the right bound and the eastern tile is air, move
		if (t.x >= 0 && sprite.getPosition().x < 48 * 30 &&
			tilemap[t.x + 1][t.y]->getType() == tileType::AIR)
		{
			sprite.move(moveSpeed, 0);
			moved = true;
		}
		break;
	case direction::WEST:
		//If the tile position is on the map and the sprite is
		//right of the left bound and the western tile is air, move
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
	//Maintain animation direction when changing to north/south
	case direction::NORTH:
		heading = direction::SOUTH;
		break;
	case direction::SOUTH:
		heading = direction::NORTH;
		break;
	case direction::EAST:
		heading = direction::WEST;
		curAnim = animIndex::LEFT; //Adjust animation to face left
		break;
	case direction::WEST:
		heading = direction::EAST;
		curAnim = animIndex::RIGHT; //Adjust animation to face right
	}
}


void Enemy::randomHeading(Tile* tilemap[33][15])
{
	sf::Vector2i t = getTilePosition();
	if (heading == direction::NORTH || heading == direction::SOUTH)
	{
		if (rand() % 2 == 0)
		{
			//If not on the west wall and the western tile is air
			if (t.x > 1 &&
				tilemap[t.x - 1][t.y]->getType() == tileType::AIR)
			{
				heading = direction::WEST;
				curAnim = animIndex::LEFT;
			}
		}
		else
		{
			//If not on the east wall and the eastern tile is air
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
			//If not on the north wall and the northern tile is air
			if (t.y > 1 &&
				tilemap[t.x][t.y - 1]->getType() == tileType::AIR)
				heading = direction::NORTH;
		}
		else
		{
			//If not on the south wall and the southern tile is air
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

	/*
	FOR VERTICAL HEADINGS
		Vertical distance from sprite to tile must be less than clipping margin
		Vertical position must be greater than tile position
	FOR HORIZONTAL HEADINGS
		Horizontal distance from sprite to tile must be less than clipping margin
		Horziontal position must be greater than tile positon
	*/
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

	//Prevent collision with dead enemies
	Collidable::updateRect(sf::FloatRect(0, 0, 0, 0));
}


bool Enemy::isAlive() const
{
	return alive;
}


bool Enemy::completedDeathAnim() const
{
	return dead;
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