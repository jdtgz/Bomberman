#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"


class Player
{
	private:
		enum class AnimationIndex
		{
			WalkingLeft, WalkingRight, WalkingDown, WalkingUp, Count
		};

	public:
		Player();
		~Player(); 

		void setUpAnimations(sf::Texture&);
		void handleInput(sf::Keyboard::Key, bool); 
		void draw(sf::RenderWindow&) const; 
		void update(sf::Time);


	private:
		// visual attributes
		sf::Sprite mSprite;
		Animation animations[int(AnimationIndex::Count)];
		AnimationIndex cAnimation = AnimationIndex::WalkingRight; 
		
		// movements attributes 
		float speed;
		sf::Vector2f velocity; 
};

