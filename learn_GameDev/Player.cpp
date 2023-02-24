#include "Player.h"


Player::Player()
{
	// initialize movement attributes 
	speed = 3.f;
	for (int i = 0; i < directions::COUNT; i++)
	{
		movement[i] = false; 
		canMove[i] = true; 
	}
	
	// get the texture
	sf::Texture* t = &TextureHolder::get(textures::PLAYER);

	// setup animations 
	animations[int(animIndex::WALKING_LEFT)].setUp(*t, 0, 16 * 0, 12, 16, 3);
	animations[int(animIndex::WALKING_RIGHT)].setUp(*t, 0, 16 * 1, 12, 16, 3);
	animations[int(animIndex::WALKING_DOWN)].setUp(*t, 0, 16 * 2, 12, 16, 3);
	animations[int(animIndex::WALKING_UP)].setUp(*t, 0, 16 * 3, 12, 16, 3);
	animations[int(animIndex::DEATH)].setUp(*t, 0, 16 * 4, 16, 16, 7);

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
			movement[directions::UP] = true;
			curAnimation = animIndex::WALKING_UP;
			//Reset 'can moves' for all other directions
			canMove[directions::RIGHT] = true; 
			canMove[directions::LEFT] = true;
			canMove[directions::DOWN] = true;
			break;
		case sf::Keyboard::Down:
			movement[directions::DOWN] = true;
			curAnimation = animIndex::WALKING_DOWN;
			//Reset 'can moves' for all other directions
			canMove[directions::RIGHT] = true;
			canMove[directions::LEFT] = true;
			canMove[directions::UP] = true;
			break;
		case sf::Keyboard::Left:
			movement[directions::LEFT] = true;
			curAnimation = animIndex::WALKING_LEFT;
			//Reset 'can moves' for all other directions
			canMove[directions::UP] = true;
			canMove[directions::DOWN] = true;
			canMove[directions::RIGHT] = true;
			break;
		case sf::Keyboard::Right:
			movement[directions::RIGHT] = true;
			curAnimation = animIndex::WALKING_RIGHT;
			//Reset 'can moves' for all other directions
			canMove[directions::UP] = true;
			canMove[directions::DOWN] = true;
			canMove[directions::LEFT] = true;
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
		movement[directions::UP] = false;
		break;
	case sf::Keyboard::Down:
		movement[directions::DOWN] = false;
		break;
	case sf::Keyboard::Left:
		movement[directions::LEFT] = false;
		break;
	case sf::Keyboard::Right:
		movement[directions::RIGHT] = false;
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
	if (movement[directions::UP] || movement[directions::DOWN] 
		|| movement[directions::LEFT] || movement[directions::RIGHT])
	{
		animations[int(curAnimation)].update(dt);
		animations[int(curAnimation)].applyToSprite(sprite);
	}

	//Update velocity based on user input, move speed, and
	//the directions the player can currently move in
	int x = canMove[directions::LEFT] * movement[directions::LEFT] * -speed; 
	x += canMove[directions::RIGHT] * movement[directions::RIGHT] * speed; 

	int y = canMove[directions::UP] * movement[directions::UP] * -speed;
	y += canMove[directions::DOWN] * movement[directions::DOWN] * speed;

	setVelocity(x, y);

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
void Player::setCanMove(const int& dir, const bool& v)
{
	canMove[dir] = v;
	return;
}


//Get player move speed
float Player::getSpeed() const
{
	return speed;
}