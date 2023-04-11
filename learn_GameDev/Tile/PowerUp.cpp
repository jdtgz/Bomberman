#include "PowerUp.h"


// Create a PowerUp at (x,y) and set its powerUpType 
PowerUp::PowerUp(const int& x, const int& y)
	: Tile(x, y, tileType::POWERUP_HIDDEN)
{
	// set the power up type randomly
	srand(time(NULL)); 
	powerUpType = (int)(rand() % 8);

	// set the initial state of powerUp
	destroyed = false; 
}


// destructor
PowerUp::~PowerUp()
{
}


// if collided with a flame from bomb, 
// then destroy old mSprite & reveal actual mSprite
void PowerUp::revealPowerUp()
{
	// set the type to be a revealed powerUp
	type = tileType::POWERUP_REVEALED; 

	// Based on pwoerUpType, set the sprite
	switch (powerUpType)
	{
		case powerups::BOMB_UP:
			mSprite.setTextureRect({ 0, 48, 16, 16 });
			std::cout << "BOMB UP\n";
			break;
		case powerups::FLAME_UP:
			mSprite.setTextureRect({ 16, 48, 16, 16 });
			std::cout << "FLAME UP\n";
			break;
		case powerups::SPEED_UP:
			mSprite.setTextureRect({ 32, 48, 16, 16 });
			std::cout << "SPEED UP\n";
			break;
		case powerups::WALL_PASS:
			mSprite.setTextureRect({ 48, 48, 16, 16 });
			std::cout << "WALL PASS\n";
			break;
		case powerups::DETONATOR:
			mSprite.setTextureRect({ 64, 48, 16, 16 });
			std::cout << "DETONATOR\n";
			break;
		case powerups::BOMB_PASS:
			mSprite.setTextureRect({ 80, 48, 16, 16 });
			std::cout << "BOMB PASS\n";
			break;
		case powerups::FLAME_PASS:
			mSprite.setTextureRect({ 96, 48, 16, 16 });
			std::cout << "FLAME PASS\n";
			break;
		case powerups::INVINCIBILITY:
			mSprite.setTextureRect({ 112, 48, 16, 16 });
			std::cout << "INVINCIBLE\n";
			break;
	}

	// scale the sprite properly
	mSprite.setScale(3, 3);
}


// Dictates a tile's behavior when colliding with bomb explosions 
void PowerUp::interact()
{
	// destroy the powerUp
	destroyed = true;

	/*
	// If the power up is revealed 
	if (type == tileType::POWERUP_REVEALED)
	{
		// spawn enemies on the screen
		spawnEnemies();

		// set the block to air AND make the powerUp unaccessable 
		setTile(tileType::AIR);
	}
	*/
}


// Update the sprite state of the tile
void PowerUp::update(const float& dt)
{
	// initiate the blowUp animation IF the tile has been destoryed 
	if (destroyed && type == tileType::POWERUP_HIDDEN)
	{
		// display one cycle of the blowUp animation
		blowUp.applyToSprite(mSprite);
		blowUp.update(dt);
		
		// if lsat the last frame of the animation
		if (blowUp.getCurrentFrame() == 5)
		{
			// reveal the powerUp
			revealPowerUp(); 
		}
	}
}

void PowerUp::collisions(Player& plr)
{
	//determine what type of power up it is & update player
	std::cout << "Obtained: ";
	switch (powerUpType)
	{
		case powerups::BOMB_UP:
			std::cout << "BOMB UP\n";
			plr.plusBomb();
			break;
		case powerups::FLAME_UP:
			std::cout << "FLAME UP\n";
			plr.plusFlame();
			break;
		case powerups::SPEED_UP:
			std::cout << "SPEED UP\n";
			plr.plusSpeed();
			break;
		case powerups::WALL_PASS:
			std::cout << "WALL PASS\n";
			plr.enableWallPass();
			break;
		case powerups::DETONATOR:
			std::cout << "DETONATOR\n";
			plr.enableDetonator();
			break;
		case powerups::BOMB_PASS:
			std::cout << "BOMB PASS\n";
			plr.enableBombPass();
			break;
		case powerups::FLAME_PASS:
			std::cout << "FLAME PASS\n";
			plr.enableFlamePass();
			break;
		case powerups::INVINCIBILITY:
			std::cout << "INVINCIBLE\n";
			plr.enableInvincible();
			break;
	}

	// set the tile to air once it has served its purpose
	setTile(tileType::AIR);
}


// if the powerUp has already been revealed && collides with a bomb,
// then spwan enemies and sel-destruct
void PowerUp::spawnEnemies()
{
	std::cout << "POWERUP DESTOYED, ENEMIES\n";
}
