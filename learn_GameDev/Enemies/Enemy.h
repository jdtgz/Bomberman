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
	virtual void move(Tile* [33][15]) = 0;

	void draw(sf::RenderWindow&) const;
	void die();

	bool isAlive() const;

	sf::Vector2f getPosition() const;
	sf::Vector2i getTilePosition() const;

	~Enemy();
protected:
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

	//Movement
	direction heading;
	float moveSpeed;
	float clippingMargin;
	const Player* playerRef;
	bool moveForward(Tile* [33][15]);
	void bounce();
	void randomHeading(Tile* [33][15]);
	bool atTile(Tile* [33][15]);
};