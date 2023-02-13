#include "Level.h"

Level::Level()
{
	//Set positions and sizes of the tiles
	int xPos = 0, yPos = 0;

	for (int x = 0; x < 32; x++)
	{
		for (int y = 0; y < 12; y++)
		{
			tilemap[x][y] = new Tile(xPos, yPos, 50);
			yPos += 50;
		}
		xPos += 50;
		yPos = 0;
	}
}

Level::~Level()
{
	for (int x = 0; x < 32; x++)
		for (int y = 0; y < 12; y++)
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

void Level::print(sf::RenderWindow& window)
{
	//print the tiles to the window
	for (int x = 0; x < 32; x++)
		for (int y = 0; y < 12; y++)
			tilemap[x][y]->print(window);
}