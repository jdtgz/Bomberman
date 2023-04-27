#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "../Tile/Tile.h"
#include "../Enemies/Enemy.h"
#include "../Tile/Tile.h"
#include "../Tile/PowerUp.h"
#include "../Enum.h"
#include "Scoreboard.h"


class Level
{
public:
	Level();
	~Level();

	void generate(const int& levelNum, const Player* plrPtr);
	void loadLevel(int levelNum, int totalAirCount, const Player* plrPtr);
	bool isLevelCleared() const;
	void draw(sf::RenderWindow& window) const;
	int getLength() const;
	int getHeight() const;

	// manage bombs
	void keyPressed(const sf::Keyboard::Key& key, Player& plr);

	//Set Datamap
	void setMap(sf::Vector2i pos, int type);

	void setScoreboardPtr(Scoreboard* ptr);

	void collisions(Player& plr);
	bool deathCheck(std::vector<int> range, sf::Vector2i bombPos, const sf::FloatRect& bounds);

	void update(const float& dt, Player& plr);
private:
	const int MAP_LENGTH = 33;
	const int MAP_HEIGHT = 15;

	std::vector<std::vector<int>> datamap;
	std::vector<Bomb*> bombs;
	std::vector<Enemy*> enemies;
	sf::Vector2i powerUp_pos;

	Tile* tilemap[33][15];
	bool bombManager[10] = { false };

	void setPowerup(const int&, const int&);

	bool levelCleared, outOfTime;

	Scoreboard* scoreboardPtr;

	sf::Sound levelCompleteSound, powerupPickupSound;
	sf::SoundBuffer levelCompleteBuffer, powerupPickupBuffer;
	bool levelCompletePlayed;
};