#pragma once
#include <SFML/Graphics.hpp>

class StartMenu
{
public:
	StartMenu(const bool&);

	bool isActive() const;

	void setActive(const bool isActive) { active = isActive; }

	void draw(sf::RenderWindow& window);
private:
	//Logo
	sf::Texture menuLogo;
	sf::Sprite logoSprite;
	
	//Buttons
	sf::Text startButton;
	sf::Font font;

	//Is menu still active
	bool active;
};