#pragma once
#include "TextureHolder.h"

class Bomb
{
public:
	Bomb(int x, int y, int range, bool timer);
	~Bomb();

	//Can accept sf::RenderWindow and sf::RenderTexture
	void draw(sf::RenderTarget& target);
	void explode();

private:
	void initAnimation();

	sf::Texture* m_explosion_sheet, *m_bomb_sheet;
	std::vector<sf::IntRect*> m_frames;
	sf::Time m_timer;

	bool m_exploded;
	int m_range;
};

