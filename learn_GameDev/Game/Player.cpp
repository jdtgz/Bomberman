#include "Player.h"


Player::Player()
{
	// initialize visual attributes 
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


	// initialize movement attributes 
	for (int i = 0; i < directions::COUNT; i++)
	{
		movement[i] = false; 
		canMove[i] = true; 
	}

	// initialize the player/powerUp attributes 
	bombCount = 3; 
	flameRange = 2; 
	speed = 3.f;
	wallPass = false; 
	detonator = false;
	bombPass = false; 
	flamePass = false; 
	invincible = false; 

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
			movement[directions::NORTH] = true;
			curAnimation = animIndex::WALKING_UP;
			//Reset 'can moves' for all other directions
			canMove[directions::EAST] = true; 
			canMove[directions::WEST] = true;
			canMove[directions::SOUTH] = true;
			break;
		case sf::Keyboard::Down:
			movement[directions::SOUTH] = true;
			curAnimation = animIndex::WALKING_DOWN;
			//Reset 'can moves' for all other directions
			canMove[directions::EAST] = true;
			canMove[directions::WEST] = true;
			canMove[directions::NORTH] = true;
			break;
		case sf::Keyboard::Left:
			movement[directions::WEST] = true;
			curAnimation = animIndex::WALKING_LEFT;
			//Reset 'can moves' for all other directions
			canMove[directions::NORTH] = true;
			canMove[directions::SOUTH] = true;
			canMove[directions::EAST] = true;
			break;
		case sf::Keyboard::Right:
			movement[directions::EAST] = true;
			curAnimation = animIndex::WALKING_RIGHT;
			//Reset 'can moves' for all other directions
			canMove[directions::NORTH] = true;
			canMove[directions::SOUTH] = true;
			canMove[directions::WEST] = true;
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
		movement[directions::NORTH] = false;
		break;
	case sf::Keyboard::Down:
		movement[directions::SOUTH] = false;
		break;
	case sf::Keyboard::Left:
		movement[directions::WEST] = false;
		break;
	case sf::Keyboard::Right:
		movement[directions::EAST] = false;
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
	if (movement[directions::NORTH] || movement[directions::SOUTH] 
		|| movement[directions::WEST] || movement[directions::EAST])
	{
		animations[int(curAnimation)].update(dt);
		animations[int(curAnimation)].applyToSprite(sprite);
	}

	//Update velocity based on user input, move speed, and
	//the directions the player can currently move in
	int x = canMove[directions::WEST] * movement[directions::WEST] * -speed; 
	x += canMove[directions::EAST] * movement[directions::EAST] * speed; 

	int y = canMove[directions::NORTH] * movement[directions::NORTH] * -speed;
	y += canMove[directions::SOUTH] * movement[directions::SOUTH] * speed;

	setVelocity(x, y);

	//Move sprite by velocity
	move(xVel, yVel);

	
	//Fix for the player being glitched out when between a tile on top and below
	sf::FloatRect playerBounds = sprite.getGlobalBounds();
	playerBounds.height /= 1.1;

	Collidable::updateRect(playerBounds);
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


sf::Vector2f Player::getPosition() const
{
	return sf::Vector2f((sprite.getPosition().x + 24) / 48 + 1,
		(sprite.getPosition().y + 24) / 48 - 1);
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


// return number of bombs player can place at a time 
int Player::getBombCount() const
{
	return bombCount; 
}


// +1 number of bombs player can place at a time 
void Player::plusBomb()
{
	if(bombCount != 10)
		bombCount++; 
}


// return range of the bomb explosions
int Player::getFlameRange() const
{
	return flameRange; 
}


// +1 range of bomb explosion
void Player::plusFlame()
{
	if (flameRange != 10)
		flameRange++; 
}


//Get player move speed
float Player::getSpeed() const
{
	return speed;
}


// increment the movement speed of the player by 10%
void Player::plusSpeed()
{
	speed += (speed * 0.10);
}


// return if player can move through walls 
bool Player::hasWallPass() const
{
	return wallPass;
}


// activate the wallPass powerUp
void Player::enableWallPass()
{
	wallPass = true; 
}


// return if player can detonate bombs 
bool Player::hasDetonator() const
{
	return detonator; 
}


// activate the detonator powerUp
void Player::enableDetonator()
{
	detonator = true; 
}


// return if player can walk through bombs 
bool Player::hasBombPass() const
{
	return bombPass; 
}


// activate the active bombPass powerUp
void Player::enableBombPass() 
{
	bombPass = true; 
}


// return if player can move through flames 
bool Player::hasFlamePass() const
{
	return flamePass;
}


// activate the flamePass powerUp
void Player::enableFlamePass()
{
	flamePass = true; 
}


// return if player is invincible
bool Player::isInvincible() const
{
	return invincible; 
}


// activate the invincibility powerUp
void Player::enableInvincible()
{
	
}