#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"

enum class AnimationIndex
{
	WalkingUp, WalkingDown, WalkingRight, WalkingLeft, Count
};

class Player
{
	public:
		Player();
		Player(sf::Texture&); 
		~Player(); 

		// accessors 
		void setSprite(sf::Texture&);
		
		void handleInput(sf::Keyboard::Key, bool); 
		void draw(sf::RenderWindow&) const; 
		void update(sf::Time);


	private:
		sf::Sprite mSprite;
		Animation animations[int(AnimationIndex::Count)]; 
		float speed; 
		sf::Vector2f velocity; 
};

