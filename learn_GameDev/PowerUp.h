#pragma once
#include "Player.h"
#include "Bomb.h"


class PowerUp
{
	private:
		enum powerups 
		{ BombUp, FlameUp, SpeedUp, WallPass, Detonator,
			BombPass, FlamePass, Invincibility };
	public:
		PowerUp(int); 
		~PowerUp(); 

		// visual functions 
		void revealPowerUp();

		// utility funcitons 
		void applyPowerUp(Player&);
		void detectCollisions(Player&); 
		void detectCollisions(Bomb&); 
	private:
		sf::Sprite mSprite; 
		bool revealed; 
		int powerType; 
};