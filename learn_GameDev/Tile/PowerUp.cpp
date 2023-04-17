#include "PowerUp.h"


// Create a PowerUp at (x,y) and set its powerUpType 
PowerUp::PowerUp(const int& x, const int& y)
	: Tile(x, y, tileType::POWERUP_HIDDEN)
{
	// set the power up type randomly
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
			if (DEBUG)
				std::cout << "BOMB UP\n";
			break;
		case powerups::FLAME_UP:
			mSprite.setTextureRect({ 16, 48, 16, 16 });
			if (DEBUG)
				std::cout << "FLAME UP\n";
			break;
		case powerups::SPEED_UP:
			mSprite.setTextureRect({ 32, 48, 16, 16 });
			if (DEBUG)
				std::cout << "SPEED UP\n";
			break;
		case powerups::WALL_PASS:
			mSprite.setTextureRect({ 48, 48, 16, 16 });
			if (DEBUG)
				std::cout << "WALL PASS\n";
			break;
		case powerups::DETONATOR:
			mSprite.setTextureRect({ 64, 48, 16, 16 });
			if (DEBUG)
				std::cout << "DETONATOR\n";
			break;
		case powerups::BOMB_PASS:
			mSprite.setTextureRect({ 80, 48, 16, 16 });
			if (DEBUG)
				std::cout << "BOMB PASS\n";
			break;
		case powerups::FLAME_PASS:
			mSprite.setTextureRect({ 96, 48, 16, 16 });
			if (DEBUG)
				std::cout << "FLAME PASS\n";
			break;
		case powerups::INVINCIBILITY:
			mSprite.setTextureRect({ 112, 48, 16, 16 });
			if (DEBUG)
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
	// If the PowerUp is destroyed and it is hidden, initiate reveal sequence 
	if (destroyed && type == tileType::POWERUP_HIDDEN)
	{
		blowUp.applyToSprite(mSprite);
		blowUp.update(dt);
		
		// If animation is finished, reveal the powerUp sprite
		if (blowUp.getCurrentFrame() == 5)
			revealPowerUp(); 
	}
}


// Reveals the powerUp when it's is colliding with the player and destroys it
void PowerUp::collision(Player& plr)
{
	switch (powerUpType)
	{
		case powerups::BOMB_UP:
			if (DEBUG)
				std::cout << "BOMB UP\n";
			plr.plusBomb(); 
			break;
		case powerups::FLAME_UP: 
			if (DEBUG)
				std::cout << "FLAME UP\n";
			plr.plusFlame(); 
			break;
		case powerups::SPEED_UP: 
			if (DEBUG)
				std::cout << "SPEED UP\n";
			plr.plusSpeed(); 
			break; 
		case powerups::WALL_PASS:
			if (DEBUG)
				std::cout << "WALL PASS\n";
			plr.enableWallPass(); 
			break;
		case powerups::DETONATOR:
			if (DEBUG)
				std::cout << "DETONATOR\n";
			plr.enableDetonator();
			break;
		case powerups::BOMB_PASS:
			if (DEBUG)
				std::cout << "BOMB PASS\n";
			plr.enableBombPass(); 
			break;
		case powerups::FLAME_PASS:
			if (DEBUG)
				std::cout << "FLAME PASS\n";
			plr.enableFlamePass(); 
			break;
		case powerups::INVINCIBILITY:
			if (DEBUG)
				std::cout << "INVINCIBLE\n";
			plr.enableInvincible();
			break;
	}
	setTile(tileType::AIR);
}


// Spawns enemies in all directions from the current PowerUp tile
// powerUp tile must be revealed and colliding with an explosion
void PowerUp::spawnEnemies()
{
	if (DEBUG)
		std::cout << "POWERUP DESTOYED, ENEMIES\n";
}
