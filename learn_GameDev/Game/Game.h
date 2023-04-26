#pragma once
#include "SFML/Graphics.hpp"
#include "../Graphics/TextureHolder.h"
#include "Player.h"
#include "Level.h"
#include "StartMenu.h"
#include "Scoreboard.h"
#include "../Tile/Bomb.h"


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
		void render(const sf::Time&);
		void updateView(); 

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

		int playerLives;

		// Level Number
		int levelNumber;

		//Start Menu
		StartMenu startMenu;

		Scoreboard scoreboard;

		//Font for text
		sf::Font font;

		/* Needed for how long to keep the level */
		/* number to display on screen */
		sf::Clock levelScreenClock;


		sf::Music levelMusic;
		sf::Music startMenuMusic;

		sf::Sound newLevelSound;
		sf::SoundBuffer newLevelBuffer;
};