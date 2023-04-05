#pragma once
#include "../Graphics/TextureHolder.h"
#include "../Graphics/Animation.h"

class Bomb
{
	public:
		// constructor/destructor
		Bomb(int x, int y, int range, bool timer);
		~Bomb();

		// Game functions 
		void draw(sf::RenderWindow& target);
		void update(float dt);
		void explode();

		// Accessors 
		int getRange()  const;
		sf::Vector2i getPosition()  const;
		bool getExploded();
		bool getExploding();
		std::vector<int> getExplodingRange();

		// Collision methods 
		bool isBombColliding(sf::Sprite& sprite);
		bool isExplosionColliding(sf::Sprite& sprite);
		bool isColliding(sf::Sprite& sprite);
		std::vector<std::vector<int>> 
			datamapExplosionCollision(std::vector<std::vector<int>>);
		bool isEntityColliding(sf::Sprite& sprite);
		void showCollisions(sf::RenderWindow& window);


	private:
		// Total Bomb animations
		enum class animationIndex
		{
			BOMB,
			CENTER,
			RIGHT,
			LEFT,
			UP,
			DOWN,
			HORIZONTAL,
			VERTICAL,
			COUNT
		};

		// initialize all spriteRects for animation
		void initAnimation();

		// Bomb/explosion sprite
		sf::Sprite m_sprite;
		
		// animations of the Bomb object
		Animation m_animations[(int)animationIndex::COUNT];

		// range of the bomb's explosion
		int m_range;
	
		// Tilemap coordinates, NOT sprite window coordinates
		sf::Vector2i m_position;

		// Before Explosion Sequence: 
		// Timer to explode bombs after being placed
		sf::Time m_timer;
		
		// Status of bomb's initiation of its explosion sequence
		bool m_exploded;

		// During Explosion Sequence:
		// Timer to for the animation of the explosion
		sf::Clock m_explode_clock;
		
		// tracks when the explosion animation is done
		bool m_explosion_finished;

		//How far the explosion can go.
		// [0] N -> [1] E -> [2] S -> [3] W
		//Default will be m_range
		int m_exploding_range[4];
};

