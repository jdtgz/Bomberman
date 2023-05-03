#pragma once
#include "SFML/Graphics.hpp"
#include "../Graphics/Animation.h"
#include "../Graphics/TextureHolder.h"
#include "../Tile/Bomb.h"
#include "Collidable.h"
#include "../Enum.h"

#include <SFML/Audio.hpp>


class Player : public Collidable
{
	public:
		Player();
		~Player();

		void hardReset();
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
		void setPosition(const float& x, const float& y);
		void updateMoves(int dir);
		sf::Vector2f getPosition() const;
		sf::Vector2i getTilePosition() const;
		sf::FloatRect getBoundingBox() const;
		sf::Sprite& getSprite();
		const bool* getCanMove() const { return movement; }


		int getBombCount() const; 
		void plusBomb();
		void minusBomb();

		int getFlameRange() const; 
		void plusFlame();
		void minusFlame();

		float getSpeed() const;
		void plusSpeed(); 
		void minusSpeed();

		bool hasWallPass() const;
		void enableWallPass();
		void disableWallPass();
		 
		bool hasDetonator() const;
		void enableDetonator();
		void disableDetonator();

		bool hasBombPass() const; 
		void enableBombPass(); 
		void disableBombPass();

		bool hasFlamePass() const; 
		void enableFlamePass(); 
		void disableFlamePass();

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
		float invincible; /* if number is more than 0, invincibility is active */

		//Is the player alive
		bool alive;

		//Has the player death animation ended
		bool dead;



		sf::Clock walk_sound_timer;
		//The difference between death_sound and just_died_sound
		//is that one (just_died_sound) is a short tune thats played after the player dies
		//and the other (death_sound) is the players death sound
		sf::Sound walk_sound, death_sound, just_died_sound;
		sf::SoundBuffer walk_horizontal_buffer, walk_vertical_buffer, death_buffer,
						just_died_buffer;
		bool justDiedPlayed; //So that the just_died_sound doesnt repeatedly play itself
};