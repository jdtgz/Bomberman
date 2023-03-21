#include "Bomb.h"
//Uncomment this to use the new drawing method
//#define NEW_DRAWING

Bomb::Bomb(int x, int y, int range, bool has_timer)
{
	m_range = range;

	for (int i = 0; i < 4; i++)
		m_exploding_range[i] = m_range;

	m_exploded = false;
	m_explosion_finished = false;

	if (has_timer)
		m_timer = sf::seconds(2.5);
	else if (!has_timer)
		m_timer = sf::seconds(-1);

	m_sprite.setPosition(((x - 1) * 48), ((y + 1) * 48)); //Bomb position is leftmost explosion 
	m_position = sf::Vector2i(x, y);

	initAnimation();
}


Bomb::~Bomb()
{
}


void Bomb::draw(sf::RenderWindow& target)
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
		sf::Vector2f centerPos(((m_position.x - 1) * 48), ((m_position.y + 1) * 48));
		drawSprite(centerPos, animationIndex::CENTER);

		/*		Go to start of this file for an explanation for this		*/
#ifdef NEW_DRAWING
		//Draw up
		for (int i = 1; i < m_exploding_range[0]; i++)
		{
			if (i < m_exploding_range[0] - 1)
				drawSprite(sf::Vector2f(centerPos.x - (48 * i), centerPos.y), animationIndex::VERTICAL);
			else
				drawSprite(sf::Vector2f(centerPos.x - (48 * i), centerPos.y), animationIndex::UP);
		}
		//Draw right
		for (int i = 1; i < m_exploding_range[1]; i++)
		{
			if (i < m_exploding_range[1] - 1)
				drawSprite(sf::Vector2f(centerPos.x, centerPos.y + (48 * i)), animationIndex::HORIZONTAL);
			else
				drawSprite(sf::Vector2f(centerPos.x - (48 * i), centerPos.y), animationIndex::RIGHT);
		}
		//Draw down
		for (int i = 1; i < m_exploding_range[2]; i++)
		{
			if (i < m_exploding_range[2] - 1)
				drawSprite(sf::Vector2f(centerPos.x + (48 * i), centerPos.y), animationIndex::VERTICAL);
			else
				drawSprite(sf::Vector2f(centerPos.x - (48 * i), centerPos.y), animationIndex::DOWN);
		}
		//Draw left
		for (int i = 1; i < m_exploding_range[3]; i++)
		{
			if (i < m_exploding_range[3] - 1)
				drawSprite(sf::Vector2f(centerPos.x, centerPos.y - (48 * i)), animationIndex::HORIZONTAL);
			else
				drawSprite(sf::Vector2f(centerPos.x - (48 * i), centerPos.y), animationIndex::LEFT);
		}
#else
		for (int i = 0; i < m_range; i++)
		{
			int k = i + 1;
			sf::Vector2f leftPos = sf::Vector2f(centerPos.x - (48 * k), centerPos.y);
			sf::Vector2f rightPos = sf::Vector2f(centerPos.x + (48 * k), centerPos.y);
			sf::Vector2f downPos = sf::Vector2f(centerPos.x, centerPos.y + (48 * k));
			sf::Vector2f upPos = sf::Vector2f(centerPos.x, centerPos.y - (48 * k));

			if (i < m_range - 1)
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
#endif
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
	if (m_exploded && !m_explosion_finished)
	{
		sf::Vector2f centerPos(((m_position.x - 1) * 48), ((m_position.y + 1) * 48));

		//returns a boolean depending on if the sprites 
		//bounding box intersects with bomb
		auto intersectionCheck = [&](sf::Vector2f positionToCheck) -> bool
		{
			bool result = false;
			m_sprite.setPosition(positionToCheck);
			if (sprite.getGlobalBounds().intersects(m_sprite.getGlobalBounds()))
				result = true;
			m_sprite.setPosition(centerPos);
			return result;
		};

		if (intersectionCheck(centerPos))
			return true;

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
	}
	else if (!m_explosion_finished)
	{
		return m_sprite.getGlobalBounds().intersects(sprite.getGlobalBounds());
	}

	return false;
}

bool Bomb::isBombColliding(sf::Sprite& sprite)
{
	if (sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
		return true;
	return false;
}

bool Bomb::isExplosionColliding(sf::Sprite& sprite)
{
	if (m_exploded && !m_explosion_finished)
	{
		sf::Vector2f centerPos(((m_position.x - 1) * 48), ((m_position.y + 1) * 48));

		//returns a boolean depending on if the sprites 
		//bounding box intersects with bomb
		auto intersectionCheck = [&](sf::Vector2f positionToCheck) -> bool
		{
			bool result = false;
			m_sprite.setPosition(positionToCheck);
			if (sprite.getGlobalBounds().intersects(m_sprite.getGlobalBounds()))
				result = true;
			m_sprite.setPosition(centerPos);
			return result;
		};

		if (intersectionCheck(centerPos))
			return true;

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
	}
	else if (!m_explosion_finished)
	{
		return m_sprite.getGlobalBounds().intersects(sprite.getGlobalBounds());
	}

	return false;
}

bool Bomb::datamapExplosionCollision(int datamap[31][15])
{
	bool result = false;

	//Check up
	for (int i = 1; i < m_range; i++)
	{
		if (m_position.y - i > 0)
		{
			if (datamap[m_position.x][m_position.y - i] != 0)
			{
				m_exploding_range[0] = i;
				result = true;

				if (datamap[m_position.x][m_position.y - i] != 2)
				{
					datamap[m_position.x][m_position.y - i] = 0;
				}
			}
		}
		else
			m_exploding_range[0] = i;
	}
	//Check right
	for (int i = 1; i < m_range; i++)
	{
		if (m_position.x + i < 31)
		{
			if (datamap[m_position.x+i][m_position.y] != 0)
			{
				m_exploding_range[1] = i;
				result = true;

				if (datamap[m_position.x+1][m_position.y] != 2)
				{
					datamap[m_position.x+1][m_position.y] = 0;
				}
			}
		}
		else
			m_exploding_range[1] = i;
	}
	//Check down
	for (int i = 1; i < m_range; i++)
	{
		if (m_position.y + i < 15)
		{
			if (datamap[m_position.x][m_position.y + i] != 0)
			{
				m_exploding_range[2] = i;
				result = true;

				if (datamap[m_position.x][m_position.y + i] != 2)
				{
					datamap[m_position.x][m_position.y + i] = 0;
				}
			}
		}
		else
			m_exploding_range[2] = i;
	}
	//Check left
	for (int i = 1; i < m_range; i++)
	{
		if (m_position.x - i > 0)
		{
			if (datamap[m_position.x-1][m_position.y] != 0)
			{
				m_exploding_range[3] = i;
				result = true;

				if (datamap[m_position.x-1][m_position.y] != 2)
				{
					datamap[m_position.x-1][m_position.y] = 0;
				}
			}
		}
		else
			m_exploding_range[3] = i;
	}

	return result;
}

bool Bomb::isEntityColliding(sf::Sprite& sprite)
{
	return false;
}

void Bomb::showCollisions(sf::RenderWindow& target)
{
	sf::Vector2f centerPos(((m_position.x - 1) * 48), ((m_position.y + 1) * 48));
	m_sprite.setPosition(centerPos);
	target.draw(m_sprite);

	//Loop through the range of the bomb
	for (int i = 0; i < m_range; i++)
	{
		int k = i + 1;
		sf::Vector2f leftPos = sf::Vector2f(centerPos.x - (48 * k), centerPos.y);
		sf::Vector2f rightPos = sf::Vector2f(centerPos.x + (48 * k), centerPos.y);
		sf::Vector2f downPos = sf::Vector2f(centerPos.x, centerPos.y + (48 * k));
		sf::Vector2f upPos = sf::Vector2f(centerPos.x, centerPos.y - (48 * k));


		m_sprite.setPosition(leftPos);
		target.draw(m_sprite);

		m_sprite.setPosition(rightPos);
		target.draw(m_sprite);

		m_sprite.setPosition(downPos);
		target.draw(m_sprite);

		m_sprite.setPosition(upPos);
		target.draw(m_sprite);
	}
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
