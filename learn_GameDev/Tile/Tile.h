#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Graphics/TextureHolder.h"
#include "../Graphics/Animation.h"
#include "../Enum.h"
#include "../Game/Player.h"


class Tile : public Collidable
{
	public:
		// constuctors/destructors 
		Tile() = default; 
		Tile(const int& x, const int& y, const tileType::ID& typ);
		~Tile();
	
		// Game funcitons 
		virtual void interact();
		void draw(sf::RenderWindow& window);
		virtual void update(const float& dt);
		virtual void collision(Player& plr); 

		// Accessors/Modifiers 
		tileType::ID getType() const;
		void setTile(const tileType::ID& typ);
		sf::Vector2f getPosition() const;

	protected: 
		// visual attributes 
		sf::Sprite mSprite; 
		Animation blowUp; 

		// Type of the tile 
		tileType::ID type;

		// state of the block
		bool destroyed; 

};