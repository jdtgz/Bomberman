#include "Level.h"
#include "../Enemies/Valcom.h"
#include "../Enemies/ONeal.h"
#include <math.h>


Level::Level()
{
	//Set positions and sizes of the tiles
	int xPos = -48, yPos = 52;

	//set size of the datamap
	datamap.resize(MAP_LENGTH);
	for (auto& x : datamap)
		x.resize(MAP_HEIGHT);

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
}


Level::~Level()
{
	//Unallocate tilemap memory
	for (int x = 0; x < MAP_LENGTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
			delete tilemap[x][y];

	for (int i = 0; i < enemies.size(); i++)
		delete enemies[i];
}


void Level::generate(const int& levelNum, const Player* plrPtr)
{
	int i = 0;
	int totalBrickCount = 0, targetBrick = 0; // Used for random positions for PowerUp and Door
	int totalAirCount = 0, targetAir = 0, enemyCount = 0; // Used for random enemy Placement

	//For every tile position
	for (int x = 0; x < MAP_LENGTH - 1; x++)
	{
		for (int y = 0; y < MAP_HEIGHT - 1; y++)
		{
			//If it is not a Tile tile and it
			//is not in the top left corner
			if (datamap[x][y] != tileType::TILE &&
				x + y - 2 > 1 &&
				x >= 1 && y >= 1)
			{
				//Reset to Air
				datamap[x][y] = tileType::AIR;
				tilemap[x][y]->setTile(tileType::AIR); 
				totalAirCount++;

				//Randomly assign tiles to Brick
				if (rand() % 4 == 1)
				{
					totalBrickCount++;
					datamap[x][y] = tileType::BRICK;
					tilemap[x][y]->setTile(tileType::BRICK); 
				}
			}
		}
	}


	while (enemyCount < 6)
	{
		i = 0;
		targetAir = rand() % totalAirCount + 1;
		for (int x = 0; x < MAP_LENGTH-1; x++)
		{
			for (int y = 0; y < MAP_HEIGHT-1; y++)
			{
				if (datamap[x][y] == tileType::AIR)
					i++;
				if (targetAir == i) //At randomly picked air tile
				{
					i++; //Increment counter to prevent spawning enemies in one spot

					//TEMPORARY RANDOM
					if(rand() % 2 == 0)
						enemies.push_back(new Valcom(plrPtr, sf::Vector2i(x,y)));
					else
						enemies.push_back(new ONeal(plrPtr, sf::Vector2i(x, y)));

					//Increment nmber of enemies on screen
					enemyCount++;

					//DEBUG TESTING
					std::cout << "ENEMY: " << x << ", " << y << '\n';
				}
			}
		}

	}

	/*
	//PowerUp Set
	targetBrick = rand % totalBrickCount; //pick random brick block

	for (int x = 0; x < mapLength; x++)
	{
		for (int y = 0; y < mapHeight; y++)
		{
			if(tilemap[x][y]->getType() == 1)
				i++;
			if(targetBrick == i)
				// set x,y to a powerup
		}
	}
	*/

	targetBrick = rand() % totalBrickCount + 1; //Pick random brick tile
	i = 0; //Reset counter

	for (int x = 0; x < MAP_LENGTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			//Count the number of bricks
			if (datamap[x][y] == tileType::BRICK)
				i++;
			if (targetBrick == i) //At randomly picked brick tile
			{
				i++; //Increment counter to prevent spawning multiple doors

				//DEBUG TESTING
				std::cout << "DOOR: " << x << ", " << y << '\n';

				//Set the tile to be a closed door
				datamap[x][y] = tileType::DOOR_CLOSED;
				tilemap[x][y]->setTile(tileType::DOOR_CLOSED);
			}
		}
	}
  
	// place a powerUp
	std::cout << "POWERUP: 10, 1\n"; 
	datamap[10][1] = tileType::POWERUP; 
	delete tilemap[10][1];
	tilemap[10][1] = new PowerUp(480 -48, 100); 

	//TEMPORARY
	//enemies.push_back(new Valcom(plrPtr));
	//enemies.push_back(new ONeal(plrPtr));
	//^^^^^^^^^
}


void Level::end()
{
	//will check for level end
}


int Level::getLength() const
{
	return MAP_LENGTH;
}


int Level::getHeight() const
{
	return MAP_HEIGHT;
}


// detects whether a key has been pressed and acts accordingly
void Level::keyPressed(const sf::Keyboard::Key& key)
{
	// change the direction of the player based on input
	switch (key)
	{
	case sf::Keyboard::A:
		for (int i = 0; i < bombCount; i++)
		{
			if (bombManager[i] == false)
			{
				for (int i = 0; i < bombs.size(); i++)
				{
					if (bombs[i]->isColliding(playerSprite))
					{
						std::cout << "COLLIDE!\n";
						return;
					}
				}
				bombManager[i] = true;

				// initialize the bomb
				if (detonator == false)
				{
					tilemap[playerX][playerY]->setTile(tileType::SOLID_AIR);
					bombs.push_back(new Bomb(playerX, playerY, flameRange, true));
				}
				else
				{
					tilemap[playerX][playerY]->setTile(tileType::SOLID_AIR);
					bombs.push_back(new Bomb(playerX, playerY, flameRange, false));
				}
				break;
			}
		}
		break;
	case sf::Keyboard::B:
		for (int i = 0; i < bombs.size(); i++)
		{
			if (bombManager[i] = true)
				bombs[i]->explode();
		}
		break;
	}
}


// draw all the objects and emeies onto the screen 
void Level::draw(sf::RenderWindow& window) const
{
	//Print the tiles to the window
	for (int x = 0; x < MAP_LENGTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
			tilemap[x][y]->draw(window);
	
	for(int i = 0; i < enemies.size(); i++)
		enemies[i]->draw(window);

	for (int i = 0; i < bombs.size(); i++)
		bombs[i]->draw(window, datamap);
}


void Level::setMap(sf::Vector2i pos, int type)
{
	datamap[pos.x][pos.y] = type;
}


//Detect collisions between player and tile
void Level::collisions(Player& plr)
{
	sf::Vector2f offset;

	for (int i = 0; i < enemies.size(); i++)
	{
		if (plr.check(*enemies[i]))
		{
			playerDead = true;
			std::cout << "PLAYER DEAD\n";
		}
	}


	for (int x = 0; x < MAP_LENGTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			if (tilemap[x][y]->getType() != tileType::AIR &&
				tilemap[x][y]->getType() != tileType::DOOR_OPEN &&
				!(tilemap[x][y]->getType() == tileType::SOLID_AIR && x == playerX && y == playerY))
			{
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
					plr.check(*tilemap[x][y], offset);
				}
			}
		}

	plr.move(offset.x, offset.y);
}


bool Level::deathCheck(std::vector<int> range, sf::Vector2i bombPos)
{
	// Check if player is in spots above
	for (int i = 0; i <= range[0]; i++)
	{
		if (sf::Vector2i(playerX, playerY) == sf::Vector2i(bombPos.x, bombPos.y - i))
			return true;
	}
	// to the right
	for (int i = 0; i <= range[1]; i++)
	{
		if (sf::Vector2i(playerX, playerY) == sf::Vector2i(bombPos.x + i, bombPos.y))
			return true;
	}
	// below
	for (int i = 0; i <= range[2]; i++)
	{
		if (sf::Vector2i(playerX, playerY) == sf::Vector2i(bombPos.x, bombPos.y + i))
			return true;
	}
	// and to the left of the bomb
	for (int i = 0; i <= range[3]; i++)
	{
		if (sf::Vector2i(playerX, playerY) == sf::Vector2i(bombPos.x - i, bombPos.y))
			return true; //If the positions match player dies
	}
	return false; // If no matches found player lives
}


void Level::update(const float& dt, sf::Vector2f playerPos, 
	int bCount, int fRange, bool detonate, sf::Sprite pSprite)
{
	int offset = 1;
	bool collided = false;

	// update the enemies
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update(dt);
		enemies[i]->move(tilemap);
	}


	// Check for tileType conflicts for every tile in datamap and tileMap
	for (int x = 0; x < MAP_LENGTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			// If tileTypes conflict, they have been destroyed
			if (datamap[x][y] != tilemap[x][y]->getType())
			{
				if (tilemap[x][y]->getType() == tileType::POWERUP) 
					datamap[x][y] = tileType::POWERUP;

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
					// de-activate the bomb
					bombManager[i] = false;

					// Destroy the Bricks
					datamap = bombs[0]->datamapExplosionCollision(datamap);

					// Change TileType of the Bomb Location
					tilemap[bombs[0]->getPosition().x][bombs[0]->getPosition().y]->setTile(tileType::AIR);
					
					// Check if player dies
					if(deathCheck(bombs[0]->getExplodingRange(), bombs[0]->getPosition()))
						std::cout << "PLAYER DEAD\n";

					// Remove Bomb
					delete bombs[0];
					bombs.erase(bombs.begin());
				}
			}
			else
				bombManager[i] = false;
		}
	}

	//Update bombs
	for (int i = 0; i < bombs.size(); i++)
	{
		bombs[i]->update(dt);
	}

	//Set all data recived from player
	playerX = playerPos.x;
	playerY = playerPos.y;
	flameRange = fRange;
	bombCount = bCount;
	detonator = detonate;
	playerSprite = pSprite;
}