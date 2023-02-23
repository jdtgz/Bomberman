#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"
#include "Player.h"


namespace tileType 
{
	enum tileID { AIR = 0, BRICK, TILE, DOOR, BOMB, POWERUP };
}


class Tile
{
	public:
		Tile(const int&, const int&, const int&);
		~Tile();

		int getType();
		void setTile(const int&);
		//void destroy();

		void draw(sf::RenderWindow&) const;

		// collision detection
		void detectCollision(Player&,
			const int&, const int&, const int&, const int&);
		//void detectCollision(Enemy&); 
	private:
		sf::Sprite tile; 
		//Animaiton blowUp

		int type;
};