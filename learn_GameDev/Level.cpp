#include "Level.h"


Level::Level()
{
	//Set positions and sizes of the tiles
	int xPos = 0, yPos = 100;
	for (int x = 0; x < mapLength; x++)
	{
		for (int y = 0; y < mapHeight; y++)
		{
			if (y == 0 || x == 0 || y == mapHeight - 1 || x == mapLength - 1)
				tilemap[x][y] = new Tile(xPos, yPos, TileType::Air);
			else if (x % 2 != 0 && y % 2 != 0)
				tilemap[x][y] = new Tile(xPos, yPos, TileType::Tile);
			else
				tilemap[x][y] = new Tile(xPos, yPos, TileType::Air);

			yPos += 50;
		}
		xPos += 50;
		yPos = 100;
	}
}


Level::~Level()
{
	//Unallocate tilemap memory
	for (int x = 0; x < mapLength; x++)
		for (int y = 0; y < mapHeight; y++)
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
	for (int x = 0; x < mapLength; x++)
		for (int y = 0; y < mapHeight; y++)
			tilemap[x][y]->draw(window);
}