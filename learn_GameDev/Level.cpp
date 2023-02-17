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
	//will set all the tile IDs on level start
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