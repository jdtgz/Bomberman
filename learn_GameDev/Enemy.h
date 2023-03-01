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
	virtual void move(Tile*[31][13], const sf::Vector2i&, const sf::Vector2i&) = 0;

	void draw(sf::RenderWindow&) const;
	void die();

	bool isAlive() const;

	sf::Vector2f getPosition() const;

	~Enemy();
protected:
	enum class animIndex
	{
		WALKING_LEFT = 0,
		WALKING_RIGHT,
		WALKING_DOWN,
		WALKING_UP,
		DEATH,
		COUNT
	};
	sf::Sprite sprite;
	Animation anims[int(animIndex::COUNT)];
	animIndex curAnim;

	bool alive;
	float moveSpeed;
};