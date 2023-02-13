#pragma once
#include "Tile.h"
#include "SFML/Graphics.hpp"
#include <vector>

class Level
{
public:
	Level();
	~Level();

	void generate(int);
	void end();

	void print(sf::RenderWindow&);
private:
	const int mapLength = 31;
	const int mapHeight = 13;

	Tile* tilemap[31][13];
};