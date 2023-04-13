#pragma once
#include "../Game/Player.h"
#include "Tile.h"
#include "Bomb.h"


class PowerUp: public Tile
{
	public:
		// constructor/destructor
		PowerUp(const int& x, const int& y);
		~PowerUp(); 

		// visual functions 
		void revealPowerUp();

		// Collision response function
		virtual void interact(); 

		// game functions
		virtual void update(const float& dt); 
		virtual void collisions(Player& plr); 
		void spawnEnemies(); 
	private:
		enum powerups
		{
			BOMB_UP = 0, FLAME_UP, SPEED_UP, WALL_PASS, DETONATOR,
			BOMB_PASS, FLAME_PASS, INVINCIBILITY
		};

		// ID for type of attributes player should change
		int powerUpType; 
};