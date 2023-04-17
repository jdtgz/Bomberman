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

	reset();
}


Player::~Player()
{
}


void Player::reset()
{
	animations[int(animIndex::WALKING_LEFT)].setFrame(0);
	animations[int(animIndex::WALKING_RIGHT)].setFrame(0);
	animations[int(animIndex::WALKING_DOWN)].setFrame(0);
	animations[int(animIndex::WALKING_UP)].setFrame(0);
	animations[int(animIndex::DEATH)].setFrame(0);

	// set the starting animation
	curAnimation = animIndex::WALKING_RIGHT;
	animations[int(curAnimation)].applyToSprite(sprite);


	// initialize movement attributes 
	for (int i = 0; i < direction::COUNT; i++)
	{
		movement[i] = false;
		canMove[i] = true;
	}

	// initialize the player/powerUp attributes 
	bombCount = 1;
	flameRange = 1;
	speed = 3.f;
	wallPass = false;
	detonator = false;
	bombPass = false;
	flamePass = false;
	invincible = false;

	alive = true;
	dead = false;

	//Default position in the top left corner
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
	if (!invincible)
	{
		if (DEBUG)
			std::cout << "PLAYER DEAD\n";

		alive = false;
		curAnimation = animIndex::DEATH;

		//Prevent collision with enemies
		Collidable::updateRect(sf::FloatRect(0, 0, 0, 0));
	}
}


// detects whether a key has been pressed and acts accordingly
void Player::keyPressed(const sf::Keyboard::Key& key)
{
	// change the direction of the player based on input
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


// detects if a key is no longer being pressed and stops movement
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


// update the animation of the player and the position based on movement attirbutes 
void Player::update(const float& dt)
{
	if (alive)
	{
		if (movement[direction::NORTH] || movement[direction::SOUTH]
			|| movement[direction::WEST] || movement[direction::EAST])
		{
			animations[int(curAnimation)].update(dt);
			animations[int(curAnimation)].applyToSprite(sprite);
		}


		int x = canMove[direction::WEST] * movement[direction::WEST] * -speed;
		x += canMove[direction::EAST] * movement[direction::EAST] * speed;

		int y = canMove[direction::NORTH] * movement[direction::NORTH] * -speed;
		y += canMove[direction::SOUTH] * movement[direction::SOUTH] * speed;

		setVelocity(x, y);

		move(xVel, yVel);

		// Fix for the player being glitched out when between a tile on top and below
		sf::FloatRect playerBounds = sprite.getGlobalBounds();
		playerBounds.height -= speed;

		Collidable::updateRect(playerBounds);
	}
	else
	{
		//Play death animation
		animations[int(curAnimation)].update(dt);
		animations[int(curAnimation)].applyToSprite(sprite);
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


//Get the hitbox for the player sprite
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
	if(bombCount != 10)
		bombCount++; 
}


int Player::getFlameRange() const
{
	return flameRange; 
}


void Player::plusFlame()
{
	if (flameRange != 10)
		flameRange++; 
}


float Player::getSpeed() const
{
	return speed;
}


void Player::plusSpeed()
{
	speed += (speed * 0.10);
}


bool Player::hasWallPass() const
{
	return wallPass;
}


void Player::enableWallPass()
{
	wallPass = true; 
}


bool Player::hasDetonator() const
{
	return detonator; 
}


void Player::enableDetonator()
{
	detonator = true; 
}


bool Player::hasBombPass() const
{
	return bombPass; 
}


void Player::enableBombPass() 
{
	bombPass = true; 
}


bool Player::hasFlamePass() const
{
	return flamePass;
}


void Player::enableFlamePass()
{
	flamePass = true; 
}


bool Player::isInvincible() const
{
	return invincible; 
}


void Player::enableInvincible()
{
	invincible = true;
}