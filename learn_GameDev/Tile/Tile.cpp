 #include "Tile.h"


// place a tile of type t at (xCoord, yCoord)
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
}


// destructor
Tile::~Tile()
{
}


//Tile interactions when colliding with a bomb/explosion
void Tile::interact()
{	
	// destory the brick 
	if (type == tileType::BRICK || type == tileType::DOOR_CLOSED)
		destroyed = true;

}


//Draws the tile to the screen
void Tile::draw(sf::RenderWindow& window)
{
	Collidable::updateRect(mSprite.getGlobalBounds());
	window.draw(mSprite);
}


// updates the block's display 
void Tile::update(const float& dt)
{
	//std::cout << "Update";
	// initiate the blowUp animation IF the tile has been destoryed 
	if (destroyed == true && (type == tileType::BRICK || type == tileType::DOOR_CLOSED))
	{
		// display one cycle of the blowUp animation
		blowUp.applyToSprite(mSprite);
		blowUp.update(dt); 
	
		// set the tile to air 
		if (blowUp.getCurrentFrame() == 5)
		{
			if (type == tileType::BRICK)
				setTile(tileType::AIR);
			else
			{
				setTile(tileType::DOOR_OPEN);
				//spawn enemies
			}
		}
	}
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
		case tileType::POWERUP:
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


sf::Vector2f Tile::getPosition() const
{
	return mSprite.getPosition();
}
