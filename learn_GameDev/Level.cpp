#include "Level.h"


Level::Level()
{
	//Set positions and sizes of the tiles
	int xPos = 0, yPos = 100;
	for (int x = 0; x < MAP_LENGTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			if (y == 0 || x == 0 || y == MAP_HEIGHT - 1 || x == MAP_LENGTH - 1)
				tilemap[x][y] = new Tile(xPos, yPos, tileType::AIR);
			else if (x % 2 != 0 && y % 2 != 0)
				tilemap[x][y] = new Tile(xPos, yPos, tileType::TILE);
			else
				tilemap[x][y] = new Tile(xPos, yPos, tileType::AIR);

			yPos += 50;
		}
		xPos += 50;
		yPos = 100;
	}
}


Level::~Level()
{
	//Unallocate tilemap memory
	for (int x = 0; x < MAP_LENGTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
			delete tilemap[x][y];
}


void Level::generate(int levelNum)
{
	int random = 0, randX = 0, randY = 0, totalSoftBlock = 0, i = 0;
	//int ememies = 0;

	for (int x = 0; x < mapLength; x++)
	{
		for (int y = 0; y < mapHeight; y++)
		{
			if (!(x % 2 != 0 && y % 2 != 0) && x + y > 1) // keep top left corner open
			{
				random = rand() % 4;
				if (random == 1)
				{
					totalSoftBlock++;
					tilemap[x][y]->setTileRect(1);
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
	random = rand % totalSoftBlock; //pick random soft block

	for (int x = 0; x < mapLength; x++)
	{
		for (int y = 0; y < mapHeight; y++)
		{
			if(tilemap[x][y]->getType() == 1)
				i++;
			if(random == i)
				// set x,y to a powerup
		}
	}

	//Exit Set
	random = rand % totalSoftBlock; //pick random soft block
	i = 0;

	for (int x = 0; x < mapLength; x++)
	{
		for (int y = 0; y < mapHeight; y++)
		{
			if(tilemap[x][y]->getType() == 1)
				i++;
			if(random == i)
				// set x,y to a exit
		}
	}
	*/

}


void Level::end()
{
	//will check for level end
}


void Level::draw(sf::RenderWindow& window) const
{
	//Print the tiles to the window
	for (int x = 0; x < MAP_LENGTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
			tilemap[x][y]->draw(window);
}


//Detect collisions between player and tile
void Level::collisions(Player& plr)
{
	for (int x = 0; x < MAP_LENGTH; x++)
		for (int y = 0; y < MAP_HEIGHT; y++)
			tilemap[x][y]->detectCollision(plr);
}