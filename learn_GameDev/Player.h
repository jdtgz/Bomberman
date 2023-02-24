#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "TextureHolder.h"

namespace directions
{
	// directions 
	enum ID { RIGHT = 0, LEFT, UP, DOWN, COUNT };
}

class Player
{
	public:

		// constructor/destructor
		Player();
		~Player();

		// Given a key, do something
		void keyPressed(const sf::Keyboard::Key&);
		void keyReleased(const sf::Keyboard::Key&);

		// Draws player onto the screen
		void draw(sf::RenderWindow&) const;

		// updates attributes of player while in main
		void update(const float&);

		void setVelocity(const int&, const int&);

		float getSpeed() const;

		//Collision
		void move(const float&, const float&);
		void setCanMove(const int&, const bool&);
		sf::FloatRect getBoundingBox() const;
		sf::Vector2f getVelocity() const;
		sf::Sprite getSprite() const;

	private:
		// total animations of the player
		enum class animIndex
		{
			WALKING_LEFT = 0,
			WALKING_RIGHT,
			WALKING_DOWN,
			WALKING_UP,
			DEATH,
			COUNT
		};
		// visual attributes
		sf::Sprite sprite;
		Animation animations[int(animIndex::COUNT)];
		animIndex curAnimation;

		// movements attributes 
		float speed;
		int xVel = 0, yVel = 0;
		// Direction that the player is moving 
		bool movement[directions::COUNT];

		// Directions where player 'can possibly' move
		bool canMove[directions::COUNT]; 
};