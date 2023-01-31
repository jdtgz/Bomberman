#include "Player.h"


Player::Player()
{
	// initialize variables
	speed = 100.f; 
	velocity.x = 0.f;
	velocity.y = 0.f; 

	// initialize animation sprites
}


Player::~Player()
{
}


void Player::setUpAnimations(sf::Texture& txt)
{
	//animations[int(AnimationIndex::WalkingLeft)].initializeRects({ 0,0,12,16 }, 3);
	//animations[int(AnimationIndex::WalkingRight)].initializeRects( { 0,16,12,16 }, 3);
	//animations[int(AnimationIndex::WalkingDown)].initializeRects({ 0,16*2,12,16 }, 3);
	//animations[int(AnimationIndex::WalkingUp)].initializeRects({ 0,16*3,12,16 }, 3);
}


void Player::handleInput(sf::Keyboard::Key key, bool moving)
{
	if (moving)
	{
		switch (key)
		{
			case sf::Keyboard::Up:
				velocity.y = -speed; 
				cAnimation = AnimationIndex::WalkingUp; 
				break;
			case sf::Keyboard::Down:
				velocity.y = speed; 
				cAnimation = AnimationIndex::WalkingDown;
				break;
			case sf::Keyboard::Left:
				velocity.x = -speed;
				cAnimation = AnimationIndex::WalkingLeft;
				break;
			case sf::Keyboard::Right:
				velocity.x = speed; 
				cAnimation = AnimationIndex::WalkingRight;
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
	animations[int(cAnimation)].update(dt.asSeconds()); 
	animations[int(cAnimation)].applyToSprite(mSprite); 
	mSprite.move( velocity.x * dt.asSeconds(), velocity.y * dt.asSeconds());
}