#include "Tile.h"


Tile::Tile(int xCord, int yCord, int t)
{
	type = t; 
	initalizeTile(xCord, yCord);
}


Tile::~Tile()
{
}


//Draws the tile to the screen
void Tile::draw(sf::RenderWindow& window) const
{
	window.draw(tile);
}


//Returns the tile type as an integer
int Tile::getType()
{
	return type;
}


//Sets the tile type to the given type
void Tile::setTileRect()
{
	switch (type)
	{
		//put anything related to tile type changes here
		case TileType::Air:
			tile.setTextureRect({ 96,32,16,16 });
			break;
		case TileType::Brick:
			tile.setTextureRect({ 16,16,16,16 });
			break;
		case TileType::Tile:
			tile.setTextureRect({ 0,16,16,16 });
			break;
		case TileType::Door:
			tile.setTextureRect({ 32,16,16,16 });
			break;
	}
	tile.setScale(3, 3); 
}




//Set the tile to be a square of the given size at position x, y
void Tile::initalizeTile(int xCord, int yCord)
{
	tile.setTexture(TextureHolder::get(Textures::Items)); 
	setTileRect(); 
	tile.setPosition(xCord, yCord);

	// debug
	std::cout << "Tile Created at " << xCord << "," << yCord << '\n';
}





