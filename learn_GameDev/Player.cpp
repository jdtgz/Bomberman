#include "Player.h"


Player::Player()
{
	// initialize movement attributes 
	speed = 3.f;
	
	// get the texture
	sf::Texture* t = &TextureHolder::get(textures::PLAYER);

	// setup animations 
	animations[int(animIndex::WALKING_LEFT)].setUp(*t, 0, 0, 12, 16, 3);
	animations[int(animIndex::WALKING_RIGHT)].setUp(*t, 0, 16, 12, 16, 3);
	animations[int(animIndex::WALKING_DOWN)].setUp(*t, 0, 32, 12, 16, 3);
	animations[int(animIndex::WALKING_UP)].setUp(*t, 0, 48, 12, 16, 3);
	animations[int(animIndex::DEATH)].setUp(*t, 0, 64, 16, 16, 7);

	// set the starting animation
	curAnimation = animIndex::WALKING_RIGHT;
	animations[int(curAnimation)].applyToSprite(sprite);

	//Default position in the top left corner
	sprite.setPosition(0, 100);
}


// destructor
Player::~Player()
{
}


// detects whether a key has been pressed and acts accordingly
void Player::keyPressed(const sf::Keyboard::Key &key)
{
	// change the direction of the player based on input
	switch (key)
	{
		case sf::Keyboard::Up:
			up = true; 
			curAnimation = animIndex::WALKING_UP;
			//Reset 'can moves' for all other directions
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
			break;
		case sf::Keyboard::Down:
			down = true; 
			curAnimation = animIndex::WALKING_DOWN;
			//Reset 'can moves' for all other directions
			canMoveUp = true;
			canMoveLeft = true;
			canMoveRight = true;
			break;
		case sf::Keyboard::Left:
			left = true;
			curAnimation = animIndex::WALKING_LEFT;
			//Reset 'can moves' for all other directions
			canMoveUp = true;
			canMoveDown = true;
			canMoveRight = true;
			break;
		case sf::Keyboard::Right:
			right = true; 
			curAnimation = animIndex::WALKING_RIGHT;
			//Reset 'can moves' for all other directions
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			break;
		case sf::Keyboard::A:
			// place a bomb
			break;
		case sf::Keyboard::B:
			// detonate a bomb IF detonate powerUp == true
			break;
	}
}


// detects if a key is no longer being pressed and stops movement
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


// draws player onto the screen 
void Player::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}


// update the animation of the player and the position based on movement attirbutes 
void Player::update(const float& dt)
{
	// update animations 
	if (right || left || down || up)
	{
		animations[int(curAnimation)].update(dt);
		animations[int(curAnimation)].applyToSprite(sprite);
	}
	// if plr collides with fire (witout flameUp powerUp)
	// or enemy -> death animation...

	//Update velocity based on user input, move speed, and
	//the directions the player can currently move in
	setVelocity((canMoveLeft * left * -speed) + (canMoveRight * right * speed),
		(canMoveUp * up * -speed) + (canMoveDown * down * speed));

	//Move sprite by velocity
	move(xVel, yVel);
}


// sets the velocity of the player
void Player::setVelocity(const int& newX, const int& newY)
{
	xVel = newX;
	yVel = newY;
}


//Get the movement velocity of the player
sf::Vector2f Player::getVelocity() const
{
	return sf::Vector2f(xVel, yVel);
}


//Get the hitbox for the player sprite
sf::FloatRect Player::getBoundingBox() const
{
	return sprite.getGlobalBounds();
}


// return sprite of player 
sf::Sprite Player::getSprite() const 
{
	return sprite;
}


//Move player sprite by x, y
void Player::move(const float& x, const float& y)
{
	sprite.move(x, y);
	return;
}


//Set if the player can move left or not
void Player::setCanMoveLeft(const bool& v)
{
	canMoveLeft = v;
	return;
}


//Set if the player can move right or not
void Player::setCanMoveRight(const bool& v)
{
	canMoveRight = v;
	return;
}


//Set if the player can move up or not
void Player::setCanMoveUp(const bool& v)
{
	canMoveUp = v;
	return;
}


//Set if the player can move down or not
void Player::setCanMoveDown(const bool& v)
{
	canMoveDown = v;
	return;
}


//Get player move speed
float Player::getSpeed() const
{
	return speed;
}