#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"
#include "Player.h"
#include "Animation.h"


namespace tileType 
{
	enum ID { AIR = 0, BRICK, TILE, DOOR, POWERUP };
}


class Tile
{
public:
	Tile() = default; 
	Tile(const int&, const int&, const tileType::ID&);
	~Tile();

	tileType::ID getType() const;
	void setTile(const tileType::ID&);
	void interact();

	void draw(sf::RenderWindow&) const;

		// collision detection
	void detectCollision(Player&,
		const tileType::ID&, const tileType::ID&,
		const tileType::ID&, const tileType::ID&);

	sf::Vector2f getPosition() const;

protected: 
	sf::Sprite sprite; 
	Animation blowUp; 
	tileType::ID type;
};