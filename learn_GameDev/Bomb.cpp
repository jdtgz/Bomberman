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

	m_frame_time = sf::seconds(0.1f);

	m_sprite.setPosition(x * 16, y * 16);
	m_position = sf::Vector2i(x, y);

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
	//Bomb
	if (!m_exploded)
	{
		m_sprite.setTexture(*m_bomb_sheet);
		m_sprite.setTextureRect(sf::IntRect(0,0,16,16));
		target.draw(m_sprite);
	}

	else
	{
		//Center explosion
		//Left explosion
		//Right explosion
		//Down explosion
		//Up explosion
		
	}
}


void Bomb::explode()
{
	m_exploded = true;
}


void Bomb::update(float dt)
{
	if (m_explode_clock.getElapsedTime() > m_timer && !m_exploded)
	{
		explode();
		m_explode_clock.restart();
	}
	else if (m_explode_clock.getElapsedTime() > m_frame_time)
	{
		m_current_frame = (m_current_frame + 1) % 4;

		m_explode_clock.restart();
	}
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


	//Continuous Vertical
	m_frames.push_back(new sf::IntRect(16 * 0, 16 * 5, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 1, 16 * 5, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 2, 16 * 5, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 3, 16 * 5, 16, 16));
	
	//Continuous Horizontal
	m_frames.push_back(new sf::IntRect(16 * 0, 16 * 6, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 1, 16 * 6, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 2, 16 * 6, 16, 16));
	m_frames.push_back(new sf::IntRect(16 * 3, 16 * 6, 16, 16));
}
