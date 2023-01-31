#include "Player.h"


Player::Player(sf::Texture& t)
	: rightWalk(t, 1, 16, 12, 16)
{
	// initialize variables
	speed = 100.f; 
	velocity.x = 0.f;
	velocity.y = 0.f; 
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
				break;
			case sf::Keyboard::Down:
				velocity.y = speed; 
				break;
			case sf::Keyboard::Left:
				velocity.x = -speed;
				break;
			case sf::Keyboard::Right:
				velocity.x = speed; 
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
	rightWalk.update(dt.asSeconds()); 
	rightWalk.applyToSprite(mSprite); 
	mSprite.move( velocity.x * dt.asSeconds(), velocity.y * dt.asSeconds());
}