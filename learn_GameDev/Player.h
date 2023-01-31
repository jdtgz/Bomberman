#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"


class Player
{
private:
	enum class AnimationIndex
	{
		WalkingLeft = 0, 
		WalkingRight,
		WalkingDown,
		WalkingUp,
		Count
	};
	public:
		Player(sf::Texture&);
		~Player(); 

		void handleInput(sf::Keyboard::Key, bool); 
		void draw(sf::RenderWindow&) const; 
		void update(sf::Time);


	private:
		// visual attributes
		sf::Sprite mSprite;
		Animation animations[int(AnimationIndex::Count)];
		AnimationIndex curAnimation;

		// movements attributes 
		float speed;
		sf::Vector2f velocity; 
};

