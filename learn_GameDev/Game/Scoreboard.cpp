#include "Scoreboard.h"

Scoreboard::Scoreboard()
{
	font.loadFromFile("Textures/font.TTF");

	background.setSize(sf::Vector2f(750, 150));
	background.setFillColor(sf::Color(125, 18, 255));

	background.setPosition(sf::Vector2f(-50, -100));
	timeTxt.setPosition(sf::Vector2f(100, 0));
	scoreTxt.setPosition(sf::Vector2f(500, 0));
	enemiesTxt.setPosition(sf::Vector2f(600, 0));
	scoreTxt.setOrigin(scoreTxt.getLocalBounds().width, 0);
	timeTxt.setFont(font);
	scoreTxt.setFont(font);
	enemiesTxt.setFont(font);
}


Scoreboard::~Scoreboard()
{

}


void Scoreboard::setScore(int newNum)
{
	score = newNum;
}


int Scoreboard::getScore()
{
	return score;
}


void Scoreboard::setEnemies(int newNum)
{
	enemies = newNum;
}


void Scoreboard::setTime(int newNum)
{
	time = newNum;
}


int Scoreboard::getTime()
{
	return time;
}


//Move Position of scoreboard
void Scoreboard::move(int newPos)
{
	background.setPosition(sf::Vector2f(newPos - 375, -100));
	timeTxt.setPosition(sf::Vector2f(newPos - 275, 0));
	scoreTxt.setPosition(sf::Vector2f(newPos + 125, 0));
	enemiesTxt.setPosition(sf::Vector2f(newPos + 225, 0));
}


 //update data
void Scoreboard::update()
{
	timeTxt.setString(std::to_string(time));
	scoreTxt.setString(std::to_string(score));
	enemiesTxt.setString("LEFT: " + std::to_string(enemies));

	scoreTxt.setOrigin(scoreTxt.getLocalBounds().width, 0);
}

//Draw scoreboard 
void Scoreboard::draw(sf::RenderWindow& w)
{
	w.draw(background);
	w.draw(timeTxt);
	w.draw(scoreTxt);
	w.draw(enemiesTxt);
}