#include "Level.h"
#include "../Enemies/Enemy.h"
#include <math.h>


Level::Level()
{
	int xPos = -48, yPos = 52;

	datamap.resize(MAP_LENGTH);
	for (auto& x : datamap)
		x.resize(MAP_HEIGHT);

	// Generate Solid Tiles
	for (int x = 0; x < MAP_LENGTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			if ((x == 1 || y == 1 || x == MAP_LENGTH - 2 || y == MAP_HEIGHT - 2 ||
				x % 2 != 0 || y % 2 != 0) && (x > 0 && y > 0 && x < MAP_LENGTH - 1 && y < MAP_HEIGHT - 1))
			{
				tilemap[x][y] = new Tile(xPos, yPos, tileType::AIR);
				datamap[x][y] = tileType::AIR;
			}
			else
			{
				tilemap[x][y] = new Tile(xPos, yPos, tileType::TILE);
				datamap[x][y] = tileType::TILE;
			}
			yPos += 48;
		}
		xPos += 48;
		yPos = 52;
	}

	scoreboardPtr = nullptr;

	levelCompleteBuffer.loadFromFile("Sound/Level Complete.wav");
	levelCompleteSound.setBuffer(levelCompleteBuffer);

	powerupPickupBuffer.loadFromFile("Sound/Powerup Pickup.wav");
	powerupPickupSound.setBuffer(powerupPickupBuffer);
}


Level::~Level()
{
	for (int x = 0; x < MAP_LENGTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
			delete tilemap[x][y];

	for (int i = 0; i < enemies.size(); i++)
		delete enemies[i];
}


// Creates a new level, called on player death & game start
void Level::generate(const int& levelNum, const Player* plrPtr)
{
	int i = 0;
	// Used for random positions for PowerUp and Door
	int totalBrickCount = 0, targetBrick = 0;

	// Used for random enemy Placement
	int totalAirCount = 0, targetAir = 0, enemyCount = 0;

	//Removeany lefover powerups
	delete tilemap[powerUp_pos.x][powerUp_pos.y];
	tilemap[powerUp_pos.x][powerUp_pos.y] =
		new Tile((powerUp_pos.x - 1) * 48,
			(powerUp_pos.y - 1) * 48 + 100,
			tileType::AIR);


	for (int x = 0; x < MAP_LENGTH - 1; x++)
	{
		for (int y = 0; y < MAP_HEIGHT - 1; y++)
		{
			//Ignore Tiles and the Top Left Corner
			if (datamap[x][y] != tileType::TILE &&
				x + y - 2 > 1 &&
				x >= 1 && y >= 1)
			{
				datamap[x][y] = tileType::AIR;
				tilemap[x][y]->setTile(tileType::AIR);
				totalAirCount++;

				if (rand() % 4 == 1)
				{
					totalAirCount--;
					totalBrickCount++;
					datamap[x][y] = tileType::BRICK;
					tilemap[x][y]->setTile(tileType::BRICK);
				}
			}
		}
	}

	//Add Powerup to the Map
	targetBrick = rand() % totalBrickCount + 1; //Pick random brick tile
	i = 0;
	for (int x = 0; x < MAP_LENGTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			if (datamap[x][y] == tileType::BRICK)
			{
				i++;
				if (targetBrick == i)
				{
					setPowerup(x, y);
					totalBrickCount--;
				}
			}
		}
	}

	//Add Door to the Map
	targetBrick = rand() % totalBrickCount + 1;
	i = 0;
	for (int x = 0; x < MAP_LENGTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			if (datamap[x][y] == tileType::BRICK)
			{
				i++;
				if (targetBrick == i)
				{
					if (DEBUG)
						std::cout << "DOOR: " << x << ", " << y << '\n';

					datamap[x][y] = tileType::DOOR_CLOSED;
					tilemap[x][y]->setTile(tileType::DOOR_CLOSED);
				}
			}
		}
	}

	for (int i = 0; i < bombs.size(); i++)
		delete bombs.at(i);
	bombs = {};
	for (int i = 0; i < 10; i++)
		bombManager[i] = false;


	for (int i = 0; i < enemies.size(); i++)
		delete enemies[i];
	enemies = {}; //Empty pointer array after deallocating all memory

	loadLevel(levelNum, totalAirCount, plrPtr);

	//Note: Figure out why this needs to be called here
	tilemap[0][0]->setTile(tileType::TILE);

	levelCleared = false;
	outOfTime = false;
	levelCompletePlayed = false;

	scoreboardPtr->setTime(201);
}


//Loads the enemy types from a file
void Level::loadLevel(int levelNum, int totalAirCount, const Player* plrPtr)
{
	int targetAir = 0, enemyCount = 0, i = 0, tempRand = 0; // Used for random enemy Placement
	int lineNum = 0;
	std::vector<int> enemyOddList = {};
	std::ifstream fileHandle;

	fileHandle.open("LevelData.txt");

	enemyOddList.resize(enemyType::PONTAN + 1);

	//Take the string of numbers and stor them in the enemy ID array
	if (fileHandle.is_open())
	{
		std::string line;

		//Go down untill Line matches Level number

		while (std::getline(fileHandle, line) && lineNum < levelNum)
		{
			std::istringstream ss(line);
			ss >> enemyOddList[enemyType::VALCOM] >> enemyOddList[enemyType::ONEAL] >>
				enemyOddList[enemyType::DAHL] >> enemyOddList[enemyType::MINVO] >>
				enemyOddList[enemyType::DORIA] >> enemyOddList[enemyType::OVAPE] >>
				enemyOddList[enemyType::PASS] >> enemyOddList[enemyType::PONTAN];
			lineNum++;
		}

		fileHandle.close();
	}

	while (enemyCount < 6)
	{
		i = 0;
		targetAir = rand() % totalAirCount + 1;
		tempRand = rand() % 100; //random number 0 - 99
		for (int x = 0; x < MAP_LENGTH - 1; x++)
		{
			for (int y = 0; y < MAP_HEIGHT - 1; y++)
			{
				if (datamap[x][y] == tileType::AIR && (x + y) > 1)
				{
					/* Make enemies not spawn right next to the player */
					if (x > 5 || y > 5)
					{
						i++;
						if (targetAir == i) //At randomly picked air tile
						{

							int eType = enemyType::VALCOM;
							while (tempRand > 0 && eType < 8)
							{
								tempRand -= enemyOddList[eType];
								eType++;
							}

							//An enemy type was randomly chosen
							if (tempRand <= 0)
							{
								enemies.push_back(new Enemy(plrPtr, (enemyType)(eType - 1), { x, y }));

								//Increment nmber of enemies on screen
								enemyCount++;

								if (DEBUG)
									std::cout << "ENEMY: " << x << ", " << y << '\n';
							}
						}
					}
				}
			}
		}
	}
}


bool Level::isLevelCleared() const
{
	return levelCleared;
}


int Level::getLength() const
{
	return MAP_LENGTH;
}


int Level::getHeight() const
{
	return MAP_HEIGHT;
}


void Level::keyPressed(const sf::Keyboard::Key& key, Player& plr)
{
	switch (key)
	{
	case sf::Keyboard::A:
		for (int i = 0; i < plr.getBombCount(); i++)
		{
			//Prevents the player from putting a bomb on top of a tile that isnt air, like Doors
			if (tilemap[(int)plr.getPosition().x][(int)plr.getPosition().y]->getType() == tileType::ID::AIR)
			{
				if (bombManager[i] == false)
				{
					for (int i = 0; i < bombs.size(); i++)
					{
						sf::Sprite t = plr.getSprite();
						if (bombs[i]->isColliding(t))
						{
							if (DEBUG)
								std::cout << "COLLIDE!\n";
							return;
						}
					}
					bombManager[i] = true;

					if (!plr.hasDetonator())
						bombs.push_back(new Bomb((int)plr.getPosition().x, (int)plr.getPosition().y, plr.getFlameRange(), true));
					else
						bombs.push_back(new Bomb((int)plr.getPosition().x, (int)plr.getPosition().y, plr.getFlameRange(), false));

					break;
				}
			}
		}
		break;
	case sf::Keyboard::B:
		if (plr.hasDetonator() && bombs.size() > 0)
			for (int i = 0; i < 10; i++)
				if (bombManager[i])
				{
					if (!bombs[0]->getExploding())
						bombs[0]->explode();
				}
		break;
	}
}


// draw all parts on the level on the screen
void Level::draw(sf::RenderWindow& window) const
{
	for (int x = 0; x < MAP_LENGTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
			tilemap[x][y]->draw(window);

	for (int i = 0; i < enemies.size(); i++)
		enemies[i]->draw(window);

	for (int i = 0; i < bombs.size(); i++)
		bombs[i]->draw(window, datamap);
}


void Level::setMap(sf::Vector2i pos, int type)
{
	datamap[pos.x][pos.y] = type;
}

void Level::setScoreboardPtr(Scoreboard* ptr)
{
	scoreboardPtr = ptr;
}


//Create a hidden Power-Up at a set x,y cordinate
void Level::setPowerup(const int& x, const int& y)
{
	if (DEBUG)
		std::cout << "POWERUP: " << x << ", " << y << '\n';
	datamap[x][y] = tileType::POWERUP_HIDDEN;
	delete tilemap[x][y];
	tilemap[x][y] = new PowerUp((x - 1) * 48, (y - 1) * 48 + 100);
	powerUp_pos = { x,y };
}


// Detect collisions between player and tile
void Level::collisions(Player& plr)
{
	sf::Vector2f offset;

	// check to see the player's collisions with enemies 
	for (int i = 0; i < enemies.size(); i++)
		if (plr.check(*enemies[i]))
			plr.die();

	//Tilemap collisions
	for (int x = 0; x < MAP_LENGTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			//If the tile is not an air tile,
			if (tilemap[x][y]->getType() != tileType::AIR &&
				//Not solid air that the player is standing on or solid air while the player has bomb pass,
				!(tilemap[x][y]->getType() == tileType::SOLID_AIR
					&& (x == plr.getPosition().x && y == plr.getPosition().y || plr.hasBombPass())) &&
				//Not an open door while there are still enemies
				!(tilemap[x][y]->getType() == tileType::DOOR_OPEN && enemies.size() > 0) &&
				//Not a brick, closed door, or hidden powerup while the player has wall pass
				!((tilemap[x][y]->getType() == tileType::BRICK ||
					tilemap[x][y]->getType() == tileType::DOOR_CLOSED ||
					tilemap[x][y]->getType() == tileType::POWERUP_HIDDEN) &&
					plr.hasWallPass()))
			{
				//Collide
				sf::Vector2f center_tile = {
					tilemap[x][y]->getBounds().left + (tilemap[x][y]->getBounds().width / 2),
					tilemap[x][y]->getBounds().top + (tilemap[x][y]->getBounds().height / 2)
				};
				sf::Vector2f center_other =
				{
					plr.getBounds().left + (plr.getBounds().width / 2),
					plr.getBounds().top + (plr.getBounds().height / 2)
				};

				float distance = sqrt(pow(center_other.x - center_tile.x, 2) +
					pow(center_other.y - center_tile.y, 2));

				if (distance < 48 * 2)
				{
					if (plr.check(*tilemap[x][y], offset))
					{
						switch (tilemap[x][y]->getType())
						{
						case tileType::POWERUP_REVEALED:
							((PowerUp*)tilemap[x][y])->collision(plr);
							powerupPickupSound.play();

							break;
						case tileType::DOOR_OPEN:
							tilemap[x][y]->collision(plr);

							if (enemies.size() == 0)
							{
								levelCleared = true;
								if (!levelCompletePlayed)
								{
									levelCompleteSound.play();
									levelCompletePlayed = true;
								}
							}

							break;
						}
					}
				}
			}
		}
	}

	plr.move(offset.x, offset.y);
}


//Checks to see if a hitbox collided with an exploding bomb
bool Level::deathCheck(std::vector<int> range, sf::Vector2i bombPos, const sf::FloatRect& bounds)
{
	for (int i = 0; i <= range[0]; i++)
	{
		if (bounds.intersects(sf::FloatRect((bombPos.x - 1) * 48, (bombPos.y - i - 1) * 48 + 100, 48, 48)))
			return true;
	}

	for (int i = 0; i <= range[1]; i++)
	{
		if (bounds.intersects(sf::FloatRect((bombPos.x + i - 1) * 48, (bombPos.y - 1) * 48 + 100, 48, 48)))
			return true;
	}

	for (int i = 0; i <= range[2]; i++)
	{
		if (bounds.intersects(sf::FloatRect((bombPos.x - 1) * 48, (bombPos.y + i - 1) * 48 + 100, 48, 48)))
			return true;
	}

	for (int i = 0; i <= range[3]; i++)
	{
		if (bounds.intersects(sf::FloatRect((bombPos.x - i - 1) * 48, (bombPos.y - 1) * 48 + 100, 48, 48)))
			return true;
	}

	return false;
}


// Update TileMap, Bomb and Enemy Status, and Player-Bomb collision checks
void Level::update(const float& dt, Player& plr)
{
	int offset = 1;
	bool collided = false;

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies.at(i)->update(dt);
		if (enemies.at(i)->isAlive())
			enemies.at(i)->move(tilemap);
	}

	//Delete all dead enemies
	for (int i = enemies.size() - 1; i >= 0; i--)
	{
		if (enemies.at(i)->completedDeathAnim())
		{
			Enemy* temp = enemies.at(i);
			enemies.at(i) = enemies.at(enemies.size() - 1);
			enemies.at(enemies.size() - 1) = temp;

			/* Add points to scoreboard */
			scoreboardPtr->setScore(scoreboardPtr->getScore() + temp->getPointValue());

			delete enemies.at(enemies.size() - 1);
			enemies.pop_back();
		}
	}

	// Check for tileType conflicts between datamap and tilemap
	for (int x = 0; x < MAP_LENGTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			if (datamap[x][y] != tilemap[x][y]->getType())
			{
				if (tilemap[x][y]->getType() == tileType::POWERUP_REVEALED)
					datamap[x][y] = tileType::POWERUP_REVEALED;

				tilemap[x][y]->interact();
			}

			// Animation update for brick destroy animation
			tilemap[x][y]->update(dt);
		}
	}

	// Clear bombs
	for (int i = 0; i < 10; i++)
	{
		if (bombManager[i])
		{
			if (bombs.size() > 0)
			{
				if (bombs[0]->getExploded())
				{
					bombManager[i] = false;

					// Destroy the Bricks
					datamap = bombs[0]->datamapExplosionCollision(datamap);

					// Change TileType of the Bomb Location
					tilemap[bombs[0]->getPosition().x][bombs[0]->getPosition().y]->setTile(tileType::AIR);

					// Check if player dies
					if (deathCheck(bombs[0]->getExplodingRange(), bombs[0]->getPosition(), plr.getBoundingBox())
						&& !plr.hasFlamePass())
						plr.die();

					// Check if enemies die
					for (int e = 0; e < enemies.size(); e++)
						if (deathCheck(bombs[0]->getExplodingRange(),
							bombs[0]->getPosition(), enemies.at(e)->getBoundingBox()))
							enemies.at(e)->die();

					delete bombs[0];
					bombs.erase(bombs.begin());
				}
			}
			else
				bombManager[i] = false;
		}
	}

	for (int i = 0; i < bombs.size(); i++)
	{
		bombs[i]->update(dt);
	}

	//Checks the players collisions with bombs
	for (int i = 0; i < bombs.size(); i++)
	{
		Bomb* bomb = bombs.at(i);
		sf::Vector2i position = bomb->getPosition();

		if (tilemap[position.x][position.y]->getType() != tileType::SOLID_AIR)
		{
			if (!bomb->isEntityColliding(plr.getBoundingBox()))
				tilemap[position.x][position.y]->setTile(tileType::SOLID_AIR);
		}
	}

	scoreboardPtr->decrementTime(dt);

	if (scoreboardPtr->getTime() == 0 && !outOfTime)
	{
		outOfTime = true;

		//spawn enemies
	}
}