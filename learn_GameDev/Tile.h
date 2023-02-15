#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"

namespace TileType 
{
	enum Tile_ID { Air = 0, Brick, Tile, Door };
}

class Tile
{
public:
	Tile(int, int, int);
	~Tile();

	int getType();
	void setTileRect();
	void destroy();

	void draw(sf::RenderWindow&) const;

private:
	sf::Sprite tile; 
	void initalizeTile(int, int);

	int type;
};