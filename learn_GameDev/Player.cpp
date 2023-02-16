#include "Player.h"


Player::Player()
{
	// initialize movement attributes 
	speed = 3.f;
	
	sf::Texture* t = &TextureHolder::get(textures::PLAYER);

	// setup animations 
	animations[int(animIndex::WALKING_LEFT)].setUp(*t, 0, 0, 12, 16, 3);
	animations[int(animIndex::WALKING_RIGHT)].setUp(*t, 0, 16, 12, 16, 3);
	animations[int(animIndex::WALKING_DOWN)].setUp(*t, 0, 32, 12, 16, 3);
	animations[int(animIndex::WALKING_UP)].setUp(*t, 0, 48, 12, 16, 3);

	// set the starting animation
	curAnimation = animIndex::WALKING_RIGHT;
	
	animations[int(curAnimation)].applyToSprite(mSprite);
}


// destructor
Player::~Player()
{
}


void Player::keyPressed(const sf::Keyboard::Key &key)
{
	// change the direction of the player based on input
	switch (key)
	{
		case sf::Keyboard::Up:
			up = true; 
			curAnimation = animIndex::WALKING_UP;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
			break;
		case sf::Keyboard::Down:
			down = true; 
			curAnimation = animIndex::WALKING_DOWN;
			canMoveUp = true;
			canMoveLeft = true;
			canMoveRight = true;
			break;
		case sf::Keyboard::Left:
			left = true;
			curAnimation = animIndex::WALKING_LEFT;
			canMoveUp = true;
			canMoveDown = true;
			canMoveRight = true;
			break;
		case sf::Keyboard::Right:
			right = true; 
			curAnimation = animIndex::WALKING_RIGHT;
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			break;
	}
}


void Player::keyReleased(const sf::Keyboard::Key &key)
{
	// change the direction of the player based on input
	switch (key)
	{
	case sf::Keyboard::Up:
		up = false;
		break;
	case sf::Keyboard::Down:
		down = false;
		break;
	case sf::Keyboard::Left:
		left = false;
		break;
	case sf::Keyboard::Right:
		right = false;
		break;
	}
}


void Player::draw(sf::RenderWindow& window) const
{
	window.draw(mSprite); 
}


void Player::update(const float& dt)
{
	// update animations 
	if (right || left || down || up)
	{
		animations[int(curAnimation)].update(dt);
		animations[int(curAnimation)].applyToSprite(mSprite);
	}

	// update location
	xVel = ((canMoveLeft * left * -speed) + (canMoveRight * right * speed));
	yVel = ((canMoveUp * up * -speed) + (canMoveDown * down * speed));

	move(xVel, yVel);
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


sf::FloatRect Player::getBoundingBox() const
{
	return mSprite.getGlobalBounds();
}


void Player::move(const float& x, const float& y)
{
	mSprite.move(x, y);
	return;
}


void Player::setCanMoveLeft(const bool& v)
{
	canMoveLeft = v;
	return;
}


void Player::setCanMoveRight(const bool& v)
{
	canMoveRight = v;
	return;
}


void Player::setCanMoveUp(const bool& v)
{
	canMoveUp = v;
	return;
}


void Player::setCanMoveDown(const bool& v)
{
	canMoveDown = v;
	return;
}


float Player::getSpeed() const
{
	return speed;
}