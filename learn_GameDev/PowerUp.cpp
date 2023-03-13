#include "PowerUp.h"


PowerUp::PowerUp(const int& x, const int& y, const int& typ)
	: Tile(x, y, tileType::POWERUP)
{
	powerUpType = typ;
	revealed = false;
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
			sprite.setTextureRect({ 0, 48, 16, 16 });
			std::cout << "BOMB UP\n";
			break;
		case powerups::FLAME_UP:
			sprite.setTextureRect({ 16, 48, 16, 16 });
			std::cout << "FLAME UP\n";
			break;
		case powerups::SPEED_UP:
			sprite.setTextureRect({ 32, 48, 16, 16 });
			std::cout << "SPEED UP\n";
			break;
		case powerups::WALL_PASS:
			sprite.setTextureRect({ 48, 48, 16, 16 });
			std::cout << "WALL PASS\n";
			break;
		case powerups::DETONATOR:
			sprite.setTextureRect({ 64, 48, 16, 16 });
			std::cout << "DETONATOR\n";
			break;
		case powerups::BOMB_PASS:
			sprite.setTextureRect({ 80, 48, 16, 16 });
			std::cout << "BOMB PASS\n";
			break;
		case powerups::FLAME_PASS:
			sprite.setTextureRect({ 96, 48, 16, 16 });
			std::cout << "FLAME PASS\n";
			break;
		case powerups::INVINCIBILITY:
			sprite.setTextureRect({ 112, 48, 16, 16 });
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