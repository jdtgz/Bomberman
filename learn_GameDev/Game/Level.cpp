#include "Level.h"
#include "../Enemies/Valcom.h"
#include "../Enemies/ONeal.h"
#include <math.h>

Level::Level()
{
	//Set positions and sizes of the tiles
	int xPos = -48, yPos = 52;
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

	enemies.push_back(new Valcom(sf::Vector2i(0, 0)));
	enemies.push_back(new ONeal(sf::Vector2i(0, 0)));
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


void Level::generate(const int& levelNum)
{
	int totalBrickCount = 0, targetBrick = 0, i = 0;
	//int enemies = 0;

	for (int x = 0; x < MAP_LENGTH - 1; x++)
	{
		for (int y = 0; y < MAP_HEIGHT - 1; y++)
		{
			if ((datamap[x][y] == tileType::AIR || datamap[x][y] == tileType::BRICK ||
				datamap[x][y] == tileType::DOOR) &&
				(x + y - 2 > 1) &&
				x >= 1 && y >= 1)
			{
				//Reset on regeneration
				datamap[x][y] = tileType::AIR;

				if (rand() % 4 == 1)
				{
					totalBrickCount++;
					datamap[x][y] = tileType::BRICK;
				}
			}
		}
	}

	/*
	while(enemies < 6)
	{
	randX = (rand() % (mapLength - 2)) + 1
	randY = (rand() % (mapHeight - 2)) + 1

	if(tilemap[x][y]->getType() == 0 && x + y > 1)
		//Create enemy at x,y
	}

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

	targetBrick = rand() % totalBrickCount + 1; //pick random brick block
	i = 0;

	for (int x = 0; x < MAP_LENGTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			if (datamap[x][y] == tileType::BRICK)
				i++;
			if (targetBrick == i)
			{
				i++;
				std::cout << "DOOR: " << x << ", " << y << '\n';
				datamap[x][y] = tileType::DOOR;
			}
		}
	}
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


// draw all the objects and emeies onto the screen 
void Level::draw(sf::RenderWindow& window) const
{
	//Print the tiles to the window
	for (int x = 0; x < MAP_LENGTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
			tilemap[x][y]->draw(window);
	
	for(int i = 0; i < enemies.size(); i++)
		enemies[i]->draw(window);

}


void Level::setMap(sf::Vector2i pos, int type)
{
	datamap[pos.x][pos.y] = type;
}


//Detect collisions between player and tile
void Level::collisions(Player& plr)
{
	sf::Vector2f offset;
	for (int x = 0; x < MAP_LENGTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			if (tilemap[x][y]->getType() != tileType::AIR)
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


void Level::update(const float& dt, int flameRange)
{
	int offset = 1;
	bool collided = false;
	
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update(dt);
		enemies[i]->move(tilemap, sf::Vector2i(MAP_LENGTH, MAP_HEIGHT));
	}

	//visually set all the tiles to the data map
	for (int x = 0; x < MAP_LENGTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			tilemap[x][y]->update(dt);
			if (datamap[x][y] != tilemap[x][y]->getType())
				tilemap[x][y]->setTile((tileType::ID)datamap[x][y]);
		}
	}
}