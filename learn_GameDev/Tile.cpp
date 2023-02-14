#include "Tile.h"


Tile::Tile(int xCord, int yCord, int size)
{
	initalizeTile(xCord, yCord, size);
}


Tile::~Tile()
{
}


//Set the tile to be a square of the given size at position x, y
void Tile::initalizeTile(int xCord, int yCord, int size)
{
	tile.setSize(sf::Vector2f(size, size));
	tile.setPosition(xCord, yCord);

	//For testing purposes
	//tile.setFillColor(sf::Color::Red);
	//tile.setOutlineThickness(5);
	//tile.setOutlineColor(sf::Color::Green);

	//Debug
	std::cout << "Tile Created at " << xCord << "," << yCord << '\n';
}


//Returns the tile type as an integer
int Tile::getTileType()
{
	return tileType;
}


//Sets the tile type to the given type
void Tile::setTileType(const int type)
{
	tileType = type;

	switch (tileType)
	{
		//put anything related to tile type changes here
	case TILE_TYPES::AIR:
		break;
	case TILE_TYPES::BOMB:
		break;
	case TILE_TYPES::BRICK:
		break;
	case TILE_TYPES::EXIT:
		break;
	case TILE_TYPES::EXPLOTION:
		break;
	case TILE_TYPES::POWERUP:
		break;
	case TILE_TYPES::TILE:
		sf::Texture* tileTex = &TextureHolder::get(Textures::Items);
		tile.setTexture(tileTex);
		tile.setTextureRect(sf::IntRect(0,16,16,16));
		break;
	}
}


void Tile::move(int distance)
{
	tile.move(distance, 0);
}


//Draws the tile to the screen
void Tile::print(sf::RenderWindow& window) const
{
	window.draw(tile);
}