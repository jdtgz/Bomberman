#include "Bomb.h"

Bomb::Bomb(int x, int y, int range, bool has_timer)
{
	m_bomb_sheet = &TextureHolder::get(Textures::Items);
	m_explosion_sheet = &TextureHolder::get(Textures::Explosion);
	m_range = range;
	m_exploded = false;

	if (has_timer)
		m_timer = sf::seconds(2.5);
	else if (!has_timer)
		m_timer = sf::seconds(-1);

	initAnimation();
}

Bomb::~Bomb()
{
	while (m_frames.size() > 0)
	{
		delete m_frames.at(0);
		m_frames.erase(m_frames.begin());
	}
}

void Bomb::draw(sf::RenderTarget& target)
{
}

void Bomb::explode()
{
	m_exploded = true;
}

void Bomb::initAnimation()
{
	//Loading frames from small explosion to large explosion

	//Center Animation
	m_frames.push_back(new sf::IntRect(16 * 0, 16 * 0, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 1, 16 * 0, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 2, 16 * 0, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 3, 16 * 0, 16, 16));

	//Vertical Animation
	//Up

	m_frames.push_back(new sf::IntRect(16 * 0, 16 * 1, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 1, 16 * 1, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 2, 16 * 1, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 3, 16 * 1, 16, 16));

	//Down

	m_frames.push_back(new sf::IntRect(16 * 0, 16 * 3, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 1, 16 * 3, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 2, 16 * 3, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 3, 16 * 3, 16, 16));

	//Horizontal Animation
	//Continuous

	//Up

	m_frames.push_back(new sf::IntRect(16 * 0, 16 * 2, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 1, 16 * 2, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 2, 16 * 2, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 3, 16 * 2, 16, 16));

	//Down

	m_frames.push_back(new sf::IntRect(16 * 0, 16 * 4, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 1, 16 * 4, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 2, 16 * 4, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 3, 16 * 4, 16, 16));
}
