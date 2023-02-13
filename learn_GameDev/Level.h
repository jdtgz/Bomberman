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
	Tile* tilemap[32][12];
};

