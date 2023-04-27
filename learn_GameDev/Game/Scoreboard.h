#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Scoreboard
{
public:

	Scoreboard();
	~Scoreboard();

	void setScore(const int&);
	int getScore() const;

	void setLives(const int&);
	int getLives() const;

	void decrementTime(const float&);
	void setTime(const int&);
	int getTime() const;

	//Move Position of scoreboard
	void move(const int&);

	//Draw scoreboard & update data
	void update();
	void draw(sf::RenderWindow& w);

private:
	float time;
	int score, lives;
	sf::Text timeTxt, scoreTxt, livesTxt;
	sf::RectangleShape background;
	sf::Font font;

	const sf::Vector2f DROPSHADOW = { 1.5, 1.5 };
};