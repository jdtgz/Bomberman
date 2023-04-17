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
	Enemy(const Player*);

	void update(const float&);

	virtual void move(Tile*[33][15]) = 0;

	void draw(sf::RenderWindow&) const;

	void die();
	bool isAlive() const;
	bool completedDeathAnim() const;

	sf::Vector2f getPosition() const;
	sf::Vector2i getTilePosition() const;
	sf::FloatRect getBoundingBox() const;

	~Enemy();
protected:
	//Animation & Visuals
	enum animIndex
	{
		RIGHT = 0,
		LEFT,
		DEATH,
		COUNT
	};
	sf::Sprite sprite;
	Animation anims[int(animIndex::COUNT)];
	animIndex curAnim;

	//Enemy is alive
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
	//Death animation is over
	bool deathEnded;

	const Player* playerRef; //Reference to the player for chasing
};