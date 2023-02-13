#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

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
	enum types
	{
		AIR = 0,
		BRICK, // breakable
		TILE, // invincible
		BOMB,
		EXPLOTION,
		POWERUP,
		EXIT
	};

	void initalizeTile(int, int, int);

	int tileType = 0;
};