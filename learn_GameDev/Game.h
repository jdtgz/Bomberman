#pragma once
#include "SFML/Graphics.hpp"
#include "TextureHolder.h"
class Game
{
public:
	Game(); 
	~Game(); 
	void run(); 

private:
	void processEvents();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed); 
	void update(sf::Time);
	void render();
	
private:
	// sfml screen
	sf::RenderWindow window; 

	// indicator for headeing 
	enum directions {NORTH = 0, EAST, SOUTH, WEST};

	sf::Time TimePerFrame = sf::seconds(1.f / 60.f); 

	// Player variable (will be a class in the future)
	TextureHolder gameTextures; 
	sf::Sprite player; 
	// bool to determine stillness 
	bool p_isMoving = false; 
	// player heading
	int p_dir;
	// player speed
	int p_speed = 200.f; 
	// offset to move player
	sf::Vector2f offset;
};

