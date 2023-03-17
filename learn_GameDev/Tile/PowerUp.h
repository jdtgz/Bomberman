#pragma once
#include "../Game/Player.h"
#include "Tile.h"
#include "Bomb.h"


class PowerUp: public Tile
{
public:
	// constructor/destructor
	PowerUp(const int&, const int&, const int&);
	~PowerUp(); 

	// visual functions 
	void revealPowerUp();
	virtual void interact(); 
	virtual void update(const float&); 

	// utility funcitons 
	void applyPowerUp(Player&);
	void spawnEnemies(); 

	// player collisions & powerUps involved 
	virtual void detectCollision(Player&,
		const tileType::ID&, const tileType::ID&,
		const tileType::ID&, const tileType::ID&);
private:
	enum powerups
	{
		BOMB_UP = 0, FLAME_UP, SPEED_UP, WALL_PASS, DETONATOR,
		BOMB_PASS, FLAME_PASS, INVINCIBILITY
	};

	bool revealed; 
	int powerUpType; 
};