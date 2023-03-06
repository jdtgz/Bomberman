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
	flameRange = 1; 
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
			for (int i = 0; i < bombCount; i++)
			{
				if (bombManager[i] == false)
				{
					for (int i = 0; i < bombs.size(); i++)
					{
						if (bombs[i]->isColliding(sprite))
						{
							std::cout << "COLLIDE!\n";
							return;
						}
					}
					bombManager[i] = true;

					// initialize the bomb
					if (detonator == false)
						bombs.push_back(new Bomb(getPosition().x, getPosition().y, flameRange, true));
					else
						bombs.push_back(new Bomb(getPosition().x, getPosition().y, flameRange, false));
					break;
				}
			}
			break;
		case sf::Keyboard::B:
			for (int i = 0; i < bombs.size(); i++)
			{
				if (bombManager[i] = true)
					bombs[i]->explode(); 
			}
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
	for (int i = 0; i < bombs.size(); i++)
	{
		bombs[i]->draw(window);
	}
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
	
	
	//Clear bombs
	for (int i = 0; i < bombs.size(); i++)
	{
		// if the bomb exploded and the bomb is active
		if (bombs[i]->getExploded() && bombManager[i] == true)
		{
			// de-activate the bomb and delete it 
			bombManager[i] = false;
			delete bombs[i];
			bombs.erase(bombs.begin() + i);
			std::cout << bombManager[0] << bombManager[1] << bombManager[2] << '\n';
		}
	}

	//Update bombs
	for (int i = 0; i < bombs.size(); i++)
	{
		bombs[i]->update(dt);
	}
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


//Get player move speed
float Player::getSpeed() const
{
	return speed;
}


// detonate the oldest bomb
void Player::detonate()
{
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

sf::Vector2f Player::getPosition()
{
	int x = (sprite.getPosition().x + 24) / 48;
	int y = (sprite.getPosition().y + 24) / 48;
	//std::cout << x + 1 << "," << y - 1 << '\n';
	return sf::Vector2f(x + 1, y - 1);
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
int Player::getBombCount()
{
	return bombCount; 
}


// +1 number of bombs player can place at a time 
void Player::plusBombCount()
{
	bombCount++; 
}


// return range of the bomb explosions
int Player::getFlameRange()
{
	return flameRange; 
}


// +1 range of bomb explosion
void Player::plusFlameRange()
{
	flameRange++; 
}


// return if player can move through walls 
bool Player::wallPass_status()
{
	return wallPass;
}


// activate the wallPass powerUp
void Player::activate_wallPass()
{
	if(!wallPass)
		wallPass = true; 
}


// return if player can detonate bombs 
bool Player::detonator_status()
{
	return detonator; 
}


// activate the detonator powerUp
void Player::activate_detonator()
{
	if(!detonator)
		detonator = true; 
}


// return if player can walk through bombs 
bool Player::bombPass_status()
{
	return bombPass; 
}


// activate the active bombPass powerUp
void Player::activate_bombPass()
{
	if (!bombPass)
		bombPass = true; 
}


// return if player can move through flames 
bool Player::flamePass_status()
{
	return flamePass;
}


// activate the flamePass powerUp
void Player::activate_flamePass()
{
	if (!flamePass)
		flamePass = true; 
}


// return if player is invincible
bool Player::invincible_status()
{
	return invincible; 
}


// activate the invincibility powerUp
void Player::activate_invincible()
{
	if (!invincible)
		invincible = true; 
}


// deactivate the invincibility powerUp
void Player::stop_invincible()
{
	invincible = false; 
}