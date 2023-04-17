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
		Player();
		~Player();

		void reset();

		bool isAlive() const;
		bool completedDeathAnim() const;
		void die();


		void keyPressed(const sf::Keyboard::Key& key);
		void keyReleased(const sf::Keyboard::Key& key);


		void draw(sf::RenderWindow& window) const;


		void update(const float& dt);
		void setVelocity(const int& newX, const int& newY);
		sf::Vector2f getVelocity() const;


		void move(const float& x, const float& y);
		void setCanMove(const int& dir, const bool& v);
		void updateMoves(int dir);
		sf::Vector2f getPosition() const;
		sf::Vector2i getTilePosition() const;
		sf::FloatRect getBoundingBox() const;
		sf::Sprite& getSprite();


		int getBombCount() const; 
		void plusBomb(); 

		int getFlameRange() const; 
		void plusFlame(); 

		float getSpeed() const;
		void plusSpeed(); 

		bool hasWallPass() const;
		void enableWallPass();
		 
		bool hasDetonator() const;
		void enableDetonator();

		bool hasBombPass() const; 
		void enableBombPass(); 

		bool hasFlamePass() const; 
		void enableFlamePass(); 

		bool isInvincible() const; 
		void enableInvincible(); 		

	private:
		enum class animIndex
		{
			WALKING_UP = 0,
			WALKING_RIGHT,
			WALKING_DOWN,
			WALKING_LEFT,
			DEATH,
			COUNT
		};
		sf::Sprite sprite;
		Animation animations[int(animIndex::COUNT)];
		animIndex curAnimation;

		int xVel, yVel;
		bool movement[direction::COUNT];
		bool canMove[direction::COUNT];

		int bombCount; 
		int flameRange;
		float speed;
		bool wallPass; 
		bool detonator; 
		bool bombPass;
		bool flamePass; 
		bool invincible;

		//Is the player alive
		bool alive;

		//Has the player death animation ended
		bool dead;
};