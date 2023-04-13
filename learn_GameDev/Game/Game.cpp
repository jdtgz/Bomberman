#include "Game.h"


Game::Game() : startMenu(true)
{
	//Randomize generator
	srand(time(NULL));

	//Create a new window
	window = new sf::RenderWindow(sf::VideoMode(750, 750), "Bomberman");
	window->setFramerateLimit(144);

	view.setSize(sf::Vector2f(window->getSize()));

	//player.getSprite().setPosition(48 * 31 / 2, 48 * 13 / 2);

	//Generate the level
	levelNumber = 0;
	levelRegenPause = 0;
	level.generate(levelNumber, &player);
}


Game::~Game() 
{
	//Unallocate window
	delete window; 
}


// Runs the game
// Keeps track of time for movement and animations
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
		
			//Detect all collisions and adjust player accordingly
			level.collisions(player);

			//Tick
			update(timePerFrame); 
		}

		//Display updated gamestate
		render(timePerFrame);
	}
}


//Event manager
void Game::processEvents()
{
	sf::Event evnt;
	while (window->pollEvent(evnt))
	{
		// If start menu is active, dont go through game events
		if (!startMenu.isActive() && player.isAlive())
		{
			switch (evnt.type)
			{
				// Tell the player when a key is down
				case sf::Event::KeyPressed:
					// manage the player's movement inputs
					player.keyPressed(evnt.key.code);

					// manage the player's bomb inputs
					level.keyPressed(evnt.key.code, player);
					break;
					// Tell the player when a key is released
				case sf::Event::KeyReleased:
					// manage the player's movement inputs
					player.keyReleased(evnt.key.code);
					break;
			}
		}

		//Closes the window
		if (evnt.type == sf::Event::Closed)
			window->close();
	}
}


// Tick
void Game::update(const sf::Time& dt)
{
	//If start menu is active, dont update game
	if (!startMenu.isActive())
	{
		// update the player's animations and position
		player.update(dt.asSeconds());

		//Prevent viewport from going off of the map
		if (player.getSprite().getPosition().x > (view.getSize().x / 2) - 48 &&
			player.getSprite().getPosition().x < (31 * 48) - (view.getSize().x / 3))
		{
			view.setCenter(sf::Vector2f(player.getSprite().getPosition().x,
				window->getSize().y / 2 + 48));
		}
		else if (player.getSprite().getPosition().x < (view.getSize().x / 2) - 48)
		{
			view.setCenter(sf::Vector2f((view.getSize().x / 2) - 48,
				window->getSize().y / 2 + 48));
		}
		else if (player.getSprite().getPosition().x > (31 * 48) - (view.getSize().x / 3))
		{
			view.setCenter(sf::Vector2f((31 * 48) - (view.getSize().x / 3),
				window->getSize().y / 2 + 48));
		}

		// update all in-game objects 
		level.update(dt.asSeconds(), player);
	}
	else
	{
		startMenu.update();
	}
}


// Draw all objects to the window
void Game::render(const sf::Time& dt)
{
	window->clear(); 
  
	//If start menu is active, dont render game
	if (!startMenu.isActive())
	{
		//Center viewport on player
		window->setView(view);

		// draw the level and player 
		if (!player.completedDeathAnim())
		{
			level.draw(*window);
			player.draw(*window);
		}
		else
		{
			levelRegenPause += dt.asSeconds();
			//Wait time for level regeneration
			if (levelRegenPause >= 5)
			{
				levelRegenPause = 0;
				level.generate(levelNumber, &player);
				player.reset();
			}
		}
	}
	else
	{
		startMenu.draw(*window);
	}
  
	window->display(); 
}