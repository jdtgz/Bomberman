#pragma once
#include "SFML/Graphics.hpp"
class Game
{
public:
	Game(); 
	~Game(); 
	void run(); 

private:
	void processEvents();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed); 
	void update();
	void render();
	
private:
	bool* ptrDir; 
	sf::RenderWindow window; 
	sf::CircleShape player; 
};

