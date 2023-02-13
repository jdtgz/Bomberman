#include "Player.h"


Player::Player(sf::Texture& t)
{
	// initialize movement attributes 
	speed = 100.f;

	// setup animations 
	animations[int(AnimationIndex::WalkingLeft)].setUp(t, 0, 0, 12, 16, 3);
	animations[int(AnimationIndex::WalkingRight)].setUp(t, 0, 16, 12, 16, 3);
	animations[int(AnimationIndex::WalkingDown)].setUp(t, 0, 32, 12, 16, 3);
	animations[int(AnimationIndex::WalkingUp)].setUp(t, 0, 48, 12, 16, 3);

	// set the starting animation
	curAnimation = AnimationIndex::WalkingRight;
}


// destructor
Player::~Player()
{
}


void Player::keyPressed(sf::Keyboard::Key key)
{
	// change the direction of the player based on input
	switch (key)
	{
		case sf::Keyboard::Up:
			up = true; 
			curAnimation = AnimationIndex::WalkingUp;
			break;
		case sf::Keyboard::Down:
			down = true; 
			curAnimation = AnimationIndex::WalkingDown;
			break;
		case sf::Keyboard::Left:
			left = true;
			curAnimation = AnimationIndex::WalkingLeft;
			break;
		case sf::Keyboard::Right:
			right = true; 
			curAnimation = AnimationIndex::WalkingRight;
			break;
	}
}

void Player::keyReleased(sf::Keyboard::Key key)
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


void Player::update(float dt)
{
	// update animations 
	animations[int(curAnimation)].update(dt);
	animations[int(curAnimation)].applyToSprite(mSprite);

	// update location
	mSprite.move(((left * -3) + (right * 3)), ((up * -3) + (down * 3)));
}