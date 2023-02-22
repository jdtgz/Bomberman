#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"
#include "Player.h"

namespace tileType 
{
	enum tileId { AIR = 0, BRICK, TILE, DOOR };
}


class Tile
{
public:
	Tile(int, int, int);
	~Tile();

	int getType();
	void setTileRect(int);
	
	void draw(sf::RenderWindow&) const;
	void detectCollision(Player&);
private:
	sf::Sprite tile; 

	int type;
};
