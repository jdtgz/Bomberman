#include "PowerUp.h"


PowerUp::PowerUp(int typ)
{
	sf::Texture* t = &TextureHolder::get(textures::ITEMS); 
	
	// initialize the "fake" sprite for the powerup
	mSprite.setTexture(*t); 
	mSprite.setTextureRect({ 16, 16, 16, 16 });

	revealed = false; 
	powerType = typ;  
}


PowerUp::~PowerUp()
{
}


// if collided with a flame from bomb, 
// then destroy old sprite & reveal actual sprite
void PowerUp::revealPowerUp()
{
	revealed = true; 
	switch (powerType)
	{
		case powerups::BombUp:
			mSprite.setTextureRect({ 0, 48, 16, 16 });
			std::cout << "BOMB UP\n";
			break;
		case powerups::FlameUp:
			mSprite.setTextureRect({ 16, 48, 16, 16 });
			std::cout << "FLAME UP\n";
			break;
		case powerups::SpeedUp:
			mSprite.setTextureRect({ 32, 48, 16, 16 });
			std::cout << "SPEED UP\n";
			break;
		case powerups::WallPass:
			mSprite.setTextureRect({ 48, 48, 16, 16 });
			std::cout << "WALL PASS\n";
			break;
		case powerups::Detonator:
			mSprite.setTextureRect({ 64, 48, 16, 16 });
			std::cout << "DETONATOR\n";
			break;
		case powerups::BombPass:
			mSprite.setTextureRect({ 80, 48, 16, 16 });
			std::cout << "BOMB PASS\n";
			break;
		case powerups::FlamePass:
			mSprite.setTextureRect({ 96, 48, 16, 16 });
			std::cout << "FLAME PASS\n";
			break;
		case powerups::Invincibility:
			mSprite.setTextureRect({ 112, 48, 16, 16 });
			std::cout << "INVINCIBLE\n";
			break;
	}
		
}


// aceess the player once & adjust its powerUp attirbutes
void PowerUp::applyPowerUp(Player& player)
{
	// determine what type of power up it is & update player
	switch (powerType)
	{
		case powerups::BombUp:
			std::cout << "BOMB UP\n";
			break;
		case powerups::FlameUp: 
			std::cout << "FLAME UP\n";
			break;
		case powerups::SpeedUp: 
			std::cout << "SPEED UP\n";
			break; 
		case powerups::WallPass:
			std::cout << "WALL PASS\n";
			break;
		case powerups::Detonator:
			std::cout << "DETONATOR\n";
			break;
		case powerups::BombPass:
			std::cout << "BOMB PASS\n";
			break;
		case powerups::FlamePass:
			std::cout << "FLAME PASS\n";
			break;
		case powerups::Invincibility:
			std::cout << "INVINCIBLE\n";
			break;
	}	
}


// detect the collision between a player and the powerup
// if revealed = false, push player back like a normal tile 
// if revealed = true, applyPowerUp
void PowerUp::detectCollisions(Player& plr)
{
}


// detects the collisions between the power up and flames from bomb
// if colliding & revealed = false, reveal true sprite of power up
void PowerUp::detectCollisions(Bomb& bomb)
{
}
