#pragma once
#include "Tile.h"
#include "SFML/Graphics.hpp"
#include <vector>


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

		// track player collisions 
		void collisions(Player&);
		// track enemy collisions 
		//void collisions(Enemy&);
	private:
		static const int MAP_LENGTH = 31;
		static const int MAP_HEIGHT = 13;
		static const int BORDER_COUNT = (2 * (MAP_LENGTH + 2)) + (2 * MAP_HEIGHT);

		Tile* tilemap[MAP_LENGTH][MAP_HEIGHT];
		Tile* border[BORDER_COUNT];
};