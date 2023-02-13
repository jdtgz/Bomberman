#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"

enum TILE_TYPES
{
	AIR = 0,
	BRICK, // breakable
	TILE, // invincible
	BOMB,
	EXPLOTION,
	POWERUP,
	EXIT
};

class Tile
{
public:
	Tile(int, int, int);
	~Tile();

	int getTileType();
	void setTileType(int);

	void move(int); //Tiles only move side to side
	
	void print(sf::RenderWindow&) const;
	sf::RectangleShape tile;
private:
	void initalizeTile(int, int, int);

	int tileType = 0;
};