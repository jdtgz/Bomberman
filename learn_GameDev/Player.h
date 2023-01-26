#pragma once
#include "SFML/Graphics.hpp"

class Player
{
	public:
		Player(); 
		~Player(); 

		// accessors 
		void setSprite(sf::Texture);
		
		void handleInput(sf::Keyboard::Key, bool); 
		void draw(sf::RenderWindow&) const; 
		void update(sf::Time);


	private:
		sf::Sprite mSprite;
		float speed; 
		sf::Vector2f velocity; 
};

