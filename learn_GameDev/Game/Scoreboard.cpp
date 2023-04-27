#include "Scoreboard.h"

Scoreboard::Scoreboard()
{
	score = 0;
	lives = 0;
	time = 0.f;

	font.loadFromFile("Textures/font.TTF");

	background.setSize(sf::Vector2f(750, 150));
	background.setFillColor(sf::Color(125, 18, 255));

	background.setPosition(sf::Vector2f(-50, -100));
	timeTxt.setPosition(sf::Vector2f(0, 0));
	scoreTxt.setPosition(sf::Vector2f(500, 0));
	livesTxt.setPosition(sf::Vector2f(600, 0));
	scoreTxt.setOrigin(scoreTxt.getLocalBounds().width, 0);
	timeTxt.setFont(font);
	scoreTxt.setFont(font);
	livesTxt.setFont(font);
}


Scoreboard::~Scoreboard()
{

}


void Scoreboard::setScore(const int& nScore)
{
	score = nScore;
}


int Scoreboard::getScore() const
{
	return score;
}


void Scoreboard::setLives(const int& nLives)
{
	lives = nLives;
}


int Scoreboard::getLives() const
{
	return 0;
}


void Scoreboard::decrementTime(const float& dt)
{
	time -= dt;
}


void Scoreboard::setTime(const int& nTime)
{
	time = nTime;
}


int Scoreboard::getTime() const
{
	return time;
}


//Move Position of scoreboard
void Scoreboard::move(const int& newPos)
{
	background.setPosition(sf::Vector2f(newPos - 375, -100));
	timeTxt.setPosition(sf::Vector2f(newPos - 325, 0));
	scoreTxt.setPosition(sf::Vector2f(newPos + 125, 0));
	livesTxt.setPosition(sf::Vector2f(newPos + 225, 0));
}


 //update data
void Scoreboard::update()
{
	timeTxt.setString("TIME\t" + std::to_string((time > 0 ? (int)time : 0)));
	scoreTxt.setString(std::to_string(score));
	livesTxt.setString("LEFT " + std::to_string(lives));

	scoreTxt.setOrigin(scoreTxt.getLocalBounds().width, 0);
}


//Draw scoreboard 
void Scoreboard::draw(sf::RenderWindow& w)
{
	w.draw(background);

	timeTxt.move(DROPSHADOW);
	timeTxt.setFillColor(sf::Color::Black);
	w.draw(timeTxt);

	timeTxt.move(-DROPSHADOW);
	timeTxt.setFillColor(sf::Color::White);
	w.draw(timeTxt);
	
	scoreTxt.move(DROPSHADOW);
	scoreTxt.setFillColor(sf::Color::Black);
	w.draw(scoreTxt);

	scoreTxt.move(-DROPSHADOW);
	scoreTxt.setFillColor(sf::Color::White);
	w.draw(scoreTxt);

	livesTxt.move(DROPSHADOW);
	livesTxt.setFillColor(sf::Color::Black);
	w.draw(livesTxt);

	livesTxt.move(-DROPSHADOW);
	livesTxt.setFillColor(sf::Color::White);
	w.draw(livesTxt);
}