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


// reveals the sprite of the powerup or spawns enemies based on currernt status 
void PowerUp::interact()
{
	if (revealed == true)
		spawnEnemies();
	else
		revealed = true; 
}


void PowerUp::update(const float& dt)
{
	// initiate the blowUp animation IF the tile has been destoryed 
	if (destroyed == true && type == tileType::POWERUP)
	{
		// display one cycle of the blowUp animation
		while (blowUp.getCurrentFrame() <= 6)
		{
			blowUp.applyToSprite(mSprite);
			blowUp.update(dt);
		}

		// reveal the true sprite of the powerUp
		revealPowerUp(); 
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
			player.plusBomb(); 
			break;
		case powerups::FLAME_UP: 
			std::cout << "FLAME UP\n";
			player.plusFlame(); 
			break;
		case powerups::SPEED_UP: 
			std::cout << "SPEED UP\n";
			player.plusSpeed(); 
			break; 
		case powerups::WALL_PASS:
			std::cout << "WALL PASS\n";
			player.activate_wallPass(); 
			break;
		case powerups::DETONATOR:
			std::cout << "DETONATOR\n";
			player.activate_detonator();
			break;
		case powerups::BOMB_PASS:
			std::cout << "BOMB PASS\n";
			player.activate_bombPass(); 
			break;
		case powerups::FLAME_PASS:
			std::cout << "FLAME PASS\n";
			player.activate_flamePass(); 
			break;
		case powerups::INVINCIBILITY:
			std::cout << "INVINCIBLE\n";
			player.activate_invincible(); 
			break;
	}	

	// set the tile to air once it has served its purpose
	setTile(tileType::AIR); 
}


// if the powerUp has already been revealed && collides with a bomb,
// then spwan enemies and sel-destruct
void PowerUp::spawnEnemies()
{
}


// detects the collisions between the player and the powerUp, acts like a normal tile unless it is revealed
void PowerUp::detectCollision(Player& plr, const tileType::ID& u, const tileType::ID& d,
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