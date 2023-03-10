#pragma once
#include <SFML/Graphics.hpp>

class StartMenu
{
public:
	StartMenu(bool active = true);

	bool isActive() const { return m_active; }

	void update();
	void draw(sf::RenderWindow& window);
private:
	//Logo
	sf::Texture m_menu_logo;
	sf::Sprite m_logo_sprite;
	
	//Buttons
	sf::Text m_start_button;
	sf::Font m_font;

	//Is menu still active
	bool m_active;
};

