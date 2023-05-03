#include "Player.h"


Player::Player()
{
	// initialize visual attributes 
	sf::Texture* t = &TextureHolder::get(textures::PLAYER);

	animations[int(animIndex::WALKING_LEFT)].setUp(*t, 0, 16 * 0, 12, 16, 3);
	animations[int(animIndex::WALKING_RIGHT)].setUp(*t, 0, 16 * 1, 12, 16, 3);
	animations[int(animIndex::WALKING_DOWN)].setUp(*t, 0, 16 * 2, 12, 16, 3);
	animations[int(animIndex::WALKING_UP)].setUp(*t, 0, 16 * 3, 12, 16, 3);
	animations[int(animIndex::DEATH)].setUp(*t, 0, 16 * 4, 16, 16, 7);

	hardReset();

	walk_horizontal_buffer.loadFromFile("Sound/Horizontal Step.wav");
	walk_vertical_buffer.loadFromFile("Sound/Vertical Step.wav");
	//walk_sound.setBuffer(walk_horizontal_buffer);

	//Death sound isnt from the NES game since i couldnt find the sound
	//Its the cannon sound effect from SNES - Super Bomberman 2
	death_buffer.loadFromFile("Sound/Bomberman Death.wav");
	death_sound.setBuffer(death_buffer);

	just_died_buffer.loadFromFile("Sound/Just Died.wav");
	just_died_sound.setBuffer(just_died_buffer);
}


Player::~Player()
{
}


//Set all atributes of the Player back to their base state
void Player::hardReset()
{
	animations[int(animIndex::WALKING_LEFT)].setFrame(0);
	animations[int(animIndex::WALKING_RIGHT)].setFrame(0);
	animations[int(animIndex::WALKING_DOWN)].setFrame(0);
	animations[int(animIndex::WALKING_UP)].setFrame(0);
	animations[int(animIndex::DEATH)].setFrame(0);

	bombCount = 1;
	flameRange = 1;
	speed = 3.f;
	wallPass = false;
	bombPass = false;
	flamePass = false;

	reset();
}


void Player::reset()
{
	for (int i = 0; i < direction::COUNT; i++)
	{
		movement[i] = false;
		canMove[i] = true;
	}

	curAnimation = animIndex::WALKING_RIGHT;
	animations[int(curAnimation)].applyToSprite(sprite);

	alive = true;
	dead = false;

	detonator = false;
	invincible = 0;

	sprite.setPosition(0, 100);
}


bool Player::isAlive() const
{
	return alive;
}


bool Player::completedDeathAnim() const
{
	return dead;
}


void Player::die()
{
	if (!invincible && alive)
	{
		if (DEBUG)
			std::cout << "PLAYER DEAD\n";

		alive = false;
		curAnimation = animIndex::DEATH;

		death_sound.play();
		justDiedPlayed = false;

		//Prevent collision with enemies
		Collidable::updateRect(sf::FloatRect(0, 0, 0, 0));
	}
}


void Player::keyPressed(const sf::Keyboard::Key& key)
{
	switch (key)
	{
		case sf::Keyboard::Up:
			updateMoves(direction::NORTH);
			break;
		case sf::Keyboard::Down:
			updateMoves(direction::SOUTH);
			break;
		case sf::Keyboard::Left:
			updateMoves(direction::WEST);
			break;
		case sf::Keyboard::Right:
			updateMoves(direction::EAST);
	}
}


void Player::keyReleased(const sf::Keyboard::Key& key)
{
	switch (key)
	{
	case sf::Keyboard::Up:
		movement[direction::NORTH] = false;
		break;
	case sf::Keyboard::Down:
		movement[direction::SOUTH] = false;
		break;
	case sf::Keyboard::Left:
		movement[direction::WEST] = false;
		break;
	case sf::Keyboard::Right:
		movement[direction::EAST] = false;
		break;
	}
}


void Player::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);

	if (DEBUG)
	{
		//Display hitbox
		sf::RectangleShape box;
		box.setPosition(getBoundingBox().left, getBoundingBox().top);
		box.setSize(sf::Vector2f(getBoundingBox().width, getBoundingBox().height));
		box.setFillColor(sf::Color(255, 0, 0, 100));
		window.draw(box);
	}
}


// update the animation and position of the player
void Player::update(const float& dt)
{
	if (alive)
	{
		if (invincible > 0)
			invincible -= dt;
		else
			invincible = 0;

		if (movement[direction::NORTH] || movement[direction::SOUTH]
			|| movement[direction::WEST] || movement[direction::EAST])
		{
			animations[int(curAnimation)].update(dt);
			animations[int(curAnimation)].applyToSprite(sprite);
			
			/* Play walk sound */
			if (walk_sound_timer.getElapsedTime().asSeconds() > 0.2)
			{
				if (movement[direction::WEST] || movement[direction::EAST])
					walk_sound.setBuffer(walk_horizontal_buffer);
				else
					walk_sound.setBuffer(walk_vertical_buffer);

				walk_sound.play();
				walk_sound_timer.restart();
			}
		}


		int x = canMove[direction::WEST] * movement[direction::WEST] * -speed;
		x += canMove[direction::EAST] * movement[direction::EAST] * speed;

		int y = canMove[direction::NORTH] * movement[direction::NORTH] * -speed;
		y += canMove[direction::SOUTH] * movement[direction::SOUTH] * speed;

		setVelocity(x, y);

		move(xVel, yVel);

		sf::FloatRect playerBounds = sprite.getGlobalBounds();
		playerBounds.height -= speed;

		Collidable::updateRect(playerBounds);
	}
	else
	{
		//Play death animation
		animations[int(curAnimation)].update(dt);
		animations[int(curAnimation)].applyToSprite(sprite);

		if (death_sound.getStatus() != sf::Sound::Playing && 
			just_died_sound.getStatus() != sf::Sound::Playing &&
			!justDiedPlayed)
		{
			just_died_sound.play();
			justDiedPlayed = true;
		}
	}
	
	//Death animation completed
	if (curAnimation == animIndex::DEATH &&
		animations[(int)curAnimation].getCurrentFrame() == animations[(int)curAnimation].getFrameCount() - 1)
		dead = true;
}


void Player::setVelocity(const int& newX, const int& newY)
{
	xVel = newX;
	yVel = newY;
}


sf::Vector2f Player::getVelocity() const
{
	return sf::Vector2f(xVel, yVel);
}


void Player::move(const float& x, const float& y)
{
	sprite.move(x, y);
	return;
}


void Player::setCanMove(const int& dir, const bool& v)
{
	canMove[dir] = v;
	return;
}

void Player::setPosition(const float& x, const float& y)
{
	sprite.setPosition(x, y);
}

void Player::updateMoves(int dir)
{
	movement[dir] = true;
	curAnimation = (animIndex)(dir);
	for (int i = 0; i < 4; i++)
		if (i != dir)
			canMove[i] = true;
}


sf::Vector2f Player::getPosition() const
{
	return sf::Vector2f((sprite.getPosition().x + 24) / 48 + 1,
		(sprite.getPosition().y + 24) / 48 - 1);
}


sf::Vector2i Player::getTilePosition() const
{
	//Shift by one to adjust for border
	return sf::Vector2i(sprite.getPosition().x / 48 + 1,
		(sprite.getPosition().y - 100) / 48 + 1);
}


sf::FloatRect Player::getBoundingBox() const
{
	sf::FloatRect alteredBox = sprite.getGlobalBounds();
	alteredBox.left += 1.5 + speed;
	alteredBox.top += 3.75 + speed;
	alteredBox.width -= 3 + 2 * speed;
	alteredBox.height -= 7.5 + 2 * speed;
	return alteredBox;
}


sf::Sprite& Player::getSprite() 
{
	return sprite;
}


int Player::getBombCount() const
{
	return bombCount; 
}


void Player::plusBomb()
{
	if(bombCount < 10)
		bombCount++;
}


void Player::minusBomb()
{
	if (bombCount > 1)
		bombCount--;
}


int Player::getFlameRange() const
{
	return flameRange; 
}


void Player::plusFlame()
{
	if (flameRange < 10)
		flameRange++; 
}


void Player::minusFlame()
{
	if (flameRange > 1)
		flameRange++;
}


float Player::getSpeed() const
{
	return speed;
}


void Player::plusSpeed()
{
	speed += speed * 0.10;
}


void Player::minusSpeed()
{
	speed -= speed * 0.10;
}


bool Player::hasWallPass() const
{
	return wallPass;
}


void Player::enableWallPass()
{
	wallPass = true; 
}


void Player::disableWallPass()
{
	wallPass = false;
}


bool Player::hasDetonator() const
{
	return detonator; 
}


void Player::enableDetonator()
{
	detonator = true; 
}


void Player::disableDetonator()
{
	detonator = false;
}


bool Player::hasBombPass() const
{
	return bombPass; 
}


void Player::enableBombPass() 
{
	bombPass = true; 
}


void Player::disableBombPass()
{
	bombPass = false;
}


bool Player::hasFlamePass() const
{
	return flamePass;
}


void Player::enableFlamePass()
{
	flamePass = true; 
}


void Player::disableFlamePass()
{
	flamePass = false;
}


bool Player::isInvincible() const
{
	return invincible > 0; 
}


void Player::enableInvincible()
{
	invincible = 30;
}