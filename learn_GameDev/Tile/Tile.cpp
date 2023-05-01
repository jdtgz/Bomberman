 #include "Tile.h"


// Create a tile at (x,y) and set the type
// @param typ -> enum that indentifies the tile's properties
Tile::Tile(const int& x, const int& y, const tileType::ID& typ)
{
	mSprite.setTexture(TextureHolder::get(textures::ITEMS));
	setTile(typ);

	blowUp.setUp(TextureHolder::get(textures::ITEMS), 0, 16 * 2, 16, 16, 6); 
	blowUp.showOnce(); 

	mSprite.setPosition(x, y);

	destroyed = false; 
}


// destructor
Tile::~Tile()
{
}


// Evaluates wheter the block will interact after collisions with a bomb
void Tile::interact()
{	
	// if tileType is brick OR door_closed, destroy the tile
	if (type == tileType::BRICK || type == tileType::DOOR_CLOSED)	
		destroyed = true; 
}


// Draws the tile to a window
void Tile::draw(sf::RenderWindow& window)
{
	Collidable::updateRect(mSprite.getGlobalBounds());
	window.draw(mSprite);
}


// Evaluates the current state of the tile and controls its visual display
void Tile::update(const float& dt)
{
	// If block is destoryed AND type is brick/door_closed, init blow up sequence
	if (destroyed == true && (type == tileType::BRICK || type == tileType::DOOR_CLOSED))
	{
		blowUp.applyToSprite(mSprite);
		blowUp.update(dt); 
	
		// If animation is finished, reset the type
		if (blowUp.getCurrentFrame() == 5)
		{
			// If tile is a brick, convert to air, Else, convert to door_open
			if (type == tileType::BRICK)
				setTile(tileType::AIR);
			else
				setTile(tileType::DOOR_OPEN);
		}
	}
}


void Tile::collision(Player& plr)
{
}


// Returns the tileID of tile
tileType::ID Tile::getType() const
{
	return type;
}


// Given a tileID, set the proper textureRect & scale it 
void Tile::setTile(const tileType::ID& t)
{
	type = t;
	switch (t)
	{
		case tileType::AIR:
		case tileType::SOLID_AIR:
		case tileType::BOMB:
			mSprite.setTextureRect({ 16 * 6, 16 * 2, 16, 16 });
			break;
		case tileType::BRICK:
		case tileType::POWERUP_HIDDEN:
		case tileType::DOOR_CLOSED:
			mSprite.setTextureRect({ 16 * 1, 16 * 1, 16, 16 });
			break;
		case tileType::DOOR_OPEN:
			mSprite.setTextureRect({ 16 * 2, 16, 16, 16 });
			break;
		case tileType::TILE:
			mSprite.setTextureRect({ 16 * 0, 16, 16, 16 });
	}
	mSprite.setScale(3, 3);
}


// returns the window position of the tile's sprite (top, left)
sf::Vector2f Tile::getPosition() const
{
	return mSprite.getPosition();
}
