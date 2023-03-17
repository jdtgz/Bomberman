#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "../Tile/Tile.h"
#include "../Enemies/Enemy.h"
#include "../Enemies/Valcom.h"
#include "../Tile/Tile.h"

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
  
private:
	const int MAP_LENGTH = 33;
	const int MAP_HEIGHT = 15;

	int datamap[33][15];
	Tile* tilemap[33][15];

	std::vector<Enemy*> enemies;
};