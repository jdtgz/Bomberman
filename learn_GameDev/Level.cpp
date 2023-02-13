#include "Level.h"

Level::Level()
{
	//Set positions and sizes of the tiles
	int xPos = 0, yPos = 0;

	map.resize(32);
	for (auto& x : map)
		x.resize(12);

	for (auto& x : map)
	{
		for (auto tile : x)
		{
			tile = new Tile(xPos, yPos, 50);
			yPos += 50;
		}
		xPos += 50;
		yPos = 0;
	}
}

Level::~Level()
{
	for (auto& x : map)
		for (auto y : x)
			delete y;
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
	for (auto& x : map)
		for (auto& y : x)
			y->print(window);
}
