 #include "Tile.h"


// Create a tile at (x,y) and set the type
// @param typ -> enum that indentifies the tile's properties
Tile::Tile(const int& x, const int& y, const tileType::ID& typ)
{
	// load the texture and set the sprite for tile
	mSprite.setTexture(TextureHolder::get(textures::ITEMS));
	setTile(typ);

	// blow up animation
	blowUp.setUp(TextureHolder::get(textures::ITEMS), 0, 16 * 2, 16, 16, 6); 
	blowUp.showOnce(); 

	// place the tile 
	mSprite.setPosition(x, y);

	// set intial state of the tile 
	destroyed = false; 
}


// destructor
Tile::~Tile()
{
}


//Returns the tileID of tile
tileType::ID Tile::getType() const
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
		case tileType::SOLID_AIR:
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


// Dictates a tile's behavior when colliding with bomb explosions
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


// Update the sprite state of the tile
void Tile::update(const float& dt)
{
	// If block is destoryed AND type is brick OR door_closed,
	// init blowup sequence
	if (destroyed == true && (type == tileType::BRICK || type == tileType::DOOR_CLOSED))
	{
		// Update the frames of animation in relation to dt
		blowUp.applyToSprite(mSprite);
		blowUp.update(dt); 
	
		// If at last frame of animation, reset the type
		if (blowUp.getCurrentFrame() == 5)
		{
			// If tile is type brick, set type to air 
			if (type == tileType::BRICK)
				setTile(tileType::AIR);
			// Else, set the type to door_open
			else
			{
				setTile(tileType::DOOR_OPEN);
				//spawn enemies
			}
		}
	}
}


// returns the position of the tile's sprite (top, left)
sf::Vector2f Tile::getPosition() const
{
	return mSprite.getPosition();
}
