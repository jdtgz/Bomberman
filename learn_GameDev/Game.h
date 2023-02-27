#pragma once
#include "SFML/Graphics.hpp"
#include "TextureHolder.h"
#include "Player.h"
#include "Level.h"


#include "Bomb.h"

class Game
{
	public:
		// constructor / destructor
		Game(); 
		~Game(); 

		// runs the whole game 
		void run(); 

	private:
		// helper functions for "run"
		void processEvents();
		void update(const sf::Time&);
		void render();

		// sfml screen attributes 
		sf::RenderWindow* window;
		sf::View view;

		// All textures necessary for game  
		TextureHolder gameTextures;

		// FPS
		sf::Time timePerFrame = sf::seconds(1.f / 60.f); 

		// Player 
		Player player;

		// Level
		Level level;

		// Level Number
		int levelNumber = 0;

		/*							TESTING PURPOSE								*/
		Bomb m_bomb;
};