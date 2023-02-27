#include "Bomb.h"

Bomb::Bomb(int x, int y, int range, bool has_timer)
{
	m_bomb_sheet = &TextureHolder::get(textures::ITEMS);
	m_explosion_sheet = &TextureHolder::get(textures::EXPLOSION);
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
		m_animations[(int)animationIndex::BOMB].applyToSprite(m_sprite);
		target.draw(m_sprite);
	}

	else
	{
		//Center explosion
		m_animations[(int)animationIndex::CENTER].applyToSprite(m_sprite);
		target.draw(m_sprite);

		auto drawSprite = [&]() { target.draw(m_sprite); };

		for (int i = 0; i < m_range; i++)
		{
			m_sprite.setPosition(sf::Vector2f(m_position.x * 16, m_position.y * 16));
			sf::Vector2f leftPos = m_sprite.getPosition() - sf::Vector2f((m_sprite.getLocalBounds().width * (i + 1)) * 16, 0);
			sf::Vector2f rightPos = m_sprite.getPosition() + sf::Vector2f((m_sprite.getLocalBounds().width * (i + 1)) * 16, 0);
			sf::Vector2f downPos = m_sprite.getPosition() + sf::Vector2f(0, (m_sprite.getLocalBounds().height * (i + 1)) * 16);
			sf::Vector2f upPos = m_sprite.getPosition() - sf::Vector2f(0, (m_sprite.getLocalBounds().height * (i + 1)) * 16);

			if (i < m_range)
			{
				//Left explosion line
				m_animations[(int)animationIndex::HORIZONTAL].applyToSprite(m_sprite);
				m_sprite.setPosition(leftPos);
				drawSprite();

				//Right explosion line
				m_sprite.setPosition(rightPos);
				drawSprite();
				
				//Down explosion line
				m_animations[(int)animationIndex::VERTICAL].applyToSprite(m_sprite);
				m_sprite.setPosition(downPos);
				drawSprite();
				
				//Up explosion line
				m_sprite.setPosition(upPos);
				drawSprite();
			}

			else
			{
				//Left explosion end
				m_animations[(int)animationIndex::LEFT].applyToSprite(m_sprite);
				m_sprite.setPosition(leftPos);
				drawSprite();

				//Right explosion end
				m_animations[(int)animationIndex::RIGHT].applyToSprite(m_sprite);
				m_sprite.setPosition(rightPos);
				drawSprite();

				//Down explosion end
				m_animations[(int)animationIndex::DOWN].applyToSprite(m_sprite);
				m_sprite.setPosition(downPos);
				drawSprite();

				//Up explosion end
				m_animations[(int)animationIndex::UP].applyToSprite(m_sprite);
				m_sprite.setPosition(upPos);
				drawSprite();
			}
		}
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
	else if (m_explode_clock.getElapsedTime() > m_frame_time && m_exploded)
	{
		m_current_frame = (m_current_frame + 1) % 4;



		m_explode_clock.restart();
	}

	if (m_exploded)
	{

		if (m_animations[(int)animationIndex::CENTER].getCurrentFrame() < 4)
		{
			m_animations[(int)animationIndex::CENTER].update(dt);
			m_animations[(int)animationIndex::LEFT].update(dt);
			m_animations[(int)animationIndex::RIGHT].update(dt);
			m_animations[(int)animationIndex::UP].update(dt);
			m_animations[(int)animationIndex::DOWN].update(dt);
			m_animations[(int)animationIndex::HORIZONTAL].update(dt);
			m_animations[(int)animationIndex::VERTICAL].update(dt);
		}
		else
		{

		}
	}

	m_animations[0].update(dt);
}


void Bomb::initAnimation()
{
	//Loading frames from small explosion to large explosion
	sf::Texture* bomb = &TextureHolder::get(textures::ITEMS);
	sf::Texture* explosion = &TextureHolder::get(textures::EXPLOSION);

	m_animations[(int)animationIndex::BOMB].setUp(*bomb, 0, 16 * 0, 16, 16, 3);
	m_animations[(int)animationIndex::CENTER].setUp(*explosion, 0, 16 * 0, 16, 16, 4);
	m_animations[(int)animationIndex::RIGHT].setUp(*explosion, 0, 16 * 1, 16, 16, 4);
	m_animations[(int)animationIndex::LEFT].setUp(*explosion, 0, 16 * 2, 16, 16, 4);
	m_animations[(int)animationIndex::UP].setUp(*explosion, 0, 16 * 3, 16, 16, 4);
	m_animations[(int)animationIndex::DOWN].setUp(*explosion, 0, 16 * 4, 16, 16, 4);
	m_animations[(int)animationIndex::HORIZONTAL].setUp(*explosion, 0, 16 * 5, 16, 16, 4);
	m_animations[(int)animationIndex::VERTICAL].setUp(*explosion, 0, 16 * 5, 6, 16, 4);
}
