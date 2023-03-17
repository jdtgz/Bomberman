#pragma once
#include "Tile.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include "Enemy.h"
#include "Valcom.h"
#include "PowerUp.h"

class Level
{
public:
	// constructor/destructor
	Level();
	~Level();

	// load the stage
	void generate(const int&);
	// end the level 
	void end();

	// get the height/lenth of game board
	int getLength() const;
	int getHeight() const;

	// draw level onto sfml screen 
	void draw(sf::RenderWindow&) const;

	void setMap(sf::Vector2i, int);

	// track player collisions 
	void collisions(Player&);
	// track enemy collisions 
	//void collisions(Enemy&);

	void update(const float&, int);
  
  Tile* getTilemap();
	sf::Vector2i getClosestTile(const sf::Vector2f&);
private:
	const int MAP_LENGTH = 33;
	const int MAP_HEIGHT = 15;

	int datamap[33][15];
	Tile* tilemap[33][15];

	std::vector<Enemy*> enemies;
};