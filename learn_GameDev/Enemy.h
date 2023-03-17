#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Animation.h"
#include "Tile.h"

class Enemy
{
public:
	Enemy();

	virtual void update(const float&) = 0;
	virtual void move(Tile*[33][15], const sf::Vector2i&) = 0;

	void draw(sf::RenderWindow&) const;
	void die();

	bool isAlive() const;

	sf::Vector2f getPosition() const;

	~Enemy();
protected:
	enum class animIndex
	{
		LEFT = 0,
		RIGHT,
		UP,
		DOWN,
		DEATH,
		COUNT
	};
	sf::Sprite sprite;
	Animation anims[int(animIndex::COUNT)];
	animIndex curAnim;

	enum dir { NORTH = 0, EAST, SOUTH, WEST };
	dir heading;

	bool alive;
	float moveSpeed;
	sf::Vector2i tilePos;
};