#include "Enemy.h"


Enemy::Enemy(const Player* plrPtr, const enemyType& t)
{
	init(plrPtr, t, { 1, 1 }, direction::NORTH);
}


Enemy::Enemy(const Player* plrPtr, const enemyType& t,
	const sf::Vector2i& tPos)
{
	init(plrPtr, t, tPos, direction::NORTH);
}


Enemy::Enemy(const Player* plrPtr, const enemyType& t,
	const sf::Vector2i & tPos, const direction& d)
{
	init(plrPtr, t, tPos, d);
}


Enemy::~Enemy()
{
}


void Enemy::init(const Player* plrPtr, const enemyType& typ,
	const sf::Vector2i& tPos, const direction& dir)
{
	setHeading(dir);
	type = typ;
	sf::Texture* t = &TextureHolder::get(textures::ENEMIES);
	anims[int(animIndex::RIGHT)].setUp(*t, 0, 16 * (typ * 3), 16, 16, 3);
	anims[int(animIndex::LEFT)].setUp(*t, 0, 16 *
		(typ == enemyType::PONTAN ? typ * 3 : typ * 3 + 1),
		16, 16, 3);
	anims[int(animIndex::DEATH)].setUp(*t, 0, 16 *
		(typ == enemyType::PONTAN ? typ * 3 + 1 : typ * 3 + 2),
		16, 16, 5);
	anims[animIndex::DEATH].showOnce();
	anims[int(curAnim)].applyToSprite(sprite);
	alive = true;
	deathEnded = false;
	wallpass = false;
	chasePlayer = false;
	playerRef = plrPtr;
	sprite.setPosition(48 * (tPos.x - 1), 100 + 48 * (tPos.y - 1));
	switch (typ)
	{
	case enemyType::VALCOM:
		moveSpeed = 1.f;
		clippingMargin = 0.25f;
		pointValue = 100;
		break;
	case enemyType::ONEAL:
		moveSpeed = 1.5f;
		clippingMargin = 1.25f;
		pointValue = 200;
		break;
	case enemyType::DAHL:
		moveSpeed = 1.75f;
		clippingMargin = 1.5f;
		pointValue = 400;
		break;
	case enemyType::MINVO:
		moveSpeed = 2.25f;
		clippingMargin = 2.f;
		pointValue = 800;
		break;
	case enemyType::OVAPE:
		moveSpeed = 1.25f;
		clippingMargin = 1.f;
		pointValue = 1000;
		wallpass = true;
		break;
	case enemyType::DORIA:
		moveSpeed = 0.8f;
		clippingMargin = 1.f;
		pointValue = 2000;
		wallpass = true;
		break;
	case enemyType::PASS:
		moveSpeed = 2.66f;
		clippingMargin = 2.25f;
		pointValue = 4000;
		break;
	case enemyType::PONTAN:
		moveSpeed = 3.f;
		clippingMargin = 2.5f;
		pointValue = 8000;
		wallpass = true;
	}
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


void Enemy::move(Tile* tilemap[33][15])
{
	switch (type)
	{
	//Aimless movement
	case enemyType::VALCOM:
	case enemyType::OVAPE:
	case enemyType::PONTAN:
		//If no movement occurred (wall in front)
		if (!moveForward(tilemap))
			//Bounce off of the wall
			bounce();

		//If at a tile and the debounce is valid
		if ((++movementDebounce >= (type == enemyType::VALCOM ? 10 : 6) ||
			(type == enemyType::VALCOM && distanceToPlayer() < 5 && movementDebounce >= 5)) &&
			atTile(tilemap))
		{
			//Reset debounce counter
			movementDebounce = 0;

			//Attempt to assign random heading
			randomHeading(tilemap);
		}
		break;
		//Only chase
	case enemyType::DORIA:
		pathfindingHeading(tilemap);
		moveForward(tilemap);
		break;
	//Occassionally chase, otherwise aimless movement
	case enemyType::ONEAL:
	case enemyType::DAHL:
	case enemyType::MINVO:
	case enemyType::PASS:
		bool pf = false;

		//If chasing player, then set the heading based on pathfinding
		if (chasePlayer)
			pf = pathfindingHeading(tilemap);
		//If distance between the player and enemy is large enough
		//then 10% chance to start chasing the player
		else if (distanceToPlayer() >
			(type == enemyType::MINVO ? 3 : 5)
			&& rand() % 10 <
				(type == enemyType::MINVO ? 7 : 4))
			chasePlayer = true;


		//If not moving forward (hitting wall)
		if (!moveForward(tilemap) && !pf)
		{
			//Bounce off of the wall
			bounce();

			//Stop chasing the player
			chasePlayer = false;
		}

		//If at a tile and the debounce is valid and not pathfinding
		if (!pf && atTile(tilemap) && ++movementDebounce >=
			(type == enemyType::MINVO ? 3 : 5))
		{
			//Reset debounce counter
			movementDebounce = 0;

			//Attempt to assign random heading
			randomHeading(tilemap);
		}
	}
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


int Enemy::getPointValue() const
{
	return pointValue;
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


//Move forward based on the current heading
bool Enemy::moveForward(Tile* tilemap[33][15])
{
	sf::Vector2i t = getTilePosition();
	bool moved = false; //Whether or not any movement occured this call
	switch (heading)
	{
	case direction::NORTH:
		//If the tile position is on the map and the sprite is
		//below the top bound and the northern tile is air, move
		if (t.y >= 0 && sprite.getPosition().y >= 100 && walkableTile(tilemap, t))
		{
			sprite.move(0, -moveSpeed);
			moved = true;
		}
		break;
	case direction::SOUTH:
		//If the tile position is on the map and the sprite is
		//above the bottom bound and the southern tile is air, move
		if (t.y < 14 && sprite.getPosition().y < 48 * 12 + 100 && walkableTile(tilemap, { t.x, t.y + 1 }))
		{
			sprite.move(0, moveSpeed);
			moved = true;
		}
		break;
	case direction::EAST:
		//If the tile position is on the map and the sprite is
		//left of the right bound and the eastern tile is air, move
		if (t.x >= 0 && sprite.getPosition().x < 48 * 30 && walkableTile(tilemap, { t.x + 1, t.y }))
		{
			sprite.move(moveSpeed, 0);
			moved = true;
		}
		break;
	case direction::WEST:
		//If the tile position is on the map and the sprite is
		//right of the left bound and the western tile is air, move
		if (t.x < 32 && sprite.getPosition().x >= 0 && walkableTile(tilemap, t))
		{
			sprite.move(-moveSpeed, 0);
			moved = true;
		}
	}
	return moved;
}


//Change heading so the enemy moves 'backwards'
void Enemy::bounce()
{
	setHeading((direction)((heading + 2) % 4));
}


//Randomly assign a heading if certain conditions are met
void Enemy::randomHeading(Tile* tilemap[33][15])
{
	sf::Vector2i t = getTilePosition();
	if (heading == direction::NORTH || heading == direction::SOUTH)
	{
		if (rand() % 2 == 0)
		{
			//If not on the west wall and the western tile is air
			if (t.x > 1 && walkableTile(tilemap, { t.x - 1, t.y }))
			{
				setHeading(direction::WEST);
			}
		}
		else
		{
			//If not on the east wall and the eastern tile is air
			if (t.x < 31 && walkableTile(tilemap, { t.x + 1, t.y }))
			{
				setHeading(direction::EAST);
			}
		}
	}
	else
	{
		if (rand() % 2 == 0)
		{
			//If not on the north wall and the northern tile is air
			if (t.y > 1 && walkableTile(tilemap, { t.x, t.y - 1 }))
				setHeading(direction::NORTH);
		}
		else
		{
			//If not on the south wall and the southern tile is air
			if (t.y < 13 && walkableTile(tilemap, { t.x, t.y + 1 }))
				setHeading(direction::SOUTH);
		}
	}
}


//Returns whether the enemy is close enough to a tile to be considered 'at' it
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


void Enemy::setHeading(const direction& d)
{
	heading = d;

	if (d == direction::WEST)
		curAnim = animIndex::LEFT; //Adjust animation to face left
	else if (d == direction::EAST)
		curAnim = animIndex::RIGHT; //Adjust animation to face right
}


//Tell the enemy what the path to follow is when pathfinding
bool Enemy::pathfindingHeading(Tile* tilemap[33][15])
{
	bool pathToFollow = false;

	//Once every number of calls, update the path
	if (++pathfindingDebounce > 300 || (path.size() > 0 && getTilePosition() == path.at(0)))
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
			if (heading % 2 == 1 || atTile(tilemap))
			{
				if (tPos.x - 1 == next.x)
				{
					setHeading(direction::WEST);
					pathToFollow = true;
				}
				else if (tPos.x + 1 == next.x)
				{
					setHeading(direction::EAST);
					pathToFollow = true;
				}
			}
			else if (heading % 2 == 0 || atTile(tilemap))
			{
				if (tPos.y - 1 == next.y)
				{
					setHeading(direction::NORTH);
					pathToFollow = true;
				}
				else if (tPos.y + 1 == next.y)
				{
					setHeading(direction::SOUTH);
					pathToFollow = true;
				}
			}
		}
	}

	return pathToFollow;
}


//Generate a path between this enemy and the player
std::vector<sf::Vector2i> Enemy::pathfind(Tile* tilemap[33][15])
{
	if (DEBUG)
		std::cout << "CALLING PATHFIND\n";

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
				walkableTile(tilemap, current + offset))
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


float Enemy::distanceToPlayer() const
{
	return sqrt(pow(getTilePosition().x - playerRef->getTilePosition().x, 2) +
		pow(getTilePosition().y - playerRef->getTilePosition().y, 2));
}


bool Enemy::walkableTile(Tile* tilemap[33][15], const sf::Vector2i& t)
{
	bool walkable = false;
	if (tilemap[t.x][t.y]->getType() == tileType::AIR ||
		tilemap[t.x][t.y]->getType() == tileType::DOOR_OPEN ||
		tilemap[t.x][t.y]->getType() == tileType::POWERUP_REVEALED ||
		(wallpass &&
			(tilemap[t.x][t.y]->getType() == tileType::BRICK ||
				tilemap[t.x][t.y]->getType() == tileType::DOOR_CLOSED ||
				tilemap[t.x][t.y]->getType() == tileType::POWERUP_HIDDEN)))
	{
		walkable = true;
	}
	return walkable;
}