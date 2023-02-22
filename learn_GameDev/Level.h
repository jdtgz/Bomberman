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

	void draw(sf::RenderWindow&) const;
	void collisions(Player&);
private:
	const int MAP_LENGTH = 31;
	const int MAP_HEIGHT = 13;

	Tile* tilemap[31][13];
};