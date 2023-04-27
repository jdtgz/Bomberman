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

	void decrementTime(const float&);
	void setTime(const int&);
	int getTime();

	//Move Position of scoreboard
	void move(int);

	//Draw scoreboard & update data
	void update();
	void draw(sf::RenderWindow& w);

private:
	float time;
	int score, enemies;
	sf::Text timeTxt, scoreTxt, enemiesTxt;
	sf::RectangleShape background;
	sf::Font font;

};