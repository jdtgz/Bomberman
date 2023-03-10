#include "Game.h"

Game::Game() : startMenu(true)
{
	//Randomize generator
	srand(time(NULL));

	//Create a new window
	window = new sf::RenderWindow(sf::VideoMode(750, 750), "Bomberman");
	window->setFramerateLimit(144);

	//Generate the level
	level.generate(levelNumber);

	view.setSize(sf::Vector2f(window->getSize()));

	player.getSprite().setPosition(48 * 31 / 2, 48 * 13 / 2);

	tempBomb.x = -1;
	tempBomb.y = -1;
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
		level.collisions(player);

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
		//If start menu is active, dont go through game events
		if (!startMenu.isActive())
		{
			switch (evnt.type)
			{
				//Tell the player when a key is down
			case sf::Event::KeyPressed:
				tempBomb = player.keyPressed(evnt.key.code);
				if (!(tempBomb.x < 0))
					level.setMap(tempBomb, 4);
				break;
				//Tell the player when a key is released
			case sf::Event::KeyReleased:
				player.keyReleased(evnt.key.code);
				break;
				//Close the window
			case sf::Event::Closed:
				window->close();
			}
		}
	}
}


//Tick
void Game::update(const sf::Time& dt)
{
	//If start menu is active, dont update game
	if (!startMenu.isActive())
	{
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

		//update data map for all exploding tiles
		level.setMap(player.getExplotionPosition(), 5);

		level.update(dt.asSeconds(), player.getFlameRange());
	}
	else
	{
		startMenu.update();
	}
}


//Draw all objects to the window
void Game::render()
{
	window->clear(); 
  
	//If start menu is active, dont render game
	if (!startMenu.isActive())
	{
		//Center viewport on player
		window->setView(view);

		// draw the level and player 
		level.draw(*window);
		player.draw(*window);
	}
	else
	{
		startMenu.draw(*window);
	}
  
	window->display(); 
}