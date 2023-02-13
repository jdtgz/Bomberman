#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class myTile
{
public:
	myTile(int, int, int);
	~myTile();

	int getTileType();
	void setTileType(int);

	void move(int); //Tiles only move side to side

	void print(sf::RenderWindow&) const;
	sf::RectangleShape tile;
private:
	void initalizeTile(int, int, int);

	int tileType = 0;
};