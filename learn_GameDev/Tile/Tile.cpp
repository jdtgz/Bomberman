 #include "Tile.h"


// place a tile of type t at (xCoord, yCoord)
Tile::Tile(const int& x, const int& y, const tileType::ID& typ)
{
	// load the texture and set the sprite for tile
	mSprite.setTexture(TextureHolder::get(textures::ITEMS));
	setTile(typ);

	// blow up animation ONLY for tileType::BRICK
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
	if (type == tileType::BRICK)
	{
		// destory the brick 
		destroyed = true; 
	}
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
	if (destroyed == true && type == tileType::BRICK)
	{
		std::cout << "Animate";
		// display one cycle of the blowUp animation
		blowUp.applyToSprite(mSprite);
		blowUp.update(dt); 
	
		if (blowUp.getCurrentFrame() == 5)
		{
			// set the tile to air 
			setTile(tileType::AIR);
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
			mSprite.setTextureRect({ 16 * 6, 16 * 2, 16, 16 });
			break;
		case tileType::BRICK:
			mSprite.setTextureRect({ 16 * 1,16 * 1,16,16 });
			break;
		case tileType::TILE:
			mSprite.setTextureRect({ 16 * 0, 16, 16, 16 });
			break;
		case tileType::DOOR:
			mSprite.setTextureRect({ 16 * 1, 16 * 1, 16, 16 });
			break; 
		case tileType::POWERUP:
			mSprite.setTextureRect({ 16 * 1,16 * 1,16,16 });
	}
	mSprite.setScale(3, 3);
}


//tracks collisions between the player and the tile, 
//pushes them away from the tile
void Tile::detectCollision(Player& plr, const tileType::ID& u, const tileType::ID& d,
	const tileType::ID& l, const tileType::ID& r)
{
	//Get hitboxes
	sf::FloatRect pB = plr.getBoundingBox();
	sf::FloatRect tB = mSprite.getGlobalBounds();

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
	return mSprite.getPosition();
}
