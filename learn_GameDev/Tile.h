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
		Tile(const int&, const int&, const tileType::tileID&);
		~Tile();

		tileType::tileID getType();
		void setTile(const tileType::tileID&);
		void interact();

		void draw(sf::RenderWindow&) const;

		// collision detection
		void detectCollision(Player&,
			const tileType::tileID&, const tileType::tileID&,
			const tileType::tileID&, const tileType::tileID&);
	private:
		sf::Sprite tile; 
		//Animaiton blowUp

		tileType::tileID type;
};