#include "Tile.h"


// place a tile of type t at (xCoord, yCoord)
Tile::Tile(const int& x, const int& y, const tileType::ID& t)
{
	// set the tileID, if it is a block and not a Bomb/PowerUp
	if(t != tileType::BOMB && t != tileType::POWERUP)
		type = t;

	// load the texture and set the sprite for tile
	tile.setTexture(TextureHolder::get(textures::ITEMS));
	setTile(t);

	// blow up animation ONLY for tileType::BRICK
	blowUp.setUp(TextureHolder::get(textures::ITEMS), 0, 16 * 2, 16, 16, 6); 

	// place the tile 
	tile.setPosition(x, y);
}


// destructor
Tile::~Tile()
{
}


//Tile interactions
void Tile::interact()
{
}


//Draws the tile to the screen
void Tile::draw(sf::RenderWindow& window) const
{
	window.draw(tile);
}


//Returns the tileID of tile
tileType::ID Tile::getType()
{
	return type;
}


//Given an tileID, set the proper textureRect & scale it 
void Tile::setTile(const tileType::ID& t)
{
	type = t;
	switch (t)
	{
		//put anything related to tile type changes here
		case tileType::AIR:
			tile.setTextureRect({ 16 * 6, 16 * 2, 16, 16 });
			break;
		case tileType::BRICK:
			tile.setTextureRect({ 16 * 1,16 * 1,16,16 });
			break;
		case tileType::TILE:
			tile.setTextureRect({ 16 * 0, 16, 16, 16 });
			break;
		case tileType::DOOR:
			tile.setTextureRect({ 16 * 2, 16 * 1, 16, 16 });
	}
	tile.setScale(3, 3);
}


/*
//destroys the tile if its tileID is Brick
//should be called AFTER a confirmed collision with a bomb object
void Tile::destroy()
{
	if (type == TileType::Brick)
	{

	}
}
*/


//tracks collisions between the player and the tile, 
//pushes them away from the tile
void Tile::detectCollision(Player& plr, const tileType::ID& u, const tileType::ID& d,
	const tileType::ID& l, const tileType::ID& r)
{
	//Get hitboxes
	sf::FloatRect pB = plr.getBoundingBox();
	sf::FloatRect tB = tile.getGlobalBounds();

	//For "auto correct" feature
	const float NEAR = 0.3f; //x% from the top
	const float FAR = 1.f - NEAR; //x% from the bottom

	//Adjust player box by player move speed
	pB.top -= plr.getSpeed();
	pB.height += 2 * plr.getSpeed();
	pB.left -= plr.getSpeed();
	pB.width += 2 * plr.getSpeed();

	//The player box is intersecting a tile and the tile is non-passable
	if (pB.intersects(tB) && type != tileType::AIR)
	{
		//Moving horizontally
		if (plr.getVelocity().x != 0)
		{
			//Up Correction
			if (pB.top + pB.height > tB.top &&
				pB.top + pB.height < tB.top + (tB.height * NEAR) &&
				u == tileType::AIR)
				plr.move(0, -plr.getSpeed());
			//Down Correction
			else if (pB.top < tB.top + tB.height &&
				pB.top > tB.top + (tB.height * FAR) &&
				d == tileType::AIR)
				plr.move(0, plr.getSpeed());
			//Running into tile
			else
			{
				//Prevent player from moving into tile
				if (plr.getVelocity().x > 0)
					plr.setCanMove(directions::RIGHT, false);
				else
					plr.setCanMove(directions::LEFT, false);
			}
		}
		//Moving vertically
		else if (plr.getVelocity().y != 0)
		{
			//Left Correction
			if (pB.left + pB.width > tB.left &&
				pB.left + pB.width < tB.left + (tB.width * NEAR) &&
				l == tileType::AIR)
				plr.move(-plr.getSpeed(), 0);
			//Right Correction
			else if (pB.left < tB.left + tB.width &&
				pB.left > tB.left + (tB.width * FAR) &&
				r == tileType::AIR)
				plr.move(plr.getSpeed(), 0);
			//Running into tile
			else
			{
				//Prevent player from moving into tile
				if (plr.getVelocity().y > 0)
					plr.setCanMove(directions::DOWN, false);
				else
					plr.setCanMove(directions::UP, false);
			}
		}
	}
}


sf::Vector2f Tile::getPosition() const
{
	return tile.getPosition();
}