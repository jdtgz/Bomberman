#include "Game.h"


// constructor 
Game::Game()
	: player1(gameTextures.get(Textures::Player))
{
	window = nullptr; 
	window = new sf::RenderWindow(sf::VideoMode(600, 600), "GAME!!");
}


// destructor
Game::~Game() 
{ 
	delete window; 
}


// runs the entirty of the game 
// tracks time to calc movement and animations 
void Game::run()
{
	// initialize closk and deltaTime
	sf::Clock clock; 
	sf::Time timeSinceLastUpdate = sf::Time::Zero; 

	while (window->isOpen())
	{
		processEvents(); 
		timeSinceLastUpdate += clock.restart(); 
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents(); 
			update(TimePerFrame); 
		}
		render(); 
	}
}


// Tracks all events in the game and acts accordingly 
void Game::processEvents()
{
	sf::Event evnt;
	while (window->pollEvent(evnt))
	{
		switch (evnt.type)
		{
			// if a key is pressed 
			case sf::Event::KeyPressed:
				player1.handleInput(evnt.key.code, true); 
				break;
			// if a key is released 
			case sf::Event::KeyReleased:
				player1.handleInput(evnt.key.code, false); 
				break;
			// if window is closed 
			case sf::Event::Closed: 
				window->close(); 
				break; 
		}
	}
}


// updates all the events in the game 
void Game::update(sf::Time dt)
{ 
	player1.update(dt); 
}


// renders all objects onto sfml window 
void Game::render()
{
	window->clear(); 
	player1.draw(*window);  
	window->display(); 
}
