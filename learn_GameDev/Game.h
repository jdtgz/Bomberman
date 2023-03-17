#pragma once
#include "SFML/Graphics.hpp"
#include "TextureHolder.h"
#include "Player.h"
#include "Level.h"
#include "StartMenu.h"

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

		// Level
		Level level;

		// Player 
		Player player;

		// New Bomb Location
		sf::Vector2i tempBomb;

		// Level Number
		int levelNumber;

		//Start Menu
		StartMenu startMenu;
};