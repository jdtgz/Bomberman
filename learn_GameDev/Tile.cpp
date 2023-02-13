#include "Tile.h"

Tile::Tile(int xCord, int yCord, int size)
{
	initalizeTile(xCord, yCord, size);
}

Tile::~Tile()
{
}

void Tile::initalizeTile(int xCord, int yCord, int size)
{
	tile.setSize(sf::Vector2f(size, size));
	tile.setPosition(xCord, yCord);
	tile.setFillColor(sf::Color::Red);
	tile.setOutlineThickness(5);
	tile.setOutlineColor(sf::Color::Green);

	std::cout << "Tile Created at " << xCord << "," << yCord << '\n';
}

int Tile::getTileType()
{
	return tileType;
}

void Tile::setTileType(int newType)
{
	tileType = newType;
}

void Tile::move(int distance)
{
	tile.move(distance, 0);
}

void Tile::print(sf::RenderWindow& window) const
{
	//window.draw(tile);
}