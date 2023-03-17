#include "Level.h"
#include <math.h>
#include "Valcom.h"
#include "ONeal.h"

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
				datamap[x][y] == tileType::DOOR) && !(x == 1 && y == 1) &&
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
	for (int x = 0; x < MAP_LENGTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
			tilemap[x][y]->detectCollision(plr,
				y > 0 ? tilemap[x][y - 1]->getType() : tileType::TILE,
				y < MAP_HEIGHT - 1 ? tilemap[x][y + 1]->getType() : tileType::TILE,
				x > 0 ? tilemap[x - 1][y]->getType() : tileType::TILE,
				x < MAP_LENGTH - 1 ? tilemap[x + 1][y]->getType() : tileType::TILE);
}


sf::Vector2i Level::getClosestTile(const sf::Vector2f& v2)
{
	int x = 0, y = 0;
	Tile* closestTile = tilemap[x][y];

	for (int a = 0; a < MAP_LENGTH; a++)
	{
		for (int b = 0; b < MAP_HEIGHT; b++)
		{
			if (sqrt(pow(closestTile->getPosition().x - v2.x, 2) +
				pow(closestTile->getPosition().y - v2.y, 2)) >
				sqrt(pow(tilemap[a][b]->getPosition().x - v2.x, 2) +
					pow(tilemap[a][b]->getPosition().y - v2.y, 2)))
			{
				closestTile = tilemap[a][b];
				x = a;
				y = b;
			}
		}
	}

	return sf::Vector2i(x, y);
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
			if (datamap[x][y] != tilemap[x][y]->getType())
			  tilemap[x][y]->setTile((tileType::ID)datamap[x][y]);
        
			  tilemap[x][y]->update(dt);
		}
	}
}