#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "../Tile/Tile.h"
#include "../Enemies/Enemy.h"
#include "../Tile/Tile.h"
#include "../Tile/PowerUp.h"
#include "../Enum.h"


class Level
{
public:
	// constructor/destructor
	Level();
	~Level();

	// load the stage
	void generate(const int& levelNum, const Player* plrPtr);
	// end the level 
	void end();

	// get the height/lenth of game board
	int getLength() const;
	int getHeight() const;

	// manage bombs
	void keyPressed(const sf::Keyboard::Key& key, Player& plr);

	// draw level onto sfml screen 
	void draw(sf::RenderWindow& window) const;

	// sets the datamap
	void setMap(sf::Vector2i pos, int type);

	// track player collisions 
	void collisions(Player& plr);
	bool deathCheck(std::vector<int> range, sf::Vector2i bombPos, const sf::FloatRect& bounds);

	// track enemy collisions 
	// void collisions(Enemy&);

	void update(const float& dt, Player& plr);
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

	void setPowerup(const int&, const int&);
};