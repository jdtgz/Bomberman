#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"


class Player
{
	public:
		Player(sf::Texture&);
		~Player(); 

		void handleInput(sf::Keyboard::Key, bool); 
		void draw(sf::RenderWindow&) const; 
		void update(sf::Time);


	private:
		// visual attributes
		sf::Sprite mSprite;
		Animation rightWalk; 
		
		// movements attributes 
		float speed;
		sf::Vector2f velocity; 
};

