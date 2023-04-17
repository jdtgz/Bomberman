#pragma once
#include "ONeal.h"
class Dahl : public ONeal
{
public:
	Dahl(const Player*);
	Dahl(const Player*, const sf::Vector2i&);
	Dahl(const Player*, const sf::Vector2i&, const direction&);

	~Dahl();
private:
	void init(const sf::Vector2i&, const direction&);
};