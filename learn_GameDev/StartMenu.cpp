#include "StartMenu.h"

StartMenu::StartMenu(bool active)
{
	m_menu_logo.loadFromFile("Logo.png");

	m_logo_sprite.setTexture(m_menu_logo);
	m_logo_sprite.setOrigin(m_menu_logo.getSize().x / 2, 0);

	m_font.loadFromFile("font.TTF");

	m_start_button.setString("Start");
	m_start_button.setFont(m_font);
	m_start_button.setOrigin(m_start_button.getLocalBounds().width / 2, 0);

	m_active = active;
}

void StartMenu::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_active = false;
}

void StartMenu::draw(sf::RenderWindow& window)
{
	m_logo_sprite.setPosition(window.getSize().x/2, 0);
	window.draw(m_logo_sprite);

	m_start_button.setPosition(window.getSize().x/2, m_menu_logo.getSize().y + 50);
	window.draw(m_start_button);
}
