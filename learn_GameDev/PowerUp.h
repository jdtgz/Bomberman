#pragma once
#include "Player.h"
#include "Tile.h"
#include "Bomb.h"


class PowerUp: public Tile
{
	public:
		// constructor/destructor
		PowerUp(const int&); 
		~PowerUp(); 

		// visual functions 
		void revealPowerUp();
		void setPowerType(const int&);

		// utility funcitons 
		void applyPowerUp(Player&);
		void spawnEnemies(); 
	private:
		enum powerups
		{
			BOMB_UP = 0, FLAME_UP, SPEED_UP, WALL_PASS, DETONATOR,
			BOMB_PASS, FLAME_PASS, INVINCIBILITY
		};

		bool revealed; 
		int powerUpType; 
};