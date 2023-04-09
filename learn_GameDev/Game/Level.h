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
		void keyPressed(const sf::Keyboard::Key& key);

		// draw level onto sfml screen 
		void draw(sf::RenderWindow& window) const;

		// sets the datamap
		void setMap(sf::Vector2i pos, int type);

		// track player collisions 
		void collisions(Player& plr);
		bool deathCheck(std::vector<int> range, sf::Vector2i bombPos);

		// track enemy collisions 
		// void collisions(Enemy&);

		void update(const float& dt, sf::Vector2f playerPos, 
			int bCount, int fRange, bool detonate, sf::Sprite pSprite);
  
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