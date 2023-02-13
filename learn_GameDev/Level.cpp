#include "Level.h"


Level::Level()
{
	//Set positions and sizes of the tiles
	int xPos = 0, yPos = 100;
	for (int x = 0; x < mapLength; x++)
	{
		for (int y = 0; y < mapHeight; y++)
		{
			tilemap[x][y] = new Tile(xPos, yPos, 50);
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

	//This is to test tile textures
	for (int x = 0; x < mapLength; x++)
		for (int y = 0; y < mapHeight; y++)
			tilemap[x][y]->setTileType(TILE_TYPES::TILE);
}


void Level::end()
{
	//will check for level end
}


void Level::print(sf::RenderWindow& window)
{
	//Print the tiles to the window
	for (int x = 0; x < mapLength; x++)
		for (int y = 0; y < mapHeight; y++)
			tilemap[x][y]->print(window);
}