#pragma once
#include "Tile.h"
#include "SFML/Graphics.hpp"
#include <vector>


class Level
{
public:
	Level();
	~Level();

	void generate(const int&);
	void end();

	int getLength() const;
	int getHeight() const;

	void draw(sf::RenderWindow&) const;
	void collisions(Player&);
private:
	static const int MAP_LENGTH = 31;
	static const int MAP_HEIGHT = 13;
	static const int BORDER_COUNT = (2 * (MAP_LENGTH + 2)) + (2 * MAP_HEIGHT);

	Tile* tilemap[MAP_LENGTH][MAP_HEIGHT];
	Tile* border[BORDER_COUNT];
};