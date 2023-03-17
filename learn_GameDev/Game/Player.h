#pragma once
#include "SFML/Graphics.hpp"
#include "../Graphics/Animation.h"
#include "../Graphics/TextureHolder.h"
#include "../Tile/Bomb.h"
#include "Collidable.h"
#include "../Enum.h"


class Player : public Collidable
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

		void detonate(); 
		sf::Vector2i getExplosionPosition();

		//Collision
		void move(const float&, const float&);
		void setCanMove(const int&, const bool&);
		sf::Vector2f getPosition();
		sf::FloatRect getBoundingBox() const;
		sf::Sprite getSprite() const;

		// powerup/player attributes 
		int getBombCount() const; 
		void plusBomb(); 

		int getFlameRange() const; 
		void plusFlame(); 

		float getSpeed() const;
		void plusSpeed(); 

		bool wallPass_status() const;
		void activate_wallPass(); 
		 
		bool detonator_status() const;
		void activate_detonator();

		bool bombPass_status() const; 
		void activate_bombPass(); 

		bool flamePass_status() const; 
		void activate_flamePass(); 

		bool invincible_status() const; 
		void activate_invincible(); 		

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
		int xVel, yVel;
		// Direction that the player is moving 
		bool movement[directions::COUNT];
		// Directions where player 'can possibly' move
		bool canMove[directions::COUNT];

		//bomb manager
		bool bombManager[10] = { false };
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