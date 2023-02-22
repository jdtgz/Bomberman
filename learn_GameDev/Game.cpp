#include "Game.h"


Game::Game()
{
	//Create a new window
	window = new sf::RenderWindow(sf::VideoMode(750, 750), "GAME!!");
	window->setFramerateLimit(144);

	//Generate the level
	level.generate(levelNumber);

	view.setSize(sf::Vector2f(window->getSize()));

	player1.getSprite().setPosition(48 * 31 / 2, 48 * 13 / 2);
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
		//Detect all collisions and adjust player accordingly
		level.collisions(player1);

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

	//Prevent viewport from going off of the map
	if (player1.getSprite().getPosition().x > (view.getSize().x / 2) - 48 &&
		player1.getSprite().getPosition().x < (31 * 48) - (view.getSize().x / 3))
	{
		view.setCenter(sf::Vector2f(player1.getSprite().getPosition().x,
			window->getSize().y / 2 + 48));
	}
	else if (player1.getSprite().getPosition().x < (view.getSize().x / 2) - 48)
	{
		view.setCenter(sf::Vector2f((view.getSize().x / 2) - 48, 
						window->getSize().y / 2 + 48));
	}
	else if (player1.getSprite().getPosition().x > (31 * 48) - (view.getSize().x / 3))
	{
		view.setCenter(sf::Vector2f((31 * 48) - (view.getSize().x / 3), 
						window->getSize().y / 2 + 48));
	}
}


//Draw all objects to the window
void Game::render()
{
	window->clear(); 
  
	//Center viewport on player
	window->setView(view);
  
	level.draw(*window);
	player1.draw(*window); 
  
	window->display(); 
}