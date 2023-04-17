#include "Game.h"


Game::Game() : startMenu(true)
{
	srand(time(NULL));

	window = new sf::RenderWindow(sf::VideoMode(750, 750), "Bomberman", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(144);
	view.setSize(sf::Vector2f(window->getSize()));

	//Generate the level
	levelNumber = 0;
	levelRegenPause = 0;
	level.generate(levelNumber, &player);
}


Game::~Game() 
{
	delete window; 
}


// Runs the game
// Keeps track of time for movement and animations
void Game::run()
{
	sf::Clock clock; 
	sf::Time timeSinceLastTick = sf::Time::Zero;

	while (window->isOpen())
	{
		processEvents();

		timeSinceLastTick += clock.restart();

		// Take input and update level stage while current frame is active
		while (timeSinceLastTick > timePerFrame)
		{
			timeSinceLastTick -= timePerFrame;
			processEvents();
			level.collisions(player);
			update(timePerFrame); 
		}
		render(timePerFrame);
	}
}


// Takes user input and interprets what it means 
void Game::processEvents()
{
	sf::Event evnt;
	while (window->pollEvent(evnt))
	{
		// If start menu is active and playe is alive, dont process input
		if (!startMenu.isActive() && player.isAlive())
		{
			switch (evnt.type)
			{
				case sf::Event::KeyPressed:
					// manage the player's movement inputs
					player.keyPressed(evnt.key.code);

					// manage the player's bomb inputs
					level.keyPressed(evnt.key.code, player);
					break;
				case sf::Event::KeyReleased:
					// manage the player's movement inputs
					player.keyReleased(evnt.key.code);
					break;
			}
		}
		
		// Closes window
		if (evnt.type == sf::Event::Closed)
			window->close();
	}
}


// Updates the state of all level and window objects in game of a single frame
// Calls functions from Level, player, and game for real-time updates
void Game::update(const sf::Time& dt)
{
	// If start menu is active, dont update game
	if (!startMenu.isActive())
	{
		player.update(dt.asSeconds());
		updateView(); 
		level.update(dt.asSeconds(), player);
	}
	// Else, update the menu
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


// Uses the player's position to keep viewport focused on them
void Game::updateView()
{
	sf::Vector2f plr = player.getSprite().getPosition(); 

	/*Need commnets on what each condition is testing*/
	if (plr.x > (view.getSize().x / 2) - 48 && plr.x < (31 * 48) - (view.getSize().x / 3))
	{
		view.setCenter(sf::Vector2f(player.getSprite().getPosition().x,
			window->getSize().y / 2 + 48));
	}
	else if (plr.x < (view.getSize().x / 2) - 48)
	{
		view.setCenter(sf::Vector2f((view.getSize().x / 2) - 48,
			window->getSize().y / 2 + 48));
	}
	else if (plr.x > (31 * 48) - (view.getSize().x / 3))
	{
		view.setCenter(sf::Vector2f((31 * 48) - (view.getSize().x / 3),
			window->getSize().y / 2 + 48));
	}
}