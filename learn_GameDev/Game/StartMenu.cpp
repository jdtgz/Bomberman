#include "StartMenu.h"


StartMenu::StartMenu(const bool& actv)
{
	menuLogo.loadFromFile("Textures/Logo.png");

	logoSprite.setTexture(menuLogo);
	logoSprite.setOrigin(menuLogo.getSize().x / 2, 0);

	font.loadFromFile("Textures/font.TTF");

	startButton.setString("Start");
	startButton.setFont(font);
	startButton.setOrigin(startButton.getLocalBounds().width / 2, 0);

	active = actv;
}


bool StartMenu::isActive() const 
{ 
	return active; 
}


void StartMenu::draw(sf::RenderWindow& window)
{
	logoSprite.setPosition(window.getSize().x/2, 0);
	window.draw(logoSprite);

	startButton.setPosition(window.getSize().x/2, menuLogo.getSize().y + 50);
	window.draw(startButton);
}