#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "TextureHolder.h"
#include "Bomb.h"


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
		sf::Vector2i keyPressed(const sf::Keyboard::Key&);
		void keyReleased(const sf::Keyboard::Key&);

		// Draws player onto the screen
		void draw(sf::RenderWindow&) const;

		// updates attributes of player while in main
		void update(const float&);
		void setVelocity(const int&, const int&);
		sf::Vector2f getVelocity() const;
		float getSpeed() const;
		void detonate(); 
		sf::Vector2i getExplotionPosition();

		//Collision
		void move(const float&, const float&);
		void setCanMove(const int&, const bool&);
		sf::Vector2f getPosition();
		sf::FloatRect getBoundingBox() const;
		sf::Sprite getSprite() const;

		// powerup/player attributes 
		int getBombCount(); 
		void plusBombCount(); 

		int getFlameRange(); 
		void plusFlameRange(); 

		bool wallPass_status();
		void activate_wallPass(); 

		bool detonator_status();
		void activate_detonator();

		bool bombPass_status(); 
		void activate_bombPass(); 

		bool flamePass_status(); 
		void activate_flamePass(); 

		bool invincible_status(); 
		void activate_invincible(); 
		void stop_invincible(); 
		

	private:
		// Visual attributes
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
		sf::Sprite sprite;
		Animation animations[int(animIndex::COUNT)];
		animIndex curAnimation;


		// Movement attributes 
		int xVel = 0, yVel = 0;
		// Direction that the player is moving 
		bool movement[directions::COUNT];
		// Directions where player 'can possibly' move
		bool canMove[directions::COUNT];

		//bomb manager
		bool bombManager[10] = {false};
		std::vector<Bomb*> bombs;

		// player attirbutes 
		int bombCount; 
		int flameRange; 
		float speed;
		bool wallPass; 
		bool detonator; 
		bool bombPass;
		bool flamePass; 
		bool invincible; 

};