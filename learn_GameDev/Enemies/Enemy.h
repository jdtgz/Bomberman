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
		DEATH,
		COUNT
	};
	sf::Sprite sprite;
	Animation anims[int(animIndex::COUNT)];
	animIndex curAnim;

	directions heading;

	bool alive;
	float moveSpeed;
	sf::Vector2i tilePos;
};