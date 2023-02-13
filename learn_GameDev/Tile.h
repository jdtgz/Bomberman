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
private:
	void initalizeTile(int, int, int);

	sf::RectangleShape tile;
	int tileType = 0;
};

