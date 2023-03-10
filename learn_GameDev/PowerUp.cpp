#include "PowerUp.h"


PowerUp::PowerUp(const int& typ)
{
	// initialize the "fake" mSprite
	mSprite.setTexture(TextureHolder::get(textures::ITEMS)); 
	setTile(tileType::BRICK);

	// set the "real" type to ensure it is not treated like a brick in level
	type = tileType::POWERUP; 

	// set the type of powerup it is 
	powerUpType = typ; 
}


PowerUp::~PowerUp()
{
}


// if collided with a flame from bomb, 
// then destroy old mSprite & reveal actual mSprite
void PowerUp::revealPowerUp()
{
	revealed = true;
	std::cout << "Revealed: ";
	switch (type)
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
		
}


// aceess the player once & adjust its powerUp attirbutes
void PowerUp::applyPowerUp(Player& player)
{
	//determine what type of power up it is & update player
	std::cout << "Obtained: ";
	switch (type)
	{
		case powerups::BOMB_UP:
			std::cout << "BOMB UP\n";
			break;
		case powerups::FLAME_UP: 
			std::cout << "FLAME UP\n";
			break;
		case powerups::SPEED_UP: 
			std::cout << "SPEED UP\n";
			break; 
		case powerups::WALL_PASS:
			std::cout << "WALL PASS\n";
			break;
		case powerups::DETONATOR:
			std::cout << "DETONATOR\n";
			break;
		case powerups::BOMB_PASS:
			std::cout << "BOMB PASS\n";
			break;
		case powerups::FLAME_PASS:
			std::cout << "FLAME PASS\n";
			break;
		case powerups::INVINCIBILITY:
			std::cout << "INVINCIBLE\n";
			break;
	}	
}


// if the powerUp has already been revealed && collides with a bomb,
// then spwan enemies and sel-destruct
void PowerUp::spawnEnemies()
{
}