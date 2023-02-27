#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"
#include "Player.h"
#include "Animation.h"


namespace tileType 
{
	enum ID { AIR = 0, BRICK, TILE, DOOR, BOMB, POWERUP };
}


class Tile
{
	public:
		Tile(const int&, const int&, const tileType::ID&);
		~Tile();

		tileType::ID getType();
		void setTile(const tileType::ID&);
		void interact();

		void draw(sf::RenderWindow&) const;

		// collision detection
		void detectCollision(Player&,
			const tileType::ID&, const tileType::ID&,
			const tileType::ID&, const tileType::ID&);

		sf::Vector2f getPosition() const;
	private:
		sf::Sprite tile; 
		Animation blowUp; 

		tileType::ID type;
};