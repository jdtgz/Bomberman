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
		case tileType::AIR:
			tile.setTextureRect({ 96,32,16,16 });
			break;
		case tileType::BRICK:
			tile.setTextureRect({ 16,16,16,16 });
			break;
		case tileType::TILE:
			tile.setTextureRect({ 0,16,16,16 });
			break;
		case tileType::DOOR:
			tile.setTextureRect({ 32,16,16,16 });
			break;
	}
	tile.setScale(3, 3); 

}


//Set the tile to be a square of the given size at position x, y
void Tile::initalizeTile(int xCord, int yCord)
{
	tile.setTexture(TextureHolder::get(textures::ITEMS));
	setTileRect();
	tile.setPosition(xCord, yCord);

	// debug
	std::cout << "Tile Created at " << xCord << "," << yCord << '\n';
}


void Tile::detectCollision(Player& plr)
{
	sf::FloatRect pB = plr.getBoundingBox();
	sf::FloatRect tB = tile.getGlobalBounds();

	if (pB.intersects(tB) && type != tileType::AIR)
	{
		//Moving Horizontally
		if (plr.getVelocity().x != 0)
		{
			//Moving Right
			if (plr.getVelocity().x > 0)
			{
				plr.setCanMoveRight(false);
				plr.move(-plr.getSpeed(), 0);
			}
			//Moving Left
			else
			{
				plr.setCanMoveLeft(false);
				plr.move(plr.getSpeed(), 0);
			}
		}
		//Moving Vertically
		else if (plr.getVelocity().y != 0)
		{
			//Moving Down
			if (plr.getVelocity().y > 0)
			{
				plr.setCanMoveDown(false);
				plr.move(0, -plr.getSpeed());
			}
			//Moving Up
			else
			{
				plr.setCanMoveUp(false);
				plr.move(0, plr.getSpeed());
			}
		}
	}
}