#pragma once
#include "Player.h"
#include "Bomb.h"


class PowerUp
{
public:
	PowerUp(const int&); 
	~PowerUp(); 

	// visual functions 
	void revealPowerUp();

	// utility funcitons 
	void applyPowerUp(Player&);
	void detectCollisions(Player&); 
	void detectCollisions(Bomb&); 
private:
	enum powerups
	{
		BOMB_UP = 0, FLAME_UP, SPEED_UP, WALL_PASS, DETONATOR,
		BOMB_PASS, FLAME_PASS, INVINCIBILITY
	};

	sf::Sprite sprite; 
	bool revealed; 
	int powerType; 
};