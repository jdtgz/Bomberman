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
	Enemy(const Player*, const enemyType&);
	Enemy(const Player*, const enemyType&,
		const sf::Vector2i&);
	Enemy(const Player*, const enemyType&,
		const sf::Vector2i&, const direction&);

	~Enemy();

	void update(const float& dt);

	virtual void move(Tile* tilemap[33][15]);

	void draw(sf::RenderWindow&) const;

	int getPointValue() const;

	void die();
	bool isAlive() const;
	bool completedDeathAnim() const;

	sf::Vector2f getPosition() const;
	sf::Vector2i getTilePosition() const;
	sf::FloatRect getBoundingBox() const;
private:
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

	//Death animation is over
	bool deathEnded;

	int pointValue;

	enemyType type;

	direction heading;
	float moveSpeed;

	//Similar to player wallpass, allows for enemy to move through bricks
	bool wallpass;

	//The distance the enemy sprite can clip into walls
	//Higher numbers result in more random ai, but more visual clipping
	float clippingMargin;

	const Player* playerRef; //Reference to the player for chasing

	//The current path found by pathfind
	std::vector<sf::Vector2i> path;

	int movementDebounce, pathfindingDebounce;
	bool chasePlayer;

	void init(const Player*, const enemyType&,
		const sf::Vector2i&, const direction&);

	void setHeading(const direction&);
	float distanceToPlayer() const;

	bool moveForward(Tile* [33][15]);
	void bounce();
	void randomHeading(Tile* [33][15]);
	bool pathfindingHeading(Tile* [33][15]);
	bool atTile(Tile* [33][15]);

	//Creates a path between this enemy and the player
	std::vector<sf::Vector2i> pathfind(Tile* [33][15]);

	bool walkableTile(Tile* [33][15], const sf::Vector2i&);
};