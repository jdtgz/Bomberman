#include "Game.h"


Game::Game()
{
	//Create a new window
	window = new sf::RenderWindow(sf::VideoMode(750, 750), "GAME!!");
	window->setFramerateLimit(144);

	//Generate the level
	level.generate(levelNumber);
}


Game::~Game() 
{
	//Unallocate window
	delete window; 
}


//Runs the game
//Keeps track of time for movement and animations
void Game::run()
{
	//Initialize clock & delta time
	sf::Clock clock; 
	sf::Time timeSinceLastTick = sf::Time::Zero;

	while (window->isOpen())
	{
		//Poll events
		processEvents();

		//Calculate dt
		timeSinceLastTick += clock.restart();

		//While there is time in the current tick
		while (timeSinceLastTick > timePerFrame)
		{
			//Decrement dt
			timeSinceLastTick -= timePerFrame;

			//Poll events again
			processEvents();

			//Tick
			update(timePerFrame); 
		}

		//Display updated gamestate
		render(); 
	}
}


//Event manager
void Game::processEvents()
{
	sf::Event evnt;
	while (window->pollEvent(evnt))
	{
		switch (evnt.type)
		{
			//Tell the player when a key is down
			case sf::Event::KeyPressed:
				player1.keyPressed(evnt.key.code); 
				break;
			//Tell the player when a key is released
			case sf::Event::KeyReleased:
				player1.keyReleased(evnt.key.code); 
				break;
			//Close the window
			case sf::Event::Closed: 
				window->close();
		}
	}
}


//Tick
void Game::update(sf::Time dt)
{ 
	player1.update(dt.asSeconds()); 
}


//Draw all objects to the window
void Game::render()
{
	window->clear(); 
	level.draw(*window);
	player1.draw(*window);  
	window->display(); 
}
