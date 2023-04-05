#include "Bomb.h"

// Creates a bomb at (x,y)
// @param range -> number of tiles explosion reaches in all directions 
// @param has_timer -> determines if explosion will explode on a timer
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

	m_sprite.setPosition(((x - 1) * 48), ((y + 1) * 48)); //Bomb position is left most explosion 
	m_position = sf::Vector2i(x, y);

	initAnimation();
}


// destructor
Bomb::~Bomb()
{
}


// draws the bomb onto the game window
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



		//North drawing
		for (int i = 0; i < m_exploding_range[0]; i++)
		{
			int k = i + 1;
			if (k < m_exploding_range[0])
			{
				drawSprite(sf::Vector2f(centerPos.x, centerPos.y - (48 * k)), animationIndex::VERTICAL);
			}
			else
				drawSprite(sf::Vector2f(centerPos.x, centerPos.y - (48 * k)), animationIndex::UP);
		}

		//South drawing
		for (int i = 0; i < m_exploding_range[2]; i++)
		{
			int k = i + 1;
			if (k < m_exploding_range[2])
			{
				drawSprite(sf::Vector2f(centerPos.x, centerPos.y + (48 * k)), animationIndex::VERTICAL);
			}
			else
				drawSprite(sf::Vector2f(centerPos.x, centerPos.y + (48 * k)), animationIndex::DOWN);
		}

		//East drawing
		for (int i = 0; i < m_exploding_range[1]; i++)
		{
			int k = i + 1;
			if (k < m_exploding_range[1])
			{
				drawSprite(sf::Vector2f(centerPos.x + (48 * k), centerPos.y), animationIndex::HORIZONTAL);
			}
			else
				drawSprite(sf::Vector2f(centerPos.x + (48 * k), centerPos.y), animationIndex::RIGHT);
		}

		//West drawing
		for (int i = 0; i < m_exploding_range[3]; i++)
		{
			int k = i + 1;

			if (k < m_exploding_range[3])
			{
				drawSprite(sf::Vector2f(centerPos.x - (48 * k), centerPos.y), animationIndex::HORIZONTAL);
			}
			else
				drawSprite(sf::Vector2f(centerPos.x - (48 * k), centerPos.y), animationIndex::LEFT);
		}
	}
}


// updates the bomb's state
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


// Initiates the explosion sequence for the bomb
void Bomb::explode()
{
	m_exploded = true;
}


// return range of explosion
int Bomb::getRange() const 
{ 
	return m_range; 
}


// return position of bomb (center of explosion)
sf::Vector2i Bomb::getPosition() const
{ 
	return m_position; 
}


// returns if bomb has initialized its explosions sequence 
bool Bomb::getExploded()
{ 
	return m_explosion_finished; 
}


// returns if the explosion sequence is still active
bool Bomb::getExploding()
{
	return m_exploded;
}

std::vector<int> Bomb::getExplodingRange()
{
	std::vector<int> range;
	
	for (int i = 0; i < 4; i++)
		range.push_back(m_exploding_range[i]);

	return range;
}


// *Needs explanation*
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

// Bomb collisions with other objects 
bool Bomb::isBombColliding(sf::Sprite& sprite)
{
	if (sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
		return true;
	return false;
}


// Explosion collisions with other objects 
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


// updates datamap after explosion takes affect on environment
std::vector<std::vector<int>> 
Bomb::datamapExplosionCollision(std::vector<std::vector<int>> datamap)
{
	bool stop = false;

	for (int i = 0; i < 4; i++)
		m_exploding_range[i] = 0;
	for (int i = 0; i < 4; i++)
		std::cout << m_exploding_range[i] << " - ";
	std::cout << '\n';

	//Check up
	for (int i = 1; i <= m_range; i++)
	{
		if (m_position.y - i > 0)
		{
			std::cout << "can check up\n";
			if (datamap[m_position.x][m_position.y - i] != 0 && !stop)
			{
				//std::cout << "Up explotion range " << m_exploding_range[0] << '\n';
				std::cout << "Up: " << i << '\n';
					m_exploding_range[0] = i;


				if (datamap[m_position.x][m_position.y - i] != 2 && !stop)
				{
					datamap[m_position.x][m_position.y - i] = 0;
					stop = true;
				}
				else
					stop = true;
			}
		}
		else
			m_exploding_range[0] = i;
	}

	stop = false;

	//Check right
	for (int i = 1; i <= m_range; i++)
	{
		if (m_position.x + i < 31)
		{
			std::cout << "can check right\n";
			if (datamap[m_position.x+i][m_position.y] != 0 && !stop)
			{
				//std::cout << "Right explotion range " << m_exploding_range[1] << '\n';

				std::cout << "Right: " << i << '\n';
					m_exploding_range[1] = i;

				if (datamap[m_position.x+i][m_position.y] != 2 && !stop)
				{
					datamap[m_position.x+i][m_position.y] = 0;
					stop = true;
				}
				else
					stop = true;
			}
		}
		else
			m_exploding_range[1] = i;
	}

	stop = false;

	//Check down
	for (int i = 1; i <= m_range; i++)
	{
		if (m_position.y + i < 15)
		{
			std::cout << "can check down\n";
			if (datamap[m_position.x][m_position.y + i] != 0 && !stop)
			{
				//std::cout << "Down explotion range " << m_exploding_range[2] << '\n';

				std::cout << "Down: " << i << '\n';
					m_exploding_range[2] = i;

				if (datamap[m_position.x][m_position.y + i] != 2 && !stop)
				{
					datamap[m_position.x][m_position.y + i] = 0;
					stop = true;
				}
				else
					stop = true;
			}
		}
		else
			m_exploding_range[2] = i;
	}

	stop = false;

	//Check left
	for (int i = 1; i <= m_range; i++)
	{
		if (m_position.x - i > 0)
		{
			std::cout << "can check left\n";
			if (datamap[m_position.x-i][m_position.y] != 0 && !stop)
			{
				//std::cout << "Left explotion range " << m_exploding_range[3] << '\n';

				std::cout << "Left: " << i << '\n';
					m_exploding_range[3] = i;

				if (datamap[m_position.x - i][m_position.y] != 2 && !stop)
				{
					datamap[m_position.x - i][m_position.y] = 0;
					stop = true;
				}
				else
					stop = true;
			}
		}
		else
			m_exploding_range[3] = i;
	}

	stop = false;

	for (int i = 0; i < 4; i++)
		std::cout << m_exploding_range[i] << " - ";
	std::cout << '\n';

	return datamap;
}


// *Needs explanation*
bool Bomb::isEntityColliding(sf::Sprite& sprite)
{
	return false;
}


// *Needs explanation*
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


// initialize all spriteRects for animation
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
