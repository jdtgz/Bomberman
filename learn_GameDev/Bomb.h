#pragma once
#include "TextureHolder.h"
#include "Animation.h"

class Bomb
{
public:
	Bomb(int x, int y, int range, bool timer);
	~Bomb();

	//Can accept sf::RenderWindow and sf::RenderTexture
	void draw(sf::RenderTarget& target);
	void explode();

	void update(float dt);

	int getRange() const { return m_range; }
	sf::Vector2i getPosition() const { return m_position; }
	bool getExploded() { return m_explosion_finished; };
	bool isColliding(sf::Sprite& sprite);

	//If the bomb itself is colliding
	bool isBombColliding(sf::Sprite& sprite);
	//Returns true if the explosion is colliding with sprite
	bool isExplosionColliding(sf::Sprite& sprite);
	//returns true only if explosion is active
	bool isEntityColliding(sf::Sprite& sprite);

	//Accepts a window and rendertexture
	void showCollisions(sf::RenderWindow& target);


private:
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
};

