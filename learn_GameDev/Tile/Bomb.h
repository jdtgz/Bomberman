#pragma once
#include "../Graphics/TextureHolder.h"
#include "../Graphics/Animation.h"

class Bomb
{
public:
	Bomb(int x, int y, int range, bool timer);
	~Bomb();

	void draw(sf::RenderWindow& target);
	void explode();

	void update(float dt);

	int getRange() const { return m_range; }
	sf::Vector2i getPosition() const { return m_position; }
	bool getExploded() { return m_explosion_finished; };
	bool getExploding() { return m_exploded; };
	bool isColliding(sf::Sprite& sprite);

	//If the bomb itself is colliding
	bool isBombColliding(sf::Sprite& sprite);
	//Returns true if the explosion is colliding with sprite
	bool isExplosionColliding(sf::Sprite& sprite);
	std::vector<std::vector<int>> datamapExplosionCollision(std::vector<std::vector<int>>);
	//returns true only if explosion is active
	bool isEntityColliding(sf::Sprite& sprite);

	void showCollisions(sf::RenderWindow& window);


private:
	/* Main bomb info */
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

	void initAnimation();

	sf::Time m_timer;
	sf::Clock m_explode_clock;
	sf::Sprite m_sprite;
	//This is for tile map coordinates, separate from the sprite coordinates
	sf::Vector2i m_position;

	Animation m_animations[(int)animationIndex::COUNT];

	int m_current_frame;
	bool m_exploded;
	int m_range;
	bool m_explosion_finished;
	float scaled_size = 16 * 3;


	//How far the explosion can go.
	// [0] N -> [1] E -> [2] S -> [3] W
	//Default will be m_range
	int m_exploding_range[4];
};

