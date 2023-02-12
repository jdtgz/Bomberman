#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"


class Player
{
private:
	// total animations of the player
	enum class AnimationIndex
	{
		WalkingLeft = 0, 
		WalkingRight,
		WalkingDown,
		WalkingUp,
		Count
	};
	public:
		// constructor/destructor
		Player(sf::Texture&);
		~Player(); 

		// Given a key, do something
		void handleInput(sf::Keyboard::Key, bool); 

		// Draws player onto the screen
		void draw(sf::RenderWindow&) const; 

		// updates attributes of player while in main
		void update(float);


	private:
		// visual attributes
		sf::Sprite mSprite;
		Animation animations[int(AnimationIndex::Count)];
		AnimationIndex curAnimation;

		// movements attributes 
		float speed;
		sf::Vector2f velocity; 
};

