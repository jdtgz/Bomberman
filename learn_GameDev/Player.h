#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"


class Player
{
private:
	// total animations of the player
	enum class AnimationIndex
	{
		WALKING_LEFT = 0, 
		WALKING_RIGHT,
		WALKING_DOWN,
		WALKING_UP,
		COUNT
	};
	public:
		// constructor/destructor
		Player(sf::Texture&);
		~Player(); 

		// Given a key, do something
		void keyPressed(sf::Keyboard::Key); 
		void keyReleased(sf::Keyboard::Key);

		// Draws player onto the screen
		void draw(sf::RenderWindow&) const; 

		// updates attributes of player while in main
		void update(float);


	private:
		// visual attributes
		sf::Sprite mSprite;
		Animation animations[int(AnimationIndex::COUNT)];
		AnimationIndex curAnimation;

		// movements attributes 
		float speed;
		bool left = false, right = false, up = false, down = false;
};