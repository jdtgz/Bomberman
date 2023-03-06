#pragma once
#include <SFML/Graphics.hpp>

class StartMenu
{
public:
	StartMenu();


private:
	//Logo
	sf::Texture m_menu_logo;
	
	//Buttons
	sf::Text m_start_button;
};

