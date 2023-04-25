#include "Bomb.h"
#include "../Enum.h"


// Creates a bomb at (x,y)
// @param range -> number of tiles explosion reaches in all directions 
// @param has_timer -> determines if explosion will explode on a timer
Bomb::Bomb(int x, int y, int range, bool has_timer)
{
	m_range = range;

	for (int i = 0; i < 4; i++)
		m_exploding_range[i] = m_range;

	m_exploded = false;
	m_exploded_update = false;
	m_explosion_finished = false;

	if (has_timer)
		m_timer = sf::seconds(2.5);
	else
		m_timer = sf::seconds(-1);
	
	//Bomb position is left most explosion 
	m_sprite.setPosition(((x - 1) * 48), ((y + 1) * 48) + 4); 
	m_position = sf::Vector2i(x, y);

	initAnimation();
}


// draws the bomb onto the game window
void Bomb::draw(sf::RenderWindow& target, std::vector<std::vector<int>> datamap)
{
	//If not exploded, draw the bombs animation
	if (!m_exploded)
	{
		m_animations[(int)animationIndex::BOMB].applyToSprite(m_sprite);
		target.draw(m_sprite);
	}

	// If the bomb has exploded but the explosion is not finished,
	// draw the explosion animation
	else if (!m_explosion_finished)
	{
		if (!m_exploded_update)
		{
			bool stop = false;

			// calculates where the explosion animations should display 
			// based on bomb position, range, and surroundings 
			auto updateRange = [&](int xoffset, int yoffset, int range_direction, int iterator)
			{
				int x = m_position.x + (xoffset * iterator);
				int y = m_position.y + (yoffset * iterator);

				if (datamap[x][y] != tileType::AIR && !stop) //See if tile in way
				{
					m_exploding_range[range_direction] = iterator;
					stop = true;
					if (datamap[x][y] == tileType::TILE) // Dont animate on solid tile
						m_exploding_range[range_direction]--;
				}
				else if (datamap[x][y] == tileType::AIR && !stop) // constantly set range on open tile
					m_exploding_range[range_direction] = iterator;
			};

			// Check up
			for (int i = 1; i <= m_range; i++)
			{
				if (m_position.y - i > 0)
					updateRange(0, -1, 0, i);
				else
				{
					m_exploding_range[0] = i-1;
					i = m_range;
				}
			}

			stop = false; // reset if explosion finished

			// Check right
			for (int i = 1; i <= m_range; i++)
			{
				if (m_position.x + i < 32)
					updateRange(1, 0, 1, i);
				else
				{
					m_exploding_range[1] = i-1;
					i = m_range;
				}
			}

			stop = false;

			// Check down
			for (int i = 1; i <= m_range; i++)
			{
				if (m_position.y + i < 15)
					updateRange(0, 1, 2, i);
				else
				{
					m_exploding_range[2] = i-1;
					i = m_range;
				}
			}

			stop = false;

			// Check left
			for (int i = 1; i <= m_range; i++)
			{
				if (m_position.x - i > 0)
					updateRange(-1, 0, 3, i);
				else
				{
					m_exploding_range[3] = i-1;
					i = m_range;
				}
			}

			m_exploded_update = true;
		}

		// draws animaition and sprites onto screen 
		auto drawSprite = [&](const sf::Vector2f position, animationIndex type)
		{
			m_animations[(int)type].applyToSprite(m_sprite);
			m_sprite.setPosition(position);
			target.draw(m_sprite);
		};

		// Center explosion
		sf::Vector2f centerPos(((m_position.x - 1) * 48), (((m_position.y + 1) * 48) + 4));
		drawSprite(centerPos, animationIndex::CENTER);


		// North drawing
		for (int i = 0; i < m_exploding_range[0]; i++)
		{
			int k = i + 1;
			if (k < m_exploding_range[0])
				drawSprite(sf::Vector2f(centerPos.x, centerPos.y - (48 * k)), animationIndex::VERTICAL);
			else
				drawSprite(sf::Vector2f(centerPos.x, centerPos.y - (48 * k)), animationIndex::UP);
		}

		//South drawing
		for (int i = 0; i < m_exploding_range[2]; i++)
		{
			int k = i + 1;
			if (k < m_exploding_range[2])
				drawSprite(sf::Vector2f(centerPos.x, centerPos.y + (48 * k)), animationIndex::VERTICAL);
			else
				drawSprite(sf::Vector2f(centerPos.x, centerPos.y + (48 * k)), animationIndex::DOWN);
		}

		//East drawing
		for (int i = 0; i < m_exploding_range[1]; i++)
		{
			int k = i + 1;
			if (k < m_exploding_range[1])
				drawSprite(sf::Vector2f(centerPos.x + (48 * k), centerPos.y), animationIndex::HORIZONTAL);
			else
				drawSprite(sf::Vector2f(centerPos.x + (48 * k), centerPos.y), animationIndex::RIGHT);
		}

		//West drawing
		for (int i = 0; i < m_exploding_range[3]; i++)
		{
			int k = i + 1;

			if (k < m_exploding_range[3])
				drawSprite(sf::Vector2f(centerPos.x - (48 * k), centerPos.y), animationIndex::HORIZONTAL);
			else
				drawSprite(sf::Vector2f(centerPos.x - (48 * k), centerPos.y), animationIndex::LEFT);
		}
	}
}


// sets the proper sprite in each frame of the game 
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


sf::Sprite& Bomb::getSprite()
{
	return m_sprite;
}


// returns true if a sprite is colliding with the explosion
bool Bomb::isColliding(sf::Sprite& sprite)
{
	if (m_exploded && !m_explosion_finished)
	{
		sf::Vector2f centerPos(((m_position.x - 1) * 48), ((m_position.y + 1) * 48));

		// returns a boolean depending on if the sprites 
		// bounding box intersects with bomb
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
	if (m_sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()))
		return true;
	return false;
}


// updates datamap after explosion takes affect on environment
std::vector<std::vector<int>> 
Bomb::datamapExplosionCollision(std::vector<std::vector<int>> datamap)
{
	bool stop = false;


	auto updateRange = [&](int xoffset, int yoffset, int range_direction, int iterator)
	{
		int x = m_position.x + (xoffset * iterator);
		int y = m_position.y + (yoffset * iterator);

		if (datamap[x][y] != tileType::AIR && !stop)
		{
			if (datamap[x][y] != tileType::TILE && !stop)
			{
				m_exploding_range[range_direction] = iterator;
				datamap[x][y] = tileType::AIR;
				stop = true;
			}
			else
				stop = true;
		}
		else if (datamap[x][y] == tileType::AIR && !stop)
			m_exploding_range[range_direction] = iterator;
	};

	//Check up
	for (int i = 1; i <= m_range; i++)
		if (m_position.y - i > 0)
			updateRange(0, -1, 0, i);

	stop = false;

	//Check right
	for (int i = 1; i <= m_range; i++)
		if (m_position.x + i < 31)
			updateRange(1, 0, 1, i);

	stop = false;

	//Check down
	for (int i = 1; i <= m_range; i++)
		if (m_position.y + i < 15)
			updateRange(0, 1, 2, i);

	stop = false;

	//Check left
	for (int i = 1; i <= m_range; i++)
		if (m_position.x - i > 0)
			updateRange(-1, 0, 3, i);

	stop = false;

	return datamap;
}


// This was repurposed to do colliding checks with floatrects instead of sprites
// due to an issue with checking the sprites themselves
// Fixes the issue where the player would suddenly go off the bomb when its placed
bool Bomb::isEntityColliding(sf::FloatRect rect)
{
	// This is here because getting the sprites size would most of the time be 0 instead of 48
	sf::FloatRect bombBounds = 
		sf::FloatRect((m_position.x - 1) * 48, (m_position.y + 1) * 48, 48, 48);

	if (bombBounds.intersects(rect))
		return true;

	return false;
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