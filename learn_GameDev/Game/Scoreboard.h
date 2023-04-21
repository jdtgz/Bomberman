#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Scoreboard
{
public:

	Scoreboard();
	~Scoreboard();

	void setScore(int);
	int getScore();

	void setEnemies(int);

	void setTime(int);
	int getTime();

	//Move Position of scoreboard
	void move(int);

	//Draw scoreboard & update data
	void update();
	void draw(sf::RenderWindow& w);

private:

	int time, score, enemies;
	sf::Text timeTxt, scoreTxt, enemiesTxt;
	sf::RectangleShape background;
	sf::Font font;

};