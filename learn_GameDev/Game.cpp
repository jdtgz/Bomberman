#include "Game.h"


Game::Game()
	: window(sf::VideoMode(600, 600), "GAME!!"), player()
{
	ptrDir = new bool[4]; 
	player.setRadius(40.f); 
	player.setPosition(100.f, 100.f); 
	player.setFillColor(sf::Color::Cyan); 
}


Game::~Game() 
{ 
	delete[] ptrDir; 
}


void Game::run()
{
	while (window.isOpen())
	{
		processEvents(); 
		update(); 
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
		case sf::Event::Closed:
			window.close(); 
		case sf::Event::KeyPressed:

		case sf::Event::KeyReleased:


		}
	}
}


void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	
}


void Game::update()
{

}


void Game::render()
{
	window.clear(); 
	window.draw(player); 
	window.display(); 
}