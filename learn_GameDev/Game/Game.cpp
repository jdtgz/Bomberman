#include "Game.h"


Game::Game() : startMenu(true)
{
	srand(time(NULL));

	window = new sf::RenderWindow(sf::VideoMode(750, 800), "Bomberman", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(144);
	view.setSize(sf::Vector2f(window->getSize()));

	//Generate the level
	levelNumber = 1;
	level.generate(levelNumber, &player);

	playerLives = 2;

	scoreboard.setEnemies(0);
	scoreboard.setTime(0);
	scoreboard.setScore(0);

	font.loadFromFile("Textures/font.TTF");

	level.setScoreboardPtr(&scoreboard);
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
		// If start menu is active, player is alive, and level isnt cleared, dont process input
		if (!startMenu.isActive() && player.isAlive() && !level.isLevelCleared())
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
				case sf::Event::JoystickButtonPressed: /* Player bombs with joystick */
					/* Joystick button
					* A = 0
					* B = 1
					*/

					sf::Keyboard::Key button;

					if (evnt.joystickButton.button == 0)
						button = sf::Keyboard::A;
					else if (evnt.joystickButton.button == 1)
						button = sf::Keyboard::B;
					else
						button = sf::Keyboard::Unknown;

					level.keyPressed(button, player);

					break;
				case sf::Event::JoystickMoved: /* Players movement with joystick*/
					float x = sf::Joystick::getAxisPosition(evnt.joystickMove.joystickId, sf::Joystick::X);
					float y = sf::Joystick::getAxisPosition(evnt.joystickMove.joystickId, sf::Joystick::Y);

					//Set threshold of more than 50
					if (abs(x) > 50 || abs(y) > 50)
					{
						//Moving Left
						if (x < -50)
						{
							player.keyReleased(sf::Keyboard::Right);
							player.keyPressed(sf::Keyboard::Left);
						}

						//Moving Right
						if (x > 50)
						{
							player.keyReleased(sf::Keyboard::Left);
							player.keyPressed(sf::Keyboard::Right);
						}

						//Moving up
						if (y < -50)
						{
							player.keyReleased(sf::Keyboard::Down);
							player.keyPressed(sf::Keyboard::Up);
						}

						//Moving Down
						else if (y > 50)
						{
							player.keyReleased(sf::Keyboard::Up);
							player.keyPressed(sf::Keyboard::Down);
						}
					}

					//stop movement if below threshold
					if (abs(x) < 50)
					{
						player.keyReleased(sf::Keyboard::Left);
						player.keyReleased(sf::Keyboard::Right);
					}
					if (abs(y) < 50)
					{
						player.keyReleased(sf::Keyboard::Up);
						player.keyReleased(sf::Keyboard::Down);
					}
					
					break;
			}
		}

		else if (startMenu.isActive())
		{
			/* Set start menu active when button A on joystick or keyboard is pressed */
			if (evnt.type == sf::Event::JoystickButtonPressed)
			{
				if (evnt.joystickButton.button == 0 /* A */)
					startMenu.setActive(false);
			}
			else if (evnt.type == sf::Event::KeyPressed)
			{
				if (evnt.key.code == sf::Keyboard::A)
					startMenu.setActive(false);
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
		if (!level.isLevelCleared())
		{
			player.update(dt.asSeconds());
			updateView();
			level.update(dt.asSeconds(), player);

			//Update Scoreboard numbers & move
			scoreboard.move(view.getCenter().x);
			scoreboard.update();
		}
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
		if (!player.completedDeathAnim() && !level.isLevelCleared())
		{
			level.draw(*window);
			player.draw(*window);
			scoreboard.draw(*window);

			levelScreenClock.restart();
		}

		if (player.completedDeathAnim() || level.isLevelCleared())
		{
			/* Set view so that text is centered */
			sf::View view(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
			window->setView(view);

			if (levelScreenClock.getElapsedTime().asSeconds() >= 5)
			{
				if (player.completedDeathAnim())
				{
					playerLives--;
					scoreboard.setScore(0);

					if (playerLives < 0)
					{
						player.hardReset();
						playerLives = 2;
						levelNumber = 1;
					}
					else
						player.reset();
				}
				else if (level.isLevelCleared())
				{
					levelNumber++;
					player.getSprite().setPosition(0, 100); // Set player to (1, 1) in tile coords
				}

				level.generate(levelNumber, &player);
				
				player.keyReleased(sf::Keyboard::Up);
				player.keyReleased(sf::Keyboard::Down);
				player.keyReleased(sf::Keyboard::Right);
				player.keyReleased(sf::Keyboard::Left);
			}

			sf::Text text;
			text.setFont(font);
			text.setString("Level " + std::to_string(levelNumber));
			/* Set text to center */
			text.setOrigin(sf::Vector2f(text.getLocalBounds().width/2,
				text.getLocalBounds().height / 2));
			/* Set text to middle of window */
			text.setPosition(window->getSize().x / 2, window->getSize().y / 2);
			window->draw(text);
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
			window->getSize().y / 2 -52));
	}
	else if (plr.x < (view.getSize().x / 2) - 48)
	{
		view.setCenter(sf::Vector2f((view.getSize().x / 2) - 48,
			window->getSize().y / 2 - 52));
	}
	else if (plr.x > (31 * 48) - (view.getSize().x / 3))
	{
		view.setCenter(sf::Vector2f((31 * 48) - (view.getSize().x / 3),
			window->getSize().y / 2 - 52));
	}
}