#pragma once
#include "SFML/Graphics.hpp"
#include "TextureHolder.h"
#include "Player.h"

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
	void update(sf::Time);
	void render();

	// collision functions 
	
private:
	// sfml screen
	sf::RenderWindow* window;

	// All textures necessary for game  
	TextureHolder gameTextures;

	// FPS
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f); 

	// Player 
	Player player1;
};

