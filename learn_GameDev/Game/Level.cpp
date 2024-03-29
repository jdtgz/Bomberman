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
			//On the outside border of the playable map
			bool topLeftEdge = (x == 1 || y == 1);
			bool bottomRightEdge = (x == MAP_LENGTH - 2 || y == MAP_HEIGHT - 2);

			//Is on an alternating line
			bool gridPattern = (x % 2 != 0 || y % 2 != 0);

			//Is within the map boundary
			bool inBounds = (x > 0 && y > 0 && x < MAP_LENGTH - 1 && y < MAP_HEIGHT - 1);

			if ((topLeftEdge || bottomRightEdge || gridPattern) && inBounds)
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

	popupFont.loadFromFile("Textures/font.TTF");
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

					//Set to a "bomb" tile type - Player can walk through but enemy cannot
					if (!plr.hasDetonator())
						bombs.push_back(new Bomb((int)plr.getPosition().x, (int)plr.getPosition().y, plr.getFlameRange(), true));
					else
						bombs.push_back(new Bomb((int)plr.getPosition().x, (int)plr.getPosition().y, plr.getFlameRange(), false));

					//Set the tile type to solid air
					tilemap[(int)plr.getPosition().x][(int)plr.getPosition().y]->setTile(tileType::SOLID_AIR);

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

	for (int i = 0; i < textPopups.size(); i++)
		window.draw(textPopups.at(i));
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
			if ((tilemap[x][y]->getType() != tileType::AIR && tilemap[x][y]->getType() != tileType::SOLID_AIR) &&
				//Not solid air that the player is standing on or solid air while the player has bomb pass,
				!(tilemap[x][y]->getType() == tileType::BOMB
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

				if (sqrt(pow(center_other.x - center_tile.x, 2) +
					pow(center_other.y - center_tile.y, 2)) < 48 * 2)
				{
					/* Get the sprites global bounds */
					const sf::FloatRect& sprite_bounds = plr.getSprite().getGlobalBounds();
					/* Get tile position by using the center of the 
					player sprite instead of using the origin */
					sf::Vector2f center_sprite;
					center_sprite.x = sprite_bounds.left + (sprite_bounds.width / 2);
					center_sprite.y = sprite_bounds.top + (sprite_bounds.height / 2);
					sf::Vector2i tile_coord; //Tile coordinates of the player
					tile_coord.x = (center_sprite.x / 48) + 1;
					tile_coord.y = (center_sprite.y / 48) - 1;
					sf::Vector2i center_tile; //Center of tile in window coordinates
					center_tile.x = (tile_coord.x - 1) * 48;
					center_tile.y = (tile_coord.y - 1) * 48 + 100;

					auto lerp = [](float a, float b, float t) -> float
					{
						return a + t * (b - a);
					};

					auto isSolidTile = [&](const int& x, const int& y) -> bool
					{
						return tilemap[x][y]->getType() != tileType::AIR;
					};

					float smooth = 0.05f;

					int heading_x = plr.getCanMove()[1] - plr.getCanMove()[3];
					int heading_y = plr.getCanMove()[2] - plr.getCanMove()[0];
					bool solidOnX = isSolidTile(tile_coord.x + heading_x, tile_coord.y);
					bool solidOnY = isSolidTile(tile_coord.x, tile_coord.y + heading_y);

					//North and South movement
					if ((plr.getCanMove()[0] || plr.getCanMove()[2]) && !solidOnY)
					{
						float x = lerp(sprite_bounds.left, center_tile.x + (sprite_bounds.width / 6), smooth);
						plr.setPosition(x, sprite_bounds.top);
					}
					//East and West movement
					if ((plr.getCanMove()[1] || plr.getCanMove()[3]) && !solidOnX)
					{
						float y = lerp(sprite_bounds.top, center_tile.y, smooth);
						plr.setPosition(sprite_bounds.left, y);
					}

					if (plr.check(*tilemap[x][y], offset))
					{
						switch (tilemap[x][y]->getType())
						{
						case tileType::POWERUP_REVEALED:
							((PowerUp*)tilemap[x][y])->collision(plr);
							powerupPickupSound.play();

							break;
						case tileType::DOOR_OPEN:
							if (enemies.size() == 0)
							{
								levelCleared = true;
								if (!levelCompletePlayed)
								{
									levelCompleteSound.play();
									levelCompletePlayed = true;
								}
							}
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

	for (int i = 0; i < textTimers.size(); i++)
	{
		textTimers.at(i) += dt;
		if (textTimers.at(i) >= 2)
		{
			textTimers.pop_back();
			textPopups.pop_back();
		}
	}

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
				if (tilemap[x][y]->getType() == tileType::POWERUP_REVEALED ||
					tilemap[x][y]->getType() == tileType::DOOR_OPEN)
				{
					for (int directions = 0; directions < direction::COUNT; directions++)
					{
						if (DEBUG)
							std::cout << "Additional Enemies Spawned";
						enemies.push_back(new Enemy(&plr,
							(enemyType)(((PowerUp*)tilemap[powerUp_pos.x][powerUp_pos.y])->getPowerupType()),
							{x,y}, (direction)(directions)));
					}
				}
				if (tilemap[x][y]->getType() == tileType::POWERUP_REVEALED)
					tilemap[x][y]->setTile(tileType::AIR);

				tilemap[x][y]->interact();
			}

			// Animation update for brick destroy animation
			tilemap[x][y]->update(dt);

			if (tilemap[x][y]->getType() == tileType::POWERUP_REVEALED)
				datamap[x][y] = tileType::POWERUP_REVEALED;
			else if (tilemap[x][y]->getType() == tileType::DOOR_OPEN)
				datamap[x][y] = tileType::DOOR_OPEN;
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
					{
						if (deathCheck(bombs[0]->getExplodingRange(),
							bombs[0]->getPosition(), enemies.at(e)->getBoundingBox()))
						{
							enemies.at(e)->die();

							sf::Text popup;
							
							popup.setFont(popupFont);
							popup.setString(std::to_string(enemies.at(e)->getPointValue()));
							popup.setOrigin(popup.getLocalBounds().width / 2.,
								popup.getLocalBounds().height / 2.);
							popup.setPosition(enemies.at(e)->getPosition().x + 24,
								enemies.at(e)->getPosition().y + 24);
							popup.setScale(.33f, .33f);

							textPopups.insert(textPopups.begin(), popup);
							textTimers.insert(textTimers.begin(), 0);
						}
					}

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

		if (tilemap[position.x][position.y]->getType() != tileType::BOMB)
		{
			if (!bomb->isEntityColliding(plr.getBoundingBox()))
				tilemap[position.x][position.y]->setTile(tileType::BOMB);
		}
	}

	scoreboardPtr->decrementTime(dt);

	//Timer runs out
	if (scoreboardPtr->getTime() <= 0 && !outOfTime)
	{
		outOfTime = true;

		//Remove all enemies
		for (int e = 0; e < enemies.size(); e++)
		{
			delete enemies.at(e);
		}
		enemies.clear();

		//Spawn ten pontans
		for (int pontan = 0; pontan < 10; pontan++)
		{
			sf::Vector2i pos = { 0,0 };

			//Prevent them from spawning on non-air tiles
			//and from spawning too close to the player
			while (!(tilemap[pos.x][pos.y]->getType() == tileType::AIR &&
				(abs(pos.x - plr.getTilePosition().x) > 3 ||
				abs(pos.y - plr.getTilePosition().y) > 3)))
			{
				pos = { rand() % 32 + 1, rand() % 14 + 1 };
			}

			enemies.push_back(new Enemy(&plr, enemyType::PONTAN,
				pos, (direction)(rand() % 4)));
		}
	}
}


int Level::powerupType() const
{
	return ((PowerUp*)tilemap[powerUp_pos.x][powerUp_pos.y])->getPowerupType();
}


bool Level::powerupObtained() const
{
	return tilemap[powerUp_pos.x][powerUp_pos.y]->getType() != tileType::POWERUP_HIDDEN &&
		tilemap[powerUp_pos.x][powerUp_pos.y]->getType() != tileType::POWERUP_REVEALED;
}