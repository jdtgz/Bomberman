#include "Enemy.h"


Enemy::Enemy(const Player* plrPtr)
{
	//Default enemy values
	heading = direction::NORTH;
	curAnim = animIndex::RIGHT;
	anims[animIndex::DEATH].showOnce();
	moveSpeed = 1.f;
	clippingMargin = 1.f;
	pathfindingDebounce = PATHFINDING_DEBOUNCE_MAX;
	alive = true;
	deathEnded = false;
	playerRef = plrPtr;
}


void Enemy::update(const float& dt)
{
	anims[int(curAnim)].update(dt);
	anims[int(curAnim)].applyToSprite(sprite);

	if (alive)
	{
		Collidable::updateRect(getBoundingBox());
	}

	if (curAnim == animIndex::DEATH &&
		anims[curAnim].getCurrentFrame() == anims[curAnim].getFrameCount() - 1)
	{
		deathEnded = true;
	}
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
	heading = (direction)((heading + 2) % 4);

	if (heading == direction::WEST)
		curAnim = animIndex::LEFT; //Adjust animation to face left
	else if (heading == direction::EAST)
		curAnim = animIndex::RIGHT; //Adjust animation to face right
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
	{
		at = true;
	}

	return at;
}


void Enemy::draw(sf::RenderWindow& w) const
{
	w.draw(sprite);

	if (DEBUG)
	{
		//Display hitbox
		sf::RectangleShape box;
		box.setPosition(getBoundingBox().left, getBoundingBox().top);
		box.setSize(sf::Vector2f(getBoundingBox().width, getBoundingBox().height));
		box.setFillColor(sf::Color(255, 0, 0, 100));
		w.draw(box);
	}
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
	return deathEnded;
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


sf::FloatRect Enemy::getBoundingBox() const
{
	sf::FloatRect alteredBox = sprite.getGlobalBounds();
	alteredBox.left += 1.5 + moveSpeed;
	alteredBox.top += 1.5 + moveSpeed;
	alteredBox.width -= 3 + 2 * moveSpeed;
	alteredBox.height -= 3 + 2 * moveSpeed;
	return alteredBox;
}


bool Enemy::pathfindingHeading(Tile* tilemap[33][15])
{
	bool pathToFollow = false;

	//Once every number of calls, update the path
	if (++pathfindingDebounce > PATHFINDING_DEBOUNCE_MAX)
	{
		pathfindingDebounce = 0;
		path = pathfind(tilemap);
	}

	if (path.size() > 0)
	{
		//Get the next path
		sf::Vector2i next = path.at(path.size() - 1);
		sf::Vector2i tPos = getTilePosition();

		//If at the next tile, then go to the next tile
		if (atTile(tilemap) && tPos == next)
		{
			path.pop_back();
		}

		if (path.size() > 0)
		{
			next = path.at(path.size() - 1);
			if (tPos.x - 1 == next.x && (heading % 2 == 1 || atTile(tilemap)))
			{
				heading = direction::WEST;
				curAnim = animIndex::LEFT;
				pathToFollow = true;
			}
			else if (tPos.x + 1 == next.x && (heading % 2 == 1 || atTile(tilemap)))
			{
				heading = direction::EAST;
				curAnim = animIndex::RIGHT;
				pathToFollow = true;
			}
			else if (tPos.y - 1 == next.y && (heading % 2 == 0 || atTile(tilemap)))
			{
				heading = direction::NORTH;
				pathToFollow = true;
			}
			else if (tPos.y + 1 == next.y && (heading % 2 == 0 || atTile(tilemap)))
			{
				heading = direction::SOUTH;
				pathToFollow = true;
			}
		}
	}

	return pathToFollow;
}


std::vector<sf::Vector2i> Enemy::pathfind(Tile* tilemap[33][15])
{
	const sf::Vector2i start = getTilePosition(), end = playerRef->getTilePosition();
	std::vector<sf::Vector3i> open, closed;
	sf::Vector2i current, offset;
	int steps = 0;

	//Add start to the open list
	open.push_back({ start.x, start.y, steps });

	while (open.size() > 0 && current != end)
	{
		//Get the first item in the vector
		current = { open.at(0).x, open.at(0).y };

		//Move current to closed list
		open.erase(open.begin());
		closed.push_back({ current.x, current.y, steps });

		steps++;

		//for each direction
		for (int i = 0; i < 4; i++)
		{
			//Get an offset of one tile in that direction
			switch (i)
			{
			case direction::NORTH:
				offset = { 0, -1 };
				break;
			case direction::EAST:
				offset = { 1, 0 };
				break;
			case direction::SOUTH:
				offset = { 0, 1 };
				break;
			case direction::WEST:
				offset = { -1,0 };
			}

			//Check for a tile in that direction
			if (current.x > 0 && current.x < 32 && current.y > 0 && current.y < 14 &&
				tilemap[(current + offset).x][(current + offset).y]->getType() == tileType::AIR)
			{
				//Determine if the tile has already been found by the enemy
				int iterator = 0;
				while (iterator < closed.size() &&
					!(closed.at(iterator).x == (current + offset).x &&
						closed.at(iterator).y == (current + offset).y))
					iterator++;
				//If it has not already been found, then add it
				if (iterator == closed.size())
					open.push_back({ (current + offset).x, (current + offset).y, steps });
				//If it has been found but this path is faster, update with the faster path
				else if (closed.at(iterator).z > steps)
					closed.at(iterator).z = steps;
			}
		}
	}

	std::vector<sf::Vector2i> foundPath = {};

	//Reconstruct path if the end was found
	if (current == end)
	{
		while (current != start)
		{
			foundPath.push_back(current);

			sf::Vector3i shortest = { -1,-1,-1 };

			//for each direction
			for (int i = 0; i < 4; i++)
			{
				//Get an offset of one tile in that direction
				switch (i)
				{
				case direction::NORTH:
					offset = { 0, -1 };
					break;
				case direction::EAST:
					offset = { 1, 0 };
					break;
				case direction::SOUTH:
					offset = { 0, 1 };
					break;
				case direction::WEST:
					offset = { -1,0 };
				}

				for (int c = 0; c < closed.size(); c++)
				{
					if (closed.at(c).x == current.x + offset.x && closed.at(c).y == current.y + offset.y)
					{
						if (shortest.z == -1 || shortest.z > closed.at(c).z)
							shortest = closed.at(c);
					}
				}
			}

			current = { shortest.x, shortest.y };
		}
	}

	return foundPath;
}


Enemy::~Enemy()
{
}