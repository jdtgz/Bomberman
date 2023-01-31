#include "Player.h"


Player::Player(sf::Texture& t)
{
	// initialize variables
	speed = 100.f; 
	velocity.x = 0.f;
	velocity.y = 0.f;

	animations[WalkingLeft] = Animation(t, 0, 0, 12, 16, 3);
	animations[WalkingRight] = Animation(t, 0, 16, 12, 16, 3);
	animations[WalkingDown] = Animation(t, 0, 32, 12, 16, 3);
	animations[WalkingUp] = Animation(t, 0, 48, 12, 16, 3);

	curAnimation = WalkingRight;
}


Player::~Player()
{
}


void Player::handleInput(sf::Keyboard::Key key, bool moving)
{
	if (moving)
	{
		switch (key)
		{
			case sf::Keyboard::Up:
				velocity.y = -speed; 
				curAnimation = WalkingUp;
				break;
			case sf::Keyboard::Down:
				velocity.y = speed; 
				curAnimation = WalkingDown;
				break;
			case sf::Keyboard::Left:
				velocity.x = -speed;
				curAnimation = WalkingLeft;
				break;
			case sf::Keyboard::Right:
				velocity.x = speed; 
				curAnimation = WalkingRight;
				break;
		}
	}
	else 
		velocity = { 0.0f, 0.0f };

}


void Player::draw(sf::RenderWindow& window) const
{
	window.draw(mSprite); 
}


void Player::update(sf::Time dt)
{
	animations[curAnimation].update(dt.asSeconds());
	animations[curAnimation].applyToSprite(mSprite);
	mSprite.move( velocity.x * dt.asSeconds(), velocity.y * dt.asSeconds());
}