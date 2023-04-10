#pragma once
#include <SFML/Graphics.hpp>
#include "../Graphics/TextureHolder.h"
#include "../Graphics/Animation.h"
#include "../Game/Collidable.h"
#include "../Tile/Tile.h"
#include "../Enum.h"

class Enemy : public Collidable
{
public:
	//Constructor, requires player for chasing
	Enemy(const Player*);

	//Update for animation
	void update(const float&);

	//Abstract virtual function for movement ai
	virtual void move(Tile*[33][15]) = 0;

	//Draw to the screen
	void draw(sf::RenderWindow&) const;

	//Tell the enemy it is dead
	void die();

	//Returns whether the enemy is alive or not
	bool isAlive() const;

	//Returns true when the death anim has been completed
	bool completedDeathAnim() const;

	//Returns the position of the enemy sprite
	sf::Vector2f getPosition() const;

	//Returns the tile coordinates of the enemy
	sf::Vector2i getTilePosition() const;

	//Destructor
	~Enemy();
protected:
	//Animation & Visuals
	enum animIndex
	{
		LEFT = 0,
		RIGHT,
		DEATH,
		COUNT
	};
	sf::Sprite sprite;
	Animation anims[int(animIndex::COUNT)];
	animIndex curAnim;

	bool alive;

	direction heading;
	float moveSpeed;

	//The distance the enemy sprite can clip into walls
	//Higher numbers result in more random ai, but more visual clipping
	float clippingMargin;

	//Move forward based on the current heading
	bool moveForward(Tile* [33][15]);

	//Change heading so the enemy moves 'backwards'
	void bounce();

	//Randomly assign a heading if certain conditions are met
	void randomHeading(Tile* [33][15]);

	//Returns whether the enemy is close enough to a tile to be considered 'at' it
	bool atTile(Tile* [33][15]);

private:
	bool dead;

	const Player* playerRef; //Reference to the player for chasing
};