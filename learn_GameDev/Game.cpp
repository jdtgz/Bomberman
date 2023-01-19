#include "Game.h"


Game::Game()
	: window(sf::VideoMode(600, 600), "GAME!!"), player()
{

	// create the player
	player.setRadius(40.f); 
	player.setOrigin(player.getRadius() / 2, player.getRadius() / 2);
	player.setPosition(100.f, 100.f); 
	player.setFillColor(sf::Color::Cyan); 
}


Game::~Game() 
{ 
}


void Game::run()
{
	sf::Clock clock; 
	sf::Time timeSinceLastUpdate = sf::Time::Zero; 
	while (window.isOpen())
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


void Game::processEvents()
{
	sf::Event evnt; 
	while (window.pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(evnt.key.code, true); 
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(evnt.key.code, false); 
			break; 
		case sf::Event::Closed: 
			window.close(); 
			break; 
		}
	}
}


void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (isPressed)
	{
		p_isMoving = true;
		switch (key)
		{
		case sf::Keyboard::Key::W:
			p_dir = 0;
			break;
		case sf::Keyboard::Key::D:
			p_dir = 1;
			break;
		case sf::Keyboard::Key::S:
			p_dir = 2;
			break;
		case sf::Keyboard::Key::A:
			p_dir = 3;
			break;
		}
	}
	else
	{
		p_dir = -1; 
		p_isMoving = false; 
	}
}


void Game::update(sf::Time dt)
{
	p_speed = 200.f;
	offset = { 0.f, 0.f }; 
	if (p_isMoving)
	{
		switch (p_dir)
		{
			case NORTH:
				offset.y -= p_speed;
				break;
			case EAST:
				offset.x += p_speed;
				break;
			case SOUTH: 
				offset.y += p_speed; 
				break;
			case WEST:
				offset.x -= p_speed;
				break;
		}
	
		player.move(offset * dt.asSeconds()); 
	}
}


void Game::render()
{
	window.clear(); 
	window.draw(player); 
	window.display(); 
}