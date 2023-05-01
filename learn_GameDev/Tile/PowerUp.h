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

		int getPowerupType() const;

		// game functions
		virtual void interact(); 
		virtual void update(const float& dt); 
		virtual void collision(Player& plr); 
	private:
		enum powerups
		{
			BOMB_UP = 0, FLAME_UP, SPEED_UP, WALL_PASS, BOMB_PASS,
			DETONATOR, FLAME_PASS, INVINCIBILITY
		};

		// ID for type of attributes player should change
		int powerUpType; 
};