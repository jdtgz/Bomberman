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

	for (int i = 0; i < powerups.size(); i++)
	{
		//Remove any powerups that exist
		delete tilemap[powerups.at(i).x][powerups.at(i).y];

		//Replace them with a new generic tile
		tilemap[powerups.at(i).x][powerups.at(i).y] =
			new Tile((powerups.at(i).x - 1) * 48,
				(powerups.at(i).y - 1) * 48 + 100,
				tileType::AIR);
	}
	powerups = {}; //Empty array

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
					totalAirCount--; //Remove from air count and add to brick count
					totalBrickCount++;
					datamap[x][y] = tileType::BRICK;
					tilemap[x][y]->setTile(tileType::BRICK); 
				}
			}
		}
	}

	//Remove any enemies that may exist
	for (int i = 0; i < enemies.size(); i++)
		delete enemies[i];
	enemies = {}; //Empty pointer array after deallocating all memory

	//Add enemies to the map
	while (enemyCount < 6)
	{
		i = 0;
		targetAir = rand() % totalAirCount + 1;
		for (int x = 0; x < MAP_LENGTH-1; x++)
		{
			for (int y = 0; y < MAP_HEIGHT-1; y++)
			{
				if (datamap[x][y] == tileType::AIR)
				{
					i++;
					if (targetAir == i) //At randomly picked air tile
					{
						//TEMPORARY RANDOM
						if (rand() % 2 == 0)
							enemies.push_back(new Valcom(plrPtr, sf::Vector2i(x, y)));
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
			{
				i++;
				if (targetBrick == i) //At randomly picked brick tile
				{
					//DEBUG TESTING
					std::cout << "DOOR: " << x << ", " << y << '\n';

					//Set the tile to be a closed door
					datamap[x][y] = tileType::DOOR_CLOSED;
					tilemap[x][y]->setTile(tileType::DOOR_CLOSED);
				}
			}
		}
	}
  
  setPowerup(10, 1);
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
void Level::keyPressed(const sf::Keyboard::Key& key, Player& plr)
{
	// change the direction of the player based on input
	switch (key)
	{
	case sf::Keyboard::A:
		for (int i = 0; i < plr.getBombCount(); i++)
		{
			//Prevents the player from putting a bomb on top of a tile that isnt air.
			//Without this if statement, the player can put a bomb on top of the door tile
			//and the door would end up vanishing.
			if (tilemap[(int)plr.getPosition().x][(int)plr.getPosition().y]->getType() == tileType::ID::AIR)
			{
				if (bombManager[i] == false)
				{
					for (int i = 0; i < bombs.size(); i++)
					{
						sf::Sprite t = plr.getSprite();
						if (bombs[i]->isColliding(t))
						{
							std::cout << "COLLIDE!\n";
							return;
						}
					}
					bombManager[i] = true;

					// initialize the bomb
					//tilemap[(int)plr.getPosition().x][(int)plr.getPosition().y]->setTile(tileType::SOLID_AIR);

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
		for (int i = 0; i < bombs.size(); i++)
		{
			if (bombManager[i] == true && plr.hasDetonator() == true)
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
	
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->draw(window);

		/* Display enemy hitbox
		sf::RectangleShape box;
		box.setPosition(enemies[i]->getBoundingBox().left, enemies[i]->getBoundingBox().top);
		box.setSize(sf::Vector2f(enemies[i]->getBoundingBox().width, enemies[i]->getBoundingBox().height));
		box.setFillColor(sf::Color(255, 255, 255, 100));
		window.draw(box);
		//*/
	}

	for (int i = 0; i < bombs.size(); i++)
		bombs[i]->draw(window, datamap);
}


void Level::setMap(sf::Vector2i pos, int type)
{
	datamap[pos.x][pos.y] = type;
}


void Level::setPowerup(const int& x, const int& y)
{
	std::cout << "POWERUP: " << x << ", " << y << '\n';
	datamap[x][y] = tileType::POWERUP_HIDDEN;
	delete tilemap[x][y];
	tilemap[x][y] = new PowerUp((x - 1) * 48, (y - 1) * 48 + 100);
}


// Detect collisions between player and tile
void Level::collisions(Player& plr)
{
	sf::Vector2f offset;

	// check to see the player's collisions with enemies 
	if (!plr.isInvincible())
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			if (plr.check(*enemies[i]))
			{
				playerDead = true;
				std::cout << "PLAYER DEAD\n";
			}
		}
	}

	//Tilemap collisions
	for (int x = 0; x < MAP_LENGTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			//If the tile is not an air or open door,
			if (tilemap[x][y]->getType() != tileType::AIR && tilemap[x][y]->getType() != tileType::DOOR_OPEN &&
				//Not solid air that the player is standing on or solid air while the player has bomb pass,
				!(tilemap[x][y]->getType() == tileType::SOLID_AIR 
					&& (x == plr.getPosition().x && y == plr.getPosition().y || plr.hasBombPass())) &&
				//Not a brick, closed door, or hidden powerup while the player has wall pass
				!((tilemap[x][y]->getType() == tileType::BRICK ||
					tilemap[x][y]->getType() == tileType::DOOR_CLOSED ||
					tilemap[x][y]->getType() == tileType::POWERUP_HIDDEN) &&
					plr.hasWallPass()))
			{
				//Then collide with then tile
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
							/* Checks if the player is colliding with a revealed powerup */
							((PowerUp*)tilemap[x][y])->applyPowerUp(plr);
							
							break;
						case tileType::DOOR_OPEN: 
							/* Checks if the player is colliding with a open door */
							break;
						}
					}	
				}
			}
		}

	plr.move(offset.x, offset.y);
}


bool Level::deathCheck(std::vector<int> range, sf::Vector2i bombPos, const sf::FloatRect& bounds)
{
	// Check if entity is in spots above
	for (int i = 0; i <= range[0]; i++)
	{
		if (bounds.intersects(sf::FloatRect((bombPos.x - 1) * 48, (bombPos.y - i - 1) * 48 + 100, 48, 48)))
			return true;
	}
	// to the right
	for (int i = 0; i <= range[1]; i++)
	{
		if (bounds.intersects(sf::FloatRect((bombPos.x + i - 1) * 48, (bombPos.y - 1) * 48 + 100, 48, 48)))
			return true;	}
	// below
	for (int i = 0; i <= range[2]; i++)
	{
		if (bounds.intersects(sf::FloatRect((bombPos.x - 1) * 48, (bombPos.y + i - 1) * 48 + 100, 48, 48)))
			return true;
	}
	// and to the left of the bomb
	for (int i = 0; i <= range[3]; i++)
	{
		if (bounds.intersects(sf::FloatRect((bombPos.x - i - 1) * 48, (bombPos.y - 1) * 48 + 100, 48, 48)))
			return true;
	}
	return false; //Entity was not hit by bomb
}


void Level::update(const float& dt, Player& plr)
{
	int offset = 1;
	bool collided = false;

	// update the enemies
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
			delete enemies.at(enemies.size() - 1);
			enemies.pop_back();
		}
	}

	// Check for tileType conflicts for every tile in datamap and tileMap
	for (int x = 0; x < MAP_LENGTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			// If tileTypes conflict, they have been destroyed
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
					// de-activate the bomb
					bombManager[i] = false;

					// Destroy the Bricks
					datamap = bombs[0]->datamapExplosionCollision(datamap);

					// Change TileType of the Bomb Location
					tilemap[bombs[0]->getPosition().x][bombs[0]->getPosition().y]->setTile(tileType::AIR);
					
					// Check if player dies
					if (!plr.isInvincible())
						if(deathCheck(bombs[0]->getExplodingRange(), bombs[0]->getPosition(), plr.getBoundingBox()))
							std::cout << "PLAYER DEAD\n";

					// Check if enemies die
					for (int e = 0; e < enemies.size(); e++)
						if (deathCheck(bombs[0]->getExplodingRange(),
							bombs[0]->getPosition(), enemies.at(e)->getBoundingBox()))
							enemies.at(e)->die();

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

	//Checks the players collisions with bombs
	//If the bomb tile doesnt have solid air, check
	//if the player is off of the bomb, set the tile to solid air
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
}