#pragma once
#include "Player.h"


class PowerUp
{
	private:
		enum powerType { BombUp, FireUp, SpeedUp, Detonator, WallPass, BombPass, FirePass, Invincibility };
	public:
		PowerUp(int); 
		~PowerUp(); 

		void applyPowerUp(Player&);

	private:
		int powerType; 
};