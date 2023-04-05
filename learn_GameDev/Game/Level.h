#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "../Tile/Tile.h"
#include "../Enemies/Enemy.h"
#include "../Tile/Tile.h"
#include "../Tile/PowerUp.h"


class Level
{
public:
	// constructor/destructor
	Level();
	~Level();

	// load the stage
	void generate(const int&, const Player*);
	// end the level 
	void end();

	// get the height/lenth of game board
	int getLength() const;
	int getHeight() const;

	//manage bombs
	void keyPressed(const sf::Keyboard::Key&);

	// draw level onto sfml screen 
	void draw(sf::RenderWindow&) const;

	void setMap(sf::Vector2i, int);

	// track player collisions 
	void collisions(Player&);
	bool deathCheck(std::vector<int>, sf::Vector2i);

	// track enemy collisions 
	//void collisions(Enemy&);

	void update(const float&, sf::Vector2f, int, int, bool, sf::Sprite);
  
private:
	const int MAP_LENGTH = 33;
	const int MAP_HEIGHT = 15;

	std::vector<std::vector<int>> datamap;
	Tile* tilemap[33][15];
	std::vector<sf::Vector2i> powerups;

	std::vector<Enemy*> enemies;

	//bomb manager
	bool bombManager[10] = { false };
	std::vector<Bomb*> bombs;

	// player attirbutes 
	int bombCount;
	int flameRange;
	bool detonator;
	int playerX;
	int playerY;
	sf::Sprite playerSprite;
	bool playerDead = false;
};