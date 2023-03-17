#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"
#include "Player.h"
#include "Animation.h"
#include "Enum.h"


class Tile : public Collidable
{
public:
	Tile() = default; 
	Tile(const int&, const int&, const tileType::ID&);
	~Tile();

	// tile identification functions
	tileType::ID getType() const;
	void setTile(const tileType::ID&);
	
	// based on a collision, take the appropriate action(s) 
	virtual void interact();

	// game funcitons 
	void draw(sf::RenderWindow&) const;
	virtual void update(const float&); 

	// collision detection
	virtual void detectCollision(Player&,
		const tileType::ID&, const tileType::ID&,
		const tileType::ID&, const tileType::ID&);

	sf::Vector2f getPosition() const;

protected: 
	// visual attributes 
	sf::Sprite mSprite; 
	Animation blowUp; 

	// functionality attributes  
	tileType::ID type;
	bool destroyed; 

};