#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Scoreboard
{
public:

	Scoreboard(int startScore, int startEnemies)
	{
		score = startScore;
		enemies = startEnemies;
		time = 200;

		background.setSize(sf::Vector2f(700, 150));
	}
	Scoreboard();

	void setScore(int);
	int getScore();

	void setEnemies(int);
	int setScore();

	void setTime(int);
	int getTime();

	//Move Position of scoreboard
	void move(int);

	//Draw scoreboard & update data
	void update();

private:

	int time, score, enemies;
	sf::Text timeTxt, scoreTxt, enemiesTxt;
	sf::RectangleShape background;

};

