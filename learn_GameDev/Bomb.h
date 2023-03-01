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

	sf::Texture* m_explosion_sheet, * m_bomb_sheet;
	sf::Time m_timer;
	sf::Clock m_explode_clock;
	sf::Sprite m_sprite;
	sf::Vector2i m_position;

	Animation m_animations[(int)animationIndex::COUNT];

	int m_current_frame;
	bool m_exploded;
	int m_range;

	bool m_explosion_finished;

	float scaled_size = 16 * 3;
};

