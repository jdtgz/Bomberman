#include "Bomb.h"

Bomb::Bomb(int x, int y, int range, bool has_timer)
{
	m_bomb_sheet = &TextureHolder::get(textures::ITEMS);
	m_explosion_sheet = &TextureHolder::get(textures::EXPLOSION);
	m_range = range;
	m_exploded = false;
	m_explosion_finished = false;

	if (has_timer)
		m_timer = sf::seconds(2.5);
	else if (!has_timer)
		m_timer = sf::seconds(-1);

	m_sprite.setPosition(8 + ((x - 1) * 48), 8 + ((y + 1) * 48)); //Bomb position is leftmost explosion 
	m_position = sf::Vector2i(x, y);

	initAnimation();
}


Bomb::~Bomb()
{
}


void Bomb::draw(sf::RenderTarget& target)
{
	//Bomb
	if (!m_exploded)
	{
		m_animations[(int)animationIndex::BOMB].applyToSprite(m_sprite);
		target.draw(m_sprite);
	}

	else if (!m_explosion_finished)
	{
		//Decrease line count with lambda function to draw sprites
		auto drawSprite = [&](const sf::Vector2f position, animationIndex type)
		{
			m_animations[(int)type].applyToSprite(m_sprite);
			m_sprite.setPosition(position);
			target.draw(m_sprite);
		};

		//Center explosion
		sf::Vector2f centerPos(8 + ((m_position.x - 1) * 48), 8 + ((m_position.y+1) * 48));
		drawSprite(centerPos, animationIndex::CENTER);

		for (int i = 0; i < m_range; i++)
		{
			int k = i + 1;
			sf::Vector2f leftPos = sf::Vector2f(centerPos.x - (48 * k), centerPos.y);
			sf::Vector2f rightPos = sf::Vector2f(centerPos.x + (48 * k), centerPos.y);
			sf::Vector2f downPos = sf::Vector2f(centerPos.x, centerPos.y + (48 * k));
			sf::Vector2f upPos = sf::Vector2f(centerPos.x, centerPos.y - (48 * k));

			if (i < m_range-1)
			{
				//Left explosion line
				drawSprite(leftPos, animationIndex::HORIZONTAL);

				//Right explosion line
				drawSprite(rightPos, animationIndex::HORIZONTAL);
				
				//Down explosion line
				drawSprite(downPos, animationIndex::VERTICAL);
				
				//Up explosion line
				drawSprite(upPos, animationIndex::VERTICAL);
			}
			else
			{
				//Left explosion end
				drawSprite(leftPos, animationIndex::LEFT);

				//Right explosion end
				drawSprite(rightPos, animationIndex::RIGHT);

				//Down explosion end
				drawSprite(downPos, animationIndex::DOWN);

				//Up explosion end
				drawSprite(upPos, animationIndex::UP);
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
	if (m_explode_clock.getElapsedTime() > m_timer && !m_exploded && m_timer.asSeconds() != -1)
	{
		explode();
		m_explode_clock.restart();
	}

	if (m_exploded && !m_explosion_finished)
	{

		if (m_animations[(int)animationIndex::CENTER].getCurrentFrame() < 3)
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
			m_explosion_finished = true;
		}
	}

	m_animations[0].update(dt);
}

bool Bomb::isColliding(sf::Sprite& sprite)
{
	sf::Vector2f centerPos(8 + ((m_position.x - 1) * 48), 8 + ((m_position.y + 1) * 48));

	//returns a boolean depending on if the sprites bounding box intersects with bomb
	auto intersectionCheck = [&](sf::Vector2f positionToCheck) -> bool
	{
		m_sprite.setPosition(positionToCheck);
		if (sprite.getGlobalBounds().intersects(m_sprite.getGlobalBounds()))
			return true;
		m_sprite.setPosition(centerPos);
	};

	intersectionCheck(centerPos);

	//Loop through the range of the bomb
	for (int i = 0; i < m_range; i++)
	{
		int k = i + 1;
		sf::Vector2f leftPos = sf::Vector2f(centerPos.x - (48 * k), centerPos.y);
		sf::Vector2f rightPos = sf::Vector2f(centerPos.x + (48 * k), centerPos.y);
		sf::Vector2f downPos = sf::Vector2f(centerPos.x, centerPos.y + (48 * k));
		sf::Vector2f upPos = sf::Vector2f(centerPos.x, centerPos.y - (48 * k));

		if (intersectionCheck(leftPos) || intersectionCheck(rightPos) ||
			intersectionCheck(downPos) || intersectionCheck(upPos))
			return true;
	}
	return false;
}


void Bomb::initAnimation()
{
	//Loading frames from small explosion to large explosion
	sf::Texture* bomb = &TextureHolder::get(textures::ITEMS);
	sf::Texture* explosion = &TextureHolder::get(textures::EXPLOSION);

	m_animations[(int)animationIndex::BOMB].setUp(*bomb, 0, 16 * 0, 16, 16, 3);
	m_animations[(int)animationIndex::CENTER].setUp(*explosion, 0, 16 * 0, 16, 16, 4);
	m_animations[(int)animationIndex::UP].setUp(*explosion, 0, 16 * 1, 16, 16, 4);
	m_animations[(int)animationIndex::RIGHT].setUp(*explosion, 0, 16 * 2, 16, 16, 4);
	m_animations[(int)animationIndex::DOWN].setUp(*explosion, 0, 16 * 3, 16, 16, 4);
	m_animations[(int)animationIndex::LEFT].setUp(*explosion, 0, 16 * 4, 16, 16, 4);
	m_animations[(int)animationIndex::VERTICAL].setUp(*explosion, 0, 16 * 5, 16, 16, 4);
	m_animations[(int)animationIndex::HORIZONTAL].setUp(*explosion, 0, 16 * 6, 16, 16, 4);
}
